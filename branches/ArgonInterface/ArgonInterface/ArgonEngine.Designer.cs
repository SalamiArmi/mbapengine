namespace Argon
{
    partial class ArgonEngine
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
            this.m_RenderPanel = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // m_RenderPanel
            // 
            this.m_RenderPanel.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.m_RenderPanel.Location = new System.Drawing.Point(12, 45);
            this.m_RenderPanel.Name = "m_RenderPanel";
            this.m_RenderPanel.Size = new System.Drawing.Size(1521, 739);
            this.m_RenderPanel.TabIndex = 0;
            // 
            // ArgonEngine
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1545, 796);
            this.Controls.Add(this.m_RenderPanel);
            this.Name = "ArgonEngine";
            this.Text = "Argon Editor";
            this.Load += new System.EventHandler(this.ArgonEngine_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel m_RenderPanel;
    }
}

