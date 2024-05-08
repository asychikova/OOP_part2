/*
*****************************************************************************
                          OOP345 Workshop - #6 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#ifndef SENECA_PROFESSOR_H
#define SENECA_PROFESSOR_H
#include <string>
#include <iostream>
#include "Employee.h"

namespace seneca {
    class Professor : public Employee {
    private:
        std::string m_department;
    public:
        Professor(std::istream& in);
        void readProfessorRecord(std::istream& in) ;
        void display(std::ostream& out) const override;
        std::string status() const override;
        std::string department() const ;
    };
}

#endif
