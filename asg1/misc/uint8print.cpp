// $Id: uint8print.cpp,v 1.6 2022-01-07 13:20:55-08 - - $

// Show how to print a uint8_t as a number.
// Options:
// -c as characters
// -n as numbers

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;

#ifdef __GNUG__

   #include <cxxabi.h>
   string demangle (const char* name) {
      int status = 0;
      unique_ptr<char,void(*)(void*)> result {
         abi::__cxa_demangle (name, nullptr, nullptr, &status),
         std::free,
      };
      return status == 0 ? result.get() : name; 
   }

#else

   string demangle (const char* name) {
      return name;
   }

#endif

string basename (const string &name) {
   return name.substr (name.rfind ('/') + 1);
}

template <typename T>
void print() {
   const char* type = typeid(T).name();
   cout << "Printing as " << type << " = " << demangle (type) << endl;
   cout << "[";
   for (uint8_t n = 0; n <= 9; ++n) cout << T(n);
   cout << "]" << endl;
}

unordered_map<string,void(*)()> fns {
   {"-8", print<uint8_t>},
   {"-i", print<int>},
   {"-u", print<unsigned>},
};

int main (int argc, char** argv) {
   string execname = basename (argv[0]);
   string opt = argc == 1 ? "" : argv[1];
   auto fn = fns.find (opt);
   if (argc != 2 or fn == fns.end()) {
      cerr << "Usage: " << execname << " -8|-i|-u" << endl;
      return EXIT_FAILURE;
   }
   fn->second();
   return EXIT_SUCCESS;
}

//TEST// for cmd in "uint8print -8" \
//TEST//            "uint8print -8 | cat -t" \
//TEST//            "uint8print -8 | od -c" \
//TEST//            "uint8print -i" \
//TEST//            "uint8print -u"
//TEST// do
//TEST//    echo ""
//TEST//    echo bash: $cmd
//TEST//    sh -c "$cmd"
//TEST// done >uint8print.out
//TEST// mkpspdf uint8print.ps uint8print.cpp uint8print.out

