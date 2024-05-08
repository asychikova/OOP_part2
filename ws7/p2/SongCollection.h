/*
*****************************************************************************
                          OOP345 Workshop - #7 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#ifndef SENECA_SONGCOLLECTION_H
#define SENECA_SONGCOLLECTION_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

namespace seneca {

    struct Song {
        std::string title;
        std::string artist ;
        std::string album;
        int year ;
        int length;
        double m_price;
    };

    std::ostream& operator<<(std::ostream& out, const Song& song);

    class SongCollection {
        std::vector<Song> songs;
    public:
        SongCollection(const std::string& filename);
        void display(std::ostream& out) const ;

        static bool compareByTitle(const Song& a,const Song& b);
        static bool compareByAlbum(const Song& a,const Song& b) ;
        static bool compareByLength(const Song& a, const Song& b);
        void sort(const std::string& field);

        void cleanAlbum();
        bool inCollection(const std::string& artist) const;
        std::list<Song> getSongsForArtist(const std::string& artist) const;
        
        std::string trim(const std::string& str);
        std::string formatLength(int length) const ;
        int totalPlayTime() const;
        std::string formatTotalPlayTime(int totalSeconds) const;
    
    };

}

#endif 
