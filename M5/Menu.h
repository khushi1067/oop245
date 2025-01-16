/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-12-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#ifndef SENECA_MENU_H__
#define SENECA_MENU_H__
#include <iostream>
namespace seneca {

	const int MAX_MENU_ITEMS = 20;
	class MenuItem
	{
		char* m_menuitem;
		friend class Menu;
		MenuItem(const char* item = nullptr);
		MenuItem(const MenuItem& itm) = delete;
		MenuItem& operator=(const MenuItem& itm) = delete;
		~MenuItem();
		operator bool() const;
		operator const char* () const;
		void display(std::ostream& os) const;

	};

	class Menu
	{
		MenuItem m_title;
		MenuItem* m_items[MAX_MENU_ITEMS] = {};
		int m_noofitems;

	public:
		Menu();
		Menu(const char* title);

		~Menu();
		Menu(const Menu& menu) = delete;
		Menu& operator=(const Menu& menu) = delete;
		void displaytitle(std::ostream& os) const;
		void displaymenu(std::ostream& os) const;
		unsigned int run() const;
		unsigned int operator~() const;
		Menu& operator<<(const char* menuitemConent);
		operator int() const;
		operator unsigned int() const;
		operator bool() const;
		const char* operator[](int index) const;


	};

	std::ostream& operator<<(std::ostream& os, const Menu& menu);


}
#endif