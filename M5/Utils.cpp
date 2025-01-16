/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-12-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/


#include "Utils.h"
#include <iostream>
using namespace std;
namespace seneca {

    //utility function to read
    //used in menu and LibApp
    void read(int& i, int min, int max, const char* error)
    {
        //initialize flag to false
        bool valid = false;       

        //stores \n char
        char newline;             

        do
        {
            //read input
            cin >> i;   

            //gets newline character
            newline = cin.get();    
            
            //if fail to catch
            if (cin.fail() || newline != '\n')
            {
                //set flag to false
                valid = false;     
                
                //claear input string
                cin.clear();         
                
                //ignore until newline characters  
                cin.ignore(1000, '\n');   
            }
            else
            {

                if (i <= max)
                {
                    if (i >= min)
                    {
                        //set falg to true
                        valid = true;

                    }
                }
                //if (i <= max && i >= min) 
                //    valid = true;         
            }
        } while (!valid && cout << error); 
    }

}