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
        }
        public Target Target { get; set; }
        public UIElement UIElement { get; set; }
        public TranslateTransform TT { get; set; }
    };
    class TargetListController
    {
        private static List<Target> staticNewTargets = new List<Target>();//视觉系统新捕抓到的目标

        private static List<TargetUI> staticStuffTargets = new List<TargetUI>();//显示在界面送料带上

        private static List<int> staticCatchedTargetIDs = new List<int>();//被抓取的目标

        //        private static List<Target> m_boxTargets = new List<Target>();//显示在界面进箱带上
        public static void AddNewTarget(Target targrt)
        {
            staticNewTargets.Add(targrt);
        }
        public static void AddCatchTargetID(int id)
        { 
            staticCatchedTargetIDs.Add(id);
        }
        public static bool DealWithCatchedTargets()
        {
            bool res = true;
            while (staticCatchedTargetIDs.Count() > 0)
            {
                for (int i = 0; i < staticStuffTargets.Count(); ++i)
                {
                    if (staticStuffTargets[i].Target.ID == staticCatchedTargetIDs[0])
                    {
                        staticCatchedTargetIDs.RemoveAt(0);
                        break;
                    }
                    staticCatchedTargetIDs.RemoveAt(0);
                    res = false;
                }
            }
            return res;
        }
//         public static void AddDisplayTarget(TargetUI targetUI)
//         {
//             staticStuffTargets.Add(targetUI);
//         }
//         public static bool GetNewTarget(int index, out TargetUI targetUI)
//         {
//             Target target = staticNewTargets[index];
//             targetUI = new TargetUI(target);
//             //转存到已显示的队列
//             targetUI = new TargetUI(target);
//             TargetListController.AddDisplayTarget(targetUI);
//             staticNewTargets.RemoveAt(index);
//             return true;
//         }
//         public static void GetDisplayTarget(int index, out TargetUI target)
//         {
//             target = staticStuffTargets[index];
//         }
//         public static void DelNewTarget(int index)
//         {
//             staticNewTargets.RemoveAt(index);
//         }
//         public static bool DelDisplayTarget(int targetID)
//         {
//             for (int i = 0; i < staticStuffTargets.Count(); ++i)
//             {
//                 if (staticStuffTargets[i].Target.ID == targetID)
//                 {
//                     staticStuffTargets.RemoveAt(i);
//                     return true;
//                 }
//             }
//             return false;
//         }
        public delegate bool MoveDelegate(IEnumerator<TargetUI> ie);
        public static void Move(MoveDelegate MakeDelegate)
        {
            IEnumerator<TargetUI> ie = staticStuffTargets.GetEnumerator();
            while (ie.MoveNext())
            {
                MakeDelegate(ie);
            }
//             if (staticStuffTargets.Count() <= 0) return;
//             for (int index = 0; index < staticStuffTargets.Count(); )
//             {
//                 //超出画布范围后，当前target被删除，之后的target向前移位
//                 if (MakeDelegate(index))
//                     ++index;
//             }
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
