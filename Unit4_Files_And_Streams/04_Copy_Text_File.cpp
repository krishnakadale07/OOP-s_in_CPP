#include <fstream>
#include <iostream>
#include <string>

int main() {

    std::ifstream sourceFile("message.txt");

    std::ofstream destinationFile(
        "message_copy.txt"
    );

    if (!sourceFile) {
        std::cerr
            << "Error: Could not open source file.\n";
        return 1;
    }

    if (!destinationFile) {
        std::cerr
            << "Error: Could not create destination file.\n";
        return 1;
    }

    std::string line;

    while (std::getline(sourceFile, line)) {
        destinationFile << line << '\n';
    }

    std::cout
        << "File copied successfully to message_copy.txt\n";

    return 0;
}