#pragma once
#ifndef SENECA_SHOPPINGLIST_H 
#define SENECA_SHOPPINGLIST_H
//#define namespace_name_header_file_name_H


//header file for shopping list functions

namespace seneca 
{
    bool loadList();
    void displayList();
    void removeBoughtItems();
    void removeItem(int index);
    bool saveList();
    void clearList();
    void toggleBought();
    void addItemToList();
    void removeItemfromList();
    bool listIsEmpty();
}

#endif



