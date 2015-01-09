using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Robot
{
    class VirtualVision
    {
        [DllImport("VirtualVision.dll", EntryPoint = "VirtualVision_Start", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        public extern static int VirtualVision_Start();
        [DllImport("VirtualVision.dll", EntryPoint = "VirtualVision_Stop", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        public extern static int VirtualVision_Stop();
    }
}
