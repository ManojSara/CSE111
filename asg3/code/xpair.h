// $Id: xpair.h,v 1.7 2021-12-20 12:56:53-08 - - $
// Manoj Sara (msara), Manas Sara (msara)

#ifndef XPAIR_H
#define XPAIR_H

#include <iostream>

using namespace std;

//
// Class xpair works like pair(c++).
//
// The implicitly generated members will work, because they just
// send messages to the first and second fields, respectively.
// Caution:  xpair() does not initialize its fields unless
// first_t and second_t do so with their default ctors.
//

template <typename first_t, typename second_t>
struct xpair {
   first_t first{};
   second_t second{};
   xpair() = default;
   xpair (const first_t& first_, const second_t& second_):
                first(first_), second(second_) {}
};

template <typename first_t, typename second_t>
ostream& operator<< (ostream& out,
                     const xpair<first_t,second_t>& pair) {
   out << "{" << pair.first << "," << pair.second << "}";
   return out;
}

#endif

