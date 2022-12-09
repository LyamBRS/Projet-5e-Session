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
            Update_ModuleIcon_Global();

            Update_Disc_ColorIndicator();
            OverView_Update_TruckPosition();

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
                    CommandCenter.Operation.Buttons.ClearTerminal.State = ControlState.Warning;
                }
                else
                {
                    CommandCenter.Operation.Buttons.ClearTerminal.State = ControlState.Inactive;
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
        /// entire application
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
        /// Updates the sorting factory's mode buttons present inside 
        /// the entire applicationb
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
                            if(ModuleData_SortingStation.Current.State == State_Offline || ModuleData_SortingStation.Current.State == State_ClassInitialised)
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
            CommandCenter.Technician.Buttons.SortingStation.State = CommandCenter.Operation.Buttons.SortingStation.State;
            CommandCenter.Operation.Overview.SortingStation.State = CommandCenter.Operation.Buttons.SortingStation.State;
        }
        //#############################################################//
        /// <summary>
        /// Updates the vehicle's mode buttons present inside the
        /// entire application
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
                            if (ModuleData_Vehicle.Current.State == State_Offline || ModuleData_Vehicle.Current.State == State_ClassInitialised)
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
            CommandCenter.Technician.Buttons.Vehicle.State = CommandCenter.Operation.Buttons.Vehicle.State;
            CommandCenter.Operation.Overview.Vehicle.State = CommandCenter.Operation.Buttons.Vehicle.State;
        }
        //#############################################################//
        /// <summary>
        /// Updates the weight station's mode button present inside the
        /// entire application
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
                            if (ModuleData_WeightStation.Current.State == State_Offline || ModuleData_WeightStation.Current.State == State_ClassInitialised)
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
            CommandCenter.Technician.Buttons.WeightStation.State = CommandCenter.Operation.Buttons.WeightStation.State;
            CommandCenter.Operation.Overview.WeightStation.State = CommandCenter.Operation.Buttons.WeightStation.State;
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
                        bool sortingStationOffline = ModuleData_SortingStation.Current.State == State_Offline || ModuleData_SortingStation.Current.State == State_ClassInitialised;
                        bool weightStationOffline = ModuleData_WeightStation.Current.State == State_Offline || ModuleData_WeightStation.Current.State == State_ClassInitialised;
                        bool vehicleOffline = ModuleData_Vehicle.Current.State == State_Offline || ModuleData_Vehicle.Current.State == State_ClassInitialised;

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
                        SetGlobalModeTo(WantedMode.Paused);
                    }
                    else
                    {
                        SetGlobalModeTo(WantedMode.Emergency);
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
        /// <summary>
        /// Function called when the button to clear the terminal
        /// is pressed.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Operation_Terminal_Clear_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Attempting to clear the terminal");
            OperationLogs.Window.Clear();

            if (OperationLogs.Window.Window.Text == "")
            {
                Debug.Success("terminal cleared!");
                NewUserTextInfo(UserInfos.Terminal.Cleared, 1);
            }
            else
            {
                Debug.Aborted("terminal cleared!");
                //NewUserTextInfo("Canceled clearing", 3);
            }
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Happens when you click on the saving icon located inside of
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
                        SetGlobalModeTo(WantedMode.Operating);
                    }
                    else
                    {
                        SetGlobalModeTo(WantedMode.Paused);
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
                        if (ModuleData_SortingStation.Current.State == State_Offline || ModuleData_SortingStation.Current.State == State_ClassInitialised)
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
                                // regular states that the sorting station can have
                                if (ModuleData_SortingStation.Current.State == States_Ref.calibrated)                    { NewUserTextInfo(UserInfos.Modules.SortingStation.calibrated, 1); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.calibrating)                   { NewUserTextInfo(UserInfos.Modules.SortingStation.calibrating, 3); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.empty)                         { NewUserTextInfo(UserInfos.Modules.SortingStation.empty, 1); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.error)                         { NewUserTextInfo(UserInfos.Modules.SortingStation.error, 2); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.atSortingFactory)              { NewUserTextInfo(UserInfos.Modules.SortingStation.atSortingFactory, 2); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.atWeightStation)               { NewUserTextInfo(UserInfos.Modules.SortingStation.atWeightStation, 2); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.finishedSortingAndHasLoaded)   { NewUserTextInfo(UserInfos.Modules.SortingStation.finishedSortingAndHasLoaded, 1); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.finishedWeighting)             { NewUserTextInfo(UserInfos.Modules.SortingStation.finishedWeighting, 3); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.paused)                        { NewUserTextInfo(UserInfos.Modules.SortingStation.paused, 1); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.processing)                    { NewUserTextInfo(UserInfos.Modules.SortingStation.processing, 1); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.safe)                          { NewUserTextInfo(UserInfos.Modules.SortingStation.safe, 1); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.testing)                       { NewUserTextInfo(UserInfos.Modules.SortingStation.testing, 1); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.waiting)                       { NewUserTextInfo(UserInfos.Modules.SortingStation.waiting, 3); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.waitingToSort)                 { NewUserTextInfo(UserInfos.Modules.SortingStation.waitingToSort, 1); }
                                if (ModuleData_SortingStation.Current.State == States_Ref.waitingToWeight)               { NewUserTextInfo(UserInfos.Modules.SortingStation.waitingToWeight, 2); }
                                if (!ModuleData_SortingStation.IsStateAllowed())
                                {
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
                        if (ModuleData_Vehicle.Current.State == State_Offline || ModuleData_Vehicle.Current.State == State_ClassInitialised)
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
                                // regular states that the sorting station can have
                                if (ModuleData_Vehicle.Current.State == States_Ref.calibrated)                    { NewUserTextInfo(UserInfos.Modules.Vehicle.calibrated, 1); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.calibrating)                   { NewUserTextInfo(UserInfos.Modules.Vehicle.calibrating, 3); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.empty)                         { NewUserTextInfo(UserInfos.Modules.Vehicle.empty, 1); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.error)                         { NewUserTextInfo(UserInfos.Modules.Vehicle.error, 2); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.atSortingFactory)              { NewUserTextInfo(UserInfos.Modules.Vehicle.atSortingFactory, 2); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.atWeightStation)               { NewUserTextInfo(UserInfos.Modules.Vehicle.atWeightStation, 2); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.finishedSortingAndHasLoaded)   { NewUserTextInfo(UserInfos.Modules.Vehicle.finishedSortingAndHasLoaded, 1); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.finishedWeighting)             { NewUserTextInfo(UserInfos.Modules.Vehicle.finishedWeighting, 3); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.paused)                        { NewUserTextInfo(UserInfos.Modules.Vehicle.paused, 1); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.processing)                    { NewUserTextInfo(UserInfos.Modules.Vehicle.processing, 1); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.safe)                          { NewUserTextInfo(UserInfos.Modules.Vehicle.safe, 1); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.testing)                       { NewUserTextInfo(UserInfos.Modules.Vehicle.testing, 1); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.waiting)                       { NewUserTextInfo(UserInfos.Modules.Vehicle.waiting, 3); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.waitingToSort)                 { NewUserTextInfo(UserInfos.Modules.Vehicle.waitingToSort, 1); }
                                if (ModuleData_Vehicle.Current.State == States_Ref.waitingToWeight)               { NewUserTextInfo(UserInfos.Modules.Vehicle.waitingToWeight, 2); }
                                if(!ModuleData_Vehicle.IsStateAllowed())
                                {
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
                        if (ModuleData_WeightStation.Current.State == State_Offline || ModuleData_WeightStation.Current.State == State_ClassInitialised)
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
                                if (ModuleData_WeightStation.Current.State == States_Ref.calibrated)                    { NewUserTextInfo(UserInfos.Modules.WeightStation.calibrated, 1); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.calibrating)                   { NewUserTextInfo(UserInfos.Modules.WeightStation.calibrating, 3); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.empty)                         { NewUserTextInfo(UserInfos.Modules.WeightStation.empty, 1); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.error)                         { NewUserTextInfo(UserInfos.Modules.WeightStation.error, 2); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.atSortingFactory)              { NewUserTextInfo(UserInfos.Modules.WeightStation.atSortingFactory, 2); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.atWeightStation)               { NewUserTextInfo(UserInfos.Modules.WeightStation.atWeightStation, 2); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.finishedSortingAndHasLoaded)   { NewUserTextInfo(UserInfos.Modules.WeightStation.finishedSortingAndHasLoaded, 1); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.finishedWeighting)             { NewUserTextInfo(UserInfos.Modules.WeightStation.finishedWeighting, 3); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.paused)                        { NewUserTextInfo(UserInfos.Modules.WeightStation.paused, 1); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.processing)                    { NewUserTextInfo(UserInfos.Modules.WeightStation.processing, 1); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.safe)                          { NewUserTextInfo(UserInfos.Modules.WeightStation.safe, 1); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.testing)                       { NewUserTextInfo(UserInfos.Modules.WeightStation.testing, 1); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.waiting)                       { NewUserTextInfo(UserInfos.Modules.WeightStation.waiting, 3); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.waitingToSort)                 { NewUserTextInfo(UserInfos.Modules.WeightStation.waitingToSort, 1); }
                                if (ModuleData_WeightStation.Current.State == States_Ref.waitingToWeight)               { NewUserTextInfo(UserInfos.Modules.WeightStation.waitingToWeight, 2); }
                                
                                if(!ModuleData_WeightStation.IsStateAllowed())
                                {
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
                    bool sortingStationOffline = ModuleData_SortingStation.Current.State    == State_Offline || ModuleData_SortingStation.Current.State == State_ClassInitialised;
                    bool weightStationOffline  = ModuleData_WeightStation.Current.State     == State_Offline || ModuleData_WeightStation.Current.State  == State_ClassInitialised;
                    bool vehicleOffline        = ModuleData_Vehicle.Current.State           == State_Offline || ModuleData_Vehicle.Current.State == State_ClassInitialised;

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

        #region OverView
        #region Positions
        //#############################################################//
        /// <summary>
        /// Updates the visualized location of the truck inside of the
        /// OverView present inside of Tab_Operation
        /// </summary>
        //#############################################################//
        public void OverView_Update_TruckPosition()
        {
            if (MasterProtocol.mode == Modes_Ref.operation)
            {
                //--------------------------------------------------------//
                // Get Button locations 
                //--------------------------------------------------------//
                Point SortingPosition = Overview_SortingStation.Location;
                Point WeightPosition = Overview_WeightStation.Location;
                Point VehiclePosition = Overview_Vehicle.Location;
                //--------------------------------------------------------//
                // Get float equivalent of button locations
                //--------------------------------------------------------//
                float sortingX = (float)(SortingPosition.X);
                float weightX = (float)(WeightPosition.X);
                float vehicleX = (float)(VehiclePosition.X);

                //Defaults to middle of the 2
                float wantedX = ((weightX - sortingX) / 2) + sortingX;
                //--------------------------------------------------------//
                // Check vehicle location
                //--------------------------------------------------------//
                bool atWeightStation = (ModuleData_Vehicle.Current.State == States_Ref.atWeightStation) || ModuleData_Vehicle.Current.State == States_Ref.empty || ModuleData_Vehicle.Current.State == States_Ref.waiting || ModuleData_Vehicle.Current.State == State_ClassInitialised;

                if (ModuleData_Vehicle.Current.State == States_Ref.atSortingFactory)
                {
                    wantedX = sortingX + ((float)(Overview_SortingStation.Size.Width));
                }

                if (atWeightStation)
                {
                    wantedX = weightX - ((float)(Overview_WeightStation.Size.Width));
                }
                //--------------------------------------------------------//
                // Lerp vehicle location
                //--------------------------------------------------------//
                float newXLocation = BRS.Smoothing.Lerp(vehicleX, wantedX, 0.1f);
                //--------------------------------------------------------//
                // Set buttons to new location
                //--------------------------------------------------------//
                Overview_Vehicle.Location = new Point(((int)(newXLocation)), VehiclePosition.Y);
                CommandCenter.Operation.Overview.Vehicle.UpdateOriginalPositions(Overview_Vehicle.Location);
            }
        }
        #endregion Positions
        #region Clicks
        //#############################################################//
        /// <summary>
        /// Happens everytime you click on the Vehicule.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Overview_Vehicle_Click(object sender, EventArgs e)
        {
            Operation_Module_Vehicle_Click(sender, e);
        }
        //#############################################################//
        /// <summary>
        /// Executed each time the sorting station button is pressed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Overview_SortingStation_Click(object sender, EventArgs e)
        {
            Operation_Module_SortingStation_Click(sender, e);
        }
        //#############################################################//
        /// <summary>
        /// Happens everytime you click on the Weight Station.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Overview_WeightStation_Click(object sender, EventArgs e)
        {
            Operation_Module_WeightStation_Click(sender, e);
        }
        #endregion Clicks
        #endregion OverView

        #region DiscColorStuff
        //#############################################################//
        /// <summary>
        /// used to update the icon of the disc color present in
        /// the Tab_Operation
        /// </summary>
        //#############################################################//
        public void Update_Disc_ColorIndicator()
        {
            //--------------------------------------------------------//
            // If USB is opened
            //--------------------------------------------------------//
            if(!BRS.ComPort.Port.IsOpen)
            {
                CommandCenter.Operation.Buttons.Disc.State = ControlState.Inactive;
                ModuleData_SortingStation.DetectedDiscColor(DiscColor.NoData);
            }
            else
            {
                //--------------------------------------------------------//
                // If the CAN bus is online
                //--------------------------------------------------------//
                if (MasterProtocol.isActive)
                {
                    //--------------------------------------------------------//
                    // Check if module is offline
                    //--------------------------------------------------------//
                    if (ModuleData_SortingStation.Current.State == State_Offline || ModuleData_SortingStation.Current.State == State_ClassInitialised)
                    {
                        CommandCenter.Operation.Buttons.Disc.State = ControlState.Inactive;
                        ModuleData_SortingStation.DetectedDiscColor(DiscColor.NoData);
                    }
                    else
                    {
                        DiscColor currentColor = ModuleData_SortingStation.DetectedDiscColor();

                        //--------------------------------------------------------//
                        // Never received disc related data
                        //--------------------------------------------------------//
                        if (currentColor == DiscColor.NoData)
                        {
                            CommandCenter.Operation.Buttons.Disc.State = ControlState.Inactive;
                        }
                        //--------------------------------------------------------//
                        // Orange disc color
                        //--------------------------------------------------------//
                        if (currentColor == DiscColor.Red)
                        {
                            CommandCenter.Operation.Buttons.Disc.State = ControlState.Error;
                        }
                        //--------------------------------------------------------//
                        // Black disc color
                        //--------------------------------------------------------//
                        if (currentColor == DiscColor.Black)
                        {
                            CommandCenter.Operation.Buttons.Disc.State = ControlState.Warning;
                        }
                        //--------------------------------------------------------//
                        // Metallic / Silver disc color
                        //--------------------------------------------------------//
                        if (currentColor == DiscColor.Metallic)
                        {
                            CommandCenter.Operation.Buttons.Disc.State = ControlState.Active;
                        }
                        //--------------------------------------------------------//
                        // No more disc
                        //--------------------------------------------------------//
                        if (currentColor == DiscColor.NoDisc)
                        {
                            CommandCenter.Operation.Buttons.Disc.State = ControlState.Inactive;
                        }
                    }
                }
                else
                {
                    CommandCenter.Operation.Buttons.Disc.State = ControlState.Inactive;
                    ModuleData_SortingStation.DetectedDiscColor(DiscColor.NoData);
                }
            }
        }
        //#############################################################//
        /// <summary>
        /// Event related function which is called whenever the button
        /// is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Operation_Disc_Color_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Giving information about currently detected disc color...");

            if(BRS.ComPort.Port.IsOpen)
            {
                Debug.Success("Port is opened");
                if(MasterProtocol.isActive)
                {
                    Debug.Success("CAN is online");

                    DiscColor result = ModuleData_SortingStation.DetectedDiscColor();

                    if(result == DiscColor.Black)
                    {
                        BRS.Debug.Comment("Sorting station is seeing a black disc");
                        NewUserTextInfo(UserInfos.Modules.SortingStation.DiscIsBlack,1);
                    }
                    if (result == DiscColor.Metallic)
                    {
                        BRS.Debug.Comment("Sorting station is seeing a metallic disc");
                        NewUserTextInfo(UserInfos.Modules.SortingStation.DiscIsSilver, 1);
                    }
                    if (result == DiscColor.Red)
                    {
                        BRS.Debug.Comment("Sorting station is seeing a red disc");
                        NewUserTextInfo(UserInfos.Modules.SortingStation.DiscIsRed, 1);
                    }
                    if (result == DiscColor.NoDisc)
                    {
                        BRS.Debug.Comment("Sorting station no longer seeing colored disc");
                        NewUserTextInfo(UserInfos.Modules.SortingStation.DiscHasNoColor, 1);
                    }
                    if (result == DiscColor.NoData)
                    {
                        BRS.Debug.Comment("Sorting station has never seen a disc");
                        NewUserTextInfo(UserInfos.Modules.SortingStation.DiscNeverDetected, 1);
                    }
                }
                else
                {
                    Debug.Aborted("Can is offline");
                    NewUserTextInfo(UserInfos.MasterProtocol.IsOffline,2);
                }
            }
            else
            {
                BRS.Debug.Aborted("USB is offline");
                NewUserTextInfo(UserInfos.ComPort.IsOffline,2);
            }
            BRS.Debug.Header(false);
        }
        #endregion DiscColorStuff

        #region Scale
        //#############################################################//
        /// <summary>
        /// Update the displayed weight depending on ModuleData_Weight
        /// and other factors such as the COM port.
        /// </summary>
        //#############################################################//
        public void Operation_Update_Weight()
        {
            string Weight = "--";

            if(BRS.ComPort.Port.IsOpen)
            {
                if(MasterProtocol.isActive)
                {
                    byte weight = ModuleData_WeightStation.Current.Weight;

                    if (weight == Weight_Offline)
                    {
                        Weight = WeightInfos.isOffline;
                    }
                    else
                    {
                        //--------------------------------------------------// Display empty or the actual weight
                        if (weight == Weight_ScaleEmpty)
                        {
                            Weight = WeightInfos.isEmpty;
                        }
                        else
                        {
                            Weight = weight.ToString();
                        }

                        //--------------------------------------------------//
                        if (ModuleData_WeightStation.IsWeightUnitCorrect(WeightUnits.None))
                        {
                            Weight = Weight + WeightInfos.Units.UnknownUnit;
                        }
                        //--------------------------------------------------//
                        else
                        {
                            if (ModuleData_WeightStation.IsWeightUnitCorrect(WeightUnits.Multiple))
                            {
                                Weight = Weight + WeightInfos.Units.UnknownUnit;
                                ModuleData_WeightStation.Reset_WeightDatas();
                            }
                            //--------------------------------------------------//
                            else
                            {
                                WeightUnits currentlyWanted = DropDown_ScaleUnit.Text.Contains("Metric") ? WeightUnits.Metric : WeightUnits.Imperial;

                                if (ModuleData_WeightStation.IsWeightUnitCorrect(currentlyWanted))
                                {
                                    if(currentlyWanted == WeightUnits.Imperial)
                                    {
                                        Weight = Weight + WeightInfos.Units.Imperial;
                                    }
                                    else
                                    {
                                        Weight = Weight + WeightInfos.Units.Metric;
                                    }
                                }
                                else
                                {
                                    Weight = WeightInfos.isError;
                                }
                            }
                        }
                    }
                }
                else
                {
                    Weight = WeightInfos.isOffline;
                    Operation_Weight_Label.ForeColor = Color.DarkGray;
                }
            }
            else
            {
                Weight = WeightInfos.isOffline;
            }
            //----------------------------------------------------------//
            // Display the correct color for the weight label
            //----------------------------------------------------------//
            switch (CommandCenter.Operation.Buttons.WeightStation.State)
            {
                case (ControlState.Active):
                    Operation_Weight_Label.ForeColor = ControlStateColors.Active;
                    break;

                case (ControlState.Disabled):
                    Operation_Weight_Label.ForeColor = ControlStateColors.Disabled;
                    break;

                case (ControlState.Inactive):
                    Operation_Weight_Label.ForeColor = ControlStateColors.Inactive;
                    break;

                case (ControlState.Warning):
                    Operation_Weight_Label.ForeColor = ControlStateColors.Warning;
                    break;

                case (ControlState.Error):
                    Operation_Weight_Label.ForeColor = ControlStateColors.Error;
                    break;
            }
            //------------------------------------------------------------//
            // Only update the text if it differs from what's currently
            // shown. Note that this doesn't increase performences at all..
            // it's there just to prevent visual glitches from repetitive
            // updating
            //------------------------------------------------------------//
            if (Operation_Weight_Label.Text != Weight)
            {
                Operation_Weight_Label.Text = Weight;
            }
        }
        #endregion Scale
    }
}
