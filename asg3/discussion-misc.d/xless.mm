.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.de BULLETS
.   ALX \[bu] 0 "" 0 0
..
.TITLE "struct xless, struct xgreater"
.RCS "$Id: xless.mm,v 1.8 2022-02-06 18:32:08-08 - - $"
.PWD
.URL
.EQ
delim $$
.EN
.H 1 "struct xless, struct xgreater"
In this example we show how to use a single comparator to perform
all comparisons. 
Consider the function object
.V= xless .
.DS
.VTCODE* 1 "template <typename Type>"
.VTCODE* 1 "struct xless {"
.VTCODE* 1 \
"   bool operator() (const Type &left, const Type &right) const {"
.VTCODE* 1 "      return left < right;"
.VTCODE* 1 "   }"
.VTCODE* 1 "};"
.DE
When instantiated as an object, 
it behaves as would any function.
.V= operator()
in C++ is special in that it can be written to take any number
of arguments.
Other operators in C++ are restricted to the number of
arguments given by the syntax.
.P
.V= xless<string>
can be passed into any function as a comparator strings.
Similarly,
.V= xless<int>
can be passed in as a function object for integers.
It is not possible syntactically to use an operator as an argument.
.P
Example\(::
.V= f(operator<)
is just a syntax error.
But
.V= f(xless())
can be used for the same purpose.
.P
Also consider sorting in the reverse order.
.DS
.VTCODE* 1 "template <typename Type>"
.VTCODE* 1 "struct xgreater {"
.VTCODE* 1 \
"   bool operator() (const Type &left, const Type &right) const {"
.VTCODE* 1 "      return left > right;"
.VTCODE* 1 "   }"
.VTCODE* 1 "};"
.DE
.H 1 Sorting
.V= sort
is one of the algorithms in the standard library.
If we have
.DS
.VTCODE* 1 "vector<string> vs {\[Dq]hello\[Dq], \[Dq]world\[Dq], " \
"" "\[Dq]foo\[Dq], \[Dq]bar\[Dq], \[Dq]baz\[Dq]};"
.VTCODE* 1 "vector<int> vi {3, 1, 4, 55, 77, -8};"
.DE
.P
They could be sorted as follows\(::
.DS
.VTCODE* 1 "sort (vs.begin(), vs.end());"
.VTCODE* 1 "sort (vs.begin(), vs.end(), xgreater<string>());"
.VTCODE* 1 "sort (vi.begin(), vi.end(), xgreater<int>());"
.VTCODE* 1 "sort (vi.begin(), vi.end(), xless<int>());"
.DE
In the first case
.V= sort
will sort in increasing order by default.
In the other cases, a function object is passed into sort
to determine ordering.
In fact any comparison might be used, 
such as alphabetical rather than lexicographcc order.
.P
If names are to be sorted, a slightly more complicated sorter
might be used, such as one that compares last names,
and only considers first names when last names are the same.
.P
See the examples 
.V= test-xless.cpp
and
.V= sorting.cpp
in the 
.V= misc/
subdirectory.
.P
If we have, for example
.DS
.VTCODE* 1 "struct name {"
.VTCODE* 1 "   string last;"
.VTCODE* 1 "   string first;"
.VTCODE* 1 "};   "
.VTCODE* 1 "bool operator< (const name& one, const name& two) {"
.VTCODE* 1 "   if (one.last < two.last) return true;"
.VTCODE* 1 "   if (one.last > two.last) return false;"
.VTCODE* 1 "   return one.first < two.first;"
.VTCODE* 1 "}"
.DE
then
.V= xless<name>()
could be passed into the sorting function,
as in
.VTCODE* 1 "sort (vn.begin(), vn.end(), xless<name>());"
