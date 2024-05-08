// Utilities.cpp

#include "Utilities.h"
#include "Employee.h"
#include <iostream>
#include <sstream>

namespace seneca {
    Person* buildInstance(std::istream& in) {
        char tag;
        if (!(in >> std::ws >> tag)) // Skip whitespace and read the first character
            return nullptr;

        try {
            if (tag == 'e' || tag == 'E') {
                std::string line;
                std::getline(in >> std::ws, line); // Read the entire line
                std::istringstream iss(line); // Create a string stream from the line
                std::string token;

                // Read tokens separated by commas
                std::getline(iss, token, ','); // Read tag, but we don't need it

                std::getline(iss, token, ','); // Read name
                std::string name = token.substr(1);
                size_t lastNonWhitespace = name.find_last_not_of(" \t");
                if (lastNonWhitespace != std::string::npos) {
                    name = name.substr(0, lastNonWhitespace + 1);
                }

                std::getline(iss, token, ','); // Read age
                int age = std::stoi(token);

                std::getline(iss, token); // Read ID
                std::string id;
                if (token.empty() || token[1] != 'E' || token[0] != ' ') {
                    // Print the error message before tests
                    std::cerr << name << "++Invalid record!" << std::endl;
                    return nullptr;
                }
                id = token.substr(1); // Remove leading 'E' or 'e'

                // Create and return an Employee object
                return new Employee(name, age, id);
            } else {
                // If the first non-blank character is not 'e' or 'E', return nullptr
                return nullptr;
            }
        } catch (const std::exception& e) {
          //  std::cerr << e.what() << std::endl;
            return nullptr;
        }
    }
}
