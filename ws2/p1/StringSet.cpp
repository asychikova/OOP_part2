#include "StringSet.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace seneca {

    StringSet::StringSet() : strings(nullptr), numStrings(0) {}

 /*   StringSet::StringSet(const char* fileName) : strings(nullptr), numStrings(0) {
        std::ifstream file(fileName);
        if (file.is_open()) {
            // Count number of strings
            std::string word;
            while (file >> word) {
                ++numStrings;
            }

            // Allocate memory and read strings
            file.clear();
            file.seekg(0, std::ios::beg);
            strings = new std::string[numStrings];
            for (size_t i = 0; i < numStrings; ++i) {
                file >> strings[i];
            }
            file.close();
        }
    } */

 StringSet::StringSet(const char* fileName) : strings(nullptr), numStrings(0) {
    std::ifstream file(fileName);
    if (file.is_open()) {
        // Count number of strings
        std::string word;
        while (std::getline(file, word, ' ')) {
            ++numStrings;
        }

        // Allocate memory and read strings
        file.clear();
        file.seekg(0, std::ios::beg);
        strings = new std::string[numStrings];
        for (size_t i = 0; i < numStrings; ++i) {
            std::getline(file, strings[i], ' ');
        }

        file.close();
    }
}

    StringSet::~StringSet() {
        delete[] strings;
    }

    size_t StringSet::size() const {
        return numStrings;
    }

    std::string StringSet::operator[](size_t index) const {
        return (index < numStrings) ? strings[index] : "";
    }

    // Inside StringSet.cpp
StringSet::StringSet(const StringSet& other) : strings(nullptr), numStrings(0) {
    numStrings = other.numStrings;
    strings = new std::string[numStrings];
    
    // Copy the strings
    for (size_t i = 0; i < numStrings; ++i) {
        strings[i] = other.strings[i];
    }
}

StringSet& StringSet::operator=(const StringSet& other) {
    if (this != &other) {  // Check for self-assignment
        // Release existing memory
        delete[] strings;

        // Copy data
        numStrings = other.numStrings;
        strings = new std::string[numStrings];
        
        // Copy the strings
        for (size_t i = 0; i < numStrings; ++i) {
            strings[i] = other.strings[i];
        }
    }
    return *this;
}


} // namespace seneca
