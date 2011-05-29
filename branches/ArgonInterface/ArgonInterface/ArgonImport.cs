namespace Argon
{
    class ArgonEngineDll
    {
        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern void PreLoadEngine();

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern void CreateEngine(System.IntPtr Window, uint RenderSystemIndex, uint DriverIndex, uint ModeIndex);

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern bool DestoryEngine();

        [System.Runtime.InteropServices.DllImport(@"ArgonEngine.dll")]
        public static extern void FrameUpdate();
    } //Class
} //Namespace