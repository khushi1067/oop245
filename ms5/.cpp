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
    void LibApp::load() {
        cout << "Loading Data" << endl;
        ifstream infile(m_filename);
        char type{};

        for (int i = 0; infile; i++) {
            infile >> type;

            if (infile) {
                if (type == 'P') {
                    m_publication[i] = new Publication;
                }
                else if (type == 'B') {
                    m_publication[i] = new Book;
                }
                if (m_publication[i]) {
                    infile >> *m_publication[i];
                    m_numpub++;
                }
            }
        }

        if (m_numpub > 0) {
            m_librefapp = m_publication[m_numpub - 1]->getRef();
        }
        else {
            m_librefapp = 0;
        }
    }

    // Save function
    void LibApp::save() {
        cout << "Saving Data" << endl;
        ofstream onfile(m_filename);

        if (onfile.is_open()) {
            for (int i = 0; i < m_numpub; i++) {
                if (m_publication[i]->getRef() != 0) {
                    onfile << *m_publication[i];
                }
            }
        }
    }

    // Function for printing publication by reference number
    void LibApp::prnPub(Publication* p[], int size, int ref) {
        for (int i = 0; i < size; i++) {
            if (ref == p[i]->getRef()) {
                cout << *p[i] << endl;
                break;
            }
        }
    }

    // Constructor
    LibApp::LibApp(const char* file)
        : m_changed(false),
        m_mainMenu("Seneca Library Application"),
        m_exitMenu("Changes have been made to the data, what would you like to do?"),
        m_publicationmenu("Choose the type of publication:") {

        strcpy(m_filename, file);
        m_numpub = 0;
        m_librefapp = -1;

        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_publicationmenu << "Book" << "Publication";

        load();
    }

    // Function to confirm
    bool LibApp::confirm(const char* message) {
        Menu temp(message);
        temp << "Yes";
        return temp.run() == 1;
    }

    // Search function
    int LibApp::search(int type) {
        int res = 0;
        char filename[256];

        cout << "Publication Title: ";
        cin.ignore();
        cin.getline(filename, 256);

        ifstream infile(m_filename);
        PublicationSelector ps("Select one of the following found matches:", 15);

        char pubType{};
        for (int i = 0; i < m_numpub; i++) {
            infile >> pubType;
            infile.ignore();

            if (infile) {
                bool matches = (pubType == 'B' && strstr(*m_publication[i], filename) && (type == 1 || m_publication[i]->onLoan() == (type == 2))) ||
                    (pubType == 'P' && strstr(*m_publication[i], filename) && (type == 1 || m_publication[i]->onLoan() == (type == 2)));

                if (matches) {
                    ps << m_publication[i];
                }
            }
        }

        if (ps) {
            ps.sort();
            int ref = ps.run();
            if (ref) {
                cout << *getPub(ref) << endl;
                res = ref;
            }
            else {
                cout << "Aborted!" << endl;
            }
        }
        else {
            cout << "No matches found!" << endl;
        }
        return res;
    }

    // Get publication by reference number
    Publication* LibApp::getPub(int libRef) {
        for (int i = 0; i < m_numpub; i++) {
            if (m_publication[i]->getRef() == libRef) {
                return m_publication[i];
            }
        }
        return nullptr;
    }

    // Return publication to library
    void LibApp::returnPub() {
        cout << "Return publication to the library" << endl;
        int ref = search(2);

        if (ref > 0 && confirm("Return Publication?")) {
            Date temp = getPub(ref)->checkoutDate();
            Date today;

            if (today - temp > 15) {
                int penalty = (today - temp) - 15;
                double price = penalty * 0.5;
                cout << "Please pay $" << fixed << setprecision(2) << price << " penalty for being " << penalty << " days late!" << endl;
            }
            getPub(ref)->set(0);
            cout << "Publication returned" << endl;
            m_changed = true;
        }
    }

    // Add new publication function
    void LibApp::newPublication() {
        if (m_numpub == SENECA_LIBRARY_CAPACITY) {
            cout << "Library is at its maximum capacity!" << endl;
        }
        else {
            cout << "Adding new publication to the library" << endl;
            int selection = m_publicationmenu.run();

            if (selection == 0) {
                cout << "Aborted!" << endl;
                return;
            }

            Publication* temp = (selection == 1) ? new Book : new Publication;
            temp->read(cin);

            if (cin && confirm("Add this publication to the library?")) {
                m_publication[m_numpub] = temp;
                m_publication[m_numpub]->setRef(m_librefapp + 1);
                m_librefapp++;
                m_numpub++;
                m_changed = true;
                cout << "Publication added" << endl;
            }
            else {
                delete temp;
                cout << "Failed to add publication!" << endl;
            }
        }
    }

    // Remove a publication from the library
    void LibApp::removePublication() {
        cout << "Removing publication from the library" << endl;
        int ref = search(1);

        if (ref > 0 && confirm("Remove this publication from the library?")) {
            getPub(ref)->setRef(0);
            m_changed = true;
            cout << "Publication removed" << endl;
        }
    }

    // Check out a publication from the library
    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library" << endl;
        int ref = search(3);
        int mem = 0;

        if (ref > 0 && confirm("Check out publication?")) {
            cout << "Enter Membership number: ";
            cin >> mem;

            while (!(mem >= 10000 && mem <= 99999)) {
                cout << "Invalid membership number, try again: ";
                cin >> mem;
            }

            if (cin) {
                getPub(ref)->set(mem);
                m_changed = true;
                cout << "Publication checked out" << endl;
            }
        }
    }

    // Run the application
    void LibApp::run() {
        bool done = true;
        int selection = -1;
        do {
            selection = m_mainMenu.run();

            if (selection == 1) {
                newPublication();
                cout << endl;
            }
            else if (selection == 2) {
                removePublication();
                cout << endl;
            }
            else if (selection == 3) {
                checkOutPub();
                cout << endl;
            }
            else if (selection == 4) {
                returnPub();
                cout << endl;
            }
            else {
                if (m_changed) {
                    int exitSelection = m_exitMenu.run();
                    switch (exitSelection) {
                    case 1:
                        save();
                        done = false;
                        break;
                    case 2:
                        break;
                    case 0:
                        if (confirm("This will discard all the changes. Are you sure?")) {
                            done = false;
                        }
                        break;
                    }
                }
                else {
                    done = false;
                }
            }
        } while (done);

        cout << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;
    }

    // Destructor
    LibApp::~LibApp() {
        for (int i = 0; i < m_numpub; i++) {
            delete m_publication[i];
        }
    }
}



//
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <cstring>
//#include <fstream>
//#include <string>
//#include "LibApp.h"
//#include <iomanip>
//
//using namespace std;
//
//namespace seneca 
//{
//
//    //load function
//    void LibApp::load()
//    {
//        //print loading data
//        cout << "Loading Data" << endl;
//
//        //open file read file
//        ifstream infile(m_filename);
//        char type{};
//        
//        //read publication add it to lobrary
//        for (int i = 0; infile; i++)
//        {
//            //read file
//            infile >> type;
//
//
//            if (infile)
//            {
//
//                if (type == 'P')
//                {
//                    m_publication[i] = new Publication;
//                 }
//                
//                else if (type == 'B')
//                {
//                    m_publication[i] = new Book;
//
//                }
//                if (m_publication[i])
//                {
//                    //read data
//                    infile >> *m_publication[i];
//                    //increment 
//                    m_numpub++;
//                }
//            }
//        }
//
//        m_librefapp = m_publication[m_numpub - 1]->getRef();
//    }
//
//
//    //save function
//    void LibApp::save()
//    {
//        //print saving data
//        cout << "Saving Data" << endl;
//
//        //open file usin ofstream
//        ofstream onfile(m_filename);
//        
//
//        if (onfile.is_open())
//        {
//            //write data to file
//            for (int i = 0; i < m_numpub; i++) {
//
//                if (m_publication[i]->getRef() != 0)
//                {
//                    onfile << *m_publication[i];
//                }
//            }
//        }
//    }
//
//    //function for printing publication by reference number
//    void LibApp::prnPub(Publication* p[], int size, int ref) 
//    {
//
//        int i;
//        for (i = 0; i < size; i++) 
//        {
//            //if referece number matches it prints publication
//            if (ref == p[i]->getRef()) 
//            {
//                cout << *p[i] << endl;
//                break;
//                //i = size; // Exit the loop.
//            }
//        }
//    }
//
//
//    //constructor
//    LibApp::LibApp(const char* file) 
//        :m_changed(), 
//        m_mainMenu("Seneca Library Application"), 
//        m_exitMenu("Changes have been made to the data, what would you like to do?"), 
//        m_publicationmenu("Choose the type of publication:")
//    {
//        //set flag to false
//        m_changed = false;
//
//        //copy file name to argument
//        strcpy(m_filename, file);
//
//        //initialize number of production to 0
//        m_numpub = 0;
//        //initialize reference number to -1
//        m_librefapp = -1;
//
//        //add option to main menu use << overloaded operator for adding data
//        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
//
//        //add options to exit menu
//        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
//        
//        //add options to publication menu
//        m_publicationmenu << "Book" << "Publication";
//       
//        //call load function
//        load();
//
//
//    }
//
//
//    //function to confirm
//    bool LibApp::confirm(const char* message)
//    {
//
//        //set flag to false
//        bool flag = false;
//
//        //create menu
//        Menu temp(message);
//
//        //add "Yes" to menu as a option by using << operator overloading
//        temp << "Yes";
//
//        //if yes is selected
//        int i = temp.run();
//        if (i == 1)
//        {
//            //set flag to true
//            flag = true;
//        }
//        return flag;
//    }
//
//
//
////search function
//int LibApp::search(int type)
//{
//
//    int res = 0;
//    //store title
//    char filename[256];
//
//    //store user selection
//    int selection1 = -1;     
//
//    // Open file for reading
//    ifstream infile(m_filename);
//
//    //create a publication selector
//    PublicationSelector ps("Select one of the following found matches:", 15); 
//
//    selection1 = m_publicationmenu.run(); 
//
//    cout << "Publication Title: ";
//
//    //get title
//    cin.getline(filename, '\n'); 
//
//    char pubType{};
//
//    // Iterate through the publications to find matches
//    for (int i = 0; i < m_numpub; i++) 
//    {
//        // Read the type of publication by using >> operator 
//        infile >> pubType; 
//        infile.ignore();
//
//        if (infile) {
//            bool matches = (pubType == 'B' && strstr(*m_publication[i], filename) && (type == 1 || m_publication[i]->onLoan() == (type == 2))) ||
//                (pubType == 'P' && strstr(*m_publication[i], filename) && (type == 1 || m_publication[i]->onLoan() == (type == 2)));
//
//            if (matches) {
//                ps << m_publication[i]; // Add matching publication to selector
//            }
//        }
//    }
//
//    if (ps) 
//    {
//        // Sort the matches
//        ps.sort(); 
//
//        // Get the user's selection
//        int ref = ps.run(); 
//        if (ref) 
//        {
//            // Print the selected publication
//            cout << *getPub(ref) << endl; 
//            res = ref;
//        }
//
//        else 
//        {
//            cout << "Aborted!" << endl;
//        }
//    }
//    
//    else 
//    {
//        cout << "No matches found!" << endl;
//    }
//    return res;
//}
//
//
//    //get publication by reference number
//    Publication* LibApp::getPub(int libRef)
//    {
//        Publication* temp = nullptr;
//        for (int i = 0; i < m_numpub; i++)
//        {
//            if (m_publication[i]->getRef() == libRef)
//            {
//                temp = m_publication[i];
//            }
//        }
//        return temp;
//    }
//
//    //return publication to library
//    void LibApp::returnPub()
//    {
//        cout << "Return publication to the library" << endl;
//
//        //search publication
//        int ref = search(2);
//        
//        if (ref > 0 && confirm("Return Publication?")) 
//        {
//            // Get the checkout date
//            Date temp = getPub(ref)->checkoutDate(); 
//            Date today;
//
//           // check if the publication is overdue
//            if (today - temp > 15) 
//            {
//                // Calculate the penalty
//                int penalty = (today - temp) - 15; 
//                // Calculate te the price
//                double price = penalty * 0.5; 
//
//                cout << "Please pay $" << fixed << setprecision(2) << price << " penalty for being " << penalty << " days late!" << endl;
//            }
//            // Return the publication
//            getPub(ref)->set(0); 
//            cout << "Publication returned" << endl;
//            
//            //set flag to true
//            m_changed = true; 
//        }
//    }
//   
//    //add new publication function
//
//    void LibApp::newPublication()
//    {
//        if (m_numpub == SENECA_LIBRARY_CAPACITY)
//        {
//            cout << "Library is at its maximum capacity!" << endl;
//        }
//        else
//        {
//            cout << "Adding new publication to the library" << endl;
//            int selection = -1;
//
//            selection = m_publicationmenu.run();
//            switch (selection)
//            {
//            case 0:
//            {
//                cout << "Aborted!" << endl;
//                break;
//            }
//            case 1:
//            {
//                Publication* temp = new Book;
//                temp->read(cin);
//
//                if (cin)
//                {
//                    bool r = confirm("Add this publication to the library?");
//                    if (r == true)
//                    {
//                        if (temp)
//                        {
//
//                            m_publication[m_numpub] = temp;
//                            m_publication[m_numpub]->setRef(m_librefapp + 1);
//                            m_librefapp++;
//                            m_numpub++;
//                            m_changed = true;
//                            cout << "Publication added" << endl;
//                        }
//                        else
//                        {
//                            cout << "Failed to add publication!" << endl;
//                            delete temp;
//                        }
//                    }
//                }
//                else
//                {
//                    cout.clear();
//                    cout << "Aborted" << endl;
//                }
//                break;
//            }
//            case 2:
//            {
//                Publication* temp = new Publication;
//                temp->read(cin);
//
//                if (cin)
//                {
//                    bool r = confirm("Add this publication to the library?");
//                    if (r == true)
//                    {
//                        if (temp)
//                        {
//                            m_publication[m_numpub] = temp;
//                            m_publication[m_numpub]->setRef(m_librefapp + 1);
//                            m_librefapp++;
//
//                            m_numpub++;
//                            m_changed = true;
//                            cout << "Publication added" << endl;
//                        }
//                        else
//                        {
//                            cout << "Failed to add publication!" << endl;
//                            delete temp;
//                        }
//                    }
//                }
//                else
//                {
//                    cout.clear();
//                    cout << "Aborted" << endl;
//                }
//                break;
//            }
//            }
//
//
//        }
//    }
//    
//    //void LibApp::newPublication() {
//    //    if (m_numpub == SENECA_LIBRARY_CAPACITY) { // If the library is full
//    //        cout << "Library is at its maximum capacity!" << endl;
//    //    }
//    //    else {
//    //        cout << "Adding new publication to the library" << endl;
//    //        int selection = m_publicationmenu.run(); // Get the type of publication to add
//    //        if (selection == 0) {
//    //            cout << "Aborted!" << endl;
//    //            return;
//    //        }
//
//    //        // Create the appropriate publication object based on selection
//    //        Publication* temp = (selection == 1) ? new Book : new Publication;
//    //        temp->read(cin); // Read the publication data
//
//    //        if (cin && confirm("Add this publication to the library?")) { // Confirm addition
//    //            m_publication[m_numpub] = temp; // Add the publication to the library
//    //            m_publication[m_numpub]->setRef(m_librefapp + 1); // Set the reference number
//    //            m_librefapp++; // Increment last reference number
//    //            m_numpub++; // Increment number of publications
//    //            m_changed = true; // Set changed flag to true
//    //            cout << "Publication added" << endl;
//    //        }
//    //        else {
//    //            delete temp; // Delete the temporary publication object
//    //            cout << "Failed to add publication!" << endl;
//    //        }
//    //    }
//    //}
//
//
//
//    //remove a publication from library
//    void LibApp::removePublication() 
//    {
//        cout << "Removing publication from the library" << endl;
//     
//        // Search for the publication to remove
//        int ref = search(1); 
//
//        // Confirm removal
//        if (ref > 0 && confirm("Remove this publication from the library?")) 
//        { 
//            // Remove the publication by setting reference to 0
//            getPub(ref)->setRef(0); 
//            
//            // Set changed flag to true
//            m_changed = true; 
//            cout << "Publication removed" << endl;
//        }
//    }
//
//
//    void LibApp::checkOutPub()
//    {
//        cout << "Checkout publication from the library" << endl;
//        int ref = 0;
//        int mem = 0;
//
//        ref = search(3);
//        if (ref > 0)
//        {
//            bool r = confirm("Check out publication?");
//            if (r == true)
//            {
//                cout << "Enter Membership number: ";
//                //cin.getline(mem, 5, '\n');
//                cin >> mem;
//                while (!(mem >= 10000 && mem <= 99999))
//                {
//
//                    {
//                        cout << "Invalid membership number, try again: ";
//
//                        cin >> mem;
//                    }
//                }
//                if (cin)
//                {
//                    int mid = int(mem);
//                    getPub(ref)->set(mid);
//                    m_changed = true;
//                    cout << "Publication checked out" << endl;
//                }
//
//            }
//        }
//    }
//
//
//   
//    void LibApp::run()
//    {
//        bool done = true;
//        int selection = -1;
//        do
//        {
//
//            selection = m_mainMenu.run();
//
//            {
//                if (selection == 1)
//                {
//                    newPublication();
//                    cout << endl;
//
//                }
//                else if (selection == 2)
//                {
//                    removePublication();
//                    cout << endl;
//
//                }
//                else if (selection == 3)
//                {
//                    checkOutPub();
//                    cout << endl;
//                }
//                else if (selection == 4)
//                {
//                    returnPub();
//                    cout << endl;
//                }
//                else
//                {
//                    if (m_changed == true)
//                    {
//                        int i = -1;
//                        i = m_exitMenu.run();
//                        switch (i)
//                        {
//                        case 1:
//                        {
//                            save();
//                            done = false;
//                        }
//                        case 2:
//                        {
//                            continue;
//                        }
//                        case 0:
//                        {
//                            bool exit = confirm("This will discard all the changes are you sure?");
//                            if (exit == true)
//                            {
//
//                                done = false;
//                            }
//                        }
//                        }
//                    }
//
//                    break;
//
//                }
//            };
//        } while (done);
//        cout << endl;
//        cout << "-------------------------------------------" << endl;
//        cout << "Thanks for using Seneca Library Application" << endl;
//    }
//
//
//    LibApp::~LibApp()
//    {
//        for (int i = 0; i < m_numpub; i++)
//        {
//            delete m_publication[i];
//        }
//    }
//}
//
//
//
//
//
//
//
//
////int LibApp::search(int type)//(bool all, bool onloan, bool notloan)
////{
////    int res = 0;
////    char filename[256];
//
////    int selection = -1;
////    ifstream infile(m_filename);
//
////    PublicationSelector ps("Select one of the following found matches:", 15);
////   
////    if (type == 1)
////    {
////        selection = m_publicationmenu.run();
////        switch (selection)
////        {
////        case 1:
////        {
////            cout << "Publication Title: ";
////            cin.getline(filename, '\n');
////            char type{};
////            int i;
////            for (i = 0; i < m_numpub; i++) {
////                infile >> type;
////                infile.ignore();
////                if (infile) {
////                    if (m_publication[i]->type() == 'B' && strstr(*m_publication[i], filename) && m_publication[i]->getRef() != 0)
////                        ps << m_publication[i];
//
////                }
////            }
////            if (ps) {
////                ps.sort(); // sort them based on date and title
////                int ref = ps.run(); // display the publications and select one
////                if (ref) {
//
////                    cout << *getPub(ref) << endl;
////                    res = ref;
////                }
////                else {
////                    cout << "Aborted!" << endl;
////                }
////            }
////            else {
////                cout << "No matches found!" << endl;
////            }
//
////            break;
////        }
////        case 2:
////        {
////            cout << "Publication Title: ";
////            cin.getline(filename, '\n');
////            char type{};
////            int i;
////            for (i = 0; i < m_numpub; i++) {
////                infile >> type;
////                infile.ignore();
////                if (infile) {
//
////                    if (m_publication[i]->type() == 'P' && strstr(*m_publication[i], filename) && m_publication[i]->getRef() != 0)
////                        ps << m_publication[i];
//
////                }
////            }
////            if (ps) {
////                ps.sort(); // sort them based on date and title
////                int ref = ps.run(); // display the publications and select one
////                if (ref) {
//
////                    cout << *getPub(ref) << endl;
////                    res = ref;
////                }
////                else {
////                    cout << "Aborted!" << endl;
////                }
////            }
////            else {
////                cout << "No matches found!" << endl;
////            }
//
////            break;
////        }
////        case 0:
////        {
////            cout << "Aborted!" << endl;
////            break;
////        }
////        }
////    }
////    if (type == 2)
////    {
////        selection = m_publicationmenu.run();
////        switch (selection)
////        {
////        case 1:
////        {
////            cout << "Publication Title: ";
////            cin.getline(filename, '\n');
////            char type{};
////            int i;
////            for (i = 0; i < m_numpub; i++) {
////                infile >> type;
////                infile.ignore();
////                if (infile) {
//
////                    if (m_publication[i]->type() == 'B' && strstr(*m_publication[i], filename) && m_publication[i]->onLoan())
////                        ps << m_publication[i];
//
////                }
////            }
////            if (ps) {
////                ps.sort(); // sort them based on date and title
////                int ref = ps.run(); // display the publications and select one
////                if (ref) {
//
////                    cout << *getPub(ref) << endl;
////                    res = ref;
////                }
////                else {
////                    cout << "Aborted!" << endl;
////                }
////            }
////            else {
////                cout << "No matches found!" << endl;
////            }
//
////            break;
////        }
////        case 2:
////        {
////            cout << "Publication Title: ";
////            cin.getline(filename, '\n');
////            char type{};
////            int i;
////            for (i = 0; i < m_numpub; i++) {
////                infile >> type;
////                infile.ignore();
////                if (infile) {
//
////                    if (m_publication[i]->type() == 'P' && strstr(*m_publication[i], filename) && m_publication[i]->onLoan())
////                        ps << m_publication[i];
//
////                }
////            }
////            if (ps) {
////                ps.sort(); // sort them based on date and title
////                int ref = ps.run(); // display the publications and select one
////                if (ref) {
//
////                    cout << *getPub(ref) << endl;
////                    res = ref;
////                }
////                else {
////                    cout << "Aborted!" << endl;
////                }
////            }
////            else {
////                cout << "No matches found!" << endl;
////            }
//
////            break;
////        }
////        case 0:
////        {
////            cout << "Aborted!" << endl;
////            break;
////        }
////        }
////    }
////    if (type == 3)
////    {
////        selection = m_publicationmenu.run();
////        switch (selection)
////        {
////        case 1:
////        {
////            cout << "Publication Title: ";
////            cin.getline(filename, '\n');
////            char type{};
////            int i;
////            for (i = 0; i < m_numpub; i++) {
////                infile >> type;
////                infile.ignore();
////                if (infile) {
//
////                    if (m_publication[i]->type() == 'B' && strstr(*m_publication[i], filename) && !m_publication[i]->onLoan())
////                        ps << m_publication[i];
//
////                }
////            }
////            if (ps) {
////                ps.sort(); // sort them based on date and title
////                int ref = ps.run(); // display the publications and select one
////                if (ref) {
//
////                    cout << *getPub(ref) << endl;
////                    res = ref;
////                }
////                else {
////                    cout << "Aborted!" << endl;
////                }
////            }
////            else {
////                cout << "No matches found!" << endl;
////            }
//
////            break;
////        }
////        case 2:
////        {
////            cout << "Publication Title: ";
////            cin.getline(filename, '\n');
////            char type{};
////            int i;
////            for (i = 0; i < m_numpub; i++) {
////                infile >> type;
////                infile.ignore();
////                if (infile) {
//
////                    if (m_publication[i]->type() == 'P' && strstr(*m_publication[i], filename) && !m_publication[i]->onLoan())
////                        ps << m_publication[i];
//
////                }
////            }
////            if (ps) {
////                ps.sort(); // sort them based on date and title
////                int ref = ps.run(); // display the publications and select one
////                if (ref) {
//
////                    cout << *getPub(ref) << endl;
////                    res = ref;
////                }
////                else {
////                    cout << "Aborted!" << endl;
////                }
////            }
////            else {
////                cout << "No matches found!" << endl;
////            }
//
////            break;
////        }
////        case 0:
////        {
////            cout << "Aborted!" << endl;
////            break;
////        }
////        }
////    }
////    return res;
////}
//
//
//
// //void LibApp::returnPub()
//    //{
//    //    cout << "Return publication to the library" << endl;
//
//    //    int ref = 0;
//    //    bool r = false;
//    //    ref = search(2);
//    //    if (ref > 0)
//    //    {
//    //        r = confirm("Return Publication?");
//    //        if (r)
//    //        {
//    //            Date temp = getPub(ref)->checkoutDate();
//    //            Date today;
//    //            if (today - temp > 15)
//    //            {
//    //                int penalty = (today - temp) - 15;
//    //                double price = penalty * 0.5;
//    //                // Please pay $4.00 penalty for being 8 days late!
//    //                cout << "Please pay " << "$";
//    //                cout.setf(ios::fixed);
//    //                cout.width(3);
//    //                cout.precision(2);
//    //                cout << price << " penalty for being " << penalty << " days late!" << endl;
//    //            }
//    //            getPub(ref)->set(0);
//
//    //            cout << "Publication returned" << endl;
//    //            m_changed = true;
//    //        }
//    //    }
//    //}
//
//
//
//    //void LibApp::newPublication()
//    //{
//    //    //check if library is full
//    //    if (m_numpub == SENECA_LIBRARY_CAPACITY)
//    //    {
//    //        cout << "Library is at its maximum capacity!" << endl;
//    //    }
//
//    //    else
//    //    {
//    //        //add publication
//
//    //        cout << "Adding new publication to the library" << endl;
//    //        int selection = -1;
//
//    //        selection = m_publicationmenu.run();
//    //        switch (selection)
//    //        {
//    //        case 0:
//    //        {
//    //            cout << "Aborted!" << endl;
//    //            break;
//    //        }
//    //        case 1:
//    //        {
//    //            Publication* temp = new Book;
//    //            temp->read(cin);
//
//    //            if (cin)
//    //            {
//    //                bool r = confirm("Add this publication to the library?");
//    //                if (r == true)
//    //                {
//    //                    if (temp)
//    //                    {
//
//    //                        m_publication[m_numpub] = temp;
//    //                        m_publication[m_numpub]->setRef(m_librefapp + 1);
//    //                        m_librefapp++;
//    //                        m_numpub++;
//    //                        m_changed = true;
//    //                        cout << "Publication added" << endl;
//    //                    }
//    //                    else
//    //                    {
//    //                        cout << "Failed to add publication!" << endl;
//    //                        delete temp;
//    //                    }
//    //                }
//    //            }
//    //            else
//    //            {
//    //                cout.clear();
//    //                cout << "Aborted" << endl;
//    //            }
//    //            break;
//    //        }
//    //        case 2:
//    //        {
//    //            Publication* temp = new Publication;
//    //            temp->read(cin);
//
//    //            if (cin)
//    //            {
//    //                bool r = confirm("Add this publication to the library?");
//    //                if (r == true)
//    //                {
//    //                    if (temp)
//    //                    {
//    //                        m_publication[m_numpub] = temp;
//    //                        m_publication[m_numpub]->setRef(m_librefapp + 1);
//    //                        m_librefapp++;
//
//    //                        m_numpub++;
//    //                        m_changed = true;
//    //                        cout << "Publication added" << endl;
//    //                    }
//    //                    else
//    //                    {
//    //                        cout << "Failed to add publication!" << endl;
//    //                        delete temp;
//    //                    }
//    //                }
//    //            }
//    //            else
//    //            {
//    //                cout.clear();
//    //                cout << "Aborted" << endl;
//    //            }
//    //            break;
//    //        }
//    //        }
//
//
//    //    }
//    //}
//
