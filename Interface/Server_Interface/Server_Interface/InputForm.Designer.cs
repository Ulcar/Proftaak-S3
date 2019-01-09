namespace Server_Interface
{
    partial class InputForm
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
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.Connect_btn = new System.Windows.Forms.Button();
            this.ipTbx = new System.Windows.Forms.TextBox();
            this.potrTbx = new System.Windows.Forms.TextBox();
            this.Cancel_btn = new System.Windows.Forms.Button();
            this.Errorlabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(37, 59);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(26, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Port";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(37, 33);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "IP address";
            // 
            // Connect_btn
            // 
            this.Connect_btn.Location = new System.Drawing.Point(65, 165);
            this.Connect_btn.Name = "Connect_btn";
            this.Connect_btn.Size = new System.Drawing.Size(75, 23);
            this.Connect_btn.TabIndex = 2;
            this.Connect_btn.Text = "Connect";
            this.Connect_btn.UseVisualStyleBackColor = true;
            this.Connect_btn.Click += new System.EventHandler(this.Connect_btn_Click);
            // 
            // ipTbx
            // 
            this.ipTbx.Location = new System.Drawing.Point(100, 30);
            this.ipTbx.Name = "ipTbx";
            this.ipTbx.Size = new System.Drawing.Size(141, 20);
            this.ipTbx.TabIndex = 0;
            this.ipTbx.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Tbx_KeyDown);
            // 
            // potrTbx
            // 
            this.potrTbx.Location = new System.Drawing.Point(100, 56);
            this.potrTbx.Name = "potrTbx";
            this.potrTbx.Size = new System.Drawing.Size(141, 20);
            this.potrTbx.TabIndex = 1;
            this.potrTbx.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Tbx_KeyDown);
            // 
            // Cancel_btn
            // 
            this.Cancel_btn.Location = new System.Drawing.Point(166, 165);
            this.Cancel_btn.Name = "Cancel_btn";
            this.Cancel_btn.Size = new System.Drawing.Size(75, 23);
            this.Cancel_btn.TabIndex = 5;
            this.Cancel_btn.Text = "Cancel";
            this.Cancel_btn.UseVisualStyleBackColor = true;
            this.Cancel_btn.Click += new System.EventHandler(this.Cancel_btn_Click);
            // 
            // Errorlabel
            // 
            this.Errorlabel.AutoSize = true;
            this.Errorlabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Errorlabel.ForeColor = System.Drawing.Color.Red;
            this.Errorlabel.Location = new System.Drawing.Point(78, 115);
            this.Errorlabel.Name = "Errorlabel";
            this.Errorlabel.Size = new System.Drawing.Size(0, 18);
            this.Errorlabel.TabIndex = 6;
            // 
            // InputForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(295, 224);
            this.Controls.Add(this.Errorlabel);
            this.Controls.Add(this.Cancel_btn);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.potrTbx);
            this.Controls.Add(this.Connect_btn);
            this.Controls.Add(this.ipTbx);
            this.Name = "InputForm";
            this.Text = "InputForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button Connect_btn;
        private System.Windows.Forms.TextBox ipTbx;
        private System.Windows.Forms.TextBox potrTbx;
        private System.Windows.Forms.Button Cancel_btn;
        private System.Windows.Forms.Label Errorlabel;
    }
}