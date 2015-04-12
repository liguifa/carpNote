using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;


namespace carpNote
{
    class ConfigXML
    {
        XmlNode root = null;//根节点
        public ConfigXML()
        {

            XmlDataDocument configXMLDocu = new XmlDataDocument();
            configXMLDocu.Load("./config.xml");
            root = configXMLDocu.DocumentElement;
            
        }

        //得到用户账号
        public string getUserID()
        {    
            XmlNode UserIDNode = root.SelectSingleNode("UserID");
            return UserIDNode.InnerText;
        }

        //修改用户账户
        public bool setUserID(string UserID)
        {
            XmlNode UserIDNode = root.SelectSingleNode("UserID");
            UserIDNode.InnerText = UserID;

            return true;
        }

        //得到用户密码
        public string getUserPW()
        {
            XmlNode UserPWNode = root.SelectSingleNode("UserPW");
            return UserPWNode.InnerText;
        }

        //修改用户密码
        public bool setUserPW(string UserPW)
        {
            XmlNode UserPWNode = root.SelectSingleNode("UserPW");
            UserPWNode.InnerText = UserPW;

            return true;
        }

        //得到最后看的笔记本
        public string getLastUseBook()
        {
            XmlNode lastUseBook = root.SelectSingleNode("lastUseBook");
            return lastUseBook.InnerText;
        }

        //设置最后看的笔记本
        public bool SetLastUseBook(string UseBook)
        {
            XmlNode lastUseBook = root.SelectSingleNode("lastUseBook");
            lastUseBook.InnerText = UseBook;

            return true;
        }

        //设置最后使用的笔记
        public string getLastUseNote()
        {
            XmlNode lastUseNote = root.SelectSingleNode("lastUseNote");
            return lastUseNote.InnerText;
        }

        //设置最后使用的笔记
        public bool SetLastUseNote(string UseNote)
        {
            XmlNode lastUseNote = root.SelectSingleNode("lastUseNote");
            lastUseNote.InnerText = UseNote;

            return true;
        }

        public bool addBook(string bookName)
        {
            XmlNode UserBook = root.SelectSingleNode("UserBook");
            //XmlElement newBook = new XmlElement("book",bookName,new Attributes(""));
            XmlDocument doc = new XmlDocument();
            //XmlAttribute attr = doc.CreateAttribute("updataStat");
            XmlElement newBook = doc.CreateElement("book");
            newBook.InnerText = bookName;
            newBook.SetAttribute("updataStat", "false");
            UserBook.AppendChild(newBook);

            
            return true;
        }

        //暂时不实现为垃圾回收做准备
        public bool delBook(string bookName)
        {

            return true;
        }

        public bool addNote(string bookName, string noteName)
        {
            XmlNode UserBook = root.SelectSingleNode("UserBook");
            XmlNode book = UserBook.SelectSingleNode(bookName);
            XmlDocument doc = new XmlDocument();
            XmlElement newNote = doc.CreateElement("note");
            newNote.InnerText = noteName;
            newNote.SetAttribute("updataStat", "false");
            book.AppendChild(newNote);
            
            return true;
        }

        //
        //暂时不实现，为以后垃圾回收做准备
        public bool delNote(string bookName, string noteName)
        {

            return true;
        }

        //标记属性来表示笔记是否已经同步
        public bool updataNote(string bookName, string  noteName,string updataStat)
        {
            XmlNode UserBook = root.SelectSingleNode("UserBook");
            XmlNode book = UserBook.SelectSingleNode(bookName);
            XmlNode note = book.SelectSingleNode(noteName);
            note.Attributes[0].Value = updataStat;

            return true;
        }

        //标记属性来表示笔记本是否已经同步
        public bool updataBook(string bookName,string updataStat)
        {
            XmlNode UserBook = root.SelectSingleNode("UserBook");
            XmlNode book = UserBook.SelectSingleNode(bookName);
            book.Attributes[0].Value = updataStat;

            return true;
        }
    }
}
