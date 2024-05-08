/*
*****************************************************************************
                          OOP345 Workshop - #4 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#ifndef SENECA_TOY_H
#define SENECA_TOY_H

#include <iostream>
#include <string>

namespace seneca {

    class Toy {
        int m_orderId;
        std::string m_name;
        int m_numItems ;
        double m_price;
        double m_hst;
        double calculateTax()const;

    public:
        Toy();
        void update(int numItems);
        Toy(const std::string& toy) ;
        friend std::ostream& operator<<( std::ostream& os, const Toy& toy);
        bool operator==(const Toy& other )const;
    };

}
#endif 
