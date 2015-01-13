using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Collections;

namespace Robot
{
    public class TargetUI 
    {
        public TargetUI(Target target)
        {
            Target = target;
            TT = new TranslateTransform();
            ShowEncoderValue = target.EncoderValue;
        }
        public Target Target { get; set; }
        public UIElement UIElement { get; set; }
        public TranslateTransform TT { get; set; }
        public int ShowEncoderValue { get; set; }
    };
    class TargetListController
    {
        private static List<Target> staticNewTargets = new List<Target>();//视觉系统新捕抓到的目标
        private static List<TargetUI> staticStuffTargets = new List<TargetUI>();//显示在界面送料带上
        private static List<int> staticCatchedTargetIDs = new List<int>();//被抓取的目标
        public static void AddNewTarget(Target targrt)
        {
            staticNewTargets.Add(targrt);
        }
        public static void AddCatchTargetID(int id)
        { 
            staticCatchedTargetIDs.Add(id);
        }
        public delegate bool DelUIElement(UIElement element);
        public static bool DealWithCatchedTargets(DelUIElement DelElement)
        {
            if (staticStuffTargets.Count() <= 0) return false;
            bool res = true;
            while (staticCatchedTargetIDs.Count() > 0) 
            {
                for (int i = 0; i < staticStuffTargets.Count(); ++i)
                {
                    if (staticStuffTargets[i].Target.ID == staticCatchedTargetIDs[0])
                    {
                        DelElement(staticStuffTargets[i].UIElement);
                        staticStuffTargets.RemoveAt(i);
                        staticCatchedTargetIDs.RemoveAt(0);
                        break;
                    }
                    staticCatchedTargetIDs.RemoveAt(0);
                    res = false;
                }
            }
            return res;
        }
        public delegate bool MoveDelegate(IEnumerator<TargetUI> ie);
        public static void Move(MoveDelegate MakeDelegate)
        {
            IEnumerator<TargetUI> ie = staticStuffTargets.GetEnumerator();
            while (ie.MoveNext())
            {
                MakeDelegate(ie);
            }
        }
        public delegate bool DrawDelegate(ref TargetUI targetUI);
        public static void Draw(DrawDelegate MakeDelegate)
        {
            if (staticNewTargets.Count() <= 0) return;
            while(staticNewTargets.Count()>0)
            {
                TargetUI targetUI = new TargetUI(staticNewTargets[0]);
                staticStuffTargets.Add(targetUI);
                MakeDelegate(ref targetUI);
                staticNewTargets.RemoveAt(0);
            }
        }
    }
}
