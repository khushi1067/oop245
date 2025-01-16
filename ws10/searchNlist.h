/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-28-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#ifndef SENECA_SEARCH_H_
#define SENECA_SEARCH_H_
#include "Collection.h"

using namespace std;

namespace seneca 
{
	//template declaration
	template <typename T, typename S>

	//function template search
	//collection of template obj, template to hold array,number to hold array element, 
	//template to hold value of search
	bool search(Collection<T>& CP, const T* ar, int number, S value);

	template <typename T, typename S>

	bool search(Collection<T>& CP, const T* ar, int number, S value) 
	{
		//initialize flag to false
		bool isValid = false;
		//counter to 0
		int i = 0;

		//loop through array
		for (i=0;i<number;i++)
		{ 
			//check if current element matches the search value
			if (ar[i] == value) 
			{
				//add element to collection
				CP.add(ar[i]); 

				//set flag to true
				isValid = true;
			}
			
		}
		return isValid;
	}


	template <typename T>

	//list all the elements of an array
	void listArrayElements(const char* title, const T a[], int number);
	
	template <typename T>

	//const char for title, const array template of obj, number of elements of array
	void listArrayElements(const char* title, const T a[], int number) 
	{
		//print title
		cout << title << endl; 
		
		//initialize loop
		int i = 0;

		//loop through array
		for ( i = 0; i < number; i++)
		{

			//print the array element
			cout << i + 1 << ": " << a[i] << endl; 
		
		}
	}

}
#endif
