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
#include "LineManager.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace seneca {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) : m_cntCustomerOrder(0), m_firstStation(nullptr){
    std::ifstream filename(file);
    std::string record;
        m_cntCustomerOrder= g_pending.size();
        while (std::getline(filename, record )) {
            char delimiter ='|';
            size_t delimiterPos = record.find(delimiter);
            std::string firststName= record.substr(0,delimiterPos);
            for (Workstation* st :stations) {
                if (st->getItemName() ==firststName) {
                    m_firstStation = st;
                    break;
                }
            } if (m_firstStation) {
                m_activeLine.push_back(m_firstStation);
                }
        }
         filename.clear();
        filename.seekg(0);

        while (std::getline(filename,record)) {
            char delimiter ='|';
            size_t delimiterPos = record.find(delimiter);
            if (delimiterPos !=std::string::npos){ 
                std::string firststName= record.substr(0,delimiterPos);
                std::string secondstName =record.substr(delimiterPos +1);

                Workstation* secondst =nullptr;
                for (Workstation* st : m_activeLine) {
                    if ( st->getItemName() == firststName) {
                        m_firstStation = st;
                    }
                    if ( st->getItemName() == secondstName) {
                        secondst = st;
                    }
                }
                if (m_firstStation && secondst){
                m_firstStation->setNextStation(secondst);
                }
            } 
             else{
                std::string laststName= record ;
                Workstation* lastst = nullptr;
                for (Workstation* st : m_activeLine) {
                    if ( st->getItemName() ==laststName) {
                        lastst= st;
                        break;
                    }
                } 
                if( lastst){
                lastst->setNextStation(nullptr );
                };
            }
        }
       /* for (Workstation* st : m_activeLine ){
            if (!st->getNextStation() ) {
                m_firstStation =st;
                break;
            }
        }*/ //not correct, set last station Bookcase as first :(
    }

   void LineManager::reorderStations() {
        std::vector<Workstation*> reorderedLine;
        for (Workstation* st : m_activeLine){
            bool isStartSt = true;
            for (Workstation* otherStation : m_activeLine) {
                if (otherStation->getNextStation() ==st) {
                    isStartSt = false;
                    break;
                }
            }
            if (isStartSt){
                m_firstStation = st;
                break;
            }
        }
        if (!m_firstStation){
            throw std::runtime_error("Error: Unable to determine the first station to reorder.");
        }
        Workstation* currentStation = m_firstStation;
        while (currentStation){
            reorderedLine.push_back(currentStation) ;
            currentStation =currentStation->getNextStation();
        }

        if (reorderedLine.size()!= m_activeLine.size()) {
            throw std::runtime_error("Error: Unable to reorder all stations.");
        }
        m_activeLine =reorderedLine;
        m_firstStation = m_activeLine.front();
    }

    bool LineManager::run(std::ostream& os){
        static size_t countIter =1;
        os<<"Line Manager Iteration: "<<countIter++ <<std::endl;

        if(!g_pending.empty() ){
            *m_firstStation +=std::move(g_pending.front());
            g_pending.pop_front();
        }
        for(const auto& st :m_activeLine) {
            st->fills(os) ;
        }
        for (auto& st : m_activeLine) {
            st->attemptToMoveOrder();
        }
        size_t totalCompletedAndIncomplete =g_completed.size() + g_incomplete.size();
        return totalCompletedAndIncomplete == m_cntCustomerOrder;

    }

    void LineManager::display(std::ostream& os) const {
        for (const auto* station : m_activeLine )
            station->display(os) ;
    }
}
