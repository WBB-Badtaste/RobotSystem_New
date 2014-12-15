using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;

namespace Robot
{
    public struct Target
    {
        public ushort ID { get; set; }///特征码，（其值为1~9999）
        public double PosX { get; set; }///横坐标，单位mm，精确到0.32mm
        public double PosY { get; set; }///纵坐标，单位mm，精确到0.32mm
        public float Aangle { get; set; }///旋转角度,精确到0.5度。平行X轴为0度，正值代表顺时针偏转，负值相反
        public long EncoderValue { get; set; }///编码器值，十位         
    };
    public class TargetUI
    {
        public TargetUI(Target target)
        {
            Target = target;
            TT = new TranslateTransform();
        }
        public Target Target { get; set; }
        public UIElement UIElement { get; set; }
        public TranslateTransform TT { get; set; }
    };
    class TargetListController
    {
        private static List<Target> staticNewTargets = new List<Target>();

        private static List<TargetUI> staticStuffTargets = new List<TargetUI>();//显示在界面送料带上

        //        private static List<Target> m_boxTargets = new List<Target>();//显示在界面进箱带上
        public static void AddNewTarget(Target targrt)
        {
            staticNewTargets.Add(targrt);
        }
        public static void AddDisplayTarget(TargetUI targetUI)
        {
            staticStuffTargets.Add(targetUI);
        }
        public static bool GetNewTarget(int index, out TargetUI targetUI)
        {
            Target target = staticNewTargets[index];
            targetUI = new TargetUI(target);
            //转存到已显示的队列
            targetUI = new TargetUI(target);
            TargetListController.AddDisplayTarget(targetUI);
            staticNewTargets.RemoveAt(index);
            return true;
        }
        public static void GetDisplayTarget(int index, out TargetUI target)
        {
            target = staticStuffTargets[index];
        }
        public static void DelNewTarget(int index)
        {
            staticNewTargets.RemoveAt(index);
        }
        public static void DelDisplayTarget(int index)
        {
            staticStuffTargets.RemoveAt(index);
        }
        public delegate bool ListMethonDelegate(int index);
        public static void Move(ListMethonDelegate MakeDelegate)
        {
            if (staticStuffTargets.Count() <= 0) return;
            for (int index = 0; index < staticStuffTargets.Count(); )
            {
                //超出画布范围后，当前target被删除，之后的target向前移位
                if (MakeDelegate(index))
                    ++index;
            }
        }
        public static void Draw(ListMethonDelegate MakeDelegate)
        {
            if (staticNewTargets.Count() <= 0) return;
            for (int index = 0; index < staticNewTargets.Count(); ++index)
            {
                MakeDelegate(index);
            }
        }
        //暂时使用
        public static void GenerateNewTarget(int nowpos)
        {
            Target newTarget = new Target();
            newTarget.Aangle = 0;
            newTarget.EncoderValue = nowpos;
            newTarget.PosX = 0;
            newTarget.PosY = 0;
            newTarget.ID = 0;
            staticNewTargets.Add(newTarget);
        }
    }
}
