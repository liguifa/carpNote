/*************************************************************************
	> File Name: fileOP.h
	> Author: 
	> Mail: 
	> Created Time: Thu 02 Apr 2015 06:38:32 AM PDT
 ************************************************************************/

#ifndef _FILEOP_H
#define _FILEOP_H

#include<iostream>
#include<string>

using namespace std;

class fileOP{

public:
    fileOP();
    bool setRootDir();
    bool setUserDir(string UserName);
    bool modifyUserDirName(string UserName,string newUserName);
    bool setBookDir(string UserName,string BookName);
    bool modifyBookDirName(string UserName,string BookName,string newBookName);
    bool setNoteFile(string UserName,string BookName,string NoteName);
    bool modifyNoteFileName(string UserName,string BookName,string NoteName,string newNoteName);
    bool writeToNoteFile(string UserName,string BookName,string NoteName,char *fileCache);
    char *readForNoteFile(string UserName,string BookName,string NoteName);

private:
    string userRootDir;



};










#endif
