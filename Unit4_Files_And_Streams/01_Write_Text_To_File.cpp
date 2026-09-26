#include <fstream>  // Provides the output file stream used to write the file.
#include <iostream> // Provides console input and output streams.

int main() { // Program execution starts here.

    std::ofstream outputFile("message.txt"); // Open message.txt for writing; create it if needed.

    if (!outputFile) { // Check whether the output file opened successfully.
        std::cerr
            << "Error: Could not create message.txt\n";
        return 1; // Stop with an error status if the file could not be opened.
    }

    outputFile
        << "Welcome to C++ File Handling\n"; // Write the first line of text to the file.

    outputFile
        << "This is the first line written to a file.\n"; // Write another line to the file.

    outputFile
        << "Files store data permanently.\n"; // Write the final example line.

    outputFile.close(); // Close the file and flush any buffered output.

    std::cout
        << "Data written successfully to message.txt\n"; // Confirm completion in the console.

    return 0; // Report that the program completed successfully.
}