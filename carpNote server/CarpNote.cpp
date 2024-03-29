#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <map>
#include <time.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <vector>
#include <algorithm>
#include <string>
#include "carpNote_mysql.h"
#include "fileOP.h"


using namespace std;

#define   IP   "115.28.164.8"
#define   PORT  9050
#define   MAXCONNECT 1024
//#define FILEPATH "/tmp/images/"


struct fdSet
{
    int epfd;
    int fd;
};
// typedef struct CMsgReq
// {
// 	unsigned int type;
// 	unsigned int len ;
// 	char sBuf[0]; 
// }msgReq;

// typedef struct CMsgRsp
// {
// 	unsigned int type;
// 	unsigned int len ;
// 	// char sBuf[0];
// }msgRsp;

map<unsigned int,unsigned int> mapsockfile;

void init_addr(struct sockaddr_in *paddr)
{
	bzero(paddr,sizeof(struct sockaddr_in));
	paddr->sin_family = AF_INET;
	paddr->sin_port   = htons(PORT);
//    paddr->sin_port=PORT;
	paddr->sin_addr.s_addr = inet_addr(IP);
   // paddr->sin_addr.s_addr=IP;
	return;
}

int sock_bind(int sockfd,struct sockaddr_in addr)
{
	return bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
}

int sock_reuseaddr(int sockfd)
{
	int opt;
	return setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(void*)&opt,sizeof(opt));
}

int sock_setNoNblock(int sockfd)
{
	int flag = fcntl(sockfd,F_GETFL);
	if( flag < 0)
		return -1;
	if(flag & O_NONBLOCK)
	{
		printf("O_NONBLOCK\n");
		return 0;
	}
	flag  |= O_NONBLOCK;
	if(fcntl(sockfd,F_SETFL,flag) >=0)
		return 0;
	return -1;
}

int sock_epoll_reg(int efd,int sockfd,int flag)
{
	struct epoll_event ev;
	ev.data.fd  = sockfd;
	ev.events = flag;
	printf("reg epoll\n");
	return epoll_ctl(efd,EPOLL_CTL_ADD,sockfd,&ev);
}

void sock_epoll_delete (int efd, int sockfd)
{
	epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
}

string getSomeCharByCharCom(char* ch)
{
    //string str;
    char strch[4];
    int start=16;
    int end=19;
    for(int i=0;start<=end;start++,i++)
    {
       strch[i]=ch[start];
    }
    string str=strch;
    return str;
}

string getSomeCharByCharName(char* ch)
{
    //string str;
    char strch[8];
    int start=0;
    int end=7;
    for(int i=0;start<=end;start++,i++)
    {
       strch[i]=ch[start];
    }
    string str=strch;
    return str;
}

string getSomeCharByCharPW(char* ch)
{
    //string str;
    char strch[8];
    int start=8;
    int end=15;
    for(int i=0;start<=end;start++,i++)
    {
       strch[i]=ch[start];
    }
    string str=strch;
    return str;
}

vector<string> getDirNameList(char * ch,int n)
{
    vector<string> strV;
    //char chStr[]="0";
    string str;
    for(int i=0,j=0;j<n;i++,j++)
    {
        if(ch[i]=='|')
        {
            i=0;
            strV.push_back(str);
        }
       str+=ch[i];
    }
    return strV;
}

bool sendNoteToClient(string UserName,string BookName,string noteName,int fd)
{
    fileOP *fileop=new fileOP();
    char *fileStr;
    fileStr=fileop->readForNoteFile(UserName,BookName,noteName);
    write(fd,fileStr,sizeof(fileStr));

    return true;
}

bool recvNoteFromClient(string UserName,string BookName,string noteName,int fd)
{
    fileOP *fileop=new fileOP();
    char fileStr[]="0";
    int len=read(fd,fileStr,2000);
    fileop->writeToNoteFile(UserName, BookName,noteName,fileStr);

    return true;
}

// void map_insert(unsigned int fd,unsigned filefd)
// {
// 	mapsockfile[fd] = filefd;
// 	printf("insert map fd=%d filefd=%d\n",fd,filefd);
// 	return;
// }

// void map_delete(unsigned int fd)
// {
// 	map<unsigned int,unsigned int>::iterator it;
// 	it = mapsockfile.find(fd);
// 	mapsockfile.erase(it);
// 	printf("delete map\n");
// 	return ;
// }

// unsigned int  map_find(unsigned int fd)
// {
// 	map<unsigned int,unsigned int>::iterator it;
// 	it = mapsockfile.find(fd);
// 	printf("find map\n");
// 	return (*it).second;
// }

// void do_send_msg(int epoll_fd,int fd,int type)
// {
// 	msgRsp msgrsp;
// 	msgrsp.type = htonl(type +1);
// 	msgrsp.len = htonl(0);
// 	send(fd,(char*)&msgrsp,sizeof(msgrsp),0);
// }

// unsigned int get_file_fd()
// {  
// 	unsigned int  filefd = -1;
// 	time_t ti;
// 	struct tm *t  = NULL;
// 	time(&ti);
// 	t = localtime(&ti);
// 	char strtime[32]= {0};
// 	snprintf(strtime,sizeof(strtime),"%shtx%02d%02d%02d_%04d%02d%02d",\
// 		FILEPATH,t->tm_hour,t->tm_min,t->tm_sec,t->tm_year + 1900,t->tm_mon +1,t->tm_mday);
// 	filefd  = open(strtime,O_WRONLY | O_CREAT,S_IRUSR|S_IWUSR|S_IRUSR|S_IRWXG|S_IROTH);
// 	printf("create file=%s fd=%d\n",strtime,filefd);
// 	return filefd;
// }

//client请求处理线程
void *thread_OP_Func(void* arg)
{
	fdSet *fdset=(fdSet *)arg;
	//验证账户合法性
	//string UserName=Client->opMsg->UserID;
	//string UserPW=Client->opMsg->UserPW;
    //string comStr=Client->opMsg->op;

    //string str11="qqweeeqeq";
    //cout<<"1111111111111111"<<endl;
    char msg[20]="0";
    int len=0;

    len=recv(fdset->fd,msg,20,0);
    //
    //处理不合规则的字符串,退出线程,结束相关所有操作 
    //
    if(len!=20){
 //       pthread_exit(NULL);
        //return ;
        close(fdset->fd);
        pthread_exit(NULL);
    }

    string comStr=getSomeCharByCharCom(msg);
    string UserName=getSomeCharByCharName(msg);
    string UserPW=getSomeCharByCharPW(msg);

    if(comStr=="chek")
    {
       /// cout<<"222222222222"<<endl;
	carpNoteSQL *userQuery=new carpNoteSQL();
	bool userStat=userQuery->checkUser(UserName,UserPW);
	if (userStat)
	{
		char ch[]="ok";
		int wlen  = send(fdset->fd,ch,strlen(ch),0);

		//int wlen  = write(fdset->fd,ch,strlen(ch));
		//sock_epoll_delete(fdset->epfd,fdset->fd);
		//return;
	} 
	else
	{
		char ch[]="no";
		int wlen  = send(fdset->fd,ch,strlen(ch),0);

		//int wlen  = write(fdset->fd,ch,strlen(ch));
		//char *ch="no";
		//sock_epoll_delete(fdset->epfd,fdset->fd);
		//return;
    }
    }
    else if(comStr=="regi")
    {
        carpNoteSQL *userQuery=new carpNoteSQL();
        bool comStat=userQuery->addUser(UserName,UserPW);
        if(comStat)
        {
            char ch[]="ok";
            send(fdset->fd,ch,sizeof(ch),0);

          //  sock_epoll_delete(fdset->epfd,fdset->fd);
        }
        else
        {
            char ch[]="no";
            send(fdset->fd,ch,sizeof(ch),0);

            //sock_epoll_delete(fdset->epfd,fdset->fd);
        }
    }
    else if(comStr=="sybk")
    {
        char dirName[]="0";
        int dirLen=0;
        carpNoteSQL *userQuery=new carpNoteSQL();
        dirLen=recv(fdset->fd,dirName,2000,0);
        vector<string> cdirStr=getDirNameList(dirName,dirLen);
        vector<string> sdirStr=userQuery->getUserBook(UserName);
        //sort(cdirStr.begin(),cdirStr.end());
        vector<string> clientLack,serverLack;
        for(vector<string>::iterator ite=cdirStr.begin();ite<=cdirStr.end();ite++)
        {

            vector<string>::iterator result=find(sdirStr.begin(),sdirStr.end(),*ite);
            if(result!=sdirStr.end())
            {
                serverLack.push_back(*ite);
            }
        }
        if(serverLack.size()!=0)
        {
            fileOP * fileop=new fileOP();

            for(vector<string>::iterator ite=serverLack.begin();ite<=serverLack.end();ite++)
            {
                userQuery->addBook(UserName,*ite);
                fileop->setBookDir(UserName,*ite);
                

            }
        }

        for(vector<string>::iterator ite=sdirStr.begin();ite<=sdirStr.end();ite++)
        {
            vector<string>::iterator result=find(cdirStr.begin(),cdirStr.end(),*ite);
                //clientLack.push_back(*ite);
            if(result!=cdirStr.end())
            {
                clientLack.push_back(*ite);
            }
        }

        if(clientLack.size()!=0)
        {
            string sendstr;
            for(vector<string>::iterator ite=clientLack.begin();ite<=clientLack.end();ite++)
            {
                sendstr+=*ite;
            }
            const char *clientLockBuffer=sendstr.c_str();
            write(fdset->fd,clientLockBuffer,sizeof(clientLockBuffer));
        }
        else
        {
            char clientLockBuffer[]="NONEED";
            write(fdset->fd,clientLockBuffer,sizeof(clientLockBuffer));
        }
        
    }
    else if(comStr=="synt")
    {
        char *noteBookName;
        int strLen=read(fdset->fd,noteBookName,2000);
        vector<string> str=getDirNameList(noteBookName,strLen);
        string bookName=str[0];
        for(int i=1;i<=str.size();i++)
        {
            recvNoteFromClient(UserName,bookName,str[i],fdset->fd);
        }
    }
    else if(comStr=="sypt")
    {


    }
    //更新某个笔记的某些语句
    //NoteBookName+NoteName+修改日期(精确到ms)+修改之后的内容
    //之后根据日期修改note
    else if(comStr=="sdnt")
    {
        char *modifyNoteStr;
        int strLen=read(fdset->fd,modifyNoteStr,2000);
        //
        //得到NoteBookName NoteName modifyData modifyStr
        //

        
    }





    close(fdset->fd);
	//执行相关操作

	pthread_exit(NULL);
}



void do_recv_msg(int epoll_fd,int fd)
{
	//操作指令
	//opStr *clientOPStr;
	//clientFD client;
	//char msgHead[20] = {0};
	//int len;
	pthread_t tid;
    fdSet fdset;
    int i=epoll_fd;
    cout<<i<<endl;
    fdset.epfd=epoll_fd;
    fdset.fd=fd;

	//len=recv(fd,msgHead,20,0);
	//错误处理
	//if (len<=0)
	//{
	//}
    
    //一条指令完成,剩下交给线程处理
    sock_epoll_delete(epoll_fd,fd);

	//clientOPStr=(opStr *)msgHead;
	//client.opMsg=clientOPStr;
	//client.epfd=epoll_fd;
	//client.fd=fd;

	//
	//账户与密码核对留到指令里在做
	//

	//根据指令进行操作
	pthread_create(&tid,NULL,thread_OP_Func,(void *)&fdset);

//处理字节序的 暂时不处理
//
/*	pCur = msgHead;*/
// 	unsigned int type = ntohl(*(unsigned int*)pCur);
// 	unsigned int len  = ntohl(*(unsigned int*)(pCur + sizeof(unsigned int)));
// 	msgReq *pmsgReq = (msgReq*)malloc(sizeof(msgReq) + len);
// 	pCur = &(pmsgReq->sBuf[0]);


// 	if(type == 2 || type == 3)
// 	{
// 		unsigned int filefd = map_find(fd);
// 		map_delete(fd);
// 		sock_epoll_delete(epoll_fd,fd);
// 		close(filefd);
// 		close(fd);        
// 	}
// 	else if(type == 0)
// 	{
// 		unsigned int filefd = get_file_fd();
// 		if( filefd < 0)
// 		{
// 			exit(-1);
// 		}
// 		map_insert(fd,filefd);
// 	}
// 	unsigned int size = len;
// 	printf("recv length =%d\n",len);
// 	while( size > 0)
// 	{
// 		int rlen  = read(fd,pCur,len);
// 		if( rlen > 0)
// 		{
// 			size  -= rlen;
// 			pCur  += rlen;
// 		}
// 		else if( rlen == 0 && size <=0)
// 		{
// 			break;
// 		}
// 		else if( rlen < 0 && errno ==EAGAIN)
// 		{
// 			if( ++time > 100)
// 			{
// 				break;
// 			}
// 			continue;
// 		}
// 		else
// 		{
// 			free(pmsgReq);
// 			exit(-1);			
// 		}
// 	}	
// 	unsigned int filefd = map_find(fd);
// 	int wlen  = write(filefd,pmsgReq->sBuf,len);
// 	if(wlen < 0)
// 		exit(-1);
// 	printf("write len=%d\n",wlen);
// 	if(wlen == len)
// 	{
// 		free(pmsgReq);
// 	}
// 	do_send_msg(epoll_fd,fd,type);
	return ;
}
int main(int argc,char *argv[])
{
	//int listenfd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	int listenfd = socket(PF_INET,SOCK_STREAM,0);

	struct sockaddr_in ser_addr;
	init_addr(&ser_addr);
	int ret = sock_bind(listenfd,ser_addr);
	if(ret < 0)
	{
		perror("bind");
		exit(-1);
	}
	//reuseraddr and set noblock

	ret = sock_reuseaddr(listenfd);
	if( ret < 0)
	{
		perror("setsockopt");
		exit(-1);
	}
	printf("setsockopt succ\n");

	ret = sock_setNoNblock(listenfd);
	if( ret < 0)
	{
		perror("setNoNblock");
		exit(-1);
	}	
	printf("setNoNblock succ\n");


	struct epoll_event events[1024];
	int epoll_fd = epoll_create(MAXCONNECT);
	if(epoll_fd < 0)
	{
		perror("epoll create");
		exit(-1);
	}
	ret = sock_epoll_reg(epoll_fd,listenfd,EPOLLIN | EPOLLOUT | EPOLLHUP);
	if( ret < 0)
	{
		perror("epoll reg");
		exit(-1);
	}
	ret = listen(listenfd,MAXCONNECT);
	if( ret < 0)
	{
		perror("listen");
		exit(-1);
	}
	printf("listen succ \n");
	while(1)
	{
		int efds = epoll_wait(epoll_fd,events,20,1);
		int i = 0;
		for(;i< efds;++i)
		{
			int cur_fd = events[i].data.fd ;
			if(cur_fd == listenfd)
			{
				if( !(events[i].events & EPOLLIN))
				{
					continue;
				}
				int fd = -1;
				printf("cur_fd\n");
				while( (fd = accept(listenfd,NULL,NULL)) > 0)
				{
					sock_setNoNblock(fd);
					printf("a client accept\n");
					if( sock_epoll_reg(epoll_fd,fd,EPOLLIN|EPOLLERR|EPOLLHUP) < 0)
					{
						perror(
							"cliet epoll reg");
						exit(-1);
					}
				}
			}
			else if(cur_fd&EPOLLIN)
			{
				printf("client send message to server\n");
				if(!(events[i].events & EPOLLIN))
				{   
					printf("continue\n");
	        		continue;
				}
				do_recv_msg(epoll_fd,cur_fd);
			}
            else if(cur_fd&EPOLLOUT)
            {
                
            }
            else
            {

            }
		}
	}
}

