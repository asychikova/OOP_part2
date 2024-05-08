/*
*****************************************************************************
                          OOP345 Workshop - #2 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#ifndef SENECA_TIMEDEVENTS_H
#define SENECA_TIMEDEVENTS_H
#include <iostream>
#include <chrono>
#include <string>

namespace seneca {
    struct Event {
        std::string name;
        std::string units;
        std::chrono::steady_clock::duration duration;
    };

    class TimedEvents {
    private:
        static const size_t MAX_EVENTS =10;
        size_t numRecords;
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point endTime;
        Event events[ MAX_EVENTS];
    public:
        TimedEvents();
        void startClock();
        void stopClock() ;
        void addEvent( const char* eventName);
        friend std::ostream& operator<<( std::ostream& os,const TimedEvents& te);
    };
} 
#endif
