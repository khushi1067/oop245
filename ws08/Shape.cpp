/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-10-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#include "Shape.h"

namespace seneca
{
	//extraction operator
	ostream& operator<<(ostream& ostr, const Shape& shape)
	{
		shape.draw(ostr);
		return ostr;
	}

	//insertion operator by overloading >>
	istream& operator>>(istream& istr, Shape& shape)
	{
		shape.getSpecs(istr);
		return istr;
	}
}
