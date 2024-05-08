/*
*****************************************************************************
                          OOP345 Workshop - #1 (P2)
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

    Event::Event() : description( nullptr), start_time(0) {}

    Event::~Event() {
        delete[] description;
    }  

    Event::Event(const Event& other) : description(nullptr), start_time( other.start_time) {
        if ( other.description !=nullptr && other.description[0] !='\0') {
            description =new char[ strlen(other.description ) + 1];
            strcpy(description, other.description );  
        }
    }

    void Event::set(const char* desc) {
        delete[] description;
        if (desc != nullptr && desc[0] !='\0') {
            description =new char[ strlen(desc) + 1];
            strcpy(description, desc);
            start_time = g_sysClock ; 
        } else {
           description = nullptr;
            start_time = 0;
        }
    } 

    Event& Event::operator=(const Event& other) {
        if (this != &other ) {
            delete[] description;
            start_time = other.start_time ;
            if (other.description != nullptr && other.description[0] !='\0') {
                description = new char[ strlen(other.description) + 1];
                strcpy(description, other.description );
            } else {
                description = nullptr;
            }
        }return *this;
    }

    void Event::display() const {
        static int counter = 0;
        std::cout <<std::setfill(' ')<<std::setw(2)<< ++counter<<". ";
        if (description != nullptr) {
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
