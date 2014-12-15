using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;
using System.Windows.Media;

namespace Robot
{
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
