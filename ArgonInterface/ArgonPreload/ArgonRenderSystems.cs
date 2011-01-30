using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Argon
{
    public partial class ArgonRenderSystems : Form
    {
        private IntPtr m_Window;

        public ArgonRenderSystems(IntPtr Window)
        {
            InitializeComponent();
            m_Window = Window;
        }

        private void ArgonRenderSystems_Load(object sender, EventArgs e)
        {
            Argon.ArgonEngineDll.PreLoadEngine();

            int RenderSystemCount = ArgonEngineDll.GetRenderSystemCount();
            if (RenderSystemCount > 0)
            {
                Console.WriteLine("RenderSystems found, " + RenderSystemCount.ToString());

                for (int Index = 0; Index < RenderSystemCount; ++Index)
                {
                    string RenderSystemName = ArgonEngineDll.GetRenderSystemName(Index);
                    m_RenderSystemsList.Items.Add(RenderSystemName);
                    int RenderSystemDriverCount = ArgonEngineDll.GetRenderSystemDriversCount(Index);
                    for (int DriverIndex = 0; DriverIndex < RenderSystemCount; ++DriverIndex)
                    {
                        int ModeCount = ArgonEngineDll.GetRenderSystemDriverModesCount(Index, DriverIndex);
                        for (int ModeIndex = 0; ModeIndex < ModeCount; ++ModeIndex)
                        {
                            string ModeDesc = ArgonEngineDll.GetRenderSystemDriverModeDesc(Index, DriverIndex, ModeIndex);
                            m_VideoModes.Items.Add(ModeDesc);
                        }
                    }
                }
            }
            else Application.Exit();
        }

        private void m_CreateDevice_Click(object sender, EventArgs e)
        {
            ArgonEngineDll.CreateEngine(m_RenderSystemsList.SelectedIndex, 0, 0, m_Window);
            this.DialogResult = DialogResult.OK;
        }

        private void m_Cancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
        }       
    }
}
