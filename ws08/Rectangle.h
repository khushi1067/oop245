/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-10-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#ifndef RECTANGLE_H
#define RECTANGLE_H

using namespace std;
#include "LblShape.h"

namespace seneca 
{
    //inherits from lbl shape
    class Rectangle : public LblShape 
    {
        //data members holds width and height of the rectangle
        int m_width;
        int m_height;

    public:
        //default 
        Rectangle();

        //3 arguments constructor
        Rectangle(const char* label, int width, int height);
        
        
        void draw(std::ostream& os) const override;
        
        void getSpecs(std::istream& is) override;
    };
}

#endif
