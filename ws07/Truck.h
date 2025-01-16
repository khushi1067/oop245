/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-10-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#pragma once

#ifndef SENECA_TRUCK_H__
#define SENECA_TRUCK_H__
#include <iostream>
#include "MotorVehicle.h"
namespace seneca 
{
    // Defines the Truck class that inherits from MotorVehicle
	class Truck :public MotorVehicle 
    {
        // Maximum weight
		double mCapacity = 0.0;

        // Current cargo load
		double mCargo = 0.0;

	public:

        // Custom constructor
		Truck(const char* plate, int year, double cargo, const char* address);

        // add cargo
        bool addCargo(double cargo);

        // Unloads  cargo from the truck
		bool unloadCargo();


        // function to write data
		std::ostream& write(std::ostream& os) const;

        //function to read data
		std::istream& read(std::istream& in);
	};
    // Overloads << operator to write
	std::ostream& operator<<(std::ostream& ostr, const Truck& right);

    // Overloads >> operator to read

	std::istream& operator>>(std::istream& istr, Truck& right);
}
#endif





