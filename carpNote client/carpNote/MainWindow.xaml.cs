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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using System.Windows.Interop;

namespace carpNote
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            MouseLeftButtonDown += (o, args) =>
            {
                var hwnd = new WindowInteropHelper(this).Handle;
                ReleaseCapture();
                SendMessage(hwnd, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            };

            fileOP createDir = new fileOP();
            createDir.createFileRootDir("CarpNote");

            List<string> bookNameList = createDir.traBook();

            for (int i = 0; i < bookNameList.Count;i++ )
            {
                TreeViewItem tvi = new TreeViewItem();
                tvi.Header=bookNameList[i].ToString();
                tv_book_book.Items.Add(tvi);
            }

            ConfigXML userInfo = new ConfigXML();
            UserName = userInfo.getUserID();
            UserPW = userInfo.getUserPW();

        }

        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;
        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int msg, int wParam, int lParam);
        [DllImport("user32.dll")]
        public static extern bool ReleaseCapture();
        public string UserName;
        public string UserPW;

        private void but_Exit_Click_1(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();

        }

        private void but_Login_Click(object sender, RoutedEventArgs e)
        {
            Login loginPage = new Login();
            loginPage.ShowDialog();
        }

        private void but_Setting_Click(object sender, RoutedEventArgs e)
        {
            Setting setPage = new Setting();
            setPage.ShowDialog();
        }

        private void but_syn_Click(object sender, RoutedEventArgs e)
        {
            ConfigXML configXML = new ConfigXML();
            configXML.getUserID();
        }

        private void bt_createBook_Click(object sender, RoutedEventArgs e)
        {
            CreateBook book = new CreateBook();
            book.ShowDialog();
            if (book.bookName==null)
            {
                return;
            }

            TreeViewItem newItem = new TreeViewItem();
            newItem.Header = book.bookName;
            tv_book_book.Items.Add(newItem);

        }

        private void bt_createNote_Click(object sender, RoutedEventArgs e)
        {
            createNote note = new createNote();
            
            if (tv_book.SelectedItem==null)
            {
                MessageBox.Show("请选择一个笔记本!");
                return;
            }
            TreeViewItem selectItem =(TreeViewItem)tv_book.SelectedItem;
            note.bookName = selectItem.Header.ToString();
            note.ShowDialog();

            lb_noteList.Items.Clear();
            TreeViewItem selectItem2 = (TreeViewItem)tv_book.SelectedItem;
            string selectItemName = selectItem2.Header.ToString();
            gb_note.Header = selectItemName;

            fileOP op = new fileOP();
            List<string> noteNameList = op.traNote(selectItemName);
            for (int i = 0; i < noteNameList.Count; i++)
            {
                ListBoxItem note2 = new ListBoxItem();
                note2.Content = noteNameList[i];
                lb_noteList.Items.Add(note2);
            }

        }

        private void tv_book_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            //必须清除遗留下的item
            lb_noteList.Items.Clear();
            TreeViewItem selectItem = (TreeViewItem)tv_book.SelectedItem;
            string selectItemName = selectItem.Header.ToString();
            if (selectItemName=="笔记本")
            {
                return;
            }
            gb_note.Header = selectItemName;

            fileOP op = new fileOP();
            List<string> noteNameList=op.traNote(selectItemName);
            for (int i = 0; i < noteNameList.Count;i++ )
            {
                ListBoxItem note = new ListBoxItem();
                note.Content = noteNameList[i];
                lb_noteList.Items.Add(note);
            }

        }

        private void lb_noteList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            fileOP op = new fileOP();
            ListBoxItem noteUse = new ListBoxItem();
            noteUse = (ListBoxItem)lb_noteList.SelectedItems[0];
            string noteUseFileName = noteUse.Content.ToString();//笔记名称
            TreeViewItem selectItem = (TreeViewItem)tv_book.SelectedItem;
            string selectItemName = selectItem.Header.ToString();//笔记本名称
            string fileContent = op.readToNote(selectItemName, noteUseFileName);
            htmlEditor.ContentHtml = fileContent;//为编辑框添加内容

        }
    }
}
