/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-10-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <iomanip>
#include "MotorVehicle.h"

using namespace std;
namespace seneca 
{

	MotorVehicle::MotorVehicle() 
	
	{
		// Initializes the plateNo array to an empty string
		m_plate[0] = {};

		// Initializes the address array to an empty string
		m_address[0] = {};

		// Initializes the year to 0
		m_year = 0;
	}

	MotorVehicle::MotorVehicle(const char* plate, int year) 
	{
		// Sets address to "Factory"
		strcpy(this->m_address, "Factory");


		// copy plate to argument plate
		strcpy(this->m_plate, plate);

		// Sets the year to the provided year
		m_year = year;
	}

	void MotorVehicle::moveTo(const char* address) 
	{
		// Checks if argument address 
		if (address != m_address) 
		{
			cout << "|" << setw(8) << m_plate << "|";
			cout << " |" << setw(20) << m_address << " ---> ";

			// Sets the output to left-aligned
			cout.setf(ios::left);
			cout << setw(20) << address << "|";
			cout.unsetf(ios::left);
			cout << endl;

			// Copies affress to argument address calue
			strncpy(m_address, address, 63);


			m_address[63] = char(0);
		}
	}

	std::ostream& MotorVehicle::write(std::ostream& os)const
	{
		os << "| " << m_year << " | " << m_plate << " | " << m_address;
		return os;
	}

	std::istream& MotorVehicle::read(std::istream& in) 
	{

		cout << "Built year: ";
		in >> m_year;
		
		// Reads the built year
		cout << "License plate: ";
		in >> m_plate;

		// Reads the current location
		cout << "Current location: ";
		in >> m_address;

		return in;
	}

	// Overload << operator to write
	std::ostream& operator<<(std::ostream& ostr, const MotorVehicle& right) 
	{
		return right.write(ostr);
	}


	// Overload >> operator to read

	std::istream& operator>>(std::istream& istr, MotorVehicle& right) 
	{
		return right.read(istr);
	}

}
