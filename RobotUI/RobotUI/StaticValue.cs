using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace Robot
{
    class StaticValue : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public StaticValue()
        {
            stuffConveyorLength = 3000;
            stuffConveyorWidth = 600;
            boxConveyorLength = 3000;
            boxConveyorWidth = 200;
            targetRadius = 100;
            canvasX = 3200;
            canvasY = 1000;
            refreshTime = 100;
        }
/******************************************************
 *
 *                  画布大小
 *        
******************************************************/
        private static double canvasX = 0;
        public double CanvasX
        {
            get{return canvasX;}
            set
            { 
                canvasX = value ; 
                if(PropertyChanged!=null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("CanvasX"));
                }
            }
        }
        private static double canvasY = 0;
        public double CanvasY
        {
            get { return canvasY ; }
            set 
            { 
                canvasY = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("CanvasY"));
                }
            }
        }
/******************************************************
 *
 *                  视觉系统
 *        
 ******************************************************/
        //图像原点相对传送带的位置坐标X
        private static double picOriginX=0;
        public double PicOriginX
        {
            get { return picOriginX; }
            set
            {
                picOriginX = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("PicOriginX"));
                }
            }
        }
        //图像原点相对传送带的位置坐标Y
        private static double picOriginY=0;
        public double PicOriginY
        {
            get { return picOriginY; }
            set
            {
                picOriginY = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("PicOriginY"));
                }
            }
        }
/******************************************************
 *
 *                  传送带
 *        
 ******************************************************/
        //送料带原点位置
        private static double stuffConveyorOriginX = 0;
        public double StuffConveyorOriginX
        {
            get { return stuffConveyorOriginX; }
            set
            {
                stuffConveyorOriginX = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("StuffConveyorOriginX"));
                }
            }
        }
        private static double stuffConveyorOriginY = 0;
        public double StuffConveyorOriginY
        {
            get { return stuffConveyorOriginY; }
            set
            {
                stuffConveyorOriginY = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("StuffConveyorOriginY"));
                }
            }
        }
        //送料带长度 单位mm
        private static double stuffConveyorLength=0;
        public double StuffConveyorLength
        {
            get{return stuffConveyorLength;}
            set 
            {
                stuffConveyorLength = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("StuffConveyorLength"));
                }
            }
        }
        //送料带宽度 单位mm
        private static double stuffConveyorWidth=0;
        public double StuffConveyorWidth
        {
            get { return stuffConveyorWidth; }
            set 
            {
                StuffConveyorWidth = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("stuffConveyorWidth"));
                }
            }
        }
        //送料带原点位置
        private static double boxConveyorOriginX = 0;
        public double BoxConveyorOriginX
        {
            get { return boxConveyorOriginX; }
            set
            {
                boxConveyorOriginX = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("BoxConveyorOriginX"));
                }
            }
        }
        private static double boxConveyorOriginY = 0;
        public double BoxConveyorOriginY
        {
            get { return boxConveyorOriginY; }
            set
            {
                boxConveyorOriginY = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("BoxConveyorOriginY"));
                }
            }
        }
        //送箱带长度 单位mm
        private static double boxConveyorLength=0;
        public double BoxConveyorLength
        {
            get { return boxConveyorLength; }
            set
            {
                boxConveyorLength = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("BoxConveyorLength"));
                }
            }
        }
        //送箱带宽度 单位mm
        private static double boxConveyorWidth=0;
        public double BoxConveyorWidth
        {
            get { return boxConveyorWidth; }
            set
            {
                boxConveyorWidth = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("BoxConveyorWidth"));
                }
            }
        }
/******************************************************
 *
 *                  编码器
 *        
 ******************************************************/
        //编码器线位代表的实际长度 单位mm/线
        private static double stuffEncoderRate=1;
        public double StuffEncoderRate
        {
            get { return stuffEncoderRate; }
            set
            {
                stuffEncoderRate = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("StuffEncoderRate"));
                }
            }
        }
        private static double boxEncoderRate = 1;
        public double BoxEncoderRate
        {
            get { return boxEncoderRate; }
            set
            {
                boxEncoderRate = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("BoxEncoderRate"));
                }
            }
        }
/******************************************************
 *
 *                   屏幕
 *        
 ******************************************************/
        // 刷新时间间隔
        private static double refreshTime = 100;
        public double RefreshTime
        {
            get { return refreshTime; }
            set
            {
                refreshTime = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("RefreshTime"));
                }
            }
        }
        //缩放比例系数
        private static double zoomRate = 1;
        public double ZoomRate
        {
            get { return zoomRate; }
            set 
            { 
                zoomRate = value; 
                if(PropertyChanged!=null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("ZoomRate"));
                }
            }
        }
        //屏幕像素代表的实际长度 单位mm/px
        private static double screenRate=1;
        public double ScreenRate
        {
            get { return screenRate; }
            set
            {
                screenRate = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("ScreenRate"));
                }
            }
        }

/******************************************************
 *
 *                  抓取目标
 *        
 ******************************************************/
        private static enTargetShape targetShape = enTargetShape.ROUND;
        public enTargetShape TargetShape
        {
            get { return targetShape; }
            set
            {
                targetShape = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("TargetShape"));
                }
            }
        }
        //目标宽度
        private static double targetWidth=0;
        public double TargetWidth
        {
            get { return targetWidth; }
            set
            {
                targetWidth = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("TargetWidth"));
                }
            }
        }
        //目标长度
        private static double targetLength=0;
        public double TargetLength
        {
            get { return targetLength; }
            set
            {
                targetLength = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("TargetLength"));
                }
            }
        }
        private static double targetRadius=0;
        /// <summary>
        /// 目标半径
        /// </summary>
        public double TargetRadius
        {
            get { return targetRadius; }
            set
            {
                targetRadius = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("TargetRadius"));
                }
                
            }
        }
/******************************************************
 *
 *                  其他
 *        
 ******************************************************/
        /// <summary>
        /// 控制器数量
        /// </summary>
        public static int RcCount { get; set; }
    }
/******************************************************
 *
 *                  转换器
 *        
 ******************************************************/
    public class DoubleScreenRateZoomRateConverter:IMultiValueConverter
    {
        public object Convert(object[] values, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return (double)values[0] / (double)values[1] * (double)values[2];
        }
        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    
    
}
