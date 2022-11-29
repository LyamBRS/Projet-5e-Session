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
            //FormConsoleRef = this;
            Debug.Success();           
            /////////////////////////////////////////////////////////////
            #region DynamicButtons
            //----------------------------------------------------------
            BRS.Debug.Comment("Initializing BRS's Dynamic Buttons Bitmaps and colors...");
            CommandCenter.Buttons.Mode = new GenericButton(Button_Mode, Power_Icons.GetStatesColors(), Power_Icons.GetStatesBitmaps());
            CommandCenter.Buttons.USB = new GenericButton(Button_USB, USB_Icons.GetStatesColors(), USB_Icons.GetStatesBitmaps());
            CommandCenter.Buttons.Link = new GenericButton(Button_Link, Link_Icons.GetStatesColors(), Link_Icons.GetStatesBitmaps());
            CommandCenter.Buttons.Terminal = new GenericButton(Button_Terminal, Terminal_Icons.GetStatesColors(), Terminal_Icons.GetStatesBitmaps());
            CommandCenter.Buttons.AutoConnection = new GenericButton(Button_AutoConnect, CheckBox_Icons.GetStatesColors(), CheckBox_Icons.GetStatesBitmaps());
            CommandCenter.Buttons.CloseBeagle = new GenericButton(Button_CloseBeagleBone, X_Icons.GetStatesColors(), X_Icons.GetStatesBitmaps());
            Debug.Success("");
            //----------------------------------------------------------
            BRS.Debug.Comment("Toggeling Dynamic Buttons animations states...");
            CommandCenter.Buttons.Mode.Animated = true;
            CommandCenter.Buttons.USB.Animated = true;
            CommandCenter.Buttons.Link.Animated = true;
            CommandCenter.Buttons.Terminal.Animated = true;
            CommandCenter.Buttons.AutoConnection.Animated = true;
            CommandCenter.Buttons.CloseBeagle.Animated = true;
            Debug.Success("");
            //----------------------------------------------------------
            BRS.Debug.Comment("Setting Dynamic buttons initial values...");
            CommandCenter.Buttons.Mode.State = ControlState.Inactive;
            CommandCenter.Buttons.USB.State = ControlState.Inactive;
            CommandCenter.Buttons.Link.State = ControlState.Inactive;
            CommandCenter.Buttons.Terminal.State = ControlState.Inactive;
            CommandCenter.Buttons.AutoConnection.State = ControlState.Inactive;
            CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
            Debug.Success("");
            #endregion DynamicButtons
            /////////////////////////////////////////////////////////////
            BRS.Debug.Comment("Specifying RX callbacks and events of BRS.ComPort");
            BRS.ComPort.startPortUpdater();
            BRS.Debug.Comment("Setting port to UTF8...");
            BRS.ComPort.Port.Encoding = Encoding.UTF8;
            Debug.Success();
            //----------------------------------------------------------
            /////////////////////////////////////////////////////////////
            //----------------------------------------------------------
            BRS.Debug.Comment("Initialising UART list...");
            BRS.ComPort.ListOfPortChanged.CollectionChanged += ListChanged;
            BRS.ComPort.StoreAllAvailableComs();
            OldSettings = BRS.ComPort.Port;
            Debug.Success();
            /////////////////////////////////////////////////////////////
            BRS.Debug.Comment("Initialising setting boxes for UART");
            InnitComDropDown();
            InnitBaudRateBox();
            InnitStopBit();
            InnitParity();
            InnitFlowControl();
            InnitDataBit();
            Debug.Success();
            /////////////////////////////////////////////////////////////
            BRS.Debug.Comment("Starting timers...");
            UpdatePortList.Enabled = true;
            Debug.Success();
            /////////////////////////////////////////////////////////////
            BRS.Debug.Comment("Loading saved settings...");
            Settings.formSettings = this;
            Settings.LoadSettings();

            BaudRateBox.Text = Settings.BaudRate();
            DataBitBox.Text = Settings.DataBits();
            ParityBox.Text = Settings.Parity();
            StopBitBox.Text = Settings.StopBits();
            FlowControlBox.Text = Settings.Flow();
            RXTimeOutBox.Text = Settings.TimeOut_RX();
            TXTimeOutBox.Text = Settings.TimeOut_TX();

            BeagleBone_User.Text = Settings.BeagleBone_User();
            BeagleBone_Password.Text = Settings.BeagleBone_Password();
            BeagleBone_FileName.Text = Settings.BeagleBone_FileName();
            BeagleBone_FilePath.Text = Settings.BeagleBone_FilePath();

            DropDown_ScaleUnit.Text = Settings.Scale_Unit();

            CommandCenter.Buttons.AutoConnection.State = (Settings.BeagleBone_AutoConnect().Equals("True") ? ControlState.Active : ControlState.Inactive);
            AutoConnect = (Settings.BeagleBone_AutoConnect().Equals("True") ? true : false);
            Debug.Success();

            BRS.Debug.Comment("Setting up terminal functions...");
            CommandCenter.terminal = new Terminal(ConsoleArea, this, BRS.ComPort.Port);
            CommandCenter.terminal.Window = ConsoleArea;

            BRS.ComPort.createInfoReceivedEvent();
            BRS.ComPort.DataReceivedAction = CommandCenter.terminal.DataReceiverHandling;
            Debug.Success();

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
            Debug.LocalStart(false);
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
            Debug.LocalEnd();
        }

        private void button1_Click(object sender, EventArgs e)
        {

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
            public static BRS.Buttons.GenericButton AutoConnection;
            public static BRS.Buttons.GenericButton CloseBeagle;
        }

        public static RichTextBox tempo;
        /// <summary>
        /// The command center's terminal.
        /// </summary>
        public static Terminal terminal;
    }
}
