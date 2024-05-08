#ifndef SDDS_TOY_H
#define SDDS_TOY_H

#include <iostream>
#include <string>

namespace seneca {

    class Toy {
        int m_orderId;
        std::string m_name;
        int m_numItems;
        double m_price;
        double m_hst;

        // Private member function to calculate tax
        double calculateTax() const;

    public:
        Toy();
        void update(int numItems);
        Toy(const std::string& toy);
        friend std::ostream& operator<<(std::ostream& os, const Toy& toy);
    };

}
#endif // SDDS_TOY_H
