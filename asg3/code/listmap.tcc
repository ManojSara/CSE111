// $Id: listmap.tcc,v 1.15 2019-10-30 12:44:53-07 - - $
// Manoj Sara (msara), Manas Sara (msara)

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
   while (not empty()) erase (begin());
}

//
// iterator listmap::insert (const value_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::insert (const value_type& pair) {
   DEBUGF ('l', &pair << "->" << pair);
   node *temp = anchor()->next;
   while (temp != anchor()) {
      if (not (less(temp->value.first, pair.first))) {
         if (not (less(pair.first, temp->value.first))) {
            temp->value.second = pair.second;
            return iterator(temp);
         } else {
            node *in = new node (temp, temp->prev, pair);
            temp->prev->next = in;
            temp->prev = in;
            return iterator(temp->prev);
         }
      }
      temp = temp->next;
   }
   node *in = new node(temp, temp->prev, pair);
   temp->prev->next = in;
   temp->prev = in;
   return iterator(temp->prev);
}

//
// listmap::find(const key_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::find (const key_type& that) {
   DEBUGF ('l', that);
   node *temp = anchor()->next;
   while (temp != anchor()) {
      if ((not (less(temp->value.first, that))) and
          (not (less(that, temp->value.first)))) {
         return iterator(temp);
      }
      temp = temp->next;
   }
   return iterator(anchor());
}

//
// iterator listmap::erase (iterator position)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::erase (iterator position) {
   DEBUGF ('l', &*position);
   position.where->prev->next = position.where->next;
   position.where->next->prev = position.where->prev;
   iterator ret = iterator(position.where->next);
   delete position.where;
   return ret;
}
