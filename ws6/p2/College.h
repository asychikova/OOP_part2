/*
*****************************************************************************
                          OOP345 Workshop - #6 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#ifndef SENECA_COLLEGE_H
#define SENECA_COLLEGE_H
#include <vector>
#include <list>
#include "Person.h"

namespace seneca{
    class College {
    private:
        std::vector<Person*> m_persons;
    public:
        College& operator+=(Person* thePerson) ;
        void display( std::ostream& out) const;
        ~College();
        template <typename T>
        void select(const T& test, std::list<const Person*>& persons ) ;
    };
    
    template <typename T>
    void College::select(const T& test, std::list<const Person*>& persons)
        { for(const auto& person : m_persons)
            {if (test(person) )
                persons.push_back(person);
            }
        }
}

#endif
