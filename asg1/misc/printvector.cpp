// $Id: printvector.cpp,v 1.9 2022-01-12 17:32:55-08 - - $

#include <iostream>
#include <vector>
using namespace std;

// Example of printing a vector of uint8_t.

ostream& operator<< (ostream& out, const vector<uint8_t>& vec) {
   for (uint8_t byte: vec) out << static_cast<int> (byte);
   return out;
}

void print_rev1 (const vector<uint8_t>& vec) {
   for (auto itor = vec.crbegin(); itor != vec.crend(); ++itor) {
      cout << static_cast<int> (*itor);
   }
}

void print_rev2 (const vector<uint8_t>& vec) {
   // Note: ssize_t, not size_t, because must stop at -1, not 0.
   for (ssize_t index = vec.size() - 1; index >= 0; --index) {
      cout << static_cast<int> (vec[index]);
   }
}

template <typename Itor>
void print_itor (Itor begin, Itor end) {
   for (; begin != end; ++begin) cout << static_cast<int> (*begin);
}

int main() {
   vector<uint8_t> data {6, 3, 8, 9, 0, 2, 1};
   cout << "operator<<: " << data << endl;
   cout << "print_rev1: "; print_rev1 (data); cout << endl;
   cout << "print_rev2: "; print_rev2 (data); cout << endl;
   cout << "print fwd: "; print_itor (data.cbegin(), data.cend());
   cout << endl;
   cout << "print rev: "; print_itor (data.crbegin(), data.crend());
   cout << endl;
}

//TEST// ./printvector >printvector.out
//TEST// mkpspdf printvector.ps printvector.cpp printvector.out

