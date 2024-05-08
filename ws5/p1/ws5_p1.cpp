#include <iostream>
#include <iomanip>
#include <fstream>
#include "Book.h"

int main(int argc, char** argv)
{
    std::cout << "Command Line:\n";
    std::cout << "--------------------------\n";
    for (int i = 0; i < argc; i++)
        std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
    std::cout << "--------------------------\n\n";

    // get the books
    seneca::Book library[7];
    if (argc == 2) {
        std::ifstream file(argv[1]);
        if (!file.is_open()) {
            std::cerr << "ERROR: Cannot open file.\n";
            return 1;
        }
        
        std::string line;
        int index = 0;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#')
                continue;
            library[index++] = seneca::Book(line);
        }
    }
    else {
        std::cerr << "ERROR: Incorrect number of arguments.\n";
        return 2;
    }

    double usdToCadRate = 1.3;
    double gbpToCadRate = 1.5;

    auto fixPrice = [&](seneca::Book& book) {
        if (book.country() == "US")
            book.price() *= usdToCadRate;
        else if (book.country() == "UK" && book.year() >= 1990 && book.year() <= 1999)
            book.price() *= gbpToCadRate;
    };

    std::cout << "-----------------------------------------\n";
    std::cout << "The library content\n";
    std::cout << "-----------------------------------------\n";
    for (const auto& book : library)
        std::cout << book << '\n';
    std::cout << "-----------------------------------------\n\n";

    std::cout << "-----------------------------------------\n";
    std::cout << "The library content (updated prices)\n";
    std::cout << "-----------------------------------------\n";
    for (auto& book : library)
        fixPrice(book);
    for (const auto& book : library)
        std::cout << book << '\n';
    std::cout << "-----------------------------------------\n";

    return 0;
}
