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
#include <cstring>
using namespace std;
#include "Menu.h"
#include "Utils.h"

namespace seneca
{
	MenuItem::MenuItem(const char* item)
	{
		if (item != nullptr)
		{
			//allocate memory of len argument
			m_menuitem = new char[strlen(item) + 1];
			
			//copy into argument 
			strcpy(m_menuitem, item);
		}
		else
		{
			//set it to nullptr
			m_menuitem = nullptr;
		}
	}

	//destructor
	MenuItem::~MenuItem()
	{
		delete[] m_menuitem;
		m_menuitem = nullptr;
	}


	MenuItem::operator bool() const
	{
		//initialize flag to false
		bool flag = false;


		if (m_menuitem != nullptr)
		{
			//set flag to true
			flag = true;
		}

		//return flag 
		return flag;
	}


	MenuItem::operator const char* () const
	{
		//function returns menu item

		return m_menuitem;
	}

	void MenuItem::display(std::ostream& os) const
	{

		{
			//display menu item
			os << m_menuitem;
		}
	}

	Menu::Menu()
	{
		//set no of items in menu to 0
		m_noofitems = 0;
	}

	Menu::Menu(const char* title)
	{

		if (title != nullptr)
		{
			//allocate memory
			m_title.m_menuitem = new char[strlen(title) + 1];
			
			//store on argumant value
			strcpy(m_title.m_menuitem, title);
		}

		//set numberof items to 0
		m_noofitems = 0;
	}

	//destructor for menu
	Menu::~Menu()
	{
		//use loop to delete memory
		//loop through items
		for (int i = 0; i < m_noofitems; i++)
		{
			delete m_items[i];
			m_items[i] = nullptr;
		}

	}

	//display title
	void Menu::displaytitle(std::ostream& os) const
	{
		
		if (m_title.m_menuitem != nullptr)
		{
			//display title call display function
			m_title.display(os);
		}
	}


	//fnction to diaplay items in menu
	void Menu::displaymenu(std::ostream& os) const
	{
		if (m_title.m_menuitem != nullptr)
		{
			//display titlr
			displaytitle(os);
			os << endl;
		}

		for (int i = 0; i < m_noofitems; i++)
		{
			os << " " << i + 1 << "- ";
			m_items[i]->display(os);
			os << endl;
		}
		os << " 0- Exit" << endl << "> ";
	}


	unsigned int Menu::run() const
	{
		//initialize variable
		int selection = 0;

		//display menu
		displaymenu(cout);

		//read users selection 

		read(selection, 0, m_noofitems, "Invalid Selection, try again: ");
		
		//store selection in variable
		unsigned int sel = selection;

		//returns user delection
		return sel;
	}


	//destructor 
	unsigned int Menu::operator~() const
	{
		//return run function
		return run();
	}


	Menu& Menu::operator<<(const char* menuitemConent)
	{
		if (m_noofitems < MAX_MENU_ITEMS)
		{
			//initialize pointer to null
			MenuItem* temp = nullptr;

			//allocate memory
			temp = new MenuItem;

			//allocate memory for menu item
			temp->m_menuitem = new char[strlen(menuitemConent) + 1];

			//copy content in newly allocated memory
			strcpy(temp->m_menuitem, menuitemConent);

			//store menu itrm in array 
			m_items[m_noofitems] = temp;

			//increment number of items in menu
			m_noofitems++;

		}

		//return this
		return *this;
	}

	
	Menu::operator int() const
	{
		//returns number of items in menu
		return m_noofitems;
	}


	Menu::operator unsigned int() const
	{
		//returns number of items 
		return m_noofitems;
	}

	Menu::operator bool() const
	{
		//set flag to false
		bool flag = false;
		
		//if number of items >0
		if (m_noofitems > 0)
		{

			//set flag to true
			flag = true;
		}

		//return flag value
		return flag;
	}

	
	const char* Menu::operator[](int i) const
	{
		//if i > number of items
		if (i > m_noofitems)
		{
			
			i = i % m_noofitems;
		}
		return *m_items[i];
	}

	std::ostream& operator<<(std::ostream& os, const Menu& menu)
	{
		//display title
		menu.displaytitle(os);

		//return os
		return os;
	}
}