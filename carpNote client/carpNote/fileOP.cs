using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

//
//包含文件和文件夹的操作，即笔记和笔记本的操作
//
namespace carpNote
{
    class fileOP
    {
        string notePath = System.Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

        //创建文件夹
        public bool createFileDir(string fileDirName)
        {
            if (Directory.Exists(notePath+'\\'+fileDirName)==false)
            {
                Directory.CreateDirectory(notePath + fileDirName);
            }
            return true;
        }

        //创建笔记的文件
        public bool createNoteFile(string book,string note)
        {
            if (File.Exists(notePath+'\\'+book+'\\'+note)==false)
            {
                File.Create(notePath + '\\' + book + '\\' + note);
            }
            return true;
        }

        //删除文件夹
        public bool delFileDir(string fileDirName)
        {
            if (Directory.Exists(notePath + '\\' + fileDirName))
            {
                Directory.Delete(notePath + fileDirName);
            }
            return true;
        }

        //删除笔记文件
        public bool delNoteFile(string book, string note)
        {
            if (File.Exists(notePath + '\\' + book + '\\' + note) == false)
            {
                File.Delete(notePath + '\\' + book + '\\' + note);
            }
            return true;
        }

        //修改文件夹的名字
        public bool modifyFileDirName(string fileDirName,string fileDirNewName)
        {
            if (Directory.Exists(notePath + '\\' + fileDirName))
            {
                Directory.Move(notePath + '\\' + fileDirName, notePath + '\\' + fileDirNewName);
            }

            return true;
        }

        //修改文件名
        public bool modifyFileName(string book, string note,string newNoteName)
        {
            if (File.Exists(notePath + '\\' + book + '\\' + note))
            {
                File.Move(notePath + '\\' + book + '\\' + note, notePath + '\\' + book + '\\' + newNoteName);

            }

            return true;
        }

        //向笔记中写内容
        public bool writeToNote(string book,string note,string content)
        {
            if (File.Exists(notePath + '\\' + book + '\\' + note))
            {
                //StreamWriter sw = new StreamWriter(notePath + '\\' + book + '\\' + note),Encoding.GetEncoding("gb2312"));
                File.WriteAllText((notePath + '\\' + book + '\\' + note), content, Encoding.GetEncoding("gb2312"));
            }

            return true;
        }
        

    }
}
