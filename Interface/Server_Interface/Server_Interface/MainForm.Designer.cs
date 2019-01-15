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
            this.DataGroupbox = new System.Windows.Forms.GroupBox();
            this.ToggleEnabledBtn = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.EnabledLb = new System.Windows.Forms.Label();
            this.CurrentClientLb = new System.Windows.Forms.Label();
            this.ConsoleGroupbox = new System.Windows.Forms.GroupBox();
            this.DisconnectBtn = new System.Windows.Forms.Button();
            this.ToolbarGroupbox = new System.Windows.Forms.GroupBox();
            this.ReloadBtn = new System.Windows.Forms.Button();
            this.DisableClientsBtn = new System.Windows.Forms.Button();
            this.LaundryGroupBox = new System.Windows.Forms.GroupBox();
            this.PoundsNummericUpDown = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.ColorGroupBox = new System.Windows.Forms.GroupBox();
            this.TemperatureGroupBox = new System.Windows.Forms.GroupBox();
            this.ColorLightRadioButton = new System.Windows.Forms.RadioButton();
            this.ColorDarkRadioButton = new System.Windows.Forms.RadioButton();
            this.ColorColorRadioButton = new System.Windows.Forms.RadioButton();
            this.TempHotRadioButton = new System.Windows.Forms.RadioButton();
            this.TempWarmRadioButton = new System.Windows.Forms.RadioButton();
            this.TempColdRadioButton = new System.Windows.Forms.RadioButton();
            this.LaundryBtn = new System.Windows.Forms.Button();
            this.MachinesGroupBox = new System.Windows.Forms.GroupBox();
            this.WashingMachineCheckBox = new System.Windows.Forms.CheckBox();
            this.DryerCheckBox = new System.Windows.Forms.CheckBox();
            this.CentrifugeCheckBox = new System.Windows.Forms.CheckBox();
            this.SteamerCheckBox = new System.Windows.Forms.CheckBox();
            this.ClientGroupbox.SuspendLayout();
            this.DataGroupbox.SuspendLayout();
            this.ConsoleGroupbox.SuspendLayout();
            this.ToolbarGroupbox.SuspendLayout();
            this.LaundryGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PoundsNummericUpDown)).BeginInit();
            this.ColorGroupBox.SuspendLayout();
            this.TemperatureGroupBox.SuspendLayout();
            this.MachinesGroupBox.SuspendLayout();
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
            this.label4.Location = new System.Drawing.Point(6, 16);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(66, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Total Water:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(162, 16);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(60, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Total Watt:";
            // 
            // ConsoleList
            // 
            this.ConsoleList.FormattingEnabled = true;
            this.ConsoleList.HorizontalScrollbar = true;
            this.ConsoleList.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.ConsoleList.Location = new System.Drawing.Point(6, 19);
            this.ConsoleList.Name = "ConsoleList";
            this.ConsoleList.ScrollAlwaysVisible = true;
            this.ConsoleList.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.ConsoleList.Size = new System.Drawing.Size(532, 537);
            this.ConsoleList.TabIndex = 9;
            // 
            // TotalWaterLb
            // 
            this.TotalWaterLb.AutoSize = true;
            this.TotalWaterLb.Location = new System.Drawing.Point(78, 16);
            this.TotalWaterLb.Name = "TotalWaterLb";
            this.TotalWaterLb.Size = new System.Drawing.Size(22, 13);
            this.TotalWaterLb.TabIndex = 10;
            this.TotalWaterLb.Text = "0 L";
            // 
            // SendCmdBtn
            // 
            this.SendCmdBtn.Location = new System.Drawing.Point(413, 562);
            this.SendCmdBtn.Name = "SendCmdBtn";
            this.SendCmdBtn.Size = new System.Drawing.Size(125, 20);
            this.SendCmdBtn.TabIndex = 11;
            this.SendCmdBtn.Text = "Send";
            this.SendCmdBtn.UseVisualStyleBackColor = true;
            this.SendCmdBtn.Click += new System.EventHandler(this.SendCmdBtn_Click);
            this.SendCmdBtn.KeyDown += new System.Windows.Forms.KeyEventHandler(this.SendCmdBtn_KeyDown);
            // 
            // ConsoleInputTb
            // 
            this.ConsoleInputTb.Location = new System.Drawing.Point(6, 563);
            this.ConsoleInputTb.Name = "ConsoleInputTb";
            this.ConsoleInputTb.Size = new System.Drawing.Size(401, 20);
            this.ConsoleInputTb.TabIndex = 12;
            this.ConsoleInputTb.KeyDown += new System.Windows.Forms.KeyEventHandler(this.SendCmdBtn_KeyDown);
            // 
            // TotalWattLb
            // 
            this.TotalWattLb.AutoSize = true;
            this.TotalWattLb.Location = new System.Drawing.Point(234, 16);
            this.TotalWattLb.Name = "TotalWattLb";
            this.TotalWattLb.Size = new System.Drawing.Size(27, 13);
            this.TotalWattLb.TabIndex = 13;
            this.TotalWattLb.Text = "0 W";
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
            this.ClientGroupbox.Location = new System.Drawing.Point(12, 59);
            this.ClientGroupbox.Name = "ClientGroupbox";
            this.ClientGroupbox.Size = new System.Drawing.Size(566, 291);
            this.ClientGroupbox.TabIndex = 18;
            this.ClientGroupbox.TabStop = false;
            this.ClientGroupbox.Text = "Clients";
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
            this.ConsoleGroupbox.Location = new System.Drawing.Point(584, 59);
            this.ConsoleGroupbox.Name = "ConsoleGroupbox";
            this.ConsoleGroupbox.Size = new System.Drawing.Size(544, 589);
            this.ConsoleGroupbox.TabIndex = 19;
            this.ConsoleGroupbox.TabStop = false;
            this.ConsoleGroupbox.Text = "Console";
            // 
            // DisconnectBtn
            // 
            this.DisconnectBtn.Location = new System.Drawing.Point(837, 11);
            this.DisconnectBtn.Name = "DisconnectBtn";
            this.DisconnectBtn.Size = new System.Drawing.Size(75, 23);
            this.DisconnectBtn.TabIndex = 20;
            this.DisconnectBtn.Text = "Disconnect";
            this.DisconnectBtn.UseVisualStyleBackColor = true;
            this.DisconnectBtn.Click += new System.EventHandler(this.Disconnect_btn_Click);
            // 
            // ToolbarGroupbox
            // 
            this.ToolbarGroupbox.Controls.Add(this.ReloadBtn);
            this.ToolbarGroupbox.Controls.Add(this.DisableClientsBtn);
            this.ToolbarGroupbox.Controls.Add(this.DisconnectBtn);
            this.ToolbarGroupbox.Controls.Add(this.label4);
            this.ToolbarGroupbox.Controls.Add(this.label5);
            this.ToolbarGroupbox.Controls.Add(this.TotalWattLb);
            this.ToolbarGroupbox.Controls.Add(this.TotalWaterLb);
            this.ToolbarGroupbox.Location = new System.Drawing.Point(12, 12);
            this.ToolbarGroupbox.Name = "ToolbarGroupbox";
            this.ToolbarGroupbox.Size = new System.Drawing.Size(920, 41);
            this.ToolbarGroupbox.TabIndex = 21;
            this.ToolbarGroupbox.TabStop = false;
            this.ToolbarGroupbox.Text = "Toolbar";
            // 
            // ReloadBtn
            // 
            this.ReloadBtn.Location = new System.Drawing.Point(751, 12);
            this.ReloadBtn.Name = "ReloadBtn";
            this.ReloadBtn.Size = new System.Drawing.Size(80, 23);
            this.ReloadBtn.TabIndex = 22;
            this.ReloadBtn.Text = "Reload";
            this.ReloadBtn.UseVisualStyleBackColor = true;
            this.ReloadBtn.Click += new System.EventHandler(this.ReloadBtn_Click);
            // 
            // DisableClientsBtn
            // 
            this.DisableClientsBtn.Location = new System.Drawing.Point(640, 11);
            this.DisableClientsBtn.Name = "DisableClientsBtn";
            this.DisableClientsBtn.Size = new System.Drawing.Size(105, 23);
            this.DisableClientsBtn.TabIndex = 21;
            this.DisableClientsBtn.Text = "Disable all Clients";
            this.DisableClientsBtn.UseVisualStyleBackColor = true;
            this.DisableClientsBtn.Click += new System.EventHandler(this.DisableClientsBtn_Click);
            // 
            // LaundryGroupBox
            // 
            this.LaundryGroupBox.Controls.Add(this.MachinesGroupBox);
            this.LaundryGroupBox.Controls.Add(this.LaundryBtn);
            this.LaundryGroupBox.Controls.Add(this.TemperatureGroupBox);
            this.LaundryGroupBox.Controls.Add(this.ColorGroupBox);
            this.LaundryGroupBox.Controls.Add(this.label8);
            this.LaundryGroupBox.Controls.Add(this.PoundsNummericUpDown);
            this.LaundryGroupBox.Location = new System.Drawing.Point(12, 356);
            this.LaundryGroupBox.Name = "LaundryGroupBox";
            this.LaundryGroupBox.Size = new System.Drawing.Size(566, 292);
            this.LaundryGroupBox.TabIndex = 22;
            this.LaundryGroupBox.TabStop = false;
            this.LaundryGroupBox.Text = "Laundry";
            // 
            // PoundsNummericUpDown
            // 
            this.PoundsNummericUpDown.Location = new System.Drawing.Point(261, 19);
            this.PoundsNummericUpDown.Name = "PoundsNummericUpDown";
            this.PoundsNummericUpDown.Size = new System.Drawing.Size(120, 20);
            this.PoundsNummericUpDown.TabIndex = 0;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(152, 21);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(46, 13);
            this.label8.TabIndex = 21;
            this.label8.Text = "Pounds:";
            // 
            // ColorGroupBox
            // 
            this.ColorGroupBox.Controls.Add(this.ColorColorRadioButton);
            this.ColorGroupBox.Controls.Add(this.ColorDarkRadioButton);
            this.ColorGroupBox.Controls.Add(this.ColorLightRadioButton);
            this.ColorGroupBox.Location = new System.Drawing.Point(46, 48);
            this.ColorGroupBox.Name = "ColorGroupBox";
            this.ColorGroupBox.Size = new System.Drawing.Size(202, 95);
            this.ColorGroupBox.TabIndex = 24;
            this.ColorGroupBox.TabStop = false;
            this.ColorGroupBox.Text = "Select Color";
            // 
            // TemperatureGroupBox
            // 
            this.TemperatureGroupBox.Controls.Add(this.TempHotRadioButton);
            this.TemperatureGroupBox.Controls.Add(this.TempColdRadioButton);
            this.TemperatureGroupBox.Controls.Add(this.TempWarmRadioButton);
            this.TemperatureGroupBox.Location = new System.Drawing.Point(276, 48);
            this.TemperatureGroupBox.Name = "TemperatureGroupBox";
            this.TemperatureGroupBox.Size = new System.Drawing.Size(202, 95);
            this.TemperatureGroupBox.TabIndex = 25;
            this.TemperatureGroupBox.TabStop = false;
            this.TemperatureGroupBox.Text = "Select Temperature";
            // 
            // ColorLightRadioButton
            // 
            this.ColorLightRadioButton.AutoSize = true;
            this.ColorLightRadioButton.Checked = true;
            this.ColorLightRadioButton.Location = new System.Drawing.Point(72, 19);
            this.ColorLightRadioButton.Name = "ColorLightRadioButton";
            this.ColorLightRadioButton.Size = new System.Drawing.Size(48, 17);
            this.ColorLightRadioButton.TabIndex = 0;
            this.ColorLightRadioButton.TabStop = true;
            this.ColorLightRadioButton.Text = "Light";
            this.ColorLightRadioButton.UseVisualStyleBackColor = true;
            // 
            // ColorDarkRadioButton
            // 
            this.ColorDarkRadioButton.AutoSize = true;
            this.ColorDarkRadioButton.Location = new System.Drawing.Point(72, 42);
            this.ColorDarkRadioButton.Name = "ColorDarkRadioButton";
            this.ColorDarkRadioButton.Size = new System.Drawing.Size(48, 17);
            this.ColorDarkRadioButton.TabIndex = 1;
            this.ColorDarkRadioButton.Text = "Dark";
            this.ColorDarkRadioButton.UseVisualStyleBackColor = true;
            // 
            // ColorColorRadioButton
            // 
            this.ColorColorRadioButton.AutoSize = true;
            this.ColorColorRadioButton.Location = new System.Drawing.Point(72, 65);
            this.ColorColorRadioButton.Name = "ColorColorRadioButton";
            this.ColorColorRadioButton.Size = new System.Drawing.Size(49, 17);
            this.ColorColorRadioButton.TabIndex = 2;
            this.ColorColorRadioButton.Text = "Color";
            this.ColorColorRadioButton.UseVisualStyleBackColor = true;
            // 
            // TempHotRadioButton
            // 
            this.TempHotRadioButton.AutoSize = true;
            this.TempHotRadioButton.Location = new System.Drawing.Point(72, 65);
            this.TempHotRadioButton.Name = "TempHotRadioButton";
            this.TempHotRadioButton.Size = new System.Drawing.Size(48, 17);
            this.TempHotRadioButton.TabIndex = 5;
            this.TempHotRadioButton.Text = "60*C";
            this.TempHotRadioButton.UseVisualStyleBackColor = true;
            // 
            // TempWarmRadioButton
            // 
            this.TempWarmRadioButton.AutoSize = true;
            this.TempWarmRadioButton.Location = new System.Drawing.Point(72, 42);
            this.TempWarmRadioButton.Name = "TempWarmRadioButton";
            this.TempWarmRadioButton.Size = new System.Drawing.Size(51, 17);
            this.TempWarmRadioButton.TabIndex = 4;
            this.TempWarmRadioButton.Text = "40 *C";
            this.TempWarmRadioButton.UseVisualStyleBackColor = true;
            // 
            // TempColdRadioButton
            // 
            this.TempColdRadioButton.AutoSize = true;
            this.TempColdRadioButton.Checked = true;
            this.TempColdRadioButton.Location = new System.Drawing.Point(72, 19);
            this.TempColdRadioButton.Name = "TempColdRadioButton";
            this.TempColdRadioButton.Size = new System.Drawing.Size(51, 17);
            this.TempColdRadioButton.TabIndex = 3;
            this.TempColdRadioButton.TabStop = true;
            this.TempColdRadioButton.Text = "30 *C";
            this.TempColdRadioButton.UseVisualStyleBackColor = true;
            // 
            // LaundryBtn
            // 
            this.LaundryBtn.Location = new System.Drawing.Point(276, 171);
            this.LaundryBtn.Name = "LaundryBtn";
            this.LaundryBtn.Size = new System.Drawing.Size(202, 97);
            this.LaundryBtn.TabIndex = 21;
            this.LaundryBtn.Text = "Send Laundry";
            this.LaundryBtn.UseVisualStyleBackColor = true;
            this.LaundryBtn.Click += new System.EventHandler(this.LaundryBtn_Click);
            // 
            // MachinesGroupBox
            // 
            this.MachinesGroupBox.Controls.Add(this.SteamerCheckBox);
            this.MachinesGroupBox.Controls.Add(this.CentrifugeCheckBox);
            this.MachinesGroupBox.Controls.Add(this.DryerCheckBox);
            this.MachinesGroupBox.Controls.Add(this.WashingMachineCheckBox);
            this.MachinesGroupBox.Location = new System.Drawing.Point(46, 164);
            this.MachinesGroupBox.Name = "MachinesGroupBox";
            this.MachinesGroupBox.Size = new System.Drawing.Size(202, 108);
            this.MachinesGroupBox.TabIndex = 26;
            this.MachinesGroupBox.TabStop = false;
            this.MachinesGroupBox.Text = "Select Machines";
            // 
            // WashingMachineCheckBox
            // 
            this.WashingMachineCheckBox.AutoSize = true;
            this.WashingMachineCheckBox.Location = new System.Drawing.Point(48, 19);
            this.WashingMachineCheckBox.Name = "WashingMachineCheckBox";
            this.WashingMachineCheckBox.Size = new System.Drawing.Size(109, 17);
            this.WashingMachineCheckBox.TabIndex = 0;
            this.WashingMachineCheckBox.Text = "WashingMachine";
            this.WashingMachineCheckBox.UseVisualStyleBackColor = true;
            // 
            // DryerCheckBox
            // 
            this.DryerCheckBox.AutoSize = true;
            this.DryerCheckBox.Location = new System.Drawing.Point(48, 42);
            this.DryerCheckBox.Name = "DryerCheckBox";
            this.DryerCheckBox.Size = new System.Drawing.Size(51, 17);
            this.DryerCheckBox.TabIndex = 1;
            this.DryerCheckBox.Text = "Dryer";
            this.DryerCheckBox.UseVisualStyleBackColor = true;
            // 
            // CentrifugeCheckBox
            // 
            this.CentrifugeCheckBox.AutoSize = true;
            this.CentrifugeCheckBox.Location = new System.Drawing.Point(48, 65);
            this.CentrifugeCheckBox.Name = "CentrifugeCheckBox";
            this.CentrifugeCheckBox.Size = new System.Drawing.Size(74, 17);
            this.CentrifugeCheckBox.TabIndex = 2;
            this.CentrifugeCheckBox.Text = "Centrifuge";
            this.CentrifugeCheckBox.UseVisualStyleBackColor = true;
            // 
            // SteamerCheckBox
            // 
            this.SteamerCheckBox.AutoSize = true;
            this.SteamerCheckBox.Location = new System.Drawing.Point(48, 87);
            this.SteamerCheckBox.Name = "SteamerCheckBox";
            this.SteamerCheckBox.Size = new System.Drawing.Size(65, 17);
            this.SteamerCheckBox.TabIndex = 3;
            this.SteamerCheckBox.Text = "Steamer";
            this.SteamerCheckBox.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1142, 660);
            this.Controls.Add(this.LaundryGroupBox);
            this.Controls.Add(this.ToolbarGroupbox);
            this.Controls.Add(this.ConsoleGroupbox);
            this.Controls.Add(this.ClientGroupbox);
            this.Name = "MainForm";
            this.Text = "ControlPanel";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ClientGroupbox.ResumeLayout(false);
            this.DataGroupbox.ResumeLayout(false);
            this.DataGroupbox.PerformLayout();
            this.ConsoleGroupbox.ResumeLayout(false);
            this.ConsoleGroupbox.PerformLayout();
            this.ToolbarGroupbox.ResumeLayout(false);
            this.ToolbarGroupbox.PerformLayout();
            this.LaundryGroupBox.ResumeLayout(false);
            this.LaundryGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PoundsNummericUpDown)).EndInit();
            this.ColorGroupBox.ResumeLayout(false);
            this.ColorGroupBox.PerformLayout();
            this.TemperatureGroupBox.ResumeLayout(false);
            this.TemperatureGroupBox.PerformLayout();
            this.MachinesGroupBox.ResumeLayout(false);
            this.MachinesGroupBox.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.ListBox ClientList;
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
        private System.Windows.Forms.GroupBox ToolbarGroupbox;
        private System.Windows.Forms.Button DisableClientsBtn;
        private System.Windows.Forms.Button ReloadBtn;
        private System.Windows.Forms.GroupBox LaundryGroupBox;
        private System.Windows.Forms.Button LaundryBtn;
        private System.Windows.Forms.GroupBox TemperatureGroupBox;
        private System.Windows.Forms.RadioButton TempHotRadioButton;
        private System.Windows.Forms.RadioButton TempColdRadioButton;
        private System.Windows.Forms.RadioButton TempWarmRadioButton;
        private System.Windows.Forms.GroupBox ColorGroupBox;
        private System.Windows.Forms.RadioButton ColorColorRadioButton;
        private System.Windows.Forms.RadioButton ColorDarkRadioButton;
        private System.Windows.Forms.RadioButton ColorLightRadioButton;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.NumericUpDown PoundsNummericUpDown;
        private System.Windows.Forms.GroupBox MachinesGroupBox;
        private System.Windows.Forms.CheckBox SteamerCheckBox;
        private System.Windows.Forms.CheckBox CentrifugeCheckBox;
        private System.Windows.Forms.CheckBox DryerCheckBox;
        private System.Windows.Forms.CheckBox WashingMachineCheckBox;
    }
}

