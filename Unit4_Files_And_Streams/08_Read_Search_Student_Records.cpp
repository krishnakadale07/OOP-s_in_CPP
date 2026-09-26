#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {

    std::ifstream inputFile("students.txt");

    if (!inputFile) {
        std::cerr
            << "Error: Could not open students.txt\n";
        return 1;
    }

    int targetRollNumber;

    std::cout
        << "Enter roll number to search: ";

    std::cin >> targetRollNumber;

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

            double marks =
                std::stod(marksText);

            if (rollNumber == targetRollNumber) {

                std::cout
                    << "Record Found\n";

                std::cout
                    << "Roll Number: "
                    << rollNumber << '\n';

                std::cout
                    << "Name: "
                    << name << '\n';

                std::cout
                    << "Marks: "
                    << marks << '\n';

                found = true;

                break;
            }
        }
    }

    if (!found) {
        std::cout
            << "Student record not found.\n";
    }

    return 0;
}