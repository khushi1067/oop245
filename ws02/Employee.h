/*/////////////////////////////////
Name - Khushi Abhay Bhandari
Email - kabhandari@myseneca.ca
Student ID - 106774235
Date - 05-23-2024
*/////////////////////////////////
#ifndef SENECA_EMPLOYEE_H_
#define SENECA_EMPLOYEE_H_

#define DATAFILE "employees.csv"
namespace seneca {
    struct Employee {
        char* m_name;
        int m_empNo;
        double m_salary;
    };
    //sorts the dynamic array of employees based on the GPA of the employees.
    void sort();

    // loads a employee structue with its values from the file
    bool load(Employee& employee);

    // allocates the dyanmic array of employees and loads all the file
    // recoreds into the array
    bool load();

 
    // displays a employee record on the screen:
    void display(const Employee& employee);
    
    // first sorts the employees then displays all the employees on the screen
    void display();
    
   
    // deallocate the memory 
    void deallocateMemory();
}
#endif // SENECA_EMPLOYEE_H_