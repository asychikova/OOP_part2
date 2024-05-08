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
#include "College.h"
#include "Employee.h"
#include "Professor.h"
#include "Student.h"

namespace seneca {
    College& College::operator+=(Person* thePerson)
        {
            m_persons.push_back(thePerson);
            return *this;
        }

    void College::display(std::ostream& out) const
        {
            out<< "------------------------------------------------------------------------------------------------------------------------" <<std::endl;
            out <<"|                                        Test #1 Persons in the college!                                               |" <<std::endl;
            out<< "------------------------------------------------------------------------------------------------------------------------"<< std::endl;
            for(const auto& person : m_persons) {
                    person->display(out);
                    out<< std::endl;
                }
            out<< "------------------------------------------------------------------------------------------------------------------------" <<std::endl;
            out <<"|                                        Test #2 Persons in the college!                                               |" <<std::endl;
            out<< "------------------------------------------------------------------------------------------------------------------------"<< std::endl;
            for (const auto& person : m_persons) {
                if(dynamic_cast<Professor*>(person)){
                    const Employee* employee =dynamic_cast<Employee*>(person);
                    out << "| "<<std::left <<std::setw(10)<< person->status() <<"| "<<std::setw(10)<<employee->id()<< "| "
                        << std::setw(21)<< employee->name()<<  "| "<<  std::setw(4) <<employee->age()<< "|"<< std::endl;
                } else if(dynamic_cast<Student*>(person)) {
                    const Student* student =dynamic_cast<Student*>(person);
                    out << "| "<<std::left<< std::setw(10)<< person->status() <<"| "<< std::setw(10)<<student->id()<< "| "
                        <<std::left <<std::setw(21)<< student->name()<< "| "<< std::setw(4)<< student->age()<< "|";
                    out <<std::endl;
                } else{
                    person->display(out);
                    out<< std::endl;
                }
            }out << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
        }

    College::~College()
        { for (auto& person : m_persons)
                delete person;
        }
}
