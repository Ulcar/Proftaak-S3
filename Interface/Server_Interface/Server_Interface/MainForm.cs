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
        private WiFiHandler wiFiHandler;
        private InputForm inputForm = new InputForm();
        private List<Client> clients;

        public MainForm()
        {
            InitializeComponent();
            clients = new List<Client>();
            ClientList.DataSource = clients;
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
                inputForm.SetError(error);
                this.Hide();
                inputForm.ShowDialog();
                this.Show();

                if(inputForm.ServerPort == 666)
                {
                    succes = true;
                    return;
                }

                if (inputForm.DialogResult == DialogResult.Cancel)
                {
                    this.Close();
                    return;
                }

                succes = Connect();
                error = true;
            }
        }

        private bool Connect()
        {
            try
            {
                wiFiHandler = new WiFiHandler(inputForm.ServerIPAdress, inputForm.ServerPort);
                if (wiFiHandler == null)
                    return false;
            }
            catch
            {
                return false;
            }
            return true;
        }

        private void Disconnect_btn_Click(object sender, EventArgs e)
        {
            Disconnect();
        }

        private void Disconnect()
        {
            wiFiHandler = null;
            clients.Clear();
            ConsoleList.Items.Clear();

            DataGroupbox.Visible = false;

            AskUserForIP();
        }

        private void SendCmdBtn_Click(object sender, EventArgs e)
        {
            List<string> message = new List<string> { ConsoleInputTb.Text };
            wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_CONNECT, message));
        }

        private void ClientList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if ((ClientList.SelectedItem != null) && (ClientList.SelectedItem is Client))
            {
                Client temp = ClientList.SelectedItem as Client;
                DataGroupbox.Visible = true;
                CurrentClientLb.Text = temp.MacAdress;
                ElecUsageLb.Text = temp.ElecUsage + " W";
                WaterUsageLb.Text = temp.WaterUsage + " L";
                CurrentProgramLb.Text = temp.CurrProgram;

                if(temp.Enabled)
                {
                    EnabledLb.Text = "true";
                    ToggleEnabledBtn.Text = "Disable";
                }
                else
                {
                    EnabledLb.Text = "false";
                    ToggleEnabledBtn.Text = "Enable";
                }
            }
            else
            {
                DataGroupbox.Visible = false;
            }
        }

        private void ToggleEnabledBtn_Click(object sender, EventArgs e)
        {
            if ((ClientList.SelectedItem != null) && (ClientList.SelectedItem is Client))
            {
                Client temp = ClientList.SelectedItem as Client;
                EnabledLb.Text = "xx";
                ToggleEnabledBtn.Text = "Refresh";
                List<string> message = new List<string> { temp.Enabled + "" };
                wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_SETCLIENT, message));
            }
        }

        private void AddClient(Client client)
        {
            for (int i = 0; i < clients.Count; i++)
            {
                if (clients[i].MacAdress == client.MacAdress)
                {
                    clients[i] = client;
                    return;
                }
            }
            clients.Add(client);
            ClientList.SelectedIndex = 0;
        }

        private void RefreshBtn_Click(object sender, EventArgs e)
        {
            ClientList.Items.Clear();
            List<string> messages = wiFiHandler.Receivedata();

            foreach (string message in messages)
            {
                List<string> data = Protocol.SplitString(message);

                if (data.Count <= 1)
                    return;

                switch((CP_Code) Int16.Parse(data[0]))
                {
                    case CP_Code.CP_CODE_CONNECT:
                        if (data[1] == "1")
                            Disconnect();
                        break;

                    case CP_Code.CP_CODE_CONSOLE:
                        ConsoleList.Items.Add(data[1]);
                        break;

                    case CP_Code.CP_CODE_DISABLEALLCLIENTS:
                        if (data[1] == "1")
                            return;
                        ConsoleList.Items.Add("All clients disabled, refreshing...");
                        List<string> value = new List<string> { "1" };
                        wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_GETCLIENTS, value));
                        break;

                    case CP_Code.CP_CODE_GETCLIENTS:
                        if (data.Count == 6)
                        AddClient(new Client(data[1], Int16.Parse(data[2]), Int16.Parse(data[3]), data[4], Boolean.Parse(data[5])));
                        break;

                    case CP_Code.CP_CODE_SETCLIENT:
                        ConsoleList.Items.Add("Change accepted: " + data[1]);
                        break;

                    case CP_Code.CP_CODE_TOTALPOWER:
                        TotalWattLb.Text = data[1] + " W";
                        break;

                    case CP_Code.CP_CODE_TOTALWATER:
                        TotalWaterLb.Text = data[1] + " L";
                        break;
                }
            }
        }
    }
}
