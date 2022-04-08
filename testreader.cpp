// testreader.cpp
// main function from Project 1

#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main (int argc, char **argv) {
	// Create Bible object to process the raw text file
	Bible webBible("/home/class/csc3004/Bibles/web-complete");
	
	Verse verse;
	int b = 0, c = 0, v = 0, numV = 1;
    //int numV = 1;
	LookupResult result = OTHER;
	//cout << "Using Bible from: ";
	//webBible.display();

	// Prompt for input: get reference to lookup
	// This is good for testing your classes quickly for the first milestone.
	//cout << "Enter 3 integers for book, chapter and verse to find: " << flush;
	//cin >> b >> c >> v;
	// TODO: your final program should get input from command line arguments instead.

    // Check for book number argument
	// Command line arguments: argv[0] is name of program
	// argv[1] ... argv[N] hold N actual arguments, where N = argc-1
    
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <Enter Bible Book Number (1-66)> <chapter number> <verse number> <number of verses to display(optional)>" << endl;
        exit(2);
    }

    if (argc < 3) {
        cerr << "Error: chapter and verse number missing" << endl;
        exit(2);
    }

    if (argc < 4) {
        cerr << "Error: verse number is missing" << endl;
        exit(2);
    }

    b = atoi(argv[1]);
    if (b < 1 || b > 66) {
        cerr << "Error: no such book " << argv[1] << " - must be in range 1 to 66" << endl; //66 is greatest number of books
        exit(2);
    }

    c = atoi(argv[2]);
    if (c < 1 || c > 150) {
        cerr << "Error: no such chapter " << argv[2] << " - must be in range 1 to 150" << endl;	//150 is the greatest number of chapters in a book
        exit(2);
    }

    v = atoi(argv[3]);
    if (v < 1 || v > 176) {
        cerr << "Error: no such verse " << argv[3] << " - must be in range 1 to 176" << endl;	//176 is the greatest number of verses in a chapter
        exit(2);
    }


    if (argc > 4) {
        numV = atoi(argv[4]);
        if (numV < 1 || numV > 2461) {			//2461 is the greatest number of verses in a book
            cerr << "Error: Too many verses " << argv[4] << " - must be in range 1 to 2461" << endl;
            exit(2);
        }
    }

    cout << flush;
    cout << endl;
    cout << "Using Bible from: ";
	webBible.display();

	// Create a reference from the numbers
	Ref ref(b, c, v);

	// Use the Bible object to retrieve the verse by reference
	//cout << "Looking up reference: " << flush;
	//ref.display();

    //cout << "errorrr";
	cout << endl;

    cout << "Building TextIndex ..." << flush;
    webBible.buildTextIndex();

    cout << endl << endl;

    //Check for last ref and byte count
    /*
    map<Ref, int>::iterator last = refs.find(Ref("66:22:21"));  //66:22:21 is last 

	if (last == refs.end()){
		cout << "Error: Final byte issue" << endl;
    }else{
		cout << "Final byte position: " << refs[Ref("66:22:21")] << endl; // Final byte, position of final ref
	}
    */

    cout << "Looking up reference: " << flush;
	ref.display();

    cout << endl << endl;

    verse = webBible.lookup(ref, result);

    if (result == 0){
        verse.display();
        cout << endl;

        int i = 1;
        while (numV > i){ 
            cout << endl;
            ref = webBible.next(ref, result);

            verse = webBible.lookup(ref, result);
            if(result == 0){
                if(verse.getRef().getBook() == ref.getBook()) {
                    verse.display();
                    cout << endl;
                } else {
                    cout << "END OF BOOK";
                    break;
                }
            } else {
                cout << webBible.error(result) << endl;
                break;
            }
            i++;
        }
    } else {
        cout << webBible.error(result) << endl;
    }

    //Past code for Poject 1 & 2
    /*
    if(result == 0){
	verse.display();
    cout << endl;

    int i = 1;
    while (numV > i){
        cout << endl;
        verse = webBible.nextVerse(result);
        if(verse.getRef().getBook() == ref.getBook()){
        verse.display();
        cout << endl;
        }else{
            cout << "END OF BOOK";
            break;
        }
        i++;
    }
    }else{
        cout << webBible.error(result) << endl;
    }
    */

	cout << endl;
}
