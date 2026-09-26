#include <cstring>
#include <fstream>
#include <iostream>

struct StudentRecord {
    int rollNumber;
    char name[30];
    float marks;
};

void addRecord(
    std::ofstream& file,
    int rollNumber,
    const char* name,
    float marks
) {

    StudentRecord student{};

    student.rollNumber = rollNumber;

    std::strncpy(
        student.name,
        name,
        sizeof(student.name) - 1
    );

    student.marks = marks;

    file.write(
        reinterpret_cast<const char*>(&student),
        sizeof(student)
    );
}

int main() {

    {
        std::ofstream outputFile(
            "records.dat",
            std::ios::binary |
            std::ios::trunc
        );

        if (!outputFile) {

            std::cerr
                << "Error: Could not create records.dat\n";

            return 1;
        }

        addRecord(
            outputFile,
            101,
            "Amit",
            85.5F
        );

        addRecord(
            outputFile,
            102,
            "Neha",
            91.0F
        );

        addRecord(
            outputFile,
            103,
            "Ravi",
            78.0F
        );
    }

    std::ifstream inputFile(
        "records.dat",
        std::ios::binary
    );

    if (!inputFile) {

        std::cerr
            << "Error: Could not open records.dat\n";

        return 1;
    }

    int recordNumber;

    std::cout
        << "Enter record number to read (1 to 3): ";

    std::cin >> recordNumber;

    if (recordNumber < 1 || recordNumber > 3) {

        std::cerr
            << "Invalid record number.\n";

        return 1;
    }

    const std::streamoff offset =
        static_cast<std::streamoff>(
            recordNumber - 1
        ) *
        static_cast<std::streamoff>(
            sizeof(StudentRecord)
        );

    inputFile.seekg(
        offset,
        std::ios::beg
    );

    StudentRecord selectedStudent{};

    inputFile.read(
        reinterpret_cast<char*>(&selectedStudent),
        sizeof(selectedStudent)
    );

    if (!inputFile) {

        std::cerr
            << "Error: Could not read selected record.\n";

        return 1;
    }

    std::cout
        << "Roll Number: "
        << selectedStudent.rollNumber
        << '\n';

    std::cout
        << "Name: "
        << selectedStudent.name
        << '\n';

    std::cout
        << "Marks: "
        << selectedStudent.marks
        << '\n';

    return 0;
}