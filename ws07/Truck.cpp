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
#include "Truck.h"
using namespace std;
namespace seneca 
{
    
	Truck::Truck(const char* plate, int year, double cargo, const char* address) :MotorVehicle(plate, year)
    {
        // Sets the capacity of the truck
       
        //set current cargo to 0
		mCapacity = cargo;
        // Moves the truck to the specified address
		moveTo(address);
	}

    // Adds cargo to the truck
	bool Truck::addCargo(double cargo) 
    {

        // initialize value for flag
        bool isValid = false;

        // Checks if cargo can be added
		if (mCargo != mCapacity) 
        {
            // Sets flag to true
			isValid = true;

            // If the added cargo doesn't exceed the capacity
			if (cargo < mCapacity) 
            {
                // Adds the cargo to the current load
				mCargo += cargo;
			}
			if (mCargo > mCapacity) 
            {
                // Sets the cargo to the maximum capacity
				mCargo = mCapacity;
			}
		}

       
		return isValid;
	}

    // Unloads  cargo from the truck
	bool Truck::unloadCargo()
    {
        //if current load has been changed return true else false
       
        // Checks if there is cargo to unload
		bool unload = this->mCargo > 0;
        // Sets the cargo load to 0
        mCargo = 0;

        // Returns whether the cargo was unloaded
		return unload;
	}

    // Writes the Truck object data to the output stream
	std::ostream& Truck::write(std::ostream& os)const 
    {
        //write method
		MotorVehicle::write(os);
             
		os << " | " << mCargo << "/" << mCapacity;
             
		return os;
	}

    // Reads the Truck object data from the input stream
	std::istream& Truck::read(std::istream& in) 
    {
        // read method
		MotorVehicle::read(in);

        // Reads the capacity
		cout << "Capacity: ";

		in >> mCapacity;
       
        // Reads the current cargo load
        cout << "Cargo: ";

		in >> mCargo;

        // Returns the input stream
		return in;
	}

    // Overloads  << for write function
    std::ostream& operator<<(std::ostream& ostr, const Truck& right) 
    {
        // Calls the write method to output the object data
		return right.write(ostr);
	}

    // Overloads >> for read function
	std::istream& operator>>(std::istream& istr, Truck& right)
    {
        // Calls the read method to input the object data
		return right.read(istr);
    }
	
}



