#include "Toy.h"
#include <iomanip>
#include <sstream>

namespace seneca {

    Toy::Toy() : m_orderId(0), m_name(""), m_numItems(0), m_price(0.0), m_hst(0.13) {}

    void Toy::update(int numItems) {
        m_numItems = numItems;
    }

    Toy::Toy(const std::string& toy) {
        // Extract information from the string
        std::istringstream iss(toy);
        char delimiter;
        iss >> m_orderId >> delimiter;
        std::getline(iss, m_name, ':');
        iss >> m_numItems >> delimiter;
        iss >> m_price;
        // Remove leading and trailing spaces from the name
        m_name.erase(0, m_name.find_first_not_of(' '));
        m_name.erase(m_name.find_last_not_of(' ') + 1);
    }

    double Toy::calculateTax() const {
        return m_numItems * m_price * 0.13;
    }

    std::ostream& operator<<(std::ostream& os, const Toy& toy) {
        double subtotal = toy.m_numItems * toy.m_price;
        double tax = toy.calculateTax();
        double total = subtotal + tax;

        os << "Toy " << toy.m_orderId << ": " << std::setw(8) << std::left << toy.m_name
            << std::setw(3) << toy.m_numItems << " items   "
            << std::fixed << std::setprecision(2) << std::setw(8) << toy.m_price << "/item  "
            << "subtotal: " << std::setw(7) << subtotal << " tax: " << std::setw(6) << tax << " total: " << std::setw(7) << total << '\n';

        return os;
    }

}
