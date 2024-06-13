
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca {
    size_t CustomerOrder::m_widthField =0;

    CustomerOrder::CustomerOrder() :m_name(""),m_product(""), m_cntItem(0),m_lstItem(nullptr){}

    CustomerOrder::CustomerOrder(const std::string& record): CustomerOrder(){
        Utilities util;
        size_t pos =0;
        bool more= true;
        m_name =util.extractToken(record, pos, more);
        m_product =util.extractToken(record, pos, more);
        m_cntItem= 0;
        for (char c : record){
            if (c ==util.getDelimiter()) {
                ++m_cntItem;
            }
        } --m_cntItem ;

        if (m_cntItem> 0) {
            m_lstItem =new Item*[m_cntItem];

            for (size_t i= 0; i < m_cntItem;++i){
                std::string itemRecord;
                while (pos <record.size() &&record[pos]!= util.getDelimiter()) {
                    itemRecord +=record[pos];
                    pos++;
                }
                ++pos;  
                m_lstItem[i] =new Item(itemRecord);
                size_t startPos= 0;

                //isspace used in order to remove spaces instead of manual way 
                while ( std::isspace(m_lstItem[i]->m_itemName[startPos] )) {
                    ++startPos;
                }
                m_lstItem[i]->m_itemName =m_lstItem[i]->m_itemName.substr(startPos);

                size_t endPos= m_lstItem[i] ->m_itemName.size()- 1;
                while (endPos >0 && std::isspace(m_lstItem[i]->m_itemName[endPos])){
                    --endPos;
                }
                 m_lstItem[i]-> m_itemName =m_lstItem[i]->m_itemName.substr(0,endPos + 1);
            }
            if (util.getFieldWidth()> m_widthField) {
                m_widthField =util.getFieldWidth();
            }
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& src){
        throw std::string( "Copy operations are not allowed");
    }


    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept{
        m_name =src.m_name;
        m_product= src.m_product;
        m_cntItem= src.m_cntItem;
        m_lstItem =src.m_lstItem;
        src.m_cntItem =0;
        src.m_lstItem= nullptr;
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this !=&src){
            m_name =src.m_name;
            m_product= src.m_product;
            m_cntItem= src.m_cntItem;
            m_lstItem =src.m_lstItem;
            src.m_cntItem =0;
            src.m_lstItem= nullptr;

             if (src.m_lstItem) {
                for (size_t i = 0;i < src.m_cntItem; ++i) {
                    delete src.m_lstItem[i] ;
                }
            }
        } return *this;
    }

    CustomerOrder::~CustomerOrder() {
        if (m_lstItem !=nullptr) {
             for (size_t i= 0;i < m_cntItem; ++i){
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            m_lstItem= nullptr;
        }
    }

    bool CustomerOrder::isOrderFilled() const{
        for (size_t i =0;i < m_cntItem; ++i) {
            if (!m_lstItem[i]-> m_isFilled){
                 return false;
            }
        } return true;
    }


    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
       for (size_t i =0;i < m_cntItem; ++i) {
            if (m_lstItem[i]-> m_itemName== itemName) {
                if (!m_lstItem[i]->m_isFilled) {
                    return false;
                }
            }
        } return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os){
        for (size_t i =0;i < m_cntItem;++i) {
           if(isItemToBeFilled(station,i)) {
                if (station.getQuantity()> 0) {
                    fillSingleItem(station,os, i);
                    break;
                } else{
                    unableToFillItem(os,i);
                }
            }
        }
    }

    bool CustomerOrder::isItemToBeFilled(Station& station, size_t index){
     return station.getItemName() == m_lstItem[index]->m_itemName && !m_lstItem[index]->m_isFilled;
    }

     void CustomerOrder::fillSingleItem(Station& station, std::ostream& os,size_t index) {
        m_lstItem[index]-> m_serialNumber =station.getNextSerialNumber();
        m_lstItem[index]->m_isFilled =true;
        station.updateQuantity() ;
        os<<"    Filled "<<m_name<< ", " <<m_product <<" [" <<m_lstItem[index]-> m_itemName<< "]" <<std::endl;
    }

    void CustomerOrder::unableToFillItem(std::ostream& os,size_t index) {
        os<<"    Unable to fill "<<m_name<< ", " <<m_product <<" [" <<m_lstItem[index]-> m_itemName<< "]" <<std::endl;
    }

    void CustomerOrder::display(std::ostream& os) const {
         os<< m_name<< " - "<<m_product <<std::endl;
        for (size_t i =0;i < m_cntItem; ++i) {
            os<<"[" <<std::setw(6) <<std::setfill('0') <<std::right<<m_lstItem[i]->m_serialNumber<< "] "
            <<std::setw(m_widthField -1) <<std::setfill(' ')<<std::left <<m_lstItem[i]->m_itemName<< "- "<<(m_lstItem[i]->m_isFilled ? "FILLED" :"TO BE FILLED") <<std::endl;
        }
    }

}
