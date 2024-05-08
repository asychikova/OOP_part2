#include "College.h"
#include <iomanip>
namespace seneca {
    College::~College() {
        for (auto person : m_persons)
            delete person;
    }

    College& College::operator+=(Person* thePerson) {
        m_persons.push_back(thePerson);
        return *this;
    }

    void College::display(std::ostream& out) const {
        out << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
        out << "|" << std::setw(73) <<  "Test #1 Persons in the college!" <<  std::setw(46)<< "|" << std::endl;
        out << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
        for (auto person : m_persons)
            person->display(out);
        out << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
        out << "|" <<"                                          Test #2 Persons in the college!" <<  std::setw(46)<< "|" << std::endl;
        out << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
        for (auto person : m_persons) {
            
               out << "| " << std::left << std::setw(10) << person->status() << " | "
            << std::left << std::setw(10) << person->id() << " | "
            << std::left << std::setw(20) << person->name() << " | "
            << std::left << std::setw(3) << person ->age() << " |" << std::endl;
        }
        out << "-----------------------------------------" << std::endl;


    }
}
