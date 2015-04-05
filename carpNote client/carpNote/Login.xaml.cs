using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

/*using netOP;*/


namespace carpNote
{
    /// <summary>
    /// Login.xaml 的交互逻辑
    /// </summary>
    public partial class Login : Window
    {
        public Login()
        {
            InitializeComponent();
        }

        //保存账户
        private void but_Close_Click(object sender, RoutedEventArgs e)
        {
            ConfigXML xmlOP = new ConfigXML();
            if (tb_UserID.Text.ToString() == null || tb_UserPW.Password.ToString() == null)
            {
                MessageBox.Show("请输入账号或密码！");
                tb_UserID.Text = "";
                tb_UserPW.Password = "";

                return;
            }

            if (tb_UserID.Text.ToString().Length != 8 || tb_UserPW.Password.ToString().Length != 8)
            {
                MessageBox.Show("密码和账户必须为8位！");
                return;
            }

            xmlOP.setUserID(tb_UserID.Text.ToString());
            xmlOP.setUserPW(tb_UserPW.Password.ToString()); 
        }


        private void button1_Click(object sender, RoutedEventArgs e)
        {
            netOP OP=new netOP();
            if (tb_UserID.Text.ToString() == null || tb_UserPW.Password.ToString()==null)
            {
                MessageBox.Show("请输入账号或密码！");
                tb_UserID.Text = "";
                tb_UserPW.Password = "";

                return;
            }

            if (tb_UserID.Text.ToString().Length != 8 || tb_UserPW.Password.ToString().Length!=8)
            {
                MessageBox.Show("密码和账户必须为8位！");
                return;
            }

            string reStr=OP.regissterUser(tb_UserID.Text.ToString(),tb_UserPW.Password.ToString());

            MessageBox.Show(reStr);

        }
    }
}
