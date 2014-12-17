using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Robot
{
    class Allocater
    {
        [DllImport("Allocater.dll", EntryPoint = "Start")]
        public extern static int Start(int[] rcs, int num);
        [DllImport("Allocater.dll", EntryPoint = "Allocate")]
        unsafe public extern static int Allocate(Target *targets, int num);
//        public extern static int Allocate(IntPtr prt, int num);
    }
}
