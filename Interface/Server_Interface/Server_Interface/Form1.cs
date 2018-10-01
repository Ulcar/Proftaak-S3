using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;

namespace Server_Interface
{
    public partial class Form1 : Form
    {
        private TcpClient interfaceClient;
        private int port;

        public Form1()
        {
            InitializeComponent();
        }

        private void Connect_btn_Click(object sender, EventArgs e)
        {
            interfaceClient = new TcpClient();
        }

        private void Disconnect_btn_Click(object sender, EventArgs e)
        {

        }

        private void SendData_btn_Click(object sender, EventArgs e)
        {

        }

        private void GetData_btn_Click(object sender, EventArgs e)
        {

        }
    }
}
