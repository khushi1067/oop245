#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "TextFile.h"
using namespace std;
namespace seneca {
    Line::operator const char* () const {
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
    void seneca::TextFile::setEmpty()
    {
        delete[] m_textLines;
        m_textLines = nullptr;

        delete[] m_filename;
        m_filename = nullptr;

        m_noOfLines = 0;

    }
    void seneca::TextFile::setFilename(const char* fname, bool isCopy)
    {
        if (isCopy)
        {
            delete[] m_filename;
            m_filename = new char[strlen(fname) + 3];
            strcpy(m_filename, "C_");
            strcat(m_filename, fname);

        }
        else
        {
            delete[] m_filename;
            m_filename = new char[strlen(fname) + 1];
            strcpy(m_filename, fname);
        }
    }

    void seneca::TextFile::setNoOfLines()
    {
        int count = 0;
        ifstream fin(m_filename);
        if (fin.is_open())
        {
            while (fin)
            {
                if (fin.get()=='\n')
                {
                    count++;

                }

            }
            fin.close();

        }

        if (count==0)
        {
            setEmpty();

        }
        else
        {
            m_noOfLines = count + 1;
        }


    }

    void seneca::TextFile::loadText()
    {

        if (m_filename!=nullptr)
        {
            delete[] m_textLines;
            m_textLines = new Line[m_noOfLines];

            ifstream fin(m_filename);
            unsigned i = 0;

            if (fin.is_open())
            {
                string temp;
                while (getline(fin,temp))
                {
                    m_textLines[i] = temp.c_str();
                    i++;

                }
                fin.close();

            }
            m_noOfLines = i;

        }
    }

    void seneca::TextFile::saveAs(const char* fileName) const
    {
        if (fileName!=nullptr)
        {
            ofstream fout(fileName);

            if (fout.is_open())
            {
                for (unsigned i = 0; i < m_noOfLines; i++)
                {
                    fout << m_textLines[i].m_value << endl;

                }
                fout.close();

            }

        }


    }
    TextFile::TextFile(unsigned pageSize)
        : m_textLines(nullptr), m_filename(nullptr), m_noOfLines(0), m_pageSize(pageSize) {
        // No need to check pageSize > 0 here, it's valid to have pageSize as 0.
    }

    TextFile::TextFile(const char* filename, unsigned pageSize)
        : m_textLines(nullptr), m_filename(nullptr), m_noOfLines(0), m_pageSize(pageSize) {
        if (filename != nullptr && filename[0] != '\0') {
            setFilename(filename);
            setNoOfLines();
            loadText();
        }
    }




    /*neca::TextFile::TextFile(unsigned pageSize)
    {
        m_textLines = nullptr;
        m_filename = nullptr;
        m_noOfLines = 0;
        m_pageSize = 0;

        if (pageSize>0)
        {
            m_pageSize = pageSize;

        }

       
    }

    seneca::TextFile::TextFile(const char* filename, unsigned pageSize)
    {
        m_textLines = nullptr;
        m_filename = nullptr;
        m_noOfLines = 0;
        m_pageSize = 0;

        if (pageSize>0)
        {
            m_pageSize = pageSize;

        }
        if (filename != nullptr && filename[0] != '\0')
        {
            setFilename(filename);
            setNoOfLines();
            loadText();

        }

    }*/
    TextFile::TextFile(const TextFile& src)
        : m_textLines(nullptr), m_filename(nullptr), m_noOfLines(0), m_pageSize(src.m_pageSize) {
        if (src.m_filename != nullptr && src.m_filename[0] != '\0') {
            setFilename(src.m_filename, true); // Copy with "C_" prefix
            saveAs(m_filename); // Save content from src to this object
            setNoOfLines();
            loadText();
        }
    }
    /*seneca::TextFile::TextFile(const TextFile& src)
    {
        m_textLines = nullptr;
        m_filename = nullptr;
        m_noOfLines = 0;
        m_pageSize = src.m_pageSize;
        if (this!=&src && src.m_filename!=nullptr && src.m_filename[0]!='\0')
        {
            setFilename(src.m_filename, true);
            src.saveAs(m_filename);
            setNoOfLines();
            loadText();

        }


    }*/


    TextFile& TextFile::operator=(const TextFile& src) {
        if (this != &src) { // Check for self-assignment
            // Clear current object
            delete[] m_textLines;
            m_textLines = nullptr;
            delete[] m_filename;
            m_filename = nullptr;
            m_noOfLines = 0;

            // Copy from src
            m_pageSize = src.m_pageSize;
            if (src.m_filename != nullptr && src.m_filename[0] != '\0') {
                setFilename(src.m_filename, true); // Copy with "C_" prefix
                saveAs(m_filename); // Save content from src to this object
                setNoOfLines();
                loadText();
            }
        }
        return *this;
    }
    
    //TextFile& TextFile::operator=(const TextFile& src)
    //{
    //    if (this != &src && this->m_filename != nullptr && src.m_filename != nullptr && this->m_filename[0] != '\0' && src.m_filename[0] != '\0')

    //    {
    //        delete[] m_textLines;
    //        m_textLines = nullptr;
    //        src.saveAs(m_filename);
    //        setNoOfLines();
    //        loadText();

    //    }
    //    return *this;


    //    // TODO: insert return statement here
    //}


    TextFile::~TextFile() {
        delete[] m_filename;
        m_filename = nullptr;
        delete[] m_textLines;
        m_textLines = nullptr;
    }
   /* seneca::TextFile::~TextFile()
    {
        delete[] m_filename;
        m_filename = nullptr;

        delete[] m_textLines;
        m_textLines = nullptr;


    }*/

    std::ostream& seneca::TextFile::view(std::ostream& ostr) const
    {
        if (m_filename != nullptr && m_filename[0] != '\0')
        {
            ostr << m_filename << endl;
            ostr.fill('=');
            ostr.width(strlen(m_filename));
            ostr << '=' << endl;
            for (unsigned i = 0; i < m_noOfLines; i++)
            {
                ostr << m_textLines[i].m_value << endl;
                if (m_pageSize != 0 && (i + 1) % m_pageSize == 0)
                {
                    ostr << "Hit ENTER to continue...";
                    cin.get();
                }
            }
        }
        return ostr;


        // TODO: insert return statement here
    }

    std::istream& seneca::TextFile::getFile(std::istream& istr)
    {

        string fname;
        getline(istr, fname);
        setFilename(fname.c_str());
        setNoOfLines();
        loadText();
        return istr;
        // TODO: insert return statement here
    }

    seneca::TextFile::operator bool() const
    {
        return m_filename != nullptr;
    }

    unsigned seneca::TextFile::lines() const
    {

        return m_noOfLines;
    }

    const char* seneca::TextFile::name() const
    {
        return m_filename;
    }

    const char* seneca::TextFile::operator[](unsigned index) const
    {
        return m_filename != nullptr ? m_textLines[index % m_noOfLines].m_value : nullptr;

    }

    ostream& operator<<(ostream& ostr, const TextFile& text) {
        return text.view(ostr);
    }

    // Overloaded operator>>
    istream& operator>>(istream& istr, TextFile& text) {
        return text.getFile(istr);
    }
    /*std::ostream& seneca::operator<<(std::ostream& ostr, const TextFile& text)
    {
        return text.view(ostr);

    }

    std::istream& seneca::operator>>(std::istream& istr, TextFile& text)
    {
        return text.getFile(istr);

    }*/
}