﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;

namespace Server_Interface
{
    public partial class InputForm : Form
    {
        public IPAddress ServerIPAdress { get; private set; }
        public int ServerPort { get; private set; }

        public InputForm(bool error)
        {
            InitializeComponent();
            
            DialogResult = DialogResult.Cancel;

            if (error)
            {
                Errorlabel.Text = "Connection refused";
            }
        }

        private void Connect_btn_Click(object sender, EventArgs e)
        {
            if(IPAddress.TryParse(ipTbx.Text, out IPAddress tempIp) && int.TryParse(potrTbx.Text, out int tempPort))
            {
                ServerIPAdress = tempIp;
                ServerPort = tempPort;
                DialogResult = DialogResult.OK;
                this.Close();
                return;
            }

            Errorlabel.Text = "Invalid IP/Port";
        }

        private void Cancel_btn_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
