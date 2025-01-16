/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-1-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#include "Menu.h"

#include <iostream>
#include <cstring>
#include <limits>
#include <iomanip>  

using namespace std;


namespace seneca {

    // MenuItem implementation


    MenuItem::MenuItem(const char* content)
    {
        if (content)
        {
            //allocate content to a cstring value
            m_content = new char[strlen(content) + 1];
            //set calue to argument
            std::strcpy(m_content, content);
        }

        else
        {
            //set to safe empty state
            //setEmpty();
            m_content = nullptr;
        }
    }

    //destructor
    MenuItem::~MenuItem() {
        delete[] m_content;
    }

    //bool type conversion
    MenuItem::operator bool() const
    {
        //returns true if it is not empty or else false
        return !(m_content == nullptr || m_content[0] == '\0');
    }


    MenuItem::operator const char* () const
    {
        //returns address x
        return m_content;
    }

    //display function
    std::ostream& MenuItem::display(std::ostream& os) const
    {
        //display content of menuitem
        if (!(m_content == nullptr || m_content[0] == '\0'))
        {
            os << m_content;
        }
        return os;
    }


    //Menu class

    //constructor
    Menu::Menu(const char* title) : m_title(title), m_noOfItems(0)
    {
        for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++)
        {
            m_items[i] = nullptr;
        }
    }

    //destructor
    Menu::~Menu()
    {
        //loop through menuitems array of pointers
        for (unsigned int i = 0; i < m_noOfItems; i++)
        {
            //delete each pointer up to the number of menu items 
            delete m_items[i];
        }
    }

    // display function for title
    std::ostream& Menu::displayTitle(std::ostream& os) const
    {
        m_title.display(os);
        return os;
    }

    //display
    std::ostream& Menu::display(std::ostream& os) const
    {
        //display title if it is not empty then ": newline"
        displayTitle(os);
        if (m_title) os << "\n";

        //display menu items one by one 
        //use for-loop loop through all menu items
        for (unsigned int i = 0; i < m_noOfItems; i++) {
            os << std::setfill(' ') << std::setw(2) << i + 1 << "- ";
            m_items[i]->display(os) << "\n";
        }
        os << " 0- Exit\n";
        os << "> ";

        return os;
    }

    //receives nothing and return unsigned int
    unsigned int Menu::run() const
    {
        // Display menu and get user selection
        display();

        int selection;
        bool validInput = false;
        do {
            cin >> selection;
            // Value must be >= 0 and <= number of items
            if (std::cin.fail() || selection < 0 || selection > int(m_noOfItems)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid Selection, try again: ";
            }
            else {
                validInput = true;
            }
        } while (!validInput);

        return selection;
    }

    unsigned int Menu::operator~() const
    {
        // Display menu and get user selection
        display();

        int selection;
        bool validInput = false;
        do {
            cin >> selection;
            // Value must be >= 0 and <= number of items
            if (std::cin.fail() || selection < 0 || selection > int(m_noOfItems)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid Selection, try again: ";
            }
            else {
                validInput = true;
            }
        } while (!validInput);

        return selection;
    }

    Menu& Menu::operator<<(const char* menuitem)
    {
        //if there is space in array 
        if (m_noOfItems != MAX_MENU_ITEMS)
        {
            //dynamically create menu item

            m_items[m_noOfItems] = new MenuItem(menuitem);
            //increase value of pointer by 1
            m_noOfItems++;
        }

        //return reference of the menu object
        return *this;
    }

    Menu::operator unsigned int() const
    {
        //return number if menu items
        return m_noOfItems;
    }
    Menu::operator bool() const
    {
        //return true if menu has one or mire menu items in menu
        return m_noOfItems > 0;
    }



    Menu::operator int() const
    {
        //return no of items from menu
        return m_noOfItems;
    }


    //overlaod operator
    std::ostream& operator<<(std::ostream& os, const Menu& m)
    {
        return m.displayTitle(os);
    }

    //overload indexing operator
    const char* Menu::operator[](unsigned int index) const
    {
        if (index < m_noOfItems)
        {
            return m_items[index]->m_content;
        }
        return m_items[index % m_noOfItems]->m_content;
    }

} // namespace seneca
