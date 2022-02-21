// $Id: main.cpp,v 1.13 2021-02-01 18:58:18-08 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <regex>
#include <unistd.h>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            debugflags::setflags (optarg);
            break;
         default:
            complain() << "-" << char (optopt) << ": invalid option"
                       << endl;
            break;
      }
   }
}

void read_stdin() {
   regex comment_regex {R"(^\s*(#.*)?$)"};
   regex key_value_regex {R"(^\s*(.*?)\s*=\s*(.*?)\s*$)"};
   regex trimmed_regex {R"(^\s*([^=]+?)\s*$)"}; 
   int linenum = 1;
   for (;;) {
      string line;
      getline(cin, line);
      if (cin.eof()) break;
      smatch result;
      cout << "-" << ": " << linenum << ": " << line << endl;
      if (regex_search(line, result, comment_regex)) {
         continue;
      } else if (regex_search(line, result, key_value_regex)) {
         if (result[1] == "" and result[2] == "") {
            // Print all key and value pairs in lexicographic order
            cout << "Only equal sign" << endl;
         } else if (result[1] == "") {
            // Print all key and value pairs with given value lexicographically
            cout << "Only value" << endl;
         } else if (result[2] == "") {
            // Delete key and value pair from map
            cout << "Key and equal sign" << endl;
         } else {
            // Replace key value field with new value if found,
            // else insert lexicographically. Print new key and value pair regardless?
            cout << "Normal line" << endl;
         }
         cout << "key  : " << result[1] << endl;
         cout << "value: " << result[2] << endl;
      } else if (regex_search(line, result, trimmed_regex)) {
         // Print key and value pair, if not found print "key: key not found"
         //cout << "query: " << result[1] << endl;
         cout << "Only key" << endl;
         cout << "key  : " << result[1] << endl;
         cout << "value: " << result[2] << endl;
      }
      linenum++;
   }
}  

int main (int argc, char** argv) {
   sys_info::execname (argv[0]);
   scan_options (argc, argv);
   regex comment_regex {R"(^\s*(#.*)?$)"};
   regex key_value_regex {R"(^\s*(.*?)\s*=\s*(.*?)\s*$)"};
   regex trimmed_regex {R"(^\s*([^=]+?)\s*$)"}; 
   str_str_map test;
   //cout << test << endl;
   if (optind == argc) {
      read_stdin();
   }
   for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
      if (strcmp(*argp, "-") == 0) {
         read_stdin();
         continue;
      }
      ifstream infile(*argp);
      int linenum = 1;
      for (;;) {
         string line;
         getline(infile, line);
         if (infile.eof()) break;
         smatch result;
         cout << *argp << ": " << linenum << ": " << line << endl;
         if (regex_search(line, result, comment_regex)) {
            continue;
         } else if (regex_search(line, result, key_value_regex)) {
            if (result[1] == "" and result[2] == "") {
               // Print all key and value pairs in lexicographic order
               cout << "Only equal sign" << endl;
            } else if (result[1] == "") {
               // Print all key and value pairs with given value lexicographically
               cout << "Only value" << endl;
            } else if (result[2] == "") {
               // Delete key and value pair from map
               cout << "Key and equal sign" << endl;
            } else {
               // Replace key value field with new value if found,
               // else insert lexicographically. Print new key and value pair regardless?
               cout << "Normal line" << endl;
            }
            cout << "key  : " << result[1] << endl;
            cout << "value: " << result[2] << endl;
         } else if (regex_search(line, result, trimmed_regex)) {
            // Print key and value pair, if not found print "key: key not found"
            //cout << "query: " << result[1] << endl;
            cout << "Only key" << endl;
            cout << "key  : " << result[1] << endl;
            cout << "value: " << result[2] << endl;
         }
         linenum++;
      }
      str_str_pair pair (*argp, to_string<int> (argp - argv));
      //cout << "Before insert: " << pair << endl;
      test.insert (pair);
   }

   //cout << test.empty() << endl;
   /*for (str_str_map::iterator itor = test.begin();
        itor != test.end(); ++itor) {
      cout << "During iteration: " << *itor << endl;
   }*/

   str_str_map::iterator itor = test.begin();
   test.erase (itor);

   //cout << "EXIT_SUCCESS" << endl;
   return EXIT_SUCCESS;
}

