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

namespace carpNote
{
    /// <summary>
    /// CreateBook.xaml 的交互逻辑
    /// </summary>
    public partial class CreateBook : Window
    {
        public CreateBook()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            fileOP userDir = new fileOP();
            userDir.createFileDir(textBox1.Text.ToString());

            bookName = textBox1.Text.ToString();

            this.Close();
        }

        //供主窗体设置笔记本列表
        public string bookName=null;
    }
}
