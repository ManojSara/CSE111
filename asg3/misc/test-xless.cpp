// $Id: test-xless.cpp,v 1.6 2022-02-06 17:33:46-08 - - $

// Example of how to use xless object on a pair of strings.

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

template <typename Type>
struct xless {
   bool operator() (const Type &left, const Type &right) const {
      return left < right;
   }
};

template <typename Type>
struct xgreater {
   bool operator() (const Type &left, const Type &right) const {
      return left > right;
   }
};

template <typename Type, class Less=xless<Type>>
void compare (const Type &left, const Type &right) {
   Less less;
   cout << boolalpha;
   bool is_less = less (left, right);
   bool is_greater = less (right, left);
   bool is_equal = not is_less and not is_greater;
   cout << endl;
   cout << __PRETTY_FUNCTION__ << endl;
   cout << " (" << left << ", " << right << "):" << endl;
   cout << "is_less = " << is_less << endl;
   cout << "is_greater = " << is_greater << endl;
   cout << "is_equal = " << is_equal << endl;
}

int main () {
   compare (string ("hello"), string ("world"));
   compare (string ("qwert"), string ("qwert"));
   compare (string ("zxcvb"), string ("asdfg"));
   compare<string,xgreater<string>> ("hello", "world");
   compare<string,xgreater<string>> ("qwert", "qwert");
   compare<string,xgreater<string>> ("zxcvb", "asdfg");
   return 0;
}

//TEST// testxless >testxless.out 2>&1
//TEST// mkpspdf testxless.ps testxless.cpp* testxless.out

