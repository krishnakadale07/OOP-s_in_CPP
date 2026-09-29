#include <cctype>   // Provides character case and punctuation classification.
#include <fstream>  // Provides input file stream support.
#include <iostream> // Provides console input and output streams.
#include <string>   // Provides strings for the search term and file words.

std::string normalizeWord(const std::string& text) {
    std::string normalized;

    for (unsigned char character : text) {
        if (!std::ispunct(character)) {
            normalized += static_cast<char>(std::tolower(character));
        }
    }

    return normalized;
}

int main() { // Program execution starts here.

    std::ifstream inputFile("message.txt"); // Open the file that will be searched.

    if (!inputFile) { // Check whether the file opened successfully.
        std::cerr
            << "Error: Could not open message.txt\n";
        return 1; // Stop if the search input is unavailable.
    }

    std::string searchWord; // Stores the word entered by the user.

    std::cout << "Enter word to search: "; // Prompt for the exact word to find.
    std::cin >> searchWord; // Read one whitespace-delimited search word.
    const std::string normalizedSearchWord = normalizeWord(searchWord);

    std::string word; // Holds each word extracted from the file.

    int count = 0; // Tracks how many exact matches are found.

    while (inputFile >> word) { // Read whitespace-separated words until the file ends.

        if (!normalizedSearchWord.empty() &&
            normalizeWord(word) == normalizedSearchWord) {
            ++count; // Increase the match total when they are equal.
        }
    }

    std::cout
        << "The word '"
        << searchWord
        << "' occurred "
        << count
        << " time(s).\n"; // Display the search term and its occurrence count.

    return 0; // Report successful completion.
}