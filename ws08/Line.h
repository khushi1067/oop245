/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-10-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#ifndef LINE_H
#define LINE_H

using namespace std;
#include "LblShape.h"

namespace seneca
{
	//inhertis form lblshape
	class Line :public LblShape
	{
		//variable to hold length of line
		int m_length;

	public:
		//constructor no argument
		Line();

		//two argument constructor
		Line(const char* label, int length);
		
		
		void getSpecs(istream& istr);


		void draw(ostream& ostr) const;
	};
}

#endif
