/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-12-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#ifndef SENECA_BOOK_H__
#define SENECA_BOOK_H__
#include <iostream>
#include "Publication.h"

namespace seneca 
{
	//inherits from publication
	class Book : public Publication
	{

		char* m_author;

	public:

		//rule of three
		Book();
		Book(const Book& b);
		Book& operator=(const Book& b);
		~Book();

		//methods
		char type() const;
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& istr);
		void set(int member_id);
		operator bool() const;
	};
}
#endif
