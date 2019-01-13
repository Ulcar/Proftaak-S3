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
using System.Threading;

namespace Server_Interface
{
    public partial class MainForm : Form
    {
        private WiFiHandler wiFiHandler;
        private InputForm inputForm = new InputForm();
        private BindingList<Client> clients;
        private BindingList<string> consoleOutput;
        private Thread communicationThread;
        private int liters;
        private int power;

        public MainForm()
        {
            InitializeComponent();
            clients = new BindingList<Client>();
            consoleOutput = new BindingList<string>();
            ClientList.DataSource = clients;
            ConsoleList.DataSource = consoleOutput;
            liters = 0;
            power = 0;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            AskUserForIP();
        }

        private void Disconnect_btn_Click(object sender, EventArgs e)
        {
            Disconnect();
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

                if(temp.Enabled == 1)
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
                List<string> message = new List<string> { temp.Enabled + "" };
                wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_SETCLIENT, message));
            }
        }

        private void SendCmdBtn_Click(object sender, EventArgs e)
        {
            SendCmd();
        }

        private void SendCmdBtn_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                SendCmd();
            }
        }






        private void AskUserForIP()
        {
            bool error = false;
            bool succes = false;

            while (!succes)
            {
                communicationThread = null;

                inputForm.SetError(error);
                this.Hide();
                inputForm.ShowDialog();
                this.Show();

                if (inputForm.ServerPort == 666)
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

            List<string> value = new List<string> { "1" };
            wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_GETCLIENTS, value));

            communicationThread = new Thread(Reload);
            communicationThread.Start();
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

        private void Disconnect()
        {
            wiFiHandler = null;
            clients.Clear();
            consoleOutput.Clear();
            liters = 0;
            power = 0;

            DataGroupbox.Visible = false;

            AskUserForIP();
        }

        private void AddClient(Client client)
        {
            for (int i = 0; i < clients.Count; i++)
            {
                if (clients[i].MacAdress == client.MacAdress)
                {
                    power -= clients[i].ElecUsage;
                    liters -= clients[i].WaterUsage;
                    clients[i] = client;
                    return;
                }
            }
            power += client.ElecUsage;
            liters += client.WaterUsage;

            clients.Add(client);
        }

        private void Reload()
        {
            while (wiFiHandler != null)
            {
                List<string> messages = wiFiHandler.Receivedata();

                foreach (string message in messages)
                {
                    List<string> data = Protocol.SplitString(message);

                    if (data.Count <= 1)
                        return;

                    try
                    {
                        switch ((CP_Code)Int16.Parse(data[0]))
                        {
                            case CP_Code.CP_CODE_CONNECT:
                                if (data[1] == "1")
                                    Disconnect();
                                break;

                            case CP_Code.CP_CODE_CONSOLE:
                                consoleOutput.Add(data[1]);
                                break;

                            case CP_Code.CP_CODE_DISABLEALLCLIENTS:
                                if (data[1] == "1")
                                    return;
                                consoleOutput.Add("All clients disabled, refreshing...");
                                List<string> value = new List<string> { "1" };
                                wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_GETCLIENTS, value));
                                break;

                            case CP_Code.CP_CODE_GETCLIENTS:
                                if (data.Count == 6)
                                {
                                    AddClient(new Client(data[1], Int16.Parse(data[2]), Int16.Parse(data[3]), data[4], Int16.Parse(data[5])));
                                }

                                break;

                            case CP_Code.CP_CODE_SETCLIENT:
                                consoleOutput.Add("Change accepted: " + data[1]);
                                break;

                            case CP_Code.CP_CODE_TOTALPOWER:
                                TotalWattLb.Text = data[1] + " W";
                                break;

                            case CP_Code.CP_CODE_TOTALWATER:
                                TotalWaterLb.Text = data[1] + " L";
                                break;
                        }
                    }
                    catch
                    {
                        consoleOutput.Add("~Received invalid message: " + message);
                    }
                }
            }
        }

        private void SendCmd()
        {
            if(ConsoleInputTb.Text == "reload")
            {

                List<string> value = new List<string> { "1" };
                wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_GETCLIENTS, value));
            }
            else
            {
                List<string> message = new List<string> { ConsoleInputTb.Text };
                wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_CONSOLE, message));
            }
            ConsoleInputTb.Clear();
        }

        private void ReloadBtn_Click(object sender, EventArgs e)
        {
            TotalWaterLb.Text = liters + " L";
            TotalWattLb.Text = power + " W";
            ClientList.DataSource = null;
            ConsoleList.DataSource = null;
            ClientList.DataSource = clients;
            ConsoleList.DataSource = consoleOutput;
        }
    }
}
