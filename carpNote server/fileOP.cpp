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
using namespace std;

fileOP::fileOP()
{
    userRootDir="/home/CarpNote";
}

bool fileOP::setRootDir()
{
    mkdir(userRootDir,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return true;
}

bool fileOP::setUserDir(string UserName)
{
    mkdir(userRootDir+"/"+UserName,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    return true;
}

bool fileOP::modifyUserDirName(string UserName,string newUserName)
{
    rename(userRootDir+"/"+UserName,useRootDir+"/"+newUserName);
    
    return true;
}

bool setBookDir(string UserName,string bookName)
{
    mkdir(userRootDir+"/"+UserName+"/"+bookName,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    return true;
}

bool fileOP::modifyBookDirName(string UserName,string BookName,string newBookName)
{
    rename(userRootDir+"/"+UserName+"BookName",userRootDir+"/"+UserName+"/"+newBookName);
    
    return true;
}


bool fileOP::setNoteFile(string UserName,string BookName,string noteName)
{
    int fd;
    fd=open(userRootDir+"/"+BookName+"/"+noteName,O_RDWR|O_CREAT);
    close(fd);
    
    return true;
}

bool fileOP::modifyNoteFileName(string UserName,string BookName,string NoteName,string newNoteName)
{
    rename(userRootDir+"/"+UserName+"/"+BookName+"/"+NoteName,userRootDir+"/"+BookName+"/"+newNoteName);
    
    return true;
}

bool fileOP::writeToNoteFile(string UserName,string BookName,string NoteName,char *fileCache)
{
    int fd;
    fd=open(userRootDir+"/"+UserName+"/"+BookName+"/"+NoteName,O_RDWR);
    write(fd,fileCache,sizeof(fileCache));
    
    close(fd);
    return true;
}

char* fileOP::readForNoteFile(string UserName,string BookName,string NoteName)
{
    int fd,size;
    char buffer[3000];
    fd=open(userRootDir+"/"+UserName+"/"+BookName+"/"+NoteName,O_RDWR);
    size=read(fd,buffer,sizeof(buffer));
    
    return buffer;
}
