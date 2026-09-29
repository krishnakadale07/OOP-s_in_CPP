#include <cstring> // Provides bounded copying for each fixed-size name array.
#include <fstream> // Provides binary input and output file streams.
#include <iostream> // Provides console input and output streams.

struct StudentRecord { // Defines the fixed-size record stored in the binary file.
    int rollNumber; // Stores the student's numeric identifier.
    char name[30]; // Stores the name in a fixed-size character array.
    float marks; // Stores the student's marks.
};

void addRecord(
    std::ofstream& file,
    int rollNumber,
    const char* name,
    float marks
) { // Build one record and append its bytes to the output stream.

    StudentRecord student{}; // Zero-initialize the record, including its name array.

    student.rollNumber = rollNumber; // Copy the supplied roll number into the record.

    std::strncpy(
        student.name,
        name,
        sizeof(student.name) - 1
    ); // Copy at most 29 characters so the name remains null-terminated.

    student.marks = marks; // Copy the supplied marks into the record.

    file.write(
        reinterpret_cast<const char*>(&student),
        sizeof(student)
    ); // Append the complete record as raw bytes.
}

int main() { // Program execution starts here.

    {
        std::ofstream outputFile(
            "records.dat",
            std::ios::binary |
            std::ios::trunc // Replace the file so this run starts with known records.
        ); // Open the binary record file for writing.

        if (!outputFile) { // Check whether the output file opened successfully.

            std::cerr
                << "Error: Could not create records.dat\n";

            return 1; // Stop if sample records cannot be created.
        }

        addRecord(
            outputFile,
            101,
            "Amit",
            85.5F
        ); // Write the first sample record.

        addRecord(
            outputFile,
            102,
            "Neha",
            91.0F
        ); // Write the second sample record.

        addRecord(
            outputFile,
            103,
            "Ravi",
            78.0F
        ); // Write the third sample record.
    }

    std::ifstream inputFile(
        "records.dat",
        std::ios::binary // Read the records as raw bytes.
    ); // Open the populated file for random-access reading.

    if (!inputFile) { // Check whether the input file opened successfully.

        std::cerr
            << "Error: Could not open records.dat\n";

        return 1; // Stop if the records cannot be read.
    }

    int targetRollNumber; // Stores the roll number requested by the user.

    std::cout
        << "Enter roll number to search: ";

    std::cin >> targetRollNumber; // Read the roll number to find.

    StudentRecord selectedStudent{}; // Holds the record matching the requested roll number.
    bool found = false;

    for (int index = 0; index < 3 && !found; ++index) {
        const std::streamoff offset =
            static_cast<std::streamoff>(index) *
            static_cast<std::streamoff>(sizeof(StudentRecord));

        inputFile.seekg(offset, std::ios::beg);

        StudentRecord currentStudent{};
        inputFile.read(
            reinterpret_cast<char*>(&currentStudent),
            sizeof(currentStudent)
        );

        if (!inputFile) {
            std::cerr << "Error: Could not read record from records.dat\n";
            return 1;
        }

        if (currentStudent.rollNumber == targetRollNumber) {
            selectedStudent = currentStudent;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Student with roll number " << targetRollNumber
                  << " was not found.\n";
        return 0;
    }

    std::cout
        << "Roll Number: "
        << selectedStudent.rollNumber
        << '\n'; // Display the selected student's roll number.

    std::cout
        << "Name: "
        << selectedStudent.name
        << '\n'; // Display the selected student's name.

    std::cout
        << "Marks: "
        << selectedStudent.marks
        << '\n'; // Display the selected student's marks.

    return 0; // Report successful completion.
}