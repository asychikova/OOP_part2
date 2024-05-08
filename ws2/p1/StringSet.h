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
    explicit StringSet(const char* fileName);
    StringSet(const StringSet& other);  // Copy constructor
    StringSet& operator=(const StringSet& other);  // Copy assignment
    ~StringSet();
    size_t size() const;
    std::string operator[](size_t index) const;
};


 /*   class StringSet {
    private:
        std::string* strings;
        size_t numStrings;

    public:
        StringSet();
        explicit StringSet(const char* fileName);
        ~StringSet();
        size_t size() const;
        std::string operator[](size_t index) const;
    }; */

    

} // namespace seneca

#endif // SENECA_STRINGSET_H
