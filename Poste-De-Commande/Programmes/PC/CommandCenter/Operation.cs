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
                            NewUserTextInfo("EMERGENCY [OFF]", 2);
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
                        NewUserTextInfo("[EMERGENCY MODE]", 2);
                        UpdateModeIcons();
                    }
                }
                else
                {
                    Debug.Aborted("CAN protocol is currently not active");
                    NewUserTextInfo("CAN protocol offline", 2);
                }
            }
            else
            {
                Debug.Aborted("USB is closed, the Mode cannot be set to be an emergency Stop");
                NewUserTextInfo("No SerialPort connected",2);
            }

            Update_OperationTab();
            BRS.Debug.Header(false);
        }
        //#############################################################//
        //#############################################################//
        private void Operation_Terminal_Clear_Click(object sender, EventArgs e)
        {

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
                        NewUserTextInfo("Starting Operations", 1);
                        MasterProtocol.mode = Modes_Ref.operation;
                    }
                    else
                    {
                        if (MasterProtocol.mode == Modes_Ref.operation)
                        {
                            BRS.Debug.Comment("Attempting to pause operations");
                            NewUserTextInfo("Paused Operations", 1);
                            MasterProtocol.mode = Modes_Ref.pause;
                        }
                        else
                        {
                            if (MasterProtocol.mode == Modes_Ref.emergencyStop)
                            {
                                NewUserTextInfo("EMERGENCY STOP", 2);
                            }
                            else
                            {
                                BRS.Debug.Comment("Starting operation from another mode");
                                if (BRS.PopUp.Question("Are you sure you want to start Operations? The command center is executing an other mode", "Just checking yk"))
                                {
                                    Debug.Success("Starting operations");
                                    NewUserTextInfo("Starting Operations", 3);
                                    MasterProtocol.mode = Modes_Ref.operation;
                                }
                                else
                                {
                                    Debug.Aborted("Cancelling");
                                    NewUserTextInfo("Cancelled Operations", 3);
                                }
                            }
                        }
                    }
                }
                else
                {
                    Debug.Aborted("Cancelling");
                    NewUserTextInfo("CAN is not ON", 3);
                }
            }
            else
            {
                NewUserTextInfo("No Connection", 2);
            }
            BRS.Debug.Header(false);
        }
        #endregion Button_Clicks
    }
}
