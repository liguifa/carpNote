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
	string sql="select UserPW from CarpNote.tb_user where UserName='"+UserName+"'";
	char* charSQL=sql.c_str();
	if(SQLCon->SelectQuery(charSQL))
	{
		return true;
	}

	return false;
}