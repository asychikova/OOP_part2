#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

namespace seneca {

    class Book {
    private:
        std::string author_;
        std::string title_;
        std::string country_;
        size_t year_;
        double price_;
        std::string description_;

    public:
        Book();
        const std::string& title() const;
        const std::string& country() const;
        const size_t& year() const;
        double& price();
        Book(const std::string& strBook);

        friend std::ostream& operator<<(std::ostream& os, const Book& book);
    };

}

#endif // BOOK_H
