#ifndef SENECA_SHOPPINGREC_H
#define SENECA_SHOPPINGREC_H
//#define namespace_name_header_file_name_H

// header file for shopping record functions


namespace seneca 
{
    //constant values
    const int MAX_TITLE_LENGTH = 50;
    const int MAX_QUANTITY_VALUE = 50;

    //shopping record structure
    struct ShoppingRec 
    {
        char m_title[MAX_TITLE_LENGTH + 1];
        int m_quantity;
        bool m_bought;
    };

    ShoppingRec getShoppingRec();
    void displayShoppingRec(const ShoppingRec* shp);
    void toggleBoughtFlag(ShoppingRec* rec);
    bool isShoppingRecEmpty(const ShoppingRec* shp);
}

#endif
