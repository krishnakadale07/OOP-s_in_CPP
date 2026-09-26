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

    int recordNumber; // Stores the one-based record number requested by the user.

    std::cout
        << "Enter record number to read (1 to 3): ";

    std::cin >> recordNumber; // Read which of the three records to select.

    if (recordNumber < 1 || recordNumber > 3) { // Reject record numbers outside the available range.

        std::cerr
            << "Invalid record number.\n";

        return 1; // Stop because the requested offset would be invalid.
    }

    const std::streamoff offset =
        static_cast<std::streamoff>(
            recordNumber - 1
        ) *
        static_cast<std::streamoff>(
            sizeof(StudentRecord)
        ); // Convert the one-based record number to a zero-based byte offset.

    inputFile.seekg(
        offset,
        std::ios::beg
    ); // Move the read pointer directly to the selected record.

    StudentRecord selectedStudent{}; // Holds the record read from the chosen file position.

    inputFile.read(
        reinterpret_cast<char*>(&selectedStudent),
        sizeof(selectedStudent)
    ); // Read one complete record starting at the calculated offset.

    if (!inputFile) { // Detect a failed or incomplete read.

        std::cerr
            << "Error: Could not read selected record.\n";

        return 1; // Stop rather than print incomplete record data.
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