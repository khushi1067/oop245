#define _CRT_SECURE_NO_WARNINGS

#ifndef SENECA_TEXT_H__
#define SENECA_TEXT_H__
#include <iostream>
#include<cstring>
#include<string.h>

using namespace std;
namespace seneca 
{
   class Text 
   {
      char* m_filename ;
      char* m_content ;
      int getFileLength()const;
   
   protected:
   
       const char& operator[](int index)const;

   public:

       Text(const char* filename=nullptr);

      Text(const Text& src);
      Text& operator=(const Text& src);
      ~Text();

      void read();
      virtual void write(std::ostream& os)const;
   };
   std::ostream& operator<<(std::ostream& os, const Text& text);

}
#endif // !SENECA_PERSON_H__



