
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
			m_menuitem = new char[strlen(item) + 1];
			strcpy(m_menuitem, item);
		}
		else
		{
			m_menuitem = nullptr;
		}
	}
	MenuItem::~MenuItem()
	{
		delete[] m_menuitem;
		m_menuitem = nullptr;
	}
	MenuItem::operator bool() const
	{
		bool r = false;
		if (m_menuitem != nullptr)
		{
			r = true;
		}
		return r;
	}
	MenuItem::operator const char* () const
	{
		return m_menuitem;
	}
	void MenuItem::display(std::ostream& os) const
	{

		{
			os << m_menuitem;
		}
	}
	Menu::Menu()
	{

		m_noofitems = 0;
	}
	Menu::Menu(const char* title)
	{
		if (title != nullptr)
		{
			m_title.m_menuitem = new char[strlen(title) + 1];
			strcpy(m_title.m_menuitem, title);
		}
		m_noofitems = 0;
	}

	Menu::~Menu()
	{
		for (int i = 0; i < m_noofitems; i++)
		{
			delete m_items[i];
			m_items[i] = nullptr;
		}

	}
	void Menu::displaytitle(std::ostream& os) const
	{
		if (m_title.m_menuitem != nullptr)
		{
			m_title.display(os);
		}
	}
	void Menu::displaymenu(std::ostream& os) const
	{
		if (m_title.m_menuitem != nullptr)
		{
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
		int selection = 0;
		displaymenu(cout);
		read(selection, 0, m_noofitems, "Invalid Selection, try again: ");

		unsigned int sel = selection;
		return sel;
	}
	unsigned int Menu::operator~() const
	{

		return run();
	}

	Menu& Menu::operator<<(const char* menuitemConent)
	{
		if (m_noofitems < MAX_MENU_ITEMS)
		{
			MenuItem* temp = nullptr;
			temp = new MenuItem;
			temp->m_menuitem = new char[strlen(menuitemConent) + 1];
			strcpy(temp->m_menuitem, menuitemConent);
			m_items[m_noofitems] = temp;
			m_noofitems++;

		}


		return *this;
	}
	Menu::operator int() const
	{
		return m_noofitems;
	}
	Menu::operator unsigned int() const
	{
		return m_noofitems;
	}
	Menu::operator bool() const
	{
		bool r = false;
		if (m_noofitems > 0)
		{
			r = true;
		}
		return r;
	}

	const char* Menu::operator[](int i) const
	{
		if (i > m_noofitems)
		{
			i = i % m_noofitems;
		}
		return *m_items[i];
	}
	std::ostream& operator<<(std::ostream& os, const Menu& menu)
	{
		menu.displaytitle(os);
		return os;
	}
}