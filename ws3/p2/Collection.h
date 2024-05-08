/*
*****************************************************************************
                          OOP345 Workshop - #3 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <iomanip>
#include "Pair.h"

namespace seneca {
    template <typename T, unsigned int CAPACITY>
    class Collection {
        T m_dummy{} ;
        T m_data[CAPACITY]{};
        std::size_t m_size{};

    public:
    virtual ~Collection(){}
        int size() const{
            return m_size;
        }

        void display( std::ostream& os = std::cout)const {
            os<<"----------------------\n| Collection Content |\n----------------------\n";
            for(std::size_t i = 0;i <m_size; ++i) {
                os<<m_data[i] <<'\n';  
            } os <<"----------------------\n";
        }

        virtual bool add(const T& item) {
            if (m_size <CAPACITY) {
                m_data[m_size++] =item;
                return true;
            }
            return false;
        }

        T operator[](std::size_t index)const {
            if (index< m_size) {
                return m_data[index];
            }
            return m_dummy;
        };

    };

    template <>
    class Collection<Pair, 100> {
        Pair m_dummy{ "No Key", "No Value" };
        Pair m_data[100]{};
        std::size_t m_size{};

    public:
     virtual ~Collection(){}
        int size() const{
            return m_size;
        }

        void display( std::ostream& os = std::cout)const {
            os<<"----------------------\n| Collection Content |\n----------------------\n";
            for(std::size_t i = 0;i <m_size; ++i) {
                os<<m_data[i] <<'\n';
            }os <<"----------------------\n";
        }

        virtual bool add(const Pair& item) {
            if (m_size < 100) {
                m_data[m_size++] =item;
                return true;
            } return false;
        }

        Pair operator[](std::size_t index)const {
            if (index< m_size) {
                return m_data[index];
            }
            return m_dummy;
        }
    };
} 

#endif
