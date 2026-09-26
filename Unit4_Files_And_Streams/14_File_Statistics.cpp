#include <cctype>  // Provides character classification and case conversion.
#include <fstream> // Provides input file stream support.
#include <iostream> // Provides console input and output streams.
#include <string> // Provides the user-supplied file name.

bool isVowel(char ch) { // Return whether the supplied character is an English vowel.

    ch = static_cast<char>(
        std::tolower(
            static_cast<unsigned char>(ch)
        )
    ); // Convert safely to lowercase so uppercase vowels match too.

    return ch == 'a' ||
           ch == 'e' ||
           ch == 'i' ||
           ch == 'o' ||
           ch == 'u'; // Return true when the lowercase character is one of the five vowels.
}

int main() { // Program execution starts here.

    std::string fileName; // Stores the path entered by the user.

    std::cout << "Enter file name: "; // Ask which file should be analyzed.

    std::getline(
        std::cin,
        fileName
    ); // Read the complete file name, including spaces if present.

    std::ifstream inputFile(fileName); // Open the selected file for reading.

    if (!inputFile) { // Check whether the requested file opened successfully.

        std::cerr
            << "Error: Could not open "
            << fileName
            << '\n';

        return 1; // Stop because statistics cannot be calculated without the file.
    }

    std::size_t lines = 0; // Counts newline characters and a possible final line.
    std::size_t words = 0; // Counts transitions from whitespace into words.
    std::size_t characters = 0; // Counts every character read from the file.
    std::size_t vowels = 0; // Counts alphabetic characters recognized as vowels.
    std::size_t digits = 0; // Counts numeric digit characters.
    std::size_t spaces = 0; // Counts ordinary space characters, not tabs or newlines.

    bool insideWord = false; // Tracks whether the current character belongs to a word.

    char ch; // Receives each character extracted from the file.

    while (inputFile.get(ch)) { // Analyze the file one character at a time.

        ++characters; // Count the character just read.

        if (ch == '\n') { // Newline characters mark line endings.
            ++lines; // Count this line ending.
        }

        if (std::isspace(
                static_cast<unsigned char>(ch)
            )) { // Convert to unsigned char before classifying whitespace.

            if (ch == ' ') { // Count only literal space characters in this statistic.
                ++spaces; // Add this ordinary space to the total.
            }

            insideWord = false; // Whitespace ends any word currently being counted.

        } else if (!insideWord) {

            ++words; // A non-whitespace character begins a new word.
            insideWord = true; // Mark subsequent characters as part of that word.
        }

        if (
            std::isalpha(
                static_cast<unsigned char>(ch)
            ) &&
            isVowel(ch)
        ) { // Count alphabetic characters only when the helper recognizes a vowel.
            ++vowels; // Add this character to the vowel total.
        }

        if (
            std::isdigit(
                static_cast<unsigned char>(ch)
            )
        ) { // Test whether this character is a decimal digit.
            ++digits; // Add this digit to the total.
        }
    }

    if (characters > 0) { // Check the last character only when the file has content.

        inputFile.clear(); // Clear the EOF state to allow seeking in the stream.

        inputFile.seekg(
            -1,
            std::ios::end
        ); // Move the read pointer to the file's final character.

        char lastCharacter; // Stores the final character for the line-count adjustment.

        inputFile.get(lastCharacter); // Read the final character in the file.

        if (lastCharacter != '\n') { // A final line without a newline still counts as a line.
            ++lines; // Include that unterminated final line.
        }
    }

    std::cout << "\nFile Statistics\n"; // Print a heading for the calculated totals.

    std::cout
        << "Lines: "
        << lines
        << '\n'; // Display the line count.

    std::cout
        << "Words: "
        << words
        << '\n'; // Display the word count.

    std::cout
        << "Characters: "
        << characters
        << '\n'; // Display the character count.

    std::cout
        << "Vowels: "
        << vowels
        << '\n'; // Display the vowel count.

    std::cout
        << "Digits: "
        << digits
        << '\n'; // Display the digit count.

    std::cout
        << "Spaces: "
        << spaces
        << '\n'; // Display the ordinary-space count.

    return 0; // Report successful completion.
}