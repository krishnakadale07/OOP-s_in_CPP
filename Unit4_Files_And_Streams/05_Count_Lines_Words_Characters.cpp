#include <cctype>   // Provides whitespace classification for characters.
#include <fstream>  // Provides input file stream support.
#include <iostream> // Provides console output streams.
#include <string>   // Provides string types used by the program.

int main() { // Program execution starts here.

    std::ifstream inputFile("message.txt"); // Open the text file for reading.

    if (!inputFile) { // Verify that the input file opened.
        std::cerr
            << "Error: Could not open message.txt\n";
        return 1; // Stop if the file cannot be analyzed.
    }

    std::size_t lineCount = 0; // Counts newline characters and a possible final line.
    std::size_t wordCount = 0; // Counts transitions from whitespace into words.
    std::size_t characterCount = 0; // Counts every character read from the file.

    bool insideWord = false; // Tracks whether the current character is part of a word.

    char ch; // Receives each character extracted from the file.

    while (inputFile.get(ch)) { // Process the file one character at a time.

        ++characterCount; // Include this character in the total.

        if (ch == '\n') { // A newline terminates one line.
            ++lineCount; // Count the line ending just read.
        }

        if (std::isspace(
                static_cast<unsigned char>(ch))) { // Convert safely before testing for whitespace.

            insideWord = false; // Whitespace marks the end of the current word.

        } else if (!insideWord) {

            ++wordCount; // A non-space after whitespace begins a new word.
            insideWord = true; // Mark the program as being inside that word.
        }
    }

    if (characterCount > 0) { // Only inspect the last byte when the file is non-empty.

        inputFile.clear(); // Clear EOF state so the stream can seek again.

        inputFile.seekg(-1, std::ios::end); // Move to the final character in the file.

        char lastCharacter; // Stores the final character for the line-count check.

        inputFile.get(lastCharacter); // Read the final character.

        if (lastCharacter != '\n') { // A non-newline ending still completes a line.
            ++lineCount; // Count the final unterminated line.
        }
    }

    std::cout
        << "Lines: " << lineCount << '\n'; // Print the total number of lines.

    std::cout
        << "Words: " << wordCount << '\n'; // Print the total number of words.

    std::cout
        << "Characters: "
        << characterCount << '\n'; // Print the total number of characters.

    return 0; // Report successful completion.
}