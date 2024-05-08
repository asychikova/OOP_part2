/*
*****************************************************************************
                          OOP345 Workshop - #5 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#include "Book.h"
#include <sstream>
#include <iomanip>

namespace seneca {

    Book::Book() :year_m(0),price_m(0){}

    const std::string& Book::title()const {
        return title_m; }

    const std::string& Book::country()const {
        return country_m ;}

    const size_t& Book::year()const {
        return year_m;
    }

    double& Book::price() {
        return price_m;
    }

    Book::Book(const std::string& strBook) : year_m(0),price_m(0){
        size_t pos = strBook.find(',');
        author_m =strBook.substr(0,pos);

        size_t start = 0;

        size_t nextPos =strBook.find(',',pos + 1);
        title_m= strBook.substr(pos +1,nextPos -pos-1);
        start = 0;
        while(start<title_m.length()&& (title_m[start]== ' '||title_m[start]=='\t')) {
            start++;
        }
        title_m.erase(0, start);
        size_t end = title_m.length();
        while (end>0 &&(title_m[end -1] ==' '||title_m[end -1] =='\t')) {
            end--;
        }
        title_m.erase(end);

        pos = nextPos;
        nextPos =strBook.find(',',pos+ 1);
        country_m= strBook.substr(pos +1,nextPos -pos- 1);
        start = 0;
        while (start <country_m.length()&&(country_m[start] ==' ' ||country_m[start]== '\t')) {
            start++;
        }
        country_m.erase(0, start);

        pos = nextPos;
        nextPos =strBook.find(',',pos +1);
        std::string priceStr =strBook.substr(pos+ 1,nextPos -pos-1);

        start = 0;
        while(start <priceStr.length()&& (priceStr[start] ==' '||priceStr[start]== '\t')) {
            start++;
        }
        priceStr.erase(0,start);
        price_m = std::stod(priceStr);

        pos = nextPos;
        nextPos =strBook.find(',',pos +1);
        std::string yearStr= strBook.substr(pos +1,nextPos - pos-1);
        start = 0;
        while(start<yearStr.length()&& (yearStr[start]== ' '||yearStr[start] =='\t')) {
            start++;
        }
        yearStr.erase(0, start);
        year_m= std::stoi(yearStr);

        pos =nextPos;
        description_m =strBook.substr(pos+ 1);
        start =0;
        while (start< description_m.length()&&(description_m[start] ==' ' ||description_m[start]== '\t')) {
            start++;
        }
        description_m.erase(0,start);
    }


    std::ostream& operator<<(std::ostream& os, const Book& book) {
        os<<std::setw(20)<< book.author_m <<" | "<<std::setw(22) <<book.title_m <<" | "<<std::setw(5)<< book.country_m<< " | "
            <<std::setw(4)<< book.year_m<< " | "<< std::fixed<<std::setprecision(2)<< std::setw(6)<<book.price_m << " | "<<book.description_m <<'\n';
        return os;
    }

}
