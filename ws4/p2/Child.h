/*
*****************************************************************************
                          OOP345 Workshop - #4 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#ifndef SENECA_CHILD_H
#define SENECA_CHILD_H
#include <ostream>
#include "Toy.h"

namespace seneca {

    class Child {
        std::string m_name ;
        int m_age;
        const Toy** m_toys;
        size_t m_numToys;
    public:
        Child();
        Child(const std::string& name, int age, const Toy* toys[], size_t numToys );
        Child(const Child& src) ;
        Child& operator=(const Child& src);
        Child(Child&& src)  ;
        Child& operator=(Child&& src);
        ~Child();
        friend std::ostream& operator<<(std::ostream& os, const Child& child);
    };
}
#endif
