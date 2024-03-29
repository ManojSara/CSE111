// $Id: main.cpp,v 1.13 2021-02-01 18:58:18-08 - - $
// Manoj Sara (msara), Manas Sara (msara)

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
   str_str_map test;
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
            for (auto i = test.begin(); i != test.end(); ++i) {
               cout << i->first << " = " << i->second << endl;
            }
         } else if (result[1] == "") {
            for (auto i = test.begin(); i != test.end(); ++i) {
               if (i->second == result[2]) {
                  cout << i->first << " = " << i->second << endl;
               }
            } 
         } else if (result[2] == "") {
            str_str_map::iterator to_del = test.find(result[1]);
            if (to_del == test.end()) {
               cout << result[1] << ": key not found" << endl;
            } else {
               test.erase(to_del);
            }
         } else {
            str_str_pair to_in(result[1], result[2]);
            str_str_map::iterator to_print = test.insert(to_in);
            cout << to_print->first << " = " << 
                    to_print->second << endl;
         }
      } else if (regex_search(line, result, trimmed_regex)) {
         str_str_map::iterator to_print = test.find(result[1]);
         if (to_print == test.end()) {
            cout << result[1] << ": key not found" << endl;
         } else {
            cout << to_print->first << " = " <<
                    to_print->second << endl;
         }
      }
      linenum++;
   }

   str_str_map::iterator itor = test.begin();
   if (itor != test.end()) {
      test.erase (itor);
   }

   return;
}  

int main (int argc, char** argv) {
   sys_info::execname (argv[0]);
   scan_options (argc, argv);
   int status = 0;
   string progname (basename (argv[0]));
   regex comment_regex {R"(^\s*(#.*)?$)"};
   regex key_value_regex {R"(^\s*(.*?)\s*=\s*(.*?)\s*$)"};
   regex trimmed_regex {R"(^\s*([^=]+?)\s*$)"}; 
   str_str_map test;
   if (optind == argc) {
      read_stdin();
      return status;
   }
   for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
      bool dash = false;
      if (strcmp(*argp, "-") == 0) {
         dash = true;
      }
      ifstream infile(*argp);
      if (dash == false and infile.fail()) {
         status = 1;
         cerr << progname << ": " << *argp << ": " <<
                 strerror (errno) << endl;
         continue;
      }
      int linenum = 1;
      for (;;) {
         string line;
         if (dash == true) {
            getline(cin, line);
            if (cin.eof()) break;
         } else {
            getline(infile, line);
            if (infile.eof()) break;
         }
         smatch result;
         cout << *argp << ": " << linenum << ": " << line << endl;
         if (regex_search(line, result, comment_regex)) {
            continue;
         } else if (regex_search(line, result, key_value_regex)) {
            if (result[1] == "" and result[2] == "") {
               for (auto i = test.begin(); i != test.end(); ++i) {
                  cout << i->first << " = " << i->second << endl;
               }
            } else if (result[1] == "") {
               for (auto i = test.begin(); i != test.end(); ++i) {
                  if (i->second == result[2]) {
                     cout << i->first << " = " << i->second << endl;
                  }
               } 
            } else if (result[2] == "") {
               str_str_map::iterator to_del = test.find(result[1]);
               if (to_del == test.end()) {
                  cout << result[1] << ": key not found" << endl;
               } else {
                  test.erase(to_del);
               }
            } else {
               str_str_pair to_in(result[1], result[2]);
               str_str_map::iterator to_print = test.insert(to_in);
               cout << to_print->first << " = " <<
                       to_print->second << endl;
            }
         } else if (regex_search(line, result, trimmed_regex)) {
            str_str_map::iterator to_print = test.find(result[1]);
            if (to_print == test.end()) {
               cout << result[1] << ": key not found" << endl;
            } else {
               cout << to_print->first << " = " <<
                       to_print->second << endl;
            }
         }
         linenum++;
      }
      if (dash == false) {
         infile.close();
      }
   }

   str_str_map::iterator itor = test.begin();
   if (itor != test.end()) {
      test.erase (itor);
   }

   return status;
}

