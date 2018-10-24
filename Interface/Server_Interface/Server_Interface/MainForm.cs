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
    public partial class MainForm : Form
    {
        private TcpClient interfaceClient;
        private InputForm inputForm;
        private NetworkStream stream;

        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            AskUserForIP();
        }

        private void AskUserForIP()
        {
            bool error = false;
            bool succes = false;

            while (!succes)
            {
                inputForm = new InputForm(error);
                this.Hide();
                inputForm.ShowDialog();
                this.Show();

                if (inputForm.DialogResult == DialogResult.Cancel)
                {
                    this.Close();
                    return;
                }

                succes = Connect();
            }
        }

        private bool Connect()
        {
            interfaceClient = new TcpClient();
            try
            {
                interfaceClient.Connect(inputForm.ServerIPAdress, inputForm.ServerPort);
                stream = interfaceClient.GetStream();
                SendData("interface");
            return interfaceClient.Connected;
            }
            catch
            {
                return false;
            }
        }

        private void Disconnect_btn_Click(object sender, EventArgs e)
        {
            interfaceClient.Close();
            AskUserForIP();
        }

        private void SendData_btn_Click(object sender, EventArgs e)
        {
            string message = textBox3.Text;
            // Translate the passed message into ASCII and store it as a Byte array.
            Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);

            // Get a client stream for reading and writing. 
            NetworkStream stream = interfaceClient.GetStream();

            // Send the message to the connected TcpServer. 
            stream.Write(data, 0, data.Length); //(**This is to send data using the byte method**)  

        }

        private void GetData_btn_Click(object sender, EventArgs e)
        {
            List<Byte> buffer = new List<Byte>();
            NetworkStream stream = interfaceClient.GetStream();
            GetData_btn.Text = "Reading...";
            while (stream.DataAvailable)
            {
                Byte[] data = new Byte[256];

                // String to store the response ASCII representation.
                string recievedByte = string.Empty;

                // Read the first batch of the TcpServer response bytes.
                Int32 readedBytes = stream.Read(data, 0, data.Length);
                recievedByte = System.Text.Encoding.ASCII.GetString(data, 0, readedBytes); //(**This converts it to string**)

                RecievedData_listBox.Items.Add(recievedByte);
            }
        }

        private void SendData(string text)
        {
            byte[] data = Encoding.ASCII.GetBytes(text);
            Console.WriteLine("Sending message to the Server");
            stream.Write(data, 0, data.Length);
        }
    }
}
