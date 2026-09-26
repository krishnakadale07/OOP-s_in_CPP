#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

void addStudent() {

    std::ofstream outputFile(
        "student_records.txt",
        std::ios::app
    );

    if (!outputFile) {

        std::cerr
            << "Error: Could not open student_records.txt\n";

        return;
    }

    int rollNumber;
    std::string name;
    double marks;

    std::cout << "Enter roll number: ";
    std::cin >> rollNumber;

    std::cout << "Enter name: ";

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );

    std::getline(
        std::cin,
        name
    );

    std::cout << "Enter marks: ";
    std::cin >> marks;

    outputFile
        << rollNumber
        << '|'
        << name
        << '|'
        << marks
        << '\n';

    std::cout
        << "Record added successfully.\n";
}

void displayStudents() {

    std::ifstream inputFile(
        "student_records.txt"
    );

    if (!inputFile) {

        std::cout
            << "No student record file found.\n";

        return;
    }

    std::string line;

    std::cout
        << "\nRoll No.\tName\t\tMarks\n";

    std::cout
        << "----------------------------------------\n";

    while (std::getline(inputFile, line)) {

        std::stringstream record(line);

        std::string rollText;
        std::string name;
        std::string marksText;

        if (
            std::getline(record, rollText, '|') &&
            std::getline(record, name, '|') &&
            std::getline(record, marksText)
        ) {

            std::cout
                << rollText
                << "\t\t"
                << name
                << "\t\t"
                << marksText
                << '\n';
        }
    }
}

void searchStudent() {

    std::ifstream inputFile(
        "student_records.txt"
    );

    if (!inputFile) {

        std::cout
            << "No student record file found.\n";

        return;
    }

    int targetRoll;

    std::cout
        << "Enter roll number to search: ";

    std::cin >> targetRoll;

    std::string line;

    bool found = false;

    while (std::getline(inputFile, line)) {

        std::stringstream record(line);

        std::string rollText;
        std::string name;
        std::string marksText;

        if (
            std::getline(record, rollText, '|') &&
            std::getline(record, name, '|') &&
            std::getline(record, marksText)
        ) {

            if (std::stoi(rollText) == targetRoll) {

                std::cout
                    << "Record Found\n";

                std::cout
                    << "Roll Number: "
                    << rollText
                    << '\n';

                std::cout
                    << "Name: "
                    << name
                    << '\n';

                std::cout
                    << "Marks: "
                    << marksText
                    << '\n';

                found = true;

                break;
            }
        }
    }

    if (!found) {

        std::cout
            << "Student not found.\n";
    }
}

void updateMarks() {

    std::ifstream inputFile(
        "student_records.txt"
    );

    std::ofstream temporaryFile(
        "student_records_temp.txt"
    );

    if (!inputFile || !temporaryFile) {

        std::cerr
            << "Error: Could not open record file(s).\n";

        return;
    }

    int targetRoll;
    double newMarks;

    std::cout
        << "Enter roll number to update: ";

    std::cin >> targetRoll;

    std::cout
        << "Enter new marks: ";

    std::cin >> newMarks;

    std::string line;

    bool found = false;

    while (std::getline(inputFile, line)) {

        std::stringstream record(line);

        std::string rollText;
        std::string name;
        std::string marksText;

        if (
            std::getline(record, rollText, '|') &&
            std::getline(record, name, '|') &&
            std::getline(record, marksText)
        ) {

            if (std::stoi(rollText) == targetRoll) {

                temporaryFile
                    << rollText
                    << '|'
                    << name
                    << '|'
                    << newMarks
                    << '\n';

                found = true;

            } else {

                temporaryFile
                    << line
                    << '\n';
            }
        }
    }

    inputFile.close();
    temporaryFile.close();

    if (!found) {

        std::remove(
            "student_records_temp.txt"
        );

        std::cout
            << "Student not found. "
            << "No changes made.\n";

        return;
    }

    if (
        std::remove(
            "student_records.txt"
        ) != 0 ||
        std::rename(
            "student_records_temp.txt",
            "student_records.txt"
        ) != 0
    ) {

        std::cerr
            << "Error: Could not replace the record file.\n";

        return;
    }

    std::cout
        << "Marks updated successfully.\n";
}

int main() {

    int choice;

    do {

        std::cout
            << "\nStudent Record Manager\n";

        std::cout
            << "1. Add Student\n";

        std::cout
            << "2. Display All Students\n";

        std::cout
            << "3. Search Student\n";

        std::cout
            << "4. Update Marks\n";

        std::cout
            << "0. Exit\n";

        std::cout
            << "Enter choice: ";

        std::cin >> choice;

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateMarks();
                break;

            case 0:
                std::cout
                    << "Exiting program.\n";
                break;

            default:
                std::cout
                    << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}