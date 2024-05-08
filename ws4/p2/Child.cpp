/*
*****************************************************************************
                          OOP345 Workshop - #4 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#include "Child.h"

namespace seneca {

    Child::Child(): m_name(""), m_age(0), m_toys(nullptr),m_numToys(0) {}

    Child::Child(const std::string& name,int age,const Toy* toys[],size_t numToys)
        : m_name(name),m_age(age), m_toys(nullptr),m_numToys(numToys) {
        if (numToys > 0){
            m_toys =new const Toy*[numToys];
            for (size_t i = 0;i < numToys; ++i) {
                m_toys[i]= new Toy(*toys[i] );
            }
        }
    }

    Child::Child(const Child& src): m_name(src.m_name),m_age(src.m_age),m_toys(nullptr), m_numToys(src.m_numToys) {
        if (m_numToys > 0) {
            m_toys =new const Toy*[m_numToys];
            for (size_t i = 0;i < m_numToys; ++i) {
                m_toys[i]= new Toy(*src.m_toys[i]);
            }
        }
    }

    Child& Child::operator=(const Child& src) {
        if (this != &src) {
            for (size_t i = 0;i < m_numToys; ++i) {
                delete m_toys[i];
            }delete[] m_toys;

            m_name= src.m_name;
            m_age =src.m_age;
            m_numToys= src.m_numToys ;

            if (m_numToys > 0){
                m_toys =new const Toy*[m_numToys];
                for (size_t i = 0;i < m_numToys; ++i) {
                    m_toys[i]= new Toy(*src.m_toys[i]);
                }
            }else {
                m_toys = nullptr;
            }
        }return *this;
    }

    Child::Child(Child&& src)
    : m_name(std::move(src.m_name)), m_age(src.m_age), m_toys(src.m_toys), m_numToys(src.m_numToys) {
        src.m_toys =nullptr;
        src.m_numToys= 0 ;
        src.m_age = 0;
    }

    Child& Child::operator=(Child&& src){
        if (this != &src ){
            for (size_t i =0;i < m_numToys; ++i) {
                delete m_toys[i];
            } delete[] m_toys;

            m_name= std::move(src.m_name);
            m_age =src.m_age;
            m_toys= src.m_toys;
            m_numToys = src.m_numToys;

            src.m_toys = nullptr;
            src.m_numToys =0 ;
            src.m_age = 0;
        } return *this;
    }

    Child::~Child() {
        for (size_t i = 0;i< m_numToys; ++i) {
            delete m_toys[i];
        }
        delete[] m_toys;
    }

	std::ostream& operator<<(std::ostream& os,const Child& child) {
		static int CHILDNUMBER = 0;
		++CHILDNUMBER;
		os <<"--------------------------\n"<<"Child "<< CHILDNUMBER<< ": "<< child.m_name<< " "
        <<child.m_age<< " years old:\n"<< "--------------------------\n";

		if (child.m_numToys ==0){
			os<<"This child has no toys!\n";
		}
		else {
			for(size_t i = 0;i < child.m_numToys; ++i) {
				os <<*child.m_toys[i] ;
			}
		}
		os<< "--------------------------\n";
		return os;
	}

}

