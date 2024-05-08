/*
*****************************************************************************
                          OOP345 Workshop - #5 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>
#include <iostream>

namespace seneca {

    class Book {
    private:
        std::string author_m;
        std::string title_m;
        std::string country_m;
        size_t year_m;
        double price_m;
        std::string description_m;

    public:
        Book();
        const std::string& title() const;
        const std::string& country() const;
        const size_t& year() const;
        double& price();
        Book(const std::string& strBook);

       template<typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(description_m);
        }
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
    };

}
#endif 
