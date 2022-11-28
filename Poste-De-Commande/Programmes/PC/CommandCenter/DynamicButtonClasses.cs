using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BRS;
using BRS.Buttons;
using System.Drawing;
using CommandCenter.Properties;

namespace CommandCenter
{
    //#############################################################//
    /// <summary>
    /// Class containing all the pngs used to display a USB button.
    /// </summary>
    //#############################################################//
    public class USB_Icons
    {
        /////////////////////////////////////////////////////////////
        private static EventsColors Default = new EventsColors(Color.Black);

        //////////////////////////////////////////////////////////// - LOADING
        private static Bitmap Loading_Default = Resources.Generic_Loading;
        private static Bitmap Loading_Hovering = Resources.Generic_Loading;
        private static Bitmap Loading_Pressing = Resources.Generic_Loading;
        private static EventsBitmaps Loading_Bitmaps;

        //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
        private static Bitmap Active_Default = Resources.USB_Available_Empty;
        private static Bitmap Active_Hovering = Resources.USB_Available_Empty;
        private static Bitmap Active_Pressing = Resources.USB_Available_Filled;
        private static EventsBitmaps Active_Bitmaps;

        private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
        //////////////////////////////////////////////////////////// - Disabled + inactive
        private static Bitmap Disabled_Default = Resources.USB_Disabled_Empty;
        private static Bitmap Disabled_Hovering = Resources.USB_Disabled_Empty;
        private static Bitmap Disabled_Pressing = Resources.USB_Disabled_Filled;
        private static EventsBitmaps Disabled_Bitmaps;
        //////////////////////////////////////////////////////////// - Error
        private static Bitmap Error_Default = Resources.USB_Error_Empty;
        private static Bitmap Error_Hovering = Resources.USB_Error_Empty;
        private static Bitmap Error_Pressing = Resources.USB_Error_Filled;
        private static EventsBitmaps Error_Bitmaps;

        private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
        //////////////////////////////////////////////////////////// - Warning
        private static Bitmap Warning_Default = Resources.USB_Warning_Empty;
        private static Bitmap Warning_Hovering = Resources.USB_Warning_Empty;
        private static Bitmap Warning_Pressing = Resources.USB_Warning_Filled;
        private static EventsBitmaps Warning_Bitmaps;
        ////////////////////////////////////////////////////////////
        private static StatesBitmaps statesBitmaps;
        private static StatesColors statesColors;

        public static StatesColors GetStatesColors()
        {
            statesColors = new StatesColors(Default, Active, Red, Red, Default, Default);
            return (statesColors);
        }

        public static StatesBitmaps GetStatesBitmaps()
        {
            Loading_Bitmaps  = new EventsBitmaps(Loading_Default, Loading_Hovering, Loading_Pressing);
            Active_Bitmaps   = new EventsBitmaps(Active_Default, Active_Hovering, Active_Pressing);
            Disabled_Bitmaps = new EventsBitmaps(Disabled_Default, Disabled_Hovering, Disabled_Pressing);
            Error_Bitmaps    = new EventsBitmaps(Error_Default, Error_Hovering, Error_Pressing);
            Warning_Bitmaps  = new EventsBitmaps(Warning_Default, Warning_Hovering, Warning_Pressing);

            statesBitmaps = new StatesBitmaps(Disabled_Bitmaps, Active_Bitmaps, Error_Bitmaps, Warning_Bitmaps, Loading_Bitmaps, Disabled_Bitmaps);

            return (statesBitmaps);
        }
    }
    //#############################################################//
    /// <summary>
    /// Class containing all the pngs used to display a power button.
    /// </summary>
    //#############################################################//
    public class Power_Icons
    {
        /////////////////////////////////////////////////////////////
        private static EventsColors Default = new EventsColors(Color.Black);

        //////////////////////////////////////////////////////////// - LOADING
        private static Bitmap Loading_Default = Resources.Generic_Loading;
        private static Bitmap Loading_Hovering = Resources.Generic_Loading;
        private static Bitmap Loading_Pressing = Resources.Generic_Loading;
        private static EventsBitmaps Loading_Bitmaps;

        //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
        private static Bitmap Active_Default = Resources.PowerButton_Active_Empty;
        private static Bitmap Active_Hovering = Resources.PowerButton_Active_Empty;
        private static Bitmap Active_Pressing = Resources.PowerButton_Active_Filled;
        private static EventsBitmaps Active_Bitmaps;

        private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
        //////////////////////////////////////////////////////////// - Disabled + inactive
        private static Bitmap Disabled_Default = Resources.PowerButton_Disabled_Empty;
        private static Bitmap Disabled_Hovering = Resources.PowerButton_Disabled_Empty;
        private static Bitmap Disabled_Pressing = Resources.PowerButton_Disabled_Filled;
        private static EventsBitmaps Disabled_Bitmaps;
        //////////////////////////////////////////////////////////// - Error
        private static Bitmap Error_Default = Resources.PowerButton_Error_Empty;
        private static Bitmap Error_Hovering = Resources.PowerButton_Error_Empty;
        private static Bitmap Error_Pressing = Resources.PowerButton_Error_Filled;
        private static EventsBitmaps Error_Bitmaps;

        private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
        //////////////////////////////////////////////////////////// - Warning
        private static Bitmap Warning_Default = Resources.PowerButton_Warning_Empty;
        private static Bitmap Warning_Hovering = Resources.PowerButton_Warning_Empty;
        private static Bitmap Warning_Pressing = Resources.PowerButton_Warning_Filled;
        private static EventsBitmaps Warning_Bitmaps;
        ////////////////////////////////////////////////////////////
        private static StatesBitmaps statesBitmaps;
        private static StatesColors statesColors;

        public static StatesColors GetStatesColors()
        {
            statesColors = new StatesColors(Default, Active, Red, Red, Default, Default);
            return (statesColors);
        }

        public static StatesBitmaps GetStatesBitmaps()
        {
            Loading_Bitmaps = new EventsBitmaps(Loading_Default, Loading_Hovering, Loading_Pressing);
            Active_Bitmaps = new EventsBitmaps(Active_Default, Active_Hovering, Active_Pressing);
            Disabled_Bitmaps = new EventsBitmaps(Disabled_Default, Disabled_Hovering, Disabled_Pressing);
            Error_Bitmaps = new EventsBitmaps(Error_Default, Error_Hovering, Error_Pressing);
            Warning_Bitmaps = new EventsBitmaps(Warning_Default, Warning_Hovering, Warning_Pressing);

            statesBitmaps = new StatesBitmaps(Disabled_Bitmaps, Active_Bitmaps, Error_Bitmaps, Warning_Bitmaps, Loading_Bitmaps, Disabled_Bitmaps);

            return (statesBitmaps);
        }
    }
    //#############################################################//
    /// <summary>
    /// Class containing all the pngs used to display a Link button.
    /// </summary>
    //#############################################################//
    public class Link_Icons
    {
        /////////////////////////////////////////////////////////////
        private static EventsColors Default = new EventsColors(Color.Black);

        //////////////////////////////////////////////////////////// - LOADING
        private static Bitmap Loading_Default = Resources.Generic_Loading;
        private static Bitmap Loading_Hovering = Resources.Generic_Loading;
        private static Bitmap Loading_Pressing = Resources.Generic_Loading;
        private static EventsBitmaps Loading_Bitmaps;

        //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
        private static Bitmap Active_Default = Resources.Link_Available_Empty;
        private static Bitmap Active_Hovering = Resources.Link_Available_Empty;
        private static Bitmap Active_Pressing = Resources.Link_Available_Filled;
        private static EventsBitmaps Active_Bitmaps;

        private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
        //////////////////////////////////////////////////////////// - Disabled
        private static Bitmap Disabled_Default = Resources.Link_Disabled_Empty;
        private static Bitmap Disabled_Hovering = Resources.Link_Disabled_Empty;
        private static Bitmap Disabled_Pressing = Resources.Link_Disabled_Filled;
        private static EventsBitmaps Disabled_Bitmaps;
        //////////////////////////////////////////////////////////// - Inactive
        private static Bitmap Inactive_Default = Resources.Link_Inactive_Empty;
        private static Bitmap Inactive_Hovering = Resources.Link_Inactive_Empty;
        private static Bitmap Inactive_Pressing = Resources.Link_Inactive_Filled;
        private static EventsBitmaps Inactive_Bitmaps;
        //////////////////////////////////////////////////////////// - Error
        private static Bitmap Error_Default = Resources.Link_Error_Empty;
        private static Bitmap Error_Hovering = Resources.Link_Error_Empty;
        private static Bitmap Error_Pressing = Resources.Link_Error_Filled;
        private static EventsBitmaps Error_Bitmaps;

        private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
        //////////////////////////////////////////////////////////// - Warning
        private static Bitmap Warning_Default = Resources.Link_Warning_Empty;
        private static Bitmap Warning_Hovering = Resources.Link_Warning_Empty;
        private static Bitmap Warning_Pressing = Resources.Link_Warning_Filled;
        private static EventsBitmaps Warning_Bitmaps;
        ////////////////////////////////////////////////////////////
        private static StatesBitmaps statesBitmaps;
        private static StatesColors statesColors;

        public static StatesColors GetStatesColors()
        {
            statesColors = new StatesColors(Default, Active, Red, Red, Default, Default);
            return (statesColors);
        }

        public static StatesBitmaps GetStatesBitmaps()
        {
            Loading_Bitmaps = new EventsBitmaps(Loading_Default, Loading_Hovering, Loading_Pressing);
            Active_Bitmaps = new EventsBitmaps(Active_Default, Active_Hovering, Active_Pressing);
            Disabled_Bitmaps = new EventsBitmaps(Disabled_Default, Disabled_Hovering, Disabled_Pressing);
            Error_Bitmaps = new EventsBitmaps(Error_Default, Error_Hovering, Error_Pressing);
            Warning_Bitmaps = new EventsBitmaps(Warning_Default, Warning_Hovering, Warning_Pressing);
            Inactive_Bitmaps = new EventsBitmaps(Inactive_Default, Inactive_Hovering, Inactive_Pressing);

            statesBitmaps = new StatesBitmaps(Disabled_Bitmaps, Active_Bitmaps, Error_Bitmaps, Warning_Bitmaps, Loading_Bitmaps, Inactive_Bitmaps);

            return (statesBitmaps);
        }
    }
    //#############################################################//
    /// <summary>
    /// Class containing all the pngs used to display a Link button.
    /// </summary>
    //#############################################################//
    public class Terminal_Icons
    {
        /////////////////////////////////////////////////////////////
        private static EventsColors Default = new EventsColors(Color.Black);

        //////////////////////////////////////////////////////////// - LOADING
        private static Bitmap Loading_Default = Resources.Generic_Loading;
        private static Bitmap Loading_Hovering = Resources.Generic_Loading;
        private static Bitmap Loading_Pressing = Resources.Generic_Loading;
        private static EventsBitmaps Loading_Bitmaps;

        //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
        private static Bitmap Active_Default = Resources.Terminal_Available_Empty;
        private static Bitmap Active_Hovering = Resources.Terminal_Available_Empty;
        private static Bitmap Active_Pressing = Resources.Terminal_Available_Filled;
        private static EventsBitmaps Active_Bitmaps;

        private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
        //////////////////////////////////////////////////////////// - Disabled
        private static Bitmap Disabled_Default = Resources.Terminal_Disabled_Empty;
        private static Bitmap Disabled_Hovering = Resources.Terminal_Disabled_Empty;
        private static Bitmap Disabled_Pressing = Resources.Terminal_Disabled_Filled;
        private static EventsBitmaps Disabled_Bitmaps;
        //////////////////////////////////////////////////////////// - Inactive
        private static Bitmap Inactive_Default = Resources.Terminal_Inactive_Empty;
        private static Bitmap Inactive_Hovering = Resources.Terminal_Inactive_Empty;
        private static Bitmap Inactive_Pressing = Resources.Terminal_Inactive_Filled;
        private static EventsBitmaps Inactive_Bitmaps;
        //////////////////////////////////////////////////////////// - Error
        private static Bitmap Error_Default = Resources.Terminal_Error_Empty;
        private static Bitmap Error_Hovering = Resources.Terminal_Error_Empty;
        private static Bitmap Error_Pressing = Resources.Terminal_Error_Filled;
        private static EventsBitmaps Error_Bitmaps;

        private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
        //////////////////////////////////////////////////////////// - Warning
        private static Bitmap Warning_Default = Resources.Terminal_Warning_Empty;
        private static Bitmap Warning_Hovering = Resources.Terminal_Warning_Empty;
        private static Bitmap Warning_Pressing = Resources.Terminal_Warning_Filled;
        private static EventsBitmaps Warning_Bitmaps;
        ////////////////////////////////////////////////////////////
        private static StatesBitmaps statesBitmaps;
        private static StatesColors statesColors;

        public static StatesColors GetStatesColors()
        {
            statesColors = new StatesColors(Default, Active, Red, Red, Default, Default);
            return (statesColors);
        }

        public static StatesBitmaps GetStatesBitmaps()
        {
            Loading_Bitmaps = new EventsBitmaps(Loading_Default, Loading_Hovering, Loading_Pressing);
            Active_Bitmaps = new EventsBitmaps(Active_Default, Active_Hovering, Active_Pressing);
            Disabled_Bitmaps = new EventsBitmaps(Disabled_Default, Disabled_Hovering, Disabled_Pressing);
            Error_Bitmaps = new EventsBitmaps(Error_Default, Error_Hovering, Error_Pressing);
            Warning_Bitmaps = new EventsBitmaps(Warning_Default, Warning_Hovering, Warning_Pressing);
            Inactive_Bitmaps = new EventsBitmaps(Inactive_Default, Inactive_Hovering, Inactive_Pressing);

            statesBitmaps = new StatesBitmaps(Disabled_Bitmaps, Active_Bitmaps, Error_Bitmaps, Warning_Bitmaps, Loading_Bitmaps, Inactive_Bitmaps);

            return (statesBitmaps);
        }
    }
    //#############################################################//
    /// <summary>
    /// Class containing all the pngs used to display a Link button.
    /// </summary>
    //#############################################################//
    public class CheckBox_Icons
    {
        /////////////////////////////////////////////////////////////
        private static EventsColors Default = new EventsColors(Color.Black);

        //////////////////////////////////////////////////////////// - LOADING
        private static Bitmap Loading_Default  = Resources.Generic_Loading;
        private static Bitmap Loading_Hovering = Resources.Generic_Loading;
        private static Bitmap Loading_Pressing = Resources.Generic_Loading;
        private static EventsBitmaps Loading_Bitmaps;

        //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
        private static Bitmap Active_Default  = Resources.CheckBox_Available_Empty;
        private static Bitmap Active_Hovering = Resources.CheckBox_Available_Empty;
        private static Bitmap Active_Pressing = Resources.CheckBox_Available_Filled;
        private static EventsBitmaps Active_Bitmaps;

        private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
        //////////////////////////////////////////////////////////// - Disabled
        private static Bitmap Disabled_Default  = Resources.CheckBox_Disabled_Empty;
        private static Bitmap Disabled_Hovering = Resources.CheckBox_Disabled_Empty;
        private static Bitmap Disabled_Pressing = Resources.CheckBox_Disabled_Filled;
        private static EventsBitmaps Disabled_Bitmaps;
        //////////////////////////////////////////////////////////// - Inactive
        private static Bitmap Inactive_Default  = Resources.CheckBox_Inactive_Empty;
        private static Bitmap Inactive_Hovering = Resources.CheckBox_Inactive_Empty;
        private static Bitmap Inactive_Pressing = Resources.CheckBox_Inactive_Filled;
        private static EventsBitmaps Inactive_Bitmaps;
        //////////////////////////////////////////////////////////// - Error
        private static Bitmap Error_Default  = Resources.CheckBox_Error_Empty;
        private static Bitmap Error_Hovering = Resources.CheckBox_Error_Empty;
        private static Bitmap Error_Pressing = Resources.CheckBox_Error_Filled;
        private static EventsBitmaps Error_Bitmaps;

        private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
        //////////////////////////////////////////////////////////// - Warning
        private static Bitmap Warning_Default  = Resources.CheckBox_Warning_Empty;
        private static Bitmap Warning_Hovering = Resources.CheckBox_Warning_Empty;
        private static Bitmap Warning_Pressing = Resources.CheckBox_Warning_Filled;
        private static EventsBitmaps Warning_Bitmaps;
        ////////////////////////////////////////////////////////////
        private static StatesBitmaps statesBitmaps;
        private static StatesColors statesColors;

        public static StatesColors GetStatesColors()
        {
            statesColors = new StatesColors(Default, Active, Red, Red, Default, Default);
            return (statesColors);
        }

        public static StatesBitmaps GetStatesBitmaps()
        {
            Loading_Bitmaps = new EventsBitmaps(Loading_Default, Loading_Hovering, Loading_Pressing);
            Active_Bitmaps = new EventsBitmaps(Active_Default, Active_Hovering, Active_Pressing);
            Disabled_Bitmaps = new EventsBitmaps(Disabled_Default, Disabled_Hovering, Disabled_Pressing);
            Error_Bitmaps = new EventsBitmaps(Error_Default, Error_Hovering, Error_Pressing);
            Warning_Bitmaps = new EventsBitmaps(Warning_Default, Warning_Hovering, Warning_Pressing);
            Inactive_Bitmaps = new EventsBitmaps(Inactive_Default, Inactive_Hovering, Inactive_Pressing);

            statesBitmaps = new StatesBitmaps(Disabled_Bitmaps, Active_Bitmaps, Error_Bitmaps, Warning_Bitmaps, Loading_Bitmaps, Inactive_Bitmaps);

            return (statesBitmaps);
        }
    }

    //#############################################################//
    /// <summary>
    /// Class containing all the pngs used to display a Link button.
    /// </summary>
    //#############################################################//
    public class X_Icons
    {
        /////////////////////////////////////////////////////////////
        private static EventsColors Default = new EventsColors(Color.Black);

        //////////////////////////////////////////////////////////// - LOADING
        private static Bitmap Loading_Default = Resources.Generic_Loading;
        private static Bitmap Loading_Hovering = Resources.Generic_Loading;
        private static Bitmap Loading_Pressing = Resources.Generic_Loading;
        private static EventsBitmaps Loading_Bitmaps;

        //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
        private static Bitmap Active_Default = Resources.X_Button_Available_Empty;
        private static Bitmap Active_Hovering = Resources.X_Button_Available_Empty;
        private static Bitmap Active_Pressing = Resources.X_Button_Available_Filled;
        private static EventsBitmaps Active_Bitmaps;

        private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
        //////////////////////////////////////////////////////////// - Disabled
        private static Bitmap Disabled_Default = Resources.X_Button_Disabled;
        private static Bitmap Disabled_Hovering = Resources.X_Button_Disabled;
        private static Bitmap Disabled_Pressing = Resources.X_Button_Disabled;
        private static EventsBitmaps Disabled_Bitmaps;
        //////////////////////////////////////////////////////////// - Inactive
        private static Bitmap Inactive_Default = Resources.X_Button_Disabled;
        private static Bitmap Inactive_Hovering = Resources.X_Button_Disabled;
        private static Bitmap Inactive_Pressing = Resources.X_Button_Disabled;
        private static EventsBitmaps Inactive_Bitmaps;
        //////////////////////////////////////////////////////////// - Error
        private static Bitmap Error_Default = Resources.X_Button_Disabled;
        private static Bitmap Error_Hovering = Resources.X_Button_Disabled;
        private static Bitmap Error_Pressing = Resources.X_Button_Disabled;
        private static EventsBitmaps Error_Bitmaps;

        private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
        //////////////////////////////////////////////////////////// - Warning
        private static Bitmap Warning_Default = Resources.X_Button_Warning_Empty;
        private static Bitmap Warning_Hovering = Resources.X_Button_Warning_Empty;
        private static Bitmap Warning_Pressing = Resources.X_Button_Warning_Filled;
        private static EventsBitmaps Warning_Bitmaps;
        ////////////////////////////////////////////////////////////
        private static StatesBitmaps statesBitmaps;
        private static StatesColors statesColors;

        public static StatesColors GetStatesColors()
        {
            statesColors = new StatesColors(Default, Active, Red, Red, Default, Default);
            return (statesColors);
        }

        public static StatesBitmaps GetStatesBitmaps()
        {
            Loading_Bitmaps = new EventsBitmaps(Loading_Default, Loading_Hovering, Loading_Pressing);
            Active_Bitmaps = new EventsBitmaps(Active_Default, Active_Hovering, Active_Pressing);
            Disabled_Bitmaps = new EventsBitmaps(Disabled_Default, Disabled_Hovering, Disabled_Pressing);
            Error_Bitmaps = new EventsBitmaps(Error_Default, Error_Hovering, Error_Pressing);
            Warning_Bitmaps = new EventsBitmaps(Warning_Default, Warning_Hovering, Warning_Pressing);
            Inactive_Bitmaps = new EventsBitmaps(Inactive_Default, Inactive_Hovering, Inactive_Pressing);

            statesBitmaps = new StatesBitmaps(Disabled_Bitmaps, Active_Bitmaps, Error_Bitmaps, Warning_Bitmaps, Loading_Bitmaps, Inactive_Bitmaps);

            return (statesBitmaps);
        }
    }
}
