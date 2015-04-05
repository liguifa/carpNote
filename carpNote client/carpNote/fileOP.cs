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
        public bool createFileRootDir(string fileDirName)
        {
            if (Directory.Exists(notePath+"\\"+fileDirName)==false)
            {
                Directory.CreateDirectory(notePath + "\\"+fileDirName);
            }
            return true;
        }
        //创建文件夹
        public bool createFileDir(string fileDirName)
        {
            if (Directory.Exists(notePath + "\\"+"CarpNote"+"\\" + fileDirName) == false)
            {
                Directory.CreateDirectory(notePath + "\\" + "CarpNote" + "\\" + fileDirName);
            }
            return true;
        }

        //创建笔记的文件
        public bool createNoteFile(string book,string note)
        {
            if (File.Exists(notePath+'\\'+"CarpNote"+"\\"+book+'\\'+note)==false)
            {
                File.Create(notePath + '\\' + "CarpNote" + "\\" + book + '\\' + note);
            }
            return true;
        }

        //删除文件夹
        public bool delFileDir(string fileDirName)
        {
            if (Directory.Exists(notePath + '\\' + "CarpNote" + "\\" + fileDirName))
            {
                Directory.Delete(notePath + "\\"+"CarpNote"+"\\"+fileDirName);
            }
            return true;
        }

        //删除笔记文件
        public bool delNoteFile(string book, string note)
        {
            if (File.Exists(notePath + '\\' + "CarpNote" + "\\"  +book + '\\' + note) == false)
            {
                File.Delete(notePath + '\\' +"CarpNote"+"\\"+book + '\\' + note);
            }
            return true;
        }

        //修改文件夹的名字
        public bool modifyFileDirName(string fileDirName,string fileDirNewName)
        {
            if (Directory.Exists(notePath + '\\' +"CarpNote"+"\\"+ fileDirName))
            {
                Directory.Move(notePath + '\\' + "CarpNote" + "\\" + fileDirName, notePath + '\\' + "CarpNote" + "\\" + fileDirNewName);
            }

            return true;
        }

        //修改文件名
        public bool modifyFileName(string book, string note,string newNoteName)
        {
            if (File.Exists(notePath + '\\' + "CarpNote" + "\\" + book + '\\' + note))
            {
                File.Move(notePath + '\\' + "CarpNote" + "\\" + book + '\\' + note, notePath + '\\' + "CarpNote" + "\\" + book + '\\' + newNoteName);

            }

            return true;
        }

        //向笔记中写内容
        public bool writeToNote(string book,string note,string content)
        {
            if (File.Exists(notePath + '\\' + "CarpNote" +"\\"+ book + '\\' + note))
            {
                //StreamWriter sw = new StreamWriter(notePath + '\\' + book + '\\' + note),Encoding.GetEncoding("gb2312"));
                File.WriteAllText((notePath + '\\' + "CarpNote" + "\\" + book + '\\' + note), content, Encoding.GetEncoding("gb2312"));
            }

            return true;
        }

        public string readToNote(string book, string note)
        {
            string content=null;
            if (File.Exists(notePath + '\\' + "CarpNote" +"\\"+ book + '\\' + note))
            {
                //StreamWriter sw = new StreamWriter(notePath + '\\' + book + '\\' + note),Encoding.GetEncoding("gb2312"));
                content=File.ReadAllText((notePath + '\\' + "CarpNote" + "\\" + book + '\\' + note), Encoding.GetEncoding("gb2312"));
            }

            return content;
        }

        //遍历文件夹
        public List<string> traBook()
        {
            List<string> bookNnmeList=new List<string>();

            //DriveInfo dvInfo = new DriveInfo(notePath + '\\' + bookName);
            /*DirectoryInfo*/
            DirectoryInfo dirObject = new DirectoryInfo(notePath +"\\"+ "CarpNote" + "\\");
            DirectoryInfo[] dir=dirObject.GetDirectories();
            foreach (DirectoryInfo dirInfo in dir)
            {
                bookNnmeList.Add(dirInfo.Name.ToString());
            }

            return bookNnmeList;
        }

        //遍历文件
        public List<string> traNote(string bookName)
        {
            List<string> noteNameList = new List<string>();
            DirectoryInfo dirObject = new DirectoryInfo(notePath + '\\' + "CarpNote" + "\\" + bookName);
            FileInfo[] file = dirObject.GetFiles();
            foreach (FileInfo fileInfo in file)
            {
                noteNameList.Add(fileInfo.Name.ToString());
            }

            return noteNameList;
        }
        

    }
}
