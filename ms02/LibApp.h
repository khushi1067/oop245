#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H

#include"Menu.h"

namespace seneca {

    class LibApp
    {
    private:
        //flag to track changes
        bool m_changed;

        //will be used as main menu
        Menu m_mainMenu;

        //used when exiting menu
        Menu m_exitMenu;

        //boolean function
        bool confirm(const char* message);

        //prints loading
        void load();

        //prints saving
        void save();

        //prints search
        void search();

        //calls the search()
        void returnPub();

        //adding new publications
        void newPublication();

        //removing publcation
        void removePublication();

        //check for publication
        void checkOutPub();

    public:

        //constructor 
        LibApp();

        //run method to run menu
        void run();
    };
}

#endif