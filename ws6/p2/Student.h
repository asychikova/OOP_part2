/*
*****************************************************************************
                          OOP345 Workshop - #6 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#ifndef SENECA_STUDENT_H
#define SENECA_STUDENT_H
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include "Person.h"

namespace seneca {
class Student : public Person {
    public:
        Student(std::istream& in);
        ~Student();
        std::string status() const;
        std::string name() const;
        std::string age() const ;
        std::string id() const ;
        void display(std::ostream& out) const;

    private:
        std::vector<std::string> m_courses;
        std::string m_name ;
        std::string m_id;
        int m_age;
        std::string removeLeadingAndTrailingWhitespace(const std::string& str) const;
        void readCourses(const std::string& name, int count, std::istream& in) ;
        Student(const Student& other)= delete;
        Student& operator=(const Student& other){return *this;};
    };
}
#endif 
