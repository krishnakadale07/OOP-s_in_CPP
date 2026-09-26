#include <fstream>
#include <iostream>
#include <string>

int main() {

    std::ifstream inputFile(
        "missing_file.txt"
    );

    if (!inputFile.is_open()) {

        std::cerr
            << "Error: File could not be opened.\n";

        std::cerr
            << "Check whether missing_file.txt "
            << "exists in the current folder.\n";

        return 1;
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        std::cout << line << '\n';
    }

    if (inputFile.eof()) {

        std::cout
            << "End of file reached normally.\n";

    } else if (inputFile.bad()) {

        std::cerr
            << "A serious file I/O error occurred.\n";

    } else if (inputFile.fail()) {

        std::cerr
            << "A logical file read error occurred.\n";
    }

    return 0;
}