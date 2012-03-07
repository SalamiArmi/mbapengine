using System.Runtime.InteropServices;

namespace Argon
{
    class ArgonEngineDll
    {
        #region Initialization

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern void PreLoadEngine();

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern uint GetRenderSystemCount();

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern System.IntPtr GetRenderSystemNameA(uint Index);

        public static string GetRenderSystemName(uint Index)
        {
           return Marshal.PtrToStringAnsi(GetRenderSystemNameA(Index));
        }

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern uint GetRenderSystemDriverCount(uint RenderSystemIndex);

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern uint GetRenderSystemDriverModesCount(uint RenderSystemIndex, uint DriveIndex);

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern System.IntPtr GetRenderSystemDriverModeA(uint RenderSystemIndex, uint DriveIndex, uint VideoModeIndex);

        public static string GetRenderSystemDriverMode(uint RenderSystemIndex, uint DriveIndex, uint VideoModeIndex)
        {
            return Marshal.PtrToStringAnsi(GetRenderSystemDriverModeA(RenderSystemIndex, DriveIndex, VideoModeIndex));
        }

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern void CreateEngine(System.IntPtr Window, uint RenderSystemIndex, uint DriverIndex, uint ModeIndex);

        #endregion

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern bool DestoryEngine();

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern void FrameUpdate();
    } //Class
} //Namespace