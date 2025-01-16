/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-19-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#include "Line.h"
#include <iostream>
#include <iomanip>

namespace seneca {


	Line::Line()
	{
		//sets m_length to 0
		m_length = 0;
	}

	//two argument variable
	Line::Line(const char* label, int length) :LblShape(label)
	{
		//receives c string value for length
		//set default value to argument
		if (length > 0) 
		{
			m_length = length;
		}
		else
		{
			m_length = 0;
		}
	}

	void Line::getSpecs(istream& istr)
	{
		//calls base class function
		LblShape::getSpecs(istr);
		istr >> m_length;
		istr.ignore(1000, '\n');
	}
	void Line::draw(ostream& ostr) const
	{
		
		if (label() != nullptr)
		{
			if (m_length > 0)
			{
				//print label \n 
				ostr << label() << endl;
				//==
				ostr.fill('=');
				ostr.width(m_length);
				ostr << '=';
			}
		}
	}

}
