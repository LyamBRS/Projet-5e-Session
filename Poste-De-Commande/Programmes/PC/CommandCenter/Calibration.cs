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
        //#############################################################//
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
