namespace Server_Interface
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ClientList = new System.Windows.Forms.ListBox();
            this.RefreshBtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.ConsoleList = new System.Windows.Forms.ListBox();
            this.TotalWaterLb = new System.Windows.Forms.Label();
            this.SendCmdBtn = new System.Windows.Forms.Button();
            this.ConsoleInputTb = new System.Windows.Forms.TextBox();
            this.TotalWattLb = new System.Windows.Forms.Label();
            this.ElecUsageLb = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.WaterUsageLb = new System.Windows.Forms.Label();
            this.CurrentProgramLb = new System.Windows.Forms.Label();
            this.ClientGroupbox = new System.Windows.Forms.GroupBox();
            this.ToggleEnabledBtn = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.EnabledLb = new System.Windows.Forms.Label();
            this.CurrentClientLb = new System.Windows.Forms.Label();
            this.ConsoleGroupbox = new System.Windows.Forms.GroupBox();
            this.DataGroupbox = new System.Windows.Forms.GroupBox();
            this.DisconnectBtn = new System.Windows.Forms.Button();
            this.ClientGroupbox.SuspendLayout();
            this.ConsoleGroupbox.SuspendLayout();
            this.DataGroupbox.SuspendLayout();
            this.SuspendLayout();
            // 
            // ClientList
            // 
            this.ClientList.FormattingEnabled = true;
            this.ClientList.Location = new System.Drawing.Point(7, 19);
            this.ClientList.Name = "ClientList";
            this.ClientList.Size = new System.Drawing.Size(316, 264);
            this.ClientList.TabIndex = 0;
            this.ClientList.SelectedIndexChanged += new System.EventHandler(this.ClientList_SelectedIndexChanged);
            // 
            // RefreshBtn
            // 
            this.RefreshBtn.Location = new System.Drawing.Point(300, 62);
            this.RefreshBtn.Name = "RefreshBtn";
            this.RefreshBtn.Size = new System.Drawing.Size(75, 23);
            this.RefreshBtn.TabIndex = 1;
            this.RefreshBtn.Text = "Refresh";
            this.RefreshBtn.UseVisualStyleBackColor = true;
            this.RefreshBtn.Click += new System.EventHandler(this.RefreshBtn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(47, 26);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Client:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(45, 78);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(70, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Water Usage";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(47, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(60, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Elec usage";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(58, 67);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(66, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Total Water:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(183, 67);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(60, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Total Watt:";
            // 
            // ConsoleList
            // 
            this.ConsoleList.FormattingEnabled = true;
            this.ConsoleList.Location = new System.Drawing.Point(6, 19);
            this.ConsoleList.Name = "ConsoleList";
            this.ConsoleList.ScrollAlwaysVisible = true;
            this.ConsoleList.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.ConsoleList.Size = new System.Drawing.Size(334, 290);
            this.ConsoleList.TabIndex = 9;
            // 
            // TotalWaterLb
            // 
            this.TotalWaterLb.AutoSize = true;
            this.TotalWaterLb.Location = new System.Drawing.Point(130, 67);
            this.TotalWaterLb.Name = "TotalWaterLb";
            this.TotalWaterLb.Size = new System.Drawing.Size(17, 13);
            this.TotalWaterLb.TabIndex = 10;
            this.TotalWaterLb.Text = "xx";
            // 
            // SendCmdBtn
            // 
            this.SendCmdBtn.Location = new System.Drawing.Point(274, 313);
            this.SendCmdBtn.Name = "SendCmdBtn";
            this.SendCmdBtn.Size = new System.Drawing.Size(66, 20);
            this.SendCmdBtn.TabIndex = 11;
            this.SendCmdBtn.Text = "Send";
            this.SendCmdBtn.UseVisualStyleBackColor = true;
            this.SendCmdBtn.Click += new System.EventHandler(this.SendCmdBtn_Click);
            // 
            // ConsoleInputTb
            // 
            this.ConsoleInputTb.Location = new System.Drawing.Point(6, 313);
            this.ConsoleInputTb.Name = "ConsoleInputTb";
            this.ConsoleInputTb.Size = new System.Drawing.Size(262, 20);
            this.ConsoleInputTb.TabIndex = 12;
            // 
            // TotalWattLb
            // 
            this.TotalWattLb.AutoSize = true;
            this.TotalWattLb.Location = new System.Drawing.Point(252, 67);
            this.TotalWattLb.Name = "TotalWattLb";
            this.TotalWattLb.Size = new System.Drawing.Size(17, 13);
            this.TotalWattLb.TabIndex = 13;
            this.TotalWattLb.Text = "xx";
            // 
            // ElecUsageLb
            // 
            this.ElecUsageLb.AutoSize = true;
            this.ElecUsageLb.Location = new System.Drawing.Point(141, 49);
            this.ElecUsageLb.Name = "ElecUsageLb";
            this.ElecUsageLb.Size = new System.Drawing.Size(17, 13);
            this.ElecUsageLb.TabIndex = 14;
            this.ElecUsageLb.Text = "xx";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(45, 105);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(86, 13);
            this.label7.TabIndex = 15;
            this.label7.Text = "Current Program:";
            // 
            // WaterUsageLb
            // 
            this.WaterUsageLb.AutoSize = true;
            this.WaterUsageLb.Location = new System.Drawing.Point(141, 78);
            this.WaterUsageLb.Name = "WaterUsageLb";
            this.WaterUsageLb.Size = new System.Drawing.Size(17, 13);
            this.WaterUsageLb.TabIndex = 16;
            this.WaterUsageLb.Text = "xx";
            // 
            // CurrentProgramLb
            // 
            this.CurrentProgramLb.AutoSize = true;
            this.CurrentProgramLb.Location = new System.Drawing.Point(141, 105);
            this.CurrentProgramLb.Name = "CurrentProgramLb";
            this.CurrentProgramLb.Size = new System.Drawing.Size(17, 13);
            this.CurrentProgramLb.TabIndex = 17;
            this.CurrentProgramLb.Text = "xx";
            // 
            // ClientGroupbox
            // 
            this.ClientGroupbox.Controls.Add(this.DataGroupbox);
            this.ClientGroupbox.Controls.Add(this.ClientList);
            this.ClientGroupbox.Location = new System.Drawing.Point(21, 120);
            this.ClientGroupbox.Name = "ClientGroupbox";
            this.ClientGroupbox.Size = new System.Drawing.Size(566, 402);
            this.ClientGroupbox.TabIndex = 18;
            this.ClientGroupbox.TabStop = false;
            this.ClientGroupbox.Text = "Clients";
            // 
            // ToggleEnabledBtn
            // 
            this.ToggleEnabledBtn.Location = new System.Drawing.Point(67, 164);
            this.ToggleEnabledBtn.Name = "ToggleEnabledBtn";
            this.ToggleEnabledBtn.Size = new System.Drawing.Size(75, 23);
            this.ToggleEnabledBtn.TabIndex = 20;
            this.ToggleEnabledBtn.Text = "xxx";
            this.ToggleEnabledBtn.UseVisualStyleBackColor = true;
            this.ToggleEnabledBtn.Click += new System.EventHandler(this.ToggleEnabledBtn_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(45, 134);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(49, 13);
            this.label6.TabIndex = 20;
            this.label6.Text = "Enabled:";
            // 
            // EnabledLb
            // 
            this.EnabledLb.AutoSize = true;
            this.EnabledLb.Location = new System.Drawing.Point(141, 134);
            this.EnabledLb.Name = "EnabledLb";
            this.EnabledLb.Size = new System.Drawing.Size(17, 13);
            this.EnabledLb.TabIndex = 19;
            this.EnabledLb.Text = "xx";
            // 
            // CurrentClientLb
            // 
            this.CurrentClientLb.AutoSize = true;
            this.CurrentClientLb.Location = new System.Drawing.Point(141, 26);
            this.CurrentClientLb.Name = "CurrentClientLb";
            this.CurrentClientLb.Size = new System.Drawing.Size(17, 13);
            this.CurrentClientLb.TabIndex = 18;
            this.CurrentClientLb.Text = "xx";
            // 
            // ConsoleGroupbox
            // 
            this.ConsoleGroupbox.Controls.Add(this.ConsoleList);
            this.ConsoleGroupbox.Controls.Add(this.ConsoleInputTb);
            this.ConsoleGroupbox.Controls.Add(this.SendCmdBtn);
            this.ConsoleGroupbox.Location = new System.Drawing.Point(593, 120);
            this.ConsoleGroupbox.Name = "ConsoleGroupbox";
            this.ConsoleGroupbox.Size = new System.Drawing.Size(348, 339);
            this.ConsoleGroupbox.TabIndex = 19;
            this.ConsoleGroupbox.TabStop = false;
            this.ConsoleGroupbox.Text = "Console";
            // 
            // DataGroupbox
            // 
            this.DataGroupbox.Controls.Add(this.label1);
            this.DataGroupbox.Controls.Add(this.ToggleEnabledBtn);
            this.DataGroupbox.Controls.Add(this.ElecUsageLb);
            this.DataGroupbox.Controls.Add(this.label6);
            this.DataGroupbox.Controls.Add(this.label7);
            this.DataGroupbox.Controls.Add(this.EnabledLb);
            this.DataGroupbox.Controls.Add(this.label3);
            this.DataGroupbox.Controls.Add(this.CurrentClientLb);
            this.DataGroupbox.Controls.Add(this.WaterUsageLb);
            this.DataGroupbox.Controls.Add(this.label2);
            this.DataGroupbox.Controls.Add(this.CurrentProgramLb);
            this.DataGroupbox.Location = new System.Drawing.Point(348, 42);
            this.DataGroupbox.Name = "DataGroupbox";
            this.DataGroupbox.Size = new System.Drawing.Size(200, 216);
            this.DataGroupbox.TabIndex = 21;
            this.DataGroupbox.TabStop = false;
            this.DataGroupbox.Text = "Data";
            // 
            // DisconnectBtn
            // 
            this.DisconnectBtn.Location = new System.Drawing.Point(409, 62);
            this.DisconnectBtn.Name = "DisconnectBtn";
            this.DisconnectBtn.Size = new System.Drawing.Size(75, 23);
            this.DisconnectBtn.TabIndex = 20;
            this.DisconnectBtn.Text = "Disconnect";
            this.DisconnectBtn.UseVisualStyleBackColor = true;
            this.DisconnectBtn.Click += new System.EventHandler(this.Disconnect_btn_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(966, 702);
            this.Controls.Add(this.DisconnectBtn);
            this.Controls.Add(this.ConsoleGroupbox);
            this.Controls.Add(this.ClientGroupbox);
            this.Controls.Add(this.TotalWattLb);
            this.Controls.Add(this.TotalWaterLb);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.RefreshBtn);
            this.Name = "MainForm";
            this.Text = "ControlPanel";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ClientGroupbox.ResumeLayout(false);
            this.ConsoleGroupbox.ResumeLayout(false);
            this.ConsoleGroupbox.PerformLayout();
            this.DataGroupbox.ResumeLayout(false);
            this.DataGroupbox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ListBox ClientList;
        private System.Windows.Forms.Button RefreshBtn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ListBox ConsoleList;
        private System.Windows.Forms.Label TotalWaterLb;
        private System.Windows.Forms.Button SendCmdBtn;
        private System.Windows.Forms.TextBox ConsoleInputTb;
        private System.Windows.Forms.Label TotalWattLb;
        private System.Windows.Forms.Label ElecUsageLb;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label WaterUsageLb;
        private System.Windows.Forms.Label CurrentProgramLb;
        private System.Windows.Forms.GroupBox ClientGroupbox;
        private System.Windows.Forms.Label CurrentClientLb;
        private System.Windows.Forms.GroupBox ConsoleGroupbox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label EnabledLb;
        private System.Windows.Forms.Button ToggleEnabledBtn;
        private System.Windows.Forms.GroupBox DataGroupbox;
        private System.Windows.Forms.Button DisconnectBtn;
    }
}

