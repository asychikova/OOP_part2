/*
*****************************************************************************
                          OOP345 Workshop - #6 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#ifndef SENECA_EMPLOYEE_H
#define SENECA_EMPLOYEE_H
#include <iostream>
#include "Person.h"

namespace seneca {
    class Employee : public Person {
    private:
        std::string m_name;
        int m_age;
        std::string m_id;
        void readEmployeeRecord(std::istream& in);

    public:
        Employee(std::istream& in);
        std::string status() const override;
        std::string name() const override;
        std::string id() const override;
        std::string age() const override;
        void display(std::ostream& out) const override;
        std::string removeLeadingAndTrailingWhitespace(const std::string& str) const;
    };

} 
#endif 
