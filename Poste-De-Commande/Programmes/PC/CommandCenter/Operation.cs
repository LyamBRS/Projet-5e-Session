using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;
using System.Media;
using System.Runtime.InteropServices;
using System.Threading;
using System.Collections.ObjectModel;
using System.Xml.Linq;
using BRS;
using BRS.Buttons;
using static CommandCenter.Form_MainMenu.cModule;

namespace CommandCenter
{
    public partial class Form_MainMenu : Form
    {
        #region Variables
        #endregion Variables

        #region Classes
        //#############################################################//
        /// <summary>
        /// Class allowing the program to easily log what happenned on
        /// an end user comprehensible level during operation mode.
        /// Should be done using the Terminal class, nbut wasn't due to
        /// SerialPort being an issue, and time being a constraint.
        /// </summary>
        //#############################################################//
        public static class OperationLogs
        {
            /// <summary>
            /// The Terminal used by the Operation Logs
            /// </summary>
            public static BRS.Terminal Window;
        }
        #endregion Classes

        #region Operation_Specifics
        //#############################################################//
        /// <summary>
        /// Function updating the operation mode controls each time
        /// called
        /// </summary>
        //#############################################################//
        public void Update_OperationTab()
        {
            Update_Button_EmergencyMode();
            Update_Button_ClearLog();
            Update_Button_StartStop();

            Update_ModuleIcon_Sorting();
            Update_ModuleIcon_Vehicle();
            Update_ModuleIcon_Weight();

            //reset old values.
            Old.Operation.utils.MasterProtocol.Mode = MasterProtocol.mode;
            Old.Operation.utils.MasterProtocol.isActive = MasterProtocol.isActive;
            Old.Operation.utils.ComPort.isOpen = BRS.ComPort.Port.IsOpen;
        }

        #region Individual_Updates
        //#############################################################//
        /// <summary>
        /// Updates the Emergency mode button present inside the
        /// Tab_Operation according to bunch of parameters.
        /// </summary>
        //#############################################################//
        public void Update_Button_EmergencyMode()
        {
            bool comPortIsOpen = BRS.ComPort.Port.IsOpen;
            bool masterProtocolActive = MasterProtocol.isActive;
            byte masterProtocolMode = MasterProtocol.mode;
            ////////////////////////////////////////////////////////////
            if (Old.Operation.utils.ComPort.isOpen != comPortIsOpen)
            {
                if(comPortIsOpen)
                {
                    CommandCenter.Operation.Buttons.EmergencyStop.State = ControlState.Inactive;
                }
                else
                {
                    CommandCenter.Operation.Buttons.EmergencyStop.State = ControlState.Disabled;
                }
            }
            ////////////////////////////////////////////////////////////
            if (comPortIsOpen)
            {
                if (masterProtocolActive != Old.Operation.utils.MasterProtocol.isActive || masterProtocolMode != Old.Operation.utils.MasterProtocol.Mode)
                {
                    if (masterProtocolActive)
                    {
                        if(masterProtocolMode == Modes_Ref.emergencyStop)
                        {
                            CommandCenter.Operation.Buttons.EmergencyStop.State = ControlState.Error;
                        }
                        else
                        {
                            //Defaulted to:
                            CommandCenter.Operation.Buttons.EmergencyStop.State = ControlState.Inactive;

                            if (masterProtocolMode == Modes_Ref.operation)
                            {
                                CommandCenter.Operation.Buttons.EmergencyStop.State = ControlState.Warning;
                            }

                            if (masterProtocolMode == Modes_Ref.pause)
                            {
                                CommandCenter.Operation.Buttons.EmergencyStop.State = ControlState.Active;
                            }
                        }
                    }
                    else
                    {   // Master protocol is OFF, no beaglebone communications
                        CommandCenter.Operation.Buttons.EmergencyStop.State = ControlState.Inactive;
                    }
                }
            }
        }
        //#############################################################//
        /// <summary>
        /// Updates the terminal mode button present inside the
        /// Tab_Operation according to bunch of parameters.
        /// </summary>
        //#############################################################//
        public void Update_Button_ClearLog()
        {
            bool comPortIsOpen = BRS.ComPort.Port.IsOpen;
            bool masterProtocolActive = MasterProtocol.isActive;
            byte masterProtocolMode = MasterProtocol.mode;
            ////////////////////////////////////////////////////////////
            if (Old.Operation.utils.ComPort.isOpen != comPortIsOpen)
            {
                if (comPortIsOpen)
                {
                    CommandCenter.Operation.Buttons.ClearTerminal.State = ControlState.Inactive;
                }
                else
                {
                    CommandCenter.Operation.Buttons.ClearTerminal.State = ControlState.Disabled;
                }
            }
            ////////////////////////////////////////////////////////////
            if (comPortIsOpen)
            {
                if (masterProtocolActive != Old.Operation.utils.MasterProtocol.isActive || masterProtocolMode != Old.Operation.utils.MasterProtocol.Mode)
                {
                    if (masterProtocolActive)
                    {
                        if (masterProtocolMode == Modes_Ref.emergencyStop)
                        {
                            CommandCenter.Operation.Buttons.ClearTerminal.State = ControlState.Disabled;
                        }
                        else
                        {
                            //Defaulted to:
                            CommandCenter.Operation.Buttons.ClearTerminal.State = ControlState.Inactive;

                            if (masterProtocolMode == Modes_Ref.operation)
                            {
                                CommandCenter.Operation.Buttons.ClearTerminal.State = ControlState.Active;
                            }

                            if (masterProtocolMode == Modes_Ref.pause)
                            {
                                CommandCenter.Operation.Buttons.ClearTerminal.State = ControlState.Active;
                            }
                        }
                    }
                    else
                    {   // Master protocol is OFF, no beaglebone communications
                        CommandCenter.Operation.Buttons.ClearTerminal.State = ControlState.Inactive;
                    }
                }
            }
        }
        //#############################################################//
        /// <summary>
        /// Updates the pause/play mode button present inside the
        /// Tab_Operation according to bunch of parameters.
        /// </summary>
        //#############################################################//
        public void Update_Button_StartStop()
        {
            bool comPortIsOpen = BRS.ComPort.Port.IsOpen;
            bool masterProtocolActive = MasterProtocol.isActive;
            byte masterProtocolMode = MasterProtocol.mode;
            ////////////////////////////////////////////////////////////
            if (Old.Operation.utils.ComPort.isOpen != comPortIsOpen)
            {
                if (comPortIsOpen)
                {
                    CommandCenter.Operation.Buttons.Pause.Bitmaps = Icons.Play.GetStatesBitmaps();
                    CommandCenter.Operation.Buttons.Pause.State = ControlState.Inactive;
                }
                else
                {
                    CommandCenter.Operation.Buttons.Pause.Bitmaps = Icons.Play.GetStatesBitmaps();
                    CommandCenter.Operation.Buttons.Pause.State = ControlState.Disabled;
                }
            }
            ////////////////////////////////////////////////////////////
            if (comPortIsOpen)
            {
                if (masterProtocolActive != Old.Operation.utils.MasterProtocol.isActive || masterProtocolMode != Old.Operation.utils.MasterProtocol.Mode)
                {
                    if (masterProtocolActive)
                    {
                        if (masterProtocolMode == Modes_Ref.emergencyStop)
                        {
                            CommandCenter.Operation.Buttons.Pause.Bitmaps = Icons.Play.GetStatesBitmaps();
                            CommandCenter.Operation.Buttons.Pause.State = ControlState.Error;
                        }
                        else
                        {
                            if (masterProtocolMode == Modes_Ref.operation)
                            {
                                CommandCenter.Operation.Buttons.Pause.Bitmaps = Icons.Paused.GetStatesBitmaps();
                                CommandCenter.Operation.Buttons.Pause.State = ControlState.Active;
                            }
                            else
                            {
                                if (masterProtocolMode == Modes_Ref.pause)
                                {
                                    CommandCenter.Operation.Buttons.Pause.Bitmaps = Icons.Play.GetStatesBitmaps();
                                    CommandCenter.Operation.Buttons.Pause.State = ControlState.Active;
                                }
                                else
                                {
                                    CommandCenter.Operation.Buttons.Pause.Bitmaps = Icons.Play.GetStatesBitmaps();
                                    CommandCenter.Operation.Buttons.Pause.State = ControlState.Inactive;
                                }
                            }
                        }
                    }
                    else
                    {   // Master protocol is OFF, no beaglebone communications
                        CommandCenter.Operation.Buttons.Pause.Bitmaps = Icons.Play.GetStatesBitmaps();
                        CommandCenter.Operation.Buttons.Pause.State = ControlState.Warning;
                    }
                }
            }
        }
        //#############################################################//
        /// <summary>
        /// Updates the sorting factory's mode button present inside the
        /// Tab_Operation according to bunch of parameters.
        /// </summary>
        //#############################################################//
        #region Modules
        public void Update_ModuleIcon_Sorting()
        {
            bool comPortIsOpen = BRS.ComPort.Port.IsOpen;
            bool masterProtocolActive = MasterProtocol.isActive;
            byte masterProtocolMode = MasterProtocol.mode;
            ////////////////////////////////////////////////////////////
            if (Old.Operation.utils.ComPort.isOpen != comPortIsOpen)
            {
                if (comPortIsOpen)
                {
                    CommandCenter.Operation.Buttons.SortingStation.State = ControlState.Loading;
                }
                else
                {
                    CommandCenter.Operation.Buttons.SortingStation.State = ControlState.Inactive;
                }
            }
            ////////////////////////////////////////////////////////////
            if (comPortIsOpen)
            {
                if (masterProtocolActive != Old.Operation.utils.MasterProtocol.isActive || Old.Operation.Modules.Sorting.State != ModuleData_SortingStation.Current.State)
                {
                    if (masterProtocolActive)
                    {
                        if(Old.Operation.Modules.Sorting.State != ModuleData_SortingStation.Current.State)
                        {
                            if(ModuleData_SortingStation.Current.State == State_Offline)
                            {
                                CommandCenter.Operation.Buttons.SortingStation.State = ControlState.Inactive;
                            }
                            else //was if(true)
                            {
                                if (ModuleData_SortingStation.Current.State == States_Ref.error)
                                {
                                    CommandCenter.Operation.Buttons.SortingStation.State = ControlState.Error;
                                }
                                else
                                {
                                    //Checking if the current state is expected  in the current wanted mode or not
                                    if (ModuleData_SortingStation.IsStateAllowed())
                                    {
                                        CommandCenter.Operation.Buttons.SortingStation.State = ControlState.Active;
                                    }
                                    else
                                    {
                                        CommandCenter.Operation.Buttons.SortingStation.State = ControlState.Warning;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {   // Master protocol is OFF, no beaglebone communications
                        CommandCenter.Operation.Buttons.SortingStation.State = ControlState.Loading;
                    }
                }
            }
        }
        //#############################################################//
        /// <summary>
        /// Updates the vehicle's mode button present inside the
        /// Tab_Operation according to bunch of parameters.
        /// </summary>
        //#############################################################//
        public void Update_ModuleIcon_Vehicle()
        {
            bool comPortIsOpen = BRS.ComPort.Port.IsOpen;
            bool masterProtocolActive = MasterProtocol.isActive;
            byte masterProtocolMode = MasterProtocol.mode;
            ////////////////////////////////////////////////////////////
            if (Old.Operation.utils.ComPort.isOpen != comPortIsOpen)
            {
                if (comPortIsOpen)
                {
                    CommandCenter.Operation.Buttons.Vehicle.State = ControlState.Loading;
                }
                else
                {
                    CommandCenter.Operation.Buttons.Vehicle.State = ControlState.Inactive;
                }
            }
            ////////////////////////////////////////////////////////////
            if(comPortIsOpen)
            {
                if (masterProtocolActive != Old.Operation.utils.MasterProtocol.isActive || Old.Operation.Modules.Sorting.State != ModuleData_Vehicle.Current.State)
                {
                    if (masterProtocolActive)
                    {
                        if (Old.Operation.Modules.Vehicle.State != ModuleData_Vehicle.Current.State)
                        {
                            if (ModuleData_Vehicle.Current.State == State_Offline)
                            {
                                CommandCenter.Operation.Buttons.Vehicle.State = ControlState.Inactive;
                            }
                            else //was if(true)
                            {
                                if (ModuleData_Vehicle.Current.State == States_Ref.error)
                                {
                                    CommandCenter.Operation.Buttons.Vehicle.State = ControlState.Error;
                                }
                                else
                                {
                                    //Checking if the current state is expected  in the current wanted mode or not
                                    if (ModuleData_Vehicle.IsStateAllowed())
                                    {
                                        CommandCenter.Operation.Buttons.Vehicle.State = ControlState.Active;
                                    }
                                    else
                                    {
                                        CommandCenter.Operation.Buttons.Vehicle.State = ControlState.Warning;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {   // Master protocol is OFF, no beaglebone communications
                        CommandCenter.Operation.Buttons.Vehicle.State = ControlState.Loading;
                    }
                }
            }
        }
        //#############################################################//
        /// <summary>
        /// Updates the weight station's mode button present inside the
        /// Tab_Operation according to bunch of parameters.
        /// </summary>
        //#############################################################//
        public void Update_ModuleIcon_Weight()
        {
            bool comPortIsOpen = BRS.ComPort.Port.IsOpen;
            bool masterProtocolActive = MasterProtocol.isActive;
            byte masterProtocolMode = MasterProtocol.mode;
            ////////////////////////////////////////////////////////////
            if (Old.Operation.utils.ComPort.isOpen != comPortIsOpen)
            {
                if (comPortIsOpen)
                {
                    CommandCenter.Operation.Buttons.WeightStation.State = ControlState.Loading;
                }
                else
                {
                    CommandCenter.Operation.Buttons.WeightStation.State = ControlState.Inactive;
                }
            }
            ////////////////////////////////////////////////////////////
            if (comPortIsOpen)
            {
                if (masterProtocolActive != Old.Operation.utils.MasterProtocol.isActive || Old.Operation.Modules.Sorting.State != ModuleData_WeightStation.Current.State)
                {
                    if (masterProtocolActive)
                    {
                        if (Old.Operation.Modules.Weight.State != ModuleData_WeightStation.Current.State)
                        {
                            if (ModuleData_WeightStation.Current.State == State_Offline)
                            {
                                CommandCenter.Operation.Buttons.WeightStation.State = ControlState.Inactive;
                            }
                            else //was if(true)
                            {
                                if (ModuleData_WeightStation.Current.State == States_Ref.error)
                                {
                                    CommandCenter.Operation.Buttons.WeightStation.State = ControlState.Error;
                                }
                                else
                                {
                                    //Checking if the current state is expected  in the current wanted mode or not
                                    if (ModuleData_WeightStation.IsStateAllowed())
                                    {
                                        CommandCenter.Operation.Buttons.WeightStation.State = ControlState.Active;
                                    }
                                    else
                                    {
                                        CommandCenter.Operation.Buttons.WeightStation.State = ControlState.Warning;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {   // Master protocol is OFF, no beaglebone communications
                        CommandCenter.Operation.Buttons.WeightStation.State = ControlState.Loading;
                    }
                }
            }
        }
        #endregion Modules
        //#############################################################//
        /// <summary>
        /// Updates the global icons which represent the general state
        /// of everything module related.
        /// </summary>
        //#############################################################//
        public void Update_ModuleIcon_Global()
        {
            bool comPortIsOpen = BRS.ComPort.Port.IsOpen;
            bool masterProtocolActive = MasterProtocol.isActive;
            byte masterProtocolMode = MasterProtocol.mode;
            ////////////////////////////////////////////////////////////
            if (Old.Operation.utils.ComPort.isOpen != comPortIsOpen)
            {
                if (comPortIsOpen)
                {
                    CommandCenter.Operation.Buttons.Global.State = ControlState.Loading;
                }
                else
                {
                    CommandCenter.Operation.Buttons.Global.State = ControlState.Inactive;
                }
            }
            ////////////////////////////////////////////////////////////
            if (comPortIsOpen)
            {
                if (masterProtocolActive)
                {
                    if(true) //(Old.Operation.Modules.Weight.State != ModuleData_WeightStation.Current.State)
                    {
                        bool sortingStationOffline = ModuleData_SortingStation.Current.State == State_Offline;
                        bool weightStationOffline = ModuleData_WeightStation.Current.State == State_Offline;
                        bool vehicleOffline = ModuleData_Vehicle.Current.State == State_Offline;

                        bool allModuleOffline = sortingStationOffline && weightStationOffline && vehicleOffline;
                        bool someModuleOffline = sortingStationOffline || weightStationOffline || vehicleOffline;

                        if (allModuleOffline)
                        {
                            CommandCenter.Operation.Buttons.Global.State = ControlState.Error;
                        }
                        else //was if(true)
                        {
                            if (someModuleOffline)
                            {
                                CommandCenter.Operation.Buttons.Global.State = ControlState.Warning;
                            }
                            else
                            {
                                CommandCenter.Operation.Buttons.Global.State = ControlState.Active;
                            }
                        }
                    }
                }
                else
                {   // Master protocol is OFF, no beaglebone communications
                    CommandCenter.Operation.Buttons.Global.State = ControlState.Loading;
                }
            }
        }
        #endregion Individual_Updates
        #endregion Operation_Specifics

        #region Button_Clicks
        //#############################################################//
        /// <summary>
        /// Called each time the Emergency Stop icon is pressed while
        /// tabbed in the Operation TabPage
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Operation_EmergencyStop_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);

            BRS.Debug.Comment("Checking if USB is openned...");
            if(BRS.ComPort.Port.IsOpen)
            {
                BRS.Debug.Comment("Checking if CAN MasterProtocol is active");
                if (MasterProtocol.isActive)
                {
                    if (MasterProtocol.mode == Modes_Ref.emergencyStop)
                    {
                        BRS.Debug.Comment("Asking the user if he really wants to disable the emergency protocol which isongoing");
                        if(BRS.PopUp.Question("Are you sure you want to disable the emergency proceedure?","EMERGENCY PROTOCOL"))
                        {
                            BRS.Debug.Success("Disabling EMERGENCY PROTOCOL");

                            MasterProtocol.mode = Modes_Ref.pause;
                            MasterProtocol.error = CAN_Errors.none;
                            MasterProtocol.state = States_Ref.paused;

                            ModuleData_Vehicle.Current.Mode        = Modes_Ref.pause;
                            ModuleData_SortingStation.Current.Mode = Modes_Ref.pause;
                            ModuleData_WeightStation.Current.Mode  = Modes_Ref.pause;

                            UpdateModeIcons();
                            NewUserTextInfo(UserInfos.Modes.EmergencyDisabled, 2);
                        }
                        else
                        {
                            BRS.Debug.Aborted("Keeping emergency protocol active");
                        }
                    }
                    else
                    {
                        BRS.Debug.Comment("Disregarding litterally fucking everything and setting mode to EmergencyStop");
                        MasterProtocol.mode = Modes_Ref.emergencyStop;
                        MasterProtocol.error = CAN_Errors.EmergencyStop;
                        MasterProtocol.state = States_Ref.emergencyStop;

                        ModuleData_Vehicle.Current.Mode = Modes_Ref.emergencyStop;
                        ModuleData_SortingStation.Current.Mode = Modes_Ref.emergencyStop;
                        ModuleData_WeightStation.Current.Mode = Modes_Ref.emergencyStop;
                        NewUserTextInfo(UserInfos.Modes.EmergencyEnabled, 2);
                        UpdateModeIcons();
                    }
                }
                else
                {
                    Debug.Aborted("CAN protocol is currently not active");
                    NewUserTextInfo(UserInfos.MasterProtocol.IsOffline, 2);
                }
            }
            else
            {
                Debug.Aborted("USB is closed, the Mode cannot be set to be an emergency Stop");
                NewUserTextInfo(UserInfos.ComPort.IsOffline,2);
            }

            Update_OperationTab();
            BRS.Debug.Header(false);
        }
        //#############################################################//
        //#############################################################//
        private void Operation_Terminal_Clear_Click(object sender, EventArgs e)
        {
            Random sus = new Random();
            OperationLogs.Window.Log_Comment(sus.Next().ToString());
        }
        //#############################################################//
        /// <summary>
        /// Happens when you click on the saving icon locted inside of
        /// the the Tab_Operation
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Operation_Save_Logs_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Attempting to save the Operation's logs");
            OperationLogs.Window.SaveTerminal();
            NewUserTextInfo(UserInfos.Terminal.Saved,1);
            Debug.Success();
            OperationLogs.Window.Clear();
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Executed each time the play/pause button is pressed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Operation_Pause_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Setting up for Operation");

            if (BRS.ComPort.Port.IsOpen)
            {
                if (MasterProtocol.isActive)
                {
                    if (MasterProtocol.mode == Modes_Ref.pause)
                    {
                        BRS.Debug.Comment("Attempting to start operations");
                        NewUserTextInfo(UserInfos.Modes.OperationStarted, 1);
                        MasterProtocol.mode = Modes_Ref.operation;
                    }
                    else
                    {
                        if (MasterProtocol.mode == Modes_Ref.operation)
                        {
                            BRS.Debug.Comment("Attempting to pause operations");
                            NewUserTextInfo(UserInfos.Modes.NowPaused, 1);
                            MasterProtocol.mode = Modes_Ref.pause;
                        }
                        else
                        {
                            if (MasterProtocol.mode == Modes_Ref.emergencyStop)
                            {
                                NewUserTextInfo(UserInfos.Modes.IsEmergency, 2);
                            }
                            else
                            {
                                BRS.Debug.Comment("Starting operation from another mode");
                                if (BRS.PopUp.Question("Are you sure you want to start Operations? The command center is executing an other mode", "Just checking yk"))
                                {
                                    Debug.Success("Starting operations");
                                    NewUserTextInfo(UserInfos.Modes.OperationStarted, 3);
                                    MasterProtocol.mode = Modes_Ref.operation;
                                }
                                else
                                {
                                    Debug.Aborted("Cancelling");
                                }
                            }
                        }
                    }
                }
                else
                {
                    Debug.Aborted("Cancelling");
                    NewUserTextInfo(UserInfos.MasterProtocol.IsOffline, 3);
                }
            }
            else
            {
                NewUserTextInfo(UserInfos.ComPort.IsOffline, 2);
            }
            BRS.Debug.Header(false);
        }
        #region ModuleButtons
        //#############################################################//
        /// <summary>
        /// Executed each time the sorting station button is pressed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Operation_Module_SortingStation_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Displaying sorting station's status");

            if (BRS.ComPort.Port.IsOpen)
            {
                if (MasterProtocol.isActive)
                {
                    if (ModuleData_SortingStation.error != Module_Errors.none)
                    {
                        NewUserTextInfo(ModuleData_SortingStation.error.ToString(), 1);
                    }
                    else
                    {
                        if (ModuleData_SortingStation.Current.State == State_Offline)
                        {
                            NewUserTextInfo(UserInfos.Modules.IsUnresponsive, 3);
                        }
                        else
                        {
                            if (ModuleData_SortingStation.Current.State == States_Ref.emergencyStop)
                            {
                                NewUserTextInfo(UserInfos.Modules.IsInEmergency, 2);
                            }
                            else
                            {
                                if (ModuleData_SortingStation.IsStateAllowed())
                                {
                                    // regular states that the sorting station can have
                                    if (ModuleData_SortingStation.Current.State == States_Ref.calibrated)                    { NewUserTextInfo(UserInfos.Modules.States.calibrated, 1); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.calibrating)                   { NewUserTextInfo(UserInfos.Modules.States.calibrating, 3); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.empty)                         { NewUserTextInfo(UserInfos.Modules.States.empty, 1); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.error)                         { NewUserTextInfo(UserInfos.Modules.States.error, 2); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.atSortingFactory)              { NewUserTextInfo(UserInfos.Modules.States.atSortingFactory, 2); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.atWeightStation)               { NewUserTextInfo(UserInfos.Modules.States.atWeightStation, 2); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.finishedSortingAndHasLoaded)   { NewUserTextInfo(UserInfos.Modules.States.finishedSortingAndHasLoaded, 1); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.finishedWeighting)             { NewUserTextInfo(UserInfos.Modules.States.finishedWeighting, 3); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.paused)                        { NewUserTextInfo(UserInfos.Modules.States.paused, 1); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.processing)                    { NewUserTextInfo(UserInfos.Modules.States.processing, 1); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.safe)                          { NewUserTextInfo(UserInfos.Modules.States.safe, 1); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.testing)                       { NewUserTextInfo(UserInfos.Modules.States.testing, 1); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.waiting)                       { NewUserTextInfo(UserInfos.Modules.States.waiting, 3); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.waitingToSort)                 { NewUserTextInfo(UserInfos.Modules.States.waitingToSort, 1); }
                                    if (ModuleData_SortingStation.Current.State == States_Ref.waitingToWeight)               { NewUserTextInfo(UserInfos.Modules.States.waitingToWeight, 2); }
                                }
                                else
                                {
                                    NewUserTextInfo(UserInfos.Modules.WrongStatus, 2);
                                    OperationLogs.Window.Log_Comment("[USER CONTROL]: " + ModuleData_SortingStation.name + "'s status: " + ModuleData_SortingStation.Current.State.ToString() + " does not match with the current mode: " + MasterProtocol.mode, Color.Tomato);
                                }
                        }
                        }
                    }
                }
                else
                {
                    Debug.Aborted("Cancelling");
                    NewUserTextInfo(UserInfos.MasterProtocol.IsOffline, 3);
                }
            }
            else
            {
                NewUserTextInfo(UserInfos.ComPort.IsOffline, 2);
            }
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Happens everytime you click on the Vehicule.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Operation_Module_Vehicle_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Displaying vehicle's status");

            if (BRS.ComPort.Port.IsOpen)
            {
                if (MasterProtocol.isActive)
                {
                    if (ModuleData_Vehicle.error != Module_Errors.none)
                    {
                        NewUserTextInfo(ModuleData_Vehicle.error.ToString(), 1);
                    }
                    else
                    {
                        if (ModuleData_Vehicle.Current.State == State_Offline)
                        {
                            NewUserTextInfo(UserInfos.Modules.IsUnresponsive, 3);
                        }
                        else
                        {
                            if (ModuleData_Vehicle.Current.State == States_Ref.emergencyStop)
                            {
                                NewUserTextInfo(UserInfos.Modules.IsInEmergency, 2);
                            }
                            else
                            {
                                if (ModuleData_Vehicle.IsStateAllowed())
                                {
                                    // regular states that the sorting station can have
                                    if (ModuleData_Vehicle.Current.State == States_Ref.calibrated)                    { NewUserTextInfo(UserInfos.Modules.States.calibrated, 1); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.calibrating)                   { NewUserTextInfo(UserInfos.Modules.States.calibrating, 3); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.empty)                         { NewUserTextInfo(UserInfos.Modules.States.empty, 1); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.error)                         { NewUserTextInfo(UserInfos.Modules.States.error, 2); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.atSortingFactory)              { NewUserTextInfo(UserInfos.Modules.States.atSortingFactory, 2); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.atWeightStation)               { NewUserTextInfo(UserInfos.Modules.States.atWeightStation, 2); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.finishedSortingAndHasLoaded)   { NewUserTextInfo(UserInfos.Modules.States.finishedSortingAndHasLoaded, 1); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.finishedWeighting)             { NewUserTextInfo(UserInfos.Modules.States.finishedWeighting, 3); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.paused)                        { NewUserTextInfo(UserInfos.Modules.States.paused, 1); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.processing)                    { NewUserTextInfo(UserInfos.Modules.States.processing, 1); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.safe)                          { NewUserTextInfo(UserInfos.Modules.States.safe, 1); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.testing)                       { NewUserTextInfo(UserInfos.Modules.States.testing, 1); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.waiting)                       { NewUserTextInfo(UserInfos.Modules.States.waiting, 3); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.waitingToSort)                 { NewUserTextInfo(UserInfos.Modules.States.waitingToSort, 1); }
                                    if (ModuleData_Vehicle.Current.State == States_Ref.waitingToWeight)               { NewUserTextInfo(UserInfos.Modules.States.waitingToWeight, 2); }
                                }
                                else
                                {
                                    NewUserTextInfo(UserInfos.Modules.WrongStatus, 2);
                                    OperationLogs.Window.Log_Comment("[USER CONTROL]: " + ModuleData_Vehicle.name + "'s status: " + ModuleData_Vehicle.Current.State.ToString() + " does not match with the current mode: " + MasterProtocol.mode, Color.Tomato);
                                }
                        }
                        }
                    }
                }
                else
                {
                    Debug.Aborted("Cancelling");
                    NewUserTextInfo(UserInfos.MasterProtocol.IsOffline, 3);
                }
            }
            else
            {
                NewUserTextInfo(UserInfos.ComPort.IsOffline, 2);
            }
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Happens everytime you click on the Weight Station.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Operation_Module_WeightStation_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Displaying the weight station's status");

            if (BRS.ComPort.Port.IsOpen)
            {
                if (MasterProtocol.isActive)
                {
                    if (ModuleData_WeightStation.error != Module_Errors.none)
                    {
                        NewUserTextInfo(ModuleData_WeightStation.error.ToString(), 1);
                    }
                    else
                    {
                        if (ModuleData_WeightStation.Current.State == State_Offline)
                        {
                            NewUserTextInfo(UserInfos.Modules.IsUnresponsive, 3);
                        }
                        else
                        {
                            if (ModuleData_WeightStation.Current.State == States_Ref.emergencyStop)
                            {
                                NewUserTextInfo(UserInfos.Modules.IsInEmergency, 2);
                            }
                            else
                            {
                                if (ModuleData_WeightStation.IsStateAllowed())
                                {
                                    if (ModuleData_WeightStation.Current.State == States_Ref.calibrated)                    { NewUserTextInfo(UserInfos.Modules.States.calibrated, 1); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.calibrating)                   { NewUserTextInfo(UserInfos.Modules.States.calibrating, 3); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.empty)                         { NewUserTextInfo(UserInfos.Modules.States.empty, 1); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.error)                         { NewUserTextInfo(UserInfos.Modules.States.error, 2); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.atSortingFactory)              { NewUserTextInfo(UserInfos.Modules.States.atSortingFactory, 2); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.atWeightStation)               { NewUserTextInfo(UserInfos.Modules.States.atWeightStation, 2); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.finishedSortingAndHasLoaded)   { NewUserTextInfo(UserInfos.Modules.States.finishedSortingAndHasLoaded, 1); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.finishedWeighting)             { NewUserTextInfo(UserInfos.Modules.States.finishedWeighting, 3); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.paused)                        { NewUserTextInfo(UserInfos.Modules.States.paused, 1); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.processing)                    { NewUserTextInfo(UserInfos.Modules.States.processing, 1); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.safe)                          { NewUserTextInfo(UserInfos.Modules.States.safe, 1); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.testing)                       { NewUserTextInfo(UserInfos.Modules.States.testing, 1); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.waiting)                       { NewUserTextInfo(UserInfos.Modules.States.waiting, 3); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.waitingToSort)                 { NewUserTextInfo(UserInfos.Modules.States.waitingToSort, 1); }
                                    if (ModuleData_WeightStation.Current.State == States_Ref.waitingToWeight)               { NewUserTextInfo(UserInfos.Modules.States.waitingToWeight, 2); }
                                }
                                else
                                {
                                    NewUserTextInfo(UserInfos.Modules.WrongStatus, 2);
                                    OperationLogs.Window.Log_Comment("[USER CONTROL]: " + ModuleData_WeightStation.name + "'s status: " + ModuleData_WeightStation.Current.State.ToString() + " does not match with the current mode: " + MasterProtocol.mode, Color.Tomato);
                                }
                            }
                        }
                    }
                }
                else
                {
                    Debug.Aborted("Cancelling");
                    NewUserTextInfo(UserInfos.MasterProtocol.IsOffline, 3);
                }
            }
            else
            {
                NewUserTextInfo(UserInfos.ComPort.IsOffline, 2);
            }
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Happens everytime you click on the Global module icons.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Operation_Module_Global_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            if (BRS.ComPort.Port.IsOpen)
            {
                if (MasterProtocol.isActive)
                {
                    bool sortingStationOffline = ModuleData_SortingStation.Current.State == State_Offline;
                    bool weightStationOffline  = ModuleData_WeightStation.Current.State == State_Offline;
                    bool vehicleOffline        = ModuleData_Vehicle.Current.State == State_Offline;

                    //-----------------------------------------------------------------//
                    // All modules are offline
                    //-----------------------------------------------------------------//
                    if (sortingStationOffline || weightStationOffline || vehicleOffline)
                    {
                        string sortingStationMessage = sortingStationOffline ? " Sorting," : "";
                        string vehicleMessage        = vehicleOffline        ? " Vehicle," : "";
                        string weightStationMessage  = weightStationOffline  ? " Weight," : "";

                        string result = sortingStationMessage + vehicleMessage + weightStationMessage;

                        //Remove last comma from the sentence
                        if (result.EndsWith(",")) { result = result.Remove(result.Length - 1, 1); }
                        NewUserTextInfo("Offline modules:" + result,2);
                    }
                    else
                    {
                        NewUserTextInfo(UserInfos.Modules.AllAreOnline,1);
                    }
                }
                else
                {
                    NewUserTextInfo(UserInfos.MasterProtocol.IsOffline, 2);
                }
            }
            else
            {
                BRS.Debug.Comment("No serial connection");
                NewUserTextInfo(UserInfos.ComPort.IsOffline, 2);
            }
                    BRS.Debug.Header(false);
        }
        #endregion ModuleButtons 
        #endregion Button_Clicks
    }
}
