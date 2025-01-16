/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-12-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#ifndef SENECA_PUBLICATION_H
#define SENECA_PUBLICATION_H

#include <iostream>
#include "Lib.h"
#include "Date.h"
#include "Streamable.h"

namespace seneca 
{
	class Publication :public Streamable 
	{
		char* m_title;
		char m_shelfId[SENECA_SHELF_ID_LEN + 1];
		int m_membership;
		int m_libRef;
		Date m_date;

		//set all the attribute to default values
		void setDefault();

	public:

		//rule of three
		Publication();
		Publication(const Publication& pub);
		Publication& operator=(const Publication& pub);
		~Publication();


		//Methods
		virtual void set(int member_id);
		// Sets the membership attribute to either zero or a five-digit integer.
		void setRef(int value);
		// Sets the **libRef** attribute value
		void resetDate();
		// Sets the date to the current date of the system.

		//Queries

		virtual char type()const;
		//Returns the character 'P' to identify this object as a "Publication object"
		bool onLoan()const;
		//Returns true is the publication is checkout (membership is non-zero)
		Date checkoutDate()const;
		//Returns the date attribute
		bool operator==(const char* title)const;
		//Returns true if the argument title appears anywhere in the title of the 
		//publication. Otherwise, it returns false; (use strstr() function in <cstring>)
		operator const char* ()const;
		//Returns the title attribute
		int getRef()const;
		//Returns the libRef attirbute. 

 

		bool conIO(std::ios& io)const;

		//write function
		std::ostream& write(std::ostream& os) const;
		
		//read function
		std::istream& read(std::istream& istr);
		
		operator bool() const;

	};
}
#endif // !SDDS_PUBLICATION_H
