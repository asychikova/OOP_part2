#include "SongCollection.h"

namespace seneca {
    // Helper function to trim leading and trailing spaces
    std::string SongCollection::trim(const std::string& str) {
        size_t start = str.find_first_not_of(" ");
        if (start == std::string::npos) {
            return ""; // Empty string if all spaces
        }
        size_t end = str.find_last_not_of(" ");
        return str.substr(start, end - start + 1);
    }

    SongCollection::SongCollection(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("Unable to open file");
    }

    std::string line;
    while (std::getline(file, line)) {
        // Extracting fields from the fixed-width format
        Song song;
        song.title = line.substr(0, 25);
        song.artist = line.substr(25, 25);
        song.album = line.substr(50, 25);

        // Removing leading and trailing spaces from each field
        song.title = trim(song.title);
        song.artist = trim(song.artist);
        song.album = trim(song.album);

        // Parsing year, length, and price after trimming
        std::string year_str = trim(line.substr(75, 5));
        std::string length_str = trim(line.substr(80, 5));
        std::string price_str = trim(line.substr(85, 5));

        // Converting to integers or doubles
        song.year = year_str.empty() ? 0 : std::stoi(year_str);
        song.length = length_str.empty() ? 0 : std::stoi(length_str);
        song.price = price_str.empty() ? 0.0 : std::stod(price_str);

        // Adding the song to the collection
        songs.push_back(song);
    }
    file.close();
}

std::string SongCollection::formatLength(int length) const{
            int minutes = length / 60;
            int seconds = length % 60;
            return std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
        }

    void SongCollection::display(std::ostream& out) const {
        for (const auto& song : songs) {
            out << "| " << std::setw(20) << std::left << song.title
                << " | " << std::setw(15) << std::left<< song.artist
                << " | " << std::setw(20) << std::left<< song.album
                << " | " << std::setw(6) << std::right<< song.year
                << " | "  << formatLength(song.length)
                << " | " << std::fixed << std::setprecision(2) << song.price << " |\n";
        }
    }
}
