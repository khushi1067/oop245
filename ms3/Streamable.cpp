/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-12-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#include "Streamable.h"
Streamable::~Streamable() 
{

}

//extraction operator overload
    std::ostream& operator<<(std::ostream& os, const Streamable& s)
    {
        if (s) 
        {
            s.write(os);
        }
        return os;
    }

    //insertion operator overload
    std::istream& operator>>(std::istream& is, Streamable& s) 
    {
        return s.read(is);
    }

