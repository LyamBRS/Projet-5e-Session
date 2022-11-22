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
        #region Initialisations
        public static string SelectedComFullName = "No Device";
        public static string SelectedComName = "No Device";

        /// <summary>
        /// Flag raised when combo boxes need to be cleared and re-initialised
        /// </summary>
        public static bool UpdateDropDown = false;

        /// <summary>
        /// Flag set to a value preventing the parsing of combo boxes until
        /// DeviceChangedEvent stops occuring.
        /// </summary>
        public static int TimeUntilDropDownUpdate = 0;

        /// <summary>
        /// Flag given by SerialConsole deciding if KeyPress are to be shown in the console
        /// </summary>
        public static bool UserTX = false;

        /// <summary>
        /// Flag given by SerialConsole deciding if \r are to be parsed as carriage returns or new line feed.
        /// </summary>
        public static bool ParseReturn = false;

        /// <summary>
        /// Indicates to timers that the port should be open or closed. What dictates this is the clicking on linking
        /// in the setting tab.
        /// </summary>
        public static bool ComShouldBeOpen = false;

        SerialPort OldSettings;

        /// <summary>
        /// RX data received delegate
        /// </summary>
        /// <param name="Result">RX string</param>
        public delegate void dlgThread(String Result);

        /// <summary>
        /// The RX delegate
        /// </summary>
        public dlgThread Delegate;
        /// <summary>
        /// To check, using a timer, if the port state changed.
        /// </summary>
        public static bool oldPortState = false;

        #endregion Initialisations
        #region Initialization_functions
        //#############################################################//
        /// <summary>
        /// Automatically fill PortBox1 with all the available
        /// ports given by ComPort.AvailableComsFullName. 
        /// Sets the currently selected
        /// port to ComPort.Port's setting.
        /// </summary>
        //#############################################################//
        private void InnitComDropDown()
        {
            BRS.Debug.Comment("Clearing items...");
            PortBox1.Items.Clear();
            BRS.Debug.Comment("Adding names back...");
            foreach (string name in BRS.ComPort.AvailableComsFullName)
            {
                PortBox1.Items.Add(name);
            }

            if (!PortBox1.Items.Contains(BRS.ComPort.Port.PortName))
            {
                PortBox1.Items.Add("(" + BRS.ComPort.Port.PortName + ")");
                PortBox1.SelectedItem = "(" + BRS.ComPort.Port.PortName + ")";
            }
        }
        //#############################################################//
        /// <summary>
        /// Sets the currently selected
        /// BaudRate to ComPort.Port's setting.
        /// </summary>
        //#############################################################//        
        private void InnitBaudRateBox()
        {
            BaudRateBox.Text = OldSettings.BaudRate.ToString();
        }
        //#############################################################//
        /// <summary>
        /// Automatically fill StopBitBox with all the available
        /// SerialPort.StopBits. Sets the currently selected
        /// StopBits to ComPort.Port's setting.
        /// </summary>
        //#############################################################//
        private void InnitStopBit()
        {
            foreach (string name in Enum.GetNames(typeof(StopBits)))
                if (!name.Equals("None"))
                {
                    StopBitBox.Items.Add(name);
                    StopBitBox.Text = OldSettings.StopBits.ToString();
                }
        }
        //#############################################################//
        /// <summary>
        /// Automatically fill ParityBox with all the available
        /// SerialPort.Parity. Sets the currently selected
        /// parity to ComPort.Port's setting.
        /// </summary>
        //#############################################################//
        private void InnitParity()
        {
            foreach (string name in Enum.GetNames(typeof(Parity)))
                ParityBox.Items.Add(name);
            ParityBox.Text = OldSettings.Parity.ToString();
        }
        //#############################################################//
        /// <summary>
        /// Automatically fill FlowControlBox with all the available
        /// SerialPort.Handshake. Sets the currently selected
        /// handshake to ComPort.Port's setting.
        /// </summary>
        //#############################################################//
        private void InnitFlowControl()
        {
            foreach (string name in Enum.GetNames(typeof(Handshake)))
                FlowControlBox.Items.Add(name);
            FlowControlBox.Text = OldSettings.Handshake.ToString();
        }
        //#############################################################//
        /// <summary>
        /// Set's DataBit combo box with the current ComPort.Databits
        /// values.
        /// </summary>
        //#############################################################//
        private void InnitDataBit()
        {
            DataBitBox.Text = OldSettings.DataBits.ToString();
        }
        #endregion Initialization_functions
        #region Buttons
        //#############################################################//
        /// <summary>
        /// Attempt to link with USB using defined settings in the
        /// Tab_Settings
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Button_Link_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);

            BRS.Debug.Comment("Porting changes to ComPort...");
            BRS.ComPort.Port.BaudRate = Convert.ToInt32(BaudRateBox.Text);
            BRS.ComPort.Port.Parity = (Parity)ParityBox.SelectedIndex;
            BRS.ComPort.Port.Handshake = (Handshake)FlowControlBox.SelectedIndex;
            BRS.ComPort.Port.DataBits = Convert.ToInt32(DataBitBox.Text);
            BRS.ComPort.Port.StopBits = (StopBits)StopBitBox.SelectedIndex + 1;

            try
            {
                BRS.ComPort.Port.PortName = PortBox1.Text.Split('(', ')')[1];
            }
            catch
            {
                try
                {
                    BRS.ComPort.Port.PortName = "No Device";
                }
                catch
                {
                    BRS.Debug.Comment("Port was still opened while trying to change Port Name");
                }
            }

            BRS.Debug.Comment("Port name: " + PortBox1.SelectedIndex.ToString() + ": " + BRS.ComPort.Port.PortName.ToString());
            BRS.Debug.Comment("BaudRate:  " + BaudRateBox.SelectedIndex.ToString() + ": " + BRS.ComPort.Port.BaudRate.ToString());
            BRS.Debug.Comment("DataBits:  " + DataBitBox.SelectedIndex.ToString() + ": " + BRS.ComPort.Port.DataBits.ToString());
            BRS.Debug.Comment("StopBits:  " + StopBitBox.SelectedIndex.ToString() + ": " + BRS.ComPort.Port.StopBits.ToString());
            BRS.Debug.Comment("Parity:    " + ParityBox.SelectedIndex.ToString() + ": " + BRS.ComPort.Port.Parity.ToString());
            BRS.Debug.Comment("HandShake: " + FlowControlBox.SelectedIndex.ToString() + ": " + BRS.ComPort.Port.Handshake.ToString());

            BRS.Debug.Comment("Checking if port is opened or closed.");
            if (!BRS.ComPort.Port.IsOpen)
            {
                BRS.Debug.Comment("PORT CLOSED:");
                BRS.Debug.Comment("Attempting linking with specified COM port...");
                BRS.Debug.Comment("Port name: " + BRS.ComPort.Port.PortName.ToString());
                BRS.Debug.Comment("BaudRate:  " + BRS.ComPort.Port.BaudRate.ToString());
                BRS.Debug.Comment("DataBits:  " + BRS.ComPort.Port.DataBits.ToString());
                BRS.Debug.Comment("StopBits:  " + BRS.ComPort.Port.StopBits.ToString());
                BRS.Debug.Comment("Parity:    " + BRS.ComPort.Port.Parity.ToString());
                BRS.Debug.Comment("HandShake: " + BRS.ComPort.Port.Handshake.ToString());
                try
                {
                    BRS.ComPort.Port.Open();
                    oldPortState = true;
                    Debug.Success("Port opened!");
                    NewUserTextInfo("Linked!", 1);

                    CommandCenter.Buttons.USB.State = ControlState.Warning;
                    CommandCenter.Buttons.Link.State = ControlState.Active;
                    ComShouldBeOpen = true;
                }
                catch
                {
                    Debug.Error("FAILED TO OPEN COM PORT WITH SPECIFIED INFO");
                    NewUserTextInfo("LINKING ERROR", 2);
                    SystemSounds.Hand.Play();

                    CommandCenter.Buttons.USB.State = ControlState.Disabled;
                    CommandCenter.Buttons.Link.State = ControlState.Error;
                    ComShouldBeOpen = false;
                }
            }
            else
            {
                BRS.Debug.Comment("Closing COM...");
                try
                {
                    BRS.ComPort.Port.Close();
                    oldPortState = false;
                    ComShouldBeOpen = false;
                    Debug.Success("Port closed!");
                    NewUserTextInfo("Link Terminated", 1);

                    CommandCenter.Buttons.USB.State = ControlState.Disabled;
                    CommandCenter.Buttons.Link.State = ControlState.Inactive;
                    BRS.ComPort.Port.PortName = "No Device";
                }
                catch
                {
                    Debug.Error("FAILED TO CLOSE COM PORT WITH SPECIFIED INFO");
                    NewUserTextInfo("LINKING ERROR", 2);

                    CommandCenter.Buttons.USB.State = ControlState.Error;
                    CommandCenter.Buttons.Link.State = ControlState.Error;
                }
            }

            BRS.Debug.Header(false);
        }
        #endregion Buttons
        //#############################################################//
        /// <summary>
        /// Event called when the PortBox list should be changed.
        /// Sets a "debounce" to 2 to avoid crashing when updating PortBox
        /// as if a thread updates the list while ittering through it,
        /// the form will crash
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        public void ListChanged(object sender, EventArgs e)
        {
            BRS.Debug.Comment("Increasing <debounce> timer.");
            TimeUntilDropDownUpdate = 2;
            UpdateDropDown = true;
        }
        //#############################################################//
        /// <summary>
        /// Checks if PortBox needs updating, and that no more changes
        /// are occuring.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void UpdatePortList_Tick(object sender, EventArgs e)
        {
            if (UpdateDropDown && TimeUntilDropDownUpdate == 0)
            {
                BRS.Debug.Success("Innitialising com port drop down");
                InnitComDropDown();
                UpdateDropDown = false;
            }
            else if (TimeUntilDropDownUpdate > 0)
            {
                TimeUntilDropDownUpdate--;
            }

            // Disabling the settings parameters if the port is opened.
            if (BRS.ComPort.Port.IsOpen)
            {
                BaudRateBox.Enabled = false;
                StopBitBox.Enabled = false;
                ParityBox.Enabled = false;
                FlowControlBox.Enabled = false;
                DataBitBox.Enabled = false;
                PortBox1.Enabled = false;
            }
            else
            {
                BaudRateBox.Enabled = true;
                StopBitBox.Enabled = true;
                ParityBox.Enabled = true;
                FlowControlBox.Enabled = true;
                DataBitBox.Enabled = true;
                PortBox1.Enabled = true;
            }

            // Check actual state of the USB vs the state it should be in.
            if(BRS.ComPort.Port.IsOpen != ComShouldBeOpen)
            {
                CommandCenter.Buttons.Link.State = ControlState.Error;
                CommandCenter.Buttons.USB.State = ControlState.Error;
                NewUserTextInfo("USB CONNECTION LOST",2);

                //reste flag to actual USB state in this case.
                ComShouldBeOpen = BRS.ComPort.Port.IsOpen;
            }
        }
    }
}
