using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Windows.Data;

namespace Robot
{
    public class StatusValue:INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private static enWorkStatus bWorkStatus = enWorkStatus.STOPED;
        public enWorkStatus WorkStatus
        {
            get { return bWorkStatus; }
            set
            {
                bWorkStatus = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("WorkStatus"));
                }
            }
        }
    }
    public class WorkStatusToButtonStartContentPathConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((enWorkStatus)value == enWorkStatus.STOPED) return "START";
            else return "STOP";
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class WorkStatusToButtonStartIsEnablePathConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((enWorkStatus)value == enWorkStatus.SUSPEND) return false;
            else return true;
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class WorkStatusToButtonSuspendContentPathConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((enWorkStatus)value == enWorkStatus.SUSPEND) return "CONTINUE";
            else return "SUSPEND";
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    public class WorkStatusToButtonSuspendIsEnablePathConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if ((enWorkStatus)value == enWorkStatus.STOPED) return false;
            else return true;
        }
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}

