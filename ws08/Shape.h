/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-10-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>

using namespace std;
namespace seneca 
{
	class Shape
	{
	
	public:
		//pure virtual function const
		virtual void draw(ostream& ostr) const = 0;


		virtual void getSpecs(istream& istr) = 0;
		//default virtual destructor
		virtual ~Shape() = default;
		
	};

	//helper function insertion and extraction
	ostream& operator<<(ostream& ostr, const Shape& shape);
	istream& operator>>(istream& istr, Shape& shape);
}

#endif

