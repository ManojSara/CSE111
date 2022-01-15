// $Id: ubigint.h,v 1.4 2022-01-11 15:58:58-08 - - $

#ifndef UBIGINT_H
#define UBIGINT_H

#include <exception>
#include <iostream>
#include <limits>
#include <vector>
#include <utility>
using namespace std;

#include "debug.h"
#include "relops.h"

class ubigint {
   private:
      using ubigvalue_t = vector<uint8_t>;
      ubigvalue_t uvalue {};
   public:
      void multiply_by_2();
      void divide_by_2();

      ubigint() = default; // Need default ctor as well.
      ubigint (unsigned long);
      ubigint (const string&);

      ubigint operator+ (const ubigint&) const;
      ubigint operator- (const ubigint&) const;
      ubigint operator* (const ubigint&) const;
      ubigint operator/ (const ubigint&) const;
      ubigint operator% (const ubigint&) const;

      bool operator== (const ubigint&) const;
      bool operator<  (const ubigint&) const;

      void print() const;

   friend ostream& operator<< (ostream&, const ubigint&);
   friend ostream& operator<< (ostream&, const ubigint::ubigvalue_t&);
};

#endif

