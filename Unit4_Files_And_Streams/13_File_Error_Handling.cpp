#include <fstream>  // Provides input file stream support.
#include <iostream> // Provides console input and output streams.
#include <string>   // Provides storage for lines read from the file.

int main() { // Program execution starts here.

    std::ifstream inputFile(
        "missing_file.txt"
    ); // Attempt to open a file that may not exist.

    if (!inputFile.is_open()) { // Test whether the file stream successfully opened the file.

        std::cerr
            << "Error: File could not be opened.\n";

        std::cerr
            << "Check whether missing_file.txt "
            << "exists in the current folder.\n";

        return 1; // Stop because no file contents can be read.
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