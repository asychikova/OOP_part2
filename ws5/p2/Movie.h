/*
*****************************************************************************
                          OOP345 Workshop - #5 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <string>
#include <iostream>
#include "SpellChecker.h"

namespace seneca {

    class Movie {
    private:
        std::string title_m;
        int year_m;
        std::string description_m;

    public:
        Movie();
        const std::string& title() const;
        Movie(const std::string& strMovie);

        template<typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(title_m);
            spellChecker(description_m);
        }

        friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
    };

}
#endif 
