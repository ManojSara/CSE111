.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.de BULLETS
.   ALX \[bu] 0 "" 0 0
..
.TITLE "Regular expression matchng"
.RCS \
"$Id: regex-match.mm,v 1.40 2022-02-07 22:07:37-08 - - $"
.PWD
.URL
.H 1 "Regular expressions"
Regular expressions are a powerful way of scanning lines of
text and selecting parts thereof based on pattern specifictions.
.P
In C++, the facility is made available via
.V= <regex> .
.P
.V= https://www.cplusplus.com/reference/regex/
.P
.H 1 "https://regexr.com/"
.V= https://regexr.com/ 
has an interactive page to learn about regular expressions.
.H 1 "Raw strings"
Raw strings are a way of writing string constants without the
need to escape escapes.  For example, the string
.V= \[Dq]\[rs]\[rs]\[rs]\[Dq]\[rs]t\[rs]n\[Dq]
represents a backslash, a quote, a tab, and a newline.
.P
But regexes are represented as strings,
and use backslashes for a separate semantic reason.
To avoid having to double every backslash, a
raw string can be used.
This is denoted by placing the letter
.V= R
in front of the quoted string,
and using parentheses inside the string.
.P
So, for example
.V= R\[Dq](\[rs]\[Dq]\[rs]t)\[Dq]
represents the actual string of 4 characters that appears
between the parentheses \[em]
a backslash, a quote, a backslash, and the letter ``t''.
.H 1 "Regex classes in C++"
Consider the example program
.V= matchlines.cpp .
It has the following three declarations\(::
.DS
.VTCODE* 1 "regex comment_regex " "" \
"{R\[Dq](\[ha]\[rs]s*(#.*)?\[Do])\[Dq]};"
.VTCODE* 1 "regex key_value_regex " "" \
"{R\[Dq](\[ha]\[rs]s*(.*?)\[rs]s*=\[rs]s*(.*?)\[rs]s*\[Do])\[Dq]};"
.VTCODE* 1 "regex trimmed_regex " "" \
"{R\[Dq](\[ha]\[rs]s*([\[ha]=]+?)\[rs]s*\[Do])\[Dq]};"
.DE
.V= regex
is the data type initialized with the raw strings.
Pattern matching applies a regular expression to a string and
determines a match.
Regexes are a programming language in themselves.
.P
.ne 20
Dissection of the strings.
In the following each item shows only the actual regex after the
raw string delimiters have been stripped.
.ALX a ()
.LI
.V= "\[ha]\[rs]s*(#.*)?\[Do]"
.br
Match optional white space, optionally followed by a hash
and anything that follows it.
.VL \n[Pi]
.V=LI "\[ha]"
Match the beginning of the string.
.V=LI "\[rs]s*"
Match zero or more white space characters.
Backslash escapes meta characters and makes ordinary characters
have special meanings.
.V= \[rs]s
match white space (spaces, tabs, newlines).
The asterisk indicates that the preceding item should be
recognized zero ore more times.
.V=LI "("
Begin a capture.
In a 
.V= regex_search ,
this will be an element of the result vector.
.V=LI "#.*"
Match the hash (literally), followed by zero or more of anything.
A dot
.=V ( \&. )
matches any characters except a newline, and
.=V ( \&.* )
matches zero or more of any character.
.V=LI ")?"
End the capture and place it into the result.
The question mark indicates that the preceding capture is optional.
.V=LI "\[Do]"
Match the end of the string.
.LE
.LI
.V= "\[ha]\[rs]s*(.*?)\[rs]s*=\[rs]s*(.*?)\[rs]s*\[Do]"
.br
Match any sequence of characters preceding an equal sign
.=V ( = )
and then also after the equal sign,
capturing sequences befoe and after it.
In each sequence white space is trimmed fore and aft.
.VL \n[Pi]
.V=LI "\[ha]"
Beginning of line.
.V=LI "\[rs]s*"
Zero or more white space.
.V=LI "(.*?)"
Match and capture any sequence of zero or more characters.
Non-greedy (lazy) matching, as few as possible.
.V=LI "\&.*"
would mean a greedy match, but
.V=LI "\&.*?"
is a lazy match, which matches as few characters as possible.
.V=LI "\[rs]s*"
Zero or more white space.
.V=LI "="
Match an equal sign.
.V=LI "\[rs]s*"
Zero or more white space.
.V=LI "(.*?)"
As above, the second captured match.
Parentheses indicate a capture.
Non-greedy matching of zero or more characters.
.V=LI "\[rs]s*"
Zero or more white space.
.V=LI "\[Do]"
End of line.
.LE
.br
.ne 20
.LI
.V= \[ha]\[rs]s*([\[ha]=]+?)\[rs]s*\[Do]
.br
Match a line containing a sequence of one or more characters
none of which is an equal sign.
.VL \n[Pi]
.V=LI "\[ha]"
Beginnng of line.
.V=LI "\[rs]s*"
White space.
.V=LI "([\[ha]=]+?)"
Capture what is in the parentheses.
Brackets indicate a set of characters, in this case the
character equal sign.
The circumflex (hat) complements the set.
So 
.V=LI [\[ha]=]
matches any character not an equal sign.
.V=LI [\[ha]=]+
matches one or more such characters.
.V=LI [\[ha]=]+?
matches one or more such characters, but in a non-greedy (lazy)
manner, matching as few as possible.
.V=LI "\[rs]s*"
White space.
.V=LI "\[Do]"
End of line.
.LE
.LE
.H 1 "Usage of regex"
The 
.V= regex
variables declared above are used in the example program
.V= matchlines.cpp .
Part of the code follows.
.ALX a ()
.LI
.V= "string line;"
.br
.V= "smatch result;"
.br
An
.V= smatch
variable holds the result of a regex match,
and is used to store the results of a search.
Each pair of parentheses in the regex will capture a matched result.
.BULLETS
.LI
.V= result[0]
represents the entire matched expression
.LI
.V= result[i]
represents sub-expression
.V= i
that has been matched.
.LE
.LI
.V= "if (regex_search (line, result, comment_regex)) {"
.br
Search the line to see if it matches the comment regex.
If so, we can ignore the line because comments are not data.
.V= regex_search
returns true if the match has succeeded.
.LI
.V= "}else if (regex_search (line, result, key_value_regex)) {"
.br
Search the line for a key value pair.
This regex has two captures.
If the match succeeds, the
.V= "smatch result"
variable has two values in it.
At this point\(::
.BULLETS
.LI
.V= result[1]
has the key (first captured string)
.LI
.V= result[2]
has the value (second captured string)
.LE
.LI
.V= "}else if (regex_search (line, result, trimmed_regex)) {"
.br
Search the line for the trimmed regex (the third alternative).
This is the query for the program.
.BULLETS
.LI
.V= result[1]
has the value of the query string that was captured.
.LE
.LI
.V= "}else { assert(false)" \0\|.\|.\|.
.br
This can't happen if the three regexes are exhaustive.
But an
.V= assert(false)
just does a backup check to make sure the program crashes
if the logic is wrong.
.bp
.H 1 "Complete code for \f[CB]misc/matchlines.cpp\fP example"
.DS
.ft CB
#include <cassert>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

int main() {
   regex comment_regex {R"(^\[rs]s*(#.*)?$)"};
   regex key_value_regex {R"(^\[rs]s*(.*?)\[rs]s*=\[rs]s*(.*?)\[rs]s*$)"};
   regex trimmed_regex {R"(^\[rs]s*([^=]+?)\[rs]s*$)"};
   for (;;) {
      string line;
      getline (cin, line);
      if (cin.eof()) break;
      cout << "input: \[rs]"" << line << "\[rs]"" << endl;
      smatch result;
      if (regex_search (line, result, comment_regex)) {
         cout << "Comment or empty line." << endl;
      }else if (regex_search (line, result, key_value_regex)) {
         cout << "key  : \[rs]"" << result[1] << "\[rs]"" << endl;
         cout << "value: \[rs]"" << result[2] << "\[rs]"" << endl;
      }else if (regex_search (line, result, trimmed_regex)) {
         cout << "query: \[rs]"" << result[1] << "\[rs]"" << endl;
      }else {
         assert (false and "This can not happen.");
      }
   }
   return 0;
}
.DE
