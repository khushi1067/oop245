/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-10-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#ifndef LBLSHAPE_H
#define LBLSHAPE_H
#include <iostream>
#include "Shape.h"

using namespace std;

namespace seneca 
{
	//inhertis from shape
	class LblShape :public Shape
	{
		//chat c string
		char* m_label = nullptr;

		//char* m_label{ nullptr };
	protected:

		char* label()const;

	public:
		//constructor with no arguments
		LblShape() {};
		
		//one argument constructor
		LblShape(const char* label);

		//destructor
		~LblShape();

		//copy constructor but prevent copy by using delete
		LblShape(const LblShape& lblShpae) = delete;
		LblShape& operator=(const LblShape& lblshape) = delete;


		void getSpecs(istream& istr);
	};
}

#endif
