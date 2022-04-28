# Bibleajax program
# Bob Kasper, MVNU Computer Science
# updated January 2020 to use
# c++11 compiler option, current paths on cs.mvnu.edu

# This is a Makefile for the Bible web app demo program.
# Copy this directory to a location within your home directory. 
# Change the USER name value below to your own user name.
# Then use "make" to build the server program,
# and deploy it to the live web server directory.
# To test the program, go to http://cs.mvnu.edu/class/csc3004/USER/
# and open the bibleajax.html link.

# Must replace "username" by your username
USER= julsteady

# Use GNU C++ compiler with C++11 standard
CC= g++
CFLAGS= -g -std=c++11

all: lookupclient lookupserver PutCGI PutHTML
# bibleajax.cgi PutCGI PutHTML
# comment so I don't ruin project2, I added testreader

# I added this changed from biblereader.o
# Main Program source
#testreader.o: Ref.h Verse.h Bible.h testreader.cpp
#	$(CC) $(CFLAGS) -c testreader.cpp

# I added this changed from biblereader
# Build the executable
#testreader: Ref.o Verse.o Bible.o testreader.o
#	$(CC) $(CFLAGS) -o testreader Ref.o Verse.o Bible.o testreader.o

# TO DO: For bibleajax.cgi, add dependencies to include
# compiled classes from Project 1 to be linked into the executable program
#lookupclient.cgi:	bibleajax.o Ref.o Verse.o Bible.o
#		$(CC) $(CFLAGS) -o bibleajax.cgi bibleajax.o Ref.o Verse.o Bible.o -lcgicc
#		# -l option is necessary to link with cgicc library

# main program to handle AJAX/CGI requests for Bible references
#bibleindex.o:	bibleajax.cpp
#		$(CC) $(CFLAGS) -c bibleajax.cpp

# TO DO: copy targets to build classes from Project 1:
# Bible.o, Ref.o, Verse.o
# Ref Object




lookupclient: fifo.o lookupclient.o
		$(CC) $(CFLAGS) -o lookupclient fifo.o lookupclient.o -L/usr/local/lib -lcgicc
# -l option is necessary to link with cgicc library

# main program to handle AJAX/CGI requests for Bible references
lookupclient.o:	fifo.h lookupclient.cpp
		$(CC) $(CFLAGS) -c lookupclient.cpp

lookupserver.o: fifo.h Ref.h Bible.h Verse.h lookupserver.cpp
		$(CC) $(CFLAGS) -c lookupserver.cpp

lookupserver: lookupserver.o fifo.o Ref.o Verse.o Bible.o
		$(CC) $(CFLAGS) -o lookupserver fifo.o lookupserver.o Ref.o Verse.o Bible.o

fifo.o: fifo.cpp fifo.h
		g++ -c fifo.cpp


Ref.o : Ref.h Ref.cpp
	$(CC) $(CFLAGS) -c Ref.cpp

# Verse Object
Verse.o : Ref.h Verse.h Verse.cpp
	$(CC) $(CFLAGS) -c Verse.cpp

# Bible Object
Bible.o : Ref.h Verse.h Bible.h Bible.cpp
	$(CC) $(CFLAGS) -c Bible.cpp

			
PutCGI:	lookupclient
		chmod 755 lookupclient
		cp lookupclient /var/www/html/class/csc3004/$(USER)/cgi-bin

		echo "Current contents of your cgi-bin directory: "
		ls -l /var/www/html/class/csc3004/$(USER)/cgi-bin/

PutHTML:
		cp bibleindex.html /var/www/html/class/csc3004/$(USER)

		echo "Current contents of your HTML directory: "
		ls -l /var/www/html/class/csc3004/$(USER)

clean:		
		rm *.o core lookupclient lookupserver
