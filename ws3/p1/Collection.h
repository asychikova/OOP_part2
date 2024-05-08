#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include <iomanip>
#include "Pair.h"

namespace seneca {
    template <typename T, unsigned int CAPACITY>
    class Collection {
        T m_dummy{};
        T m_data[CAPACITY]{};
        int m_size{};

    public:
        int size() const {
            return m_size;
        }

        void display(std::ostream& os = std::cout) const {
            os << "----------------------\n| Collection Content |\n----------------------\n";
            for (int i = 0; i < m_size; ++i) {
                os << m_data[i] << '\n';  
            }
            os << "----------------------\n";
        }

        bool add(const T& item) {
            if (m_size < CAPACITY) {
                m_data[m_size++] = item;
                return true;
            }
            return false;
        }

        T operator[](int index) const {
            if (index >= 0 && index < m_size) {
                return m_data[index];
            }
            return m_dummy;
        };
    };

    template <>
    class Collection<Pair, 100> {
        Pair m_dummy{ "No Key", "No Value" };
        Pair m_data[100]{};
        int m_size{};

    public:
        int size() const {
            return m_size;
        }

        void display(std::ostream& os = std::cout) const {
            os << "----------------------\n| Collection Content |\n----------------------\n";
            for (int i = 0; i < m_size; ++i) {
                os << m_data[i] << '\n';
            }
            os << "----------------------\n";
        }

        bool add(const Pair& item) {
            if (m_size < 100) {
                m_data[m_size++] = item;
                return true;
            }
            return false;
        }

        Pair operator[](int index) const {
            if (index >= 0 && index < m_size) {
                return m_data[index];
            }
            return m_dummy;
        }
    };
} 

#endif
