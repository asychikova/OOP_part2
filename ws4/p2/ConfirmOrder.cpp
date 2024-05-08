/*
*****************************************************************************
                          OOP345 Workshop - #4 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#include "ConfirmOrder.h"

namespace seneca {

    ConfirmOrder::ConfirmOrder(): m_toys(nullptr), m_numToys(0){}

    ConfirmOrder::ConfirmOrder(const ConfirmOrder& src): m_toys(nullptr), m_numToys(src.m_numToys) {
        if (m_numToys > 0) {
            m_toys =new const Toy*[m_numToys];
            for (size_t i = 0;i < m_numToys; ++i) {
                m_toys[i]= src.m_toys[i];
            }
        }
    }

    ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& src) {
        if (this != &src) {
            delete[] m_toys;

            m_numToys =src.m_numToys;
            if (m_numToys > 0) {
                m_toys =new const Toy*[m_numToys];
                for (size_t i = 0;i < m_numToys; ++i) {
                    m_toys[i]= src.m_toys[i];
                }
            } else {
                m_toys = nullptr;
            }
        } return *this;
    }

    ConfirmOrder::ConfirmOrder(ConfirmOrder&& src) : m_toys(src.m_toys), m_numToys(src.m_numToys){
        src.m_toys = nullptr;
        src.m_numToys= 0;
    }

    ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& src){
        if (this != &src) {
            delete[] m_toys;

            m_toys =src.m_toys;
            m_numToys = src.m_numToys;

            src.m_toys = nullptr;
            src.m_numToys= 0;
        } return *this;
    }

    ConfirmOrder::~ConfirmOrder() {
        delete[] m_toys;
    }

    void ConfirmOrder::display(std::ostream& os) const {
        os<< "--------------------------\n"
           <<"Confirmations to Send\n"
           <<"--------------------------\n";

        if (m_numToys== 0) {
            os<<"There are no confirmations to send!\n";
        }
        else {
            for (size_t i = 0;i < m_numToys; ++i) {
                os <<*m_toys[i];
            }
        }
        os<<"--------------------------\n";
    }

    void ConfirmOrder::add(const Toy& toy){
        if (!containsToy(toy)) {
            const Toy** temp =new const Toy*[m_numToys + 1];
            for (size_t i = 0;i < m_numToys; ++i) {
                temp[i]= m_toys[i] ;
            }
            temp[m_numToys]= &toy;
            delete[] m_toys;
            m_toys =temp;
            m_numToys++;
        }
    }

    bool ConfirmOrder::containsToy(const Toy& toy) const {
        for (size_t i = 0;i <m_numToys; ++i) {
            if (m_toys[i]== &toy) {
                return true;
            }
        }
        return false;
    }

    ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy){
        add(toy);
        return *this;
    }

    ConfirmOrder& ConfirmOrder::operator+=(ConfirmOrder&& other) {
        if (this!= &other) {
            for (size_t i = 0;i< other.m_numToys; ++i) {
                add(*(other.m_toys[i]) );
            }
            other.m_toys = nullptr;
            other.m_numToys= 0;
        }
        return *this;
    }

    ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy) {
        for (size_t i = 0;i <m_numToys; ++i) {
            if (m_toys[i]== &toy) {
                for (size_t j = i;j < m_numToys - 1; ++j) {
                    m_toys[j]= m_toys[j + 1];
                }
                --m_numToys;
                break;
            }
        }
        return *this;
    }

    ConfirmOrder& ConfirmOrder::operator-=(ConfirmOrder&& other){
        if (this != &other){
            for (size_t i = 0;i < other.m_numToys; ++i) {
                for (size_t j = 0;j <m_numToys; ++j) {
                    if (m_toys[j] ==other.m_toys[i]) {
                        for (size_t k =j; k< m_numToys -1;++k) {
                            m_toys[k]= m_toys[k + 1];
                        }
                        --m_numToys;
                        break;
                    }
                }
            }

            other.m_toys= nullptr;
            other.m_numToys =0;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const ConfirmOrder& confirmOrder){
        confirmOrder.display(os);
        return os ;
    }

}  



