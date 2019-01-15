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
        private List<Client> clients;
        private List<string> consoleOutput;
        private Thread communicationThread;
        private int liters;
        private int power;
        private bool consoleOutputEdited;
        private bool clientsEdited;
        private bool disconnect;
        private System.Windows.Forms.Timer timer;

        public MainForm()
        {
            InitializeComponent();
            timer = new System.Windows.Forms.Timer();
            clients = new List<Client>();
            consoleOutput = new List<string>();
            ClientList.DataSource = clients;
            ConsoleList.DataSource = consoleOutput;
            liters = 0;
            power = 0;
            consoleOutputEdited = false;
            clientsEdited = false;
            DataGroupbox.Visible = false;
            disconnect = false;

            timer.Tick += new EventHandler(Timer_Tick);
            timer.Interval = 1000;              // Timer will tick evert second
            timer.Enabled = true;
            timer.Start();
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
                string fu;
                if(temp.Enabled == 1)
                {
                    fu = 0 + "";
                }
                else
                {
                    fu = 1 + "";
                }
                List<string> list = new List<string> { temp.MacAdress, fu };
                wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_SETCLIENT, list));
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

        private void DisableClientsBtn_Click(object sender, EventArgs e)
        {
            wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_DISABLEALLCLIENTS, "0"));
        }

        private void ReloadBtn_Click(object sender, EventArgs e)
        {
            wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_GETCLIENTS, "1"));
        }

        private void LaundryBtn_Click(object sender, EventArgs e)
        {
            decimal pounds = PoundsNummericUpDown.Value;
            string machines = "";
            int color;
            int temperature;

            if (pounds <= 0)
            {
                consoleOutput.Add("~Enter a valid weight");
                consoleOutputEdited = true;
                return;
            }

            if (ColorLightRadioButton.Checked)
            {
                color = 0;
            }
            else if (ColorDarkRadioButton.Checked)
            {
                color = 1;
            }
            else
            {
                color = 2;
            }

            if (TempColdRadioButton.Checked)
            {
                temperature = 0;
            }
            else if (TempWarmRadioButton.Checked)
            {
                temperature = 1;
            }
            else
            {
                temperature = 2;
            }

            if (WashingMachineCheckBox.Checked)
            {
                machines += " 0";
            }
            if (DryerCheckBox.Checked)
            {
                machines += " 1";
            }
            if (CentrifugeCheckBox.Checked)
            {
                machines += " 2";
            }
            if (SteamerCheckBox.Checked)
            {
                machines += " 3";
            }

            if(machines == "")
            {
                consoleOutput.Add("~Select minimal 1 machine");
                consoleOutputEdited = true;
                return;
            }
            
            wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_CONSOLE, "laundry add " + pounds + " " + temperature + " " + color + machines));

        }






        void Timer_Tick(object sender, EventArgs e)
        {
            TotalWaterLb.Text = liters + " L";
            TotalWattLb.Text = power + " W";
            if (clientsEdited)
            {
                ClientList.DataSource = null;
                ClientList.DataSource = clients;
                clientsEdited = false;
            }

            if (consoleOutputEdited)
            {
                ConsoleList.DataSource = null;
                ConsoleList.DataSource = consoleOutput;
                consoleOutputEdited = false;
                ConsoleList.SelectedIndex = ConsoleList.Items.Count - 1;
            }

            if(disconnect)
            {
                disconnect = false;
                Disconnect();
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
            clientsEdited = true;
            consoleOutput.Clear();
            consoleOutputEdited = true;
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
                    power += client.ElecUsage;
                    liters += client.WaterUsage;
                    clients[i] = client;
                    clientsEdited = true;
                    return;
                }
            }
            power += client.ElecUsage;
            liters += client.WaterUsage;

            clients.Add(client);
            clientsEdited = true;
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
                                    disconnect = true;
                                
                                wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_GETCLIENTS, "1"));
                                break;

                            case CP_Code.CP_CODE_CONSOLE:
                                AddControlOutput(data[1]);
                                break;

                            case CP_Code.CP_CODE_DISABLEALLCLIENTS:
                                if (data[1] == "1")
                                    return;
                                consoleOutput.Add("All clients disabled, refreshing...");
                                consoleOutputEdited = true;
                                wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_GETCLIENTS, "1"));
                                break;

                            case CP_Code.CP_CODE_GETCLIENTS:
                                if (data.Count == 6)
                                {
                                    AddClient(new Client(data[1], Int16.Parse(data[2]), Int16.Parse(data[3]), data[4], Int16.Parse(data[5])));
                                }

                                break;

                            case CP_Code.CP_CODE_SETCLIENT:
                                consoleOutput.Add("Change accepted: " + data[1]);
                                consoleOutputEdited = true;
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
                        consoleOutputEdited = true;
                    }
                }
            }
        }

        private void SendCmd()
        {
            if (ConsoleInputTb.Text == "clear")
            {
                for (int i = 0; i < 15; i++)
                {
                    consoleOutput.Add("");
                }
                consoleOutputEdited = true;
            }
            else
            {
                wiFiHandler.Sendmessage(Protocol.MakeString(CP_Code.CP_CODE_CONSOLE, ConsoleInputTb.Text));
            }
            ConsoleInputTb.Clear();
        }

        private void AddControlOutput(string message)
        {
            while(true)
            {
                int index = message.IndexOf('[', 2);

                if(index == -1)
                {
                    consoleOutput.Add(message);
                    break;
                }
                consoleOutput.Add(message.Substring(0, index));
                message = message.Substring(index, message.Length - index - 1);
                
            }
            consoleOutputEdited = true;
        }
    }
}
