﻿namespace TAModLauncher
{
    partial class SettingsForm
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
            this.label1 = new System.Windows.Forms.Label();
            this.selectUpdateChannel = new System.Windows.Forms.ComboBox();
            this.btnOK = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.fileSelectLauncherDirectory = new TAModLauncher.FormFileSelector();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 26);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(84, 13);
            this.label1.TabIndex = 10;
            this.label1.Text = "Update Channel";
            // 
            // selectUpdateChannel
            // 
            this.selectUpdateChannel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.selectUpdateChannel.FormattingEnabled = true;
            this.selectUpdateChannel.Location = new System.Drawing.Point(100, 23);
            this.selectUpdateChannel.Name = "selectUpdateChannel";
            this.selectUpdateChannel.Size = new System.Drawing.Size(153, 21);
            this.selectUpdateChannel.TabIndex = 9;
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(12, 226);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 11;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(109, 13);
            this.label2.TabIndex = 13;
            this.label2.Text = "Tribes Launcher Path";
            // 
            // fileSelectLauncherDirectory
            // 
            this.fileSelectLauncherDirectory.FilePath = "";
            this.fileSelectLauncherDirectory.Location = new System.Drawing.Point(12, 65);
            this.fileSelectLauncherDirectory.MaximumSize = new System.Drawing.Size(0, 20);
            this.fileSelectLauncherDirectory.MinimumSize = new System.Drawing.Size(420, 20);
            this.fileSelectLauncherDirectory.Name = "fileSelectLauncherDirectory";
            this.fileSelectLauncherDirectory.Size = new System.Drawing.Size(420, 20);
            this.fileSelectLauncherDirectory.TabIndex = 12;
            // 
            // SettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(444, 261);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.fileSelectLauncherDirectory);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.selectUpdateChannel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "SettingsForm";
            this.Text = "SettingsForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.SettingsForm_FormClosing);
            this.Load += new System.EventHandler(this.SettingsForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        public System.Windows.Forms.ComboBox selectUpdateChannel;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Label label2;
        private FormFileSelector fileSelectLauncherDirectory;
    }
}