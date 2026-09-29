#include <fstream> // Provides binary input and output file streams.
#include <iostream> // Provides console input and output streams.

struct StudentRecord { // Groups the fields that will be stored together in binary form.
    int rollNumber; // Stores the student's numeric identifier.
    char name[30]; // Stores the name in a fixed-size character array.
    float marks; // Stores the student's marks as a floating-point value.
};

int main() { // Program execution starts here.

    StudentRecord students[] = {
        {101, "Amit Patil", 85.5F},
        {102, "Priya Shah", 91.0F},
        {103, "Rohan Desai", 78.5F}
    };
    const int studentCount = sizeof(students) / sizeof(students[0]);

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

        for (int index = 0; index < studentCount; ++index) {
            outputFile.write(
                reinterpret_cast<const char*>(&students[index]),
                sizeof(StudentRecord)
            ); // Write each complete StudentRecord object as raw bytes.
        }

        if (!outputFile) {
            std::cerr << "Error: Could not write all student records\n";
            return 1;
        }
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

        for (int index = 0; index < studentCount; ++index) {
            inputFile.read(
                reinterpret_cast<char*>(&readStudent),
                sizeof(readStudent)
            ); // Read one complete record from the binary file.

            if (!inputFile) { // Detect a failed or incomplete record read.

                std::cerr
                    << "Error: Could not read all records from students.dat\n";

                return 1; // Stop rather than display invalid record data.
            }

            std::cout << "Record " << index + 1 << '\n';
            std::cout << "Roll Number: " << readStudent.rollNumber << '\n';
            std::cout << "Name: " << readStudent.name << '\n';
            std::cout << "Marks: " << readStudent.marks << "\n\n";
        }
    }

    return 0; // Report successful completion.
}