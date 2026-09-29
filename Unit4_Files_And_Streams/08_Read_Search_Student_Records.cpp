#include <algorithm> // Provides maximum column-width calculations.
#include <fstream>  // Provides input file stream support.
#include <iomanip>  // Provides aligned table columns.
#include <iostream> // Provides console input and output streams.
#include <sstream>  // Provides string streams for splitting each record.
#include <string>   // Provides strings for input lines and record fields.
#include <vector>   // Stores all records before the table is displayed.

int main() { // Program execution starts here.

    std::ifstream inputFile("students.txt"); // Open the saved student records.

    if (!inputFile) { // Verify that the record file could be opened.
        std::cerr
            << "Error: Could not open students.txt\n";
        return 1; // Stop because no records can be searched.
    }

    struct StudentRecord {
        std::string rollNumber;
        std::string name;
        std::string courseName;
        std::string mobileNumber;
        std::string marks;
    };

    std::string line; // Holds one complete record line from the file.
    std::vector<StudentRecord> records;

    while (std::getline(inputFile, line)) { // Process records one line at a time.

        std::stringstream record(line); // Treat the current line as a stream of fields.

        StudentRecord student;

        if (
            std::getline(record, student.rollNumber, '|') &&
            std::getline(record, student.name, '|') &&
            std::getline(record, student.courseName, '|') &&
            std::getline(record, student.mobileNumber, '|') &&
            std::getline(record, student.marks)
        ) { // Continue only when all five fields were extracted.
            records.push_back(student);
        }
    }

    int rollWidth = static_cast<int>(std::string("Roll Number").length());
    int nameWidth = static_cast<int>(std::string("Name").length());
    int courseWidth = static_cast<int>(std::string("Course").length());
    int mobileWidth = static_cast<int>(std::string("Mobile Number").length());
    int marksWidth = static_cast<int>(std::string("Marks").length());

    for (const StudentRecord& student : records) {
        rollWidth = std::max(rollWidth, static_cast<int>(student.rollNumber.length()));
        nameWidth = std::max(nameWidth, static_cast<int>(student.name.length()));
        courseWidth = std::max(courseWidth, static_cast<int>(student.courseName.length()));
        mobileWidth = std::max(mobileWidth, static_cast<int>(student.mobileNumber.length()));
        marksWidth = std::max(marksWidth, static_cast<int>(student.marks.length()));
    }

    auto printSeparator = [&]() {
        std::cout << '+' << std::string(rollWidth + 2, '-')
                  << '+' << std::string(nameWidth + 2, '-')
                  << '+' << std::string(courseWidth + 2, '-')
                  << '+' << std::string(mobileWidth + 2, '-')
                  << '+' << std::string(marksWidth + 2, '-') << "+\n";
    };

    auto printRow = [&](const std::string& rollNumber,
                        const std::string& name,
                        const std::string& courseName,
                        const std::string& mobileNumber,
                        const std::string& marks) {
        std::cout << "| " << std::left << std::setw(rollWidth) << rollNumber
                  << " | " << std::setw(nameWidth) << name
                  << " | " << std::setw(courseWidth) << courseName
                  << " | " << std::setw(mobileWidth) << mobileNumber
                  << " | " << std::setw(marksWidth) << marks << " |\n";
    };

    printSeparator();
    printRow("Roll Number", "Name", "Course", "Mobile Number", "Marks");
    printSeparator();

    for (const StudentRecord& student : records) {
        printRow(student.rollNumber, student.name, student.courseName,
                 student.mobileNumber, student.marks);
    }

    printSeparator();

    return 0; // Report successful completion of the search.
}