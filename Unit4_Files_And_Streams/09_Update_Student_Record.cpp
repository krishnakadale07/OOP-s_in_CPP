#include <cstdio>  // Provides remove and rename for replacing the data file.
#include <fstream> // Provides input and output file streams.
#include <iostream> // Provides console input and output streams.
#include <sstream> // Provides string streams for splitting record fields.
#include <string> // Provides strings for lines and record fields.

int main() { // Program execution starts here.

    std::ifstream inputFile("students.txt"); // Open the original records for reading.

    std::ofstream temporaryFile(
        "students_temp.txt"
    ); // Create a temporary file to hold the updated records.

    if (!inputFile || !temporaryFile) { // Ensure both streams are ready before processing.

        std::cerr
            << "Error: Could not open file(s).\n";

        return 1; // Stop if either file could not be opened.
    }

    int targetRollNumber; // Stores which student's record should change.
    double updatedMarks; // Stores the replacement marks value.

    std::cout
        << "Enter roll number to update: ";

    std::cin >> targetRollNumber; // Read the roll number to update.

    std::cout
        << "Enter updated marks: ";

    std::cin >> updatedMarks; // Read the new marks value.

    std::string line; // Holds each original record while it is processed.

    bool found = false; // Tracks whether the target student's record exists.

    while (std::getline(inputFile, line)) { // Process each saved record line.

        std::stringstream record(line); // Prepare the line for field-by-field parsing.

        std::string rollText; // Receives the roll number field.
        std::string name; // Receives the student's name field.
        std::string marksText; // Receives the existing marks field.

        if (
            std::getline(record, rollText, '|') &&
            std::getline(record, name, '|') &&
            std::getline(record, marksText)
        ) { // Update or copy only records with all required fields.

            int rollNumber =
                std::stoi(rollText); // Convert the roll number field to an integer.

            if (rollNumber == targetRollNumber) { // Check whether this line belongs to the target student.

                temporaryFile
                    << rollNumber
                    << '|'
                    << name
                    << '|'
                    << updatedMarks
                    << '\n'; // Write the updated record to the temporary file.

                found = true; // Record that the requested student was updated.

            } else { // Preserve records that do not match the requested roll number.

                temporaryFile
                    << line
                    << '\n'; // Copy the original record unchanged.
            }
        }
    }

    inputFile.close(); // Close the source before replacing it.
    temporaryFile.close(); // Flush and close the completed temporary file.

    if (!found) { // Avoid replacing the original when no record matched.

        std::remove("students_temp.txt"); // Delete the unused temporary file.

        std::cout
            << "Student record not found. "
            << "No update performed.\n";

        return 0; // Finish normally because no update was needed.
    }

    if (std::remove("students.txt") != 0) { // Remove the old file before installing the replacement.

        std::cerr
            << "Error: Could not remove old students.txt\n";

        return 1; // Stop if the original file could not be removed.
    }

    if (
        std::rename(
            "students_temp.txt",
            "students.txt"
        ) != 0
    ) { // Rename the completed temporary file to the original file name.

        std::cerr
            << "Error: Could not rename temporary file.\n";

        return 1; // Report failure if the updated file could not be installed.
    }

    std::cout
        << "Student marks updated successfully.\n"; // Confirm that the record was replaced.

    return 0; // Report successful completion.
}