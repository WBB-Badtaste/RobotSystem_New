using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Media.Animation;
using System.Windows.Threading;
using System.Runtime.InteropServices;

namespace Robot
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    /// 
    public partial class MainWindow : Window
    {
        //运行数据对象
        private StaticValue m_staticValue;
        private StatusValue m_statusValue;
        private DoubleAnimation m_daMove;
        private DispatcherTimer m_dispatcherTimer;
        public MainWindow()
        {
            InitializeComponent();
            //初始化DLL
            BackstageOper.StartupBackstage();
            //创建屏幕相关静态数据对象
            m_staticValue = new StaticValue();
            BindCanvas();
            BindConveyor();
            //创建运行状态数据对象
            m_statusValue = new StatusValue();
            BindButton();
        }
        ~MainWindow()
        {
            Backstage.Backstage_Shutdown();
        }
        private void BindButton()
        {
            Button_Start.SetBinding(Button.ContentProperty, new Binding("WorkStatus") { Source = m_statusValue, Converter = new WorkStatusToButtonStartContentPathConverter(), Mode = BindingMode.OneWay });
            Button_Start.SetBinding(Button.IsEnabledProperty, new Binding("WorkStatus") { Source = m_statusValue, Converter = new WorkStatusToButtonStartIsEnablePathConverter(), Mode = BindingMode.OneWay });
            Button_Suspend.SetBinding(Button.ContentProperty, new Binding("WorkStatus") { Source = m_statusValue, Converter = new WorkStatusToButtonSuspendContentPathConverter(), Mode = BindingMode.OneWay });
            Button_Suspend.SetBinding(Button.IsEnabledProperty, new Binding("WorkStatus") { Source = m_statusValue, Converter = new WorkStatusToButtonSuspendIsEnablePathConverter(), Mode = BindingMode.OneWay });
        }
        private void BindCanvas()
        {
            MultiBinding MBCanvasX = new MultiBinding() { Converter = new DoubleScreenRateZoomRateConverter() };
            MBCanvasX.Bindings.Add(new Binding("CanvasX") { Source = m_staticValue });
            MBCanvasX.Bindings.Add(new Binding("ScreenRate") { Source = m_staticValue });
            MBCanvasX.Bindings.Add(new Binding("ZoomRate") { Source = m_staticValue });
            canvas2D.SetBinding(Canvas.WidthProperty, MBCanvasX);
            MultiBinding MBCanvasY = new MultiBinding() { Converter = new DoubleScreenRateZoomRateConverter() };
            MBCanvasY.Bindings.Add(new Binding("CanvasY") { Source = m_staticValue });
            MBCanvasY.Bindings.Add(new Binding("ScreenRate") { Source = m_staticValue });
            MBCanvasY.Bindings.Add(new Binding("ZoomRate") { Source = m_staticValue });
            canvas2D.SetBinding(Canvas.HeightProperty, MBCanvasY);
        }
        private void BindConveyor()
        {
            stuffConveyor.SetBinding(Canvas.LeftProperty, new Binding("StuffConveyorOriginX") { Source = m_staticValue });
            stuffConveyor.SetBinding(Canvas.TopProperty, new Binding("StuffConveyorOriginY") { Source = m_staticValue });
            boxConveyor.SetBinding(Canvas.LeftProperty, new Binding("BoxConveyorOriginX") { Source = m_staticValue });
            boxConveyor.SetBinding(Canvas.TopProperty, new Binding("BoxConveyorOriginY") { Source = m_staticValue });
            MultiBinding MBStuffConveyorX = new MultiBinding() { Converter = new DoubleScreenRateZoomRateConverter() };
            MBStuffConveyorX.Bindings.Add(new Binding("StuffConveyorLength") { Source = m_staticValue });
            MBStuffConveyorX.Bindings.Add(new Binding("ScreenRate") { Source = m_staticValue });
            MBStuffConveyorX.Bindings.Add(new Binding("ZoomRate") { Source = m_staticValue });
            stuffConveyor.SetBinding(Rectangle.WidthProperty, MBStuffConveyorX);
            MultiBinding MBStuffConveyorY = new MultiBinding() { Converter = new DoubleScreenRateZoomRateConverter() };
            MBStuffConveyorY.Bindings.Add(new Binding("StuffConveyorWidth") { Source = m_staticValue });
            MBStuffConveyorY.Bindings.Add(new Binding("ScreenRate") { Source = m_staticValue });
            MBStuffConveyorY.Bindings.Add(new Binding("ZoomRate") { Source = m_staticValue });
            stuffConveyor.SetBinding(Rectangle.HeightProperty, MBStuffConveyorY);
            MultiBinding MBBoxfConveyorX = new MultiBinding() { Converter = new DoubleScreenRateZoomRateConverter() };
            MBBoxfConveyorX.Bindings.Add(new Binding("BoxConveyorLength") { Source = m_staticValue });
            MBBoxfConveyorX.Bindings.Add(new Binding("ScreenRate") { Source = m_staticValue });
            MBBoxfConveyorX.Bindings.Add(new Binding("ZoomRate") { Source = m_staticValue });
            boxConveyor.SetBinding(Rectangle.WidthProperty, MBBoxfConveyorX);
            MultiBinding MBBoxfConveyorY = new MultiBinding() { Converter = new DoubleScreenRateZoomRateConverter() };
            MBBoxfConveyorY.Bindings.Add(new Binding("BoxConveyorWidth") { Source = m_staticValue });
            MBBoxfConveyorY.Bindings.Add(new Binding("ScreenRate") { Source = m_staticValue });
            MBBoxfConveyorY.Bindings.Add(new Binding("ZoomRate") { Source = m_staticValue });
            boxConveyor.SetBinding(Rectangle.HeightProperty, MBBoxfConveyorY);
        }
        private void BindTarget(ref Ellipse eNewTarget, ref TargetUI targetUI)
        {
            MultiBinding MBTargetR = new MultiBinding() { Converter = new TargetSizeConverter() };
            MBTargetR.Bindings.Add(new Binding("TargetRadius") { Source = m_staticValue });
            MBTargetR.Bindings.Add(new Binding("ScreenRate") { Source = m_staticValue });
            MBTargetR.Bindings.Add(new Binding("ZoomRate") { Source = m_staticValue });
            eNewTarget.SetBinding(Ellipse.WidthProperty, MBTargetR);
            eNewTarget.SetBinding(Ellipse.HeightProperty, MBTargetR);
            MultiBinding MBTargetCanvasLeft = new MultiBinding() { Converter = new TargetPosXConverter(targetUI.Target.PosX) };
            MBTargetCanvasLeft.Bindings.Add(new Binding("TargetRadius") { Source = m_staticValue });
            MBTargetCanvasLeft.Bindings.Add(new Binding("StuffConveyorOriginX") { Source = m_staticValue });
            MBTargetCanvasLeft.Bindings.Add(new Binding("ScreenRate") { Source = m_staticValue });
            MBTargetCanvasLeft.Bindings.Add(new Binding("ZoomRate") { Source = m_staticValue });
            eNewTarget.SetBinding(Canvas.LeftProperty, MBTargetCanvasLeft);
            MultiBinding MBTargetCanvasTop = new MultiBinding() { Converter = new TargetPosYConverter(targetUI.Target.PosY) };
            MBTargetCanvasTop.Bindings.Add(new Binding("TargetRadius") { Source = m_staticValue });
            MBTargetCanvasTop.Bindings.Add(new Binding("StuffConveyorOriginY") { Source = m_staticValue });
            MBTargetCanvasTop.Bindings.Add(new Binding("ScreenRate") { Source = m_staticValue });
            MBTargetCanvasTop.Bindings.Add(new Binding("ZoomRate") { Source = m_staticValue });
            eNewTarget.SetBinding(Canvas.TopProperty, MBTargetCanvasTop);
        }
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            m_daMove = new DoubleAnimation();
            m_daMove.Duration = new Duration(TimeSpan.FromMilliseconds(m_staticValue.RefreshTime));
            m_dispatcherTimer = new DispatcherTimer();
            m_dispatcherTimer.Tick += new EventHandler(OnTimedEvent);
            m_dispatcherTimer.Interval = TimeSpan.FromMilliseconds(m_staticValue.RefreshTime);
            m_dispatcherTimer.Start();
        }
        static int currentEncoderValue = 100;
        private void OnTimedEvent(object sender, EventArgs e)
        {
            
            //读编码器值
/*            Backstage.Encoder_Read(0, ref currentEncoderValue);*/
            currentEncoderValue += 20;
            //扫描并显示新的Target图形
            TargetListController.Draw(DrawTarget);
            //处理已抓取的Target
            TargetListController.DealWithCatchedTargets(DelTarget);
            //移动Targets
            TargetListController.Move(MoveTarget);
        }
        private bool MoveTarget(IEnumerator<TargetUI> ie)
        {
            m_daMove.By = (currentEncoderValue - ie.Current.ShowEncoderValue) * m_staticValue.StuffEncoderRate / m_staticValue.ScreenRate * m_staticValue.ZoomRate;
            ie.Current.TT.BeginAnimation(TranslateTransform.XProperty, m_daMove);
            ie.Current.ShowEncoderValue = currentEncoderValue;
            return true;
        }
        private bool DelTarget(UIElement element)
        {
            canvas2D.Children.Remove(element);
            return true;
        }
        private bool DrawTarget(ref TargetUI targetUI)
        {
            Ellipse eNewTarget = new Ellipse();
            //设置颜色
            SolidColorBrush mySolidColorBrush = new SolidColorBrush();
            mySolidColorBrush.Color = Color.FromArgb(255, 100, 149, 237);
            eNewTarget.Fill = mySolidColorBrush;
            //设置在画布的位置
            canvas2D.Children.Add(eNewTarget);
            //设置大小、位置
            BindTarget(ref eNewTarget, ref targetUI);
            //设置呈现变形
            eNewTarget.RenderTransform = targetUI.TT;
            //关联target实例
            targetUI.UIElement = eNewTarget;
            targetUI.ShowEncoderValue = currentEncoderValue;
            return true;
        }
        private void mainWindow_Closed(object sender, EventArgs e)
        {
            int res = Backstage.Backstage_Shutdown();
        }
        private void Button_Start_Click(object sender, RoutedEventArgs e)
        {
            if (m_statusValue.WorkStatus == enWorkStatus.STOPED) m_statusValue.WorkStatus = enWorkStatus.STARTED;
            else if (m_statusValue.WorkStatus == enWorkStatus.STARTED) m_statusValue.WorkStatus = enWorkStatus.STOPED;
        }
        private void Button_Suspend_Click(object sender, RoutedEventArgs e)
        {
            if (m_statusValue.WorkStatus == enWorkStatus.SUSPEND) m_statusValue.WorkStatus = enWorkStatus.STARTED;
            else if (m_statusValue.WorkStatus == enWorkStatus.STARTED) m_statusValue.WorkStatus = enWorkStatus.SUSPEND;
        }
        private void button1_Click1(object sender, RoutedEventArgs e)
        {
            VirtualVision.VirtualVision_Start();
        }
        private void button1_Click2(object sender, RoutedEventArgs e)
        {
            VirtualVision.VirtualVision_Stop();
        }
    }
}
