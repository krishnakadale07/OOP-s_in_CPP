#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <utility>

class Book {
private:
    int bookId;
    std::string title;
    std::string author;
    bool issued;

public:
    Book(
        int id,
        std::string bookTitle,
        std::string bookAuthor,
        bool issueStatus = false
    )
        : bookId(id),
          title(std::move(bookTitle)),
          author(std::move(bookAuthor)),
          issued(issueStatus) {}

    int getBookId() const {
        return bookId;
    }

    std::string toFileRecord() const {

        return
            std::to_string(bookId)
            + "|"
            + title
            + "|"
            + author
            + "|"
            + (issued ? "1" : "0");
    }

    void display() const {

        std::cout
            << "Book ID: "
            << bookId
            << '\n';

        std::cout
            << "Title: "
            << title
            << '\n';

        std::cout
            << "Author: "
            << author
            << '\n';

        std::cout
            << "Status: "
            << (issued ? "Issued" : "Available")
            << '\n';
    }
};

void addBook() {

    int id;

    std::string title;
    std::string author;

    std::cout
        << "Enter book ID: ";

    std::cin >> id;

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );

    std::cout
        << "Enter title: ";

    std::getline(
        std::cin,
        title
    );

    std::cout
        << "Enter author: ";

    std::getline(
        std::cin,
        author
    );

    Book book(
        id,
        title,
        author
    );

    std::ofstream outputFile(
        "library_books.txt",
        std::ios::app
    );

    if (!outputFile) {

        std::cerr
            << "Error: Could not open library_books.txt\n";

        return;
    }

    outputFile
        << book.toFileRecord()
        << '\n';

    std::cout
        << "Book added successfully.\n";
}

void displayBooks() {

    std::ifstream inputFile(
        "library_books.txt"
    );

    if (!inputFile) {

        std::cout
            << "No library record file found.\n";

        return;
    }

    std::string line;

    while (std::getline(inputFile, line)) {

        std::stringstream record(line);

        std::string idText;
        std::string title;
        std::string author;
        std::string issuedText;

        if (
            std::getline(record, idText, '|') &&
            std::getline(record, title, '|') &&
            std::getline(record, author, '|') &&
            std::getline(record, issuedText)
        ) {

            Book book(
                std::stoi(idText),
                title,
                author,
                issuedText == "1"
            );

            book.display();

            std::cout
                << "-------------------------\n";
        }
    }
}

int main() {

    int choice;

    do {

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

        std::cin >> choice;

        switch (choice) {

            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 0:
                std::cout
                    << "Exiting program.\n";
                break;

            default:
                std::cout
                    << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}