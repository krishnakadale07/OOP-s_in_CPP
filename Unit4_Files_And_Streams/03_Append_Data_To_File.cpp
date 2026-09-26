#include <fstream>
#include <iostream>

int main() {

    std::ofstream outputFile(
        "message.txt",
        std::ios::app
    );

    if (!outputFile) {
        std::cerr
            << "Error: Could not open message.txt for appending\n";
        return 1;
    }

    outputFile
        << "This line was added using append mode.\n";

    outputFile.close();

    std::cout
        << "New line appended successfully.\n";

    return 0;
}