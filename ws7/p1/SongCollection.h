#ifndef SONGCOLLECTION_H
#define SONGCOLLECTION_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

namespace seneca {

        struct Song {
        std::string title;
        std::string artist;
        std::string album;
        int year;
        int length;
        double price;
    };

    class SongCollection {
        std::vector<Song> songs;

    public:
        SongCollection(const std::string& filename);
 std::string trim(const std::string& str);
        void display(std::ostream& out) const;
               std::string formatLength(int length) const;
    };
}

#endif // SONGCOLLECTION_H
