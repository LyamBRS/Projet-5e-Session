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
        #region Classes
        /// <summary>
        /// Class containing all the beaglebone's required information,
        /// aswell as connection processes and steps.
        /// </summary>
        public static class BeagleBone
        {
            public static bool StartConnection = false;
            public static bool ConnectionHappenning = false;
            public static int CurrentStep = 0;

            public static string Error = "No Error";
        }
        /// <summary>
        /// Structure of all the possible beaglebone errors that can
        /// occcur durring beagle stuff... Cuz its a beaglebone...
        /// So errors are not even a suggestion.
        /// </summary>
        public static class BeagleErrors
        {
            public static string None = "No Error";
            public static string NoAnswers = "No answer from beaglebone";
            public static string UnexpectedAnswer = "Received an unexpected answer";
            public static string IncorrectPassword = "Set password is wrong";
            public static string DirectoryDoesntExist = "Directory is invalid";
            public static string CanCantOpen = "Can cannot open!";
            public static string SerialClosed = "BeagleBone UART Closed!";

            public static string UserDoesntExist = "Specified BBB User unexistant";
            public static string UnexpectedUser = "Wrong user already logged in";
        }
        #endregion Classes
        //#############################################################//
        /// <summary>
        /// This function starts the connecting process through the
        /// Terminal App.
        /// To start the process, be sure you are connected via a
        /// serial port.
        /// use StartBeagleBoneConnection to start the connection process.
        /// </summary>
        //#############################################################//
        public void BeagleBone_ConnectingProcess()
        {
            Debug.LocalStart(true);
            string lastLine = "";
            string beforeLast = "";
            if (ConsoleArea.Lines.Any()) { lastLine = ConsoleArea.Lines[ConsoleArea.Lines.Length - 1].ToLower(); }
            if (ConsoleArea.Lines.Length > 1) { beforeLast = ConsoleArea.Lines[ConsoleArea.Lines.Length - 2].ToLower(); }

            if (AutoConnect && MasterProtocol.isActive == false)
            {
                //////////////////////////////////////////// Wait before retries
                #region RetryingMessages
                if (BeagleBone.CurrentStep == 6)
                {
                    BeagleBone.CurrentStep = 2;
                }
                if (BeagleBone.CurrentStep == 7)
                {
                    NewUserTextInfo("Retrying...", 3);
                    BeagleBone.CurrentStep = 6;
                }
                if (BeagleBone.CurrentStep == 8)
                {
                    BeagleBone.CurrentStep = 7;
                }
                #endregion RetryingMessages
                ////////////////////////////////////////////

                //Stop connection attempts if SerialPort is no longer opened.
                if (!BRS.ComPort.Port.IsOpen && BeagleBone.CurrentStep > 0)
                {
                    BRS.Debug.Comment("Error occured during BeagleBone connection process!", true);
                    BeagleBone.StartConnection = false;
                    BeagleBone.ConnectionHappenning = true;
                    BeagleBone.CurrentStep = 0;
                    BeagleBone.Error = BeagleErrors.SerialClosed;

                    CommandCenter.Buttons.Terminal.State = ControlState.Active;
                    CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;

                    // Make last line an error line.
                    CommandCenter.terminal.Log_Error(BeagleBone.Error);
                    //ConsoleArea_LogError(BeagleBone.Error);
                    return;
                }

                // Regular BeagleBone login attempts
                if (BeagleBone.CurrentStep < 5)
                {
                    // Successful logging in.
                    if (lastLine.Contains("@beaglebone:"))
                    {
                        BeagleBone.CurrentStep = 2;
                        MasterProtocol.isActive = false;

                        // Correct user.
                        if (lastLine.Contains(BeagleBone_User.Text + "@beaglebone"))
                        {
                            //No path selected
                            if (lastLine.Contains(BeagleBone_User.Text + "@beaglebone:~$"))
                            {
                                CommandCenter.Buttons.USB.State = ControlState.Loading;
                                CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
                                CommandCenter.Buttons.Terminal.State = ControlState.Error;
                                BeagleBone.Error = BeagleErrors.None;

                                NewUserTextInfo("Navigating to File Path...", 3);
                                BRS.ComPort.Port.Write("cd " + BeagleBone_FilePath.Text + "\n");

                                BRS.Debug.Comment("Entering FilePath in BeagleBone...", true);
                                BRS.Debug.Comment("FilePath is: " + BeagleBone_FilePath.Text, true);
                                BRS.Debug.Comment("Current Line is: " + lastLine, true);
                                lastLine = "";
                            }
                            else
                            {
                                //Current line is a file path
                                if (lastLine.Contains(BeagleBone_User.Text + "@beaglebone:" + BeagleBone_FilePath.Text.ToLower() + "$"))
                                {
                                    CommandCenter.Buttons.USB.State = ControlState.Loading;
                                    CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
                                    CommandCenter.Buttons.Terminal.State = ControlState.Error;
                                    BeagleBone.Error = BeagleErrors.None;

                                    NewUserTextInfo("Attempting launch...", 3);
                                    BRS.ComPort.Port.Write("./" + BeagleBone_FileName.Text + "\n");

                                    BRS.Debug.Comment("Launching application...", true);
                                    BRS.Debug.Comment("FileName is: " + BeagleBone_FileName.Text, true);
                                    BRS.Debug.Comment("Current Line is: " + lastLine, true);
                                }
                                else
                                {
                                    if (BeagleBone.Error == BeagleErrors.None)
                                    {
                                        CommandCenter.Buttons.USB.State = ControlState.Warning;
                                        CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
                                        CommandCenter.Buttons.Terminal.State = ControlState.Disabled;
                                        BeagleBone.Error = BeagleErrors.DirectoryDoesntExist;
                                        NewUserTextInfo(BeagleBone.Error, 2);
                                        CommandCenter.terminal.Log_Error(BeagleBone.Error);
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (BeagleBone.Error == BeagleErrors.None)
                            {
                                BeagleBone.Error = BeagleErrors.UnexpectedUser;
                                CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
                                CommandCenter.Buttons.Terminal.State = ControlState.Disabled;
                                NewUserTextInfo(BeagleBone.Error, 2);
                                CommandCenter.terminal.Log_Error(BeagleBone.Error);
                            }
                        }
                    }
                    //////////////////////////////////////////// - Program is starting
                    if (lastLine.Contains("[-starting-]"))
                    {
                        NewUserTextInfo("Program Starting...", 1);
                        CommandCenter.Buttons.CloseBeagle.State = ControlState.Active;
                        CommandCenter.Buttons.Terminal.State = ControlState.Error;
                        CommandCenter.Buttons.USB.State = ControlState.Warning;
                        BRS.Debug.Comment("Waiting for beaglebone to start...", true);
                    }
                    //////////////////////////////////////////// - Indicating to us that it is using Automatic mode
                    if (lastLine.Contains("[automatic mode]"))
                    {
                        CommandCenter.Buttons.CloseBeagle.State = ControlState.Active;
                        CommandCenter.Buttons.Terminal.State = ControlState.Error;
                        NewUserTextInfo("Automatic Mode ON", 3);
                    }
                    //////////////////////////////////////////// - Program is started successfully
                    if (beforeLast.Contains("[automatic mode]"))
                    {
                        CommandCenter.Buttons.CloseBeagle.State = ControlState.Active;
                        CommandCenter.Buttons.Terminal.State = ControlState.Active;
                        CommandCenter.Buttons.USB.State = ControlState.Active;

                        NewUserTextInfo("Started!", 1);
                        BRS.Debug.Comment("Starting Master Protocol!", true);

                        MasterProtocol_Start();
                    }
                    //////////////////////////////////////////// - Asking us if we are automated or it's a user launching the application
                    if ((lastLine.Contains("[question]:") || beforeLast.Contains("[question]:")))
                    {
                        CommandCenter.Buttons.CloseBeagle.State = ControlState.Active;
                        CommandCenter.Buttons.Terminal.State = ControlState.Error;
                        CommandCenter.Buttons.USB.State = ControlState.Warning;

                        NewUserTextInfo("Answering questions...", 1);
                        BeagleBone.CurrentStep = 4;
                        BRS.Debug.Comment("Answering N to beaglebone's questions...", true);

                        try
                        {
                            BRS.ComPort.Port.Write("N\n");
                            // Start Master protocol
                            Debug.Success();
                        }
                        catch
                        {
                            NewUserTextInfo("FATAL SETUP ERROR", 1);
                            BRS.Debug.Comment("FAIL TO ANSWER BEAGLEBONE QUESTIONS", true);
                            Debug.Error();
                        }
                    }
                    // Program already started.
                    if (lastLine.Contains("reset") || beforeLast.Contains("reset"))
                    {
                        CommandCenter.Buttons.USB.State = ControlState.Active;
                        CommandCenter.Buttons.CloseBeagle.State = ControlState.Active;
                        CommandCenter.Buttons.Terminal.State = ControlState.Active;
                        NewUserTextInfo("BeagleBone Already ON", 3);
                        BRS.Debug.Comment("Starting CAN process...", true);
                        MasterProtocol_Start();
                    }
                    ////////////////////////////////////////////////////////////////////////// USER PASSWORD
                    if (lastLine.Contains("password") && BeagleBone.CurrentStep != 4)
                    {
                        BeagleBone.CurrentStep = 4;
                        CommandCenter.Buttons.USB.State = ControlState.Loading;
                        CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
                        CommandCenter.Buttons.Terminal.State = ControlState.Disabled;
                        BeagleBone.Error = BeagleErrors.None;

                        NewUserTextInfo("Entering password...", 3);
                        BRS.ComPort.Port.Write(BeagleBone_Password.Text + "\n");

                        BRS.Debug.Comment("Entering password in BeagleBone...", true);
                        BRS.Debug.Comment("Password is: " + BeagleBone_Password.Text, true);
                        BRS.Debug.Comment("Current Line is: " + lastLine, true);
                        lastLine = "";
                    }
                    /////////////////////////////////////////////////////////////////////////// USER LOGIN
                    if (lastLine.Contains("beaglebone login:") && BeagleBone.CurrentStep != 3)
                    {
                        BeagleBone.CurrentStep = 3;
                        CommandCenter.Buttons.USB.State = ControlState.Loading;
                        CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
                        CommandCenter.Buttons.Terminal.State = ControlState.Disabled;
                        BeagleBone.Error = BeagleErrors.None;

                        NewUserTextInfo("Entering Username...", 3);
                        BRS.ComPort.Port.Write(BeagleBone_User.Text + "\n");

                        BRS.Debug.Comment("Entering Username in BeagleBone...", true);
                        BRS.Debug.Comment("Username is: " + BeagleBone_User.Text, true);
                        BRS.Debug.Comment("Current Line is: " + lastLine, true);
                        lastLine = "";
                    }
                }
                #region ErrorConditions
                if (beforeLast.Contains("login incorrect") || lastLine.Contains("login incorrect"))
                {
                    if (BeagleBone.Error == BeagleErrors.None)
                    {
                        BeagleBone.CurrentStep = 8;
                        CommandCenter.Buttons.USB.State = ControlState.Warning;
                        CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
                        CommandCenter.Buttons.Terminal.State = ControlState.Warning;
                        BeagleBone.Error = BeagleErrors.IncorrectPassword;
                        NewUserTextInfo(BeagleBone.Error, 2);
                        CommandCenter.terminal.Log_Error(BeagleBone.Error);
                    }
                }
                if (beforeLast.Contains("no such file or directory") || lastLine.Contains("no such file or directory"))
                {
                    if (BeagleBone.Error == BeagleErrors.None)
                    {
                        BeagleBone.CurrentStep = 8;
                        CommandCenter.Buttons.USB.State = ControlState.Warning;
                        CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
                        CommandCenter.Buttons.Terminal.State = ControlState.Warning;
                        BeagleBone.Error = BeagleErrors.DirectoryDoesntExist;
                        NewUserTextInfo(BeagleBone.Error, 2);
                        CommandCenter.terminal.Log_Error(BeagleBone.Error);
                    }
                }
                #endregion ErrorConditions

                // Step one consist of refreshing the terminal.
                if (BeagleBone.CurrentStep == 1)
                {
                    CommandCenter.Buttons.USB.State = ControlState.Loading;
                    CommandCenter.Buttons.CloseBeagle.State = ControlState.Warning;
                    CommandCenter.Buttons.Terminal.State = ControlState.Disabled;

                    MasterProtocol.Send.ToBeagleBone.Reset();
                    MasterProtocol.Send.ToBeagleBone.Quit();

                    BeagleBone.CurrentStep = 2;
                    NewUserTextInfo("Waiting for BBB answer...", 3);
                }

                // Start of the connection process for the BeagleBone
                if (BeagleBone.StartConnection && BRS.ComPort.Port.IsOpen)
                {
                    // Handles beagleClass
                    BeagleBone.StartConnection = false;
                    BeagleBone.ConnectionHappenning = true;
                    BeagleBone.CurrentStep = 1;
                    BeagleBone.Error = BeagleErrors.None;

                    // Indicate via the USB icon that we are attempting connection with the found BeagleBoneBlue
                    CommandCenter.Buttons.USB.State = ControlState.Loading;
                    CommandCenter.Buttons.CloseBeagle.State = ControlState.Disabled;
                    CommandCenter.Buttons.Terminal.State = ControlState.Disabled;

                    //Terminal window handling.
                    CommandCenter.Buttons.Terminal.State = ControlState.Warning;

                    BRS.Debug.Comment("Starting BeagleBone connection process...", true);
                    CommandCenter.terminal.Log_header("Start of connection process");

                    //Reset the terminal text.
                    ConsoleArea.Text = "";
                }

                /////////////////////////////////////////////////////////////////// TERMINAL HANDLING
                if (CommandCenter.Buttons.Terminal.State == ControlState.Active)
                   {CommandCenter.terminal.state = Terminal.States.Active;}
                if (CommandCenter.Buttons.Terminal.State == ControlState.Disabled)
                   {CommandCenter.terminal.state = Terminal.States.Disabled;}
                if (CommandCenter.Buttons.Terminal.State == ControlState.Error)
                { CommandCenter.terminal.state = Terminal.States.Error; }
                if (CommandCenter.Buttons.Terminal.State == ControlState.Inactive)
                { CommandCenter.terminal.state = Terminal.States.Inactive; }
                if (CommandCenter.Buttons.Terminal.State == ControlState.Warning)
                { CommandCenter.terminal.state = Terminal.States.Warning; }
            }
            Debug.LocalEnd();
        }
    }
}
