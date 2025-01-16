#define _CRT_SECURE_NO_WARNINGS

#include "HtmlText.h"
#include <iostream>
#include <cstring>
#include "HtmlText.h"

namespace seneca 
{
    //class inherited fron text
    //rule of three
    // Constructor

    HtmlText::HtmlText(const char* filename, const char* title) : Text(filename)
    {
        //set m_title to null ptr
        m_title=nullptr;
        
        //if title
        if (title) 
        {
            //allocate memory
            m_title = new char[strlen(title) + 1];

            //copy title to argument
            strcpy(m_title, title);
        }
    }

    // Copy Constructor
    HtmlText::HtmlText(const HtmlText& src) : Text(src)
    {
        m_title = nullptr;

        if (src.m_title) 
        {
            m_title = new char[strlen(src.m_title) + 1];
            strcpy(m_title, src.m_title);
        }
    }

    // Destructor
    HtmlText::~HtmlText()
    {
        delete[] m_title;
    }


    // Copy Assignment Operator
    HtmlText& HtmlText::operator=(const HtmlText& src) 
    {
        if (this != &src)
        {
            Text::operator=(src);

            delete[] m_title;
            m_title = nullptr;

            if (src.m_title) 
            {
                m_title = new char[strlen(src.m_title) + 1];
                strcpy(m_title, src.m_title);
         }
        }
        return *this;
    }

    // Override write function
    void HtmlText::write(std::ostream& os) const
    {

        bool flag = false;
        
        //open tages for html page
        os << "<html><head><title>";
        
        
        if (m_title) 
        {
            os << m_title;
        }

        os << "</title></head>\n<body>\n";

        if (m_title) 
        {
            os << "<h1>" << m_title << "</h1>\n";
        }

        for (int i = 0; (*this)[i] != '\0'; ++i) 
        {
            switch ((*this)[i]) 
            {
            case '<':
                os << "&lt;";
                flag = false;
                break;
            case '>':
                os << "&gt;";
                flag = false;
                break;
            case '\n':
                os << "<br />\n";
                flag = false;
                break;
            case ' ':
                if (flag) 
                {
                    os << "&nbsp;";
                }
                else 
                {
                    flag = true;
                    os << ' ';
                }
                break;
            default:
                flag = false;
                os << (*this)[i];
                break;
            }
        }
        os << "</body>\n</html>";
    }

} // namespace seneca
