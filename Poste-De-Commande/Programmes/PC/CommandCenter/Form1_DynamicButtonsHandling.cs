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
        #region Variables
        //#############################################################//
        /// <summary>
        /// Class containing previous values for different applications
        /// used to compare with new values ot know when updates are
        /// necessary or not.
        /// </summary>
        //#############################################################//
        public class Old
        {
            public class MasterProtocol
            {
                public static byte Mode = 0;
                public static bool isActive = false;
            }
            /// <summary>
            /// Old values for comparaisons while updating stuff in
            /// the Operation tab
            /// </summary>
            public class CanTimer
            {
                public class MasterProtocol
                {
                    public static byte Mode = 0;
                    public static bool isActive = false;
                }
            }

            public class ComPort
            {
                public static bool isOpen = false;
            }
            /// <summary>
            /// Old values for comparaisons while updating stuff in
            /// the Operation tab
            /// </summary>
            public class Operation
            {
                /// <summary>
                /// Holds MasterProtocol and Comports for example
                /// </summary>
                public class utils
                {
                    public class MasterProtocol
                    {
                        public static byte Mode = 0;
                        public static bool isActive = false;
                    }
                    public class ComPort
                    {
                        public static bool isOpen = false;
                    }
                }
                /// <summary>
                /// Holds old module values.
                /// </summary>
                public class Modules
                {
                    /// <summary>
                    /// Old values of the ModuleData_SortingStation
                    /// used to compare new values with old ones to
                    /// avoid over updating stuff
                    /// </summary>
                    public class Sorting
                    {
                        public static byte State;
                        public static byte Mode;
                    }
                    /// <summary>
                    /// Old values of the ModuleData_WeightStation
                    /// used to compare new values with old ones to
                    /// avoid over updating stuff
                    /// </summary>
                    public class Weight
                    {
                        public static byte State;
                        public static byte Mode;
                    }
                    /// <summary>
                    /// Old values of the ModuleData_Vehicle
                    /// used to compare new values with old ones to
                    /// avoid over updating stuff
                    /// </summary>
                    public class Vehicle
                    {
                        public static byte State;
                        public static byte Mode;
                    }
                }
            }
        }

        public int DelayBeforeTurningBackOnUpdates = 0;
        #endregion Variables
        //#############################################################//
        /// <summary>
        /// Chooses between the correct set of StatesBitmaps for the
        /// BRS dynamic GenericButton used to display the current mode
        /// the command center is in.
        /// </summary>
        //#############################################################//
        public void UpdateModeIcons()
        {
            // Icons to use when communication with BeagleBoneBrun is ongoing
            if(MasterProtocol.isActive)
            {
                Old.ComPort.isOpen = !BRS.ComPort.Port.IsOpen;

                if (Technician.isActive && Technician.SimulateModes)
                {
                    CommandCenter.Buttons.Mode.State = ControlState.Warning;
                    //Simulating a mode
                    //-------------------------------------------------------------------------------------// OPERATION
                    if (Convert.ToByte(Technician.SelectedIndexes.Mode) == Modes_Ref.operation)
                    {
                        CommandCenter.Buttons.Mode.Bitmaps = Icons.Operation.GetStatesBitmaps();
                        //BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Operation)", true);
                    }
                    //-------------------------------------------------------------------------------------// MAINTENANCE
                    if (Convert.ToByte(Technician.SelectedIndexes.Mode) == Modes_Ref.maintenance)
                    {
                        CommandCenter.Buttons.Mode.Bitmaps = Icons.Maintenance.GetStatesBitmaps();
                        //BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Maintenance)", true);
                    }
                    //-------------------------------------------------------------------------------------// CALIBRATION
                    if (Convert.ToByte(Technician.SelectedIndexes.Mode) == Modes_Ref.calibration)
                    {
                        CommandCenter.Buttons.Mode.Bitmaps = Icons.Calibration.GetStatesBitmaps();
                        //BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Calibration)", true);
                    }
                    //-------------------------------------------------------------------------------------// PAUSED / STOP
                    if (Convert.ToByte(Technician.SelectedIndexes.Mode) == Modes_Ref.pause)
                    {
                        CommandCenter.Buttons.Mode.Bitmaps = Icons.Paused.GetStatesBitmaps();
                        //BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Pause)", true);
                    }
                    //-------------------------------------------------------------------------------------// TECH / TESTING
                    if (Convert.ToByte(Technician.SelectedIndexes.Mode) == Modes_Ref.testing)
                    {
                        CommandCenter.Buttons.Mode.Bitmaps = Icons.Tech.GetStatesBitmaps();
                        //BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Technician)", true);
                    }
                    //-------------------------------------------------------------------------------------// INITIALISATION
                    if (Convert.ToByte(Technician.SelectedIndexes.Mode) == Modes_Ref.reinitialisation)
                    {
                        CommandCenter.Buttons.Mode.Bitmaps = Icons.EveryModules.GetStatesBitmaps();
                        //BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Reinitialisation)", true);
                    }
                    //-------------------------------------------------------------------------------------// EMERGENCY MODE
                    if (Convert.ToByte(Technician.SelectedIndexes.Mode) == Modes_Ref.emergencyStop)
                    {
                        CommandCenter.Buttons.Mode.Bitmaps = Icons.Emergency.GetStatesBitmaps();
                        //BRS.Debug.Comment("The MasterProtocol's mode has been updated to (EMERGENCY MODE)", true);
                    }

                    //So that the mode icon resets after stopping the simulations
                    Old.MasterProtocol.Mode = 0xFF;
                }
                else
                {
                    CommandCenter.Buttons.Mode.State = ControlState.Active;
                    
                    //Regular modes printing
                    if (Old.MasterProtocol.Mode != MasterProtocol.mode || Old.MasterProtocol.isActive != MasterProtocol.isActive)
                    {
                        Old.MasterProtocol.Mode = MasterProtocol.mode;
                        //-------------------------------------------------------------------------------------// OPERATION
                        if (MasterProtocol.mode == Modes_Ref.operation)
                        {
                            CommandCenter.Buttons.Mode.Bitmaps = Icons.Operation.GetStatesBitmaps();
                            BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Operation)", true);
                        }
                        //-------------------------------------------------------------------------------------// MAINTENANCE
                        if (MasterProtocol.mode == Modes_Ref.maintenance)
                        {
                            CommandCenter.Buttons.Mode.Bitmaps = Icons.Maintenance.GetStatesBitmaps();
                            BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Maintenance)", true);
                        }
                        //-------------------------------------------------------------------------------------// CALIBRATION
                        if (MasterProtocol.mode == Modes_Ref.calibration)
                        {
                            CommandCenter.Buttons.Mode.Bitmaps = Icons.Calibration.GetStatesBitmaps();
                            BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Calibration)", true);
                        }
                        //-------------------------------------------------------------------------------------// PAUSED / STOP
                        if (MasterProtocol.mode == Modes_Ref.pause)
                        {
                            CommandCenter.Buttons.Mode.Bitmaps = Icons.Paused.GetStatesBitmaps();
                            BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Pause)", true);
                        }
                        //-------------------------------------------------------------------------------------// TECH / TESTING
                        if (MasterProtocol.mode == Modes_Ref.testing)
                        {
                            CommandCenter.Buttons.Mode.Bitmaps = Icons.Tech.GetStatesBitmaps();
                            BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Technician)", true);
                        }
                        //-------------------------------------------------------------------------------------// INITIALISATION
                        if (MasterProtocol.mode == Modes_Ref.reinitialisation)
                        {
                            CommandCenter.Buttons.Mode.Bitmaps = Icons.EveryModules.GetStatesBitmaps();
                            BRS.Debug.Comment("The MasterProtocol's mode has been updated to (Reinitialisation)", true);
                        }
                        //-------------------------------------------------------------------------------------// EMERGENCY MODE
                        if (MasterProtocol.mode == Modes_Ref.emergencyStop)
                        {
                            CommandCenter.Buttons.Mode.Bitmaps = Icons.Emergency.GetStatesBitmaps();
                            BRS.Debug.Comment("The MasterProtocol's mode has been updated to (EMERGENCY MODE)", true);
                        }
                    }
                }
            }
            else
            {
                Old.MasterProtocol.isActive = !MasterProtocol.isActive;

                if (Old.ComPort.isOpen != BRS.ComPort.Port.IsOpen || Old.MasterProtocol.Mode != 0xFF)
                {
                    Old.ComPort.isOpen = BRS.ComPort.Port.IsOpen;
                    if (BRS.ComPort.Port.IsOpen)
                    {
                        CommandCenter.Buttons.Mode.Bitmaps = Icons.Power.GetStatesBitmaps();
                        CommandCenter.Buttons.Mode.State = ControlState.Warning;
                        BRS.Debug.Comment("The MasterProtocol's mode icon has been updated to (POWER BUTTON)", true);
                    }
                    else
                    {
                        CommandCenter.Buttons.Mode.Bitmaps = Icons.Power.GetStatesBitmaps();
                        CommandCenter.Buttons.Mode.State = ControlState.Disabled;
                        BRS.Debug.Comment("The MasterProtocol's mode icon has been updated to (POWER BUTTON)", true);
                    }
                }
                Old.MasterProtocol.Mode = 0xFF;
            }
        }

        //#############################################################//
        /// <summary>
        /// Tick timer function executed each 10 milliseconds to update
        /// BRS Dynamic buttons.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void ButtonUpdateTimer_Tick(object sender, EventArgs e)
        {
            if (DelayBeforeTurningBackOnUpdates <= 0)
            {
                #region Universal
                CommandCenter.Buttons.USB.Update();
                CommandCenter.Buttons.Mode.Update();
                #endregion Universal
                #region Index_Settings
                if (TabControl_ModeSelector.SelectedTab == Tab_Settings)
                {
                    CommandCenter.Buttons.Link.Update();
                    CommandCenter.Buttons.AutoConnection.Update();
                }
                #endregion Index_Settings
                #region Index_Terminal
                if (TabControl_ModeSelector.SelectedTab == Tab_Terminal)
                {
                    CommandCenter.Buttons.Terminal.Update();
                    CommandCenter.Buttons.CloseBeagle.Update();
                    CommandCenter.Buttons.SaveBBBTerminal.Update();
                }
                #endregion Index_Terminal
                #region Index_Operation
                if (TabControl_ModeSelector.SelectedTab == Tab_Operation)
                {
                    CommandCenter.Operation.Buttons.ClearTerminal.Update();

                    CommandCenter.Operation.Buttons.EmergencyStop.Update();
                    CommandCenter.Operation.Buttons.Global.Update();
                    CommandCenter.Operation.Buttons.Pause.Update();
                    CommandCenter.Operation.Buttons.Vehicle.Update();
                    CommandCenter.Operation.Buttons.WeightStation.Update();
                    CommandCenter.Operation.Buttons.SortingStation.Update();
                    CommandCenter.Operation.Buttons.SaveOperationTerminal.Update();
                    CommandCenter.Operation.Buttons.Disc.Update();

                    CommandCenter.Operation.Overview.Vehicle.Update();
                    CommandCenter.Operation.Overview.WeightStation.Update();
                    CommandCenter.Operation.Overview.SortingStation.Update();

                    Operation_Update_Weight();
                }
                #endregion Index_Operation
                #region Index_Technician
                if (TabControl_ModeSelector.SelectedTab == Tab_Technician)
                {
                    CommandCenter.Technician.Buttons.ClearTerminal.Update();
                    CommandCenter.Technician.Buttons.SaveTerminal.Update();
                    CommandCenter.Technician.Buttons.KeepCanOn.Update();
                    CommandCenter.Technician.Buttons.ClearAfterSend.Update();
                    CommandCenter.Technician.Buttons.SimulateModes.Update();
                    CommandCenter.Technician.Buttons.SendConfig.Update();
                    CommandCenter.Technician.Buttons.Vehicle.Update();
                    CommandCenter.Technician.Buttons.WeightStation.Update();
                    CommandCenter.Technician.Buttons.SortingStation.Update();
                    CommandCenter.Technician.Buttons.TechMode.Update();

                    Technician_UpdateButton();
                }
                #endregion Index_Technician
                #region Index_Calibration
                if (TabControl_ModeSelector.SelectedTab == Tab_Calibration)
                {
                    Calibration_Update();
                    CommandCenter.Calibration.Buttons.Calibration.Update();
                    CommandCenter.Calibration.Buttons.ClearTerminal.Update();
                    CommandCenter.Calibration.Buttons.SaveTerminal.Update();
                    CommandCenter.Calibration.Buttons.Global.Update();
                    CommandCenter.Calibration.Buttons.SortingStation.Update();
                    CommandCenter.Calibration.Buttons.Vehicle.Update();
                    CommandCenter.Calibration.Buttons.WeightStation.Update();
                    CommandCenter.Calibration.Buttons.SaveTerminal.Update();
                    CommandCenter.Calibration.Buttons.ClearTerminal.Update();
                }
                #endregion Index_Calibration
                #region Index_Maintenance
                if (TabControl_ModeSelector.SelectedTab == Tab_Maintenance)
                {
                    Maintenance_Update();
                    CommandCenter.Maintenance.Buttons.Maintenance.Update();
                    CommandCenter.Maintenance.Buttons.ClearTerminal.Update();
                    CommandCenter.Maintenance.Buttons.SaveTerminal.Update();
                    CommandCenter.Maintenance.Buttons.Global.Update();
                    CommandCenter.Maintenance.Buttons.SortingStation.Update();
                    CommandCenter.Maintenance.Buttons.Vehicle.Update();
                    CommandCenter.Maintenance.Buttons.WeightStation.Update();
                    CommandCenter.Maintenance.Buttons.SaveTerminal.Update();
                    CommandCenter.Maintenance.Buttons.ClearTerminal.Update();
                }
                #endregion Index_Technician
            }
            else
            {
                DelayBeforeTurningBackOnUpdates--;
            }
            UpdateModeIcons();
            #region UserInfo
            int R = UserInfo.ForeColor.R;
            int G = UserInfo.ForeColor.G;
            int B = UserInfo.ForeColor.B;

            //Defines up to which point the color must fade out.
            // Always return to gray in a linear fashion.
            int minimum = 50;
            if (R > minimum) { R -= 2; }
            if (G > minimum) { G -= 2; }
            if (B > minimum) { B -= 2; }
            if (R < minimum) { R += 2; }
            if (G < minimum) { G += 2; }
            if (B < minimum) { B += 2; }

            UserInfo.ForeColor = Color.FromArgb(R, G, B);
            //ConsoleArea.Focus();
            #endregion UserInfo
        }
        #region FormResize
        //#############################################################//
        /// <summary>
        /// Resize function updating the size of referenced containers
        /// for BRS Dynamic buttons.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Form_MainMenu_Resize(object sender, EventArgs e)
        {
            
            ButtonUpdateTimer.Enabled = false;
            if (HasStartedResize == 0)
            {
                ButtonUpdateTimer.Enabled = false;
                UpdateAllButtonsPosition();
                ButtonUpdateTimer.Enabled = true;
            }
            
            
        }
        private void Form_MainMenu_ResizeBegin(object sender, EventArgs e)
        {
            
            ButtonUpdateTimer.Enabled = false;
            UpdateAllButtonsPosition();
            HasStartedResize = 1;
            
        }
        private void Form_MainMenu_ResizeEnd(object sender, EventArgs e)
        {
            
            UpdateAllButtonsPosition();
            ButtonUpdateTimer.Enabled = true;
            HasStartedResize = 0;   
        }
        #endregion FormResize
        #region Individual_Tab_Resises
        private void Tab_Technician_Resize(object sender, EventArgs e)
        {
            DelayBeforeTurningBackOnUpdates = 5;
            CommandCenter.Technician.Buttons.ClearTerminal.UpdateOriginalPositions(Technician_terminal_Clear.Location);
            CommandCenter.Technician.Buttons.SaveTerminal.UpdateOriginalPositions(Technician_Save_Logs.Location);
            CommandCenter.Technician.Buttons.KeepCanOn.UpdateOriginalPositions(Technician_CheckBox_KeepCanOnline.Location);
            CommandCenter.Technician.Buttons.ClearAfterSend.UpdateOriginalPositions(Technician_CheckBox_ClearAfterSend.Location);
            CommandCenter.Technician.Buttons.SimulateModes.UpdateOriginalPositions(Technician_ChrckBox_SimulateModes.Location);
            CommandCenter.Technician.Buttons.SendConfig.UpdateOriginalPositions(Technician_Button_SendOnce.Location);
            CommandCenter.Technician.Buttons.Vehicle.UpdateOriginalPositions(Technician_Module_Vehicle.Location);
            CommandCenter.Technician.Buttons.WeightStation.UpdateOriginalPositions(Technician_Module_WeightStation.Location);
            CommandCenter.Technician.Buttons.SortingStation.UpdateOriginalPositions(Technician_Module_SortingStation.Location);
            CommandCenter.Technician.Buttons.TechMode.UpdateOriginalPositions(Technician_Button_StartStop.Location);
        }

        private void Tab_Operation_Resize(object sender, EventArgs e)
        {
            DelayBeforeTurningBackOnUpdates = 5;
            CommandCenter.Operation.Buttons.ClearTerminal.UpdateOriginalPositions(Operation_Terminal_Clear.Location);

            CommandCenter.Operation.Buttons.EmergencyStop.UpdateOriginalPositions(Operation_EmergencyStop.Location);
            CommandCenter.Operation.Buttons.Global.UpdateOriginalPositions(Operation_Module_Global.Location);
            CommandCenter.Operation.Buttons.Pause.UpdateOriginalPositions(Operation_Pause.Location);
            CommandCenter.Operation.Buttons.Vehicle.UpdateOriginalPositions(Operation_Module_Vehicle.Location);
            CommandCenter.Operation.Buttons.WeightStation.UpdateOriginalPositions(Operation_Module_WeightStation.Location);
            CommandCenter.Operation.Buttons.SortingStation.UpdateOriginalPositions(Operation_Module_SortingStation.Location);
            CommandCenter.Operation.Buttons.SaveOperationTerminal.UpdateOriginalPositions(Operation_Save_Logs.Location);
            CommandCenter.Operation.Buttons.Disc.UpdateOriginalPositions(Operation_Disc_Color.Location);

            CommandCenter.Operation.Overview.Vehicle.UpdateOriginalPositions(Overview_Vehicle.Location);
            CommandCenter.Operation.Overview.WeightStation.UpdateOriginalPositions(Overview_WeightStation.Location);
            CommandCenter.Operation.Overview.SortingStation.UpdateOriginalPositions(Overview_SortingStation.Location);
        }

        private void Tab_Terminal_Resize(object sender, EventArgs e)
        {
            DelayBeforeTurningBackOnUpdates = 5;
            CommandCenter.Buttons.Terminal.UpdateOriginalPositions(Button_Terminal.Location);
            CommandCenter.Buttons.CloseBeagle.UpdateOriginalPositions(Button_CloseBeagleBone.Location);
            CommandCenter.Buttons.SaveBBBTerminal.UpdateOriginalPositions(Button_Save_Terminal.Location);
        }
        private void Tab_Calibration_Resize(object sender, EventArgs e)
        {
            DelayBeforeTurningBackOnUpdates = 5;
            CommandCenter.Calibration.Buttons.Calibration.UpdateOriginalPositions(Calibration_Button_StartStop.Location);
            CommandCenter.Calibration.Buttons.ClearTerminal.UpdateOriginalPositions(Calibration_Clear_Logs.Location);
            CommandCenter.Calibration.Buttons.SaveTerminal.UpdateOriginalPositions(Calibration_Save_Logs.Location);
            CommandCenter.Calibration.Buttons.Global.UpdateOriginalPositions(Calibration_Module_All.Location);
            CommandCenter.Calibration.Buttons.SortingStation.UpdateOriginalPositions(Calibration_Module_Sorting.Location);
            CommandCenter.Calibration.Buttons.Vehicle.UpdateOriginalPositions(Calibration_Module_Vehicle.Location);
            CommandCenter.Calibration.Buttons.WeightStation.UpdateOriginalPositions(Calibration_Module_Weight.Location);
        }
        private void Tab_Maintenance_Resize(object sender, EventArgs e)
        {
            DelayBeforeTurningBackOnUpdates = 5;
            CommandCenter.Maintenance.Buttons.Maintenance.UpdateOriginalPositions(Maintenance_Button_StartStop.Location);
            CommandCenter.Maintenance.Buttons.ClearTerminal.UpdateOriginalPositions(Maintenance_Clear_Logs.Location);
            CommandCenter.Maintenance.Buttons.SaveTerminal.UpdateOriginalPositions(Maintenance_Save_Logs.Location);
            CommandCenter.Maintenance.Buttons.Global.UpdateOriginalPositions(Maintenance_Module_All.Location);
            CommandCenter.Maintenance.Buttons.SortingStation.UpdateOriginalPositions(Maintenance_Module_Sorting.Location);
            CommandCenter.Maintenance.Buttons.Vehicle.UpdateOriginalPositions(Maintenance_Module_Vehicle.Location);
            CommandCenter.Maintenance.Buttons.WeightStation.UpdateOriginalPositions(Maintenance_Module_Weight.Location);
        }
        private void Tab_Settings_Resize(object sender, EventArgs e)
        {
            DelayBeforeTurningBackOnUpdates = 5;
            CommandCenter.Buttons.Link.UpdateOriginalPositions(Button_Link.Location);
            CommandCenter.Buttons.AutoConnection.UpdateOriginalPositions(Button_AutoConnect.Location);
        }
        #endregion Individual_Tab_Resises
        //#############################################################//
        /// <summary>
        /// Will update all the buttons which are not inside a TAB
        /// with a new original position
        /// </summary>
        //#############################################################//
        private void UpdateAllButtonsPosition()
        {
            #region Universal
            CommandCenter.Buttons.Mode.UpdateOriginalPositions(Button_Mode.Location);
            CommandCenter.Buttons.USB.UpdateOriginalPositions(Button_USB.Location);
            #endregion Universal
            /*
            #region Index_Settings
            CommandCenter.Buttons.Link.UpdateOriginalPositions(Button_Link.Location);
            CommandCenter.Buttons.AutoConnection.UpdateOriginalPositions(Button_AutoConnect.Location);
            #endregion Index_Settings
            #region Index_Terminal
            CommandCenter.Buttons.Terminal.UpdateOriginalPositions(Button_Terminal.Location);
            CommandCenter.Buttons.CloseBeagle.UpdateOriginalPositions(Button_CloseBeagleBone.Location);
            CommandCenter.Buttons.SaveBBBTerminal.UpdateOriginalPositions(Button_Save_Terminal.Location);
            #endregion Index_Terminal
            #region Index_Operation
            CommandCenter.Operation.Buttons.ClearTerminal.UpdateOriginalPositions(Operation_Terminal_Clear.Location);

            CommandCenter.Operation.Buttons.EmergencyStop.UpdateOriginalPositions(Operation_EmergencyStop.Location);
            CommandCenter.Operation.Buttons.Global.UpdateOriginalPositions(Operation_Module_Global.Location);
            CommandCenter.Operation.Buttons.Pause.UpdateOriginalPositions(Operation_Pause.Location);
            CommandCenter.Operation.Buttons.Vehicle.UpdateOriginalPositions(Operation_Module_Vehicle.Location);
            CommandCenter.Operation.Buttons.WeightStation.UpdateOriginalPositions(Operation_Module_WeightStation.Location);
            CommandCenter.Operation.Buttons.SortingStation.UpdateOriginalPositions(Operation_Module_SortingStation.Location);
            CommandCenter.Operation.Buttons.SaveOperationTerminal.UpdateOriginalPositions(Operation_Save_Logs.Location);
            CommandCenter.Operation.Buttons.Disc.UpdateOriginalPositions(Operation_Disc_Color.Location);

            CommandCenter.Operation.Overview.Vehicle.UpdateOriginalPositions(Overview_Vehicle.Location);
            CommandCenter.Operation.Overview.WeightStation.UpdateOriginalPositions(Overview_WeightStation.Location);
            CommandCenter.Operation.Overview.SortingStation.UpdateOriginalPositions(Overview_SortingStation.Location);
            #endregion Index_Operation
            #region Index_Technician
            
            CommandCenter.Technician.Buttons.ClearTerminal.UpdateOriginalPositions(Technician_terminal_Clear.Location);
            CommandCenter.Technician.Buttons.SaveTerminal.UpdateOriginalPositions(Technician_Save_Logs.Location);
            CommandCenter.Technician.Buttons.KeepCanOn.UpdateOriginalPositions(Technician_CheckBox_KeepCanOnline.Location);
            CommandCenter.Technician.Buttons.ClearAfterSend.UpdateOriginalPositions(Technician_CheckBox_ClearAfterSend.Location);
            CommandCenter.Technician.Buttons.SimulateModes.UpdateOriginalPositions(Technician_ChrckBox_SimulateModes.Location);
            CommandCenter.Technician.Buttons.SendConfig.UpdateOriginalPositions(Technician_Button_SendOnce.Location);
            CommandCenter.Technician.Buttons.Vehicle.UpdateOriginalPositions(Technician_Module_Vehicle.Location);
            CommandCenter.Technician.Buttons.WeightStation.UpdateOriginalPositions(Technician_Module_WeightStation.Location);
            CommandCenter.Technician.Buttons.SortingStation.UpdateOriginalPositions(Technician_Module_SortingStation.Location);
            CommandCenter.Technician.Buttons.TechMode.UpdateOriginalPositions(Technician_Button_StartStop.Location);
            
            BRS.Debug.Comment(Technician_Button_StartStop.Location.ToString());
            #endregion Index_Technician
            */
        }
    }
}
