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
using System.Xml;
using BRS;
using BRS.Buttons;
using System.Configuration;
using System.Collections.Specialized;

namespace CommandCenter
{
    public partial class Form_MainMenu : Form
    {
        #region Variables
        #endregion Variables
        #region Enums
        #endregion Enums
        #region Buttons
        #region Updates
        //#############################################################//
        /// <summary>
        /// Used to update the technician button when wanted.
        /// This changes it's state mostly
        /// </summary>
        //#############################################################//
        public void Technician_UpdateButton()
        {
            if(BRS.ComPort.Port.IsOpen)
            {
                if(MasterProtocol.isActive)
                {
                    if(MasterProtocol.mode == Modes_Ref.emergencyStop)
                    {
                        Technician.Emergency(this);
                    }
                    else
                    {
                        if(Technician.InEmergency)
                        {
                            Technician.InEmergency = false;
                            Technician.Close(this);
                        }

                        if(MasterProtocol.mode != Modes_Ref.testing)
                        {
                            if(Technician.isActive)
                            {
                                Technician.Close(this);
                                NewUserTextInfo(UserInfos.Technician.unexpectedTermination,2);
                            }
                            CommandCenter.Technician.Buttons.TechMode.State = ControlState.Inactive;
                        }
                        else
                        {
                            CommandCenter.Technician.Buttons.TechMode.State = ControlState.Active;
                        }
                    }
                }
                else
                {
                    if (Technician.InEmergency)
                    {
                        Technician.Close(this);
                    }
                    if (Technician.isActive)
                    {
                        Technician.Close(this);
                    }
                    CommandCenter.Technician.Buttons.TechMode.State = ControlState.Warning;
                }
            }
            else
            {
                CommandCenter.Technician.Buttons.TechMode.State = ControlState.Disabled;
                if(Technician.isActive)
                {
                    Technician.Close(this);
                }
                if (Technician.InEmergency)
                {
                    Technician.Close(this);
                }
            }
        }
        //#############################################################//
        /// <summary>
        /// Updates the SendConfig button whenever the latter changes
        /// </summary>
        //#############################################################//
        public void Technician_Confirm_SendConfig()
        {
            if(Technician.SendConfig)
            {
                Technician.SendConfig = false;
                CommandCenter.Technician.Buttons.SendConfig.State = ControlState.Inactive;
                Technician_Label_SendOnce.ForeColor = ControlStateColors.Inactive;
                NewUserTextInfo(UserInfos.Technician.configSent, 1);

                Technician.MasterProtolStaysOn = false;
                CommandCenter.Technician.Buttons.KeepCanOn.State = ControlState.Inactive;
                Technician_Label_KeepCanOn.ForeColor = ControlStateColors.Inactive;

                CommandCenter.Technician.terminal.Log_Comment(LogsInfos.Technician.HasSentOnce, ControlStateColors.Active);
                // CLEAR CONFIG IF ENABLED
                if(Technician.ClearAfterSendingConfig)
                {
                    Technician_Reset_DropDown();
                }
            }
        }
        #endregion Updates
        #region Clicks
        //#############################################################//
        /// <summary>
        /// Called each time the tech button is pressed inside of the
        /// Tab_Technician
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_Button_StartStop_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Parsing the request for technician mode");

            if(BRS.ComPort.Port.IsOpen)
            {
                if(MasterProtocol.isActive)
                {
                    //-------------------------------------------------//
                    // Tech mode is active // Close it
                    //-------------------------------------------------//
                    if(Technician.isActive)
                    {
                        if (SetGlobalModeTo(WantedMode.Paused))
                        {
                            Technician.Close(this);
                            Debug.Success("Technician has closed");
                            NewUserTextInfo(UserInfos.Technician.userStopped, 1);
                        }
                        else
                        {
                            Debug.Aborted("Technician is kept ON");
                        }
                    }
                    //-------------------------------------------------//
                    // Tech mode is disabled // Open it
                    //-------------------------------------------------//
                    else
                    {
                        if (SetGlobalModeTo(WantedMode.Testing))
                        {
                            Technician.Open(this);
                            NewUserTextInfo(UserInfos.Technician.hasStarted,1);
                        }
                        else
                        {
                            Debug.Aborted("Technician is kept OFF");
                        }
                    }
                }
                else
                {
                    NewUserTextInfo(UserInfos.MasterProtocol.IsOffline, 2);
                }
            }
            else
            {
                NewUserTextInfo(UserInfos.ComPort.IsOffline,2);
            }

            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Executed each time you want to save the logs stored in the
        /// technician Tab
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_Save_Logs_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Attempting to save the technician's logs");
            CommandCenter.Technician.terminal.SaveTerminal();
            NewUserTextInfo(UserInfos.Terminal.Saved, 1);
            Debug.Success();
            CommandCenter.Technician.terminal.Clear();
            BRS.Debug.Header(false);
        }

        //#############################################################//
        /// <summary>
        /// Clears the terminal present inside of the Technician Mode
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_terminal_Clear_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Attempting to clear the terminal");
            CommandCenter.Technician.terminal.Clear();

            if (CommandCenter.Technician.terminal.Window.Text == "")
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
        /// Function called when you click on the checkbox used to start
        /// or stop simulating modes
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_ChrckBox_SimulateModes_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            if(Technician.isActive)
            {
                if(Technician.SimulateModes)
                {
                    Technician.SimulateModes = false;
                    CommandCenter.Technician.Buttons.SimulateModes.State = ControlState.Inactive;
                    Technician_Label_SimulateModes.ForeColor = ControlStateColors.Inactive;
                    Technician_Label_Mode.ForeColor          = ControlStateColors.Disabled;

                    Technician_DropDown_Modes.Enabled = false;
                    Technician_DropDown_Modes.SelectedIndex = 2;
                    Technician.SelectedIndexes.Mode = 2;
                    NewUserTextInfo(UserInfos.Technician.stoppedSimulatingModes, 1);
                    CommandCenter.Technician.terminal.Log_Comment(LogsInfos.Technician.NoLongerSimulatingModes, ControlStateColors.Warning);
                }
                else
                {
                    Technician.SimulateModes = true;
                    CommandCenter.Technician.Buttons.SimulateModes.State = ControlState.Active;
                    Technician_Label_SimulateModes.ForeColor = ControlStateColors.Active;
                    Technician_DropDown_Modes.Enabled = true;
                    Technician_DropDown_Modes.SelectedIndex = 2;
                    Technician.SelectedIndexes.Mode = 2;
                    Technician_Label_Mode.ForeColor = ControlStateColors.Active;
                    NewUserTextInfo(UserInfos.Technician.nowSimulatingModes, 1);
                    CommandCenter.Technician.terminal.Log_Comment(LogsInfos.Technician.NowSimulatingModes, ControlStateColors.Active);
                }
            }
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Flips checkbox state of the keepCanOnline which enables the
        /// whole can network to stay ON.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_CheckBox_KeepCanOnline_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            if (Technician.isActive)
            {
                if (Technician.MasterProtolStaysOn)
                {
                    // Update that button and labels colors
                    Technician.MasterProtolStaysOn = false;
                    CommandCenter.Technician.Buttons.KeepCanOn.State = ControlState.Inactive;
                    Technician_Label_KeepCanOn.ForeColor = ControlStateColors.Inactive;
                    NewUserTextInfo(UserInfos.Technician.stoppedKeepingCanON, 1);

                    // Update related buttons states in order to 
                    Technician.SendConfig = false;
                    Technician.ClearAfterSendingConfig = false;
                    CommandCenter.Technician.Buttons.SendConfig.State = ControlState.Inactive;
                    CommandCenter.Technician.Buttons.ClearAfterSend.State = ControlState.Inactive;
                    Technician_Label_SendOnce.ForeColor = ControlStateColors.Inactive;
                    Technician_Label_ClearAfterSend.ForeColor = ControlStateColors.Inactive;
                    CommandCenter.Technician.terminal.Log_Comment(LogsInfos.Technician.NoLongerSendingConstantly, ControlStateColors.Active);
                }
                else
                {
                    Technician.MasterProtolStaysOn = true;
                    CommandCenter.Technician.Buttons.KeepCanOn.State = ControlState.Active;
                    Technician_Label_KeepCanOn.ForeColor = ControlStateColors.Active;
                    NewUserTextInfo(UserInfos.Technician.nowKeepingCanOn, 1);

                    // Update related buttons states in order to 
                    Technician.SendConfig = false;
                    Technician.ClearAfterSendingConfig = false;
                    CommandCenter.Technician.Buttons.SendConfig.State = ControlState.Disabled;
                    CommandCenter.Technician.Buttons.ClearAfterSend.State = ControlState.Disabled;
                    Technician_Label_SendOnce.ForeColor = ControlStateColors.Disabled;
                    Technician_Label_ClearAfterSend.ForeColor = ControlStateColors.Disabled;
                    CommandCenter.Technician.terminal.Log_Comment(LogsInfos.Technician.NowSendingConstantly, ControlStateColors.Warning);
                }
            }
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Flip the state of the checkbox used for keeping config
        /// between sends of individual stuff
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_CheckBox_ClearAfterSend_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            if (Technician.isActive)
            {
                if (Technician.ClearAfterSendingConfig)
                {
                    Technician.ClearAfterSendingConfig = false;
                    CommandCenter.Technician.Buttons.ClearAfterSend.State = ControlState.Inactive;
                    Technician_Label_ClearAfterSend.ForeColor = ControlStateColors.Inactive;

                    NewUserTextInfo(UserInfos.Technician.stoppedConstantSending, 1);
                    CommandCenter.Technician.terminal.Log_Comment(LogsInfos.Technician.NoLongerClearingConfig, ControlStateColors.Active);

                }
                else
                {
                    Technician.ClearAfterSendingConfig = true;
                    CommandCenter.Technician.Buttons.ClearAfterSend.State = ControlState.Active;
                    Technician_Label_ClearAfterSend.ForeColor = ControlStateColors.Active;

                    NewUserTextInfo(UserInfos.Technician.nowClearingConfigAfterSending, 1);
                    CommandCenter.Technician.terminal.Log_Comment(LogsInfos.Technician.NowClearingConfigWhenSending, ControlStateColors.Warning);
                }
            }
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// The protocol will send 1 tram each time this is pressed while
        /// in Debug mode
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_Button_SendOnce_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            if (Technician.isActive)
            {
                if (!Technician.SendConfig)
                {
                    Technician.SendConfig = true;
                    CommandCenter.Technician.Buttons.SendConfig.State = ControlState.Active;
                    Technician_Label_SendOnce.ForeColor = ControlStateColors.Active;
                    NewUserTextInfo(UserInfos.Technician.configSending, 1);

                    //Update correlating buttons
                    Technician.MasterProtolStaysOn = false;
                    CommandCenter.Technician.Buttons.KeepCanOn.State = ControlState.Disabled;
                    Technician_Label_KeepCanOn.ForeColor = ControlStateColors.Disabled;
                }
                /*
                else
                {
                    Technician.SendConfiguration = true;
                    CommandCenter.Technician.Buttons.KeepCanOn.State = ControlState.Active;
                    Technician_Label_KeepCanOn.ForeColor = ControlStateColors.Active;

                    NewUserTextInfo(UserInfos.Technician.nowSimulatingModes, 1);
                }
                */
            }
            BRS.Debug.Header(false);
        }

        //#############################################################//
        /// <summary>
        /// Function executed when the user clicks on the Sorting
        /// Station's module icon located inside of the Technician tab
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_Module_SortingStation_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);

            BRS.Debug.Comment("Calling operation sorting station clicks...");
            Operation_Module_SortingStation_Click(sender,e);
            Debug.Success();

            if (BRS.PopUp.Question(PopUpInfos.Technician.DoYouWantToPrintInfo, PopUpInfos.Header.Warning))
            {
                if (BRS.PopUp.UserWarning(PopUpInfos.Technician.DoYouWantToSaveInstead, PopUpInfos.Header.Warning))
                {
                    CommandCenter.Technician.terminal.SaveTerminal();
                }

                CommandCenter.Technician.terminal.Clear();
                BRS.Debug.Comment("Logging all of the Sorting Station's data");
                ModuleData_SortingStation.LogAllIn(CommandCenter.Technician.terminal);
            }

            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Function executed when the user clicks on the Vehicle's icon
        /// located inside of the Technician Tab
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_Module_Vehicle_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);

            BRS.Debug.Comment("Calling operation module vehicle clicks...");
            Operation_Module_Vehicle_Click(sender, e);
            Debug.Success();

            if (BRS.PopUp.Question(PopUpInfos.Technician.DoYouWantToPrintInfo, PopUpInfos.Header.Warning))
            {
                if(BRS.PopUp.UserWarning(PopUpInfos.Technician.DoYouWantToSaveInstead,PopUpInfos.Header.Warning))
                {
                    CommandCenter.Technician.terminal.SaveTerminal();
                }

                CommandCenter.Technician.terminal.Clear();
                BRS.Debug.Comment("Logging all of the Vehicle's data");
                ModuleData_Vehicle.LogAllIn(CommandCenter.Technician.terminal);
            }

            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Function executed when the user clicks on the WeightStation
        /// module icon located insied of the technician tab
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_Module_WeightStation_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);

            BRS.Debug.Comment("Calling operation module weightstation clicks...");
            Operation_Module_WeightStation_Click(sender, e);
            Debug.Success();

            if (BRS.PopUp.Question(PopUpInfos.Technician.DoYouWantToPrintInfo, PopUpInfos.Header.Warning))
            {
                if (BRS.PopUp.UserWarning(PopUpInfos.Technician.DoYouWantToSaveInstead, PopUpInfos.Header.Warning))
                {
                    CommandCenter.Technician.terminal.SaveTerminal();
                }

                CommandCenter.Technician.terminal.Clear();
                BRS.Debug.Comment("Logging all of the Weight Station's data");
                ModuleData_WeightStation.LogAllIn(CommandCenter.Technician.terminal);
            }

            BRS.Debug.Header(false);
        }
        #endregion Clicks
        #endregion Buttons
        #region Inits
        //#############################################################//
        /// <summary>
        /// Function called inside the form's constructor to initialise
        /// dropdowns as if tech mode is disabled
        /// </summary>
        //#############################################################//
        public void Technician_Initialise()
        {
            BRS.Debug.Header(true);
            #region DropDown
            BRS.Debug.Comment("Initialising dropdowns inside the Technician tab");

            BRS.Debug.Comment("initialising data sources...");
            Technician_DropDown_Modes.DataSource = new BindingSource(ListsInfos.EmptyData, null);
            Technician_DropDown_Status.DataSource = new BindingSource(ListsInfos.EmptyData, null);
            Technician_DropDown_DataTypeA.DataSource = new BindingSource(ListsInfos.EmptyData, null);
            Technician_DropDown_DataTypeB.DataSource = new BindingSource(ListsInfos.EmptyData, null);
            Technician_DropDown_DataA.DataSource = new BindingSource(ListsInfos.EmptyData, null);
            Technician_DropDown_DataB.DataSource = new BindingSource(ListsInfos.EmptyData, null);

            BRS.Debug.Comment("initialising display members as Values");
            Technician_DropDown_Modes.DisplayMember = "Value";
            Technician_DropDown_Status.DisplayMember = "Value";
            Technician_DropDown_DataTypeA.DisplayMember = "Value";
            Technician_DropDown_DataTypeB.DisplayMember = "Value";
            Technician_DropDown_DataA.DisplayMember = "Value";
            Technician_DropDown_DataB.DisplayMember = "Value";

            BRS.Debug.Comment("initialising value members as Keys");
            Technician_DropDown_Modes.ValueMember = "Key";
            Technician_DropDown_Status.ValueMember = "Key";
            Technician_DropDown_DataTypeA.ValueMember = "Key";
            Technician_DropDown_DataTypeB.ValueMember = "Key";
            Technician_DropDown_DataA.ValueMember = "Key";
            Technician_DropDown_DataB.ValueMember = "Key";

            BRS.Debug.Comment("Disabling dropdowns");
            Technician_DropDown_Modes.Enabled = false;
            Technician_DropDown_Status.Enabled = false;
            Technician_DropDown_DataTypeA.Enabled = false;
            Technician_DropDown_DataTypeB.Enabled = false;
            Technician_DropDown_DataA.Enabled = false;
            Technician_DropDown_DataB.Enabled = false;

            BRS.Debug.Comment("putting disabled color ot all labels");
            Technician_Label_SimulateModes.ForeColor = ControlStateColors.Active;
            Technician_Label_SendOnce.ForeColor = ControlStateColors.Active;
            Technician_Label_KeepCanOn.ForeColor = ControlStateColors.Active;
            Technician_Label_ClearAfterSend.ForeColor = ControlStateColors.Active;

            Technician_Label_Status.ForeColor = ControlStateColors.Active;
            Technician_Label_Mode.ForeColor = ControlStateColors.Active;
            Technician_Label_DataTypeA.ForeColor = ControlStateColors.Active;
            Technician_Label_DataTypeB.ForeColor = ControlStateColors.Active;
            Technician_Label_DataA.ForeColor = ControlStateColors.Active;
            Technician_Label_DataB.ForeColor = ControlStateColors.Active;

            Debug.Success("Drop downs successfully initialised");
            #endregion DropDown
            #region Buttons
            BRS.Debug.Comment("Initialising generic buttons used in tech mode");
            CommandCenter.Technician.Buttons.ClearTerminal = new GenericButton(Technician_terminal_Clear, Icons.Terminal.GetStatesColors(), Icons.Terminal.GetStatesBitmaps());
            CommandCenter.Technician.Buttons.SaveTerminal = new GenericButton(Technician_Save_Logs, Icons.Save.GetStatesColors(), Icons.Save.GetStatesBitmaps());
            CommandCenter.Technician.Buttons.KeepCanOn = new GenericButton(Technician_CheckBox_KeepCanOnline, Icons.CheckBox.GetStatesColors(), Icons.CheckBox.GetStatesBitmaps());
            CommandCenter.Technician.Buttons.ClearAfterSend = new GenericButton(Technician_CheckBox_ClearAfterSend, Icons.CheckBox.GetStatesColors(), Icons.CheckBox.GetStatesBitmaps());
            CommandCenter.Technician.Buttons.SimulateModes = new GenericButton(Technician_ChrckBox_SimulateModes, Icons.CheckBox.GetStatesColors(), Icons.CheckBox.GetStatesBitmaps());
            CommandCenter.Technician.Buttons.SendConfig = new GenericButton(Technician_Button_SendOnce, Icons.CheckBox.GetStatesColors(), Icons.CheckBox.GetStatesBitmaps());
            CommandCenter.Technician.Buttons.Vehicle = new GenericButton(Technician_Module_Vehicle, Icons.Vehicle.GetStatesColors(), Icons.Vehicle.GetStatesBitmaps());
            CommandCenter.Technician.Buttons.WeightStation = new GenericButton(Technician_Module_WeightStation, Icons.Balance.GetStatesColors(), Icons.Balance.GetStatesBitmaps());
            CommandCenter.Technician.Buttons.SortingStation = new GenericButton(Technician_Module_SortingStation, Icons.Sorting.GetStatesColors(), Icons.Sorting.GetStatesBitmaps());
            CommandCenter.Technician.Buttons.TechMode = new GenericButton(Technician_Button_StartStop, Icons.Tech.GetStatesColors(), Icons.Tech.GetStatesBitmaps());

            CommandCenter.Technician.Buttons.ClearTerminal.Animated = true;
            CommandCenter.Technician.Buttons.SaveTerminal.Animated = true;
            CommandCenter.Technician.Buttons.KeepCanOn.Animated = true;
            CommandCenter.Technician.Buttons.ClearAfterSend.Animated = true;
            CommandCenter.Technician.Buttons.SimulateModes.Animated = true;
            CommandCenter.Technician.Buttons.SendConfig.Animated = true;
            CommandCenter.Technician.Buttons.Vehicle.Animated = true;
            CommandCenter.Technician.Buttons.WeightStation.Animated = true;
            CommandCenter.Technician.Buttons.SortingStation.Animated = true;
            CommandCenter.Technician.Buttons.TechMode.Animated = true;

            CommandCenter.Technician.Buttons.ClearTerminal.State = ControlState.Inactive;
            CommandCenter.Technician.Buttons.SaveTerminal.State = ControlState.Inactive;
            CommandCenter.Technician.Buttons.KeepCanOn.State = ControlState.Disabled;
            CommandCenter.Technician.Buttons.ClearAfterSend.State = ControlState.Disabled;
            CommandCenter.Technician.Buttons.SimulateModes.State = ControlState.Disabled;
            CommandCenter.Technician.Buttons.SendConfig.State = ControlState.Disabled;
            CommandCenter.Technician.Buttons.Vehicle.State = ControlState.Disabled;
            CommandCenter.Technician.Buttons.WeightStation.State = ControlState.Disabled;
            CommandCenter.Technician.Buttons.SortingStation.State = ControlState.Disabled;
            CommandCenter.Technician.Buttons.TechMode.State = ControlState.Disabled;

            Technician.Close(this);
            Debug.Success();
            #endregion Buttons
            BRS.Debug.Header(false);
        }
        #endregion Inits
        #region Updates
        #region DropDowns
        private void Technician_DropDown_Modes_SelectionChangeCommitted(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Updating selected index inside technician class");
            Technician.SelectedIndexes.Mode = Technician_DropDown_Modes.SelectedIndex;
            BRS.Debug.Comment("Selected index is now: " + Technician.SelectedIndexes.Mode.ToString());
            BRS.Debug.Header(false);
        }

        private void Technician_DropDown_Status_SelectionChangeCommitted(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Updating selected index inside technician class");
            Technician.SelectedIndexes.State = Technician_DropDown_Status.SelectedIndex;
            BRS.Debug.Comment("Selected index is now: " + Technician.SelectedIndexes.State.ToString());
            BRS.Debug.Header(false);
        }

        private void Technician_DropDown_DataTypeA_SelectionChangeCommitted(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Updating selected index inside technician class");
            Technician.SelectedIndexes.DataTypeA = Technician_DropDown_DataTypeA.SelectedIndex;
            if (Technician.SelectedIndexes.DataTypeA == 0)
            {
                Technician_DropDown_DataA.DataSource = new BindingSource(ListsInfos.EmptyData, null);
            }

            if (Technician.SelectedIndexes.DataTypeA == 1)
            {
                Technician_DropDown_DataA.DataSource = new BindingSource(ListsInfos.Commands, null);
            }

            if (Technician.SelectedIndexes.DataTypeA == 2)
            {
                Technician_DropDown_DataA.DataSource = new BindingSource(ListsInfos.Values, null);
            }

            if (Technician.SelectedIndexes.DataTypeA == 3)
            {
                Technician_DropDown_DataA.DataSource = new BindingSource(ListsInfos.States, null);
            }
            BRS.Debug.Comment("Selected index is now: " + Technician.SelectedIndexes.DataTypeA.ToString());
            BRS.Debug.Header(false);
        }

        private void Technician_DropDown_DataA_SelectionChangeCommitted(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Updating selected index inside technician class");
            Technician.SelectedIndexes.DataA = Technician_DropDown_DataA.SelectedIndex;
            BRS.Debug.Comment("Selected index is now: " + Technician.SelectedIndexes.DataA.ToString());
            BRS.Debug.Header(false);
        }

        private void Technician_DropDown_DataTypeB_SelectionChangeCommitted(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Updating selected index inside technician class");
            Technician.SelectedIndexes.DataTypeB = Technician_DropDown_DataTypeB.SelectedIndex;
            if (Technician.SelectedIndexes.DataTypeB == 0)
            {
                Technician_DropDown_DataB.DataSource = new BindingSource(ListsInfos.EmptyData, null);
            }

            if (Technician.SelectedIndexes.DataTypeB == 1)
            {
                Technician_DropDown_DataB.DataSource = new BindingSource(ListsInfos.Commands, null);
            }

            if (Technician.SelectedIndexes.DataTypeB == 2)
            {
                Technician_DropDown_DataB.DataSource = new BindingSource(ListsInfos.Values, null);
            }

            if (Technician.SelectedIndexes.DataTypeB == 3)
            {
                Technician_DropDown_DataB.DataSource = new BindingSource(ListsInfos.States, null);
            }
            BRS.Debug.Comment("Selected index is now: " + Technician.SelectedIndexes.DataTypeB.ToString());
            BRS.Debug.Header(false);
        }

        private void Technician_DropDown_DataB_SelectionChangeCommitted(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Updating selected index inside technician class");
            Technician.SelectedIndexes.DataB = Technician_DropDown_DataB.SelectedIndex;
            BRS.Debug.Comment("Selected index is now: " + Technician.SelectedIndexes.DataB.ToString());
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Function handling the DataA available dropdown.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_DropDown_DataTypeA_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        //#############################################################//
        /// <summary>
        /// Function handling the DataB available dropdown.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Technician_DropDown_DataTypeB_SelectedIndexChanged(object sender, EventArgs e)
        {
        }
        //#############################################################//
        /// <summary>
        /// Parses the dropdowns into a CAN tram
        /// </summary>
        //#############################################################//
        public void Technician_BuildDropDown()
        {
            Technician.charA = 77;
            Technician.charB = Convert.ToByte(Technician.SelectedIndexes.Mode);

            if(Technician.SelectedIndexes.DataTypeA == 0)
            {
                Technician.charC = 0;
                Technician.charD = 0;
            }
            else
            {
                if(Technician.SelectedIndexes.DataTypeA == 1)
                {
                    Technician.charC = Convert.ToByte('C');
                    Technician.charD = Convert.ToByte(Technician.SelectedIndexes.DataA);
                }
                if (Technician.SelectedIndexes.DataTypeA == 2)
                {
                    Technician.charC = Convert.ToByte('V');
                    Technician.charD = Convert.ToByte(Technician.SelectedIndexes.DataA);
                }
                if (Technician.SelectedIndexes.DataTypeA == 3)
                {
                    Technician.charC = Convert.ToByte('S');
                    Technician.charD = Convert.ToByte(Technician.SelectedIndexes.DataA);
                }
            }

            if (Technician.SelectedIndexes.DataTypeB == 0)
            {
                Technician.charE = 0;
                Technician.charF = 0;
            }
            else
            {
                if (Technician.SelectedIndexes.DataTypeB == 1)
                {
                    Technician.charE = Convert.ToByte('C');
                    Technician.charF = Convert.ToByte(Technician.SelectedIndexes.DataB);
                }
                if (Technician.SelectedIndexes.DataTypeB == 2)
                {
                    Technician.charE = Convert.ToByte('V');
                    Technician.charF = Convert.ToByte(Technician.SelectedIndexes.DataB);
                }
                if (Technician.SelectedIndexes.DataTypeB == 3)
                {
                    Technician.charE = Convert.ToByte('S');
                    Technician.charF = Convert.ToByte(Technician.SelectedIndexes.DataB);
                }
            }

            Technician.charG = 83;
            Technician.charH = Convert.ToByte(Technician.SelectedIndexes.State);

            Technician_BuildCanVisualisation();
        }
        //#############################################################//
        /// <summary>
        /// Function called when Clear Config is enabled making it so
        /// the dropdowns reset to default states each time a config
        /// is sent once
        /// </summary>
        //#############################################################//
        public void Technician_Reset_DropDown()
        {
            Technician_DropDown_Modes.DataSource = new BindingSource(ListsInfos.Modes, null);
            Technician_DropDown_Status.DataSource = new BindingSource(ListsInfos.States, null);
            Technician_DropDown_DataTypeA.DataSource = new BindingSource(ListsInfos.DataTypes, null);
            Technician_DropDown_DataTypeB.DataSource = new BindingSource(ListsInfos.DataTypes, null);
            Technician_DropDown_DataA.DataSource = new BindingSource(ListsInfos.EmptyData, null);
            Technician_DropDown_DataB.DataSource = new BindingSource(ListsInfos.EmptyData, null);

            Technician.SelectedIndexes.Mode = 2;
            Technician.SelectedIndexes.State = 1;
            Technician.SelectedIndexes.DataTypeA = 0;
            Technician.SelectedIndexes.DataTypeB = 0;
            Technician.SelectedIndexes.DataA = 0;
            Technician.SelectedIndexes.DataB = 0;

            CommandCenter.Technician.terminal.Log_Comment(LogsInfos.Technician.ConfigCleared);
        }
        #endregion DropDowns
        #region TextBox_CanVisualisation
        static string oldResult = "";
        //#############################################################//
        /// <summary>
        /// This functions builds the CAN data visualisation as string
        /// and places it inside of the TextBox located inside of the
        /// Technician Tab.
        /// </summary>
        //#############################################################//
        public void Technician_BuildCanVisualisation()
        {
            string result = "";
            //---------------------------------------------------------// Build Address
            result = result + CAN_Addresses.TX.CommandCenter.ToString("X") + ",";
            //---------------------------------------------------------// Build Chars Mode
            result = result + (Convert.ToChar(Technician.charA)).ToString() + ",";
            result = result + Technician.charB.ToString("X") + ",";
            //---------------------------------------------------------// Build Data A
            if (Technician.charC == 0)
            {
                result = result + "0,0,";
            }
            else
            {
                result = result + (Convert.ToChar(Technician.charC)).ToString() + ",";
                result = result + Technician.charD.ToString("X") + ",";
            }
            //---------------------------------------------------------// Build Data B
            if (Technician.charE == 0)
            {
                result = result + "0,0,";
            }
            else
            {
                result = result + (Convert.ToChar(Technician.charE)).ToString() + ",";
                result = result + Technician.charF.ToString("X") + ",";
            }
            //---------------------------------------------------------// Build State
            result = result + (Convert.ToChar(Technician.charG)).ToString() + ",";
            result = result + Technician.charH.ToString("X");

            Technician_TextBox_CANData.Text = result;
            Technician.VisualizedCANData = result;
            
            // Log new CAN data if the latter changed
            if(oldResult != Technician.VisualizedCANData)
            {
                oldResult = Technician.VisualizedCANData;
                CommandCenter.Technician.terminal.Log_Comment(LogsInfos.Technician.DataChangedAnsIsNow + Technician.VisualizedCANData);
            }

        }
        //#############################################################//
        /// <summary>
        /// This function closes and updates the Technician CAN data
        /// visualisation.
        /// </summary>
        //#############################################################//
        public void Technician_Close_CanVisualisation()
        {
            Technician_TextBox_CANData.Enabled = false;
            Technician_TextBox_CANData.Text = UserInfos.Technician.CanVisualisationClosed;
            Technician_TextBox_CANData.ForeColor = ControlStateColors.Disabled;
            Technician_Label_CanOutput.ForeColor = ControlStateColors.Disabled;
        }
        //#############################################################//
        /// <summary>
        /// This function Opens and updates the Technician CAN data
        /// visualisation.
        /// </summary>
        //#############################################################//
        public void Technician_Open_CanVisualisation()
        {
            Technician_TextBox_CANData.Enabled = true;
            Technician_TextBox_CANData.Text = "";
            Technician_TextBox_CANData.ForeColor = ControlStateColors.Active;
            Technician_Label_CanOutput.ForeColor = ControlStateColors.Active;
        }
        //#############################################################//
        /// <summary>
        /// This function updates the Can Data visualisation of the
        /// Technician mode to be in Emergency mode
        /// </summary>
        //#############################################################//
        public void Technician_Emergency_CanVisualisation()
        {
            Technician_TextBox_CANData.Enabled = false;
            Technician_TextBox_CANData.Text = UserInfos.Technician.CanVisualisationInEmergency;
            Technician_TextBox_CANData.ForeColor = ControlStateColors.Error;
            Technician_Label_CanOutput.ForeColor = ControlStateColors.Error;
        }
        public void Technician_Emergency_CanVisualisation(Form_MainMenu Bruh)
        {
            Bruh.Technician_TextBox_CANData.Enabled = false;
            Bruh.Technician_TextBox_CANData.Text = UserInfos.Technician.CanVisualisationInEmergency;
            Bruh.Technician_TextBox_CANData.ForeColor = ControlStateColors.Error;
            Bruh.Technician_Label_CanOutput.ForeColor = ControlStateColors.Error;
        }
        #endregion TextBox_CanVisualisation
        #endregion Updates
        #region Classes
        //#############################################################//
        /// <summary>
        /// Class used to store all the data associated with the
        /// technician mode. This does not include GenericButtons tho.
        /// Nor Terminal classes, solely informations specific to
        /// the Technician Mode
        /// </summary>
        //#############################################################//
        public static class Technician
        {
            #region Dropdowns
            /// <summary>
            /// This classe holds a representation of the
            /// selected Index of dropdowns used to build the simulated
            /// tech CAN data. it is updated each time a selection is
            /// confirmed in a dropdown
            /// </summary>
            public static class SelectedIndexes
            {
                public static int Mode = 0;
                public static int State = 0;
                public static int DataTypeA = 0;
                public static int DataTypeB = 0;
                public static int DataA = 0;
                public static int DataB = 0;
            }
            #endregion Dropdowns
            #region Variables
            #region Sus
            /// <summary>
            /// Needed reference to the main form to get buttons or
            /// textbox from
            /// </summary>
            private static Form_MainMenu FormReference;
            /// <summary>
            /// means that there is a debug session going on.
            /// </summary>
            public static bool isActive = false;
            /// <summary>
            /// Says wether to close or not the MasterProtocol's
            /// timer after transmissions ends. This means that
            /// no receptions will occur after you click on
            /// Send Once
            /// </summary>
            public static bool MasterProtolStaysOn = false;
            /// <summary>
            /// If thisis set to false, modes wont be selectable
            /// and it will use the Technician mode by default.
            /// Simulating modes means faking Operations for example.
            /// </summary>
            public static bool SimulateModes = false;
            /// <summary>
            /// Used to send what is stored in dropdowns as the
            /// master data. This is used for SendOnce stuff
            /// </summary>
            public static bool SendConfig = false;
            /// <summary>
            /// Defines wether or not to keep continuously
            /// sending the configuration instead of clearing it
            /// each time.
            /// </summary>
            public static bool ClearAfterSendingConfig = false;
            /// <summary>
            /// Used to know if we previously were in an emergency protocol
            /// </summary>
            public static bool InEmergency = false;
            /// <summary>
            /// String which represent a fake, visualised for Debug, CAN
            /// tram that is built by the technician mode
            /// </summary>
            public static string VisualizedCANData = "NaN";
            #endregion Sus
            #region MasterProtocol
            public static byte charA = 77;
            public static byte charB = 0x01;
            public static byte charC = 0;
            public static byte charD = 0;
            public static byte charE = 0;
            public static byte charF = 0;
            public static byte charG = 83;
            public static byte charH = 0x01;
            #endregion MasterProtocol
            #endregion Variables
            #region Methods
            //#############################################################//
            /// <summary>
            /// Close the entirety of the Technician mode including
            /// dropdowns and buttons aswell as labels.
            /// </summary>
            //#############################################################//
            public static void Close(Form_MainMenu Bruh)
            {
                FormReference = Bruh;
                if (InEmergency)
                {
                    CommandCenter.Technician.terminal.Log_Warning(LogsInfos.Technician.ClosingForSafety);
                }

                BRS.Debug.Comment("Closing Technician mode");
                Bruh.Technician_DropDown_Modes.DataSource = new BindingSource(ListsInfos.EmptyData, null);
                Bruh.Technician_DropDown_Status.DataSource = new BindingSource(ListsInfos.EmptyData, null);
                Bruh.Technician_DropDown_DataTypeA.DataSource = new BindingSource(ListsInfos.EmptyData, null);
                Bruh.Technician_DropDown_DataTypeB.DataSource = new BindingSource(ListsInfos.EmptyData, null);
                Bruh.Technician_DropDown_DataA.DataSource = new BindingSource(ListsInfos.EmptyData, null);
                Bruh.Technician_DropDown_DataB.DataSource = new BindingSource(ListsInfos.EmptyData, null);

                BRS.Debug.Comment("Disabling dropdowns");
                Bruh.Technician_DropDown_Modes.Enabled = false;
                Bruh.Technician_DropDown_Status.Enabled = false;
                Bruh.Technician_DropDown_DataTypeA.Enabled = false;
                Bruh.Technician_DropDown_DataTypeB.Enabled = false;
                Bruh.Technician_DropDown_DataA.Enabled = false;
                Bruh.Technician_DropDown_DataB.Enabled = false;

                SelectedIndexes.Mode = 2;
                SelectedIndexes.State = 1;
                SelectedIndexes.DataTypeA = 0;
                SelectedIndexes.DataTypeB = 0;
                SelectedIndexes.DataA = 0;
                SelectedIndexes.DataB = 0;

                BRS.Debug.Comment("Disabling buttons");
                CommandCenter.Technician.Buttons.ClearTerminal.State = ControlState.Inactive;
                CommandCenter.Technician.Buttons.SaveTerminal.State = ControlState.Inactive;
                CommandCenter.Technician.Buttons.KeepCanOn.State = ControlState.Disabled;
                CommandCenter.Technician.Buttons.ClearAfterSend.State = ControlState.Disabled;
                CommandCenter.Technician.Buttons.SimulateModes.State = ControlState.Disabled;
                CommandCenter.Technician.Buttons.SendConfig.State = ControlState.Disabled;
                CommandCenter.Technician.Buttons.TechMode.State = ControlState.Inactive;

                BRS.Debug.Comment("Updating font colors");
                Bruh.Technician_Label_SimulateModes.ForeColor = ControlStateColors.Disabled;
                Bruh.Technician_Label_SendOnce.ForeColor = ControlStateColors.Disabled;
                Bruh.Technician_Label_KeepCanOn.ForeColor = ControlStateColors.Disabled;

                Bruh.Technician_Label_ClearAfterSend.ForeColor = ControlStateColors.Disabled;
                Bruh.Technician_Label_Status.ForeColor = ControlStateColors.Disabled;
                Bruh.Technician_Label_Mode.ForeColor = ControlStateColors.Disabled;
                Bruh.Technician_Label_DataTypeA.ForeColor = ControlStateColors.Disabled;
                Bruh.Technician_Label_DataTypeB.ForeColor = ControlStateColors.Disabled;
                Bruh.Technician_Label_DataA.ForeColor = ControlStateColors.Disabled;
                Bruh.Technician_Label_DataB.ForeColor = ControlStateColors.Disabled;

                InEmergency = false;
                isActive = false;
                SimulateModes = false;
                MasterProtolStaysOn = false;
                SendConfig = false;
                ClearAfterSendingConfig = false;

                // Only notify the user that they closed it if they actually did.
                if (!InEmergency)
                {
                    CommandCenter.Technician.terminal.Log_header(LogsInfos.Technician.userStopped);
                }
                Bruh.Technician_Close_CanVisualisation();

                Bruh.ModuleData_SortingStation.ResetReceivedData = true;
                Bruh.ModuleData_Vehicle.ResetReceivedData = true;
                Bruh.ModuleData_WeightStation.ResetReceivedData = true;
            }

            //#############################################################//
            /// <summary>
            /// Opens the technician mode and sets all the dropdowns
            /// and properties of the latter
            /// </summary>
            //#############################################################//
            public static void Open(Form_MainMenu Bruh)
            {
                FormReference = Bruh;
                BRS.Debug.Comment("Opening Technician mode");
                Bruh.Technician_DropDown_Modes.DataSource = new BindingSource(ListsInfos.Modes, null);
                Bruh.Technician_DropDown_Status.DataSource = new BindingSource(ListsInfos.States, null);
                Bruh.Technician_DropDown_DataTypeA.DataSource = new BindingSource(ListsInfos.DataTypes, null);
                Bruh.Technician_DropDown_DataTypeB.DataSource = new BindingSource(ListsInfos.DataTypes, null);
                Bruh.Technician_DropDown_DataA.DataSource = new BindingSource(ListsInfos.EmptyData, null);
                Bruh.Technician_DropDown_DataB.DataSource = new BindingSource(ListsInfos.EmptyData, null);

                BRS.Debug.Comment("Enabling dropdowns");
                Bruh.Technician_DropDown_Modes.Enabled = false;
                Bruh.Technician_DropDown_Status.Enabled = true;
                Bruh.Technician_DropDown_DataTypeA.Enabled = true;
                Bruh.Technician_DropDown_DataTypeB.Enabled = true;
                Bruh.Technician_DropDown_DataA.Enabled = true;
                Bruh.Technician_DropDown_DataB.Enabled = true;

                Bruh.Technician_DropDown_Modes.SelectedIndex = 2;
                Bruh.Technician_DropDown_Status.SelectedIndex = 1;
                Bruh.Technician_DropDown_DataTypeA.SelectedIndex = 0;
                Bruh.Technician_DropDown_DataTypeB.SelectedIndex = 0;
                Bruh.Technician_DropDown_DataA.SelectedIndex = 0;
                Bruh.Technician_DropDown_DataB.SelectedIndex = 0;

                SelectedIndexes.Mode = 2;
                SelectedIndexes.State = 1;
                SelectedIndexes.DataTypeA = 0;
                SelectedIndexes.DataTypeB = 0;
                SelectedIndexes.DataA = 0;
                SelectedIndexes.DataB = 0;

                BRS.Debug.Comment("Setting initial states of GenerButtons");
                CommandCenter.Technician.Buttons.ClearTerminal.State = ControlState.Active;
                CommandCenter.Technician.Buttons.SaveTerminal.State = ControlState.Active;
                CommandCenter.Technician.Buttons.KeepCanOn.State = ControlState.Inactive;
                CommandCenter.Technician.Buttons.ClearAfterSend.State = ControlState.Inactive;
                CommandCenter.Technician.Buttons.SimulateModes.State = ControlState.Inactive;
                CommandCenter.Technician.Buttons.SendConfig.State = ControlState.Inactive;
                CommandCenter.Technician.Buttons.TechMode.State = ControlState.Active;

                Bruh.Technician_Label_SimulateModes.ForeColor = ControlStateColors.Inactive;
                Bruh.Technician_Label_SendOnce.ForeColor = ControlStateColors.Inactive;
                Bruh.Technician_Label_KeepCanOn.ForeColor = ControlStateColors.Inactive;
                Bruh.Technician_Label_ClearAfterSend.ForeColor = ControlStateColors.Inactive;

                Bruh.Technician_Label_Status.ForeColor = ControlStateColors.Active;
                Bruh.Technician_Label_Mode.ForeColor = ControlStateColors.Disabled;
                Bruh.Technician_Label_DataTypeA.ForeColor = ControlStateColors.Active;
                Bruh.Technician_Label_DataTypeB.ForeColor = ControlStateColors.Active;
                Bruh.Technician_Label_DataA.ForeColor = ControlStateColors.Active;
                Bruh.Technician_Label_DataB.ForeColor = ControlStateColors.Active;

                isActive = true;
                SimulateModes = false;
                MasterProtolStaysOn = false;
                SendConfig = false;
                ClearAfterSendingConfig = false;

                MasterProtocol.mode = Modes_Ref.testing;
                Bruh.Technician_Open_CanVisualisation();

                Bruh.ModuleData_SortingStation.ResetReceivedData = false;
                Bruh.ModuleData_Vehicle.ResetReceivedData = false;
                Bruh.ModuleData_WeightStation.ResetReceivedData = false;

                CommandCenter.Technician.terminal.Log_header(LogsInfos.Technician.NowDebugging);
            }
            //#############################################################//
            /// <summary>
            /// Asthetics of the Technician mode while in emergency mode.
            /// </summary>
            //#############################################################//
            public static void Emergency(Form_MainMenu Bruh)
            {
                if (InEmergency == false)
                {
                    BRS.Debug.Comment("Enabling emergency style for technician mode",true);
                    FormReference = Bruh;
                    CommandCenter.Technician.terminal.Log_Error(LogsInfos.Technician.NowEmergency);
                    InEmergency = true;
                    Close(Bruh);
                    InEmergency = true;
                    Bruh.Technician_Emergency_CanVisualisation(Bruh);
                    CommandCenter.Technician.Buttons.ClearTerminal.State = ControlState.Error;
                    CommandCenter.Technician.Buttons.SaveTerminal.State = ControlState.Error;
                    CommandCenter.Technician.Buttons.KeepCanOn.State = ControlState.Error;
                    CommandCenter.Technician.Buttons.ClearAfterSend.State = ControlState.Error;
                    CommandCenter.Technician.Buttons.SimulateModes.State = ControlState.Error;
                    CommandCenter.Technician.Buttons.SendConfig.State = ControlState.Error;
                    CommandCenter.Technician.Buttons.TechMode.State = ControlState.Error;

                    Bruh.Technician_Label_SimulateModes.ForeColor = ControlStateColors.Error;
                    Bruh.Technician_Label_SendOnce.ForeColor = ControlStateColors.Error;
                    Bruh.Technician_Label_KeepCanOn.ForeColor = ControlStateColors.Error;

                    Bruh.Technician_Label_ClearAfterSend.ForeColor = ControlStateColors.Error;
                    Bruh.Technician_Label_Status.ForeColor = ControlStateColors.Error;
                    Bruh.Technician_Label_Mode.ForeColor = ControlStateColors.Error;
                    Bruh.Technician_Label_DataTypeA.ForeColor = ControlStateColors.Error;
                    Bruh.Technician_Label_DataTypeB.ForeColor = ControlStateColors.Error;
                    Bruh.Technician_Label_DataA.ForeColor = ControlStateColors.Error;
                    Bruh.Technician_Label_DataB.ForeColor = ControlStateColors.Error;
                }
            }

            #endregion Methods
        }
        #endregion Classes
    }
}
