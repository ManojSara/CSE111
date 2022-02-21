// $Id: listmap.tcc,v 1.15 2019-10-30 12:44:53-07 - - $

#include "listmap.h"
#include "debug.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename key_t, typename mapped_t, class less_t>
listmap<key_t,mapped_t,less_t>::~listmap() {
   DEBUGF ('l', reinterpret_cast<const void*> (this));
}

//
// iterator listmap::insert (const value_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::insert (const value_type& pair) {
   DEBUGF ('l', &pair << "->" << pair);
   for (auto i = begin(); i != end(); ++i) {
      if (not (xless(i->first, pair.first))) {
         if (not (xless(pair.first, i->first))) {
            i->second = pair.second;
            return i;
         } else {
            node *in = node(i.where, i.where->prev, pair);
            i.where->prev->next = in;
            i.where->prev = in;
            return --i;
         }
      }
   }
   node *in = node(end().where, end().where->prev, pair);
   end().where->prev->next = in;
   end().where->prev = in;
   return --end();
}

//
// listmap::find(const key_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::find (const key_type& that) {
   DEBUGF ('l', that);
   for (auto i = begin(); i != end(); ++i) {
      if ((not (xless(i->first, that))) and (not (xless(that, i->first)))) {
         return i;
      }
   }
   return end();
}

//
// iterator listmap::erase (iterator position)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::erase (iterator position) {
   DEBUGF ('l', &*position);
   return iterator();
}


