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
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.ErrorList = new System.Windows.Forms.ListBox();
            this.TotalWaterLb = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.ConsoleInputTb = new System.Windows.Forms.TextBox();
            this.TotalWattLb = new System.Windows.Forms.Label();
            this.ElecUsageLb = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.WaterUsageLb = new System.Windows.Forms.Label();
            this.CurrentProgramLb = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // ClientList
            // 
            this.ClientList.FormattingEnabled = true;
            this.ClientList.Location = new System.Drawing.Point(12, 119);
            this.ClientList.Name = "ClientList";
            this.ClientList.Size = new System.Drawing.Size(109, 329);
            this.ClientList.TabIndex = 0;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(353, 32);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Refresh";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(174, 119);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Client:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(140, 191);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(70, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Water Usage";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(150, 155);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(60, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Elec usage";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 19);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(66, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Total Water:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(177, 19);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(60, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Total Watt:";
            // 
            // ErrorList
            // 
            this.ErrorList.FormattingEnabled = true;
            this.ErrorList.Location = new System.Drawing.Point(308, 171);
            this.ErrorList.Name = "ErrorList";
            this.ErrorList.Size = new System.Drawing.Size(120, 251);
            this.ErrorList.TabIndex = 9;
            // 
            // TotalWaterLb
            // 
            this.TotalWaterLb.AutoSize = true;
            this.TotalWaterLb.Location = new System.Drawing.Point(84, 19);
            this.TotalWaterLb.Name = "TotalWaterLb";
            this.TotalWaterLb.Size = new System.Drawing.Size(17, 13);
            this.TotalWaterLb.TabIndex = 10;
            this.TotalWaterLb.Text = "xx";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(287, 455);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(141, 23);
            this.button2.TabIndex = 11;
            this.button2.Text = "Send Console Command";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // ConsoleInputTb
            // 
            this.ConsoleInputTb.Location = new System.Drawing.Point(158, 458);
            this.ConsoleInputTb.Name = "ConsoleInputTb";
            this.ConsoleInputTb.Size = new System.Drawing.Size(100, 20);
            this.ConsoleInputTb.TabIndex = 12;
            // 
            // TotalWattLb
            // 
            this.TotalWattLb.AutoSize = true;
            this.TotalWattLb.Location = new System.Drawing.Point(246, 19);
            this.TotalWattLb.Name = "TotalWattLb";
            this.TotalWattLb.Size = new System.Drawing.Size(17, 13);
            this.TotalWattLb.TabIndex = 13;
            this.TotalWattLb.Text = "xx";
            // 
            // ElecUsageLb
            // 
            this.ElecUsageLb.AutoSize = true;
            this.ElecUsageLb.Location = new System.Drawing.Point(220, 155);
            this.ElecUsageLb.Name = "ElecUsageLb";
            this.ElecUsageLb.Size = new System.Drawing.Size(17, 13);
            this.ElecUsageLb.TabIndex = 14;
            this.ElecUsageLb.Text = "xx";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(124, 231);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(86, 13);
            this.label7.TabIndex = 15;
            this.label7.Text = "Current Program:";
            // 
            // WaterUsageLb
            // 
            this.WaterUsageLb.AutoSize = true;
            this.WaterUsageLb.Location = new System.Drawing.Point(220, 191);
            this.WaterUsageLb.Name = "WaterUsageLb";
            this.WaterUsageLb.Size = new System.Drawing.Size(17, 13);
            this.WaterUsageLb.TabIndex = 16;
            this.WaterUsageLb.Text = "xx";
            // 
            // CurrentProgramLb
            // 
            this.CurrentProgramLb.AutoSize = true;
            this.CurrentProgramLb.Location = new System.Drawing.Point(220, 231);
            this.CurrentProgramLb.Name = "CurrentProgramLb";
            this.CurrentProgramLb.Size = new System.Drawing.Size(17, 13);
            this.CurrentProgramLb.TabIndex = 17;
            this.CurrentProgramLb.Text = "xx";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(450, 487);
            this.Controls.Add(this.CurrentProgramLb);
            this.Controls.Add(this.WaterUsageLb);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.ElecUsageLb);
            this.Controls.Add(this.TotalWattLb);
            this.Controls.Add(this.ConsoleInputTb);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.TotalWaterLb);
            this.Controls.Add(this.ErrorList);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.ClientList);
            this.Name = "MainForm";
            this.Text = "ControlPanel";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ListBox ClientList;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ListBox ErrorList;
        private System.Windows.Forms.Label TotalWaterLb;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox ConsoleInputTb;
        private System.Windows.Forms.Label TotalWattLb;
        private System.Windows.Forms.Label ElecUsageLb;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label WaterUsageLb;
        private System.Windows.Forms.Label CurrentProgramLb;

    }
}

