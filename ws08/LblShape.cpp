/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-10-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include "LblShape.h"
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
namespace seneca {

	char* LblShape::label() const
	{
		//return m_label
		return m_label;
	}

	LblShape::LblShape(const char* label)
	{
		//allocate memory
		m_label = new char[strlen(label) + 1];

		//copy it to argument
		strcpy(m_label, label);
	}

	//destrustor deallocate memory
	LblShape::~LblShape()
	{
		delete[] m_label;
		m_label = nullptr;
	}


	void LblShape::getSpecs(istream& istr)
	{
		//reads input uses ',' as deliminator
		char userInput[1000] = "\0";
		istr.getline(userInput, 1000, ',');

		delete[] m_label;

		//follow as one argument constructor
		m_label = new char[strlen(userInput) + 1];
		strcpy(m_label, userInput);
	}
}


