/*
*****************************************************************************
                          OOP345 Workshop - #1 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/
#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

namespace seneca{
 extern unsigned int g_sysClock;
    class Event {
        char description[128];
        unsigned int start_time;
        static unsigned int counter; 

    public:
        Event(); 
        Event(const Event& other) ; 
        Event& operator=(const Event& other);
        void set(const char* description = nullptr); 
        void display() const; 
    };

}
#endif 
