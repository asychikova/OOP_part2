/*
*****************************************************************************
                          OOP345 Workshop - #5 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <iomanip> 

namespace seneca {

    class SpellChecker {
    private:
        static const size_t ARRAY_SIZE = 6; 
        std::string bad_m[ARRAY_SIZE]; 
        std::string good_m[ARRAY_SIZE]; 
        int replace_m[ARRAY_SIZE] = {0}; 

    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };

} 
#endif 
