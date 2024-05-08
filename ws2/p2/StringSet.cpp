/*
*****************************************************************************
                          OOP345 Workshop - #2 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#include "StringSet.h"
#include <fstream>
#include <iostream>

namespace seneca {

    StringSet::StringSet() : strings(nullptr), numStrings(0) {}

    StringSet::StringSet(const char* fileName) : strings(nullptr),numStrings(0) {
    std::ifstream file(fileName);
        if (file.is_open()) {
            std::string word ;
            while (std::getline(file,word, ' ') ) {
                ++numStrings;
            }
            file.close();  
            file.open(fileName);

            if (file.is_open() ) {
                strings =new std::string[numStrings];
                for (size_t i = 0; i< numStrings; ++i) {
                    std::getline(file,strings[i],' ');
                }
                file.close();  
            }
        }
    }

    StringSet::~StringSet() {
        delete[] strings;
    } 

    size_t StringSet::size() const {
        return numStrings;
    }

    std::string StringSet::operator[](size_t index) const {
        if (index< numStrings) {
            return strings[index];
        } else{
            return "";
        }
    }

    void StringSet::copyFrom(const StringSet& other) {
            delete[] strings;
            numStrings =other.numStrings;
            strings = new std::string[numStrings];

            for (size_t i = 0;i< numStrings; ++i) {
                strings[i]= other.strings[i];
            }
        }

    StringSet::StringSet(const StringSet& other) : strings(nullptr), numStrings(0) {
        copyFrom(other);
    }

    StringSet& StringSet::operator=(const StringSet& other) {
        if (this!= &other ) {  
             copyFrom(other);
        }
        return *this;
    }

    void StringSet::moveFrom(StringSet&& other) {
        numStrings = other.numStrings;
        strings =other.strings;

        other.numStrings = 0;
        other.strings= nullptr;
    }

    StringSet::StringSet(StringSet&& other) :strings(nullptr), numStrings(0) {
          moveFrom(std::move(other));
    }

    StringSet& StringSet::operator=(StringSet&& other) {
        if (this!= &other) {  
            delete[] strings;
            moveFrom(std::move(other) );
        }
        return *this;
    }

} 
