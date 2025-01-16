/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-12-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#ifndef STREAMABLE_H
#define STREAMABLE_H

#include <iostream>

class Streamable
{
    //create interface streamable 
public:
    virtual ~Streamable() = 0; // Pure virtual destructor

    virtual std::ostream& write(std::ostream& os) const = 0;
    virtual std::istream& read(std::istream& is) = 0;
    virtual bool conIO(std::ios& io) const = 0;
    virtual operator bool() const = 0;
};

//operator overloading for insertion and extraction
std::ostream& operator<<(std::ostream& os, const Streamable& s);
std::istream& operator>>(std::istream& is, Streamable& s);

#endif // STREAMABLE_H
