/*
*****************************************************************************
                          OOP345 Workshop - #5 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#include "SpellChecker.h"

namespace seneca {

    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream file( filename);
        if (!file.is_open() ) {
            throw "Bad file name!";
        }

        for (size_t i =0; i<ARRAY_SIZE; ++i) {
            if (!(file>> bad_m[i]>>good_m[i])) {
                throw "Invalid file format!";
            }
        }
        file.close();
    }

    void SpellChecker::operator()(std::string& text) {
        for (size_t i =0; i <ARRAY_SIZE;++i) {
            size_t index =0;
            while (true){
                index =text.find(bad_m[i],index);
                if (index == text.length()){
                    break;
                }
                if (index!= std::string::npos) {
                    text.replace(index,bad_m[i].length(), good_m[i]);
                    replace_m[i]++;
                    index +=good_m[i].length();
                } else {
                    break;
                }
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const {
        for (size_t i =0; i<ARRAY_SIZE; ++i) {
            out <<std::setw(15)<< std::right<<bad_m[i]<<": " <<replace_m[i] <<" replacements\n";
        }
    }

} 
