using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace carpNote
{
    class netOP
    {
        public netOP()
        {
            
            clientSocket.Connect(ipep);


        }

        //注册用户，并返回注册结果
        public string  regissterUser(string UserName,string UserPW)
        {
            string msg = UserName +UserPW + "regi";

            clientSocket.Send(Encoding.ASCII.GetBytes(msg));
            
            byte[] data = new byte[1024];

            int recv = clientSocket.Receive(data);

            string tringdata = data.ToString();


            return tringdata;
        }

        //修改账户信息
        public string modifyUserNameOrPW(string UserName, string UserPW, string newUserName, string newUserPW)
        {
            string msg = UserName + UserPW + "mdNP";
            clientSocket.Send(Encoding.ASCII.GetBytes(msg));

            byte[] data = new byte[1024];

            int recv = clientSocket.Receive(data);
            string stringdata = Encoding.ASCII.GetString(data, 0, recv);

            return stringdata;
        }

        ~netOP()
        {
            clientSocket.Close();

        }

        private IPEndPoint ipep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 9050);
        private Socket clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

    }
}
