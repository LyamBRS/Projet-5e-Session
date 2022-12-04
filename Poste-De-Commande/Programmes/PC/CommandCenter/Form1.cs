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
using System.IO.Ports;

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
            StatesColors OverviewColors = new StatesColors(Panel_Overview.BackColor);
            //----------------------------------------------------------
            BRS.Debug.Comment("Initializing BRS's Dynamic Buttons Bitmaps and colors...");
            #region Universal
            CommandCenter.Buttons.Mode = new GenericButton(Button_Mode, Icons.Power.GetStatesColors(), Icons.Power.GetStatesBitmaps());
            CommandCenter.Buttons.USB = new GenericButton(Button_USB, Icons.Power.GetStatesColors(), Icons.USB.GetStatesBitmaps());
            #endregion Universal
            #region Index_Settings
            CommandCenter.Buttons.Link = new GenericButton(Button_Link, Icons.Link.GetStatesColors(), Icons.Link.GetStatesBitmaps());
            CommandCenter.Buttons.AutoConnection = new GenericButton(Button_AutoConnect, Icons.CheckBox.GetStatesColors(), Icons.CheckBox.GetStatesBitmaps());
            #endregion Index_Settings
            #region Index_Terminal
            CommandCenter.Buttons.Terminal = new GenericButton(Button_Terminal, Icons.Terminal.GetStatesColors(), Icons.Terminal.GetStatesBitmaps());
            CommandCenter.Buttons.CloseBeagle = new GenericButton(Button_CloseBeagleBone, Icons.X.GetStatesColors(), Icons.X.GetStatesBitmaps());
            CommandCenter.Buttons.SaveBBBTerminal = new GenericButton(Button_Save_Terminal, Icons.Save.GetStatesColors(), Icons.Save.GetStatesBitmaps());

            #endregion Index_Terminal
            #region Index_Operation
            CommandCenter.Operation.Buttons.ClearTerminal = new GenericButton(Operation_Terminal_Clear, Icons.Terminal.GetStatesColors(), Icons.Terminal.GetStatesBitmaps());
            CommandCenter.Operation.Buttons.SaveOperationTerminal = new GenericButton(Operation_Save_Logs, Icons.Save.GetStatesColors(), Icons.Save.GetStatesBitmaps());

            CommandCenter.Operation.Buttons.EmergencyStop = new GenericButton(Operation_EmergencyStop, Icons.Emergency.GetStatesColors(), Icons.Emergency.GetStatesBitmaps());
            CommandCenter.Operation.Buttons.Global = new GenericButton(Operation_Module_Global, Icons.EveryModules.GetStatesColors(), Icons.EveryModules.GetStatesBitmaps());
            CommandCenter.Operation.Buttons.Pause = new GenericButton(Operation_Pause, Icons.Paused.GetStatesColors(), Icons.Paused.GetStatesBitmaps());
            CommandCenter.Operation.Buttons.Vehicle = new GenericButton(Operation_Module_Vehicle, Icons.Vehicle.GetStatesColors(), Icons.Vehicle.GetStatesBitmaps());
            CommandCenter.Operation.Buttons.WeightStation = new GenericButton(Operation_Module_WeightStation, Icons.Balance.GetStatesColors(), Icons.Balance.GetStatesBitmaps());
            CommandCenter.Operation.Buttons.SortingStation = new GenericButton(Operation_Module_SortingStation, Icons.Sorting.GetStatesColors(), Icons.Sorting.GetStatesBitmaps());

            CommandCenter.Operation.Overview.Vehicle = new GenericButton(Overview_Vehicle, OverviewColors, Icons.Vehicle.GetStatesBitmaps());
            CommandCenter.Operation.Overview.WeightStation = new GenericButton(Overview_WeightStation, OverviewColors, Icons.Balance.GetStatesBitmaps());
            CommandCenter.Operation.Overview.SortingStation = new GenericButton(Overview_SortingStation, OverviewColors, Icons.Sorting.GetStatesBitmaps());
            #endregion Index_Operation
            Debug.Success("");
            //----------------------------------------------------------
            BRS.Debug.Comment("Toggeling Dynamic Buttons animations states...");
            #region Universal
            CommandCenter.Buttons.Mode.Animated = true;
            CommandCenter.Buttons.USB.Animated = true;
            #endregion Universal
            #region Index_Settings
            CommandCenter.Buttons.Link.Animated = true;
            CommandCenter.Buttons.AutoConnection.Animated = true;
            #endregion Index_Settings
            #region Index_Terminal
            CommandCenter.Buttons.Terminal.Animated = true;
            CommandCenter.Buttons.CloseBeagle.Animated = true;
            CommandCenter.Buttons.SaveBBBTerminal.Animated = true;
            #endregion Index_Terminal
            #region Index_Operation
            CommandCenter.Operation.Buttons.ClearTerminal.Animated = true;

            CommandCenter.Operation.Buttons.EmergencyStop.Animated = true;
            CommandCenter.Operation.Buttons.Global.Animated = true;
            CommandCenter.Operation.Buttons.Pause.Animated = true;
            CommandCenter.Operation.Buttons.Vehicle.Animated = true;
            CommandCenter.Operation.Buttons.WeightStation.Animated = true;
            CommandCenter.Operation.Buttons.SortingStation.Animated = true;
            CommandCenter.Operation.Buttons.SaveOperationTerminal.Animated = true;
            /*
            CommandCenter.Operation.Buttons.EmergencyStop.SizeMultiplier_MouseHover = 1;
            CommandCenter.Operation.Buttons.Global.SizeMultiplier_MouseHover = 1;
            CommandCenter.Operation.Buttons.Pause.SizeMultiplier_MouseHover = 1;
            CommandCenter.Operation.Buttons.Vehicle.SizeMultiplier_MouseHover = 1;
            CommandCenter.Operation.Buttons.WeightStation.SizeMultiplier_MouseHover = 1;
            CommandCenter.Operation.Buttons.SortingStation.SizeMultiplier_MouseHover = 1;
            */
            CommandCenter.Operation.Overview.Vehicle.Colors.Inactive.SetAll(Panel_Overview.BackColor);

            CommandCenter.Operation.Overview.Vehicle.Animated = false;
            CommandCenter.Operation.Overview.WeightStation.Animated = false;
            CommandCenter.Operation.Overview.SortingStation.Animated = false;
            #endregion Index_Operation
            Debug.Success("");
            //----------------------------------------------------------
            BRS.Debug.Comment("Setting Dynamic buttons initial values...");
            #region Universal
            CommandCenter.Buttons.Mode.State = ControlState.Inactive;
            CommandCenter.Buttons.USB.State = ControlState.Inactive;
            #endregion Universal
            #region Index_Settings
            CommandCenter.Buttons.Link.State = ControlState.Inactive;
            CommandCenter.Buttons.AutoConnection.State = ControlState.Inactive;
            #endregion Index_Settings
            #region Index_Terminal
            CommandCenter.Buttons.Terminal.State = ControlState.Inactive;
            CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
            CommandCenter.Buttons.SaveBBBTerminal.State = ControlState.Inactive;
            #endregion Index_Terminal
            #region Index_Operation
            CommandCenter.Operation.Buttons.ClearTerminal.State              = ControlState.Inactive;
                                                                            
            CommandCenter.Operation.Buttons.EmergencyStop.State              = ControlState.Disabled;
            CommandCenter.Operation.Buttons.Global.State                     = ControlState.Inactive;
            CommandCenter.Operation.Buttons.Pause.State                      = ControlState.Disabled;
            CommandCenter.Operation.Buttons.Vehicle.State                    = ControlState.Inactive;
            CommandCenter.Operation.Buttons.WeightStation.State              = ControlState.Inactive;
            CommandCenter.Operation.Buttons.SortingStation.State             = ControlState.Inactive;
            CommandCenter.Operation.Buttons.SaveOperationTerminal.State      = ControlState.Inactive;

            CommandCenter.Operation.Overview.Vehicle.State                   = ControlState.Inactive;
            CommandCenter.Operation.Overview.WeightStation.State             = ControlState.Inactive;
            CommandCenter.Operation.Overview.SortingStation.State            = ControlState.Inactive;
            #endregion Index_Operation
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
            #region Settings
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
            #endregion Settings
            /////////////////////////////////////////////////////////////
            #region Terminal
            BRS.Debug.Comment("Setting up terminal functions...");
            CommandCenter.terminal = new Terminal(ConsoleArea, this, BRS.ComPort.Port);
            CommandCenter.terminal.Window = ConsoleArea;
            CommandCenter.terminal.ShowTX = true;

            OperationLogs.Window = new Terminal(Operation_Logs, this);
            OperationLogs.Window.ShowTX = false;

            OperationLogs.Window.SavingFolder = "Operation";
            CommandCenter.terminal.SavingFolder = "BeagleBone";
            
            BRS.ComPort.createInfoReceivedEvent();
            BRS.ComPort.DataReceivedAction = CommandCenter.terminal.DataReceiverHandling;
            Debug.Success();
            #endregion Terminal
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
        //#############################################################// 
        /// <summary>
        /// Show the user which mode we are currently in.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################// 
        private void Button_Mode_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Displaying which mode the command center is currently in...");

            if (MasterProtocol.isActive)
            {
                switch (MasterProtocol.mode)
                {
                    case (0x00):
                        NewUserTextInfo(UserInfos.Modes.IsEmergency, 2);
                        break;
                    case (0x01):
                        NewUserTextInfo(UserInfos.Modes.IsPaused, 2);
                        break;
                    case (0x02):
                        NewUserTextInfo(UserInfos.Modes.IsTesting, 2);
                        break;
                    case (0x03):
                        NewUserTextInfo(UserInfos.Modes.IsMaintenance, 2);
                        break;
                    case (0x04):
                        NewUserTextInfo(UserInfos.Modes.IsOperating, 2);
                        break;
                    case (0x05):
                        NewUserTextInfo(UserInfos.Modes.IsCalibrating, 2);
                        break;
                    case (0x06):
                        NewUserTextInfo(UserInfos.Modes.IsInitialising, 2);
                        break;
                }
            }
            else
            {
                if(BRS.ComPort.Port.IsOpen)
                {
                    NewUserTextInfo(UserInfos.MasterProtocol.IsWaitingForBBB, 2);
                }
                else
                {
                    NewUserTextInfo(UserInfos.ComPort.IsOffline, 2);
                }
            }

            BRS.Debug.Header(false);
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
            public static GenericButton SaveBBBTerminal;
        }
        /// <summary>
        /// Class containing all the buttons specific to the
        /// Operation Tab
        /// </summary>
        public class Operation
        {
            public class Buttons
            {
                public static GenericButton Global;
                public static GenericButton Vehicle;
                public static GenericButton SortingStation;
                public static GenericButton WeightStation;
                public static GenericButton Pause;
                public static GenericButton EmergencyStop;
                public static GenericButton ClearTerminal;
                public static GenericButton SaveOperationTerminal;
            }
            /// <summary>
            /// Overview of operation process indicators buttons stuff
            /// </summary>
            public class Overview
            {
                public static GenericButton Vehicle;
                public static GenericButton SortingStation;
                public static GenericButton WeightStation;
            }
        }

        public static RichTextBox tempo;
        /// <summary>
        /// The command center's terminal.
        /// </summary>
        public static Terminal terminal;
    }
}
