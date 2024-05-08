/*
*****************************************************************************
                          OOP345 Workshop - #1 (P1)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include "event.h"

namespace seneca{

    unsigned int g_sysClock = 0;
    //unsigned int Event::counter =0;

    Event::Event() : start_time(0) {
        description[0] ='\0';
    } 
    // Event::Event() : description{},start_time(0){}


    Event::Event(const Event& other) : start_time( other.start_time) {
        strcpy(description, other.description );
    }

    void Event::set(const char* desc) {
        if (desc != nullptr && desc[0] !='\0') {
            strncpy(description, desc, sizeof(description) - 1);
            description[sizeof(description) - 1] = '\0'; 
            start_time = g_sysClock ;
        } else {
            description[0] ='\0';
            start_time = 0;
        }
    }

    Event& Event::operator=(const Event& other) {
        if (this != &other ) {
            start_time = other.start_time ;
            strcpy(description, other.description);
        }
        return *this;
    }

    void Event::display() const {
        static int counter = 0;
        std::cout <<std::setfill(' ')<<std::setw(2)<< ++counter<<". ";
        if (description[0] !='\0') {
            unsigned int hours = start_time /3600;
            unsigned int remaining_after_hours =start_time -(hours*3600 );
            unsigned int minutes =remaining_after_hours/60;
            unsigned int seconds = remaining_after_hours- (minutes* 60) ;

            std::cout <<std::setw(2)<<std::setfill('0') <<hours<< ":"<< std::setw(2)<< minutes << ":"<<std::setw(2) <<seconds<<" => " <<description <<std::endl;
        } else {
            std::cout<<"| No Event |" <<std::endl;
        }
    }

}

