#include <fstream>  // Provides input file stream support.
#include <iostream> // Provides console input and output streams.
#include <string>   // Provides storage for lines read from the file.

int main() { // Program execution starts here.

    std::ifstream inputFile;
    std::string fileName;

    while (true) {
        std::cout << "Enter file name: ";

        if (!std::getline(std::cin, fileName)) {
            std::cerr << "Error: No file name was entered.\n";
            return 1;
        }

        inputFile.open(fileName);
        if (inputFile.is_open()) {
            break;
        }

        std::cerr << "Error: Could not open '" << fileName
                  << "'. Please try again.\n";
        inputFile.clear();
    }

    std::string line; // Stores each line read from the input file.

    while (std::getline(inputFile, line)) { // Read lines until a stream condition ends the loop.
        std::cout << line << '\n'; // Print each successfully read line.
    }

    if (inputFile.eof()) { // Check whether reading stopped at the normal end of the file.

        std::cout
            << "End of file reached normally.\n";

    } else if (inputFile.bad()) { // Check for a serious low-level input/output failure.

        std::cerr
            << "A serious file I/O error occurred.\n";

    } else if (inputFile.fail()) { // Check for another logical stream read failure.

        std::cerr
            << "A logical file read error occurred.\n";
    }

    return 0; // Report successful completion of the error-handling example.
}