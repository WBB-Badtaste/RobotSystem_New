using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Robot
{
    public class BackstageOper
    {
        //保持委托函数活性的成员变量
        unsafe private static Backstage.CB_NEWTARGET CB_Newtarget = OnNewTarget;
        unsafe private static Backstage.CB_CATCHTARGET CB_Catchtarget = OnCatchTarget;
        public static int StartupBackstage()
        {
            //初始化DLL
            RCInfo[] rcInfos = new RCInfo[2];
            rcInfos[0].RcID = 1;
            rcInfos[0].IP = "127.0.0.1";
            rcInfos[0].Port = 60000;
            rcInfos[1].RcID = 2;
            rcInfos[1].IP = "127.0.0.1";
            rcInfos[1].Port = 60001;
            unsafe
            {
                RCInfo2dll[] rcInfos2dll = new RCInfo2dll[rcInfos.Length];
                for (int i = 0; i < rcInfos.Length; ++i)
                {
                    rcInfos2dll[i].IP = new IntPtr();
                    rcInfos2dll[i].IP = Marshal.AllocHGlobal(rcInfos[i].IP.Length);
                    rcInfos2dll[i].IP = Marshal.StringToHGlobalUni(rcInfos[i].IP);
                    rcInfos2dll[i].Port = rcInfos[i].Port;
                    rcInfos2dll[i].RcID = rcInfos[i].RcID;
                }
                int res = 0;
                string localIp = "127.0.0.1";
                fixed (RCInfo2dll* prt = &rcInfos2dll[0])
                {
                    IntPtr iPtr = new IntPtr();
                    iPtr = Marshal.AllocHGlobal(localIp.Length);
                    iPtr = Marshal.StringToHGlobalUni(localIp);
                    res = Backstage.Backstage_Startup(prt, rcInfos2dll.Length,iPtr);
                    Marshal.FreeHGlobal(iPtr);
                }
                for (int j = 0; j < rcInfos.Length; ++j)
                {
                    Marshal.FreeHGlobal(rcInfos2dll[j].IP);
                }
            }
            //设置回调
            unsafe
            {
                Backstage.Backstage_SetCallback(CB_Newtarget,CB_Catchtarget);
            }           
            return 0;
        }
        unsafe private static int OnNewTarget(Target* targets,int num)
        {
            for(int i=0;i<num;++i)
            {
                TargetListController.AddNewTarget(targets[i]);
            }
            return 0;
        }
        unsafe private static int OnCatchTarget(int* targetIDs, int num)
        {
            for (int i = 0; i < num; ++i)
            {
                TargetListController.AddCatchTargetID(targetIDs[i]);
            }
            return 0;
        }
    }
}
