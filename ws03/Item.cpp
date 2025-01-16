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
#include <iomanip>
#include "Item.h"
using namespace std;
namespace seneca 
{

    const double taxRate = 0.13;


    void Item::setName(const char* name) 
    {

        
        int i;
        //create a cstring variable name
        //set itemname to name cstring
        for (i = 0; i < 20 && name[i] != '\0'; i++)
        {
            m_itemName[i] = name[i];

        }
        m_itemName[i] = '\0';
    }

    void Item::setEmpty() 
    {

        //setting blank string to null
        m_itemName[0] = '\0';
        //setting price to an impossible value
        m_price = 0.0;

      
    }

    void Item::set(const char* name, double price, bool taxed) 
    {

        //if price is less than 0 or name is null 
        //set to safe empty state (can call function from above)
        if (price < 0 || name == nullptr)
        {
            m_itemName[0] = '\0';
            m_price = 0.0;
            


        }
        else
        {
            //set m_itemName attribute(name)

            setName(name);
            //set m_price to price and m_taxed to taxed
            m_price = price;
            m_taxed = taxed;
        }

    }

    double Item::price() const
    {
    
       
        //returns m_price
        return m_price;
    }


    double Item::tax() const
    {

        double taxAmount = 0.0;

        if (m_taxed)
        {
            //if m_taxed true
            //return price*taxrate
            taxAmount = m_price * taxRate;
        }
        else
        {
            //if false return 0.0
            taxAmount = 0.0;
        }
        return taxAmount;


       
    }


    bool Item::isValid() const
    {
        //if valid is true return and do not set to safe empty state 
        return m_itemName[0] != '\0';
       
       
    }


    void Item::display() const 
    {
        //if valid
        if (isValid())
        {
            cout << "| " << left << setw(20) << setfill('.') << m_itemName
                << " | " << right << setw(7) << setfill(' ') << fixed << setprecision(2) << m_price
                << " | ";
            if (m_taxed)
            {
                cout << "Yes |";
            }
            else
            {
                cout << "No  |";
            }
            cout << endl;
        }

        //if not valid
        else 
        {
            cout << "| xxxxxxxxxxxxxxxxxxxx | xxxxxxx | xxx |" << endl;
        }
    }
}