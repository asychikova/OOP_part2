/*
*****************************************************************************
                          OOP345 Workshop - #3 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#ifndef SENECA_SET_H
#define SENECA_SET_H

#include "Collection.h"
#include <cmath> 

namespace seneca {

    template <typename T>
    class Set :public Collection< T, 100> {
    public:
        bool add(const T& item) override{
            for (int i = 0; i <this->size();++i) {
                if (item==(*this)[i] ) {
                    return false; 
                }
            }
            return Collection<T,100>::add(item);
        }
    };

    template <>
    class Set<double> :public Collection<double, 100 > {
    public:
        bool add(const double& item) override{
            for (int i = 0; i <this->size();++i) {
                if (std::fabs( item - (*this )[i] )<=0.01) {
                    return false; 
                }
            }
            return Collection<double,100>::add(item);
        }
    };

} 

#endif
