
#ifndef SENECA_LIBAPP_H

#define SENECA_LIBAPP_H
#include"Utils.h"
#include "Menu.h"
#include "Publication.h"
#include "Book.h"
#include "PublicationSelector.h"

namespace seneca 
{
    class LibApp 
    {
        bool m_changed;
        Menu m_mainMenu;
        Menu m_exitMenu;
        Menu m_publicationmenu;

        //array of 256 char to hold data file
        char m_filename[256];

        //publication array pointer[size] 
        Publication* m_publication[SENECA_LIBRARY_CAPACITY]{};


        int m_numpub;
        int m_librefapp;


        bool confirm(const char* message);
        void load();  // prints: "Loading Data"<NEWLINE>
        void save();  // prints: "Saving Data"<NEWLINE>
        int search(int type);//(bool all = false, bool onloan = false, bool notloan = false);  // prints: "Searching for publication"<NEWLINE>

        Publication* getPub(int libRef);
        void newPublication();
        void removePublication();
        void checkOutPub();
        void returnPub();
        void prnPub(Publication* p[], int size, int ref);
    public:
        LibApp(const char* file);
        ~LibApp();
        void run();





    };
}
#endif 





 
