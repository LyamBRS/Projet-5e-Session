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
        #region Terminal
        //#############################################################//
        /// <summary>
        /// Click event called each time the clear button for the
        /// calibration terminal is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Calibration_Clear_Logs_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Attempting to clear the terminal");
            CommandCenter.Calibration.terminal.Clear();

            if (CommandCenter.Calibration.terminal.Window.Text == "")
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
        /// Click event called each time the calibration's terminal is
        /// being saved by pressing the save icon
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Calibration_Save_Logs_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Attempting to save the Maintenance's logs");
            CommandCenter.Calibration.terminal.SaveTerminal();
            NewUserTextInfo(UserInfos.Terminal.Saved, 1);
            Debug.Success();
            CommandCenter.Calibration.terminal.Clear();
            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Il faut accepter que l'on a pas le temps de tout faire!
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Calibration_Button_StartStop_Click(object sender, EventArgs e)
        {
            BRS.PopUp.Error(PopUpInfos.ThisIsntAvailable, PopUpInfos.Header.Warning);
        }
        #endregion Terminal
        #endregion Clicks
        #region Updates
        //#############################################################//
        /// <summary>
        /// Update the calibration button of the calibration TAB
        /// depending on factors like the state of BRS.ComPort.Port
        /// and the state of the masterprotocol
        /// </summary>
        //#############################################################//
        public void Calibration_Update()
        {
            if (BRS.ComPort.Port.IsOpen)
            {
                if (MasterProtocol.isActive)
                {
                    if (MasterProtocol.mode != Modes_Ref.calibration)
                    {
                        CommandCenter.Calibration.Buttons.Calibration.State = ControlState.Inactive;
                    }
                    else
                    {
                        CommandCenter.Calibration.Buttons.Calibration.State = ControlState.Active;
                    }
                }
                else
                {
                    CommandCenter.Calibration.Buttons.Calibration.State = ControlState.Warning;
                }
            }
            else
            {
                CommandCenter.Calibration.Buttons.Calibration.State = ControlState.Disabled;
            }
        }
        #endregion Updates
        #endregion Buttons
    }
}
