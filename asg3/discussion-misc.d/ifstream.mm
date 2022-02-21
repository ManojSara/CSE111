.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.de BULLETS
.   ALX \[bu] 0 "" 0 0
..
.TITLE "Files in C++ \[em] \f[CB]ifstream\fP
.RCS "$Id: ifstream.mm,v 1.13 2022-02-07 13:14:02-08 - - $"
.PWD
.URL
.EQ
delim $$
.EN
.H 1 "Files in C++ \[em] \f[CB]ifstream\fP
Files can be read in C++ by using
.V= <fstream> 's
class
.V= ifstream.
.P
Following is a sample loop that can be used to iterator over
.V= vector<string>\~filenames
and print the contents of the files.
Assume a function
.V= "void catfile (istream&)"
to use
.V= getline ,
etc., just as it would read
.V= cin .
The complete program is in the file
.V= catfile.cpp
in the 
.V= misc/
directory.
.P
.DS
.VTCODE* 1 "for (const auto& filename: filenames) {"
.VTCODE* 1 "   ifstream infile (filename);"
.VTCODE* 1 "   if (infile.fail()) {"
.VTCODE* 1 "      status = EXIT_FAILURE;"
.VTCODE* 1 "      cerr << progname << ": " << filename << ": "" "" \
" << strerror (errno) << endl;"
.VTCODE* 1 "   }else {"
.VTCODE* 1 "      catfile (infile, filename);"
.VTCODE* 1 "   }"
.VTCODE* 1 "}"
.DE
.H 1 "Dissection of the code"
.ALX a ()
.LI
.V= "string filename"
is the name of the file to open.
.LI
.V= "ifstream infile (filename);"
.br
An
.V= ifstream
is used to read a file.
This statement shows a ctor call with the filename as an argument.
If the file can be opened for input, OK.
If not, there is no exception.
The open just quietly fails.
.LI
.V= "infile.fail()"
checks to see if the open failed.
It is always necessary to check on success or failure.
.LI
.V= "cerr << progname << \[Dq]: \[Dq] << filename << \[Dq]: \[Dq]" "" \
" << strerror (errno) << endl;"
.br
Failure must always be reported properly in three parts\(::
.ALX 1 . "" 0 0
.LI
The name of the program reporting the failure.
This should always be
.V= basename(argv[0]) ,
which should be saved by 
.V= main
when the program starts.
.LI
The name of the object or file causing trougle.
.LI
The specific reason for failure.
.BULLETS
.LI
.V= errno
is an external variable with an integer code indicating the precise
reason for the failure.
.LI
.V= strerror(errno)
converts that into a human-readable string.
.LE
.LE
.LI
If the open succeeds, the file is read, processed according to
whatever the program requires.
.LI
Closing the file is necessary whenever the file is opened.
When an
.V= ifstream
goes out of scope,
the destructor is run,
as for all objects.
The destructor of an
.V= ifstream
closes the file.
.LE
.br
.ne 10
.H 1 "\f[CB]basename\f[P](3)"
The function
.V= basename (3)
is available from
.V= <libgen.h> .
In the case that you are compiling on a system lacking that
library,
here is a drop-in replacement\(::
.DS
.VTCODE* 1 "string basename (const string &name) {"
.VTCODE* 1 "   return name.substr (name.rfind ('/') + 1);"
.VTCODE* 1 "}"
.DE
.V= rfind
returns the position of the rightmost character in the string.
In the case of failure, it returns 
.V= string::npos ,
which is the largest possible
.V= size_t
value.
Thus, 
.V= "npos + 1"
overflows to 0.
