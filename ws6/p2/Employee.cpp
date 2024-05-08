/*
*****************************************************************************
                          OOP345 Workshop - #6 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#include <iostream>
#include <iomanip>
#include "Employee.h"
#include "Professor.h"
#include "Utilities.h"

namespace seneca {
    Employee::Employee(std::istream& in) {
            std::string tag;
            char ch;
            while(in.get(ch)&& ch != ',') {
                tag += ch;
            }
            tag =removeLeadingAndTrailingWhitespace(tag);

            std::string name;
            while (in.get(ch) &&ch !=',') {
                name += ch;
            }
            name =removeLeadingAndTrailingWhitespace(name);

            std::string ageStr;
            while (in.get(ch)&& ch != ',') {
                ageStr += ch;
            }
            ageStr = removeLeadingAndTrailingWhitespace(ageStr);
            int age =std::stoi(ageStr);

            char idChars[9];
            for (int i = 0;i<8; ++i) {
                if (!in.get(idChars[i])) {
                    throw std::invalid_argument(name+"++Invalid record!");
                }
            }
            idChars[8]= '\0';
            std::string id(idChars);
            id = removeLeadingAndTrailingWhitespace(id);
            if(id[0]!= 'E') {
                throw std::invalid_argument(name +"++Invalid record!");
            }
            m_name =name;
            m_age= age;
            m_id = id;
        }


    std::string Employee::status() const {
        return "Employee"; }

    std::string Employee::name() const {
        return m_name; }

    std::string Employee::id() const {
        return m_id;}

    std::string Employee::age() const {
        return std::to_string(m_age);}


    std::string Employee::removeLeadingAndTrailingWhitespace(const std::string& str) const {
        size_t first =0;
        while (first <str.length()&&(str[first] == ' '|| str[first]=='\t')) {
            ++first;}

        size_t last =str.length() - 1;
        while (last> first&& (str[last]== ' ' ||str[last] =='\t')) {
            --last;}

        if(first >=str.length()||last < first) {
            return "";}

        return str.substr(first, last-first +1);
    }

    void Employee::display(std::ostream& out) const {
        out<< "| " <<std::left<< std::setw(10)<<"Employee  | "<<std::left<< std::setw(10)<< id() << "| "
            << std::left<< std::setw(21)<<name() << "| "<<std::left << std::setw(4) <<age() << "|";
    }

} 
