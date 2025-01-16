 /*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 06-07-2024

I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.

 ******************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <istream>
#include <iomanip>
#include <cstring>
#include "Canister.h"

const double PI = 3.14159265;

using namespace std;
namespace seneca 
{

	void Canister::setToDefault()
	{
		//set attributes to default value

		//content name to null pointer
		m_contentName = NULL;   //dynamic allocated Cstring
		//height diameter and volume to 13.0, 10.0 and 0.0 
		m_height=13.0;  
		 m_diameter = 10.0;
		 
		 m_contentVolume=0.0;
		 //usable flag to true
		 m_usable=true;
	}

	bool Canister::isEmpty() const
	{
		//constant dunction returns true if vlue for cintent volume is < 000001
		if (m_contentVolume<0.00001)
		{
			return true;

		}
		return false;
	}

	bool Canister::hasSameContent(const Canister& C) const
	{

		//compare name with the argument C
		if (strcmp(m_contentName,C.m_contentName)==0)
		{
			//check if both the names are not null 
			//if not null returns true else return false
			
			if (m_contentName!=NULL)
			{
				if (C.m_contentName!=NULL)
				{
						return true;

				}


			}

		}

		return false;
	}

	void Canister::setName(const char* Cstr)
	{
		//check if entered Cstring is not null
		if (Cstr!=NULL)
		{
			//check if the canister is usable
			if (m_usable)
			{
				//delete content name
				delete[]m_contentName;

				//allocate memory to length of c string +1
				//stores length of c string in var len
				int len = strlen(Cstr);

				//allocate memory => size length of string +1
				m_contentName = new char[len + 1];
	
				//copy c string in allocated memory
				strcpy(m_contentName, Cstr);

			}
			

		}
		

	}

	Canister::Canister()
	{
		setToDefault();
	}


	Canister::Canister(const char* contentName)
	{
		//set attribute to default value (reuse code)
		setToDefault();

		//call setName function use argument given in function
		setName(contentName);
	}

	Canister::Canister(double height, double diameter, const char* contentName)
	{
		//set attributes to default values
		setToDefault();

		//if all the dimensions under acceptable values  
		if (height>=10.0 && height<=40.0) //for height 10-40
		{
			if (diameter>=10.0 && diameter<=30.0) //for diameter 10-30
			{
				//set m_height to argument height,
				//m_diameter to diameter and content volume to 0
				m_height = height;
				m_diameter = diameter;

				m_contentVolume = 0;

				//set name use argument
				setName(contentName);

			}

			//if condition not satisifies return usable as false
			else
			{
				m_usable = false;
			}

		}
		else
		{
			m_usable = false;
		}
	}

	//destructor
	Canister::~Canister()
	{
		delete[] m_contentName;
	}

	//clear function
	void Canister::clear()
	{
		//deallocate memory
		delete[]m_contentName;

		//set content name to null, volume to 0 and usable flag to true
		m_contentName = nullptr;
		m_contentVolume = 0.0;
		m_usable = true;



	}

	//calculate values 210
	double Canister::capacity() const
	{

		double H = m_height;
		double D = m_diameter;

		//Capacity = PI x (H - 0.267) x (D/2) x (D/2)
		double calculatedCapacity = PI * (H - 0.267) * 
			(D / 2) * (D / 2);

		//return calculated value
		return calculatedCapacity;
	}


	double Canister::volume() const
	{
		//return content volume

		return m_contentVolume;
	}

	Canister& Canister::setContent(const char* contentName)
	{

		//if content name i null return usable true
		if (contentName==NULL)
		{
			m_usable = false;

		}
		//if canister is empty set name 
		else if(isEmpty())
		{
			setName(contentName);


		}
		
		//if canister has content is false set usable to false 
		else if(hasSameContent(contentName)==0)   //!
		{
			m_usable = false;


		}

		//returns reference of the current object (use *this)
		return *this;
	}



	Canister& Canister::pour(double quantity)
	{
		//if cansiter is usable and quantity >0 
		//and sum of volume and quantity <= capacity()
		if (m_usable) 
		{

			if (quantity > 0) 
			{
				//if((m_contentVolume+quantity<=capacity())
				if (( volume()+quantity) <= capacity())
				{
					//add content volume and quantity
					m_contentVolume =m_contentVolume+ quantity;
				}
				//else set usable flag to false
				else 
				{
					m_usable = false;
				}
			}
			else 
			{
				m_usable = false;
			}
		}
		else 
		{
			m_usable = false;
		}

		//return reference of current object
		return *this;
	}

	

	Canister& Canister::pour(Canister& C) 
	{

			//set content name to given argument 
			setContent(C.m_contentName);
	
			//if volume is grater than capacity - volume()
			if (C.volume()>(capacity()-volume()))
			{

				//reduce argument content volume(C.m_contentVolume)
				//by capacity()-volume()

				C.m_contentVolume =C.m_contentVolume- (capacity() - volume());

				
				//set content volume to capacity
				m_contentVolume = capacity();

			}

			else
			{
				//pour function and set argument content name to pour function
				pour(C.m_contentVolume);

				//set content volume to 0.0
				C.m_contentVolume = 0.0;
			}


			//return reference of the current object
		return *this;
	}



	std::ostream& Canister::display() const 
	{
		cout << std::setw(7) << std::right << std::fixed << std::setprecision(1)
			<< capacity() << "cc (" << m_height << 'x' << m_diameter << ") Canister";

		if (!m_usable)
		{
			cout << " of Unusable content, discard!";
		}
		else if (m_contentName != NULL) 
		{
			cout << " of " << std::setw(7) << std::right << std::fixed << std::setprecision(1)
				<< volume() << "cc   " << m_contentName;
		}

		return cout;
	}


}












