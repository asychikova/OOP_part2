// Employee.cpp
#include "Employee.h"
#include "Utilities.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>


namespace seneca {

    Employee::Employee(const std::string& name, int age, const std::string& id)
        : m_name(name), m_age(age), m_id(id) {}

    std::string Employee::status() const {
        return "Employee";
    }

    std::string Employee::name() const {
        return m_name;
    }

    std::string Employee::id() const {
        return m_id;
    }

    std::string Employee::age() const {
        return std::to_string(m_age);
    }

    void Employee::display(std::ostream& out) const {
        out << "| " << std::left << std::setw(10) << status() << " | "
            << std::left << std::setw(10) << id() << " | "
            << std::left << std::setw(20) << name() << " | "
            << std::left << std::setw(3) << age() << " |" << std::endl;
    }

       std::istream& operator>>(std::istream& is, Employee& emp) {
        // Read data members of emp from is
        // For example:
        std::string name, id, ageStr;
        std::getline(is >> std::ws, name, ',');
        std::getline(is >> std::ws, ageStr, ',');
        int age = std::stoi(ageStr);
        std::getline(is >> std::ws, id);

        // Assign values to emp's data members
        emp.m_name = name;
        emp.m_age = age;
        emp.m_id = id;

        return is;
    }

}