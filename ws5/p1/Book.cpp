#include "Book.h"
#include <sstream>
#include <iomanip>

namespace seneca {

    Book::Book() : year_(0), price_(0) {}

    const std::string& Book::title() const {
        return title_;
    }

    const std::string& Book::country() const {
        return country_;
    }

    const size_t& Book::year() const {
        return year_;
    }

    double& Book::price() {
        return price_;
    }


Book::Book(const std::string& strBook) : year_(0), price_(0) {
    // Function to remove leading spaces
    auto removeLeadingSpaces = [](std::string& str) {
        size_t startPos = str.find_first_not_of(" \t");
        if (startPos != std::string::npos)
            str.erase(0, startPos);
    };

    // Function to remove trailing spaces
    auto removeTrailingSpaces = [](std::string& str) {
        size_t endPos = str.find_last_not_of(" \t");
        if (endPos != std::string::npos)
            str.erase(endPos + 1);
    };

    // Find the position of each delimiter ','
    size_t pos = strBook.find(',');
    author_ = strBook.substr(0, pos);
    removeLeadingSpaces(author_);

    size_t nextPos = strBook.find(',', pos + 1);
    title_ = strBook.substr(pos + 1, nextPos - pos - 1);
    removeLeadingSpaces(title_);
    removeTrailingSpaces(title_);

    pos = nextPos;
    nextPos = strBook.find(',', pos + 1);
    country_ = strBook.substr(pos + 1, nextPos - pos - 1);
    removeLeadingSpaces(country_);

    pos = nextPos;
    nextPos = strBook.find(',', pos + 1);
    std::string priceStr = strBook.substr(pos + 1, nextPos - pos - 1);
    removeLeadingSpaces(priceStr);
    price_ = std::stod(priceStr);

    pos = nextPos;
    nextPos = strBook.find(',', pos + 1);
    std::string yearStr = strBook.substr(pos + 1, nextPos - pos - 1);
    removeLeadingSpaces(yearStr);
    year_ = std::stoi(yearStr);

    pos = nextPos;
    description_ = strBook.substr(pos + 1);
    removeLeadingSpaces(description_);
}



std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << std::setw(20) << book.author_ << " | "
        << std::setw(22) << book.title_ << " | "
        << std::setw(5) << book.country_ << " | "
        << std::setw(4) << book.year_ << " | "
        << std::fixed << std::setprecision(2) << std::setw(6) << book.price_ << " | "
        << book.description_;
    return os;
}



}
