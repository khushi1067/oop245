/*/////////////////////////////////
Name - Khushi Abhay Bhandari
Email - kabhandari@myseneca.ca
Student ID - 106774235
Date - 05-23-2024
*/////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "File.h"

namespace seneca {
   FILE* fptr;
   bool openFile(const char filename[]) {
      fptr = fopen(filename, "r");
      return fptr != NULL;
   }
   int noOfRecords() {
      int noOfRecs = 0;
      char ch;
      while (fscanf(fptr, "%c", &ch) == 1) {
         noOfRecs += (ch == '\n');
      }
      rewind(fptr);
      return noOfRecs;
   }
   bool read(char* name[])
   {
       return false;
   }
   void closeFile() {
      if (fptr) fclose(fptr);
   }
 
   //function to read name 
   bool read(char name[]) {

       int readEmpName = fscanf(fptr, "%[^\n]\n", name);
           return readEmpName == 1;

   }

   //function to read employee Number
   bool read(int& empNo) {

       int readEmpNo = fscanf(fptr, "%d,", &empNo);
       return  readEmpNo==1;
          
   }

   //function to read employee salary
   bool read(double& salary) {
      
       int readEmpSalary = fscanf(fptr, "%lf,", &salary);
       return readEmpSalary== 1;

   }
  
}