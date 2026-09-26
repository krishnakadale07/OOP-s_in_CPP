#include <fstream>
#include <iostream>
#include <limits>
#include <string>

int main() {

    std::ofstream outputFile(
        "students.txt",
        std::ios::app
    );

    if (!outputFile) {
        std::cerr
            << "Error: Could not open students.txt\n";
        return 1;
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

    std::getline(std::cin, name);

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
        << "Student record saved successfully.\n";

    return 0;
}