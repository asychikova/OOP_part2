/*
*****************************************************************************
                          OOP345 Workshop - #4 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#ifndef SENECA_CONFIRMORDER_H
#define SENECA_CONFIRMORDER_H

#include "Toy.h"

namespace seneca {

    class ConfirmOrder {
        const Toy** m_toys;
        size_t m_numToys ;

    public:
        ConfirmOrder();
        ConfirmOrder(const ConfirmOrder& src) ;
        ConfirmOrder& operator=( const ConfirmOrder& src);
        ConfirmOrder(ConfirmOrder&& src);
        ConfirmOrder& operator=( ConfirmOrder&& src );
        ~ConfirmOrder();
        void display(std::ostream& os )const;
        void add(const Toy& toy);
        ConfirmOrder& operator+=(const Toy& toy);
        ConfirmOrder& operator+=( ConfirmOrder&& other);
        ConfirmOrder& operator-=(const Toy& toy);
        ConfirmOrder& operator-=(ConfirmOrder&& other );
        bool containsToy(const Toy& toy) const;
    };
    std::ostream& operator<<( std::ostream& os,const ConfirmOrder& confirmOrder);

}
#endif
