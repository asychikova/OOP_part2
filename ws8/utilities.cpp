#include <memory>
#include "list.h"
#include "element.h"
#include "utilities.h"

using namespace std;

namespace seneca {
List<Product> mergeRaw(const List<Description>& desc, const List<Price>& price) {
    List<Product> priceList;

    // Iterate through descriptions
    for (size_t i = 0; i < desc.size(); ++i) {
        // Search for matching price
        bool found = false;
        double foundPrice = 0.0;
        for (size_t j = 0; j < price.size(); ++j) {
            if (desc[i].code == price[j].code) {
                found = true;
                foundPrice = price[j].price;
                break;
            }
        }

        // Create Product object and add to the list
        Product* prod = new Product(desc[i].desc, found ? foundPrice : 0.0);
        try {
            prod->validate(); // Validate the product
            priceList += prod; // Add the product to the list
        } catch (const std::string& msg) {
            delete prod; // Delete the product if validation fails
            throw msg; // Throw the error message
        }
    }

    return priceList; // Return the list of products
}

}