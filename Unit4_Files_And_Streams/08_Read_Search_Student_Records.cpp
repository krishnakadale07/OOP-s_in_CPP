#include <fstream>  // Provides input file stream support.
#include <iostream> // Provides console input and output streams.
#include <sstream>  // Provides string streams for splitting each record.
#include <string>   // Provides strings for input lines and record fields.

int main() { // Program execution starts here.

    std::ifstream inputFile("students.txt"); // Open the saved student records.

    if (!inputFile) { // Verify that the record file could be opened.
        std::cerr
            << "Error: Could not open students.txt\n";
        return 1; // Stop because no records can be searched.
    }

    int targetRollNumber; // Stores the roll number requested by the user.

    std::cout
        << "Enter roll number to search: ";

    std::cin >> targetRollNumber; // Read the roll number to look up.

    std::string line; // Holds one complete record line from the file.

    bool found = false; // Tracks whether the requested record has been located.

    while (std::getline(inputFile, line)) { // Process records one line at a time.

        std::stringstream record(line); // Treat the current line as a stream of fields.

        std::string rollText; // Receives the roll number text before the first |.
        std::string name; // Receives the name between the separators.
        std::string marksText; // Receives the marks text after the second |.

        if (
            std::getline(record, rollText, '|') &&
            std::getline(record, name, '|') &&
            std::getline(record, marksText)
        ) { // Continue only when all three fields were extracted.

            int rollNumber =
                std::stoi(rollText); // Convert the saved roll number from text to an integer.

            double marks =
                std::stod(marksText); // Convert the saved marks from text to a number.

            if (rollNumber == targetRollNumber) { // Check whether this is the requested student.

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

                found = true; // Remember that a matching record was printed.

                break; // Stop searching after finding the requested record.
            }
        }
    }

    if (!found) { // Handle the case where no record matched the requested roll number.
        std::cout
            << "Student record not found.\n";
    }

    return 0; // Report successful completion of the search.
}