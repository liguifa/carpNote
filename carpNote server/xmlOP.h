/*************************************************************************
	> File Name: xmlOP.h
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Apr 2015 05:07:45 AM PDT
 ************************************************************************/

#ifndef _XMLOP_H
#define _XMLOP_H

#include<iostream>
#include<string>
#include"./tinyxml/tinyxml.h"

using namespace std;

class xmlOP{

public:
    xmlOP();
    bool addNoteBook(string UserName,string BookName);
    bool addNote(string UserName,string BookName,string NoteName);
    bool delNoteBook(string UserName,string BookName);
    bool delNote(string UserName,string BookName,string NoteName);



private:
    string carpNoteRootDir;
    TiXmlDocument openUserXml(string UserName);


}






#endif


