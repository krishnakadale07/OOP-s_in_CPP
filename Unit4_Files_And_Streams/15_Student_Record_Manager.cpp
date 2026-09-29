#include <algorithm> // Provides remove_if for deleting a student.
#include <cstdio>  // Provides remove and rename for replacing the records file.
#include <fstream> // Provides input and output file streams.
#include <iomanip> // Provides aligned table columns.
#include <iostream> // Provides console input and output streams.
#include <limits> // Provides the input-buffer size used when discarding a newline.
#include <sstream> // Provides string streams for parsing record fields.
#include <string> // Provides strings for names, lines, and record fields.
#include <vector> // Stores parsed student records.

struct StudentRecord {
    int rollNumber;
    std::string name;
    std::string course;
    std::string department;
    double marks;
};

bool parseStudentRecord(const std::string& line, StudentRecord& student) {
    std::stringstream record(line);
    std::vector<std::string> fields;
    std::string field;

    while (std::getline(record, field, '|')) {
        fields.push_back(field);
    }

    if (fields.size() != 3 && fields.size() != 5) {
        return false;
    }

    std::istringstream rollInput(fields[0]);
    if (!(rollInput >> student.rollNumber)) {
        return false;
    }

    student.name = fields[1];
    const std::string& marksText = fields.size() == 3 ? fields[2] : fields[4];

    if (fields.size() == 5) {
        student.course = fields[2];
        student.department = fields[3];
    }

    std::istringstream marksInput(marksText);
    return static_cast<bool>(marksInput >> student.marks);
}

std::vector<StudentRecord> loadStudents() {
    std::vector<StudentRecord> students;
    std::ifstream inputFile("student_records.txt");
    std::string line;

    while (std::getline(inputFile, line)) {
        StudentRecord student{};
        if (parseStudentRecord(line, student)) {
            students.push_back(student);
        }
    }

    return students;
}

void writeStudentRecord(std::ostream& output, const StudentRecord& student) {
    output << student.rollNumber << '|'
           << student.name << '|'
           << student.course << '|'
           << student.department << '|'
           << student.marks << '\n';
}

bool saveStudents(const std::vector<StudentRecord>& students) {
    std::ofstream temporaryFile("student_records_temp.txt");
    if (!temporaryFile) {
        return false;
    }

    for (const StudentRecord& student : students) {
        writeStudentRecord(temporaryFile, student);
    }
    temporaryFile.close();

    if (!temporaryFile || std::remove("student_records.txt") != 0) {
        std::remove("student_records_temp.txt");
        return false;
    }

    if (std::rename("student_records_temp.txt", "student_records.txt") != 0) {
        return false;
    }

    return true;
}

bool readRollNumber(const std::string& prompt, int& rollNumber) {
    std::cout << prompt;
    if (std::cin >> rollNumber) {
        return true;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid roll number.\n";
    return false;
}

bool readValidMarks(double& marks) {
    while (true) {
        std::cout << "Enter marks (0-100): ";
        if (!(std::cin >> marks)) {
            if (std::cin.eof()) {
                return false;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a numeric mark between 0 and 100.\n";
            continue;
        }

        if (marks >= 0 && marks <= 100) {
            return true;
        }
        std::cout << "Marks must be between 0 and 100.\n";
    }
}

std::string gradeForMarks(double marks) {
    if (marks >= 90) return "A";
    if (marks >= 80) return "B";
    if (marks >= 70) return "C";
    if (marks >= 60) return "D";
    return "F";
}

void printStudent(const StudentRecord& student) {
    std::cout << "Roll Number: " << student.rollNumber << '\n'
              << "Name: " << student.name << '\n'
              << "Course: " << student.course << '\n'
              << "Department: " << student.department << '\n'
              << "Marks: " << student.marks << '\n'
              << "Grade: " << gradeForMarks(student.marks) << '\n';
}

void addStudent() { // Collect one student record and append it to the data file.

    StudentRecord student{};
    if (!readRollNumber("Enter roll number: ", student.rollNumber)) {
        return;
    }

    const std::vector<StudentRecord> students = loadStudents();
    for (const StudentRecord& existing : students) {
        if (existing.rollNumber == student.rollNumber) {
            std::cout << "That roll number already exists.\n";
            return;
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter name: ";
    std::getline(std::cin, student.name);
    std::cout << "Enter course: ";
    std::getline(std::cin, student.course);
    std::cout << "Enter department: ";
    std::getline(std::cin, student.department);

    if (!readValidMarks(student.marks)) {
        return;
    }

    std::ofstream outputFile("student_records.txt", std::ios::app);
    if (!outputFile) {
        std::cerr << "Error: Could not open student_records.txt\n";
        return;
    }

    writeStudentRecord(outputFile, student);
    if (!outputFile) {
        std::cerr << "Error: Could not save the student record.\n";
        return;
    }

    std::cout << "Record added successfully. Grade: "
              << gradeForMarks(student.marks) << '\n';
}

void displayStudents() {
    const std::vector<StudentRecord> students = loadStudents();
    if (students.empty()) {
        std::cout << "No student records found.\n";
        return;
    }

    std::cout << '\n'
              << std::left << std::setw(12) << "Roll No."
              << std::setw(24) << "Name"
              << std::setw(20) << "Course"
              << std::setw(20) << "Department"
              << std::setw(10) << "Marks"
              << "Grade\n";
    for (const StudentRecord& student : students) {
        std::cout << std::left << std::setw(12) << student.rollNumber
                  << std::setw(24) << student.name
                  << std::setw(20) << student.course
                  << std::setw(20) << student.department
                  << std::setw(10) << student.marks
                  << gradeForMarks(student.marks) << '\n';
    }
}

void searchStudent() { // Find and display the record with a requested roll number.

    int targetRoll;
    if (!readRollNumber("Enter roll number to search: ", targetRoll)) {
        return;
    }

    for (const StudentRecord& student : loadStudents()) {
        if (student.rollNumber == targetRoll) {
            printStudent(student);
            return;
        }
    }

    std::cout << "Student not found.\n";
}

void updateMarks() {
    std::vector<StudentRecord> students = loadStudents();
    int targetRoll;
    if (!readRollNumber("Enter roll number to update: ", targetRoll)) {
        return;
    }

    for (StudentRecord& student : students) {
        if (student.rollNumber == targetRoll) {
            if (!readValidMarks(student.marks)) {
                return;
            }
            if (!saveStudents(students)) {
                std::cerr << "Error: Could not save the updated records.\n";
                return;
            }
            std::cout << "Marks updated successfully. Grade: "
                      << gradeForMarks(student.marks) << '\n';
            return;
        }
    }

    std::cout << "Student not found. No changes made.\n";
}

void deleteStudent() {
    std::vector<StudentRecord> students = loadStudents();
    int targetRoll;
    if (!readRollNumber("Enter roll number to delete: ", targetRoll)) {
        return;
    }

    const auto originalSize = students.size();
    students.erase(
        std::remove_if(
            students.begin(),
            students.end(),
            [targetRoll](const StudentRecord& student) {
                return student.rollNumber == targetRoll;
            }
        ),
        students.end()
    );

    if (students.size() == originalSize) {
        std::cout << "Student not found. No changes made.\n";
        return;
    }

    if (!saveStudents(students)) {
        std::cerr << "Error: Could not save the updated records.\n";
        return;
    }

    std::cout << "Student record deleted successfully.\n";
}

int main() { // Program execution starts here.

    int choice = -1; // Stores the user's menu selection.

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
            << "5. Delete Student\n";

        std::cout
            << "0. Exit\n"; // List the exit option.

        std::cout
            << "Enter choice: "; // Prompt for a menu selection.

        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }

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

            case 5:
                deleteStudent();
                break;

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