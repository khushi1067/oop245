/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-10-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#pragma once
#ifndef SENECA_VEHICLE_H__
#define SENECA_VEHICLE_H__
#include <iostream>

namespace seneca 
{
	class MotorVehicle 
	{
		//static array with size 9

		char m_plate[9] = {};
		
		//static array of characters with size 64
		char m_address[64] = {};
		int m_year = 0;
	
	public:

		MotorVehicle();

		//constructor with two argumants plate and  year
		MotorVehicle(const char* plate, int year);

		//move vehicle to new address
		void moveTo(const char* addressFinal);

		//insert function
		std::ostream& write(std::ostream& os)const;
		
		//read function
		std::istream& read(std::istream& in);
	};

	//helper operator overload
	std::ostream& operator<<(std::ostream& ostr, const MotorVehicle& text);
	std::istream& operator>>(std::istream& istr, MotorVehicle& text);
}
#endif
