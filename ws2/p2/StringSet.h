/*
*****************************************************************************
                          OOP345 Workshop - #2 (P2)
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
*****************************************************************************
*/

#ifndef SENECA_STRINGSET_H
#define SENECA_STRINGSET_H
#include <string>

namespace seneca {
    class StringSet {
    private:
        std::string* strings;
        size_t numStrings;
    public:
        StringSet();
        explicit StringSet(const char* fileName );
         ~StringSet();
        size_t size() const ;
        std::string operator[](size_t index) const;
        void copyFrom(const StringSet& other); 
        StringSet( const StringSet& other);  
         StringSet& operator=( const StringSet& other); 
        void moveFrom(StringSet&& other);    
        StringSet(StringSet&& other );
        StringSet& operator=(StringSet&& other);
         
    };
}
#endif
