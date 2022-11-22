using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using BRS;
using BRS.Buttons;

namespace CommandCenter
{
    public partial class Form_MainMenu : Form
    {
        public int HasStartedResize = 0;
        //#############################################################//
        /// <summary>
        /// Constructor for the Command Center's Form.
        /// </summary>
        //#############################################################//
        public Form_MainMenu()
        {
            BRS.Debug.Header(true);
            /////////////////////////////////////////////////////////////
            BRS.Debug.Comment("Initializing the command center's components...");
            InitializeComponent();
            FormConsoleRef = this;
            Debug.Success("");
            /////////////////////////////////////////////////////////////
            #region DynamicButtons
            //----------------------------------------------------------
            BRS.Debug.Comment("Initializing BRS's Dynamic Buttons Bitmaps and colors...");
            CommandCenter.Buttons.Mode = new GenericButton(Button_Mode, Power_Icons.GetStatesColors(), Power_Icons.GetStatesBitmaps());
            CommandCenter.Buttons.USB = new GenericButton(Button_USB, USB_Icons.GetStatesColors(), USB_Icons.GetStatesBitmaps());
            CommandCenter.Buttons.Link = new GenericButton(Button_Link, Link_Icons.GetStatesColors(), Link_Icons.GetStatesBitmaps());
            CommandCenter.Buttons.Terminal = new GenericButton(Button_Terminal, Terminal_Icons.GetStatesColors(), Terminal_Icons.GetStatesBitmaps());
            Debug.Success("");
            //----------------------------------------------------------
            BRS.Debug.Comment("Toggeling Dynamic Buttons animations states...");
            CommandCenter.Buttons.Mode.Animated = true;
            CommandCenter.Buttons.USB.Animated = true;
            CommandCenter.Buttons.Link.Animated = true;
            CommandCenter.Buttons.Terminal.Animated = true;
            Debug.Success("");
            //----------------------------------------------------------
            BRS.Debug.Comment("Setting Dynamic buttons initial values...");
            CommandCenter.Buttons.Mode.State = ControlState.Inactive;
            CommandCenter.Buttons.USB.State = ControlState.Inactive;
            CommandCenter.Buttons.Link.State = ControlState.Inactive;
            CommandCenter.Buttons.Terminal.State = ControlState.Inactive;
            Debug.Success("");
            #endregion DynamicButtons
            /////////////////////////////////////////////////////////////
            BRS.Debug.Comment("Specifying RX callbacks and events of BRS.ComPort");
            BRS.ComPort.createInfoReceivedEvent();
            BRS.ComPort.DataReceivedAction = DataReceiverHandling;
            BRS.ComPort.startPortUpdater();
            Debug.Success("");
            //----------------------------------------------------------
            /////////////////////////////////////////////////////////////
            BRS.Debug.Comment("Creating delegate for RX data received event...");
            Delegate = new dlgThread(RXConsoleText);
            Debug.Success("");
            //----------------------------------------------------------
            BRS.Debug.Comment("Initialising UART list...");
            BRS.ComPort.ListOfPortChanged.CollectionChanged += ListChanged;
            BRS.ComPort.StoreAllAvailableComs();
            OldSettings = BRS.ComPort.Port;
            Debug.Success("");
            /////////////////////////////////////////////////////////////
            BRS.Debug.Comment("Initialising setting boxes for UART");
            InnitComDropDown();
            InnitBaudRateBox();
            InnitStopBit();
            InnitParity();
            InnitFlowControl();
            InnitDataBit();
            Debug.Success("");
            /////////////////////////////////////////////////////////////
            BRS.Debug.Comment("Starting timers...");
            UpdatePortList.Enabled = true;
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// changes the programmer's global text with the specified one
        /// 0: normal, 1: Green, 2: red, 3: warning orange
        /// </summary>
        /// <param name="info"></param>
        /// <param name="style"></param>
        //#############################################################// 
        private void NewUserTextInfo(string info, int style)
        {
            BRS.Debug.Comment("Changing user header info...");
            switch (style)
            {
                case 0: UserInfo.ForeColor = Color.FromArgb(100, 100, 100); break; // Neutral
                case 1: UserInfo.ForeColor = Color.FromArgb(60, 255, 60); break; // Good!
                case 2: UserInfo.ForeColor = Color.FromArgb(255, 60, 60); break; // Bad
                case 3: UserInfo.ForeColor = Color.FromArgb(255, 125, 60); break; // Attempting
            }

            UserInfo.Text = info;
            Debug.Success("");
        }
    }

    //#############################################################//
    /// <summary>
    /// Class made to access BRS Dynamic buttons accross multiple
    /// files.
    /// </summary>
    //#############################################################//
    public class CommandCenter
    {
        /// <summary>
        /// All the BRS dynamic buttons used in this project
        /// can be refered to within this class.
        /// </summary>
        public class Buttons
        {
            public static BRS.Buttons.GenericButton Mode;
            public static BRS.Buttons.GenericButton USB;
            public static BRS.Buttons.GenericButton Link;
            public static BRS.Buttons.GenericButton Terminal;
        }
    }
}
