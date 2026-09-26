#include <fstream>  // Provides input and output file streams.
#include <iostream> // Provides console input and output streams.
#include <limits>   // Provides the input-buffer size used when discarding a newline.
#include <sstream>  // Provides string streams for parsing saved book records.
#include <string>   // Provides strings for book fields and file lines.
#include <utility>  // Provides std::move for transferring string values.

class Book { // Models one library book and its issue status.
private:
    int bookId; // Stores the unique identifier for this book.
    std::string title; // Stores the book title.
    std::string author; // Stores the author's name.
    bool issued; // True when the book is currently issued.

public:
    Book(
        int id,
        std::string bookTitle,
        std::string bookAuthor,
        bool issueStatus = false
    ) // Accept the book fields and an optional initial issue status.
        : bookId(id),
          title(std::move(bookTitle)),
          author(std::move(bookAuthor)),
          issued(issueStatus) {} // Initialize every data member from the supplied values.

    int getBookId() const { // Provide read-only access to the book identifier.
        return bookId; // Return this book's ID.
    }

    std::string toFileRecord() const { // Convert the book fields into one delimited file record.

        return
            std::to_string(bookId)
            + "|"
            + title
            + "|"
            + author
            + "|"
                + (issued ? "1" : "0"); // Encode the issue status as 1 or 0 for storage.
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
    }
};

void addBook() { // Read a book from the user and append it to the library file.

    int id; // Stores the ID entered for the new book.

    std::string title; // Stores the complete book title.
    std::string author; // Stores the complete author name.

    std::cout
        << "Enter book ID: ";

    std::cin >> id; // Read the numeric book ID.

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    ); // Discard the leftover newline before reading full text lines.

    std::cout
        << "Enter title: ";

    std::getline(
        std::cin,
        title
    ); // Read the title, including spaces.

    std::cout
        << "Enter author: ";

    std::getline(
        std::cin,
        author
    ); // Read the author name, including spaces.

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

    std::cout
        << "Book added successfully.\n"; // Confirm that the new book was stored.
}

void displayBooks() { // Read and display every valid book record in the file.

    std::ifstream inputFile(
        "library_books.txt"
    ); // Open the library data file for reading.

    if (!inputFile) { // Handle a missing or unreadable library file.

        std::cout
            << "No library record file found.\n";

        return; // Leave because there are no records to display.
    }

    std::string line; // Holds one saved book record at a time.

    while (std::getline(inputFile, line)) { // Process each record line in the file.

        std::stringstream record(line); // Prepare the current line for delimiter-based parsing.

        std::string idText; // Receives the ID field before the first |.
        std::string title; // Receives the title field.
        std::string author; // Receives the author field.
        std::string issuedText; // Receives the stored 1/0 issue status.

        if (
            std::getline(record, idText, '|') &&
            std::getline(record, title, '|') &&
            std::getline(record, author, '|') &&
            std::getline(record, issuedText)
        ) { // Build and display a book only when all four fields were read.

            Book book(
                std::stoi(idText),
                title,
                author,
                issuedText == "1"
            ); // Convert the ID and status text back into their original types.

            book.display(); // Print this record's book details.

            std::cout
                << "-------------------------\n"; // Separate this entry from the next one.
        }
    }
}

int main() { // Program execution starts here.

    int choice; // Stores the user's menu selection.

    do { // Show the menu at least once and repeat until the user exits.

        std::cout
            << "\nLibrary Record System\n";

        std::cout
            << "1. Add Book\n";

        std::cout
            << "2. Display Books\n";

        std::cout
            << "0. Exit\n";

        std::cout
            << "Enter choice: ";

        std::cin >> choice; // Read the selected menu option.

        switch (choice) { // Dispatch to the operation selected by the user.

            case 1:
                addBook(); // Add a new book record.
                break; // Prevent execution from continuing into the next case.

            case 2:
                displayBooks(); // Display all saved books.
                break; // End this menu choice.

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