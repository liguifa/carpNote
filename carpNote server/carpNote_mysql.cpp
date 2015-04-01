#include <carpNote_mysql.h>
#include <iostream>
#include <string>

using namespace std;

//链接数据库
void carpNoteSQL::carpNoteSQL()
{
	SQLCon=new carpNoteSQL;
	SQLCon->Connect("127.0.0.1","root","");

}

//判断账户是否存在
bool carpNoteSQL::checkUser(string UserName,string UserPW)
{
	string sql="select UserPW from CarpNote.tb_user where UserName='"+UserName+"'";
	char* charSQL=sql.c_str();
	if(SQLCon->SelectQuery(charSQL))
	{
		return true;
	}

	return false;
}