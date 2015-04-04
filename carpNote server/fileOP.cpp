/*************************************************************************
	> File Name: fileOP.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 02 Apr 2015 06:38:47 AM PDT
 ************************************************************************/

#include "fileOP.h"
#include<sys/stat.h>
#include<dirent.h>
#include<iostream>
#include<sys/types.h>
#include<fcntl.h>
#include<string>
#include<stdio.h>
using namespace std;

fileOP::fileOP()
{
    userRootDir="/home/CarpNote";
}

bool fileOP::setRootDir()
{
    const char * dir=userRootDir.c_str();
    
    mkdir(dir,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return true;
}

bool fileOP::setUserDir(string UserName)
{
	string dirStr=userRootDir+"/"+UserName;
	const char* dir=dirStr.c_str();


    mkdir(dir,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    return true;
}

bool fileOP::modifyUserDirName(string UserName,string newUserName)
{
	string strOrName=userRootDir+"/"+UserName;
	string strNewName=userRootDir+"/"+newUserName;
	const char* orName=strOrName.c_str();
	const char* newName=strNewName.c_str();

    rename(orName,newName);
    
    return true;
}

bool fileOP::setBookDir(string UserName,string bookName)
{
	string dirStr=userRootDir+"/"+UserName+"/"+bookName;
	const char* dir=dirStr.c_str();

    mkdir(dir,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    return true;
}

bool fileOP::modifyBookDirName(string UserName,string BookName,string newBookName)
{
	string strOrName=userRootDir+"/"+UserName+"/"+BookName;
	string strNewName=userRootDir+"/"+UserName+"/"+newBookName;
	const char* orName=strOrName.c_str();
	const char* newName=strNewName.c_str();

    rename(orName,newName);
    
    return true;
}


bool fileOP::setNoteFile(string UserName,string BookName,string noteName)
{
    int fd;
	string fileStr=userRootDir+"/"+UserName+"/"+BookName+"/"+noteName;
	const char* file=fileStr.c_str();
    fd=open(file,O_RDWR|O_CREAT);
    close(fd);
    
    return true;
}

bool fileOP::modifyNoteFileName(string UserName,string BookName,string NoteName,string newNoteName)
{
	string strOrName=userRootDir+"/"+UserName+"/"+BookName+"/"+NoteName;
	string strNewName=userRootDir+"/"+UserName+"/"+BookName+"/"+newNoteName;
	const char* orName=strOrName.c_str();
	const char* newName=strNewName.c_str();


    rename(orName,newName);
    
    return true;
}

bool fileOP::writeToNoteFile(string UserName,string BookName,string NoteName,char *fileCache)
{
    int fd;
	string fileStr=userRootDir+"/"+UserName+"/"+BookName+"/"+NoteName;
	const char* file=fileStr.c_str();
    fd=open(file,O_RDWR);
    write(fd,fileCache,sizeof(fileCache));
    
    close(fd);
    return true;
}

char* fileOP::readForNoteFile(string UserName,string BookName,string NoteName)
{
    int fd,size;
    char buffer[3000];
	string fileStr=userRootDir+"/"+UserName+"/"+BookName+"/"+NoteName;
	const char* file=fileStr.c_str();
    fd=open(file,O_RDWR);
    size=read(fd,buffer,sizeof(buffer));
    
    return buffer;
}
