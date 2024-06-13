
#include "Workstation.h"

namespace seneca {
    std::deque<CustomerOrder> g_pending ;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string& record) :Station(record){}

    void Workstation::fills(std::ostream& os){
        if (m_orders.empty()){
            return;
        }m_orders.front().fillItem(*this,os);
    }

    bool Workstation::attemptToMoveOrder() {
        if (m_orders.empty())
            return false ; 
        auto& thisOrder =m_orders.front();
        bool canMoveOrder= thisOrder.isItemFilled(getItemName())|| getQuantity() ==0;
        if (!canMoveOrder)
            return false; 
        if (!m_pNextStation){
            if(thisOrder.isOrderFilled() )
                g_completed.push_back(std::move( thisOrder));
            else
                g_incomplete.push_back(std::move( thisOrder));
            m_orders.pop_front() ; 
            return true; 
        }*m_pNextStation +=std::move( thisOrder) ; 
        m_orders.pop_front(); 
        return true; 
    }

   void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const {
        os<<getItemName()<< " --> " << (m_pNextStation? m_pNextStation-> getItemName() :"End of Line")<< std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& custOrder) {
        m_orders.push_back(std::move( custOrder));
        return *this;
    }
}
