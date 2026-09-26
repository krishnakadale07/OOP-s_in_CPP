#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

bool isVowel(char ch) {

    ch = static_cast<char>(
        std::tolower(
            static_cast<unsigned char>(ch)
        )
    );

    return ch == 'a' ||
           ch == 'e' ||
           ch == 'i' ||
           ch == 'o' ||
           ch == 'u';
}

int main() {

    std::string fileName;

    std::cout << "Enter file name: ";

    std::getline(
        std::cin,
        fileName
    );

    std::ifstream inputFile(fileName);

    if (!inputFile) {

        std::cerr
            << "Error: Could not open "
            << fileName
            << '\n';

        return 1;
    }

    std::size_t lines = 0;
    std::size_t words = 0;
    std::size_t characters = 0;
    std::size_t vowels = 0;
    std::size_t digits = 0;
    std::size_t spaces = 0;

    bool insideWord = false;

    char ch;

    while (inputFile.get(ch)) {

        ++characters;

        if (ch == '\n') {
            ++lines;
        }

        if (std::isspace(
                static_cast<unsigned char>(ch)
            )) {

            if (ch == ' ') {
                ++spaces;
            }

            insideWord = false;

        } else if (!insideWord) {

            ++words;
            insideWord = true;
        }

        if (
            std::isalpha(
                static_cast<unsigned char>(ch)
            ) &&
            isVowel(ch)
        ) {
            ++vowels;
        }

        if (
            std::isdigit(
                static_cast<unsigned char>(ch)
            )
        ) {
            ++digits;
        }
    }

    if (characters > 0) {

        inputFile.clear();

        inputFile.seekg(
            -1,
            std::ios::end
        );

        char lastCharacter;

        inputFile.get(lastCharacter);

        if (lastCharacter != '\n') {
            ++lines;
        }
    }

    std::cout << "\nFile Statistics\n";

    std::cout
        << "Lines: "
        << lines
        << '\n';

    std::cout
        << "Words: "
        << words
        << '\n';

    std::cout
        << "Characters: "
        << characters
        << '\n';

    std::cout
        << "Vowels: "
        << vowels
        << '\n';

    std::cout
        << "Digits: "
        << digits
        << '\n';

    std::cout
        << "Spaces: "
        << spaces
        << '\n';

    return 0;
}