/********************************************************
Name       : Khushi Abhay Bhandari
Email      : kabhandari@myseneca.ca
Srudent ID : 106774235
Date       : 05-27-2024


I have done all the coding by myself and only copied the
code that my professor provided to complete my workshops 
and assignments.

********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include<iomanip>
#include "Bill.h"
using namespace std;
namespace seneca {

    //set bill to a safe empty state
    void Bill::setEmpty() 
    {
        
        m_title[0] = '\0';
        m_items = nullptr;
       
      
    }


    bool Bill::isValid() const 
    {

        //check if m_item is empty
         if (m_title[0] == '\0')
        {
            return false;
        }
         //check for m_items if null or not
        if (m_items == nullptr)
        {
            return false;

        }

        //loop through no of items
        for (int i = 0; i < m_noOfItems; i++) 
        {
            if (m_items[i].isValid()==0)
            {
                return false;
            }
        }
        return true;
    }

    double Bill::totalTax() const 
    {
        //using loop add tax
        double totalTax = 0.0;

        for (int i = 0; i < m_noOfItems; i++) 
        {
            totalTax = totalTax + m_items[i].tax();
        }


        return totalTax;
    }

    double Bill::totalPrice() const 
    {
        //using loop add price
        double totalPrice = 0.0;
        for (int i = 0; i < m_noOfItems; i++) 
        {
            totalPrice =totalPrice+ m_items[i].price();
        }
        return totalPrice;
    }

    void Bill::Title() const 
    {
        cout << "+--------------------------------------+" << endl;
       
        if (isValid())
        {
            cout << "| " << left << setw(36) << setfill(' ') << m_title << " |" << endl;
        }

        //if bill is not valid
        else  
        {
            cout << "| Invalid Bill                         |" << endl;
        }
        cout << "+----------------------+---------+-----+" << endl;
        cout << "| Item Name            | Price   + Tax |" << endl;
        cout << "+----------------------+---------+-----+" << endl;
    }

    void Bill::footer() const 
    {
        cout << "+----------------------+---------+-----+" << endl;
        //bill is valid
        if (isValid()) 
        {
            cout << "|                Total Tax: " << right << setw(10) << setfill(' ') << fixed << setprecision(2) << totalTax() << " |" << endl;
            cout << "|              Total Price: " << right << setw(10) << setfill(' ') << fixed << setprecision(2) << totalPrice() << " |" << endl;
            cout << "|          Total After Tax: " << right << setw(10) << setfill(' ') << fixed << setprecision(2) << totalTax() + totalPrice() << " |" << endl;
        }

        //bill is not valid
        else 
        {
            cout << "| Invalid Bill                         |" << endl;
        }
        cout << "+--------------------------------------+" << endl;
    }

    void Bill::init(const char* title, int noOfItems) 
    {
        //title is null then set to safe empyty state
        if (title == nullptr )
        {
            //calling set empty function from above
            setEmpty();
        }

        //if no of items is zero or less than zero
        if (noOfItems<=0)
        {
            setEmpty();


        }
        else 
        {

            //set m_noOfItems to noOfItems
            m_noOfItems = noOfItems;
            //set m_itemsAdded and m_title to zero
            m_title[36] = '\0';
            m_itemsAdded = 0;
           
            //copy c string m_title to title set attribute to 36
            strncpy(m_title, title, 36);

          //  strcpy(m_title, title, 36);
            


            //dymanically allocate memory Item pointed m_items
            //length of Item array[m_noOfItems
            m_items = new Item[m_noOfItems];

            //loop to set memory allocation to empty 
            for (int i = 0; i < m_noOfItems; ++i)
            {
                m_items[i].setEmpty();
            }
        }
    }


    bool Bill::add(const char* item_name, double price, bool taxed) 
    {
        //if m_items added less than no of items 
        if (m_itemsAdded < m_noOfItems) 
        {
            Item i;

            //set arguments 
            i.set(item_name, price, taxed);
            m_items[m_itemsAdded] = i;
            //add 1 to m_items_added
            m_itemsAdded++;
            
            //return
            return true;

            
        }
        return false;
    }

    void Bill::display() const 
    {
        // display title
        Title();

        //loop for displaying items
        for (int i = 0; i < m_noOfItems; ++i) 
        {
            m_items[i].display();
        }

        //display footer
        footer();
    }

    //deallocate memory
    void Bill::deallocate() 
    {
        delete[] m_items;
        m_items = nullptr;
    }

}
