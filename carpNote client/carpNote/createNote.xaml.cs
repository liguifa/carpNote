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
    /// createNote.xaml 的交互逻辑
    /// </summary>
    public partial class createNote : Window
    {
        public createNote()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            if (textBox1.Text.ToString()==null)
            {
                MessageBox.Show("请输入笔记本名称!");
                return;
            }
            fileOP noteCreate = new fileOP();
            noteCreate.createNoteFile(bookName, textBox1.Text.ToString());

            this.Close();
        }

        //记录笔记的名称
        public string noteName=null;
        //记录笔记本的名称
        public string bookName=null;

    }
}
