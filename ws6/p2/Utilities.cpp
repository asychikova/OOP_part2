/*
*****************************************************************************
                          OOP345 Workshop - #6 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#include "Utilities.h"
#include "Employee.h"
#include "Student.h"
#include "Professor.h"

namespace seneca {
    Person* buildInstance(std::istream& in)
    {
        char tag;
        if (!(in>> tag))
            return nullptr;

        if (tag == ' '|| tag =='\t') {
            in >>tag;
        }
        
        if (tag == 'E'|| tag== 'e')
            return new Employee(in);
        else if (tag =='S'|| tag== 's')
            return new Student(in);
        else if (tag =='P' ||tag =='p')
            return new Professor(in);
        return nullptr;
    }
}
