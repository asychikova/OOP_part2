/*
*****************************************************************************
                          OOP345 Workshop - #6 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <iostream>
#include "Person.h"
#include "Student.h"
#include "Professor.h"

namespace seneca {
    Person* buildInstance(std::istream& in);
}

#endif
