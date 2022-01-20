// $Id: ubigint.cpp,v 1.3 2022-01-11 17:47:47-08 - - $

#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
#include <string>
using namespace std;

#include "debug.h"
#include "ubigint.h"

ubigint::ubigint (unsigned long that): uvalue (that) {
   ubigvalue_t ubi;
   uint8_t digit = 0;
   while (that != 0)
   {
      digit = that % 10;
      ubi.push_back(digit);
      that /= 10;
   }
   //DEBUGF ('~', this << " -> " << uvalue)
}

ubigint::ubigint (const string& that) {
   ubigvalue_t ubi;
   uint8_t number = stoi(that, nullptr);
   uint8_t digit = 0;
   while (number != 0)
   {
      digit = number % 10;
      ubi.push_back(digit);
      number /= 10;
   }
   //DEBUGF ('~', "that = \"" << that << "\"");
}

ubigint ubigint::operator+ (const ubigint& that) const {
   ubigint result; 
   uint8_t length = uvalue.size();
   if (that.uvalue.size() > length)
   {
      length = that.uvalue.size();
   }
   int remainder = 0;
   int total = 0;
   for (uint8_t i = 0; i < length; i++)
   {
      total = uvalue[i] + that.uvalue[i] + remainder;
      remainder = 1;
      if (total >= 10)
      {
         remainder = 1;
         total -= 10;
      }
      result.uvalue.push_back(total);
   }
   //DEBUGF ('u', *this << "+" << that);
   //DEBUGF ('u', result);
   return result;
}

ubigint ubigint::operator- (const ubigint& that) const {
   ubigint result;
   int remainder = 0;
   int total = 0;
   for (uint8_t i = 0; i < uvalue.size(); i++)
   {
      total = uvalue[i] - that.uvalue[i] - remainder;
      remainder = 0;
      if (total < 0)
      {
         total += 10;
         remainder = 1;
      }
      result.uvalue.push_back(total);
   }
   while (result.uvalue.back() == 0)
   {
      result.uvalue.pop_back();
   }
   //if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   return result;
}

ubigint ubigint::operator* (const ubigint& that) const {
   ubigint result;
   result.uvalue.reserve(uvalue.size() + that.uvalue.size());
   int carry = 0;
   int digit = 0;
   for (uint8_t i = 0; i < uvalue.size(); i++)
   {
      carry = 0;
      for (uint8_t j = 0; j < that.uvalue.size(); j++)
      {
         digit = result.uvalue[i + j] +
                 (uvalue[i] * that.uvalue[j]) + carry;
         result.uvalue[i + j] = digit % 10;
         carry = digit / 10;
      }
      result.uvalue[i + that.uvalue.size()] = carry;
   }
   return result;
}

void ubigint::multiply_by_2() {
   int carry = 0;
   int digit = 0;
   for (uint8_t i = 0; i < uvalue.size(); i++)
   {
      digit = (uvalue[i] * 2) + carry;
      carry = 0;
      if (digit >= 10)
      {
         digit -= 10;
         carry = 1;
      }
      uvalue[i] = digit;
   }
   if (carry)
   {
      uvalue.push_back(1);
   }
   return;
}

void ubigint::divide_by_2() {
   for (uint8_t i = 0; i < uvalue.size(); i++)
   {
      uvalue[i] /= 2;
      if (uvalue[i + 1] % 2 == 1)
      {
         uvalue[i] += 5;
      }
   }
   while (uvalue.back() == 0)
   {
      uvalue.pop_back();
   }
   return;
}


struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, const ubigint& divisor_) {
   // NOTE: udivide is a non-member function.
   ubigint divisor {divisor_};
   ubigint zero {0};
   if (divisor == zero) throw domain_error ("udivide by zero");
   ubigint power_of_2 {1};
   ubigint quotient {0};
   ubigint remainder {dividend}; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (power_of_2 > zero) {
      if (divisor <= remainder) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   //DEBUGF ('/', "quotient = " << quotient);
   //DEBUGF ('/', "remainder = " << remainder);
   return {.quotient = quotient, .remainder = remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   return udivide (*this, that).quotient;
}

ubigint ubigint::operator% (const ubigint& that) const {
   return udivide (*this, that).remainder;
}

bool ubigint::operator== (const ubigint& that) const {
   if (uvalue.size() != that.uvalue.size())
   {
      return false;
   }
   for (uint8_t i = 0; i < uvalue.size(); i++)
   {
      if (uvalue[i] != that.uvalue[i])
      {
         return false;
      }
   }
   return true;
}

bool ubigint::operator< (const ubigint& that) const {
   if (uvalue.size() < that.uvalue.size())
   {
      return true;
   }
   else if (uvalue.size() > that.uvalue.size())
   {
      return false;
   }
   for (uint8_t i = 0; i < uvalue.size(); i++)
   {
      if (uvalue[i] < that.uvalue[i])
      {
         return true;
      }
      else if (uvalue[i] > that.uvalue[i])
      {
         return false;
      }
   }
   return false;
}

void ubigint::print() const {
   //DEBUGF ('p', this << " -> " << *this);
   cout << *this;
}

ostream& operator<< (ostream& out, const ubigint& that) { 
   int inc = 0;
   for (auto rit = that.uvalue.rbegin();
        rit != that.uvalue.rend(); rit++)
   {
      out << *rit;
      inc++;
      if (inc == 68) {
         out << "/\n";
         inc = 0;
      }
   }
   return out;
}

