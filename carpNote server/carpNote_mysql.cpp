#include "carpNote_mysql.h"
#include "encapsulation_mysql.h"
//using EncapMysql::CEncapMysql;

//链接数据库
 carpNoteSQL::carpNoteSQL()
{
    SQLCon=new CEncapMysql;
	SQLCon->Connect("127.0.0.1","root","");

}

//判断账户是否存在
bool carpNoteSQL::checkUser(string UserName,string UserPW)
{
	string sql="select UserPW from CarpNote.tb_user where UserName=='"+UserName+"'";
	const char *charSQL=sql.c_str();
	if(SQLCon->SelectQuery(charSQL))
	{
		return true;
	}

	return false;
}

//添加账户
bool carpNoteSQL::addUser(string UserName,string UserPW)
{
	string sql="insert into CarpNote.tb_user(UserName,UserPW) values('"+UserName+"','"+UserPW+"')";
	const char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return  true;
}

//修改账户名
bool carpNoteSQL::modifyUserName(string UserName,string newUserName)
{
	string sql="update CarpNote.tb_user set UserName='"+newUserName+"' where UserName=='"+UserName+"'";
	const char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//修改用户名
bool carpNoteSQL::modifyUserPW(string UserName,string newUserPW)
{
	string sql="update CarpNote.tb_user set UserPW='"+newUserPW+"' where UserName=='"+UserName+"'";
	const char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//得到用户id
string carpNoteSQL::getUserIDByUserName(string UserName)
{
	string sql="select UserID from CarpNote.tb_user where UserName=='"+UserName+"'";
	const char* charSQL=sql.c_str();
	string str;
	SQLCon->SelectQuery(charSQL);
	while (char **r=SQLCon->FetchRow())
	{
		str=r[0];
	}

	return str;
}

//添加笔记本
bool carpNoteSQL::addBook(string UserName,string bookName)
{
	string UserID=getUserIDByUserName(UserName);
	string sql="insert into CarpNote.tb_book(UserID,bookName) values("+UserID+",'"+bookName+"')";
	const char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//修改笔记本名
bool carpNoteSQL::modifyBookName(string UserName, string BookName,string newBookName)
{
	string UserID=getUserIDByUserName(UserName);
	string sql="update CarpNote.tb_book set bookName='"+newBookName+"' where UserID=="+UserID+"bookName=='"+BookName+"'";
	const char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//得到用户的笔记本id
string carpNoteSQL::getBookIDByBookName(string UserName,string BookName)
{
	string UserID=getUserIDByUserName(UserName);
	string sql="select bookID from CarpNote.tb_user where UserID=="+UserID+"&&bookName=='"+BookName+"'";
	const char* charSQL=sql.c_str();
	string str;
	SQLCon->SelectQuery(charSQL);
	while (char **r=SQLCon->FetchRow())
	{
		str=r[0];
	}

	return str;
}

//添加笔记
bool carpNoteSQL::addNote(string UserName,string BookName,string NoteName)
{
	string UserID=getUserIDByUserName(UserName);
	string BookID=getBookIDByBookName(UserName,BookName);
	string sql="insert into CarpNote.tb_note(UserId,bookID,NoteName) values("+UserID+","+BookID+",'"+NoteName+"')";

	const char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//修改笔记的名称
bool  carpNoteSQL::modifyNoteName(string UserName,string BookName,string NoteName,string newNoteName)
{
	string UserID=getUserIDByUserName(UserName);
	string BookID=getBookIDByBookName(UserName,BookName);
	string sql="update CarpNote.tb_note set noteName='"+newNoteName+"' where UserID=="+UserID+"&&bookID=="+BookID;
	const char* charSQL=sql.c_str();
	SQLCon->ModifyQuery(charSQL);

	return true;
}

//得到某个用户的笔记本列表
vector<string> carpNoteSQL::getUserBook(string UserName)
{
	string UserID=getUserIDByUserName(UserName);
	string sql="select bookName from CarpNote.tb_book where UserID=="+UserID;
	const char* charSQL=sql.c_str();
    int i=0;
	vector<string> str;
	SQLCon->SelectQuery(charSQL);
	while (char **r=SQLCon->FetchRow())
	{
		str[i++]=r[0];
	}

	return str;
}

//得到某个用户的某个笔记本的笔记列表
vector<string> carpNoteSQL::getBookNoteName(string UserName,string BookName)
{
	string UserID=getUserIDByUserName(UserName);
	string BookID=getBookIDByBookName(UserName,BookName);
	string sql="select noteName from CarpNote.tb_note where UserID=="+UserID+"&& bookID="+BookID;
	const char* charSQL=sql.c_str();
	vector<string> str;
    int i=0;
	SQLCon->SelectQuery(charSQL);
	while (char **r=SQLCon->FetchRow())
	{
		str[i++]=r[0];
	}

	return str;


}
