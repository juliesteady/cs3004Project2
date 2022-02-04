// Verse class function definitions
// Computer Science, MVNU

#include "Verse.h"
#include <iostream>
using namespace std;

Verse::Verse() {  	// Default constructor
    verseText = "Uninitialized Verse!";
    verseRef = Ref();
} 

// REQUIRED: Parse constructor - pass verse string from file
Verse::Verse(const string s) {
	// use Ref constructor to create verseRef
	verseRef = Ref(s);
	// store the remainder of the string in verseText
	string str = s;
	GetNextToken(str, " ");
	verseText = str;
}  	

// REQUIRED: Accessors
string Verse::getVerse() {
	   return verseText; //Fix this
}

Ref Verse::getRef() {
	return verseRef;	//Fix this
}

// display reference and verse
void Verse::display() {
    verseRef.display();
    cout << " " << verseText;
 }
