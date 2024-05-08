#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <string>

namespace seneca {
    class Pair {
        std::string m_key{};
        std::string m_value{};

    public:
        const std::string& getKey() const;
        const std::string& getValue() const;

        Pair();
        Pair(const std::string& key, const std::string& value);

        bool operator==(const Pair& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Pair& pair);
    };
}

#endif
