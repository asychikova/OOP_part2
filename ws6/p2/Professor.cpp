/*
*****************************************************************************
                          OOP345 Workshop - #6 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#include <iomanip>
#include "Professor.h"

namespace seneca {
       Professor::Professor(std::istream& in) : Employee(in){
        char ch;
        bool departmentStarted = false;
        while (in.get(ch)&& ch != '\n') {
            if (!departmentStarted &&(ch == ' '|| ch== '\t'))
                continue;
            departmentStarted =true;
            m_department +=ch;
        }
        if (m_department[0]== ',') {
            m_department = m_department.substr(1);
        }
         m_department =removeLeadingAndTrailingWhitespace(m_department);
    }

    void Professor::display(std::ostream& out) const{
            Employee::display(out);
            out<< m_department<<"| Professor";
        }

    std::string Professor::status() const{
            return "Professor" ;
        }

    std::string Professor::department() const{
            return m_department;
        }
}
