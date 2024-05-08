/*
*****************************************************************************
                          OOP345 Workshop - #3 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#include <iomanip>
#include "Pair.h"

namespace seneca {

    const std::string& Pair::getKey() const {
        return m_key;
    }

    const std::string& Pair::getValue()const {
        return m_value;
    }

    Pair::Pair() = default;

    Pair::Pair(const std::string& key,const std::string& value) : m_key{key} , m_value{value}{}

    bool Pair::operator==(const Pair& other)const {
        return m_key ==other.m_key;
    }

    std::ostream& operator<<(std::ostream& os, const Pair& pair) {
        os <<std::setw(20)<< pair.getKey()<<": " <<pair.getValue();
        return os;
    }
}
