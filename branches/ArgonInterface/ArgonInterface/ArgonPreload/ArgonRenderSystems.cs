using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Argon
{
    public partial class ArgonRenderSystems : Form
    {
        private IntPtr m_Window;
        private System.Collections.Generic.Dictionary<string, System.Collections.Generic.List<string>> m_RenderSystemModes;

        public ArgonRenderSystems(IntPtr Window)
        {
            InitializeComponent();
            m_Window = Window;

            ArgonRenderSystems_Load(null, null);
        }

        private void ArgonRenderSystems_Load(object sender, EventArgs e)
        {
            m_RenderSystemModes = new System.Collections.Generic.Dictionary<string, System.Collections.Generic.List<string>>();

            uint RenderSystemCount = ArgonEngineDll.GetRenderSystemCount();
            if (RenderSystemCount > 0)
            {
                Console.WriteLine("RenderSystems found, " + RenderSystemCount.ToString());

                for (uint Index = 0; Index < RenderSystemCount; ++Index)
                {
                    System.Collections.Generic.List<string> Modes = new System.Collections.Generic.List<string>();
                    string RenderSystemName = ArgonEngineDll.GetRenderSystemName(Index);
                    m_RenderSystemsList.Items.Add(RenderSystemName);
                    uint RenderSystemDriverCount = ArgonEngineDll.GetRenderSystemDriverCount(Index);
                    for (uint DriverIndex = 0; DriverIndex < RenderSystemCount; ++DriverIndex)
                    {
                        uint ModeCount = ArgonEngineDll.GetRenderSystemDriverModesCount(Index, DriverIndex);
                        for (uint ModeIndex = 0; ModeIndex < ModeCount; ++ModeIndex)
                        {
                            string ModeDesc = ArgonEngineDll.GetRenderSystemDriverMode(Index, DriverIndex, ModeIndex);
                            Modes.Add(ModeDesc);
                        }
                    }
                    m_RenderSystemModes.Add(RenderSystemName, Modes);
                }

                m_RenderSystemsList.SelectedIndex = 0; //Set the first item as selected
            }
            else Application.Exit();
        }

        private void m_CreateDevice_Click(object sender, EventArgs e)
        {
            ArgonEngineDll.CreateEngine(m_Window, (uint)m_RenderSystemsList.SelectedIndex, (uint)0, (uint)m_VideoModes.SelectedIndex);
            this.DialogResult = DialogResult.OK;
        }

        private void m_Cancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
        }      
 
        private void m_RenderSystemsList_SelectedIndexChanged(object sender, EventArgs e)
        {
            string SelectedRenderSystemName = (string)m_RenderSystemsList.SelectedItem;

            if(SelectedRenderSystemName != "")
            {
                System.Collections.Generic.List<string> Modes = new System.Collections.Generic.List<string>();
                if(m_RenderSystemModes.TryGetValue(SelectedRenderSystemName, out Modes))
                {
                    //Populate the Mode display box
                    m_VideoModes.Items.Clear();
                    foreach (string Mode in Modes)
                    {
                        m_VideoModes.Items.Add(Mode);
                    }
                    m_VideoModes.SelectedIndex = 0;
                }
            }
        }
    }
}
