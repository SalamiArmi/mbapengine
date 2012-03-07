namespace Argon
{
    partial class ArgonRenderSystems
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
            this.m_RenderSystemsList = new System.Windows.Forms.ComboBox();
            this.m_RenderSystemsLabel = new System.Windows.Forms.Label();
            this.m_VideoModes = new System.Windows.Forms.ComboBox();
            this.m_CreateDevice = new System.Windows.Forms.Button();
            this.m_Cancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // m_RenderSystemsList
            // 
            this.m_RenderSystemsList.FormattingEnabled = true;
            this.m_RenderSystemsList.Location = new System.Drawing.Point(12, 32);
            this.m_RenderSystemsList.Name = "m_RenderSystemsList";
            this.m_RenderSystemsList.Size = new System.Drawing.Size(332, 21);
            this.m_RenderSystemsList.TabIndex = 0;
            this.m_RenderSystemsList.SelectedIndexChanged += new System.EventHandler(this.m_RenderSystemsList_SelectedIndexChanged);
            // 
            // m_RenderSystemsLabel
            // 
            this.m_RenderSystemsLabel.AutoSize = true;
            this.m_RenderSystemsLabel.Location = new System.Drawing.Point(12, 9);
            this.m_RenderSystemsLabel.Name = "m_RenderSystemsLabel";
            this.m_RenderSystemsLabel.Size = new System.Drawing.Size(81, 13);
            this.m_RenderSystemsLabel.TabIndex = 1;
            this.m_RenderSystemsLabel.Text = "RenderSystems";
            // 
            // m_VideoModes
            // 
            this.m_VideoModes.FormattingEnabled = true;
            this.m_VideoModes.Location = new System.Drawing.Point(12, 59);
            this.m_VideoModes.Name = "m_VideoModes";
            this.m_VideoModes.Size = new System.Drawing.Size(332, 21);
            this.m_VideoModes.TabIndex = 2;
            // 
            // m_CreateDevice
            // 
            this.m_CreateDevice.Location = new System.Drawing.Point(259, 145);
            this.m_CreateDevice.Name = "m_CreateDevice";
            this.m_CreateDevice.Size = new System.Drawing.Size(85, 23);
            this.m_CreateDevice.TabIndex = 3;
            this.m_CreateDevice.Text = "Create Device";
            this.m_CreateDevice.UseVisualStyleBackColor = true;
            this.m_CreateDevice.Click += new System.EventHandler(this.m_CreateDevice_Click);
            // 
            // m_Cancel
            // 
            this.m_Cancel.Location = new System.Drawing.Point(15, 145);
            this.m_Cancel.Name = "m_Cancel";
            this.m_Cancel.Size = new System.Drawing.Size(85, 23);
            this.m_Cancel.TabIndex = 3;
            this.m_Cancel.Text = "Cancel";
            this.m_Cancel.UseVisualStyleBackColor = true;
            // 
            // ArgonRenderSystems
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(356, 180);
            this.Controls.Add(this.m_Cancel);
            this.Controls.Add(this.m_CreateDevice);
            this.Controls.Add(this.m_VideoModes);
            this.Controls.Add(this.m_RenderSystemsLabel);
            this.Controls.Add(this.m_RenderSystemsList);
            this.Name = "ArgonRenderSystems";
            this.Text = "ArgonRenderSystems";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox m_RenderSystemsList;
        private System.Windows.Forms.Label m_RenderSystemsLabel;
        private System.Windows.Forms.ComboBox m_VideoModes;
        private System.Windows.Forms.Button m_CreateDevice;
        private System.Windows.Forms.Button m_Cancel;
    }
}