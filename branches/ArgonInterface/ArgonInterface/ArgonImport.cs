namespace Argon
{
    class ArgonEngineDll
    {
        [System.Runtime.InteropServices.DllImport("ArgonEngine.dll")]
        public static extern void PreLoadEngine();

        [System.Runtime.InteropServices.DllImport("ArgonEngine.dll")]
        public static extern int GetRenderSystemCount();

        [System.Runtime.InteropServices.DllImport("ArgonEngine.dll")]
        public static extern int GetRenderSystemDriversCount(int RenderSystemIndex);

        [System.Runtime.InteropServices.DllImport("ArgonEngine.dll")]
        public static extern int GetRenderSystemDriverModesCount(int RenderSystemIndex, int DriverIndex);

        [System.Runtime.InteropServices.DllImport("ArgonEngine.dll")]
        public static extern System.IntPtr GetRenderSystemDriverModeDescA(int RenderSystemIndex, int DriverIndex, int VideoIndex);

        public static string GetRenderSystemDriverModeDesc(int RenderSystemIndex, int DriverIndex, int VideoIndex)
        {
            return System.Runtime.InteropServices.Marshal.PtrToStringAnsi(GetRenderSystemDriverModeDescA(RenderSystemIndex, DriverIndex, VideoIndex));
        }

        [System.Runtime.InteropServices.DllImport("ArgonEngine.dll")]
        public static extern System.IntPtr GetRenderSystemNameA(int RenderSystemIndex);

        public static string GetRenderSystemName(int RenderSystemIndex)
        {
            return System.Runtime.InteropServices.Marshal.PtrToStringAnsi(GetRenderSystemNameA(RenderSystemIndex));
        }

        [System.Runtime.InteropServices.DllImport("ArgonEngine.dll")]
        public static  extern void CreateEngine(int RenderSystemIndex, int DriverIndex, int VideoModeIndex, System.IntPtr Window);
    } //Class
} //Namespace