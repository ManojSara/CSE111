.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CSE-111 Winter\~2022 Program\~3 "Templates and Iterators"
.RCS \
"$Id: asg3-listmap-templates.mm,v 1.119 2022-02-17 10:10:21-08 - - $"
.PWD
.URL
.EQ
delim $$
.EN
.de BULLETS
.   ALX \[bu] 0 4 0 0
..
.H 1 "Overview"
In this assignment,
you will implement template code and not use any template
classes from the standard library.
You will also write your own code to handle files.
Refer to the earlier assignment as to how to open and read files.
.P
You may use the following includes,
and if you think anything else is needed,
post a question to the discussion forum\(::
.V= <cassert> ,
.V= <cerrno> ,
.V= <cstdlib> ,
.V= <cstring> ,
.V= <exception> ,
.V= <fstream> ,
.V= <iomanip> ,
.V= <iostream> ,
.V= <regex> ,
.V= <stdexcept> ,
.V= <string> ,
.V= <typeinfo> .
.P
Specifically, you may not use any classes that take template
parameters,
such as
.V= <iterator> ,
.V= <list> ,
.V= <map> ,
.V= <pair> ,
.V= <vector> ,
except for those you write yourself.
Do not use
.V= shared_ptr ,
and instead, explicitly manage pointers yourself using
.V= new
and
.V= delete .
Ensure that there are no dangling pointers and no memory leak.
Use
.V= valgrind
to check on this.
.H 1 "Program specification"
The program is specified in the format of a Unix
.V= man (1)
page.
.SH=BVL
.MANPAGE=LI "NAME"
keyvalue \[em] manage a list of key and value pairs
.MANPAGE=LI "SYNOPSIS"
.V= keyvalue
.=V \|[ -@
.IR flags ]
.RI \|[ filename \|.\|.\|.]
.MANPAGE=LI "DESCRIPTION"
Input is read from each file in turn.
Before any processing,
each input line is echoed to
.V= cout ,
preceded by its filename and line number within the file.
The name of
.V= cin
is printed as a minus sign
.=V ( - ).
.MANPAGE=LI "OPTIONS"
The
.V= -@
option is followed by a sequence of flags to enable debugging output,
which is written to the standard error.
The option flags are only meaningful to the programmer.
.MANPAGE=LI "OPERANDS"
Each operand is the name of a file to be read.
If no filenames are specified,
.V= cin
is read.
If filenames are specified,
a filename consisting of a single minus sign
.=V ( - )
causes 
.V= cin
to be read in sequence at that position.
Any file that can not be accessed causes a message in proper format to
be printed to
.V= cerr .
.MANPAGE=LI "INPUT DESCRIPTION"
Each non-comment line causes some action on the part of the program.
Before processing a command,
leading and trailing white space is trimmed off of the key and off of
the value.
White space interior to the key or value is not trimmed.
When a key and value pair is printed,
the equivalent of the format string used is
.V= "\[Dq]%s\0=\0%s\[rs]n\[Dq]" .
Use
.V= <iostream> ,
not
.V= <stdio> .
The newline character is removed from any input line before
processing.
If there is more than one equal sign on the line,
the first separates the key from the value,
and the rest are part of the value.
Input lines are one of the following\(::
.BVL \n[Pi]
.LI \f[CB]#\f[R]
Any input line whose first non-whitespace character is a hash
.=V ( # )
is ignored as a comment.
This means that no key can begin with a hash.
An empty line or a line
consisting of nothing but white space is ignored.
.LI \f[I]key\f[R]
A line consisting of at least one non-whitespace character and no equal
sign causes the key and value pair to be printed.
If not found, the message
.VINDENT* "\f[I]key\f[CB]:\~key\~not\~found\f[R]"
is printed.
Note that the characters in italics are not printed exactly.
The actual key is printed.
This message is printed to
.V= cout .
.LI \f[I]key\f[R]\~\f[CB]=\f[R]
If there is only whitespace after the equal sign,
the key and value pair is deleted from the map.
.LI \f[I]key\f[R]\~\f[CB]=\f[R]\~\f[I]value\f[R]
If the key is found in the map,
its value field is replaced by the new value.
If not found, the key and value are inserted in increasing
lexicographic order, sorted by key.
The new key and value pair is printed.
.LI \f[CB]=\f[R]
All of the key and value pairs in the map are printed in
lexicographic order.
.LI \f[CB]=\f[R]\~\f[I]value\f[R]
All of the key and value pairs with the given value are printed in
lexicographic order sorted by key.
.LE
.MANPAGE=LI "EXIT STATUS"
.VL \n[Pi]
.LI 0
No errors were found.
.LI 1
There were some problems accessing files,
and error messages were reported to
.V= cerr .
.LE
.LE
.H 1 "Reference implementation.
Study the behavior of
.V= misc/pkeyvalue.perl ,
whose behavior your program should emulate.
The Perl version does not support the debug option of your program.
.H 1 "Implementation sequence"
Consider this implementation sequence,
but you may of course choose to implement your program in a different
order.
.ALX a ()
.LI
Implement your main program whose name is
.V= main.cpp ,
and handle files in the same way as the sample Perl code.
Instead of trying to use a map,
just print debug statements showing which of the five
kinds of statements are recognized,
printing out the key and value portion of the statement.
.LI
Instead of
.V= <pair>
from the standard library,
you will use
.V= xpair .
.LI
You will be using a linear linked list to implement your data
structure.
This is obviously unacceptable in terms of a real data structures
problem,
since unit operations will run in $ O ( n ) $ time instead of
the proper $ O ( log sub 2 n ) $ time for a balanced binary search
tree.
But iteration over a binary search tree is rather complex and
will not contribute to your learning about how to implement templates.
.LI
Look at 
.V= xless.h
and
.V= misc/testxless.cpp ,
which show how to create and use an
.V= xless
object to make comparisons.
The 
.V= listmap
class assumes this has already been declared.
.LI
The files
.V= *.tcc
are explicit template instantiations.
Templates are type-safe macros and the source is needed at
the point where they are compiled.
.LI
For the two queries requiring iteration,
your main module must make use of the 
.V= listmap
iterators.
Do not copy anything from the listmap into another data structure,
such as a vector.
That is,
there may be no function of
.V= listmap
which copies out all of the items into another data structure.
.LE
.H 1 "The main function"
Replace the code in the main function to do options analysis.
Then, for each input line,
use
.V= regex_search
using regular expressions to parse the line into one of the
three kinds of lines described above.
Use the field captures to extract the key and value fields.
See the example
.V= matchlines.cpp ,
which shows how to use regular expressions from the
.V= <regex>
library.
.H 1 "Template class \f[CB]listmap\f[P]"
We now examine the class
.V= listmap ,
which is partially implemented for you.
You need not implement functions that are never called.
.de VV
.   VTCODE* 0 \\$@
..
.de LI=VV
.   LI
.   V= \\$@
.   br
..
.ALX a ()
.LI=VV "template <typename key_t, typename mapped_t,"
.VV    "          class less_t=xless<key_t>>"
.VV "class listmap"
defines the template class with three arguments.
.V= key_t
and
.V= mapped_t
are the elements to be kept in the list.
.V= less_t
is the class used to determine the ordering of the list and
defaults to
.V= xless<key_t> .
.LI=VV "using key_type = key_t;"
.VV "using mapped_type = mapped_t;"
.VV "using value_type = xpair<const key_type, mapped_type>;"
are some standard names given to usual standard library types.
Note that the value type is an
.V= xpair,
not what is normally thought as the value,
which here is called the
mapped type.
.LI=VV "struct link"
represents the list itself and is contained in every node.
The list is kept as a circular doubly linked list with the
list itself being the start and end,
as well as the
.V= end()
result.
In a list with $n$ nodes, 
there are $n + 1$ links,
each node having a link, and the list itself having a link,
but not node values.
.LI=VV "struct node"
is a private node used to hold a value type along with forward
and backword links to form a doubly linked list.
It inherits from
.V= "struct link" .
The private function
.V= anchor()
downcasts from a
.V= link
to a
.V= node.
.LI=VV "listmap();"
.VV "listmap (const listmap&);"
.VV "listmap& operator= (const listmap&);"
.VV "listmap (listmap&&);"
.VV "listmap& operator= (listmap&&);"
.VV "~listmap();"
The usual six members are overriden and explicitly defined.
.LI=VV "iterator insert (const value_type&);"
Note that insertion takes a pair as a single argument.
If the key is already there, the value is replaced,
otherwise there is a new entry inserted into the list.
An iterator pointing at the inserted item is returned.
.P
Algorithm\(::
.ALX 1 . "" 0 0
.LI
Chase down the list from 
.V= begin
until you find either
.V= end
or a node with a key not less than the key you are searching for.
Always use
.V= xless
for comparisons.
.LI
If you hit
.V= end ,
insert in front of end.
.LI
Use
.V= xless
with the operands reversed.
.BULLETS
.LI
If they are equal, replace the value.
.LI
If not, insert the new node in front of the node just found.
.LE
.LE
You may only use 
.V= xless 
to compare keys.
Do not use any relational operator.
If
.V= xless(a,b)
and
.V= xless(b,a)
are both false,
that tells you they are equal.
.LI=VV "iterator find (const key_type&);"
Searches and returns an iterator.
If find fails, it returns the
.V= end()
iterator.
.P
As with 
.V= insert ,
use only
.V= xless
for comparisons.
Do not use
.V= == ,
.V= < ,
or other comparison operators on strings.
.LI=VV "iterator erase (iterator position);"
The item pointed at by the argument iterator is deleted from
the list.
The returned iterator points at the position immediately
following that which was erased.
.P
An attempt to erase using an invalid iterator
(including such as
.V= end )
causes
.IR "undefined behavior" .
Undefined behavior may corrupt memory,
cause a segmentation fault,
or cause other misery.
.LI=VV "iterator begin();"
.VV "iterator end();"
The usual iterator generators.
We don't bother here with a constant iterator.
Since the list is circular,
.V= end()
is just the list itself.
.LE
.H 1 "Template class \f[CB]listmap::iterator\f[P]
Although the iterator is nested inside the list map,
it is easier to read when specified separately.
Using 
.V= erase ,
.V= operator-> ,
or
.V= operator*
on an invalid iterator (including
.V= end )
causes
.IR "undefined behavior" .
Undefined means that anything can happen.
It is the programmer's responsibility not to cause undefined
behavior.
.ALX a ()
.LI=VV "class listmap<key_t,mapped_t,less_t>::iterator"
specifies precisely which class the iterator belongs to.
.LI=VV "friend class listmap<key_t,mapped_t>;"
Only a listmap is permitted to construct a valid iterator.
.LI=VV "iterator (node* where);"
The iterator keeps track of the node.
.LI=VV "value_type& operator*();"
Returns a reference to some value type (key and value pair)
in the list.
Selections are then by dot
.=V ( . ).
.LI=VV "value_type* operator->();"
Returns a pointer to some value type, from which fields can be
selected with an arrow
.=V ( -> ).
.LI=VV "iterator& operator++(); //++itor"
.VV "iterator& operator--(); //--itor"
Move backwards and forwards along the list.
Moving off the end with
.V= ++
and moving from an end iterator to the last element
does not require special coding,
since the list is a circular list.
We don't bothere here with the postfix operators.
.LI=VV "void erase();"
Removes the key and value pair from the list.
.LE
.H 1 "What to Submit"
.V= Makefile ,
.V= README ,
and all necessary C++ header and implementation
.=V ( *.h ,
.V= *.tcc ,
.V= *.cpp )
files.
If you are using pair programming, also submit
.V= PARTNER .
.if n \{ .\"
.H 1 "Diagram of listmap with data"
.DS CB
.SP
.ft CB
         end       begin
         |         |
         V         V                             last
         anchor    node      node      node      node
         +-----+   +-----+   +-----+   +-----+   +-----+
(last)-->|  *--|-->|  *--|-->|  *--|-->|  *--|-->|  *--|-->(anchor)
(last)<--|--*  |<--|--*  |<--|--*  |<--|--*  |<--|--*  |<--(anchor)
         +-----+   +-----+   +-----+   +-----+   +-----+
                   |     |   |     |   |     |   |     |
                   | key |   | key |   | key |   | key |
                   |     |   |     |   |     |   |     |
                   | map |   | map |   | map |   | map |
                   |     |   |     |   |     |   |     |
                   +-----+   +-----+   +-----+   +-----+
.SP
.DE
.\}\"
.if t \{ .\"
.H 1 "Diagram of listmap with data"
.DS CB
.PS 5.75i
boxht=1
boxwid=1.3
arrowwid=.1
arrowht=.2
linethick=1
boxdelta=boxwid/2
boxsep=boxwid+boxdelta
Anchor: box
Node1: box at Anchor+(boxsep,0)
Node2: box at Node1+(boxsep,0)
Node3: box at Node2+(boxsep,0)
Node4: box at Node3+(boxsep,0)
"\f[CB]::anchor\f[P]" rjust at Anchor.ne+(0,.15)
"\f[CB]listmap\f[P]" rjust at Anchor.ne+(0,.45)
"node1" rjust at Node1.ne+(0,.15)
"node2" rjust at Node2.ne+(0,.15)
"node3" rjust at Node3.ne+(0,.15)
"node4" rjust at Node4.ne+(0,.15)
"(last) " rjust at Node4.ne+(0,.45)
Enddot: circle fill 1 diam arrowwid at Anchor.nw+(-boxht*.7,boxht)
Begindot: circle fill 1 diam arrowwid at Node1.nw+(-boxht*.7,boxht)
End: "\f[CB]::end()\f[P]" ljust at Enddot+(-.2,.2)
"\f[CB]listmap\f[P]" ljust at End+(0,.30)
Begin: "\f[CB]::begin()\f[P]" ljust at Begindot+(-.2,.2)
"\f[CB]listmap\f[P]" ljust at Begin+(0,.30)
arrow from Begindot to Node1.nw
arrow from Enddot to Anchor.nw
Data1: box ht 2 at Node1.s-(0,1)
Data2: box ht 2 at Node2.s-(0,1)
Data3: box ht 2 at Node3.s-(0,1)
Data4: box ht 2 at Node4.s-(0,1)
arrow from Anchor.w+(-boxdelta,.2) to Anchor.w+(0,.2)
arrow from Anchor+(0,.2) to Node1.w+(0,.2)
arrow from Node1+(0,.2) to Node2.w+(0,.2)
arrow from Node2+(0,.2) to Node3.w+(0,.2)
arrow from Node3+(0,.2) to Node4.w+(0,.2)
arrow from Node4+(0,.2) to Node4.e+(boxdelta,.2)
arrow from Anchor-(0,.2) to Anchor.w-(boxdelta,.2)
arrow from Node1-(0,.2) to Anchor.e-(0,.2)
arrow from Node2-(0,.2) to Node1.e-(0,.2)
arrow from Node3-(0,.2) to Node2.e-(0,.2)
arrow from Node4-(0,.2) to Node3.e-(0,.2)
arrow from Node4.e-(-boxdelta,.2) to Node4.e-(0,.2)
circle fill 1 diam arrowwid at Anchor+(0,.2)
circle fill 1 diam arrowwid at Anchor-(0,.2)
circle fill 1 diam arrowwid at Node1+(0,.2)
circle fill 1 diam arrowwid at Node1-(0,.2)
circle fill 1 diam arrowwid at Node2+(0,.2)
circle fill 1 diam arrowwid at Node2-(0,.2)
circle fill 1 diam arrowwid at Node3+(0,.2)
circle fill 1 diam arrowwid at Node3-(0,.2)
circle fill 1 diam arrowwid at Node4+(0,.2)
circle fill 1 diam arrowwid at Node4-(0,.2)
box invis at Anchor.w-(boxdelta,0)
"(last)" rjust at Anchor.w-(boxdelta-arrowht,0)
" (anchor)" ljust at Node4.e+(boxdelta-arrowht,0)
"key1" at Data1+(0,.3)
"mapped1" at Data1-(0,.3)
"key2" at Data2+(0,.3)
"mapped2" at Data2-(0,.3)
"key3" at Data3+(0,.3)
"mapped3" at Data3-(0,.3)
"key4" at Data4+(0,.3)
"mapped4" at Data4-(0,.3)
.PE
.DE
.\}\"
