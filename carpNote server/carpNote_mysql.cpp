#include <carpNote_mysql.h>
#include <iostream>
#include <string>

using namespace std;

//�������ݿ�
void carpNoteSQL::carpNoteSQL()
{
	SQLCon=new carpNoteSQL;
	SQLCon->Connect("127.0.0.1","root","");

}

//�ж��˻��Ƿ����
bool carpNoteSQL::checkUser(string UserName,string UserPW)
{
	string sql="select UserPW from CarpNote.tb_user where UserName=='"+UserName+"'";
	char* charSQL=sql.c_str();
	if(SQLCon->SelectQuery(charSQL))
	{
		return true;
	}

	return false;
}

//����˻�
bool carpNoteSQL::addUser(string UserName,string UserPW)
{
	string sql="insert into CarpNote.tb_user(UserName,UserPw) values('"+UaerName+"','"+UserPW+"')";
	char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return  true;
}

//�޸��˻���
bool carpNoteSQL::modifyUserName(string UserName,string newUserName)
{
	string sql="update CarpNote.tb_user set UserName='"+newUserName+"' where UserName=='"+UserName+"'";
	char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//�޸��û���
bool carpNoteSQL::modifyUserPW(string UserName,string newUserPW)
{
	string sql="update CarpNote.tb_user set UserPW='"+newUserPW+"' where UserName=='"+UserName+"'";
	char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//�õ��û�id
string carpNoteSQL::getUserIDByUserName(string UserName)
{
	string sql="select UserID from CarpNote.tb_user where UserName=='"+UserName+"'";
	char* charSQL=sql.c_str();
	string str;
	SQLCon->SelectQuery(charSQL);
	while (char **r=SQLCon->FetchRow())
	{
		str=r[0];
	}

	return str;
}

//��ӱʼǱ�
bool carpNoteSQL::addBook(string UserName,string bookName)
{
	string UserID=getUserIDByUserName(UserName);
	string sql="insert into CarpNote.tb_book(UserID,bookName) values("+UserID+",'"bookName+"')";
	char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//�޸ıʼǱ���
bool carpNoteSQL::modifyBookName(string UserName, string BookName,string newBookName)
{
	string UserID=getUserIDByUserName(UserName);
	string sql="update CarpNote.tb_book set bookName='"+newBookName+"' where UserID=="+UserID+"bookName=='"+BookName+"'";
	char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//�õ��û��ıʼǱ�id
string carpNoteSQL::getBookIDByBookName(string Username,string BookName)
{
	string UserID=getUserIDByUserName(UserName);
	string sql="select bookID from CarpNote.tb_user where UserID=="+UserID+"&&bookName=='"+BookName+"'";
	char* charSQL=sql.c_str();
	string str;
	SQLCon->SelectQuery(charSQL);
	while (char **r=SQLCon->FetchRow())
	{
		str=r[0];
	}

	return str;
}

//��ӱʼ�
bool carpNoteSQL::addNote(string UserName,string BookName,string NoteName)
{
	string UserID=getUserIDByUserName(UserName);
	string BookID=getBookIDByBookName(UserName,BookName);
	string sql="insert into CarpNote.tb_note(UserId,bookID,NoteName) values("+UserID+","+BookID+",'"+NoteName+"')";

	char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//�޸ıʼǵ�����
bool  carpNoteSQL::modifyNoteName(string UserName,string BookName,string NoteName,string newNoteName)
{
	string UserID=getUserIDByUserName(UserName);
	string BookID=getBookIDByBookName(UserName,BookName);
	string sql="update CarpNote.tb_note set noteName='"+newNoteName+"' where UserID=="+UserID+"&&bookID=="+BookID;
	char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//�õ�ĳ���û��ıʼǱ��б�
vector<string> carpNoteSQL::getUserBook(string UserName)
{
	string UserID=getUserIDByUserName(UserName);
	string sql="select bookName from CarpNote.tb_book where UserID=="+UserID;
	char* charSQL=sql.c_str();
	vector<string> str;
	SQLCon->SelectQuery(charSQL);
	while (char **r=SQLCon->FetchRow())
	{
		str=r[0];
	}

	return str;
}

//�õ�ĳ���û���ĳ���ʼǱ��ıʼ��б�
vector<string> carpNoteSQL::getBookNoteName(string UserName,string BookName)
{
	string UserID=getUserIDByUserName(UserName);
	string BookID=getBookIDByBookName(UserName,BookName);
	string sql="select noteName from CarpNote.tb_note where UserID=="+UserID+"&& bookID="+BookID;
	char* charSQL=sql.c_str();
	vector<string> str;
	SQLCon->SelectQuery(charSQL);
	while (char **r=SQLCon->FetchRow())
	{
		str=r[0];
	}

	return str;


}