// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

map<Ref, int> refs;

//add index here
Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
}

//add index here
// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; }

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) { 
  	map<Ref, int>::iterator it;  // iterator for find
	
	Verse aVerse;
	string str;
  	/* First use find, so as to NOT create a new entry in refs */
  	it = refs.find(ref);
	int index = 0;

  	if (!(it == refs.end())) {

		  if (!isOpen) {
			  instream.open(infile.c_str(), ios::in);
			  isOpen = true;
		  }
		  if (!instream) {
			  error(OTHER);
			  Verse verse;
		  } else {
			  instream.seekg(refs[ref], ios::beg);
			  getline(instream, str);
			  Verse verse(str);
			  status = SUCCESS;
			  return verse;
		  }

	  }

	if (ref < (aVerse.getRef()) == NO_BOOK) {
		status = NO_CHAPTER;
	} else if (ref < (aVerse.getRef()) == NO_CHAPTER) {
		status = NO_VERSE;
	} else if (ref < (aVerse.getRef()) == NO_VERSE) {
		status = NO_VERSE;
	} else {
		status = OTHER;
	}

	return (aVerse);

	/*
    // Scan the file to retrieve the line that holds ref ...
    // update the status variable
	string buffer, verseText;
	//int book, chap, verse;
	Verse aVerse; 	  // default verse, to be replaced by a Verse object

	bool bCheck = false;
	bool cCheck = false;
	bool vCheck = false;
	*/
/*
	do {
        // get the next verse
        aVerse = nextVerse(status);

        // See if it is the right book
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
                //display the verse (if we got one)
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
	*/
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(int position, LookupResult& status) {
	string verseText;
	if(!isOpen){
		instream.open(infile.c_str(), ios::in);
		isOpen = true;
	}
	if(!instream){
		error(OTHER);
		Verse aVerse;
		return aVerse;
	} else {
		instream.seekg(position, ios::beg);
		getline(instream, verseText);
		Verse aVerse(verseText);
		return aVerse;
	}

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
	cout << infile << endl;
}
	
// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref

 Ref Bible::next(const Ref ref, LookupResult& status) {
	/*
	Verse aVerse(nextVerse(status));
	Ref aRef(aVerse.getRef());

	return aRef;
	*/
	map<Ref, int>::iterator it = refs.find(ref);
	Ref aRef;
	it++;
	//int index = it->second;	//put in check***

	//instream.seekg(index);

	//string str;
	//getline(instream, str);
	//getline(instream, str);

	//Ref aRef(str);
	if (it == refs.end()){
		return aRef;
	}else {
		return it->first;
	}

 }

// OPTIONAL: Return the reference before the given ref
//Ref Bible::prev(const Ref ref, LookupResult& status) {}




/*****************************************************************************/
/*      buildTextIndex - reads text file and constructs inverted index       */
/*****************************************************************************/

int Bible::buildTextIndex () {
  //ifstream  infile;     /* input file descriptor */
  int position;         /* location of line in the file */
  string text, line, word;
  int verseCount = 0, rootcount = 0, pos;
  //Ref ref;
  //stemming::english_stem<char, std::char_traits<char> > StemEnglish;

  /* open text file */
  instream.open(infile.c_str(), ios::in);
  if (!instream) {
	cerr << "Error - can't open input file: " << infile << endl;
	return 0;  /* false, indicates error */
  }

  /* process text file */
  while (!instream.fail()) {
    /* Get the file position at beginning of line */
    position = instream.tellg();

	instream.unsetf(ios::skipws);
    /* get the next line */
    getline(instream,line);
    /* Convert line to upper case*/
    //transform(line.begin(), line.end(), line.begin(), ::toupper);

	/* for each word in the line, stem it and put stem in map */
	if(!instream.eof()) {
	  //word = getNextWord(line);
	  //if (word.length() > 0 ) {
		/* Reduce to Stem */
		//StemEnglish(word);
		/* Convert to upper case*/
		//transform(word.begin(), word.end(),word.begin(), ::toupper);
		Ref ref(line);
		refs[ref] = position;
		verseCount++;

		//set to value for mapping no push_back
		//refs[ref].push_back(position); // remember offset for current line
	  //}
	} // end while loop for one line

  } // end while loop for lines of file
  instream.close();
  //31,102 should be verseCount
  //cout << "Verses: " << verseCount << " Unique: " << refs.size() << endl;
  return 1;  /* true, indicates success */
}
