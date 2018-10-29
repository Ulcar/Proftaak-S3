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
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.SendData_btn = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.RecievedData_listBox = new System.Windows.Forms.ListBox();
            this.GetData_btn = new System.Windows.Forms.Button();
            this.Disconnect_btn = new System.Windows.Forms.Button();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.textBox3);
            this.groupBox2.Controls.Add(this.SendData_btn);
            this.groupBox2.Location = new System.Drawing.Point(12, 13);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(279, 425);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "groupBox2";
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(6, 21);
            this.textBox3.Multiline = true;
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(267, 48);
            this.textBox3.TabIndex = 1;
            // 
            // SendData_btn
            // 
            this.SendData_btn.Location = new System.Drawing.Point(92, 75);
            this.SendData_btn.Name = "SendData_btn";
            this.SendData_btn.Size = new System.Drawing.Size(75, 23);
            this.SendData_btn.TabIndex = 0;
            this.SendData_btn.Text = "send data";
            this.SendData_btn.UseVisualStyleBackColor = true;
            this.SendData_btn.Click += new System.EventHandler(this.SendData_btn_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.RecievedData_listBox);
            this.groupBox3.Controls.Add(this.GetData_btn);
            this.groupBox3.Location = new System.Drawing.Point(308, 5);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(293, 425);
            this.groupBox3.TabIndex = 4;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "groupBox3";
            // 
            // RecievedData_listBox
            // 
            this.RecievedData_listBox.FormattingEnabled = true;
            this.RecievedData_listBox.Location = new System.Drawing.Point(7, 20);
            this.RecievedData_listBox.Name = "RecievedData_listBox";
            this.RecievedData_listBox.Size = new System.Drawing.Size(280, 355);
            this.RecievedData_listBox.TabIndex = 1;
            // 
            // GetData_btn
            // 
            this.GetData_btn.Location = new System.Drawing.Point(113, 379);
            this.GetData_btn.Name = "GetData_btn";
            this.GetData_btn.Size = new System.Drawing.Size(75, 23);
            this.GetData_btn.TabIndex = 0;
            this.GetData_btn.Text = "Get Data";
            this.GetData_btn.UseVisualStyleBackColor = true;
            this.GetData_btn.Click += new System.EventHandler(this.GetData_btn_Click);
            // 
            // Disconnect_btn
            // 
            this.Disconnect_btn.Location = new System.Drawing.Point(713, 5);
            this.Disconnect_btn.Name = "Disconnect_btn";
            this.Disconnect_btn.Size = new System.Drawing.Size(75, 23);
            this.Disconnect_btn.TabIndex = 5;
            this.Disconnect_btn.Text = "Disconnect";
            this.Disconnect_btn.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.Disconnect_btn);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Name = "MainForm";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Button SendData_btn;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button GetData_btn;
        private System.Windows.Forms.Button Disconnect_btn;
        private System.Windows.Forms.ListBox RecievedData_listBox;
    }
}

