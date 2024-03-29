// $Id: ubigint.cpp,v 1.3 2022-01-11 17:47:47-08 - - $
// Manoj Sara (msara), Manas Sara (mssara)

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
   while (uvalue.size() > 0)
   {
      uvalue.pop_back();
   }
   if (that == 0)
   {
      uvalue.push_back(0);
      return;
   }
   int digit = 0;
   while (that != 0)
   {
      digit = that % 10;
      uvalue.push_back(digit);
      that /= 10;
   }
}

ubigint::ubigint (const string& that) {
   DEBUGF ('~', "that = \"" << that << "\"");
   for (char digit: that) {
      if (not isdigit (digit)) {
         throw invalid_argument ("ubigint::ubigint(" + that + ")");
      }
      auto it = uvalue.begin();
      uvalue.insert(it, digit - '0');
   }
}

ubigint ubigint::operator+ (const ubigint& that) const {
   ubigint result;
   unsigned long length = uvalue.size();
   unsigned long shortl = that.uvalue.size();
   if (that.uvalue.size() > length)
   {
      shortl = length;
      length = that.uvalue.size();
   }
   int remainder = 0;
   int total = 0;
   for (unsigned long i = 0; i < length; i++)
   {
      if (i < shortl)
      {
         total = uvalue[i] + that.uvalue[i] + remainder;
      }
      else
      {
         if (length == uvalue.size())
         {
            total = uvalue[i] + remainder;
         }
         else
         {
            total = that.uvalue[i] + remainder;
         }
      }
      remainder = 0;
      if (total >= 10)
      {
         remainder = 1;
         total -= 10;
      }
      result.uvalue.push_back(total);
   }
   result.uvalue.push_back(remainder);
   while (result.uvalue.back() == 0 && result.uvalue.size() > 1)
   {
      result.uvalue.pop_back();
   }
   DEBUGF ('u', *this << "+" << that);
   DEBUGF ('u', result);
   return result;
}

ubigint ubigint::operator- (const ubigint& that) const {
   ubigint result;
   int remainder = 0;
   int total = 0;
   for (unsigned long i = 0; i < uvalue.size(); i++)
   {
      if (i < that.uvalue.size())
      {
         total = uvalue[i] - that.uvalue[i] - remainder;
      }
      else
      {
         total = uvalue[i] - remainder;
      }
      remainder = 0;
      if (total < 0)
      {
         total += 10;
         remainder = 1;
      }
      result.uvalue.push_back(total);
   }
   while (result.uvalue.back() == 0 && result.uvalue.size() > 1)
   {
      result.uvalue.pop_back();
   }
   //if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   return result;
}

ubigint ubigint::operator* (const ubigint& that) const {
   ubigint result;
   for (unsigned long i = 0; i < uvalue.size(); i++)
   {
      result.uvalue.push_back(0);
   }
   for (unsigned long i = 0; i < that.uvalue.size(); i++)
   {
      result.uvalue.push_back(0);
   }
   uint8_t carry = 0;
   uint8_t  digit = 0;
   for (unsigned long i = 0; i < uvalue.size(); i++)
   {
      carry = 0;
      for (unsigned long j = 0; j < that.uvalue.size(); j++)
      {
         digit = result.uvalue[i + j] +
                 (uvalue[i] * that.uvalue[j]) + carry;
         result.uvalue[i + j] = digit % 10;
         carry = digit / 10;
      }
      result.uvalue[i + that.uvalue.size()] = carry;
   }
   while (result.uvalue.back() == 0 && result.uvalue.size() > 1)
   {
      result.uvalue.pop_back();
   }
   return result;
}

void ubigint::multiply_by_2() {
   *this = *this + *this;
   return;
}

void ubigint::divide_by_2() {
   for (unsigned long i = 0; i < uvalue.size(); i++)
   {
      uvalue[i] /= 2;
      if (i < (uvalue.size() - 1))
      {
         if (uvalue[i + 1] % 2 == 1)
         {
            uvalue[i] += 5;
         }
      }
   }
   while (uvalue.back() == 0 && uvalue.size() > 1)
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
   DEBUGF ('/', "quotient = " << quotient);
   DEBUGF ('/', "remainder = " << remainder);
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
   for (unsigned long i = 0; i < uvalue.size(); i++)
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
   for (unsigned long i = uvalue.size(); i > 0; i--)
   {
      if (uvalue[i - 1] < that.uvalue[i - 1])
      {
         return true;
      }
      else if (uvalue [i - 1] > that.uvalue[i - 1])
      {
         return false;
      }
   }
   return false;
}

void ubigint::print() const {
   DEBUGF ('p', this << " -> " << *this);
   cout << *this;
}

ostream& operator<< (ostream& out, const ubigint& that) { 
   int inc = 0;
   for (auto rit = that.uvalue.rbegin();
      rit != that.uvalue.rend(); rit++)
   {
      out << static_cast<int>(*rit);
      inc++;
      if (inc == 69) {
         out << "\\" << endl;
         inc = 0;
      }
   }
   return out;
}

