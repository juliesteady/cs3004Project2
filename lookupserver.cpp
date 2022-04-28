#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "fifo.h"
#include "Ref.h"
#include "Bible.h"
#include "Verse.h"


//#include "textindex.h"

// Include stemming stuff                                              
//#include "english_stem.h"

using namespace std;

string receive_pipe = "SSrequest";
string send_pipe = "SSreply";

string bArr [66] = {"Genesis", "Exodus", "Leviticus", "Numbers", 
"Deuteronomy", "Joshua", "Judges", "Ruth", "1 Samuel", "2 Samuel", "1 Kings", 
"2 Kings", "1 Chronicles", "2 Chronicles", "Ezra", "Nehemiah", "Esther", 
"Job", "Psalms", "Proverbs", "Ecclesiastes", "Song of Solomon", "Isaiah", 
"Jeremiah", "Lamentations", "Ezekiel", "Daniel", "Hosea", "Joel", "Amos", 
"Obadiah", "Jonah", "Micah", "Nahum", "Habakkuk", "Zephaniah", "Haggai", 
"Zechariah", "Malachi", "Matthew", "Mark", "Luke", "John", 
"Acts of the Apostles", "Romans", "1 Corinthians", "2 Corinthians", 
"Galatians", "Ephesians", "Philippians", "Colossians", "1 Thessalonians", 
"2 Thessalonians", "1 Timothy", "2 Timothy", "Titus", "Philemon", "Hebrews", 
"James", "1 Peter", "2 Peter", "1 John", "2 John", "3 John", "Jude", 
"Revelation" };



string getVerse(Ref &ref, Bible &bible, Verse verse, LookupResult &result)
{
    int b = ref.getBook();
    int c = ref.getChap();
    int v = ref.getVerse();

    Ref nextRef = Ref();
    string verseText;

    try{
        verse = bible.lookup(ref, result);
        verseText = verse.getVerse();

        if (result == SUCCESS){
            nextRef = bible.next(ref, result);
            ref = nextRef;
        }

    }catch (std::bad_alloc &ba){
        std::cerr << "bad_alloc caught: " << ba.what();
    }
    return verseText;
}



/* Server main line,create name MAP, wait for and serve requests */
int main() {

  Bible webBible("/home/class/csc3004/Bibles/web-complete");
  cout << "Using Bible from: ";
	webBible.display();

  cout << "Building TextIndex ..." << flush;
  webBible.buildTextIndex();


  Fifo fifoRec(receive_pipe);
    Fifo fifoSend(send_pipe);
    fifoRec.openread(); // only open once
    Verse v;
    LookupResult result;
    string message;

    while(1){
        string bible_type = fifoRec.recv();
        string refStr = fifoRec.recv();
        cout << "Ref string: " << refStr << endl;
        Ref ref = Ref(refStr);
        string strVerses = fifoRec.recv();
        cout << "Number of verses: " << strVerses << endl; 
        //Bible &webBible = webBible_path;
        
        int Vnum = atoi(strVerses.c_str());
        int initialBook = ref.getBook();
        int initialChap = ref.getChap();
        fifoSend.openwrite();
        message = "<p>results: <br><font size = \"+1\" ><strong>" + bArr[initialBook - 1] + "</strong> </font><br><b>Chapter: " + to_string(initialChap) + "</b><br>";
        fifoSend.send(message);

        for (int i = 0; i < Vnum; i++){
            int refBook = ref.getBook();
            int refChap = ref.getChap();
            int refVerse = ref.getVerse();
            string verseText = getVerse(ref, webBible, v, result);
            if (verseText == "Uninitialized Verse!"){
                cout << result << endl;
                if (result == 2){

                    message = "<br> <font size = \"+1\" > No chapter:  " + to_string(refChap) + " in " + bArr[refBook - 1] + "</font>";
                    fifoSend.send(message);
                    message = "$end";
                    fifoSend.send(message);
                    break;

                }else{

                    message = "<br><font size = \"+1\" >No verse: " + to_string(refVerse) + " in " + bArr[refBook - 1] + " " + to_string(refChap) + "</font>";
                    fifoSend.send(message);
                    message = "$end";
                    fifoSend.send(message);
                    break;

                }
            }

            int nextChap = ref.getChap();
            int nextBook = ref.getBook();

            if (refBook <= 66){

                message = " <b>[" + to_string(refVerse) + "]</b> <em> " + verseText + "</ em></ p> ";
                fifoSend.send(message);
            }

            if (nextBook == refBook + 1){

                if (nextBook > 66){

                    message = "<br><font size = \"+1\" >End of Bible</font>";
                    fifoSend.send(message);
                    message = "$end";
                    fifoSend.send(message);

                }else{

                    message = "<br><font size = \"+1\" >" + bArr[nextBook] + "</font> <br><b>Chapter: 1</b><br>";
                    fifoSend.send(message);

                }
            }else if (nextChap == refChap + 1){

                message = "<br><b>Chapter: " + to_string(nextChap) + "</b><br>";
                fifoSend.send(message);
            }
        }

        message = "$end";
        fifoSend.send(message);
        fifoSend.fifoclose();


    }

}
