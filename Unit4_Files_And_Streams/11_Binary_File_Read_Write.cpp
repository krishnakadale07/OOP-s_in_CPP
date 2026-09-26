#include <cstring>
#include <fstream>
#include <iostream>

struct StudentRecord {
    int rollNumber;
    char name[30];
    float marks;
};

int main() {

    StudentRecord student{};

    student.rollNumber = 101;

    std::strncpy(
        student.name,
        "Amit Patil",
        sizeof(student.name) - 1
    );

    student.marks = 85.5F;

    {
        std::ofstream outputFile(
            "students.dat",
            std::ios::binary
        );

        if (!outputFile) {

            std::cerr
                << "Error: Could not create students.dat\n";

            return 1;
        }

        outputFile.write(
            reinterpret_cast<const char*>(&student),
            sizeof(student)
        );
    }

    StudentRecord readStudent{};

    {
        std::ifstream inputFile(
            "students.dat",
            std::ios::binary
        );

        if (!inputFile) {

            std::cerr
                << "Error: Could not open students.dat\n";

            return 1;
        }

        inputFile.read(
            reinterpret_cast<char*>(&readStudent),
            sizeof(readStudent)
        );

        if (!inputFile) {

            std::cerr
                << "Error: Could not read record from students.dat\n";

            return 1;
        }
    }

    std::cout
        << "Roll Number: "
        << readStudent.rollNumber
        << '\n';

    std::cout
        << "Name: "
        << readStudent.name
        << '\n';

    std::cout
        << "Marks: "
        << readStudent.marks
        << '\n';

    return 0;
}