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
            /// meanings.
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
            /// <summary>
            /// Class containing the specific meaning of each status of the sorting station
            /// </summary>
            public class SortingStation
            {
                public static string emergencyStop                  = "Sorting station in emergency";
                public static string paused                         = "Sorting is paused";
                public static string testing                        = "Executing self diagnostic";
                public static string processing                     = "Is sorting";
                public static string calibrating                    = "Station is calibrating";
                public static string calibrated                     = "Station is calibrated";
                public static string waiting                        = "Station is not operational";
                public static string safe                           = "Station is safe to handle";
                public static string error                          = "Status: in error";
                public static string atSortingFactory               = "Error: at the sorting station";
                public static string atWeightStation                = "Error: at the weight station";
                public static string finishedSortingAndHasLoaded    = "Sorting finished, and truck loaded";
                public static string waitingToSort                  = "Station is waiting for a truck";
                public static string waitingToWeight                = "Error: is waiting to weight";
                public static string finishedWeighting              = "Error: has finished weighting";
                public static string empty                          = "No more discs to sort";
            }
            /// <summary>
            /// Class containing the specific meaning of each status of the weight station
            /// </summary>
            public class WeightStation
            {
                public static string emergencyStop = "Weight station in emergency";
                public static string paused = "Weighting is paused";
                public static string testing = "Error: Executing self test";
                public static string processing = "Error: Is sorting";
                public static string calibrating = "Station is calibrating";
                public static string calibrated = "Station is calibrated";
                public static string waiting = "Station is not operational";
                public static string safe = "Station is safe to handle";
                public static string error = "Status: in error";
                public static string atSortingFactory = "Error: at the sorting station";
                public static string atWeightStation = "Error: at the weight station";
                public static string finishedSortingAndHasLoaded = "Error: Sorting finished";
                public static string waitingToSort = "Error: waiting to sort";
                public static string waitingToWeight = "Station waiting for a loaded truck";
                public static string finishedWeighting = "Finished weighting discs";
                public static string empty = "Error: is empty";
            }
            /// <summary>
            /// Class containing the specific meaning of each status of the truck
            /// </summary>
            public class Vehicle
            {
                public static string emergencyStop = "Truck in emergency";
                public static string paused = "Driving is paused";
                public static string testing = "Error: Executing self test";
                public static string processing = "Error: Is sorting";
                public static string calibrating = "Truck is calibrating";
                public static string calibrated = "Truck is calibrated";
                public static string waiting = "Truck is waiting for something";
                public static string safe = "Truck is safe to handle";
                public static string error = "Status: in error";
                public static string atSortingFactory = "Truck is at the sorting station";
                public static string atWeightStation = "Truck is at the weight station";
                public static string finishedSortingAndHasLoaded = "Error: Sorting finished";
                public static string waitingToSort = "Error: waiting to sort";
                public static string waitingToWeight = "Error: waiting to weight";
                public static string finishedWeighting = "Error: finished weighting";
                public static string empty = "Error: is empty";
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

            /// <summary>
            /// Class reminding the user that their attempts at changing the current mode
            /// is futile, as it is already that mode which is being used
            /// </summary>
            public class Already
            {
                public static string Emergency      = "Network is already in emergency";
                public static string Operating      = "Network is already operating";
                public static string Paused         = "Network is already paused";
                public static string Maintenance    = "network is already in maintnance";
                public static string Testing        = "Network is already in Technician mode";
                public static string Initialising   = "Network is already initialising";
                public static string Calibrating    = "network is already ongoing calibration";
            }
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

    /// <summary>
    /// Class containing definitions of Terminal.Log in order
    /// to universalize what is logged in terminals inside of
    /// this application
    /// </summary>
    public static class LogsInfos
    {
        public static class BeagleBone
        {

        }
        /// <summary>
        /// Class containing phrases to use when logging events
        /// during operation of the command center
        /// </summary>
        public static class Operations
        {
            public static string NowInEmergency = "Network has encountered an emergency stop request";
            public static string NoMoreEmergency = "Emergency cancelled from the CommandCenter";
            public static string NowOperating = "Operations have started";
            public static string NowPaused = "The network has stopped operation and is now waiting to resume";
            public static string NowMaintnance = "Maintenance proceedure started";
            public static string NowCalibrating = "Calibration proceedure started";
            public static string NowTesting = "Debugging session has started";
            public static string NowInitialising = "Started initialisation process";
            public static string UnexpectedEnd = "Regular operations unexpectedly stopped";
            /// <summary>
            /// Module related logs
            /// </summary>
            public static class Modules
            {
                /// <summary>
                /// Logged warning displayed in a terminal when a module which was
                /// previously seen as Online, is no longer talking on the
                /// CAN bus
                /// </summary>
                public static string NoLongerOnline = " is no longer seen talking on the CAN bus";
                /// <summary>
                /// Logged warning displayed in a terminal when a module switched offline and
                /// is now back online.
                /// </summary>
                public static string NoLongerOffline = " has started talking on the CAN bus again. This module is potentially experiencing communication errors";
                /// <summary>
                /// Comment logged when a module first boots up as the CAN bus begins
                /// </summary>
                public static string FirstTimeOnline = " has started talking on the CAN bus";
                /// <summary>
                /// Logged comment saying that this module has yet to be seen talking on
                /// the CAN bus
                /// </summary>
                public static string YetToBeOnline = " still hasn't been seen communicating on the CAN bus";
                /// <summary>
                /// How to log that a module has sent a command
                /// to other modules. Leave a space before the
                /// first quote, as the module's name will start the
                /// string. Example of a string: " is a module"
                /// Output: "Sorting station is a module"
                /// </summary>
                public static class Commands
                {
                    public static string UnexpectedData = " tried sending unexisting command";
                    #region Movements
                    public static string MoveLeft       = " asked modules to move left";
                    public static string MoveRight      = " asked modules to move right";
                    public static string MoveForwards   = " asked modules to move forwards";
                    public static string MoveBackwards  = " asked modules to move backwards";
                    public static string MoveUp         = " asked modules to move upwards";
                    public static string MoveDown       = " asked modules to move downwards";
                    #endregion Movements
                    #region Suction
                    public static string SuctionOn = " has asked to turn ON suction";
                    public static string SuctionOff = " has asked to turn OFF suction";
                    #endregion Suction
                    #region Lights
                    public static string LightAOn  = " has sent Light A ON.";
                    public static string LightAOff = " has sent Light A OFF.";
                    public static string LightBOn  = " has sent Light B ON.";
                    public static string LightBOff = " has sent Light B OFF.";
                    public static string LightCOn  = " has sent Light C ON.";
                    public static string LightCOff = " has sent Light C OFF.";
                    public static string LightDOn  = " has sent Light D ON.";
                    public static string LightDOff = " has sent Light D OFF.";
                    #endregion Lights
                    #region Gotos
                    public static string GotoSortingStation = " asked modules to go to the sorting station";
                    public static string GotoWeightStation = " asked modules to go to the weight station";
                    #endregion Gotos
                    #region Units
                    public static string UseMetric = "asked modules to now use Metric units";
                    public static string UseImperial = "asked modules to now use Imperial units";
                    #endregion Units
                    #region Discharge
                    public static string Discharge = " has asked modules to discharge";
                    #endregion Discharge
                    #region Start
                    public static string StartSorting = " asked modules to start sorting";
                    public static string StartWeighting = " asked modules to start weighting";
                    #endregion Start
                }
                /// <summary>
                /// How to log that a module has sent new values.
                /// Not to use for continuous outputs and logging, 
                /// but only when data changes from previously
                /// received data. Leave a space before the
                /// first quote, as the module's name will start the
                /// string. Example of a string: " is a module"
                /// Output: "Sorting station is a module"
                /// </summary>
                public static class Values
                {
                    public static string UnexpectedData = " tried sending unexisting value";
                    #region Discs
                    #region Colors
                    public static string disc_Red = " is now seeing an orange disc";
                    public static string disc_Silver = " is now seeing a metallic disc";
                    public static string disc_Black = " is now seeing a black disc";
                    public static string disc_NoColor = " is no longer seeing any discs";
                    #endregion Colors

                    #region Detection
                    public static string disc_Detected = " has detected a disc";
                    public static string disc_Lost = " is no longer seeing a previously seen disc";
                    public static string disc_CouldNotBeFound = " could not find any discs";
                    #endregion Detection
                    #endregion Discs

                    #region Units
                    public static string NowInMetric = " is now using Metric units";
                    public static string NowInImperial = " is now using Imperial units";
                    #endregion Units
                }
                /// <summary>
                /// How to log that a module has sent a new state.
                /// Not to use for continuous outputs and logging, 
                /// but only when data changes from previously
                /// received data. Leave a space before the
                /// first quote, as the module's name will start the
                /// string. Example of a string: " is a module"
                /// Output: "Sorting station is a module"
                /// </summary>
                public static class States
                {
                    public static string IsIncoherent = " is sending a status which does not exist: ";
                    /// <summary>
                    /// Used to log a new state of a module.
                    /// </summary>
                    public class IsNow
                    {
                        public static string InEmergencyStop = " HAS SEEN OR TRIGGERED THE EMERGENCY PROTOCOL";
                        public static string Paused = " is now paused";
                        public static string Testing = " has started it's self diagnostic proceedure";
                        public static string Processing = " has started executing a task";
                        public static string Calibrating = " has started it's calibration proceedure";
                        public static string Calibrated = " has completed it's calibration";
                        public static string Waiting = " is now waiting for an event";
                        public static string Safe = " is now safe to handle for maintenance";
                        public static string Error = " has encountered an unexpected error. See module for more info";
                        public static string AtSortingfactory = " has arrived at the sorting factory";
                        public static string AtWeightStation = " has arrived at the weight station";
                        public static string WaitingToSort = " is now waiting for an event to start sorting";
                        public static string WaitingToWeight = " is now waiting for an event to start weighting";
                        public static string Empty = " is now empty. Please take the necessary actions";
                        public static string FinishedSortingAndLoaded = " has finished it's sorting proceedure, and loaded the truck";
                        public static string FinishedWeighting = " has finished weighting the given disc";
                    }

                }
                /// <summary>
                /// Class containing the different logged sentences
                /// when a module's virtual object's mode is switched 
                /// </summary>
                public static class VirtualModes
                {
                    /// <summary>
                    /// Used to log the new wanted mode of a module.
                    /// Leave a space before the first quote of your
                    /// strings as the module's name starts the log comment
                    /// </summary>
                    public class IsNow
                    {
                        public static string Emergency      = " is now supposed to be in it's emergency proceedure";
                        public static string Paused         = " is now supposed to have paused ongoing processes";
                        public static string Maintenance    = " should start it's proceedure to be safe for maintenance";
                        public static string Testing        = " should have entered Technician Mode";
                        public static string Operating      = " should now start standard operations";
                        public static string Initialising   = " should be initialising itself";
                        public static string Calibrating    = " should start self calibation proceedure";
                    }
                }
            }
        }
    }

    public static class PopUpInfos
    {
        public static class Header
        {
            public static string Warning = "Warning";
        }
        public static class ModeSwitching
        {
            public static string IsNotPaused = "Are you sure you want to change the command center's current mode? It is not currently paused and doing this may cause issues";
            public static string DisablingEmergency = "Are you sure you want to disable the ongoing emergency proceedure? Some modules may trigger it back ON if they have not been hard reset manually";
        }
    }
}
