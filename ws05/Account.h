/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 06-08-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#ifndef SENECA_ACCOUNT_H_
#define SENECA_ACCOUNT_H_
#include <iostream>

namespace seneca 
{
   class Account 
   {
      int m_number;
      double m_balance; 
      void setEmpty();
   public:
      Account();
      Account(int number, double balance);
      std::ostream& display()const;

      //type conversion operators
      operator bool()const;
      operator int()const;
      operator double()const;

      // Unary operator
      bool operator ~()const;

      
       // Assignment operators
      Account& operator=(int);
      Account& operator=(Account&);

      // Binary member operators
      Account& operator+=(double);
      Account& operator-=(double);
      Account& operator<<(Account&);
      Account& operator>>(Account&);


   };

   // Binary helper operators
   double operator+(const Account&, const Account&);
   double& operator+=(double&, const Account&);
   
   
}
#endif // SENECA_ACCOUNT_H_