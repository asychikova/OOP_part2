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
#include "Student.h"

namespace seneca {
    Student::Student(std::istream& in) {
        char ch;
        std::string tag,name, id,ageStr, countStr;
        int age, count;
        while (in.get(ch)&& ch != ',') {
            tag += ch;
        }
        tag= removeLeadingAndTrailingWhitespace(tag);

        while (in.get(ch)&& ch != ',') {
            name += ch;
        }
        name= removeLeadingAndTrailingWhitespace(name);

        while (in.get(ch)&& ch != ',') {
            ageStr += ch;
        }
        ageStr =removeLeadingAndTrailingWhitespace(ageStr);

        bool isValidAge = true;
        for (char c : ageStr) {
            if (c <'0' || c >'9') {
                isValidAge = false;
                break;
            }
        }if (!isValidAge) {
            throw std::invalid_argument(name + "++Invalid record!");
        }
        age = std::stoi(ageStr);

        while (in.get(ch) &&ch !=',') {
            id += ch;
        }
        id = removeLeadingAndTrailingWhitespace(id);
        if (id[0] !='S') {
            throw std::invalid_argument(name +"++Invalid record! ID");
        }
        while (in.get(ch) &&ch != ',') {
            countStr+= ch;
        }
        countStr =removeLeadingAndTrailingWhitespace(countStr);
        count= std::stoi(countStr);

        readCourses(name,count, in);
        if (m_courses.size() !=static_cast<size_t>(count)) {
            throw std::invalid_argument(name+ "++Invalid record!");
        }
        m_name =name;
        m_age= age;
        m_id= id;
    }

    Student::~Student() {
    }

    std::string Student::status() const {
        return "Student";
    }

    std::string Student::name() const {
        return m_name;
    }

    std::string Student::age() const {
        return std::to_string( m_age);
    }

    std::string Student::id() const {
        return m_id;
    }

    void Student::display(std::ostream& out) const {
        out << "| "<<std::left << std::setw(10)<<status()<< "| "<< std::setw(10)<< id() << "| "
            <<std::left << std::setw(21)<< name() << "| "<< std::setw(4)<<age()<<"|";
        for (size_t i = 0; i < m_courses.size(); ++i) {
            out <<m_courses[i];
            if (i != m_courses.size()- 1)
                out <<", ";
        }
    }

    std::string Student::removeLeadingAndTrailingWhitespace(const std::string& str) const {
        size_t first =0;
        while (first <str.length()&&(str[first] == ' '|| str[first]=='\t')) {
            ++first;}

        size_t last =str.length() - 1;
        while (last> first&& (str[last]== ' ' ||str[last] =='\t')) {
            --last;}

        if (first >=str.length()||last < first) {
            return "";}

        return str.substr(first, last-first +1);
    }

    void Student::readCourses(const std::string& name, int count, std::istream& in) {
        std::string courseLine;
        std::getline(in,courseLine); 
        courseLine =removeLeadingAndTrailingWhitespace(courseLine); 
        size_t startPos= 0;
        size_t endPos =0;
        int coursesRead= 0;
        while (coursesRead <count &&endPos!= std::string::npos) {
            endPos = courseLine.find(',',startPos);
            std::string singleCourse= courseLine.substr(startPos, endPos - startPos);
            singleCourse = removeLeadingAndTrailingWhitespace(singleCourse);

            m_courses.push_back(singleCourse);
            if (endPos!= std::string::npos) {
                startPos = endPos+ 1;
            }coursesRead++;
        }
    }

}
