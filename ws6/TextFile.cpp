#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "TextFile.h"
using namespace std;
namespace seneca
{
   Line::operator const char* () const 
   {
      return (const char*)m_value;
   }

   Line& Line::operator=(const char* lineValue) {
      delete[] m_value;
      m_value = new char[strlen(lineValue) + 1];
      strcpy(m_value, lineValue);
      return *this;
   }
   Line::~Line() {
      delete[] m_value;
   }

  
   void TextFile::setEmpty()
   {
       delete[] m_textLines;
       m_textLines = nullptr;

       delete[] m_filename;
       m_filename = nullptr;

       m_noOfLines = 0;

   }

   

   void TextFile::setFilename(const char* fname, bool isCopy)
   {
       if (isCopy)
       {
           m_filename = new char[strlen(fname) + 3];
           strcpy(m_filename, "C_");
           strcat(m_filename, fname);

       }
       else
       {
           m_filename = new char[strlen(fname) + 1];
           strcpy(m_filename, fname);

       }




   }

   void TextFile::setNoOfLines()
   {
       ifstream file(m_filename);

       while (file)
       {
           m_noOfLines += (file.get() == '\n');


       }

       if (m_noOfLines==0)
       {
           delete[]m_filename;
           m_filename = nullptr;

       }
       else
       {
           m_noOfLines += 1;
       }



   }

   void TextFile::loadText()
   {
       int i = 0;
       if (m_filename != nullptr) {
           delete[] m_textLines;
           m_textLines = nullptr;
           m_textLines = new Line[m_noOfLines];
           ifstream file(m_filename);
           string line;
           while (getline(file, line)) {
               m_textLines[i++] = line.c_str();
           }
           m_noOfLines = i;
       }
   }

   void TextFile::saveAs(const char* fileName) const
   {

       ofstream file(fileName);
       int a = m_noOfLines;
       for (int i = 0; i < a; i++) {
           file << m_textLines[i] << endl;
       }
   }
   TextFile::TextFile(unsigned pageSize) :m_pageSize{ pageSize } {}

   TextFile::TextFile(const char* filename, unsigned pageSize) {
       m_pageSize = pageSize;
       setEmpty();
       if (filename != nullptr) {
           setFilename(filename);
           setNoOfLines();
           loadText();
       }
   }

   TextFile::TextFile(const TextFile& src) {
       m_pageSize = src.m_pageSize;
       setEmpty();
       if (src.m_filename != nullptr) {
           setFilename(src.m_filename, true);
           src.saveAs(m_filename);
           setNoOfLines();
           loadText();
       }
   }

   TextFile& TextFile::operator=(const TextFile& src) {
       if (this != &src) {
           delete[]m_textLines;
           m_textLines = nullptr;

           if (src.m_filename != nullptr) {
               src.saveAs(m_filename);
               setNoOfLines();
               loadText();
           }
       }
       return *this;
   }

   TextFile::~TextFile() {
       setEmpty();
   }

   unsigned TextFile::lines()const {
       return m_noOfLines;
   }

   std::ostream& TextFile::view(std::ostream& ostr) const {
       if (m_textLines != nullptr) {
           ostr << m_filename << std::endl;
           int a = std::strlen(m_filename); // Using standard library function
           for (int j = 0; j < a; j++) {
               ostr << "=";
           }
           ostr << std::endl;
           int b = m_noOfLines;
           for (int i = 0; i < b; i++) {
               ostr << m_textLines[i] << std::endl;
               if ((i + 1) % m_pageSize == 0) {
                   ostr << "Hit ENTER to continue...";
                   std::cin.ignore(1000, '\n');
               }
           }
       }
       return ostr;
   }


   TextFile::operator bool()const {
       bool isValid = false;
       if (m_textLines != nullptr) {
           isValid = true;
       }
       return isValid;
   }

   const char* TextFile::name()const {
       return m_filename;
   }

   std::istream& TextFile::getFile(std::istream& istr) {
       string get;
       getline(istr, get);
       setFilename(get.c_str());
       setNoOfLines();
       loadText();
       return istr;
   }

   const char* TextFile::operator[](unsigned index)const {
       const char* line = nullptr;
       if (*this) {
           line = m_textLines[index % m_noOfLines];
       }
       return line;
   }

   std::ostream& operator<<(std::ostream& ostr, const TextFile& text) {
       return text.view(ostr);
   }

   std::istream& operator>>(std::istream& istr, TextFile& text) {
       return text.getFile(istr);
   }



  

 
}