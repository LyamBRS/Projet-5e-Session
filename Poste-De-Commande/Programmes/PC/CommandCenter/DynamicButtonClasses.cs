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
    public class Icons
    {
        //#############################################################//
        /// <summary>
        /// Class containing all the pngs used to display a USB button.
        /// </summary>
        //#############################################################//
        public class USB
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
        /// Class containing all the pngs used to display a power button.
        /// </summary>
        //#############################################################//
        public class Power
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
        public class Link
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
        public class Terminal
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
        public class CheckBox
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default = Resources.CheckBox_Available_Empty;
            private static Bitmap Active_Hovering = Resources.CheckBox_Available_Empty;
            private static Bitmap Active_Pressing = Resources.CheckBox_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default = Resources.CheckBox_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.CheckBox_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.CheckBox_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default = Resources.CheckBox_Inactive_Empty;
            private static Bitmap Inactive_Hovering = Resources.CheckBox_Inactive_Empty;
            private static Bitmap Inactive_Pressing = Resources.CheckBox_Inactive_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default = Resources.CheckBox_Error_Empty;
            private static Bitmap Error_Hovering = Resources.CheckBox_Error_Empty;
            private static Bitmap Error_Pressing = Resources.CheckBox_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default = Resources.CheckBox_Warning_Empty;
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
        public class X
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
        //#############################################################//
        /// <summary>
        /// Class containing all the pngs used to display an Operation button.
        /// </summary>
        //#############################################################//
        #region Modes
        public class Operation
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default = Resources.Operation_Available_Empty;
            private static Bitmap Active_Hovering = Resources.Operation_Available_Empty;
            private static Bitmap Active_Pressing = Resources.Operation_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default = Resources.Operation_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.Operation_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.Operation_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default = Resources.Operation_Disabled_Empty;
            private static Bitmap Inactive_Hovering = Resources.Operation_Disabled_Empty;
            private static Bitmap Inactive_Pressing = Resources.Operation_Disabled_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default = Resources.Operation_Error_Empty;
            private static Bitmap Error_Hovering = Resources.Operation_Error_Empty;
            private static Bitmap Error_Pressing = Resources.Operation_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default = Resources.Operation_Warning_Empty;
            private static Bitmap Warning_Hovering = Resources.Operation_Warning_Empty;
            private static Bitmap Warning_Pressing = Resources.Operation_Warning_Filled;
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
        /// Class containing all the pngs used to display a tech button.
        /// </summary>
        //#############################################################//
        public class Tech
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default = Resources.Tech_Available_Empty;
            private static Bitmap Active_Hovering = Resources.Tech_Available_Empty;
            private static Bitmap Active_Pressing = Resources.Tech_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default = Resources.Tech_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.Tech_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.Tech_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default = Resources.Tech_Disabled_Empty;
            private static Bitmap Inactive_Hovering = Resources.Tech_Disabled_Empty;
            private static Bitmap Inactive_Pressing = Resources.Tech_Disabled_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default = Resources.Tech_Error_Empty;
            private static Bitmap Error_Hovering = Resources.Tech_Error_Empty;
            private static Bitmap Error_Pressing = Resources.Tech_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default = Resources.Tech_Warning_Empty;
            private static Bitmap Warning_Hovering = Resources.Tech_Warning_Empty;
            private static Bitmap Warning_Pressing = Resources.Tech_Warning_Filled;
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
        /// Class containing all the pngs used to display a Maintnance button.
        /// </summary>
        //#############################################################//
        public class Maintenance
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default = Resources.Maintenance_Available_Empty;
            private static Bitmap Active_Hovering = Resources.Maintenance_Available_Empty;
            private static Bitmap Active_Pressing = Resources.Maintenance_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default = Resources.Maintenance_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.Maintenance_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.Maintenance_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default = Resources.Maintenance_Disabled_Empty;
            private static Bitmap Inactive_Hovering = Resources.Maintenance_Disabled_Empty;
            private static Bitmap Inactive_Pressing = Resources.Maintenance_Disabled_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default = Resources.Maintenance_Error_Empty;
            private static Bitmap Error_Hovering = Resources.Maintenance_Error_Empty;
            private static Bitmap Error_Pressing = Resources.Maintenance_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default = Resources.Maintenance_Warning_Empty;
            private static Bitmap Warning_Hovering = Resources.Maintenance_Warning_Empty;
            private static Bitmap Warning_Pressing = Resources.Maintenance_Warning_Filled;
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
        /// Class containing all the pngs used to display a Calibration button.
        /// </summary>
        //#############################################################//
        public class Calibration
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default  = Resources.Calibration_Available_Empty;
            private static Bitmap Active_Hovering = Resources.Calibration_Available_Empty;
            private static Bitmap Active_Pressing = Resources.Calibration_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default  = Resources.Calibration_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.Calibration_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.Calibration_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default  = Resources.Calibration_Disabled_Empty;
            private static Bitmap Inactive_Hovering = Resources.Calibration_Disabled_Empty;
            private static Bitmap Inactive_Pressing = Resources.Calibration_Disabled_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default  = Resources.Calibration_Error_Empty;
            private static Bitmap Error_Hovering = Resources.Calibration_Error_Empty;
            private static Bitmap Error_Pressing = Resources.Calibration_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default  = Resources.Calibration_Warning_Empty;
            private static Bitmap Warning_Hovering = Resources.Calibration_Warning_Empty;
            private static Bitmap Warning_Pressing = Resources.Calibration_Warning_Filled;
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
        /// Class containing all the pngs used to display a Pause button.
        /// </summary>
        //#############################################################//
        public class Paused
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default  = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default  = Resources.Paused_Available_Empty;
            private static Bitmap Active_Hovering = Resources.Paused_Available_Empty;
            private static Bitmap Active_Pressing = Resources.Paused_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default  = Resources.Paused_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.Paused_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.Paused_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default  = Resources.Paused_Disabled_Empty;
            private static Bitmap Inactive_Hovering = Resources.Paused_Disabled_Empty;
            private static Bitmap Inactive_Pressing = Resources.Paused_Disabled_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default  = Resources.Paused_Error_Empty;
            private static Bitmap Error_Hovering = Resources.CheckBox_Error_Empty;
            private static Bitmap Error_Pressing = Resources.CheckBox_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default  = Resources.Paused_Warning_Empty;
            private static Bitmap Warning_Hovering = Resources.Paused_Warning_Empty;
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
        /// Class containing all the pngs used to display a Play button.
        /// </summary>
        //#############################################################//
        public class Play
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default = Resources.Play_Available_Empty;
            private static Bitmap Active_Hovering = Resources.Play_Available_Empty;
            private static Bitmap Active_Pressing = Resources.Play_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default = Resources.Play_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.Play_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.Play_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default = Resources.Play_Inactive_Empty;
            private static Bitmap Inactive_Hovering = Resources.Play_Inactive_Empty;
            private static Bitmap Inactive_Pressing = Resources.Play_Inactive_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default = Resources.Play_Error_Empty;
            private static Bitmap Error_Hovering = Resources.CheckBox_Error_Empty;
            private static Bitmap Error_Pressing = Resources.CheckBox_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default = Resources.Play_Warning_Empty;
            private static Bitmap Warning_Hovering = Resources.Play_Warning_Empty;
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
        /// Class containing all the pngs used to display an EmergencyMode button.
        /// </summary>
        //#############################################################//
        public class Emergency
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default  = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default  = Resources.Warning_Available_Empty;
            private static Bitmap Active_Hovering = Resources.Warning_Available_Empty;
            private static Bitmap Active_Pressing = Resources.Warning_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default  = Resources.Warning_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.Warning_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.Warning_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default  = Resources.Warning_Inactive_Empty;
            private static Bitmap Inactive_Hovering = Resources.Warning_Inactive_Empty;
            private static Bitmap Inactive_Pressing = Resources.Warning_Inactive_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default  = Resources.Warning_Error_Empty;
            private static Bitmap Error_Hovering = Resources.Warning_Error_Empty;
            private static Bitmap Error_Pressing = Resources.Warning_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default  = Resources.Warning_Warning_Empty;
            private static Bitmap Warning_Hovering = Resources.Warning_Warning_Empty;
            private static Bitmap Warning_Pressing = Resources.Warning_Warning_Filled;
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
        #endregion Modes
        #region Modules
        //#############################################################//
        /// <summary>
        /// Class containing all the pngs used to display a Vehicle button.
        /// </summary>
        //#############################################################//
        public class Vehicle
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default  = Resources.Vehicle_Available_Empty;
            private static Bitmap Active_Hovering = Resources.Vehicle_Available_Empty;
            private static Bitmap Active_Pressing = Resources.Vehicle_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default  = Resources.Vehicle_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.Vehicle_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.Vehicle_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default  = Resources.Vehicle_Disabled_Empty;
            private static Bitmap Inactive_Hovering = Resources.Vehicle_Disabled_Empty;
            private static Bitmap Inactive_Pressing = Resources.Vehicle_Disabled_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default  = Resources.Vehicle_Error_Empty;
            private static Bitmap Error_Hovering = Resources.Vehicle_Error_Empty;
            private static Bitmap Error_Pressing = Resources.Vehicle_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default  = Resources.Vehicle_Warning_Empty;
            private static Bitmap Warning_Hovering = Resources.Vehicle_Warning_Empty;
            private static Bitmap Warning_Pressing = Resources.Vehicle_Warning_Filled;
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
        /// Class containing all the pngs used to display a Vehicle button.
        /// </summary>
        //#############################################################//
        public class Balance
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default  = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default  = Resources.Balance_Available_Empty;
            private static Bitmap Active_Hovering = Resources.Balance_Available_Empty;
            private static Bitmap Active_Pressing = Resources.Balance_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default  = Resources.Balance_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.Balance_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.Balance_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default  = Resources.Balance_Disabled_Empty;
            private static Bitmap Inactive_Hovering = Resources.Balance_Disabled_Empty;
            private static Bitmap Inactive_Pressing = Resources.Balance_Disabled_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default  = Resources.Balance_Error_Empty;
            private static Bitmap Error_Hovering = Resources.Balance_Error_Empty;
            private static Bitmap Error_Pressing = Resources.Balance_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default  = Resources.Balance_Warning_Empty;
            private static Bitmap Warning_Hovering = Resources.Balance_Warning_Empty;
            private static Bitmap Warning_Pressing = Resources.Balance_Warning_Filled;
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
        /// Class containing all the pngs used to display a Sorting station button.
        /// </summary>
        //#############################################################//
        public class Sorting
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default  = Resources.Sorting_Available_Empty;
            private static Bitmap Active_Hovering = Resources.Sorting_Available_Empty;
            private static Bitmap Active_Pressing = Resources.Sorting_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default  = Resources.Sorting_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.Sorting_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.Sorting_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default  = Resources.Sorting_Disabled_Empty;
            private static Bitmap Inactive_Hovering = Resources.Sorting_Disabled_Empty;
            private static Bitmap Inactive_Pressing = Resources.Sorting_Disabled_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default  = Resources.Sorting_Error_Empty;
            private static Bitmap Error_Hovering = Resources.Sorting_Error_Empty;
            private static Bitmap Error_Pressing = Resources.Sorting_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default  = Resources.Sorting_Warning_Empty;
            private static Bitmap Warning_Hovering = Resources.Sorting_Warning_Empty;
            private static Bitmap Warning_Pressing = Resources.Sorting_Warning_Filled;
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
        /// Class containing all the pngs used to display a Sorting station button.
        /// </summary>
        //#############################################################//
        public class EveryModules
        {
            /////////////////////////////////////////////////////////////
            private static EventsColors Default = new EventsColors(Color.Black);

            //////////////////////////////////////////////////////////// - LOADING
            private static Bitmap Loading_Default = Resources.Generic_Loading;
            private static Bitmap Loading_Hovering = Resources.Generic_Loading;
            private static Bitmap Loading_Pressing = Resources.Generic_Loading;
            private static EventsBitmaps Loading_Bitmaps;

            //////////////////////////////////////////////////////////// - ACTIVE (DOWNLOAD)
            private static Bitmap Active_Default  = Resources.Global_Available_Empty;
            private static Bitmap Active_Hovering = Resources.Global_Available_Empty;
            private static Bitmap Active_Pressing = Resources.Global_Available_Filled;
            private static EventsBitmaps Active_Bitmaps;

            private static EventsColors Active = new EventsColors(Color.Black, Color.Black, Color.FromArgb(0, 128, 255));
            //////////////////////////////////////////////////////////// - Disabled
            private static Bitmap Disabled_Default  = Resources.Global_Disabled_Empty;
            private static Bitmap Disabled_Hovering = Resources.Global_Disabled_Empty;
            private static Bitmap Disabled_Pressing = Resources.Global_Disabled_Filled;
            private static EventsBitmaps Disabled_Bitmaps;
            //////////////////////////////////////////////////////////// - Inactive
            private static Bitmap Inactive_Default  = Resources.Global_Disabled_Empty;
            private static Bitmap Inactive_Hovering = Resources.Global_Disabled_Empty;
            private static Bitmap Inactive_Pressing = Resources.Global_Disabled_Filled;
            private static EventsBitmaps Inactive_Bitmaps;
            //////////////////////////////////////////////////////////// - Error
            private static Bitmap Error_Default  = Resources.Global_Error_Empty;
            private static Bitmap Error_Hovering = Resources.Global_Error_Empty;
            private static Bitmap Error_Pressing = Resources.Global_Error_Filled;
            private static EventsBitmaps Error_Bitmaps;

            private static EventsColors Red = new EventsColors(Color.Black, Color.Black, Color.FromArgb(255, 64, 0));
            //////////////////////////////////////////////////////////// - Warning
            private static Bitmap Warning_Default  = Resources.Global_Warning_Empty;
            private static Bitmap Warning_Hovering = Resources.Global_Warning_Empty;
            private static Bitmap Warning_Pressing = Resources.Global_Warning_Filled;
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
        #endregion Modules

    }
}
