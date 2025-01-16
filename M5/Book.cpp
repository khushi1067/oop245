/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-12-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstring>
#include <string>
#include "Book.h"

using namespace std;
namespace seneca
{
	//rule of three
	Book::Book()
	{
		//set to nullptr (default values)
		m_author = nullptr;
	}

	//book inherits from publication
	Book::Book(const Book& b) :Publication(b)
	{
		//if arhument author name is not nullptr
		if (b.m_author != nullptr)
		{
			//allocate memory dynamically
			m_author = new char[strlen(b.m_author) + 1];

			//copy name to argument 
			strcpy(m_author, b.m_author);
		}

		else
		{
			//set author to null
			m_author = nullptr;
		}
	}

	//copy constructor
	Book& Book::operator=(const Book& b)
	{
		if (this != &b)
		{
			Publication::operator =(b);
			delete[] m_author;
			if (b.m_author != nullptr)
			{
				m_author = new char[strlen(b.m_author) + 1];
				strcpy(m_author, b.m_author);
			}
			else
			{
				m_author = nullptr;
			}
		}

		return *this;
	}

	//destructor 
	Book::~Book()
	{
		delete[] m_author;
		m_author = nullptr;
	}


	char Book::type() const
	{
		//returns character B
		return 'B';
	}


	std::ostream& Book::write(std::ostream& os) const
	{
		if (*this)
		{
			//invoke write function
			Publication::write(os);

			//if incoming argument is console IO
			if (conIO(os))
			{
				//write single space
				os << ' ';

				//if author name is>seneca_author_width
				if (strlen(m_author) > SENECA_AUTHOR_WIDTH)
				{

					char temp[SENECA_AUTHOR_WIDTH + 1];
					strncpy(temp, m_author, 15);
					temp[SENECA_AUTHOR_WIDTH] = '\0';
					os << setw(SENECA_AUTHOR_WIDTH) << temp << " |";
				}
				else
				{
					os << setw(SENECA_AUTHOR_WIDTH) << m_author << " |";
				}
			}
			else
			{
				//write tabs character << author name
				os << '\t' << m_author << endl;
			}
		}

		//returns ostream
		return os;
	}


	std::istream& Book::read(std::istream& istr)
	{


		char author[256];

		//invoke read
		Publication::read(istr);

		//free memory
		delete m_author;
		m_author = nullptr;

		//if argument is console IO
		if (conIO(istr))
		{
			//ignore one character \n
			istr.ignore();

			//display author
			cout << "Author: ";

			//read author name entered 
			istr.getline(author, 256, '\n');

		}

		//argument !=console IO
		else
		{
			//ignore tab
			istr.ignore();

			//read author name
			istr.get(author, 256, '\n');

		}

		if (strlen(author) > 256)
		{
			istr.setstate(ios::failbit);
		}
		//if incoming fail state
		if (istr)
		{
			//dynamically allocate memory
			m_author = new char[strlen(author) + 1];

			//set value to argument entered
			strcpy(m_author, author);
		}
		return istr;
	}


	void Book::set(int member_id)
	{
		//invoke set and reset of base class therefore use ::

		Publication::set(member_id);

		Publication::resetDate();
	}


	Book::operator bool() const
	{
		//return true of name of author exist and not empty and bas class operator result is true
		bool result = false;
		if (m_author != nullptr)
		{
			if (m_author[0] != '\0')
			{
				if (Publication::operator bool() == true)
				{
					result = true;

				}

			}

		}
		return result;
	}
}