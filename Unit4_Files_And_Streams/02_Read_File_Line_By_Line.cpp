#include <fstream>  // Provides input file stream support.
#include <iostream> // Provides console input and output streams.
#include <string>   // Provides std::string for storing each line.

int main() { // Program execution starts here.

    std::ifstream inputFile("message.txt"); // Open message.txt for reading.

    if (!inputFile) { // Check whether the file opened successfully.
        std::cerr
            << "Error: Could not open message.txt\n";
        return 1; // Stop with an error status when opening fails.
    }

    std::string line; // Holds one line read from the file at a time.

    std::cout << "File Content:\n"; // Print a heading before the file contents.

    while (std::getline(inputFile, line)) { // Read lines until the end of the file.
        std::cout << line << '\n'; // Display the current line.
    }

    inputFile.close(); // Close the input file after reading.

    return 0; // Report successful completion.
}