using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace Robot
{
    public class Encoder
    {
        [DllImport("Encoder.dll", EntryPoint = "Encoder_Read")]
        public extern static int Encoder_Read(int axis_no, ref int value);
        [DllImport("Encoder.dll", EntryPoint = "Encoder_StartUp")]
        public extern static int Encoder_StartUp();
        [DllImport("Encoder.dll", EntryPoint = "Encoder_Close")]
        public extern static int Encoder_Close();
    }
}
