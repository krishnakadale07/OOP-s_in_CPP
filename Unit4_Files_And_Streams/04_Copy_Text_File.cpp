#include <fstream>  // Provides input and output file streams.
#include <iostream> // Provides console output streams.
#include <string>   // Provides std::string for the line buffer.

int main() { // Program execution starts here.

    std::ifstream sourceFile("message.txt"); // Open the original file for reading.

    std::ofstream destinationFile(
        "message_copy.txt"
    ); // Create or replace the destination file.

    if (!sourceFile) { // Check whether the source file opened successfully.
        std::cerr
            << "Error: Could not open source file.\n";
        return 1; // Stop because there is nothing to copy.
    }

    if (!destinationFile) { // Check whether the destination file was created.
        std::cerr
            << "Error: Could not create destination file.\n";
        return 1; // Stop if the copied data cannot be written.
    }

    std::string line; // Stores each line temporarily during copying.

    while (std::getline(sourceFile, line)) { // Read each source line until end-of-file.
        destinationFile << line << '\n'; // Write that line to the destination.
    }

    std::cout
        << "File copied successfully to message_copy.txt\n"; // Report successful copying.

    return 0; // Report successful completion.
}