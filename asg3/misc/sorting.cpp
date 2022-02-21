// $Id: sorting.cpp,v 1.6 2022-02-06 18:29:10-08 - - $

// Example of how to use xless object on a pair of strings.

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct name {
   string first;
   string last;
};
bool operator< (const name& one, const name& two) {
   if (one.last < two.last) return true;
   if (one.last > two.last) return false;
   return one.first < two.first;
}
ostream& operator<< (ostream& out, const name& who) {
   return out << who.first << " " << who.last;
}

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

template <typename Type>
void print (const Type& cont) {
   for (const auto& i: cont) cout << " " << i;
   cout << endl;
}

vector<string> vs {"hello", "world", "foo", "bar", "baz"};
vector<int> vi {3, 1, 4, 55, 77, -8};

vector<name> vn {{"John","Doe"},
                 {"Mary","Roe"},
                 {"Jim","Roe"},
                 {"John","Roe"},
                 {"Jane","Doe"}};

int main () {
   sort (vs.begin(), vs.end());
   print (vs);
   sort (vs.begin(), vs.end(), xgreater<string>());
   print (vs);
   sort (vi.begin(), vi.end(), xgreater<int>());
   print (vi);
   sort (vi.begin(), vi.end(), xless<int>());
   print (vi);
   sort (vn.begin(), vn.end(), xless<name>());
   print (vn);
}

//TEST// testxless >testxless.out 2>&1
//TEST// mkpspdf testxless.ps testxless.cpp* testxless.out

