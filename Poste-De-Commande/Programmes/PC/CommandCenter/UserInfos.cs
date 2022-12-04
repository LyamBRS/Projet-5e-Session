using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CommandCenter
{
    /// <summary>
    /// Class containing definitions of NewUserInterface to use
    /// instead of individually hard coding the messages to
    /// display to the user
    /// </summary>
    internal class UserInfos
    {
        /// <summary>
        /// User infos specific to the Serial port / BRS.ComPort
        /// </summary>
        public class ComPort
        {
            /// <summary>
            /// Text reminding the user that the Serial Port is offline
            /// </summary>
            public static string IsOffline = "No serial port linked";
            /// <summary>
            /// Event related text to tell the user that their attempts at linking to a serial port was a success
            /// </summary>
            public static string SuccessfulLink  = "Serial port linked successfully";
            /// <summary>
            /// Event related text telling the user that an error occured while attempting to link to their specified Serial Port
            /// </summary>
            public static string LinkingError = "Failed to link with serial port";
            /// <summary>
            /// Event related text telling the user that there was an error and the serial port could not be closed
            /// </summary>
            public static string ClosingError = "Failed to close serial port";
            /// <summary>
            /// Event related text telling the user that it closed the serial port
            /// </summary>
            public static string UserClosed = "User closed serial link";
            /// <summary>
            /// Event related text which tells the user that an unepexted error occured, and the serial port closed abruptly
            /// </summary>
            public static string UnexpectedTermination = "Serial port closed unexpectedly";
        }
        /// <summary>
        /// User info related to the Master Protocol
        /// </summary>
        public class MasterProtocol
        {
            /// <summary>
            /// Tells the user that the CAN bus / MasterProtocol is currently offline
            /// </summary>
            public static string IsOffline = "The CAN bus is offline";
            /// <summary>
            /// Tells the user that the CAN bus / MasterProtocol is currently online
            /// </summary>
            public static string IsOnline = "The CAN bus is online";
            /// <summary>
            /// Tells the user that the MasterProtocol is waiting after the BeagleBone's action before completing it's proceedure
            /// </summary>
            public static string IsWaitingForBBB = "Waiting after BeagleBone";
            /// <summary>
            /// Tells the user that the MasterProtocol successfully started with no issues
            /// </summary>
            public static string HasStarted = "CAN bus is now operational";
        }
        /// <summary>
        /// User info related to the BeagleBone's connection process
        /// </summary>
        public class BeagleBone
        {
            /// <summary>
            /// Tells the user that the BeagleBone will re-attempt it's process shortly
            /// </summary>
            public static string IsRetryingProcess = "Retrying...";
            /// <summary>
            /// Tells the user that the BeagleBone's program could not be exited successfully
            /// </summary>
            public static string ClosingError = "Failed to close BeagleBone";
            /// <summary>
            /// Tells the user that the BeagleBone is currently terminating it's program
            /// </summary>
            public static string Closing = "BeagleBone is closing";
            /// <summary>
            /// Text telling the user that it terminated/closde the beaglebone's program
            /// </summary>
            public static string UserClosed = "BeagleBone Terminated";
            /// <summary>
            /// Tells the user that a FATAL error occured in the beaglebone's process
            /// </summary>
            public static string FatalError = "BeagleBone did a beaglebone";
            /// <summary>
            /// Tells the user that the beaglebone is attempting to go to the specific directories
            /// </summary>
            public static string IsNavigatingDirectories = "Navigating BeagleBone's directories";
            /// <summary>
            /// Tells the user that the beaglebone is attempting to launch the specific program at the specified path
            /// </summary>
            public static string IsLaunchingProgram = "Launching BeagleBone's program";
            /// <summary>
            /// Tells the user that the beaglebone is currently answering some questions
            /// </summary>
            public static string IsAnsweringQuestions = "BeagleBone is answering questions";
            /// <summary>
            /// Tells the user that the beaglebone's program started, and is currently launching
            /// </summary>
            public static string ProgramLaunching = "Program is launching";
            /// <summary>
            /// Tells the user that the beaglebone's program selected Automatic as it's execution process
            /// </summary>
            public static string SelectedAutomatic = "Program's automatic mode selected";
            /// <summary>
            /// Tells the user that it's specified password for the beaglebone isn't valid with the connected beaglebone
            /// </summary>
            public static string WrongPassword = "BeagleBone's password is invalid";
            /// <summary>
            /// Tells the user that it's specified Username for the beaglebone isn't valid with the connected beaglebone
            /// </summary>
            public static string WrongUser = "BeagleBone's user is invalid";
            /// <summary>
            /// Tells the user that the beaglebone is currently writing the specific username in the terminal
            /// </summary>
            public static string WritingUser = "Entering BeagleBone's username";
            /// <summary>
            /// Tells the user that the beaglebone is currently writing the specific password for the specified username
            /// </summary>
            public static string WritingPassword = "Entering BeagleBone's password";
            /// <summary>
            /// Tells the user that the beaglebone was somehow already on when connecting to it.
            /// </summary>
            public static string WasAlreadyOn = "BeagleBone was already started";
            /// <summary>
            /// Tells the user that the program is waiting for life signals from the beaglebone through BRS.ComPort
            /// </summary>
            public static string WaitingForLifeSignals = "Waiting for a BeagleBone's life signals";
        }
        /// <summary>
        /// User info specific to modules, their states and errors
        /// </summary>
        public class Modules
        {
            /// <summary>
            /// Tells the user that all Modules are online and responsive through the MasterProtocol
            /// </summary>
            public static string AllAreOnline = "All modules are online";
            /// <summary>
            /// Tells the user that this specific module is not answering on the CAN bus
            /// </summary>
            public static string IsUnresponsive = "Not talking on the CAN bus";
            /// <summary>
            /// Tells the user that this specific module's state is EMERGENCY
            /// </summary>
            public static string IsInEmergency = "Module is in emergency mode";
            /// <summary>
            /// Tells the user that this module's state outputed on the CAN bus is incoherent
            /// with the current mode outputed by the command center
            /// </summary>
            public static string WrongStatus = "Module's status is incoherent";
            /// <summary>
            /// Class containing user text info for individual module's generic states
            /// </summary>
            public class States
            {
                public static string emergencyStop                  = "Status: In emergency";
                public static string paused                         = "Status: Paused";
                public static string testing                        = "Status: self testing";
                public static string processing                     = "Status: executing a task";
                public static string calibrating                    = "Status: calibrating";
                public static string calibrated                     = "Status: is calibrated";
                public static string waiting                        = "Status: waiting for something";
                public static string safe                           = "Status: is safe for handling";
                public static string error                          = "Status: in error";
                public static string atSortingFactory               = "Status: at the sorting station";
                public static string atWeightStation                = "Status: at the weight station";
                public static string finishedSortingAndHasLoaded    = "Status: has loaded the truck";
                public static string waitingToSort                  = "Status: is waiting to sort";
                public static string waitingToWeight                = "Status: is waiting to weight";
                public static string finishedWeighting              = "Status: has finished weighting";
                public static string empty                          = "Status: is empty";
            }
        }
        /// <summary>
        /// User infos specific to module's modes
        /// </summary>
        public class Modes
        {
            /// <summary>
            /// Tells the user that the emergency mode was just disabled
            /// </summary>
            public static string EmergencyDisabled = "Emergency mode disabled";
            /// <summary>
            /// Tells the user that the emergency mode was just enabled
            /// </summary>
            public static string EmergencyEnabled = "EMERGENCY MODE ACTIVATED";
            /// <summary>
            /// Tells the user that standard operation protocol has just been activated
            /// </summary>
            public static string OperationStarted = "Standard operation started";
            /// <summary>
            /// Tells the user that modules are now paused
            /// </summary>
            public static string NowPaused = "Pausing modules";
            /// <summary>
            /// Tells the user that the current mode is Emergency
            /// </summary>
            public static string IsEmergency = "Emergency mode is active!";
            /// <summary>
            /// Tells the user that the module network is currently paused
            /// </summary>
            public static string IsPaused = "Network is paused";
            /// <summary>
            /// Tells the user that the module network is ongoing active maintenance
            /// </summary>
            public static string IsMaintenance = "Ongoing maintenance";
            /// <summary>
            /// Tells the user that the module network is ongoing debugging/testing
            /// </summary>
            public static string IsTesting = "Ongoing debug";
            /// <summary>
            /// Tells the user that the module network is under standard operations
            /// </summary>
            public static string IsOperating = "Network is operating";
            /// <summary>
            /// Tells the user that the module network is initialising from a fresh start
            /// </summary>
            public static string IsInitialising = "Network is initialising";
            /// <summary>
            /// Tells the user that the network is ongoing active calibrations, and should not be tempered with
            /// </summary>
            public static string IsCalibrating = "Ongoing calibration";
        }
        /// <summary>
        /// Setting related user infos like when saving or errors occurs
        /// </summary>
        public class Settings
        {
            /// <summary>
            /// Message displayed when settings cannot be saved for X reasons
            /// </summary>
            public static string SavingError = "Error occured while saving";

            public static string SavedAutoConnection = "Saved auto-connecting setting";
            public static string SavedBaudrate = "Saved baudrate setting";
            public static string SavedDataBits = "Saved data bit setting";
            public static string SavedStopBits = "Saved stop bit setting";
            public static string SavedParity = "Saved parity setting";
            public static string SavedFlowControl = "Saved flow control setting";
            public static string SavedRXTimeout = "Saved receiving timeout setting";
            public static string SavedTXTimeout = "Saved transmitting timeout setting";
            public static string SavedWeightStationUnit = "Saved unit to use";

            public static string SavedFilePath = "Saved BeagleBone's program's file path";
            public static string SavedFileName = "Saved BeagleBone's program's name";
            public static string SavedPassword = "Saved BeagleBone's password";
            public static string SavedUser = "Saved BeagleBone's user";
        }
        /// <summary>
        /// User info related to BRS.Terminal
        /// </summary>
        public class Terminal
        {
            /// <summary>
            /// Tells the user that a terminal has been successfully cleared
            /// (No saving)
            /// </summary>
            public static string Cleared = "Terminal has been cleared";
            /// <summary>
            /// Tells the user that a new log file has been created for the specific terminal
            /// </summary>
            public static string Saved = "New log file created";
        }
    }
}
