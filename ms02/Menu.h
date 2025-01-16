/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-1-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include<iomanip>

#define MAX_MENU_ITEMS 20



namespace seneca {

    // Forward declaration of Menu class
    class Menu;

    // MenuItem class declaration
    class MenuItem {

        //void setEmpty();
       // MenuItem();
       // bool isEmpty() const;


        //everything is private

        //Cstring of characters
        char* m_content;

        //create constructor and set it to a nullptr
        MenuItem(const char* content = nullptr);

        // destructor
        ~MenuItem();

        // bool type conversion operator
        operator bool() const;

        // constant char conversion operator
        operator const char* () const;

        // display method
        std::ostream& display(std::ostream& os) const;

        //maximum possibility for error in display

        // Menu is a friend class
        friend class Menu;

    };

    // Menu class declaration
    class Menu {
        //title, array of menuitem pointer size-const MAX_MENU_ITEMS,int for tracking
        MenuItem m_title;
        MenuItem* m_items[MAX_MENU_ITEMS];
        unsigned int m_noOfItems;

        std::ostream& display(std::ostream& os = std::cout)const;

    public:
        //contructor for menu items
        Menu(const char* title = "");

        // Destructor
        ~Menu();

        //prevent copy assignment operator use delete
        Menu(const Menu& menu) = delete;
        void operator=(const Menu& menu) = delete;

        //overload operator to add menuItem to menu
        Menu& operator<<(const char* menuitem);

        // Conversion to bool (checks if menu has items
        operator bool()const;

        //function to display menu and get user selection
        unsigned int run() const;
        // Conversion to unsigned int (returns number of items)
        operator unsigned int() const;

        // Conversion to int (returns number of items)
        operator int() const;

        //overload the operator
        unsigned int operator~()const;

        // Indexing operator
        const char* operator[](unsigned int index) const;

        //display function
        std::ostream& displayTitle(std::ostream& os)const;





    };
    // Free function to overload insertion operator for MenuItem
    std::ostream& operator<<(std::ostream& os, const Menu& m);

} // namespace seneca
#endif // MENU_H