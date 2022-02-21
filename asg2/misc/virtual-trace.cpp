// $Id: virtual-trace.cpp,v 1.30 2022-01-25 20:53:52-08 - - $

//
// Example using objects, with a base object and two derived objects.
// Similar to inheritance2, but uses gcc demangler.
//

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>
using namespace std;


#include <cxxabi.h>
template <typename type>
string demangle_typeid (const type& object) {
   const char* name = typeid(object).name();
   int status = 0;
   unique_ptr<char,decltype(&std::free)> result {
      abi::__cxa_demangle (name, nullptr, nullptr, &status),
      std::free,
   };
   return status == 0 ? result.get() : name;
}


/////////////////////////////////////////////////////////////////
// class object
/////////////////////////////////////////////////////////////////

#define TRACE { cout << __PRETTY_FUNCTION__ << ": " << *this << endl; }

class object {
   friend ostream& operator<< (ostream&, const object&);
   private:
      static size_t next_id;
   protected:
      const size_t id;
      object(): id(++next_id) {TRACE};
   public:
      object (const object&) = delete;            // no copying
      object& operator= (const object&) = delete; // no copying
      virtual ~object() {TRACE}
      virtual ostream& print (ostream&) const;
      virtual double area() const = 0;
};
size_t object::next_id = 0;

ostream& operator<< (ostream& out, const object& obj) {
   return obj.print (out);
}

ostream& object::print (ostream& out) const {
   return out << static_cast<const void*> (this) << "->"
              << typeid(*this).name() << ":id=" << id;
}


/////////////////////////////////////////////////////////////////
// class square 
/////////////////////////////////////////////////////////////////

class square: public object {
   private:
      double width;
   public:
      explicit square (double w): width(w) {TRACE};
      virtual ~square() {TRACE};
      virtual ostream& print (ostream&) const override;
      virtual double area() const override;
};

ostream& square::print (ostream& out) const {
   return this->object::print (out) << ", width=" << width;
}

double square::area() const {
   return pow (width, 2.0);
}


/////////////////////////////////////////////////////////////////
// class circle 
/////////////////////////////////////////////////////////////////

class circle: public object {
   private:
      double radius;
   public:
      explicit circle (double r): radius(r) {TRACE};
      virtual ~circle() {TRACE};
      virtual ostream& print (ostream&) const override;
      virtual double area() const override;
};

ostream& circle::print (ostream& out) const {
   return this->object::print (out) << ", radius=" << radius;
}

double circle::area() const {
   return M_PI * pow (radius, 2.0);
}


/////////////////////////////////////////////////////////////////
// main
/////////////////////////////////////////////////////////////////

#define SHOW(STMT) cout << endl << "STMT:" << #STMT << endl; STMT

int main() {

   SHOW (vector<shared_ptr<object>> vec;)
   SHOW (vec.push_back (make_shared<circle> ( 5));)
   SHOW (vec.push_back (make_shared<square> ( 5));)
   SHOW (vec.push_back (make_shared<circle> (10));)
   SHOW (vec.push_back (make_shared<square> (10));)
   cout << endl;

   for (const auto& ptr: vec) {
      SHOW (cout << *ptr << " ...area=" << ptr->area() << endl;)
   }

   SHOW (vec.pop_back();)
   SHOW (vec.pop_back();)

   SHOW (return 0;)
}

//TEST// valgrind virtual-trace >virtual-trace.out 2>&1
//TEST// mkpspdf virtual-trace.ps virtual-trace.cpp virtual-trace.out

