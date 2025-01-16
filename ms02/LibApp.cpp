#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "LibApp.h"
#include "Menu.h"
using namespace std;

namespace seneca {

    bool LibApp::confirm(const char* message) 
    {
        bool isConfirmed;
        // instantiate function and  initialize by gument 
        Menu confirmMenu(message);

        //add message
        confirmMenu << "Yes";

        // Check if the user selected the first option (which is "Yes")
        if (confirmMenu.run() == 1) 
        {
            
            isConfirmed = true;
        }
        else {
            // If "Yes" was not selected, set isConfirmed to false
            isConfirmed = false;
        }

        // Return the result of the confirmation
        return isConfirmed;
    }

    void LibApp::load() 
    {
        std::cout << "Loading Data" << endl;
    }

    void LibApp::save() 
    {
        std::cout << "Saving Data" << endl;
    }

    void LibApp::search() 
    {
        std::cout << "Searching for publication" << endl;
    }

    void LibApp::returnPub() 
    {
        search();

        std::cout << "Returning publication" << endl;
        std::cout << "Publication returned" << endl;

        //set flag to true
        m_changed = true;
    }

    void LibApp::newPublication() 
    {
        std::cout << "Adding new publication to library" << endl;

        if (confirm("Add this publication to library?")) 
        {
            //change flag to true
            m_changed = true;

            std::cout << "Publication added" << endl;
        }
    }


    void LibApp::removePublication() 
    {
        std::cout << "Removing publication from library" << endl;

        search();

        if (confirm("Remove this publication from the library?")) 
        {
            //change flag to true
            m_changed = true;

            std::cout << "Publication removed" << endl;
        }
    }

    void LibApp::checkOutPub() 
    {
        search();

        if (confirm("Check out publication?")) 
        {
            //set flag to true
            m_changed = true;

            std::cout << "Publication checked out" << endl;
        }
    }

    LibApp::LibApp()
        : m_changed(false),
        m_mainMenu("Seneca Library Application"),
        m_exitMenu("Changes have been made to the data, what would you like to do?")
    {
        // Adding options to the main menu
        m_mainMenu << "Add New Publication"
            << "Remove Publication"
            << "Checkout publication from library"
            << "Return publication to library";

        // Adding options to the exit menu
        m_exitMenu << "Save changes and exit"
            << "Cancel and go back to the main menu";

        // Load data
      load();
    }


    void LibApp::run() 
    {

        bool done = false;
        while (!done) {
            switch (m_mainMenu.run()) 
            {
            case 1:

                newPublication();
               
                break;
            case 2:
                removePublication();
              
                break;
            case 3:
                checkOutPub();
               
                break;
            case 4:
                returnPub();
               
                break;

            case 0:
                if (m_changed) {
                    switch (m_exitMenu.run()) {
                    case 1:
                        save();
                        done = true;
                        break;
                    case 0:
                        if (confirm("This will discard all the changes are you sure?")) {
                            done = true;
                        }
                      
                
                        break;
                    }
                }
                else {
                    done = true;
                }
                break;
            }
            std::cout << endl;
        }
        std::cout << "-------------------------------------------" << endl;
        std::cout << "Thanks for using Seneca Library Application" << endl;
    }
}

