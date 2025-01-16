#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <cstring>
#include <string.h>
#include<iostream>
#include "Text.h"

using namespace std;

namespace seneca {
   int Text::getFileLength() const {
      int len = 0;
      ifstream fin(m_filename);
      while (fin) {
         fin.get();
         len += !!fin;
      }
      return len;
   }


    //rule of 3
    Text::Text(const char* filename) 
    {
        m_filename = nullptr;
        m_content = nullptr;

        if (filename) 
        {
            m_filename = new char[strlen(filename) + 1];

            strcpy(m_filename, filename);
            read();
        }
    }

    // Copy Constructor
    Text::Text(const Text& src) 
    {
        m_filename = nullptr;
        m_content = nullptr;

        if (src.m_filename) 
        {
            m_filename = new char[strlen(src.m_filename) + 1];
            strcpy(m_filename, src.m_filename);

            read();
        }
    }
 
    // Destructor
    Text::~Text() 
    {
        delete[] m_filename;

        delete[] m_content;
    }



    // operator overload =
    Text& Text::operator=(const Text& src)
    {

        if (this != &src) 
        {
            //delete allocated memory 
            delete[] m_filename;
            delete[] m_content;

            //set variables to null pointer
            m_filename = nullptr;
            m_content = nullptr;

            
            if (src.m_filename) 
            {
                //sllocate memory
                m_filename = new char[strlen(src.m_filename) + 1];
                
                //copy filename to argument
                strcpy(m_filename, src.m_filename);
                
                //read function to read content of file
                read();
            }
        }
        return *this;
    }

    // operator overload [] (array index)
    const char& Text::operator[](int index) const 
    {
        return m_content[index];
    }

    // Read file content
    void Text::read() 
    {
        //delete allocated memory         
        delete[] m_content;

        //set to nullptr
        m_content = nullptr;

        //read content of file character by character
        std::ifstream file(m_filename);
        if (file)
        {
            int length = getFileLength();

            //condition to check if file has content
            if (length > 0) 
            {
                //allocate memory
                m_content = new char[length + 1];
                
                //read content
                file.read(m_content, length);
                
                //set ot to null ptr
                m_content[length] = '\0';
            }
        }
    }



    //write method
    void Text::write(std::ostream& os) const 
    {
        //if m_content is not null
        if (m_content!=nullptr) 
        {
            //insert content using << operator 
            os << m_content;
        }
    }


    // operator overload for insertion
    std::ostream& operator<<(std::ostream& os, const Text& text) 
    {

        text.write(os);
        return os;
    }

} // namespace seneca
