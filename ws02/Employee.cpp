/*/////////////////////////////////
Name - Khushi Abhay Bhandari
Email - kabhandari@myseneca.ca
Student ID - 106774235
Date - 05-23-2024
*/////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Employee.h"
#include "File.h"
using namespace std;
namespace seneca {

   int noOfEmployees;
   Employee* employees;


   void sort() {
      int i, j;
      Employee temp;
      for (i = noOfEmployees - 1; i > 0; i--) {
         for (j = 0; j < i; j++) {
            if (employees[j].m_empNo > employees[j + 1].m_empNo) {
               temp = employees[j];
               employees[j] = employees[j + 1];
               employees[j + 1] = temp;
            }
         }
      }
   }

   bool load(Employee& employee) {
       bool ok = false;
       char name[128];

       //check if all 3 read functions working
       if (read(employee.m_empNo))
       {
           if (read(employee.m_salary))
           {
               if (read(name))
               {
                   //allocate memory and 
                   //find length of string and +1 for null terminator
                   employee.m_name = new char[strlen(name) + 1];

                   //copy value from local paramater name to newly 
                   //allocated memory employee.name
                   strcpy(employee.m_name, name);
                   
                   //returns true 
                   ok = true;


               }

           }

       }
       return ok;
   }
                 
   //function that receives no parameter *const*
   bool load() {
       bool ok = false;
       int i = 0;

       //use openFile funstion
       if (openFile(DATAFILE)) {

           //get noOfRecords and store it in a global variable called noOfEmployees
           noOfEmployees = noOfRecords();

           //allocate memory 
           employees = new Employee[noOfEmployees];

           //load record (use for loop)
           for (i = 0; i < noOfEmployees; i++) {

                  //if file not loaded properly return false
               if (!load(employees[i])) { 
                   cout<< "Error: incorrect number of records read; the data is possibly corrupted" <<endl;
                   ok = false;
                   break;
               }
           }
                   
           //if sucessfully loop through every employee return true
           if (i == noOfEmployees) { 
               ok = true;
           }
          

           closeFile();
       }
       else {
           std::cout << "Could not open data file: " << DATAFILE << std::endl;
       }

       return ok;
   }


       

   void display(const Employee& emp)
   {
       cout << emp.m_empNo << ": " << emp.m_name << ", " << emp.m_salary << endl;

       

   }

       void display()
       {
           //display header
           cout << "Employee Salary report, sorted by employee number" << endl;
           cout << "no- Empno, Name, Salary" << endl;
           cout << "------------------------------------------------" << endl;
          
            //sort data
           sort();
           
           //loop through data and display
           for (int i = 0; i < noOfEmployees; i++)
           {
               cout << (i + 1) << "- ";

             
               display(employees[i]);
               
           }

       }

       //deallocate memory
       void deallocateMemory()
       {
           for (int i = 0; i <noOfEmployees; i++)
           {
               delete[] employees[i].m_name;

           }
           delete[] employees;
       }
   }
  


