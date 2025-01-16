#ifndef SENECA_HTMLTEXT_H__
#define SENECA_HTMLTEXT_H__
#include "Text.h"
#include<iostream>
using namespace std;


namespace seneca {
   class HtmlText :  public Text {
      char* m_title;
   public:

       //rule of 3
      HtmlText(const char* filename=nullptr, const char* title = nullptr);
      ~HtmlText();
      HtmlText(const HtmlText& src);

      //operator overload =
      HtmlText& operator=(const HtmlText& src);
      
      //write method
      void write(std::ostream& os) const override;


   };
}
#endif // !SENECA_HTMLTEXT_H__

