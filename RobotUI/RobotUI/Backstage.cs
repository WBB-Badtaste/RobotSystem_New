﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Robot
{
    public struct Target
    {
        public int ID;//特征码，（其值为1~9999）
        public double PosX;//横坐标，单位mm，精确到0.32mm
        public double PosY;//纵坐标，单位mm，精确到0.32mm
        public double Aangle;//旋转角度,精确到0.5度。平行X轴为0度，正值代表顺时针偏转，负值相反
        public int EncoderValue;//编码器值，十位
    };
    public struct RCInfo2dll
    {
        public IntPtr IP;
        public int Port;
        public int RcID;
    };
    public struct RCInfo
    {
        public string IP;
        public int Port;
        public int RcID;
    };
    class Backstage
    {
        [DllImport("Backstage.dll", EntryPoint = "Backstage_Startup", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        unsafe public extern static int Backstage_Startup(RCInfo2dll* pInfos, int infoCount, IntPtr localIP);
        [DllImport("Backstage.dll", EntryPoint = "Backstage_Shutdown", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        public extern static int Backstage_Shutdown();
        //设置回调
        unsafe public delegate int CB_NEWTARGET(Target* targets, int num);
        unsafe public delegate int CB_CATCHTARGET(int* targetIDs, int num);
        [DllImport("Backstage.dll", EntryPoint = "Backstage_SetCallback", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        public extern static int Backstage_SetCallback(CB_NEWTARGET func1,CB_CATCHTARGET func2);
        //Encoder
        [DllImport("Backstage.dll", EntryPoint = "Encoder_Read", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        public extern static int Encoder_Read(int axis_no, ref int value);
        //Networker
        //Allocater
//         [DllImport("Backstage.dll", EntryPoint = "Backstage_AddNewTargets", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
//         unsafe public extern static int Backstage_AddNewTargets(Target* targets, int num);
    }
}
