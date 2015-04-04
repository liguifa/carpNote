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

    }
}
