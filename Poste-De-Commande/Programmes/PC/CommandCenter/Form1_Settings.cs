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
        /// To check, using a timer, if the port state changed.
        /// </summary>
        public static bool oldPortState = false;

        public bool AutoConnect = false;
        public ControlState previousState = ControlState.Active;

        public class Settings
        {
            #region Variables
            /// <summary>
            /// The XML document where all the settings for the command center are located.
            /// </summary>
            public static XmlDocument SettingsFile = new XmlDocument();

            private static string Filepath = "";
            /// <summary>
            /// Reference to this form
            /// </summary>
            public static Form_MainMenu formSettings;
            #endregion Variables
            #region Individual_Settings_Changes
            #region Language
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of Language</returns>
            public static string Language() { return ReadAppSettings("Language"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool Language(string valueToSave) { return (UpdateOrCreate("Language", valueToSave)); }
            #endregion Language
            #region BeagleBone_AutoConnect
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of AutoConnect</returns>
            public static string BeagleBone_AutoConnect() { return ReadAppSettings("BeagleBone_AutoConnect"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool BeagleBone_AutoConnect(string valueToSave) { return (UpdateOrCreate("BeagleBone_AutoConnect", valueToSave)); }
            #endregion BeagleBone_AutoConnect
            #region BaudRate
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of BaudRate</returns>
            public static string BaudRate() { return ReadAppSettings("BaudRate"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool BaudRate(string valueToSave) { return(UpdateOrCreate("BaudRate", valueToSave)); }
            #endregion BaudRate
            #region DataBits
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of DataBits</returns>
            public static string DataBits() { return ReadAppSettings("DataBits"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool DataBits(string valueToSave) { return (UpdateOrCreate("DataBits", valueToSave)); }
            #endregion DataBits
            #region StopBits
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of StopBits</returns>
            public static string StopBits() { return ReadAppSettings("StopBits"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool StopBits(string valueToSave) { return (UpdateOrCreate("StopBits", valueToSave)); }
            #endregion StopBits
            #region Parity
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of Parity</returns>
            public static string Parity() { return ReadAppSettings("Parity"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool Parity(string valueToSave) { return (UpdateOrCreate("Parity", valueToSave)); }
            #endregion Parity
            #region Flow
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of Flow</returns>
            public static string Flow() { return ReadAppSettings("Flow"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool Flow(string valueToSave) { return (UpdateOrCreate("Flow", valueToSave)); }
            #endregion Flow
            #region TimeOut_RX
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of TimeOut_RX</returns>
            public static string TimeOut_RX() { return ReadAppSettings("TimeOut_RX"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool TimeOut_RX(string valueToSave) { return (UpdateOrCreate("TimeOut_RX", valueToSave)); }
            #endregion TimeOut_RX
            #region TimeOut_TX
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of TimeOut_TX</returns>
            public static string TimeOut_TX() { return ReadAppSettings("TimeOut_TX"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool TimeOut_TX(string valueToSave) { return (UpdateOrCreate("TimeOut_TX", valueToSave)); }
            #endregion TimeOut_RX
            #region BeagleBone_User
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of BeagleBone_User</returns>
            public static string BeagleBone_User() { return(ReadAppSettings("BeagleBone_User")); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool BeagleBone_User(string valueToSave) { return (UpdateOrCreate("BeagleBone_User", valueToSave)); }
            #endregion BeagleBone_User
            #region BeagleBone_Password
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of BeagleBone_Password</returns>
            public static string BeagleBone_Password() { return ReadAppSettings("BeagleBone_Password"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool BeagleBone_Password(string valueToSave) { return (UpdateOrCreate("BeagleBone_Password", valueToSave)); }
            #endregion BeagleBone_Password
            #region BeagleBone_FilePath
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of BeagleBone_FilePath</returns>
            public static string BeagleBone_FilePath() { return ReadAppSettings("BeagleBone_FilePath"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool BeagleBone_FilePath(string valueToSave) { return (UpdateOrCreate("BeagleBone_FilePath", valueToSave)); }
            #endregion BeagleBone_FilePath
            #region BeagleBone_FileName
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of BeagleBone_FileName</returns>
            public static string BeagleBone_FileName() { return ReadAppSettings("BeagleBone_FileName"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool BeagleBone_FileName(string valueToSave) { return (UpdateOrCreate("BeagleBone_FileName", valueToSave)); }
            #endregion BeagleBone_FilePath
            #region Scale_Unit
            /// <summary> Gets the value from Settings.xml </summary>
            /// <returns>Value of Scale_Unit</returns>
            public static string Scale_Unit() { return ReadAppSettings("Scale_Unit"); }

            /// <summary> Gets the value from Settings.xml </summary>
            public static bool Scale_Unit(string valueToSave) { return(UpdateOrCreate("Scale_Unit", valueToSave)); }
            #endregion Scale_Unit
            #endregion Individual_Settings_Changes
            //#############################################################//
            /// <summary>
            /// Creates or saves texts inside of the AppSetting node of the
            /// CommandCenter's settings XML file. If the node already exist
            /// the inner text gets updated.
            /// </summary>
            /// <param name="doc">Settings.xml</param>
            /// <param name="elementName">Name of the setting</param>
            /// <param name="value">Value to put in the setting</param>
            /// <return>false if an error occured during saving</return>
            //#############################################################//
            private static bool UpdateOrCreate(string elementName, string value)
            {
                XmlNodeList nodes;

                #region Global_Checks_For_Nulls
                // Checking if configuration tag exists within the referenced XML
                if (SettingsFile.SelectSingleNode("//configuration") == null)
                {
                    BRS.Debug.Comment("Configuration did no exist, creating it...");
                    XmlElement Configuration = SettingsFile.CreateElement("configuration");
                    SettingsFile.AppendChild(Configuration);
                    Debug.Success();
                }
                XmlNode configuration = SettingsFile.SelectSingleNode("//configuration");

                // Checking if appSettings is present inside of configuration node
                if (SettingsFile.SelectSingleNode("//configuration/appSettings") == null)
                {
                    BRS.Debug.Comment("appSettings did no exist, creating it...");
                    XmlElement AppSettings = SettingsFile.CreateElement("appSettings");
                    configuration.AppendChild(AppSettings);
                    Debug.Success();
                }
                XmlNode appSettings = configuration.SelectSingleNode("//appSettings");
                #endregion Global_Checks_For_Nulls
                /////////////////////////////////////////////////////////////////////////
                XmlNode elementNode = appSettings.SelectSingleNode("//" + elementName);

                if (elementNode == null)
                {
                    BRS.Debug.Comment(elementName + " did no exist, creating it...");
                    XmlElement elementToCreate = SettingsFile.CreateElement(elementName);
                    appSettings.AppendChild(elementToCreate);
                    Debug.Success();
                }
                elementNode = appSettings.SelectSingleNode("//" + elementName);

                BRS.Debug.Comment("Saving " + value + " inside of " + elementName);
                elementNode.InnerText = value;

                BRS.Debug.Comment("Attempting to save Settings.xml...");
                try
                {
                    SettingsFile.Save(Filepath);
                    Debug.Success();
                    return true;
                }
                catch
                {
                    Debug.Error("FILE NO LONGER EXISTS ???");
                    return false;
                }
            }
            //#############################################################//
            /// <summary>
            /// Reads the specified setting from the Settings.xml file of the
            /// CommandCenter
            /// </summary>
            /// <param name="elementName">Name of the setting</param>
            /// <returns></returns>
            //#############################################################//
            private static string ReadAppSettings(string elementName)
            {
                SettingsFile.Load(Filepath);
                /*
                BRS.Debug.Comment();
                */
                XmlNodeList nodes;

                #region Global_Checks_For_Nulls
                // Checking if configuration tag exists within the referenced XML
                if (SettingsFile.SelectSingleNode("//configuration") == null)
                {
                    Debug.Aborted("Something went wrong in the XML formatting... configuration isn't present in Settings.xml");
                    return ("XML Error");
                }
                XmlNode configuration = SettingsFile.SelectSingleNode("//configuration");

                // Checking if appSettings is present inside of configuration node
                if (SettingsFile.SelectSingleNode("//configuration/appSettings") == null)
                {
                    Debug.Aborted("Something went wrong in the XML formatting... appSettings isnt present in Settings.xml");
                    return ("XML Error");
                }
                XmlNode appSettings = configuration.SelectSingleNode("//appSettings");
                #endregion Global_Checks_For_Nulls
                /////////////////////////////////////////////////////////////////////////
                XmlNode elementNode = appSettings.SelectSingleNode("//" + elementName);

                if (elementNode == null)
                {
                    Debug.Error(elementName + " does not exist! Create it via UpdateOrCreateAppSetting()");
                    return ("NaN");
                }
                else
                {
                    elementNode = appSettings.SelectSingleNode("//" + elementName);
                    BRS.Debug.Comment("Read: " + elementNode.InnerText);
                    return (elementNode.InnerText);
                }
            }
            //#############################################################//
            /// <summary>
            /// Loads data from the setting file. If there are no
            /// setting files, it will create an empty one, with default
            /// parameters. Place this at the end of your initialisation
            /// functions of your form
            /// </summary>
            //#############################################################//
            public static void LoadSettings()
            {
                string path = "";
                bool directoryFound = false;
                BRS.Debug.Comment("Loading settings from XML file...");
                //////////////////////////////////////////
                BRS.Debug.Comment("Navigating directories to the setting emplacement...");
                path = Directory.GetCurrentDirectory();
                //path = Path.GetFullPath(Path.Combine(path, @"..\..\"));
                BRS.Debug.Success("Directory: " + path);
                //////////////////////////////////////////
                BRS.Debug.Comment("Checking if a setting folder exists...");
                var folders = Directory.GetDirectories(path);
                foreach (string folder in folders)
                {
                    if (folder.Contains("Settings"))
                    {
                        path = folder;
                        directoryFound = true;
                        break;
                    }
                }
                //////////////////////////////////////////
                if (directoryFound)
                {
                    Debug.Success("Setting directory found!");
                    BRS.Debug.Comment("Checking if file Settings.xml exists within the directory...");
                    if (File.Exists(path + @"\Settings.xml"))
                    {
                        Debug.Success("Settings already exists!");
                    }
                    else
                    {
                        Debug.Aborted("Settings file do not exists");
                        CreateXML(path);
                    }
                }
                else
                {
                    Debug.Error("No directory for settings found... Creating one...");
                    path = path + @"\Settings";
                    Directory.CreateDirectory(path);
                    Debug.Success();

                    BRS.Debug.Comment("Creating XML file within the specified folder...");
                    CreateXML(path);
                }

                Filepath = path + @"\Settings.xml";


                BRS.Debug.Comment("Getting XML file...");
                try
                {
                    SettingsFile = new XmlDocument();
                    SettingsFile.Load(Filepath);
                    Debug.Success();

                    BRS.Debug.Comment("Settings are ready to be loaded into whatever they need be.");
                }
                catch
                {
                    Debug.Error("Could not get XML file at specified path");
                }
            }
            //#############################################################//
            /// <summary>
            /// Crate a setting XML document for the CommandCenter
            /// application at the path specified. Don't use this, only use
            /// LoadSettings(); This is only called if no setting file exists
            /// </summary>
            /// <param name="path">DIRECTORY PATH NO FILE PATH</param>
            //#############################################################//
            private static void CreateXML(string path)
            {
                BRS.Debug.Comment("Creating XML file to store application settings");
                SettingsFile = new XmlDocument();

                BRS.Debug.Comment("Creating XMl configuration...");
                XmlDeclaration xmlDeclaration = SettingsFile.CreateXmlDeclaration("1.0", "UTF-8", null);
                XmlElement root = SettingsFile.DocumentElement;
                SettingsFile.InsertBefore(xmlDeclaration, root);

                BRS.Debug.Comment("Creating necessary Settings");
                UpdateorCreate_ALL();
                BRS.Debug.Comment("Saving XML file...");
                try
                {
                    SettingsFile.Save(path + @"\Settings.xml");
                    Debug.Success();
                }
                catch
                {
                    Debug.Error("COULD NOT CREATE AND SAVE AN XML FILE AT THE SPECIFIED PATH!!!");
                }
            }
            //#############################################################//
            /// <summary>
            /// Initial creation or updates of all the settings
            /// </summary>
            //#############################################################//
            private static void UpdateorCreate_ALL()
            {
                BRS.Debug.Comment("Updating or creating all settings...");

                UpdateOrCreate("BaudRate", formSettings.BaudRateBox.Text);
                UpdateOrCreate("DataBits", formSettings.DataBitBox.Text);
                UpdateOrCreate("StopBits", formSettings.StopBitBox.Text);
                UpdateOrCreate("Parity", formSettings.ParityBox.Text);
                UpdateOrCreate("Flow", formSettings.FlowControlBox.Text);
                UpdateOrCreate("TimeOut_RX", formSettings.RXTimeOutBox.Text);
                UpdateOrCreate("TimeOut_TX", formSettings.TXTimeOutBox.Text);

                UpdateOrCreate("BeagleBone_User", formSettings.BeagleBone_User.Text);
                UpdateOrCreate("BeagleBone_Password", formSettings.BeagleBone_Password.Text);
                UpdateOrCreate("BeagleBone_FilePath", formSettings.BeagleBone_FilePath.Text);
                UpdateOrCreate("BeagleBone_FileName", formSettings.BeagleBone_FileName.Text);
                UpdateOrCreate("BeagleBone_AutoConnect", (CommandCenter.Buttons.AutoConnection.State == ControlState.Active).ToString());

                UpdateOrCreate("Scale_Unit", formSettings.DropDown_ScaleUnit.Text);
                UpdateOrCreate("Language", "English");
            }
        }

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
                try
                {
                    BRS.ComPort.Port.Open();
                    oldPortState = true;
                    Debug.Success("Port opened!");
                    NewUserTextInfo(UserInfos.ComPort.SuccessfulLink, 1);

                    CommandCenter.Buttons.USB.State = ControlState.Warning;
                    CommandCenter.Buttons.Link.State = ControlState.Active;
                    BeagleBone.StartConnection = true;
                    ComShouldBeOpen = true;
                }
                catch
                {
                    Debug.Error("FAILED TO OPEN COM PORT WITH SPECIFIED INFO");
                    NewUserTextInfo(UserInfos.ComPort.LinkingError, 2);
                    SystemSounds.Hand.Play();

                    CommandCenter.Buttons.USB.State = ControlState.Disabled;
                    CommandCenter.Buttons.Link.State = ControlState.Error;
                    ComShouldBeOpen = false;
                    MasterProtocol_Stop();
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
                    NewUserTextInfo(UserInfos.ComPort.UserClosed, 1);

                    MasterProtocol_Stop();

                    CommandCenter.Buttons.USB.State = ControlState.Disabled;
                    CommandCenter.Buttons.Link.State = ControlState.Inactive;
                    BRS.ComPort.Port.PortName = "No Device";
                }
                catch
                {
                    Debug.Error("FAILED TO CLOSE COM PORT WITH SPECIFIED INFO");
                    NewUserTextInfo(UserInfos.ComPort.ClosingError, 2);
                    MasterProtocol_Stop();

                    CommandCenter.Buttons.USB.State = ControlState.Error;
                    CommandCenter.Buttons.Link.State = ControlState.Error;
                }
            }

            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Changes the state of autoconnection.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Button_AutoConnect_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);

            BRS.Debug.Comment("Flipping autoConnect state...");
            AutoConnect = !AutoConnect;
            Debug.Success(AutoConnect.ToString());

            if (AutoConnect == false)
            {
                if (CommandCenter.Buttons.AutoConnection.State == ControlState.Warning)
                {
                    previousState = ControlState.Warning;
                    CommandCenter.Buttons.AutoConnection.State = ControlState.Inactive;
                }

                if (CommandCenter.Buttons.AutoConnection.State == ControlState.Error)
                {
                    previousState = ControlState.Error;
                    CommandCenter.Buttons.AutoConnection.State = ControlState.Inactive;
                }

                if (CommandCenter.Buttons.AutoConnection.State == ControlState.Active)
                {
                    previousState = ControlState.Active;
                    CommandCenter.Buttons.AutoConnection.State = ControlState.Inactive;
                }
                if (CommandCenter.Buttons.AutoConnection.State == ControlState.Inactive)
                {
                    previousState = ControlState.Active;
                    CommandCenter.Buttons.AutoConnection.State = ControlState.Inactive;
                }
            }
            else
            {
                CommandCenter.Buttons.AutoConnection.State = previousState;
            }
            Settings.BeagleBone_AutoConnect(AutoConnect.ToString());
            NewUserTextInfo(UserInfos.Settings.SavedAutoConnection,1);
            BRS.Debug.Header(false);
        }
        #endregion Buttons
        #region USB
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
            Debug.LocalStart(true);
            if (UpdateDropDown && TimeUntilDropDownUpdate == 0)
            {
                BRS.Debug.Success("Innitialising com port drop down...");
                InnitComDropDown();
                UpdateDropDown = false;
            }
            else if (TimeUntilDropDownUpdate > 0)
            {
                TimeUntilDropDownUpdate--;
            }

            BeagleBone_ConnectingProcess();

            if(BRS.ComPort.Port.IsOpen && CommandCenter.Buttons.CloseBeagle.State == ControlState.Disabled)
            {
                CommandCenter.Buttons.CloseBeagle.State = ControlState.Active;
            }

            if(!BRS.ComPort.Port.IsOpen && CommandCenter.Buttons.CloseBeagle.State != ControlState.Disabled)
            {
                CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
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
                TXTimeOutBox.Enabled = false;
                RXTimeOutBox.Enabled = false;
                CommandCenter.terminal.state = Terminal.States.Active;
            }
            else
            {
                BaudRateBox.Enabled = true;
                StopBitBox.Enabled = true;
                ParityBox.Enabled = true;
                FlowControlBox.Enabled = true;
                DataBitBox.Enabled = true;
                PortBox1.Enabled = true;
                TXTimeOutBox.Enabled = true;
                RXTimeOutBox.Enabled = true;
                CommandCenter.terminal.state = Terminal.States.Disabled;
            }

            // Check actual state of the USB vs the state it should be in.
            if(BRS.ComPort.Port.IsOpen != ComShouldBeOpen)
            {
                CommandCenter.Buttons.Link.State = ControlState.Error;
                CommandCenter.Buttons.USB.State = ControlState.Error;
                NewUserTextInfo(UserInfos.ComPort.UnexpectedTermination,2);

                //reste flag to actual USB state in this case.
                ComShouldBeOpen = BRS.ComPort.Port.IsOpen;
            }

            Debug.LocalEnd();
        }
        #endregion USB
        #region WhenToSaveSettings
        private void PortBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
        }
        private void BaudRateBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (Settings.BaudRate(BaudRateBox.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedBaudrate, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void DataBitBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(Settings.DataBits(DataBitBox.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedDataBits, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void StopBitBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(Settings.StopBits(StopBitBox.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedStopBits, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void ParityBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(Settings.Parity(ParityBox.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedParity, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void FlowControlBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(Settings.Flow(FlowControlBox.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedFlowControl, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void RXTimeOutBox_TextChanged(object sender, EventArgs e)
        {
            if(Settings.TimeOut_RX(RXTimeOutBox.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedRXTimeout, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void TXTimeOutBox_TextChanged(object sender, EventArgs e)
        {
            if(Settings.TimeOut_TX(TXTimeOutBox.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedTXTimeout, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void DropDown_ScaleUnit_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(Settings.Scale_Unit(DropDown_ScaleUnit.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedWeightStationUnit, 1);
                MasterProtocol.scaleUnit = DropDown_ScaleUnit.Text.Contains("Metric") ? Commands_Ref.units_Metric : Commands_Ref.units_Imperial;
                BRS.Debug.Comment("Scale unit is now: " + MasterProtocol.scaleUnit.ToString());
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void BeagleBone_FilePath_TextChanged(object sender, EventArgs e)
        {
            if(Settings.BeagleBone_FilePath(BeagleBone_FilePath.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedFilePath, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void BeagleBone_FileName_TextChanged(object sender, EventArgs e)
        {
            if(Settings.BeagleBone_FileName(BeagleBone_FileName.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedFileName, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void BeagleBone_Password_TextChanged(object sender, EventArgs e)
        {
            if(Settings.BeagleBone_Password(BeagleBone_Password.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedPassword, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void BeagleBone_User_TextChanged(object sender, EventArgs e)
        {
            if(Settings.BeagleBone_User(BeagleBone_User.Text))
            {
                NewUserTextInfo(UserInfos.Settings.SavedUser, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        private void DropDown_Languages_SelectionChangeCommitted(object sender, EventArgs e)
        {
            if (Settings.Language(DropDown_Languages.Text))
            {
                if(DropDown_Languages.Text.Contains("Fr"))
                {
                    Languages.SetLanguageToFrench();
                }
                else
                {
                    Languages.SetLanguageToEnglish();
                }
                ReloadForm();
                NewUserTextInfo(UserInfos.Settings.SavedLanguage, 1);
            }
            else
            {
                NewUserTextInfo(UserInfos.Settings.SavingError, 2);
            }
        }
        #endregion WhenToSaveSettings
    }
}
