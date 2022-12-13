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
        #region Buttons
        #region Clicks
        //#############################################################//
        /// <summary>
        /// Click event called each time the button to save logs is
        /// pressed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Maintenance_Save_Logs_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Attempting to save the Maintenance's logs");
            CommandCenter.Maintenance.terminal.SaveTerminal();
            NewUserTextInfo(UserInfos.Terminal.Saved, 1);
            Debug.Success();
            CommandCenter.Maintenance.terminal.Clear();
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Click event called each time the button to clear the
        /// maintenance logs is pressed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Maintenance_Clear_Logs_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Attempting to clear the terminal");
            CommandCenter.Maintenance.terminal.Clear();

            if (CommandCenter.Maintenance.terminal.Window.Text == "")
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
        //#############################################################//
        private void Maintenance_Button_StartStop_Click(object sender, EventArgs e)
        {
            BRS.PopUp.Error(PopUpInfos.ThisIsntAvailable,PopUpInfos.Header.Warning);
        }
        #endregion Clicks
        #region Updates
        //#############################################################//
        /// <summary>
        /// Update the maintenance button of the maintenance TAB
        /// depending on factors like the state of BRS.ComPort.Port
        /// and the state of the masterprotocol
        /// </summary>
        //#############################################################//
        public void Maintenance_Update()
        {
            if (BRS.ComPort.Port.IsOpen)
            {
                if (MasterProtocol.isActive)
                {
                    if (MasterProtocol.mode != Modes_Ref.maintenance)
                    {
                        CommandCenter.Maintenance.Buttons.Maintenance.State = ControlState.Inactive;
                    }
                    else
                    {
                        CommandCenter.Maintenance.Buttons.Maintenance.State = ControlState.Active;
                    }
                }
                else
                {
                    CommandCenter.Maintenance.Buttons.Maintenance.State = ControlState.Warning;
                }
            }
            else
            {
                CommandCenter.Maintenance.Buttons.Maintenance.State = ControlState.Disabled;
            }
        }
        #endregion Updates
        #endregion Buttons
    }
}
