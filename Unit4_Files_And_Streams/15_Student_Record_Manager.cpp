#include <cstdio>  // Provides remove and rename for replacing the records file.
#include <fstream> // Provides input and output file streams.
#include <iostream> // Provides console input and output streams.
#include <limits> // Provides the input-buffer size used when discarding a newline.
#include <sstream> // Provides string streams for parsing record fields.
#include <string> // Provides strings for names, lines, and record fields.

void addStudent() { // Collect one student record and append it to the data file.

    std::ofstream outputFile(
        "student_records.txt",
        std::ios::app // Preserve earlier records and add the new record at the end.
    ); // Open the student records file for appending.

    if (!outputFile) { // Check whether the file opened successfully.

        std::cerr
            << "Error: Could not open student_records.txt\n";

        return; // Leave without prompting if the record cannot be saved.
    }

    int rollNumber; // Stores the student's numeric roll number.
    std::string name; // Stores the student's full name.
    double marks; // Stores the student's marks.

    std::cout << "Enter roll number: "; // Prompt for the student identifier.
    std::cin >> rollNumber; // Read the numeric roll number.

    std::cout << "Enter name: "; // Prompt for the student's name.

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    ); // Discard the leftover newline before reading a complete name line.

    std::getline(
        std::cin,
        name
    ); // Read the full name, including spaces.

    std::cout << "Enter marks: "; // Prompt for the student's marks.
    std::cin >> marks; // Read the numeric marks value.

    outputFile
        << rollNumber
        << '|'
        << name
        << '|'
        << marks
        << '\n'; // Save the three fields separated by | for later parsing.

    std::cout
        << "Record added successfully.\n"; // Confirm that the record was saved.
}

    void displayStudents() { // Read and print every valid student record.

    std::ifstream inputFile(
        "student_records.txt"
    ); // Open the records file for reading.

    if (!inputFile) { // Handle the case where no records file exists or can be opened.

        std::cout
            << "No student record file found.\n";

        return; // Leave because there are no records to display.
    }

    std::string line; // Holds one record line from the file at a time.

    std::cout
        << "\nRoll No.\tName\t\tMarks\n"; // Print headings for the displayed columns.

    std::cout
        << "----------------------------------------\n"; // Separate the headings from the records.

    while (std::getline(inputFile, line)) { // Read each saved record line.

        std::stringstream record(line); // Treat the current line as a stream of fields.

        std::string rollText; // Receives the roll number field.
        std::string name; // Receives the student's name field.
        std::string marksText; // Receives the student's marks field.

        if (
            std::getline(record, rollText, '|') &&
            std::getline(record, name, '|') &&
            std::getline(record, marksText)
        ) { // Display only records whose three fields were all extracted.

            std::cout
                << rollText
                << "\t\t"
                << name
                << "\t\t"
                << marksText
                << '\n'; // Print the parsed fields as one table row.
        }
    }
}

void searchStudent() { // Find and display the record with a requested roll number.

    std::ifstream inputFile(
        "student_records.txt"
    ); // Open the records file for reading.

    if (!inputFile) { // Check whether the records file is available.

        std::cout
            << "No student record file found.\n";

        return; // Leave because there are no records to search.
    }

    int targetRoll; // Stores the roll number the user wants to find.

    std::cout
        << "Enter roll number to search: ";

    std::cin >> targetRoll; // Read the requested roll number.

    std::string line; // Holds one record line from the file.

    bool found = false; // Tracks whether a matching student has been found.

    while (std::getline(inputFile, line)) { // Search records one line at a time.

        std::stringstream record(line); // Prepare the current line for delimiter parsing.

        std::string rollText; // Receives the saved roll number.
        std::string name; // Receives the saved name.
        std::string marksText; // Receives the saved marks.

        if (
            std::getline(record, rollText, '|') &&
            std::getline(record, name, '|') &&
            std::getline(record, marksText)
        ) { // Compare records only after all fields were read successfully.

            if (std::stoi(rollText) == targetRoll) { // Convert and compare this record's roll number.

                std::cout
                    << "Record Found\n";

                std::cout
                    << "Roll Number: "
                    << rollText
                    << '\n'; // Print the matching student's roll number.

                std::cout
                    << "Name: "
                    << name
                    << '\n'; // Print the matching student's name.

                std::cout
                    << "Marks: "
                    << marksText
                    << '\n'; // Print the matching student's marks.

                found = true; // Remember that the requested record was displayed.

                break; // Stop searching once the matching record is found.
            }
        }
    }

    if (!found) { // Report when no record has the requested roll number.

        std::cout
            << "Student not found.\n"; // Inform the user that the search had no match.
    }
}

void updateMarks() { // Replace one student's marks while preserving all other records.

    std::ifstream inputFile(
        "student_records.txt"
    ); // Open the original records for reading.

    std::ofstream temporaryFile(
        "student_records_temp.txt"
    ); // Create a temporary output file for the rewritten records.

    if (!inputFile || !temporaryFile) { // Require both streams before beginning the update.

        std::cerr
            << "Error: Could not open record file(s).\n";

        return; // Leave if either file could not be opened.
    }

    int targetRoll; // Stores which student's record should be updated.
    double newMarks; // Stores the replacement marks value.

    std::cout
        << "Enter roll number to update: ";

    std::cin >> targetRoll; // Read the target student's roll number.

    std::cout
        << "Enter new marks: ";

    std::cin >> newMarks; // Read the new marks value.

    std::string line; // Holds one original record line at a time.

    bool found = false; // Tracks whether the target record appears in the file.

    while (std::getline(inputFile, line)) { // Process every saved student record.

        std::stringstream record(line); // Prepare the line for field-by-field parsing.

        std::string rollText; // Receives the roll number field.
        std::string name; // Receives the name field.
        std::string marksText; // Receives the current marks field.

        if (
            std::getline(record, rollText, '|') &&
            std::getline(record, name, '|') &&
            std::getline(record, marksText)
        ) { // Rewrite records only when each expected field is present.

            if (std::stoi(rollText) == targetRoll) { // Check whether this is the record to update.

                temporaryFile
                    << rollText
                    << '|'
                    << name
                    << '|'
                    << newMarks
                    << '\n'; // Write the target record with the replacement marks.

                found = true; // Remember that the requested record was updated.

            } else { // Keep every nonmatching record unchanged.

                temporaryFile
                    << line
                    << '\n'; // Copy the original record into the temporary file.
            }
        }
    }

    inputFile.close(); // Close the original before attempting to replace it.
    temporaryFile.close(); // Flush and close the rewritten temporary file.

    if (!found) { // Do not replace the original when no student matched.

        std::remove(
            "student_records_temp.txt"
        ); // Remove the temporary file because it contains no useful update.

        std::cout
            << "Student not found. "
            << "No changes made.\n"; // Explain that the original file was left unchanged.

        return; // Finish this operation without replacing the data file.
    }

    if (
        std::remove(
            "student_records.txt"
        ) != 0 ||
        std::rename(
            "student_records_temp.txt",
            "student_records.txt"
        ) != 0
    ) { // Remove the original and rename the completed temporary file into its place.

        std::cerr
            << "Error: Could not replace the record file.\n";

        return; // Leave if the updated file could not be installed.
    }

    std::cout
        << "Marks updated successfully.\n"; // Confirm that the update completed.
}

int main() { // Program execution starts here.

    int choice; // Stores the user's menu selection.

    do { // Display the menu at least once and repeat until the user exits.

        std::cout
            << "\nStudent Record Manager\n"; // Display the program title.

        std::cout
            << "1. Add Student\n"; // List the add-record option.

        std::cout
            << "2. Display All Students\n"; // List the display-records option.

        std::cout
            << "3. Search Student\n"; // List the search option.

        std::cout
            << "4. Update Marks\n"; // List the update-marks option.

        std::cout
            << "0. Exit\n"; // List the exit option.

        std::cout
            << "Enter choice: "; // Prompt for a menu selection.

        std::cin >> choice; // Read the selected option.

        switch (choice) { // Call the function corresponding to the selected option.

            case 1:
                addStudent(); // Add one student record.
                break; // Prevent falling through to another menu option.

            case 2:
                displayStudents(); // Display every saved student.
                break; // End this menu choice.

            case 3:
                searchStudent(); // Search for a student by roll number.
                break; // End this menu choice.

            case 4:
                updateMarks(); // Update the marks for a student.
                break; // End this menu choice.

            case 0:
                std::cout
                    << "Exiting program.\n";
                break; // Leave the switch; the loop condition will exit afterward.

            default:
                std::cout
                    << "Invalid choice. Try again.\n"; // Prompt again after an unrecognized option.
        }

    } while (choice != 0); // Repeat the menu until the exit option is selected.

    return 0; // Report successful completion.
}