using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace Argon
{
    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct MessageStruct
    {
        System.IntPtr Wnd;
        Message Message;
        System.IntPtr WParam;
        System.IntPtr LParam;
        int Time;
        Point p;
    };

    public partial class ArgonEngine : Form
    {
        public ArgonEngine()
        {
            InitializeComponent();
        }

        [System.Security.SuppressUnmanagedCodeSecurity(), System.Runtime.InteropServices.DllImport("User32.dll")]
        public static extern int PeekMessageA(MessageStruct msg, IntPtr hWnd, int messageFilterMin, int messageFilterMax, int flags);


        private bool AppIsAdle()
        {
            MessageStruct Msg = new MessageStruct();
            return (PeekMessageA(Msg, IntPtr.Zero, 0, 0, 0) == 0);
        }

        private void ArgonEngine_Load(object sender, EventArgs e)
        {
            ArgonRenderSystems RenderSystems = new ArgonRenderSystems(panel1.Handle);
            if (RenderSystems.ShowDialog() == DialogResult.OK)
            {
                System.Windows.Forms.Application.Idle += new EventHandler(this.OnApplicationUpate);
            }
            else
            {
                Application.Exit();
            }
        }

        private void OnApplicationUpate(object sender, EventArgs e)
        {
            do
            {
              ArgonEngineDll.Update();
            } while (AppIsAdle());
        }
    }
}
