#include <iostream>
#include <fstream>
#include <string>

// Stuff for Ajax
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

//Stuff for pipes                                                               
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "fifo.h"
using namespace std;

//#include "textindex.h"

#define logging // enable log file
#define LOG_FILENAME "/tmp/julsteady-lookupclient.log"
#include "logfile.h"

// Pipes for communication                                                      
string receive_pipe = "SSreply";
string send_pipe = "SSrequest";

int main() {
  // prepare the response output,
  // send required header before any other output
  cout << "Content-Type: text/plain\n\n" << endl;
  
  bool input = false;

  Cgicc cgi;
  form_iterator bt = cgi.getElement("bible_type");
  form_iterator book = cgi.getElement("book");
  form_iterator chapter = cgi.getElement("chapter");
  form_iterator verse = cgi.getElement("verse");
  form_iterator numV = cgi.getElement("num_verse");

    if(chapter != cgi.getElements().end())
    {
        int chap = chapter->getIntegerValue();
        if(chap > 150 || chap <= 0){
            cout << "<p>The chapter does not exist</p>" << endl;
        } else{
            input = true;
        }
    }
  
  string bible = **bt;
  int b = book->getIntegerValue();
  int c = chapter->getIntegerValue();
  int v = verse->getIntegerValue();
  int verseNum = numV->getIntegerValue();
  
  string ref = to_string(b) + "," + to_string(c) + "," + to_string(v);
  //string vNum = to_string(verseNum);

  Fifo recfifo(receive_pipe);
  Fifo sendfifo(send_pipe);
  
#ifdef logging
  logFile.open(logFilename.c_str(),ios::out);
#endif
  
  sendfifo.openwrite();
  log("Open request pipe");
  
  // Call server to get results                                                 
  sendfifo.send(bible);
  log("Bible request: "+ bible);

  sendfifo.send(ref);
  log("Ref lookup: "+ ref);

  sendfifo.send(to_string(verseNum));
  log("Bible request: "+ to_string(verseNum));

  recfifo.openread();
  log("Open reply fifo");

  // output
  string results = "";
  int times = 0; // Counter
  while (results != "$end") {
    results = recfifo.recv();
    log("Reply: "+results);
    if (results != "$end") {
      cout << results << endl;
      }
    }

  cout << endl; 
  recfifo.fifoclose();
  log("close reply fifo");
  sendfifo.fifoclose();
  log("close request fifo");
  return 0;
}
