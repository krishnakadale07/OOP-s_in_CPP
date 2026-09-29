#include <fstream>  // Provides output file stream support.
#include <iostream> // Provides console input and output streams.
#include <limits>   // Provides the maximum stream size used when clearing input.
#include <string>   // Provides the student's name string.

int main() { // Program execution starts here.

    std::ofstream outputFile(
        "students.txt",
        std::ios::app // Preserve earlier records and write this one at the end.
    ); // Open the student data file for appending.

    if (!outputFile) { // Check whether the record file opened successfully.
        std::cerr
            << "Error: Could not open students.txt\n";
        return 1; // Stop if the new record cannot be saved.
    }

    int rollNumber; // Stores the student's numeric roll number.
    std::string name; // Stores the student's full name.
    std::string courseName; // Stores the student's course name.
    std::string mobileNumber; // Stores the mobile number as text to preserve leading zeroes.
    double marks; // Stores the student's marks, including fractional values.

    std::cout << "Enter roll number: "; // Ask for the student's identifier.
    std::cin >> rollNumber; // Read the numeric roll number.

    std::cout << "Enter name: "; // Ask for the student's name.

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    ); // Discard the leftover newline before reading a full line of text.

    std::getline(std::cin, name); // Read the full name, including any spaces.

    std::cout << "Enter course name: ";
    std::getline(std::cin, courseName);

    std::cout << "Enter mobile number: ";
    std::getline(std::cin, mobileNumber);

    std::cout << "Enter marks: "; // Ask for the student's marks.
    std::cin >> marks; // Read the numeric marks value.

    outputFile
        << rollNumber
        << '|'
        << name
        << '|'
        << courseName
        << '|'
        << mobileNumber
        << '|'
        << marks
        << '\n'; // Save fields separated by | so they can be parsed later.

    std::cout
        << "Student record saved successfully.\n"; // Confirm the record was written.

    return 0; // Report successful completion.
}