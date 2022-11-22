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
            public static string DirectoryDoesntExist = "Project cannot be found";
            public static string CanCantOpen = "Can cannot open!";
            public static string SerialClosed = "BeagleBone UART Closed!";
        }
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
            if (!BRS.ComPort.Port.IsOpen && BeagleBone.CurrentStep > 0)
            {
                BeagleBone.StartConnection = false;
                BeagleBone.ConnectionHappenning = true;
                BeagleBone.CurrentStep = 0;
                BeagleBone.Error = BeagleErrors.SerialClosed;
                return;
            }

            if (BeagleBone.CurrentStep == 1)
            {
                BRS.ComPort.Port.Write("\n");
                BeagleBone.CurrentStep = 2;
            }

            if(BeagleBone.StartConnection && BRS.ComPort.Port.IsOpen)
            {
                BeagleBone.StartConnection = false;
                BeagleBone.ConnectionHappenning = true;
                BeagleBone.CurrentStep = 1;
                BeagleBone.Error = BeagleErrors.None;
            }
        }
    }
