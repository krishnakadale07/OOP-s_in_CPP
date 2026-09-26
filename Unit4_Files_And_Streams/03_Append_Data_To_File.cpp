#include <fstream>  // Provides output file stream support.
#include <iostream> // Provides console output streams.

int main() { // Program execution starts here.

    std::ofstream outputFile(
        "message.txt",
        std::ios::app // Open in append mode so new text goes at the end.
    ); // Create the output stream for message.txt.

    if (!outputFile) { // Check whether the file opened for appending.
        std::cerr
            << "Error: Could not open message.txt for appending\n";
        return 1; // Stop with an error status if opening failed.
    }

    outputFile
        << "This line was added using append mode.\n"; // Add a line without replacing existing contents.

    outputFile.close(); // Close the file and finish writing buffered data.

    std::cout
        << "New line appended successfully.\n"; // Confirm the append operation.

    return 0; // Report successful completion.
}