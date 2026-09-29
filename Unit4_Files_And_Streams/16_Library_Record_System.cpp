#include <algorithm> // Provides character and collection algorithms.
#include <cctype>    // Provides digit validation for dates.
#include <cstdint>   // Provides fixed-width date day counts.
#include <fstream>  // Provides input and output file streams.
#include <iostream> // Provides console input and output streams.
#include <limits>   // Provides the input-buffer size used when discarding a newline.
#include <sstream>  // Provides string streams for parsing saved book records.
#include <string>   // Provides strings for book fields and file lines.
#include <ctime>    // Provides the system's current local date.
#include <utility>  // Provides std::move for transferring string values.
#include <vector>   // Stores books while searching and updating records.

constexpr double finePerOverdueDay = 1.0;

bool parseDate(const std::string& text, int& year, int& month, int& day) {
    if (text.size() != 10 || text[4] != '-' || text[7] != '-') {
        return false;
    }

    for (std::size_t index = 0; index < text.size(); ++index) {
        if (index != 4 && index != 7 && !std::isdigit(static_cast<unsigned char>(text[index]))) {
            return false;
        }
    }

    year = std::stoi(text.substr(0, 4));
    month = std::stoi(text.substr(5, 2));
    day = std::stoi(text.substr(8, 2));

    if (year < 1 || month < 1 || month > 12) {
        return false;
    }

    const bool leapYear = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    const int daysInMonth[] = {31, leapYear ? 29 : 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31};
    return day >= 1 && day <= daysInMonth[month - 1];
}

std::int64_t daysFromCivil(int year, int month, int day) {
    year -= month <= 2;
    const int era = (year >= 0 ? year : year - 399) / 400;
    const unsigned yearOfEra = static_cast<unsigned>(year - era * 400);
    const unsigned shiftedMonth = static_cast<unsigned>(month + (month > 2 ? -3 : 9));
    const unsigned dayOfYear = (153 * shiftedMonth + 2) / 5 +
                               static_cast<unsigned>(day - 1);
    const unsigned dayOfEra = yearOfEra * 365 + yearOfEra / 4 -
                              yearOfEra / 100 + dayOfYear;
    return static_cast<std::int64_t>(era) * 146097 + dayOfEra - 719468;
}

std::int64_t currentDayNumber() {
    const std::time_t now = std::time(nullptr);
    const std::tm* localDate = std::localtime(&now);
    if (localDate == nullptr) {
        return 0;
    }
    return daysFromCivil(localDate->tm_year + 1900, localDate->tm_mon + 1,
                         localDate->tm_mday);
}

class Book { // Models one library book and its issue status.
private:
    int bookId; // Stores the unique identifier for this book.
    std::string title; // Stores the book title.
    std::string author; // Stores the author's name.
    bool issued; // True when the book is currently issued.
    std::string borrowerId;
    std::string borrowerName;
    std::string dueDate;
    double fine;

public:
    Book(
        int id,
        std::string bookTitle,
        std::string bookAuthor,
                bool issueStatus = false,
                std::string studentId = {},
                std::string studentName = {},
                std::string bookDueDate = {},
                double assessedFine = 0.0
    ) // Accept the book fields and an optional initial issue status.
        : bookId(id),
          title(std::move(bookTitle)),
          author(std::move(bookAuthor)),
                    issued(issueStatus),
                    borrowerId(std::move(studentId)),
                    borrowerName(std::move(studentName)),
                    dueDate(std::move(bookDueDate)),
                    fine(assessedFine) {} // Initialize every data member from the supplied values.

    int getBookId() const { // Provide read-only access to the book identifier.
        return bookId; // Return this book's ID.
    }

    bool isIssued() const {
        return issued;
    }

    void issueTo(std::string studentId, std::string studentName,
                 std::string bookDueDate) {
        issued = true;
        borrowerId = std::move(studentId);
        borrowerName = std::move(studentName);
        dueDate = std::move(bookDueDate);
        fine = 0.0;
    }

    double calculateFine() const {
        int year;
        int month;
        int day;
        if (!parseDate(dueDate, year, month, day)) {
            return fine;
        }

        const std::int64_t daysLate = currentDayNumber() - daysFromCivil(year, month, day);
        return static_cast<double>(std::max<std::int64_t>(0, daysLate)) *
               finePerOverdueDay;
    }

    double returnBook() {
        fine = calculateFine();
        issued = false;
        return fine;
    }

    std::string toFileRecord() const { // Convert the book fields into one delimited file record.

        return
            std::to_string(bookId)
            + "|"
            + title
            + "|"
            + author
            + "|"
                + (issued ? "1" : "0")
                + "|"
                + borrowerId
                + "|"
                + borrowerName
                + "|"
                + dueDate
                + "|"
                + std::to_string(fine); // Encode status and borrower details in the saved record.
    }

            void display() const { // Print this book's details in a readable format.

        std::cout
            << "Book ID: "
            << bookId
            << '\n'; // Display the book identifier.

        std::cout
            << "Title: "
            << title
            << '\n'; // Display the title.

        std::cout
            << "Author: "
            << author
            << '\n'; // Display the author.

        std::cout
            << "Status: "
            << (issued ? "Issued" : "Available")
            << '\n'; // Display whether the book is issued or available.

        if (!borrowerId.empty()) {
            std::cout << "Borrower ID: " << borrowerId << '\n'
                      << "Borrower Name: " << borrowerName << '\n';
        }
        if (!dueDate.empty()) {
            std::cout << "Due Date: " << dueDate << '\n';
        }
        std::cout << "Fine: " << (issued ? calculateFine() : fine)
                  << " (1 unit per overdue day)\n";
    }
};

bool parseBookRecord(const std::string& line, Book& book) {
    std::stringstream record(line);
    std::vector<std::string> fields;
    std::string field;
    while (std::getline(record, field, '|')) {
        fields.push_back(field);
    }

    if (fields.size() != 4 && fields.size() != 8) {
        return false;
    }

    int id;
    std::istringstream idInput(fields[0]);
    if (!(idInput >> id) || (fields[3] != "0" && fields[3] != "1")) {
        return false;
    }

    std::string borrowerId;
    std::string borrowerName;
    std::string dueDate;
    double fine = 0.0;
    if (fields.size() == 8) {
        borrowerId = fields[4];
        borrowerName = fields[5];
        dueDate = fields[6];
        std::istringstream fineInput(fields[7]);
        if (!(fineInput >> fine)) {
            return false;
        }
    }

    book = Book(id, fields[1], fields[2], fields[3] == "1",
                borrowerId, borrowerName, dueDate, fine);
    return true;
}

std::vector<Book> loadBooks() {
    std::vector<Book> books;
    std::ifstream inputFile("library_books.txt");
    std::string line;
    while (std::getline(inputFile, line)) {
        Book book(0, "", "");
        if (parseBookRecord(line, book)) {
            books.push_back(std::move(book));
        }
    }
    return books;
}

bool saveBooks(const std::vector<Book>& books) {
    std::ofstream temporaryFile("library_books_temp.txt");
    if (!temporaryFile) {
        return false;
    }
    for (const Book& book : books) {
        temporaryFile << book.toFileRecord() << '\n';
    }
    temporaryFile.close();

    if (!temporaryFile || std::remove("library_books.txt") != 0) {
        std::remove("library_books_temp.txt");
        return false;
    }
    if (std::rename("library_books_temp.txt", "library_books.txt") != 0) {
        return false;
    }
    return true;
}

bool readBookId(const std::string& prompt, int& id) {
    std::cout << prompt;
    if (std::cin >> id) {
        return true;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid book ID.\n";
    return false;
}

void readTextLine(const std::string& prompt, std::string& value) {
    std::cout << prompt;
    std::getline(std::cin, value);
}

std::string readDueDate() {
    std::string dueDate;
    int year;
    int month;
    int day;
    while (true) {
        readTextLine("Enter due date (YYYY-MM-DD): ", dueDate);
        if (!std::cin) {
            return {};
        }
        if (parseDate(dueDate, year, month, day)) {
            return dueDate;
        }
        std::cout << "Enter a valid date in YYYY-MM-DD format.\n";
    }
}

void addBook() { // Read a book from the user and append it to the library file.

    int id; // Stores the ID entered for the new book.

    if (!readBookId("Enter book ID: ", id)) {
        return;
    }

    if (id <= 0) {
        std::cout << "Book ID must be positive.\n";
        return;
    }

    const std::vector<Book> books = loadBooks();
    for (const Book& existing : books) {
        if (existing.getBookId() == id) {
            std::cout << "That book ID already exists.\n";
            return;
        }
    }

    std::string title;
    std::string author;

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    ); // Discard the leftover newline before reading full text lines.

    readTextLine("Enter title: ", title);
    readTextLine("Enter author: ", author);

    Book book(
        id,
        title,
        author
    ); // Create a book object with the entered details and available status.

    std::ofstream outputFile(
        "library_books.txt",
        std::ios::app // Preserve existing records and add this one at the end.
    ); // Open the library data file for appending.

    if (!outputFile) { // Check whether the data file opened successfully.

        std::cerr
            << "Error: Could not open library_books.txt\n";

        return; // Leave the function if the book cannot be saved.
    }

    outputFile
        << book.toFileRecord()
        << '\n'; // Save the delimited record as one line.

    if (!outputFile) {
        std::cerr << "Error: Could not save the book record.\n";
        return;
    }

    std::cout
        << "Book added successfully.\n"; // Confirm that the new book was stored.
}

void displayBooks() { // Read and display every valid book record in the file.
    const std::vector<Book> books = loadBooks();
    if (books.empty()) {
        std::cout << "No library records found.\n";
        return;
    }

    for (const Book& book : books) {
        book.display();
        std::cout << "-------------------------\n";
    }
}

void searchBookById() {
    int id;
    if (!readBookId("Enter book ID to search: ", id)) {
        return;
    }

    const std::vector<Book> books = loadBooks();
    const auto match = std::find_if(
        books.begin(), books.end(),
        [id](const Book& book) { return book.getBookId() == id; }
    );

    if (match == books.end()) {
        std::cout << "Book not found.\n";
        return;
    }
    match->display();
}

void issueBook() {
    int id;
    if (!readBookId("Enter book ID to issue: ", id)) {
        return;
    }

    std::vector<Book> books = loadBooks();
    const auto match = std::find_if(
        books.begin(), books.end(),
        [id](const Book& book) { return book.getBookId() == id; }
    );
    if (match == books.end()) {
        std::cout << "Book not found.\n";
        return;
    }
    if (match->isIssued()) {
        std::cout << "Book is already issued.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string borrowerId;
    std::string borrowerName;
    readTextLine("Enter student borrower ID: ", borrowerId);
    readTextLine("Enter student borrower name: ", borrowerName);
    if (!std::cin) {
        return;
    }

    const std::string dueDate = readDueDate();
    if (!std::cin) {
        return;
    }

    match->issueTo(borrowerId, borrowerName, dueDate);
    if (!saveBooks(books)) {
        std::cerr << "Error: Could not save the issue record.\n";
        return;
    }
    std::cout << "Book issued successfully.\n";
}

void returnBook() {
    int id;
    if (!readBookId("Enter book ID to return: ", id)) {
        return;
    }

    std::vector<Book> books = loadBooks();
    const auto match = std::find_if(
        books.begin(), books.end(),
        [id](const Book& book) { return book.getBookId() == id; }
    );
    if (match == books.end()) {
        std::cout << "Book not found.\n";
        return;
    }
    if (!match->isIssued()) {
        std::cout << "Book is already marked as available.\n";
        return;
    }

    const double assessedFine = match->returnBook();
    if (!saveBooks(books)) {
        std::cerr << "Error: Could not save the return record.\n";
        return;
    }
    std::cout << "Book returned successfully. Fine: " << assessedFine
              << " unit(s) at 1 unit per overdue day.\n";
}

int main() { // Program execution starts here.

    int choice = -1; // Stores the user's menu selection.

    do { // Show the menu at least once and repeat until the user exits.

        std::cout
            << "\nLibrary Record System\n";

        std::cout
            << "1. Add Book\n";

        std::cout
            << "2. Display Books\n";

        std::cout
            << "3. Search Book by ID\n";

        std::cout
            << "4. Issue Book\n";

        std::cout
            << "5. Return Book\n";

        std::cout
            << "0. Exit\n";

        std::cout
            << "Enter choice: ";

        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice.\n";
            continue;
        }

        switch (choice) { // Dispatch to the operation selected by the user.

            case 1:
                addBook(); // Add a new book record.
                break; // Prevent execution from continuing into the next case.

            case 2:
                displayBooks(); // Display all saved books.
                break; // End this menu choice.

            case 3:
                searchBookById();
                break;

            case 4:
                issueBook();
                break;

            case 5:
                returnBook();
                break;

            case 0:
                std::cout
                    << "Exiting program.\n";
                break; // Leave the switch; the loop condition will then end the program.

            default:
                std::cout
                    << "Invalid choice.\n"; // Tell the user that the option is not recognized.
        }

    } while (choice != 0); // Repeat the menu unless the user selected exit.

    return 0; // Report successful completion.
}