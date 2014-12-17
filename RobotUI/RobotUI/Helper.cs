using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;
using System.Windows.Media;
using System.Runtime.InteropServices;

namespace Robot
{
    [StructLayoutAttribute(LayoutKind.Sequential)]  
    public struct Target
    {
        public ushort ID;///特征码，（其值为1~9999）
        public double PosX;///横坐标，单位mm，精确到0.32mm
        public double PosY;///纵坐标，单位mm，精确到0.32mm
        public float Aangle;///旋转角度,精确到0.5度。平行X轴为0度，正值代表顺时针偏转，负值相反
        public int EncoderValue;///编码器值，十位  
        public int RcID;
    };
    public enum enWorkStatus
    {
            STARTED     = 0,//启动
            SUSPEND     = 1,//暂停
            STOPED      = 2,//停止
    };
    public enum enTargetShape
    {
        ROUND = 0,// 椭圆形
        RECTANGLE = 1,//长方形
    };
    
}
