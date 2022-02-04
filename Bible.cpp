// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
}

// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; }

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) { 
    // TODO: scan the file to retrieve the line that holds ref ...
    // update the status variable
	string buffer, verseText;
	//int book, chap, verse;
	Verse aVerse; 	  // default verse, to be replaced by a Verse object

	bool bCheck = false;
	bool cCheck = false;
	bool vCheck = false;
	
	do {
        /* get the next verse */
        aVerse = nextVerse(status);

        /* See if it is the right book */
		if(ref.getBook() == aVerse.getRef().getBook()){
			bCheck = true;

			if(ref.getChap() == aVerse.getRef().getChap()){
				cCheck = true;

				if(ref.getVerse() == aVerse.getRef().getChap()){
					vCheck = true;
				}
			}
		}

            if (ref == aVerse.getRef()) {
                /* display the verse (if we got one) */
				status = SUCCESS;
				return aVerse;
                //display_verse(buffer);
				//aVerse.display();
            }

        //}
    } while (ref.getBook() >= aVerse.getRef().getBook() && !instream.fail());

	if(vCheck){
		status = OTHER;
	} else if (cCheck){
		status = NO_VERSE;
	} else if (bCheck){
		status = NO_CHAPTER;
	} else {
		status = NO_BOOK;
	}
	// placeholder until retrieval is attempted
	// create and return the verse object
	                // that is constructed from a line in the file.
    return aVerse;
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) {
	string buffer, verseText;
	if(isOpen){
		getline(instream, buffer);
	}else{
		instream.open(infile.c_str(), ios::in);
		isOpen = true;
		getline(instream, buffer);
	}

	Verse aVerse(buffer); 	//Fix this
	return(aVerse);	//Fix this
}

// REQUIRED: Return an error message string to describe status
string Bible::error(LookupResult status) {
	string ans = "Error";
	if(status == 0){
		ans = "Success";
	} else if(status == 1){
		ans = "Error: BOOK DOES NOT EXIST";
	} else if(status == 2){
		ans = "Error: CHAPTER DOES NOT EXIST";
	} else if(status == 3){
		ans = "Error: VERSE DOES NOT EXIST";
	}
	if(status == 4){
		ans = "Other";
	}
	return ans; 
}

void Bible::display() {
	cout << "Bible file: " << infile << endl;
}
	
// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref

 Ref Bible::next(const Ref ref, LookupResult& status) {
	
	Verse aVerse(nextVerse(status));
	Ref aRef(aVerse.getRef());

	return aRef;
 }

// OPTIONAL: Return the reference before the given ref
//Ref Bible::prev(const Ref ref, LookupResult& status) {}
