/*************************************************************************
	> File Name: xmlOP.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Apr 2015 05:08:48 AM PDT
 ************************************************************************/

#include"xmlOP.h"
#include<iostream>
#include<string>
using namespace std;

xmlOP::xmlOP()
{
   carpNoteRootDir="/home/CarpNote";
    carpNoteBookEleName="NoteBook";

}

bool xmlOP::addNoteBook(string UserName,string BookName)
{
    TiXmlDocument doc=openUserXml(UserName);
    //TiXmlElement *newBook=new TiXmlElement(BookName);
    TiXmlElement *rootEle=doc.RootElement();
    TiXmlElement *bookEle=rootEle->NextSiblingElement(carpNoteBookEleName.c_str());

   if( bookEle->LinkEndChild(new TiXmlElement(BookName.c_str()))==NULL)
   {
       return false;
   }
    return true;
}

bool xmlOP::addNote(string UserName,string BookName,string NoteName)
{
    TiXmlDocument doc=openUserXml(UserName);
    TiXmlElement *rootEle=doc.RootElement();
    TiXmlElement *bookEle=rootEle->NextSiblingElement(carpNoteBookEleName.c_str());
    TiXmlElement *noteEle=bookEle->NextSiblingElement(BookName.c_str());

    if(noteEle->LinkEndChild(new TiXmlElement(NoteName.c_str()))==NULL)
    {
        return false;
    }

    return true;
}

bool xmlOP::delNoteBook(string UserName,string BookName)
{
    
    TiXmlDocument doc=openUserXml(UserName);
    //TiXmlElement *newBook=new TiXmlElement(BookName);
    TiXmlElement *rootEle=doc.RootElement();
    TiXmlElement *bookEle=rootEle->NextSiblingElement(carpNoteBookEleName.c_str());
    //const char *chBookName=BookName.c_str();
    if(bookEle->RemoveChild(new TiXmlElement(BookName.c_str()))==false)
    {
        return false;
    }
    return true;
}

bool xmlOP::delNote(string UserName,string BookName,string NoteName)
{

    TiXmlDocument doc=openUserXml(UserName);
    TiXmlElement *rootEle=doc.RootElement();
    TiXmlElement *bookEle=rootEle->NextSiblingElement(carpNoteBookEleName.c_str());
    TiXmlElement *noteEle=bookEle->NextSiblingElement(BookName.c_str());

    if(noteEle->RemoveChild(new TiXmlElement(NoteName.c_str()))==false)
    {
        return false;
    }

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
