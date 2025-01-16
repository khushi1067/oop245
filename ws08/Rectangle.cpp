/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-10-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/

#include "Rectangle.h"
#include "Line.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "LblShape.h"

using namespace std;

namespace seneca 
{

	Rectangle::Rectangle() : LblShape() 
    {
		// Initialize variables to 0
		m_width = 0;
		m_height = 0;
	}


    Rectangle::Rectangle(const char* label, int width, int height) 
        : LblShape(label), m_width(width), m_height(height) 
    
    {
       //if m_height <3 or m_width<length of label+2
        if (m_height < 3 || m_width < ((int)(strlen(label)) + 2))
        {
            //set rectangle to empty state 
            //make height and width 0
            m_width = 0;
            m_height = 0;
        }
    }

    void Rectangle::draw(std::ostream& os) const
    {
        //if width >0 and height >0
        if (m_width>0)
        {
            if (m_height > 0)
            {
                //+ \n
                os << '+';
                //- \n
                os << std::setw(m_width - 2) << std::setfill('-') << '-' << '+' << std::endl;

                // | m_width-2 label \n
                os << '|' << std::setw(m_width - 2) << std::setfill(' ') << std::left << label() << '|' << std::endl;

                for (int i = 0; i < m_height - 3; ++i)
                {
                    os << '|' << std::setw(m_width - 2) << ' ' << '|' << std::endl;
                }

                os << '+' << std::setw(m_width - 2) << std::setfill('-') << '-' << '+';
        
            }


        }
    }

    void Rectangle::getSpecs(std::istream& is) 
    {
        //reads data upto , 
        LblShape::getSpecs(is);
        is >> m_width;

        is.ignore();
        
        is >> m_height;
        is.ignore(1000, '\n');
    }
}
