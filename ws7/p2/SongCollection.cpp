/*
*****************************************************************************
                          OOP345 Workshop - #7 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include "SongCollection.h"

namespace seneca {

    SongCollection::SongCollection(const std::string& filename) {
        std::ifstream file(filename);
        if(!file.is_open()) {
            throw std::invalid_argument("Can't open the file");
        }
        std::string line;
        while (std::getline(file,line)){
            Song song;
            song.title =line.substr(0,25);
            song.artist= line.substr(25, 25);
            song.album= line.substr(50,25);

            song.title =trim(song.title);
            song.artist =trim(song.artist);
            song.album =trim(song.album);

            std::string year_str= trim(line.substr(75,5));
            std::string length_str= trim(line.substr(80,5));
            std::string price_str =trim(line.substr(85, 5));

            song.year =year_str.empty()? 0 : std::stoi(year_str);
            song.length=  std::stoi(length_str);
            song.m_price= std::stod(price_str);

            songs.push_back(song);
        }
        file.close() ;
    }

    std::string SongCollection::trim(const std::string& str) {
        size_t start =0;
        while(start< str.length()&& std::isspace(str[start]) ) {
            start++; }
        size_t end =str.length()- 1;
        while (end >start&& std::isspace(str[end]) ) {
            end-- ;
        }
        return str.substr(start,end -start +1);
    }

    std::string SongCollection::formatLength(int length)const {
        int minutes= length/60;
        int seconds =length%60;
        return std::to_string(minutes)+":" +(seconds< 10?"0" : "") +std::to_string(seconds);
    }

    void SongCollection::display(std::ostream& out) const {
        for(const auto& song : songs) {
            std::string year_display =(song.year== 0) ?" " : std::to_string(song.year);
        
            out<< "| "<< std::setw(20)<<std::left<<song.title<< " | "<<std::setw(15)<<std::left<< song.artist
            << " | "<<std::setw(20)<<std::left <<song.album<< " | "<<std::setw(6) <<std::right <<year_display
            <<" | "<<formatLength(song.length)<<" | " <<std::fixed <<std::setprecision(2) << song.m_price <<" |\n";
        }
       int totalSeconds = totalPlayTime();
    std::string formattedTotalTime =formatTotalPlayTime(totalSeconds);
    out << "----------------------------------------------------------------------------------------\n"
        << "| "<<std::setw(87) <<std::right<< "Total Listening Time: "+ formattedTotalTime+" |\n";
    }

    bool SongCollection::compareByTitle(const Song& a,const Song& b) {
        return a.title <b.title;
    }

    bool SongCollection::compareByAlbum(const Song& a,const Song& b) {
        return a.album <b.album;
    }

    bool SongCollection::compareByLength(const Song& a,const Song& b) {
        return a.length <b.length;
    }

    void SongCollection::sort(const std::string& field){
        if (field =="title") {
            std::sort(songs.begin(), songs.end(),compareByTitle);
        }else if (field== "album") {
            std::sort(songs.begin(), songs.end(),compareByAlbum);
        } else if (field== "length") {
            std::sort(songs.begin(), songs.end(),compareByLength);
        }
    }


    void SongCollection::cleanAlbum() {
        std::for_each(songs.begin(),songs.end(),[](Song& song) {
            if (song.album =="[None]") {
                song.album ="";
            }
        });
        /*for(auto& song : songs) {
            if (song.album =="[None]") {
                song.album ="";
            }
        }*/
    }

    bool SongCollection::inCollection(const std::string& artist) const {
        return std::any_of( songs.begin(),songs.end(), [&artist](const Song& song){
            return song.artist== artist;
        /*for (const auto& song : songs) {
            if(song.artist== artist) {
                return true;
            }
        }
        return false;
        }*/
        });
    }

    std::list<Song> SongCollection::getSongsForArtist(const std::string& artist) const { 
        std::list<Song> artistSongs;
        std::copy_if(songs.begin(),songs.end(),std::back_inserter(artistSongs),[&artist](const Song& song) {
        return song.artist ==artist;
        });
        return artistSongs;
        /* for (const auto& song : songs ) {
            if (song.artist== artist) {
                artistSongs.push_back(song) ;
            }
        }
        return artistSongs; */
    }

    int SongCollection::totalPlayTime() const { 
        int totalTime =0;
        for (const auto& song : songs) {
            totalTime+= song.length;
        }
        return totalTime;
    }

    std::string SongCollection::formatTotalPlayTime(int totalSeconds) const {
        int hours= totalSeconds/3600;
        int minutes =(totalSeconds %3600) /60;
        int seconds = totalSeconds%60;
        return std::to_string(hours)+":"+(minutes <10 ? "0":"") +std::to_string(minutes) +":"+(seconds <10 ? "0":"") + std::to_string(seconds);
    }

    std::ostream& operator<<(std::ostream& out, const Song& song) {
        int minutes= song.length/60;
        int seconds= song.length%60;
        out << "| "<< std::setw(20)<<std::left<<song.title<< " | "<<std::setw(15)<<std::left<< song.artist
            << " | "<<std::setw(20)<<std::left <<song.album<< " | "<<std::setw(6) <<std::right <<song.year
            <<" | "<<minutes<<":"<<seconds<< " | "<<std::fixed <<std::setprecision(2)<< song.m_price <<" |";
        return out;
    }

}
