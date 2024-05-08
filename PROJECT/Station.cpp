/*
*****************************************************************************
                          OOP345 MS3
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
Date of completion: 6th of March, 
I started Project at the first day of the release, during the midterm week, ~26 of February
*****************************************************************************
*/
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace seneca{
    size_t Station::m_widthField= 0;
    size_t Station::id_generator =0;

    Station::Station(const std::string& str) {
        Utilities util;
        bool more =true;
        size_t next_pos =0;

        m_itemName= util.extractToken(str, next_pos, more);
        std::string nextSerialNumberStr = util.extractToken(str,next_pos, more);
        std::string quantityStr =util.extractToken(str,next_pos, more);

        m_nextSerialNumber= std::stoi(nextSerialNumberStr);
        m_quantity =std::stoi(quantityStr);

        if(m_itemName.length()> m_widthField)
            m_widthField = m_itemName.length();
        if (util.getFieldWidth() >m_widthField)
            m_widthField =util.getFieldWidth();

        m_description= util.extractToken(str, next_pos, more);
        
        //trim
        size_t startPos= 0;
        while (startPos <m_description.length() &&(m_description[startPos] ==' ')) {
            ++startPos;
        }
        m_description = m_description.substr(startPos);

        //trim
         size_t endPos = m_description.length();
        while (endPos >0 &&(m_description[endPos- 1] ==' ')) {
            --endPos;
            
        }
        m_description= m_description.substr(0,endPos);
        m_id= ++id_generator;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_nextSerialNumber++;
    }

   void Station::updateQuantity() {
        if (m_quantity> 0) {
            m_quantity--;
        }
        else {
            std::cout <<"Quantity cannot be less than 0"<< std::endl;
        }
    }

     void Station::display(std::ostream& os, bool full) const {
        os << std::setw(3) <<std::setfill('0') << std::right<< m_id
           <<" | " <<std::setw(m_widthField)<<std::left <<std::setfill(' ')<<m_itemName
           << "| "<<std::setw(6) <<std::right<<std::setfill('0') <<m_nextSerialNumber<<" | ";

        if (full)
        {
            os<<std::setw(4)<< std::right <<std::setfill(' ')<< m_quantity<< " | "<<m_description;
        }
        os << std::endl;
    }
    
}
