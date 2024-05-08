/*
*****************************************************************************
                          OOP345 Workshop - #5 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/


#include "Movie.h"
#include <sstream>
#include <iomanip>
namespace seneca {

    Movie::Movie() :year_m(0){}

    const std::string& Movie::title()const {
        return title_m;
    }

    Movie::Movie(const std::string& strMovie) :year_m(0){
        size_t pos =strMovie.find(',');

        title_m= strMovie.substr(0,pos);
        size_t start =0;
        while (start <title_m.length() &&(title_m[start] ==' ' ||title_m[start]=='\t')) {
            start++;
        }
        title_m.erase(0, start);
        size_t end =title_m.length();
        while (end >0 &&(title_m[end- 1] ==' ' ||title_m[end- 1]== '\t')) {
            end--;
        }
        title_m.erase(end);

        size_t nextPos= strMovie.find(',',pos + 1);
        year_m =std::stoi(strMovie.substr(pos +1, nextPos -pos-1));

        description_m=strMovie.substr(nextPos+ 1);
        start = 0;
        while (start <description_m.length()&& (description_m[start]==' ' ||description_m[start] =='\t')) {
            start++;
        }
        description_m.erase(0,start);
        end =description_m.length();
        while(end >0 &&(description_m[end -1] ==' ' ||description_m[end -1] =='\t')) {
            end--;
        }
        description_m.erase(end) ;
    }

    std::ostream& operator<<(std::ostream& os, const Movie& movie) {
        os<< std::setw(40)<<movie.title()<<" | "<<std::setw(4)<< movie.year_m <<" | "<<movie.description_m <<'\n';
        return os;
    }

} 
