/*/////////////////////////////////
Name - Khushi Abhay Bhandari
Email - kabhandari@myseneca.ca
Student ID - 106774235
Date - 05-23-2024
*/////////////////////////////////
#ifndef SENECA_FILE_H_
#define SENECA_FILE_H_
namespace seneca {

   bool openFile(const char filename[]);
   void closeFile();
   int noOfRecords();

   //declating prototypes

   //to read name (charcater c string)
    bool read(char name[]);    

   //to read employee number
    bool read(int& empNo);
      
    //to read employee salary
    bool read(double& salary);

 

}
#endif // !SENECA_FILE_H_
