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
      ubi.insert(*ubi.end(), digit);
      that /= 10;
   }
   DEBUGF ('~', this << " -> " << uvalue)
}

ubigint::ubigint (const string& that) {
   ubigvalue_t ubi;
   uint8_t dig = 0;
   for (char digit: that) {
      dig = stoi(digit);
      ubi.insert(*ubi.end(), dig);
   }
   DEBUGF ('~', "that = \"" << that << "\"");
}

ubigint ubigint::operator+ (const ubigint& that) const {
   ubigint result = new ubigint(); 
   uint8_t length = uvalue.length();
   if (that.uvalue.length() > length)
   {
      length = that.uvalue.length();
   }
   uint8_t remainder = 0;
   uint8_t total = 0;
   for (uint8_t i = 0; i < length; i++)
   {
      total = uvalue[i] + that.uvalue[i] + remainder;
      remainder = 1;
      if (total >= 10)
      {
         remainder = 1;
         total -= 10;
      }
      result.push_back(total);
   }
   DEBUGF ('u', *this << "+" << that);
   DEBUGF ('u', result);
   return result;
}

ubigint ubigint::operator- (const ubigint& that) const {
   if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   return ubigint (uvalue - that.uvalue);
}

ubigint ubigint::operator* (const ubigint& that) const {
   return ubigint (uvalue * that.uvalue);
}

void ubigint::multiply_by_2() {
   uvalue *= 2;
}

void ubigint::divide_by_2() {
   uvalue /= 2;
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
   return uvalue == that.uvalue;
}

bool ubigint::operator< (const ubigint& that) const {
   return uvalue < that.uvalue;
}

void ubigint::print() const {
   DEBUGF ('p', this << " -> " << *this);
   cout << uvalue;
}

ostream& operator<< (ostream& out, const ubigint& that) { 
   return out << "ubigint(" << that.uvalue << ")";
}

