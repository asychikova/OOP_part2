/*
*****************************************************************************
                          OOP345 MS3
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
Date of completion: 4th of April, (customer order module was changed for 3rd MS) 
I started Project at the first day of the release, during the midterm week. 
*****************************************************************************
*/
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include "Station.h"

namespace seneca {
    struct Item 
    {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string& src) : m_itemName(src) {};
    };

    class CustomerOrder {
       std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        Item** m_lstItem;
        static size_t m_widthField;

    public:
        CustomerOrder();
        CustomerOrder(const std::string&);
        CustomerOrder(const CustomerOrder&) ;
        ~CustomerOrder() ;
        CustomerOrder& operator=(const CustomerOrder&) = delete;
        CustomerOrder& operator=(CustomerOrder&&) noexcept;
        CustomerOrder(CustomerOrder&&) noexcept;
       bool isOrderFilled() const ;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
       void display(std::ostream& os) const;
        bool isItemToBeFilled(Station& station, size_t index) ;
        void fillSingleItem(Station& station,std::ostream& os,size_t index);
        void unableToFillItem(std::ostream& os,size_t index);
    };
}
#endif 