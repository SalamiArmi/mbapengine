using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
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

            this.FormClosing += new FormClosingEventHandler(this.OnFormDestroyed);
        }

        [System.Security.SuppressUnmanagedCodeSecurity(), System.Runtime.InteropServices.DllImport("User32.dll")]
        public static extern int PeekMessageA(MessageStruct msg, IntPtr hWnd, int messageFilterMin, int messageFilterMax, int flags);

        private bool AppIsAdle()
        {
            MessageStruct Msg = new MessageStruct();

            PeekMessageA(Msg, IntPtr.Zero, 0, 0, 0);

            return false;
        }

        private void ArgonEngine_Load(object sender, EventArgs e)
        {
            ArgonEngineDll.PreLoadEngine();
            ArgonEngineDll.CreateEngine(m_RenderPanel.Handle, 0, 0, 0);

            Application.Idle += new EventHandler(this.OnApplicationUpate);
        }

        private void OnApplicationUpate(object sender, EventArgs e)
        {
             ArgonEngineDll.FrameUpdate();
        }

        private void OnFormDestroyed(object sender, FormClosingEventArgs e)
        {
            ArgonEngineDll.DestoryEngine();
        }
    }
}
