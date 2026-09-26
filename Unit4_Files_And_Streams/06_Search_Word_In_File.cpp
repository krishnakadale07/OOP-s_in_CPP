#include <fstream>
#include <iostream>
#include <string>

int main() {

    std::ifstream inputFile("message.txt");

    if (!inputFile) {
        std::cerr
            << "Error: Could not open message.txt\n";
        return 1;
    }

    std::string searchWord;

    std::cout << "Enter word to search: ";
    std::cin >> searchWord;

    std::string word;

    int count = 0;

    while (inputFile >> word) {

        if (word == searchWord) {
            ++count;
        }
    }

    std::cout
        << "The word '"
        << searchWord
        << "' occurred "
        << count
        << " time(s).\n";

    return 0;
}