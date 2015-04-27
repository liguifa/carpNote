/*************************************************************************
	> File Name: xmlOP.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Apr 2015 05:08:48 AM PDT
 ************************************************************************/

#include<xmlOP.h>
#include<iostream>
#include<string>
using namespace std;

xmlOP::xmlOP()
{
   carpNoteRootDir="/home/CarpNote";
}

bool xmlOP::addNoteBook(string UserName,string BookName)
{
    TiXmlDocument doc=openUserXml(UserName);
    //TiXmlElement *newBook=new TiXmlElement(BookName);
   if( doc.LinkEndChild(new TiXmlElement(BookName.c_str()))==NULL)
   {
       return false;
   }
    return true;
}

bool xmlOP::addNote(string UserName,string BookName,string NoteName)
{

    return true;
}

bool xmlOP::delNoteBook(string UserName,string BookName)
{
    
    return true;
}

bool xmlOP::delNote(string UserName,string BookName,string NoteName)
{

    return true;
}

TiXmlDocument xmlOP::openUserXml(string UserName)
{
    TiXmlDocument doc;
    UserName=carpNoteRootDir+"/"+UserName;
    const char *userXml=UserName.c_str();
    doc.LoadFile(userXml);
    return doc;
}
