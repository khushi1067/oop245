/*******************************************************************

 Name        : Khushi Abhay Bhandari
 Email       : kabhandari@myseneca.ca
 Student ID  : 106774235
 Date        : 06-08-2024

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.

 ******************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Account.h"

using namespace std;
namespace seneca {
   void Account::setEmpty() {
      m_number = -1;
      m_balance = 0.0;
   }
   // New account
   Account::Account() {  
      m_number = 0;
      m_balance = 0.0;
   }
   Account::Account(int number, double balance ) {
      setEmpty();
      if (number >= 10000 && number <= 99999
         && balance > 0) {
         m_number = number;
         m_balance = balance;
      }
   }
   std::ostream& Account::display() const{
      if (*this) {  
         cout << " ";
         cout << m_number;
         cout << " | ";
         cout.width(12);
         cout.precision(2);
         cout.setf(ios::right);
         cout.setf(ios::fixed);
         cout << m_balance;
         cout.unsetf(ios::right);
         cout << " ";
      }
      else if(~*this) {
         cout << "  NEW  |         0.00 ";
      }
      else {
         cout << "  BAD  |    ACCOUNT   ";
      }
      return cout;
   }

   //type conversion operators
   Account::operator bool()const
   {
      return  m_number > 0;
   }

   Account::operator int() const 
   {
       
       return m_number;
   }

   Account::operator double() const 
   {
       
       return m_balance;
   }

   // Unary operator
   bool Account::operator~() const 
   {
       return m_number == 0;
   }

   // Assignment operators

   Account& Account::operator=(int number) 
   {
       if (m_number == 0) 
       {
           if (number >= 10000 && number <= 99999)
           {
               m_number = number;
           }
           else 
           {
               setEmpty();
           }
       }
       return *this;
   }

   Account& Account::operator=(Account& secondAccount) 
   {
       
       if (m_number == 0 && secondAccount)
       {
           m_number = secondAccount.m_number;
           m_balance = secondAccount.m_balance;
           secondAccount.m_number = 0;
           secondAccount.m_balance = 0.0;
       }
       return *this;
   }

   // Binary member operators
   Account& Account::operator+=(double amount)
   {
       if (*this && amount >= 0) {
           m_balance =m_balance+ amount;
       }
       return *this;
   }

   Account& Account::operator-=(double amount)
   {
       if (*this && amount >= 0 && m_balance >= amount)
       {
           m_balance =m_balance- amount;
       }
       return *this;
   }

   Account& Account::operator<<(Account& secondAccount)
   {
   
       if (this != &secondAccount && *this && secondAccount)
       {
           m_balance =m_balance+ secondAccount.m_balance;
           secondAccount.m_balance = 0.0;
       }
       return *this;
   }

   Account& Account::operator>>(Account& secondAccount) 
   {
       if (this != &secondAccount && *this && secondAccount)
       {
           secondAccount.m_balance =secondAccount.m_balance+ m_balance;
           m_balance = 0.0;
       }
       return *this;
   }

   // Binary helper operators
   double operator+(const Account& accountOne, const Account& accountTwo)
   {
       if (accountOne && accountTwo)
       {
           double result;
           result= (double)accountOne + (double)accountTwo;
           return result;
       }
       return 0.0;
   }

  double& operator+=(double& number, const Account& account) 
  {
       double& sum = number;
       sum += double(account);
       return sum;
   }
}
   

