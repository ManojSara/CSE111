// $Id: relops.h,v 1.2 2022-01-11 12:06:50-08 - - $

//
// Assuming that for any given type T, there are operators
// bool operator< (const T&, const T&);
// bool operator== (const T&, const T&);
// as fundamental comparisons for type T, define the other
// six operators in terms of the basic ones.
//

#ifndef RELOPS_H
#define RELOPS_H

#ifdef TEMPLATE_OPERATOR_NE
template <typename value>
inline bool operator!= (const value& left, const value& right) {
   return not (left == right); 
}
#endif

template <typename value>
inline bool operator>  (const value& left, const value& right) {
   return right < left; 
}

template <typename value>
inline bool operator<= (const value& left, const value& right) {
   return not (right < left);
}

template <typename value>
inline bool operator>= (const value& left, const value& right) {
   return not (left < right); 
}

#endif

