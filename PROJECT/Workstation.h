
#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace seneca {
    extern std::deque<CustomerOrder>g_pending ;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;
    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation ;

    public:
        Workstation(const std::string& record);
        Workstation(const Workstation&) = delete;
        Workstation& operator=(const Workstation&) =delete;
       Workstation(Workstation&&)= delete ;
        Workstation& operator=(Workstation&&) = delete;
        void fills(std::ostream& os) ;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& custOrder) ;
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const ;
    };
} 
#endif 
