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
            CommandCenter.Operation.Buttons.Disc = new GenericButton(Operation_Disc_Color, Icons.Disc.GetStatesColors(), Icons.Disc.GetStatesBitmaps());

            CommandCenter.Operation.Overview.Vehicle = new GenericButton(Overview_Vehicle, OverviewColors, Icons.Vehicle.GetStatesBitmaps());
            CommandCenter.Operation.Overview.WeightStation = new GenericButton(Overview_WeightStation, OverviewColors, Icons.Balance.GetStatesBitmaps());
            CommandCenter.Operation.Overview.SortingStation = new GenericButton(Overview_SortingStation, OverviewColors, Icons.Sorting.GetStatesBitmaps());
            #endregion Index_Operation
            #region Index_Calibration
            CommandCenter.Calibration.Buttons.Calibration = new GenericButton(Calibration_Button_StartStop, Icons.Calibration.GetStatesColors(), Icons.Calibration.GetStatesBitmaps());
            CommandCenter.Calibration.Buttons.Global = new GenericButton(Calibration_Module_All, Icons.EveryModules.GetStatesColors(), Icons.EveryModules.GetStatesBitmaps());
            CommandCenter.Calibration.Buttons.Vehicle = new GenericButton(Calibration_Module_Vehicle, Icons.Vehicle.GetStatesColors(), Icons.Vehicle.GetStatesBitmaps());
            CommandCenter.Calibration.Buttons.WeightStation = new GenericButton(Calibration_Module_Weight, Icons.Balance.GetStatesColors(), Icons.Balance.GetStatesBitmaps());
            CommandCenter.Calibration.Buttons.SortingStation = new GenericButton(Calibration_Module_Sorting, Icons.Sorting.GetStatesColors(), Icons.Sorting.GetStatesBitmaps());
            CommandCenter.Calibration.Buttons.ClearTerminal = new GenericButton(Calibration_Clear_Logs, Icons.Terminal.GetStatesColors(), Icons.Terminal.GetStatesBitmaps());
            CommandCenter.Calibration.Buttons.SaveTerminal = new GenericButton(Calibration_Save_Logs, Icons.Save.GetStatesColors(), Icons.Save.GetStatesBitmaps());
            #endregion Index_Calibration
            #region Index_Maintenance
            CommandCenter.Maintenance.Buttons.Maintenance = new GenericButton(Maintenance_Button_StartStop, Icons.Maintenance.GetStatesColors(), Icons.Maintenance.GetStatesBitmaps());
            CommandCenter.Maintenance.Buttons.Global = new GenericButton(Maintenance_Module_All, Icons.EveryModules.GetStatesColors(), Icons.EveryModules.GetStatesBitmaps());
            CommandCenter.Maintenance.Buttons.Vehicle = new GenericButton(Maintenance_Module_Vehicle, Icons.Vehicle.GetStatesColors(), Icons.Vehicle.GetStatesBitmaps());
            CommandCenter.Maintenance.Buttons.WeightStation = new GenericButton(Maintenance_Module_Weight, Icons.Balance.GetStatesColors(), Icons.Balance.GetStatesBitmaps());
            CommandCenter.Maintenance.Buttons.SortingStation = new GenericButton(Maintenance_Module_Sorting, Icons.Sorting.GetStatesColors(), Icons.Sorting.GetStatesBitmaps());
            CommandCenter.Maintenance.Buttons.ClearTerminal = new GenericButton(Maintenance_Clear_Logs, Icons.Terminal.GetStatesColors(), Icons.Terminal.GetStatesBitmaps());
            CommandCenter.Maintenance.Buttons.SaveTerminal = new GenericButton(Maintenance_Save_Logs, Icons.Save.GetStatesColors(), Icons.Save.GetStatesBitmaps());

            #endregion Index_Maintenance
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
            CommandCenter.Operation.Buttons.Disc.Animated = true;
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
            #region Index_Calibration
            CommandCenter.Calibration.Buttons.Calibration.Animated = true;
            CommandCenter.Calibration.Buttons.Global.Animated = true;
            CommandCenter.Calibration.Buttons.Vehicle.Animated = true;
            CommandCenter.Calibration.Buttons.WeightStation.Animated = true;
            CommandCenter.Calibration.Buttons.SortingStation.Animated = true;
            CommandCenter.Calibration.Buttons.ClearTerminal.Animated = true;
            CommandCenter.Calibration.Buttons.SaveTerminal.Animated = true;
            #endregion Index_Calibration
            #region Index_Maintenance
            CommandCenter.Maintenance.Buttons.Maintenance.Animated = true;
            CommandCenter.Maintenance.Buttons.Global.Animated = true;
            CommandCenter.Maintenance.Buttons.Vehicle.Animated = true;
            CommandCenter.Maintenance.Buttons.WeightStation.Animated = true;
            CommandCenter.Maintenance.Buttons.SortingStation.Animated = true;
            CommandCenter.Maintenance.Buttons.ClearTerminal.Animated = true;
            CommandCenter.Maintenance.Buttons.SaveTerminal.Animated = true;
            #endregion Index_Maintenance
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
            CommandCenter.Operation.Buttons.Disc.State                       = ControlState.Disabled;

            CommandCenter.Operation.Overview.Vehicle.State                   = ControlState.Inactive;
            CommandCenter.Operation.Overview.WeightStation.State             = ControlState.Inactive;
            CommandCenter.Operation.Overview.SortingStation.State            = ControlState.Inactive;
            #endregion Index_Operation
            #region Index_Calibration
            CommandCenter.Calibration.Buttons.Calibration.State = ControlState.Disabled;
            CommandCenter.Calibration.Buttons.Global.State = ControlState.Disabled;
            CommandCenter.Calibration.Buttons.Vehicle.State = ControlState.Disabled;
            CommandCenter.Calibration.Buttons.WeightStation.State = ControlState.Disabled;
            CommandCenter.Calibration.Buttons.SortingStation.State = ControlState.Disabled;
            CommandCenter.Calibration.Buttons.ClearTerminal.State = ControlState.Inactive;
            CommandCenter.Calibration.Buttons.SaveTerminal.State = ControlState.Inactive;
            #endregion Index_Calibration
            #region Index_Maintenance
            CommandCenter.Maintenance.Buttons.Maintenance.State = ControlState.Disabled;
            CommandCenter.Maintenance.Buttons.Global.State = ControlState.Disabled;
            CommandCenter.Maintenance.Buttons.Vehicle.State = ControlState.Disabled;
            CommandCenter.Maintenance.Buttons.WeightStation.State = ControlState.Disabled;
            CommandCenter.Maintenance.Buttons.SortingStation.State = ControlState.Disabled;
            CommandCenter.Maintenance.Buttons.ClearTerminal.State = ControlState.Inactive;
            CommandCenter.Maintenance.Buttons.SaveTerminal.State = ControlState.Inactive;
            #endregion Index_Maintenance
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
            DropDown_Languages.Text = Settings.Language();

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

            CommandCenter.Technician.terminal = new Terminal(Technician_Logs, this);
            CommandCenter.Technician.terminal.ShowTX = false;

            CommandCenter.Calibration.terminal = new Terminal(Calibration_Logs, this);
            CommandCenter.Calibration.terminal.ShowTX = false;

            CommandCenter.Maintenance.terminal = new Terminal(Maintenance_Logs, this);
            CommandCenter.Maintenance.terminal.ShowTX = false;

            OperationLogs.Window.SavingFolder = "Operation";
            CommandCenter.terminal.SavingFolder = "BeagleBone";
            CommandCenter.Technician.terminal.SavingFolder = "Technician";
            CommandCenter.Maintenance.terminal.SavingFolder = "Maintenance";
            CommandCenter.Calibration.terminal.SavingFolder = "Calibration";

            BRS.ComPort.createInfoReceivedEvent();
            BRS.ComPort.DataReceivedAction = CommandCenter.terminal.DataReceiverHandling;
            Debug.Success();
            #endregion Terminal
            /////////////////////////////////////////////////////////////
            #region Technician
            Technician_Initialise();
            MasterProtocol.scaleUnit = DropDown_ScaleUnit.Text.Contains("Metric") ? Commands_Ref.units_Metric : Commands_Ref.units_Imperial;
            #endregion Technician


            //Initial initialisation of the previously selected language into the form as it opens
            Debug.Comment("Initialising the language used by the end user");
            if (DropDown_Languages.Text.Contains("Fr"))
            {
                Debug.Success("Selecting french");
                Languages.SetLanguageToFrench();
            }
            else
            {
                Debug.Success("Selecting english (looks better tbh)");
                Languages.SetLanguageToEnglish();
            }
            ReloadForm();
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
                case 0: UserInfo.ForeColor = ControlStateColors.Inactive; break; // Neutral
                case 1: UserInfo.ForeColor = ControlStateColors.Active; break; // Good!
                case 2: UserInfo.ForeColor = ControlStateColors.Error; break; // Bad
                case 3: UserInfo.ForeColor = ControlStateColors.Warning; break; // Attempting
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
        /// Show the user which mode we are currently in. Will be a
        /// warning color if the current mode is simulated
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################// 
        private void Button_Mode_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Displaying which mode the command center is currently in...");

            BRS.Debug.Comment("Checking if master protocol is active");
            if (MasterProtocol.isActive)
            {
                byte modeToCheck = MasterProtocol.mode;
                BRS.Debug.Comment("Checking if technician mode is active");
                if(Technician.isActive && Technician.SimulateModes)
                {
                    Debug.Success("Using simulated mode as button answer");
                    modeToCheck = Convert.ToByte(Technician.SelectedIndexes.Mode);
                }

                switch (modeToCheck)
                {
                    case (0x00):
                        NewUserTextInfo(UserInfos.Modes.IsEmergency, 1);
                        break;
                    case (0x01):
                        NewUserTextInfo(UserInfos.Modes.IsPaused, 1);
                        break;
                    case (0x02):
                        NewUserTextInfo(UserInfos.Modes.IsTesting, 1);
                        break;
                    case (0x03):
                        NewUserTextInfo(UserInfos.Modes.IsMaintenance, 1);
                        break;
                    case (0x04):
                        NewUserTextInfo(UserInfos.Modes.IsOperating, 1);
                        break;
                    case (0x05):
                        NewUserTextInfo(UserInfos.Modes.IsCalibrating, 1);
                        break;
                    case (0x06):
                        NewUserTextInfo(UserInfos.Modes.IsInitialising, 1);
                        break;

                    default:
                        NewUserTextInfo(UserInfos.Modes.DoesntExist, 2);
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


        #region SetMode
        /// <summary>
        /// Contains possible modes that you can set the command center
        /// n MasterProtocl ect to.
        /// </summary>
        public enum WantedMode
        {
            Emergency,
            Paused,
            Maintenance,
            Testing,
            Operating,
            Initialising,
            Calibrating
        }
        //#############################################################//
        /// <summary>
        /// handles all the classes you need to check and handle
        /// when you simply want to change which mode the CommandCenter
        /// is currrently in.
        /// </summary>
        /// <param name="mode"></param>
        //#############################################################//
        public bool SetGlobalModeTo(WantedMode mode)
        {
            bool worked = false;
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Parsing new wanted mode...");
            if(BRS.ComPort.Port.IsOpen)
            {
                if(MasterProtocol.isActive)
                {
                    //--------------------------------------------------// WANTS TO START OPERATIONS
                    if(mode == WantedMode.Operating)
                    {
                        if (MasterProtocol.mode != Modes_Ref.emergencyStop)
                        {
                            // already in the same mode bruh
                            if (MasterProtocol.mode == Modes_Ref.operation)
                            {
                                NewUserTextInfo(UserInfos.Modes.Already.Operating, 2);
                            }
                            else
                            {
                                if (MasterProtocol.mode == Modes_Ref.pause)
                                {
                                    NewUserTextInfo(UserInfos.Modes.OperationStarted, 1);
                                    MasterProtocol.mode = Modes_Ref.operation;
                                    MasterProtocol.error = CAN_Errors.none;
                                    MasterProtocol.state = States_Ref.operating;
                                    OperationLogs.Window.Log_header(LogsInfos.Operations.NowOperating);

                                    ModuleData_SortingStation.SetNewMode(Modes_Ref.operation);
                                    ModuleData_WeightStation.SetNewMode(Modes_Ref.operation);
                                    ModuleData_Vehicle.SetNewMode(Modes_Ref.operation);
                                    worked = true;
                                }
                                else
                                {
                                    if (PopUp.Question(PopUpInfos.ModeSwitching.IsNotPaused, PopUpInfos.Header.Warning))
                                    {
                                        NewUserTextInfo(UserInfos.Modes.OperationStarted, 1);
                                        MasterProtocol.mode = Modes_Ref.operation;
                                        MasterProtocol.error = CAN_Errors.none;
                                        MasterProtocol.state = States_Ref.processing;
                                        OperationLogs.Window.Log_header(LogsInfos.Operations.NowOperating);

                                        ModuleData_SortingStation.SetNewMode(Modes_Ref.operation);
                                        ModuleData_WeightStation.SetNewMode(Modes_Ref.operation);
                                        ModuleData_Vehicle.SetNewMode(Modes_Ref.operation);
                                        worked = true;
                                    }
                                }
                            }
                        }
                        else
                        {
                            NewUserTextInfo(UserInfos.Modes.IsEmergency, 2);
                        }
                    }
                    //--------------------------------------------------//
                    if (mode == WantedMode.Paused)
                    {
                        if(MasterProtocol.mode == Modes_Ref.pause)
                        {
                            NewUserTextInfo(UserInfos.Modes.Already.Paused, 2);
                        }
                        else
                        {
                            // Disabling emergency
                            if(MasterProtocol.mode == Modes_Ref.emergencyStop)
                            {
                                if (BRS.PopUp.Question(PopUpInfos.ModeSwitching.DisablingEmergency, PopUpInfos.Header.Warning))
                                {
                                    BRS.Debug.Success("Disabling EMERGENCY PROTOCOL");

                                    MasterProtocol.mode = Modes_Ref.pause;
                                    MasterProtocol.error = CAN_Errors.none;
                                    MasterProtocol.state = States_Ref.paused;

                                    ModuleData_Vehicle.SetNewMode(Modes_Ref.pause);
                                    ModuleData_SortingStation.SetNewMode(Modes_Ref.pause);
                                    ModuleData_WeightStation.SetNewMode(Modes_Ref.pause);

                                    NewUserTextInfo(UserInfos.Modes.EmergencyDisabled, 2);
                                    OperationLogs.Window.Log_header(LogsInfos.Operations.NoMoreEmergency);           
                                    OperationLogs.Window.Log_Warning(LogsInfos.Operations.NowPaused);
                                    worked = true;
                                }
                                else
                                {
                                    BRS.Debug.Aborted("Keeping emergency protocol active");
                                }
                            }
                            else
                            {
                                NewUserTextInfo(UserInfos.Modes.IsPaused, 1);
                                MasterProtocol.mode = Modes_Ref.pause;
                                MasterProtocol.error = CAN_Errors.none;
                                MasterProtocol.state = States_Ref.paused;

                                OperationLogs.Window.Log_header(LogsInfos.Operations.NowPaused);
                                ModuleData_SortingStation.SetNewMode(Modes_Ref.pause);
                                ModuleData_WeightStation.SetNewMode(Modes_Ref.pause);
                                ModuleData_Vehicle.SetNewMode(Modes_Ref.pause);
                                worked = true;
                            }
                        }
                    }
                    //--------------------------------------------------//
                    if (mode == WantedMode.Maintenance)
                    {
                        if (MasterProtocol.mode != Modes_Ref.emergencyStop)
                        {
                            // already in the same mode bruh
                            if (MasterProtocol.mode == Modes_Ref.maintenance)
                            {
                                NewUserTextInfo(UserInfos.Modes.Already.Maintenance, 2);
                            }
                            else
                            {
                                if (MasterProtocol.mode == Modes_Ref.pause)
                                {
                                    NewUserTextInfo(UserInfos.Modes.IsMaintenance, 1);
                                    MasterProtocol.mode = Modes_Ref.maintenance;
                                    MasterProtocol.error = CAN_Errors.none;
                                    MasterProtocol.state = States_Ref.safe;
                                    OperationLogs.Window.Log_header(LogsInfos.Operations.NowMaintnance);
                                    
                                    ModuleData_SortingStation.SetNewMode(Modes_Ref.maintenance);
                                    ModuleData_WeightStation.SetNewMode(Modes_Ref.maintenance);
                                    ModuleData_Vehicle.SetNewMode(Modes_Ref.maintenance);
                                    worked = true;
                                }
                                else
                                {
                                    if (PopUp.Question(PopUpInfos.ModeSwitching.IsNotPaused, PopUpInfos.Header.Warning))
                                    {
                                        if (MasterProtocol.mode == Modes_Ref.operation)
                                        {
                                            OperationLogs.Window.Log_Error(LogsInfos.Operations.UnexpectedEnd);
                                        }
                                        NewUserTextInfo(UserInfos.Modes.IsMaintenance, 1);
                                        MasterProtocol.mode = Modes_Ref.maintenance;
                                        MasterProtocol.error = CAN_Errors.none;
                                        MasterProtocol.state = States_Ref.safe;
                                        OperationLogs.Window.Log_header(LogsInfos.Operations.NowMaintnance);

                                        ModuleData_SortingStation.SetNewMode(Modes_Ref.operation);
                                        ModuleData_WeightStation.SetNewMode(Modes_Ref.maintenance);
                                        ModuleData_Vehicle.SetNewMode(Modes_Ref.maintenance);
                                        worked = true;
                                    }
                                }
                            }
                        }
                        else
                        {
                            NewUserTextInfo(UserInfos.Modes.IsEmergency,2);
                        }
                    }
                    //--------------------------------------------------//
                    if (mode == WantedMode.Calibrating)
                    {
                        if (MasterProtocol.mode != Modes_Ref.emergencyStop)
                        {
                            // already in the same mode bruh
                            if (MasterProtocol.mode == Modes_Ref.calibration)
                            {
                                NewUserTextInfo(UserInfos.Modes.Already.Calibrating, 2);
                            }
                            else
                            {
                                if (MasterProtocol.mode == Modes_Ref.pause)
                                {
                                    NewUserTextInfo(UserInfos.Modes.IsCalibrating, 1);
                                    MasterProtocol.mode = Modes_Ref.calibration;
                                    MasterProtocol.error = CAN_Errors.none;
                                    MasterProtocol.state = States_Ref.calibrated;
                                    OperationLogs.Window.Log_header(LogsInfos.Operations.NowCalibrating);
                                    
                                    ModuleData_SortingStation.SetNewMode(Modes_Ref.calibration);
                                    ModuleData_WeightStation.SetNewMode(Modes_Ref.calibration);
                                    ModuleData_Vehicle.SetNewMode(Modes_Ref.calibration);
                                    worked = true;
                                }
                                else
                                {
                                    if (PopUp.Question(PopUpInfos.ModeSwitching.IsNotPaused, PopUpInfos.Header.Warning))
                                    {
                                        if (MasterProtocol.mode == Modes_Ref.operation)
                                        {
                                            OperationLogs.Window.Log_Error(LogsInfos.Operations.UnexpectedEnd);
                                        }
                                        NewUserTextInfo(UserInfos.Modes.IsCalibrating, 1);
                                        MasterProtocol.mode = Modes_Ref.calibration;
                                        MasterProtocol.error = CAN_Errors.none;
                                        MasterProtocol.state = States_Ref.calibrated;
                                        OperationLogs.Window.Log_header(LogsInfos.Operations.NowCalibrating);
                                        
                                        ModuleData_SortingStation.SetNewMode(Modes_Ref.calibration);
                                        ModuleData_WeightStation.SetNewMode(Modes_Ref.calibration);
                                        ModuleData_Vehicle.SetNewMode(Modes_Ref.calibration);
                                        worked = true;
                                    }
                                }
                            }
                        }
                        else
                        {
                            NewUserTextInfo(UserInfos.Modes.IsEmergency, 2);
                        }
                    }
                    //--------------------------------------------------//
                    if (mode == WantedMode.Emergency)
                    {
                        BRS.Debug.Comment("Disregarding litterally fucking everything and setting mode to EmergencyStop");
                        MasterProtocol.mode = Modes_Ref.emergencyStop;
                        MasterProtocol.error = CAN_Errors.EmergencyStop;
                        MasterProtocol.state = States_Ref.emergencyStop;

                        ModuleData_Vehicle.SetNewMode(Modes_Ref.emergencyStop);
                        ModuleData_SortingStation.SetNewMode(Modes_Ref.emergencyStop);
                        ModuleData_WeightStation.SetNewMode(Modes_Ref.emergencyStop);
                        NewUserTextInfo(UserInfos.Modes.EmergencyEnabled, 2);
                        OperationLogs.Window.Log_header(LogsInfos.Operations.NowInEmergency);
                        worked = true;
                    }
                    //--------------------------------------------------//
                    if (mode == WantedMode.Testing)
                    {
                        if (MasterProtocol.mode != Modes_Ref.emergencyStop)
                        {
                            // already in the same mode bruh
                            if (MasterProtocol.mode == Modes_Ref.testing)
                            {
                                NewUserTextInfo(UserInfos.Modes.Already.Testing, 2);
                            }
                            else
                            {
                                if (MasterProtocol.mode == Modes_Ref.pause)
                                {
                                    NewUserTextInfo(UserInfos.Modes.IsTesting, 1);
                                    MasterProtocol.mode = Modes_Ref.testing;
                                    MasterProtocol.error = CAN_Errors.none;
                                    MasterProtocol.state = States_Ref.testing;
                                    OperationLogs.Window.Log_header(LogsInfos.Operations.NowTesting);

                                    ModuleData_SortingStation.SetNewMode(Modes_Ref.testing);
                                    ModuleData_WeightStation.SetNewMode(Modes_Ref.testing);
                                    ModuleData_Vehicle.SetNewMode(Modes_Ref.testing);
                                    worked = true;
                                }
                                else
                                {
                                    if (PopUp.Question(PopUpInfos.ModeSwitching.IsNotPaused, PopUpInfos.Header.Warning))
                                    {
                                        if (MasterProtocol.mode == Modes_Ref.operation)
                                        {
                                            OperationLogs.Window.Log_Error(LogsInfos.Operations.UnexpectedEnd);
                                        }
                                        NewUserTextInfo(UserInfos.Modes.IsTesting, 1);
                                        MasterProtocol.mode = Modes_Ref.testing;
                                        MasterProtocol.error = CAN_Errors.none;
                                        MasterProtocol.state = States_Ref.testing;
                                        OperationLogs.Window.Log_header(LogsInfos.Operations.NowTesting);
                                        
                                        ModuleData_SortingStation.SetNewMode(Modes_Ref.testing);
                                        ModuleData_WeightStation.SetNewMode(Modes_Ref.testing);
                                        ModuleData_Vehicle.SetNewMode(Modes_Ref.testing);
                                        worked = true;
                                    }
                                }
                            }
                        }
                        else
                        {
                            NewUserTextInfo(UserInfos.Modes.IsEmergency, 2);
                        }
                    }
                    //--------------------------------------------------//
                    if (mode == WantedMode.Initialising)
                    {
                        if (MasterProtocol.mode != Modes_Ref.emergencyStop)
                        {
                            // already in the same mode bruh
                            if (MasterProtocol.mode == Modes_Ref.reinitialisation)
                            {
                                NewUserTextInfo(UserInfos.Modes.Already.Initialising, 2);
                            }
                            else
                            {
                                if (MasterProtocol.mode == Modes_Ref.pause)
                                {
                                    NewUserTextInfo(UserInfos.Modes.IsInitialising, 1);
                                    MasterProtocol.mode = Modes_Ref.reinitialisation;
                                    MasterProtocol.error = CAN_Errors.none;
                                    MasterProtocol.state = States_Ref.waiting;
                                    OperationLogs.Window.Log_header(LogsInfos.Operations.NowInitialising);

                                    ModuleData_SortingStation.SetNewMode(Modes_Ref.reinitialisation);
                                    ModuleData_WeightStation.SetNewMode(Modes_Ref.reinitialisation);
                                    ModuleData_Vehicle.SetNewMode(Modes_Ref.reinitialisation);
                                    worked = true;
                                }
                                else
                                {
                                    if (PopUp.Question(PopUpInfos.ModeSwitching.IsNotPaused, PopUpInfos.Header.Warning))
                                    {
                                        if (MasterProtocol.mode == Modes_Ref.operation)
                                        {
                                            OperationLogs.Window.Log_Error(LogsInfos.Operations.UnexpectedEnd);
                                        }

                                        NewUserTextInfo(UserInfos.Modes.IsInitialising, 1);
                                        MasterProtocol.mode = Modes_Ref.reinitialisation;
                                        MasterProtocol.error = CAN_Errors.none;
                                        MasterProtocol.state = States_Ref.waiting;
                                        OperationLogs.Window.Log_header(LogsInfos.Operations.NowInitialising);

                                        ModuleData_SortingStation.SetNewMode(Modes_Ref.reinitialisation);
                                        ModuleData_WeightStation.SetNewMode(Modes_Ref.reinitialisation);
                                        ModuleData_Vehicle.SetNewMode(Modes_Ref.reinitialisation);
                                        worked = true;
                                    }
                                }
                            }
                        }
                        else
                        {
                            NewUserTextInfo(UserInfos.Modes.IsEmergency, 2);
                        }
                    }
                }
                else
                {
                    NewUserTextInfo(UserInfos.MasterProtocol.IsOffline,2);
                    MasterProtocol.mode = Modes_Ref.pause;
                }
            }
            else
            {
                NewUserTextInfo(UserInfos.ComPort.IsOffline,2);
                MasterProtocol.mode = Modes_Ref.pause;
            }
            UpdateModeIcons();
            BRS.Debug.Header(false);
            return worked;
        }
        #endregion SetMode


        /// <summary>
        /// Class containing the colors to use when displaying the
        /// weight gotten from the scale on the screen. These colos
        /// are exactly matched with icons used throughout this
        /// application
        /// </summary>
        public static class ControlStateColors
        {
            public static Color Active = Color.FromArgb(64, 192, 87);
            public static Color Disabled = Color.FromArgb(77, 77, 77);
            public static Color Warning = Color.FromArgb(250, 176, 5);
            public static Color Error = Color.FromArgb(250, 82, 82);
            public static Color Inactive = Color.FromArgb(115, 115, 115);
        }
        //#############################################################//
        /// <summary>
        /// Reloads the entire form's languages. This enables french or
        /// english to be replaced in the form
        /// </summary>
        //#############################################################//
        public void ReloadForm()
        {
            Debug.Comment("Replacing Label names inside the application");
            Label_FileName.Text = Label_Names.Label_FileName;
            Label_User.Text = Label_Names.Label_User;
            Label_Password.Text = Label_Names.Label_Password;
            Label_FileName.Text = Label_Names.Label_FileName;
            Label_FilePath.Text = Label_Names.Label_FilePath;
            Label_AutoConnect.Text = Label_Names.Label_AutoConnect;
            Label_Language.Text = Label_Names.Label_Language;
            Label_ScaleUnit.Text = Label_Names.Label_ScaleUnit;

            Debug.Comment("Replacing Label specific to the technician mode");
            Technician_Label_Mode.Text = Label_Names.Technician_Label_Mode;
            Technician_Label_Status.Text = Label_Names.Technician_Label_Status;
            Technician_Label_DataTypeA.Text = Label_Names.Technician_Label_DataTypeA;
            Technician_Label_DataTypeB.Text = Label_Names.Technician_Label_DataTypeB;
            Technician_Label_DataA.Text = Label_Names.Technician_Label_DataA;
            Technician_Label_DataB.Text = Label_Names.Technician_Label_DataB;
            Technician_Label_CanOutput.Text = Label_Names.Technician_Label_CanOutput;

            Debug.Comment("Replacing Label specific to buttons inside the technician mode");
            Technician_Label_SimulateModes.Text = Label_Names.Technician_Label_SimulateModes;
            Technician_Label_KeepCanOn.Text = Label_Names.Technician_Label_KeepCanOn;
            Technician_Label_ClearAfterSend.Text = Label_Names.Technician_Label_ClearAfterSend;
            Technician_Label_SendOnce.Text = Label_Names.Technician_Label_SendOnce;

            Debug.Comment("Replacing tab names");
            Tab_Calibration.Text = Tab_Names.Calibration;
            Tab_Maintenance.Text = Tab_Names.Maintenance;
            Tab_Operation.Text = Tab_Names.Operation;
            Tab_Settings.Text = Tab_Names.Settings;
            Tab_Technician.Text = Tab_Names.Technician;
            Tab_Terminal.Text = Tab_Names.Terminal;

            Debug.Comment("Replacing module names");
            ModuleData_SortingStation.name = Module_Names.SortingStation;
            ModuleData_Vehicle.name = Module_Names.Vehicle;
            ModuleData_WeightStation.name = Module_Names.WeightStation;

            // terminal reset
            Debug.Comment("Clearing terminals with no prior warnings cuz I couldn't be asked");
            CommandCenter.Technician.terminal.Clear();
            CommandCenter.terminal.Clear();
            CommandCenter.Maintenance.terminal.Clear();
            CommandCenter.Calibration.terminal.Clear();

            // Close technician mode (basically to reset dropdowns)
            if(Technician.isActive)
            {
                Debug.Comment("Terminating technician mode");
                Technician.Close(this);
            }
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
            /// <summary>
            /// All genericButtons used in the Tab_Operation
            /// </summary>
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
                public static GenericButton Disc;
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
        /// <summary>
        /// Class containing all the buttons specific to the
        /// Technician tab
        /// </summary>
        public class Technician
        {
            public class Buttons
            {
                public static GenericButton Vehicle;
                public static GenericButton SortingStation;
                public static GenericButton WeightStation;
                public static GenericButton ClearTerminal;
                public static GenericButton SaveTerminal;

                public static GenericButton SendConfig;
                public static GenericButton ClearAfterSend;
                public static GenericButton SimulateModes;
                public static GenericButton KeepCanOn;

                public static GenericButton TechMode;
            }

            public static Terminal terminal;
        }
        /// <summary>
        /// Class containing all the buttons specific to the
        /// Calibration tab
        /// </summary>
        public class Calibration
        {
            public class Buttons
            {
                public static GenericButton Vehicle;
                public static GenericButton SortingStation;
                public static GenericButton WeightStation;
                public static GenericButton Global;
                public static GenericButton ClearTerminal;
                public static GenericButton SaveTerminal;

                public static GenericButton Calibration;
            }

            public static Terminal terminal;
        }
        /// <summary>
        /// Class containing all the buttons specific to the
        /// Calibration tab
        /// </summary>
        public class Maintenance
        {
            public class Buttons
            {
                public static GenericButton Vehicle;
                public static GenericButton SortingStation;
                public static GenericButton WeightStation;
                public static GenericButton Global;
                public static GenericButton ClearTerminal;
                public static GenericButton SaveTerminal;

                public static GenericButton Maintenance;
            }

            public static Terminal terminal;
        }
        public static RichTextBox tempo;
        /// <summary>
        /// The command center's terminal.
        /// </summary>
        public static Terminal terminal;
    }
}
