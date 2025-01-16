/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 07-12-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "LibApp.h"
#include <iomanip>

using namespace std;

namespace seneca 
{
    // Load function
    void LibApp::load()
    {
        //print loading data
        cout << "Loading Data" << endl;
        //open file read file
        ifstream infile(m_filename);
        char type{};

        //read publication add it to lobrary
        for (int i = 0; infile; i++)
        {
            //read file
            infile >> type;

            //if file sicessfully read
            if (infile) 
            {
                if (type == 'P')
                {
                    //allocate memory for publication object
                    m_publication[i] = new Publication;
                }

                else if (type == 'B')
                {
                    //allocate memory fot book object
                    m_publication[i] = new Book;
                }
                //of publication object was created 
                if (m_publication[i])
                {
                    //read data
                    infile >> *m_publication[i];

                    //increment
                    m_numpub++;
                }
            }
        }

        //set reference for the last publication loaded
        m_librefapp = m_publication[m_numpub - 1]->getRef();
    }



    void LibApp::save()
    {
        //print saving data
        cout << "Saving Data" << endl;

        //open file usin ofstream
        ofstream onfile(m_filename);
        if (onfile.is_open())
        {
            //write data to file
            for (int i = 0; i < m_numpub; i++) {

                if (m_publication[i]->getRef() != 0)
                {
                    onfile << *m_publication[i];
                }
            }
        }
    }

    // Function for printing publication by reference number
    void LibApp::prnPub(Publication* p[], int size, int ref) 
    {
        int i;
        for (i = 0; i < size; i++)
        {
            //if referece number matches it prints publication
            if (ref == p[i]->getRef()) 
            {
                cout << *p[i] << endl;
                break;
                //i = size; // Exit the loop.
            }
        }
    }

    LibApp::LibApp(const char* file) 
        :m_changed(), 
        m_mainMenu("Seneca Library Application"), 
        m_exitMenu("Changes have been made to the data, what would you like to do?"), 
        m_publicationmenu("Choose the type of publication:")
    {
        m_changed = false;

        //copy file name to argument
        strcpy(m_filename, file);

        //initialize number of production to 0
        m_numpub = 0;

        //initialize reference number to -1
        m_librefapp = -1;

        //add option to main menu use << overloaded operator for adding data
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";

        //add options to exit menu

        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";

        //add options to publication menu

        m_publicationmenu << "Book" << "Publication";

        //call load function
        load();


    }

    // Function to confirm
    bool LibApp::confirm(const char* message)
    {
        //set flag to false
        bool flag = false;

        //create menu
        Menu temp(message);

        //add "Yes" to menu as a option by using << operator overloading

        temp << "Yes";

        //if yes is selected

        int i = temp.run();
        if (i == 1)
        {
            //set flag to true

            flag = true;
        }
        return flag;
    }

    int LibApp::search(int type)
    {
        //vat to store result
        int res = 0;

        //store publication title size -> 256      
        char filename[256];

        //variable to store selection
        int selection = -1;

        //open file
        ifstream infile(m_filename);


        PublicationSelector ps("Select one of the following found matches:", 15);
        
        if (type == 1)
        {
            selection = m_publicationmenu.run();
            switch (selection)
            {
            case 1:
            {
                //display title

                cout << "Publication Title: ";

                //get title

                cin.getline(filename, '\n');
                char type{};
                int i;
                for (i = 0; i < m_numpub; i++) 
                {
                    //read type of publication
                    infile >> type;

                    //ignore characters 
                    infile.ignore();

                    if (infile)
                    {
                        
                        if (m_publication[i]->type() == 'B' 
                            && strstr(*m_publication[i], filename) 
                            && m_publication[i]->getRef() != 0)
                        { 
                            ps << m_publication[i];
                        }
                    }
                }
                if (ps) 
                {
                    ps.sort(); 
                    int ref = ps.run(); 
                    if (ref) 
                    {

                        cout << *getPub(ref) << endl;
                        res = ref;
                    }
                    else 
                    {
                        cout << "Aborted!" << endl;
                    }
                }
                else
                {
                    cout << "No matches found!" << endl;
                }

                break;
            }
            case 2:
            {
                cout << "Publication Title: ";
                cin.getline(filename, '\n');
                char type{};
                int i;
                for (i = 0; i < m_numpub; i++)
                {
                    infile >> type;
                    infile.ignore();
                    if (infile) 
                    {

                        if (m_publication[i]->type() == 'P'
                            && strstr(*m_publication[i], filename)
                            && m_publication[i]->getRef() != 0)
                        {
                            ps << m_publication[i];
                        }
                    }
                }

                //if match found
                if (ps)
                {
                    //call sort function
                    ps.sort(); 


                    int ref = ps.run(); 
                    
                    if (ref) 
                    {
                        //display selected publication

                        cout << *getPub(ref) << endl;

                        //set result to slected publication references
                        res = ref;
                    }
                    else 
                    {
                        cout << "Aborted!" << endl;
                    }
                }
                else 
                {
                    cout << "No matches found!" << endl;
                }

                break;
            }
            case 0:
            {
                cout << "Aborted!" << endl;
                break;
            }
            }
        }

        //case 2 if puclication is not a book
        if (type == 2)
        {
            selection = m_publicationmenu.run();
            switch (selection)
            {
            case 1:
            {
                cout << "Publication Title: ";
                cin.getline(filename, '\n');
                char type{};
                int i;
                for (i = 0; i < m_numpub; i++) {
                    infile >> type;
                    infile.ignore();
                    if (infile) {

                        if (m_publication[i]->type() == 'B'
                            && strstr(*m_publication[i], filename)
                            && m_publication[i]->onLoan())

                        {
                            ps << m_publication[i];
                        }
                    }
                }
                if (ps) {
                    ps.sort(); 
                    int ref = ps.run();
                    if (ref) 
                    {

                        cout << *getPub(ref) << endl;
                        res = ref;
                    }
                    else
                    {
                        cout << "Aborted!" << endl;
                    }
                }
                else 
                {
                    cout << "No matches found!" << endl;
                }

                break;
            }
            case 2:
            {
                cout << "Publication Title: ";
                cin.getline(filename, '\n');
                char type{};
                int i;
                
                for (i = 0; i < m_numpub; i++) 
                {
                    infile >> type;
                    infile.ignore();
                    if (infile)
                    {

                        if (m_publication[i]->type() == 'P'
                            && strstr(*m_publication[i], filename)
                            && m_publication[i]->onLoan())

                        {
                            ps << m_publication[i];
                        }
                    }
                }
                if (ps) 
                {
                    ps.sort(); 
                    int ref = ps.run(); 
                    if (ref)
                    {

                        cout << *getPub(ref) << endl;
                        res = ref;
                    }
                    else 
                    {
                        cout << "Aborted!" << endl;
                    }
                }
                else 
                {
                    cout << "No matches found!" << endl;
                }

                break;
            }
            case 0:
            {
                cout << "Aborted!" << endl;
                break;
            }
            }
        }
        if (type == 3)
        {
            selection = m_publicationmenu.run();
            switch (selection)
            {
            case 1:
            {
                cout << "Publication Title: ";
                cin.getline(filename, '\n');
                char type{};
                int i;
                for (i = 0; i < m_numpub; i++)
                {
                    infile >> type;
                    infile.ignore();
                    if (infile) {

                        if (m_publication[i]->type() == 'B'
                            && strstr(*m_publication[i], filename)
                            && !m_publication[i]->onLoan())
                        {
                            ps << m_publication[i];
                        }
                    }
                }
                if (ps)
                {
                    ps.sort(); 
                    int ref = ps.run(); 
                    if (ref) 
                    {

                        cout << *getPub(ref) << endl;
                        res = ref;
                    }
                    else 
                    {
                        cout << "Aborted!" << endl;
                    }
                }
                else 
                {
                    cout << "No matches found!" << endl;
                }

                break;
            }
            case 2:
            {
                cout << "Publication Title: ";
                cin.getline(filename, '\n');
                char type{};
                int i;
                for (i = 0; i < m_numpub; i++) 
                {
                    infile >> type;
                    infile.ignore();
                    if (infile)
                    {

                        if (m_publication[i]->type() == 'P'
                            && strstr(*m_publication[i], filename)
                            && !m_publication[i]->onLoan())
                        {
                            ps << m_publication[i];
                        }
                    }
                }
                if (ps)
                {
                    ps.sort(); 
                    int ref = ps.run(); 
                    if (ref) 
                    {

                        cout << *getPub(ref) << endl;
                        res = ref;
                    }
                    else 
                    {
                        cout << "Aborted!" << endl;
                    }
                }

                else 
                {
                    cout << "No matches found!" << endl;
                }

                break;
            }
            case 0:
            {
                cout << "Aborted!" << endl;
                break;
            }
            }
        }
        return res;
    }


    
    // Get publication by reference number
    Publication* LibApp::getPub(int libRef)
    {
        //initialize variable temp 
        Publication* temp = nullptr;

        //loop through all publications
        for (int i = 0; i < m_numpub; i++)
        {
            //check if any reference matches to temp 
            if (m_publication[i]->getRef() == libRef)
            {
                //if match
                //assign it to temp variable created
                temp = m_publication[i];
            }
        }

        //return temp variable
        return temp;
    }


    void LibApp::newPublication()
    {
        // If the library is full
        if (m_numpub == SENECA_LIBRARY_CAPACITY)
        {
            cout << "Library is at its maximum capacity!" << endl;
        }
        else
        {
            cout << "Adding new publication to the library" << endl;

            // Initialize the variable
            int selection = -1;

            // Get the type of publication to add
            selection = m_publicationmenu.run();

            if (selection == 0)
            {
                // Case for aborting the operation
                cout << "Aborted!" << endl;
            }
            else if (selection == 1)
            {
                
                // Dynamically allocate memory for a new Book object
                Publication* temp = new Book;   

                // Read data
                temp->read(cin);                

                //if sucessfully read
                if (cin)                        
                {
                    
                    bool flag = confirm("Add this publication to the library?"); 
                    
                    if (flag == true)             
                    {
                        //if publication is created
                        if (temp)               
                        {
                            // Add the new publicaion 
                            m_publication[m_numpub] = temp;

                            // Set the reference for the new publication
                            m_publication[m_numpub]->setRef(m_librefapp + 1);
                            
                            //increment m_librefapp
                            m_librefapp++;

                            // Increment the number of publications
                            m_numpub++;

                            // set m_changed flag to true
                            m_changed = true;

                            cout << "Publication added" << endl; 
                        }
                        else
                        {
                            cout << "Failed to add publication!" << endl;

                            //delete created temp object
                            delete temp; 
                        }
                    }
                }
                else
                {
                    //  clear the input stream 
                    cout.clear();
                    cout << "Aborted" << endl;
                }
            }
            else if (selection == 2)
            {
                // Dynamically allocate memory for a new Book object
                Publication* temp = new Publication; 

                // Read data

                temp->read(cin);                      

                //if sucessfully read

                if (cin)                            
                {
                    bool flag = confirm("Add this publication to the library?"); 
                    if (flag == true)                 
                    {
                        //if publication is created

                        if (temp)                  
                        {
                            // Add the new publicaion 
                            m_publication[m_numpub] = temp;

                            // Set the reference for the new publication
                            m_publication[m_numpub]->setRef(m_librefapp + 1);
                            
                            //increment m_librefapp
                            m_librefapp++;

                            // Increment the number of publications
                            m_numpub++;
                            
                            // set m_changed flag to true
                            m_changed = true;
                            cout << "Publication added" << endl; 
                        }
                        else
                        {
                            cout << "Failed to add publication!" << endl; 

                            //delete created temp object

                            delete temp; 
                        }
                    }
                }
                else
                {
                    //  clear the input stream 
                    cout.clear();
                    cout << "Aborted" << endl;
                }
            }
        }
    }

  

    // Return publication to library

    void LibApp::returnPub()
    {
        cout << "Return publication to the library" << endl;

        //search publication

        int ref = 0;
        bool r = false;
        ref = search(2);
        if (ref > 0)
        {
            r = confirm("Return Publication?");
            if (r)
            {
                // Get the checkout date

                Date temp = getPub(ref)->checkoutDate();
                Date today;

                // check if the publication is overdue

                if (today - temp > 15)
                {
                    // Calculate the penalty

                    int penalty = (today - temp) - 15;

                    // Calculate te the price

                    double price = penalty * 0.5;
                    cout << "Please pay " << "$";
                    cout.setf(ios::fixed);
                    cout.width(3);
                    cout.precision(2);
                    cout << price << " penalty for being " << penalty << " days late!" << endl;
                }
                // Return the publication

                getPub(ref)->set(0);

                cout << "Publication returned" << endl;

                //set flag to true

                m_changed = true;
            }
        }
    }




    // Remove a publication from the library

    void LibApp::removePublication()
    {
        cout << "Removing publication from the library" << endl;

        // Search for the publication to remove

        int ref = 0;
        Publication* temp;
        ref = search(1);
        // Confirm removal

        if (ref > 0)
        {
            bool r = confirm("Remove this publication from the library?");
            if (r == true)
            {
                // Remove the publication by setting reference to 0

                temp = getPub(ref);
                temp->setRef(0);

                // Set changed flag to true

                m_changed = true;
                cout << "Publication removed" << endl;
            }
        }
    }


    // Check out a publication from the library

    void LibApp::checkOutPub()
    {
        cout << "Checkout publication from the library" << endl;
        int ref = 0;
        int num = 0;

        ref = search(3);
        if (ref > 0)
        {
            bool flag = confirm("Check out publication?");
            if (flag == true)
            {
                cout << "Enter Membership number: ";
                //cin.getline(mem, 5, '\n');
                cin >> num;

                while (!(num >= 10000 && num <= 99999))
                {

                    {
                        cout << "Invalid membership number, try again: ";

                        cin >> num;
                    }
                }
                if (cin)
                {
                    int mid = int(num);
                    getPub(ref)->set(mid);
                    m_changed = true;
                    cout << "Publication checked out" << endl;
                }

            }
        }
    }


    //destructor
    LibApp::~LibApp()
    {
        //deallocate memory using loop
        for (int i = 0; i < m_numpub; i++)
        {
            delete m_publication[i];
        }
    }


    
    void LibApp::run()
    {
        bool done = true;
        int selection = -1;
        do
        {

            selection = m_mainMenu.run();

            {
                if (selection == 1)
                {
                    newPublication();
                    cout << endl;

                }
                else if (selection == 2)
                {
                    removePublication();
                    cout << endl;

                }
                else if (selection == 3)
                {
                    checkOutPub();
                    cout << endl;
                }
                else if (selection == 4)
                {
                    returnPub();
                    cout << endl;
                }
                else
                {
                    if (m_changed == true)
                    {
                        int i = -1;
                        i = m_exitMenu.run();
                        switch (i)
                        {
                        case 1:
                        {
                            save();
                            done = false;
                        }
                        case 2:
                        {
                            continue;
                        }
                        case 0:
                        {
                            bool exit = confirm("This will discard all the changes are you sure?");
                            if (exit == true)
                            {

                                done = false;
                            }
                        }
                        }
                    }

                    break;

                }
            };
        } while (done);
        cout << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;
    }

}
