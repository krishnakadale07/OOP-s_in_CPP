#include <fstream>  // Provides file streams and seek direction constants.
#include <iostream> // Provides console output streams.

int main() { // Program execution starts here.

    std::fstream file(
        "navigation.txt",
        std::ios::in |
        std::ios::out |
        std::ios::trunc // Start with an empty file, replacing earlier contents.
    ); // Open the file for both reading and writing.

    if (!file) { // Check whether the file opened successfully.

        std::cerr
            << "Error: Could not open navigation.txt\n";

        return 1; // Stop if pointer navigation cannot be demonstrated.
    }

    file << "ABCDE"; // Write five characters so their positions can be inspected.

    std::cout
        << "Output position after writing: "
        << file.tellp()
        << '\n'; // Display the current output position after writing.

    file.flush(); // Ensure written bytes are available before reading them.

    file.seekg(0, std::ios::beg); // Move the input pointer to the start of the file.

    char firstCharacter; // Receives the character at the start of the file.

    file.get(firstCharacter); // Read one character and advance the input pointer.

    std::cout
        << "First character: "
        << firstCharacter
        << '\n'; // Print the first character that was read.

    std::cout
        << "Input position after reading one character: "
        << file.tellg()
        << '\n'; // Show the input pointer position after reading one character.

    file.seekg(2, std::ios::beg); // Move the input pointer to zero-based position 2.

    char thirdCharacter; // Receives the character at position 2.

    file.get(thirdCharacter); // Read the selected character from that position.

    std::cout
        << "Character at position 2: "
        << thirdCharacter
        << '\n'; // Display the character found at position 2.

    file.seekp(5, std::ios::beg); // Move the output pointer to the position after ABCDE.

    file << "F"; // Write F at position 5, extending the file to ABCDEF.

    file.close(); // Close the file after all pointer operations are complete.

    std::cout
        << "Navigation completed. "
        << "Check navigation.txt\n"; // Report that the pointer demonstration is complete.

    return 0; // Report successful completion.
}