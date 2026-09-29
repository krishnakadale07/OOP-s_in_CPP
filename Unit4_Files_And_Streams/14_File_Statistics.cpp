#include <cctype>  // Provides character classification and case conversion.
#include <array>   // Stores character frequencies by byte value.
#include <fstream> // Provides input file stream support.
#include <iostream> // Provides console input and output streams.
#include <sstream> // Builds the report for both the console and report.txt.
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
    std::size_t consonants = 0; // Counts alphabetic characters that are not vowels.
    std::size_t digits = 0; // Counts numeric digit characters.
    std::size_t spaces = 0; // Counts ordinary space characters, not tabs or newlines.
    std::size_t punctuation = 0; // Counts punctuation characters.
    std::array<std::size_t, 256> characterFrequencies{};
    unsigned char mostFrequentCharacter = 0;
    std::size_t mostFrequentCount = 0;

    bool insideWord = false; // Tracks whether the current character belongs to a word.

    char ch; // Receives each character extracted from the file.

    while (inputFile.get(ch)) { // Analyze the file one character at a time.

        ++characters; // Count the character just read.
        const unsigned char character = static_cast<unsigned char>(ch);
        const std::size_t frequency = ++characterFrequencies[character];
        if (frequency > mostFrequentCount) {
            mostFrequentCharacter = character;
            mostFrequentCount = frequency;
        }

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

        if (std::isalpha(character)) {
            if (isVowel(ch)) {
                ++vowels;
            } else {
                ++consonants;
            }
        }

        if (std::isdigit(character)) {
            ++digits;
        }

        if (std::ispunct(character)) {
            ++punctuation;
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

    std::string frequentCharacterDescription = "None (file is empty)";
    if (characters > 0) {
        switch (mostFrequentCharacter) {
        case '\n':
            frequentCharacterDescription = "newline";
            break;
        case '\r':
            frequentCharacterDescription = "carriage return";
            break;
        case '\t':
            frequentCharacterDescription = "tab";
            break;
        case ' ':
            frequentCharacterDescription = "space";
            break;
        case '\'':
            frequentCharacterDescription = "apostrophe";
            break;
        case '"':
            frequentCharacterDescription = "double quote";
            break;
        case '\\':
            frequentCharacterDescription = "backslash";
            break;
        default:
            if (std::isprint(mostFrequentCharacter)) {
                frequentCharacterDescription =
                    std::string("'") + static_cast<char>(mostFrequentCharacter) + "'";
            } else {
                frequentCharacterDescription = "non-printing character";
            }
        }
    }

    std::ostringstream report;
    report << "File Statistics for " << fileName << '\n'
           << "Lines: " << lines << '\n'
           << "Words: " << words << '\n'
           << "Characters: " << characters << '\n'
           << "Vowels: " << vowels << '\n'
           << "Consonants: " << consonants << '\n'
           << "Digits: " << digits << '\n'
           << "Spaces: " << spaces << '\n'
           << "Punctuation: " << punctuation << '\n'
           << "Most frequent character: " << frequentCharacterDescription;

    if (characters > 0) {
        report << " (" << mostFrequentCount << " occurrence(s))";
    }
    report << '\n';

    std::ofstream reportFile("report.txt");
    if (!reportFile) {
        std::cerr << "Error: Could not create report.txt\n";
        return 1;
    }

    reportFile << report.str();
    if (!reportFile) {
        std::cerr << "Error: Could not write report.txt\n";
        return 1;
    }

    std::cout << report.str();
    std::cout << "Report saved to report.txt\n";

    return 0; // Report successful completion.
}