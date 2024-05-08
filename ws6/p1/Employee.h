// Employee.h
#ifndef SENECA_EMPLOYEE_H
#define SENECA_EMPLOYEE_H

#include "Person.h"
#include <iostream>

namespace seneca {

    class Employee : public Person {
    private:
        std::string m_name;
        int m_age;
        std::string m_id;

    public:
        Employee(const std::string& name, int age, const std::string& id);

        std::string status() const override;
        std::string name() const override;
        std::string id() const override;
        std::string age() const override;
        void display(std::ostream& out) const override;
         friend std::istream& operator>>(std::istream& is, Employee& emp);
    };
}

#endif