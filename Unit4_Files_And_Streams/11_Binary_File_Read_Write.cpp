#include <cstring> // Provides bounded copying for the fixed-size name array.
#include <fstream> // Provides binary input and output file streams.
#include <iostream> // Provides console input and output streams.

struct StudentRecord { // Groups the fields that will be stored together in binary form.
    int rollNumber; // Stores the student's numeric identifier.
    char name[30]; // Stores the name in a fixed-size character array.
    float marks; // Stores the student's marks as a floating-point value.
};

int main() { // Program execution starts here.

    StudentRecord student{}; // Zero-initialize all fields before assigning values.

    student.rollNumber = 101; // Set the example student's roll number.

    std::strncpy(
        student.name,
        "Amit Patil",
        sizeof(student.name) - 1
    ); // Copy the name while leaving room for the terminating null character.

    student.marks = 85.5F; // Set the example student's marks.

    {
        std::ofstream outputFile(
            "students.dat",
            std::ios::binary // Write raw bytes rather than formatted text.
        ); // Open the binary file for output.

        if (!outputFile) { // Check whether the binary file was created successfully.

            std::cerr
                << "Error: Could not create students.dat\n";

            return 1; // Stop if the record cannot be written.
        }

        outputFile.write(
            reinterpret_cast<const char*>(&student),
            sizeof(student)
        ); // Write the bytes occupied by the complete StudentRecord object.
    }

    StudentRecord readStudent{}; // Provides storage for the record read back from disk.

    {
        std::ifstream inputFile(
            "students.dat",
            std::ios::binary // Read the file as raw bytes.
        ); // Open the binary file for input.

        if (!inputFile) { // Check whether the binary file opened successfully.

            std::cerr
                << "Error: Could not open students.dat\n";

            return 1; // Stop if the saved record cannot be accessed.
        }

        inputFile.read(
            reinterpret_cast<char*>(&readStudent),
            sizeof(readStudent)
        ); // Read exactly one record's worth of bytes into the object.

        if (!inputFile) { // Detect a failed or incomplete record read.

            std::cerr
                << "Error: Could not read record from students.dat\n";

            return 1; // Stop rather than display invalid record data.
        }
    }

    std::cout
        << "Roll Number: "
        << readStudent.rollNumber
        << '\n'; // Display the roll number recovered from the binary file.

    std::cout
        << "Name: "
        << readStudent.name
        << '\n'; // Display the name recovered from the binary file.

    std::cout
        << "Marks: "
        << readStudent.marks
        << '\n'; // Display the marks recovered from the binary file.

    return 0; // Report successful completion.
}