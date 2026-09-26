#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {

    std::ifstream inputFile("students.txt");

    std::ofstream temporaryFile(
        "students_temp.txt"
    );

    if (!inputFile || !temporaryFile) {

        std::cerr
            << "Error: Could not open file(s).\n";

        return 1;
    }

    int targetRollNumber;
    double updatedMarks;

    std::cout
        << "Enter roll number to update: ";

    std::cin >> targetRollNumber;

    std::cout
        << "Enter updated marks: ";

    std::cin >> updatedMarks;

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

            int rollNumber =
                std::stoi(rollText);

            if (rollNumber == targetRollNumber) {

                temporaryFile
                    << rollNumber
                    << '|'
                    << name
                    << '|'
                    << updatedMarks
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

        std::remove("students_temp.txt");

        std::cout
            << "Student record not found. "
            << "No update performed.\n";

        return 0;
    }

    if (std::remove("students.txt") != 0) {

        std::cerr
            << "Error: Could not remove old students.txt\n";

        return 1;
    }

    if (
        std::rename(
            "students_temp.txt",
            "students.txt"
        ) != 0
    ) {

        std::cerr
            << "Error: Could not rename temporary file.\n";

        return 1;
    }

    std::cout
        << "Student marks updated successfully.\n";

    return 0;
}