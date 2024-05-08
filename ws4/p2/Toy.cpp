/*
*****************************************************************************
                          OOP345 Workshop - #4 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#include "Toy.h"
#include <iomanip>
#include <sstream>

namespace seneca {

    Toy::Toy() :m_orderId(0), m_name(""), m_numItems(0), m_price(0.0), m_hst(0.13){}

    void Toy::update(int numItems) {
        m_numItems =numItems;
    }

    Toy::Toy(const std::string& toy) {
        size_t position = 0;
        char delimiter =':';

        for (int i = 0;i < 4; ++i)  {
            size_t nextPosit =toy.find(delimiter,position);
            std::string token =toy.substr(position, nextPosit- position);
            switch (i) {
                case 0:m_orderId =std::stoi(token); break;
                case 1:m_name= token;break;
                case 2:m_numItems =std::stoi(token); break;
                case 3:m_price = std::stod(token);break;
            }position =nextPosit +1;
        }
        m_name.erase( 0,m_name.find_first_not_of(' ') );
        m_name.erase(m_name.find_last_not_of(' ')+ 1);
    }

    double Toy::calculateTax() const {
        return m_numItems * m_price *0.13;
    }

    std::ostream& operator<<(std::ostream& os, const Toy& toy) {
        double subtotal= toy.m_numItems * toy.m_price;
        double tax =toy.calculateTax();
        double total= subtotal+ tax;

        os<<"Toy "<<toy.m_orderId << ":"<<std::setw(18) <<std::right <<toy.m_name
            <<std::setw(3) <<toy.m_numItems<<" items"
            << std::fixed <<std::setprecision(2)<< std::setw(8)<<std::right <<toy.m_price
            << "/item  subtotal: "<< std::setw(6)<<std::right<< subtotal 
            <<" tax:"<<std::setw(6) <<std::right<< tax
            << " total: "<< std::setw(6)<< std::right <<total<< '\n';

        return os;
    }

    bool Toy::operator==(const Toy& other) const {
            return m_orderId == other.m_orderId;
        }

}
