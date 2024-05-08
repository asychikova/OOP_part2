/*
*****************************************************************************
                          OOP345 MS3
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
Date of completion: 4th of April, 
I started Project at the first day of the release, during the midterm week. 
*****************************************************************************
*/
#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H
#include <vector>
#include "Workstation.h"

namespace seneca {
    class LineManager {
        std::vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder ;
         Workstation* m_firstStation;


    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void display(std::ostream& os) const ;
        void reorderStations();
        bool run(std::ostream& os);
    };
}
#endif 
