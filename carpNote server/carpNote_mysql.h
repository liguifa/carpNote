/*************************************************************************
	> File Name: carpNote_mysql.h
	> Author: 
	> Mail: 
	> Created Time: Tue 31 Mar 2015 02:46:35 AM PDT
 ************************************************************************/

#ifndef _CARPNOTE_MYSQL_H
#define _CARPNOTE_MYSQL_H

#include"encapsulation_mysql.h"
#include<iostream>
#include<vector>
#include<string>

using namespace std;
//using namespace EncapMysql;


class carpNoteSQL{
public:
    carpNoteSQL();
bool addUser(string UserName,string UserPW);
bool modifyUserName(string UserName,string newUserName);
bool modifyUserPW(string UserName,string newUserPW);
string getUserIDByUserName(string UserName);
bool addBook(string UserName,string bookName);
bool modifyBookName(string UserName, string BookName,string newBookName);
string getBookIDByBookName(string UserName,string BookName);
bool addNote(string UserName,string BookName,string NoteName);
bool modifyNoteName(string UserName,string BookName,string NoteName,string newNoteName);
bool checkUser(string UserName,string UserPW);
vector<string> getUserBook(string UserName);
vector<string> getBookNoteName(string UserName,string BookName);

private:
CEncapMysql *SQLCon;

};


#endif
