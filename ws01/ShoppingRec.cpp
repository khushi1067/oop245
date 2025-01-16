#include <iostream>
#include "ShoppingRec.h"
#include "Utils.h"

//constants values 
//values are already defined in ShoppingRec.h 

//const int MAX_TITLE_LENGTH = 50;
//const int MAX_QUANTITY_VALUE = 50;



//shopping record functions defination

namespace seneca {

    ShoppingRec getShoppingRec() {
        ShoppingRec R = {};
        std::cout << "Item name: ";
        readCstr(R.m_title, MAX_TITLE_LENGTH);
        std::cout << "Quantity: ";
        R.m_quantity = readInt(1, MAX_QUANTITY_VALUE);
        return R;
    }

    void displayShoppingRec(const ShoppingRec* shp) {
        std::cout << "[" << (shp->m_bought ? 'X' : ' ') << "]" << shp->m_title <<
            " qty:(" << shp->m_quantity << ")" << std::endl;
    }

    void toggleBoughtFlag(ShoppingRec* rec) {
        rec->m_bought = !rec->m_bought;
    }

    bool isShoppingRecEmpty(const ShoppingRec* shp) {
        return shp->m_title[0] == 0;
    }
}


