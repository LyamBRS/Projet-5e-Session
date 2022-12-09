using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;

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
            public static string SuccessfulLink = "Serial port linked successfully";
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
                public static string emergencyStop = "Status: In emergency";
                public static string paused = "Status: Paused";
                public static string testing = "Status: self testing";
                public static string processing = "Status: executing a task";
                public static string calibrating = "Status: calibrating";
                public static string calibrated = "Status: is calibrated";
                public static string waiting = "Status: waiting for something";
                public static string safe = "Status: is safe for handling";
                public static string error = "Status: in error";
                public static string atSortingFactory = "Status: at the sorting station";
                public static string atWeightStation = "Status: at the weight station";
                public static string finishedSortingAndHasLoaded = "Status: has loaded the truck";
                public static string waitingToSort = "Status: is waiting to sort";
                public static string waitingToWeight = "Status: is waiting to weight";
                public static string finishedWeighting = "Status: has finished weighting";
                public static string empty = "Status: is empty";
            }
            /// <summary>
            /// Class containing the specific meaning of each status of the sorting station
            /// </summary>
            public class SortingStation
            {
                public static string emergencyStop = "Sorting station in emergency";
                public static string paused = "Sorting is paused";
                public static string testing = "Executing self diagnostic";
                public static string processing = "Is sorting";
                public static string calibrating = "Station is calibrating";
                public static string calibrated = "Station is calibrated";
                public static string waiting = "Station is not operational";
                public static string safe = "Station is safe to handle";
                public static string error = "Status: in error";
                public static string atSortingFactory = "Error: at the sorting station";
                public static string atWeightStation = "Error: at the weight station";
                public static string finishedSortingAndHasLoaded = "Sorting finished, and truck loaded";
                public static string waitingToSort = "Station is waiting for a truck";
                public static string waitingToWeight = "Error: is waiting to weight";
                public static string finishedWeighting = "Error: has finished weighting";
                public static string empty = "No more discs to sort";

                public static string DiscIsRed = "Sorting has a red disc";
                public static string DiscIsBlack = "Sorting has a black disc";
                public static string DiscIsSilver = "Sorting has a metallic disc";
                public static string DiscHasNoColor = "Sorting no longer has a disc";
                public static string DiscNeverDetected = "No disc has been seen";
            }
            /// <summary>
            /// Class containing the specific meaning of each status of the weight station
            /// </summary>
            public class WeightStation
            {
                public static string emergencyStop = "Weight station in emergency";
                public static string paused = "Weighting is paused";
                public static string testing = "Error: Executing self test";
                public static string processing = "Weighting blocks";
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
                public static string processing = "Truck is moving";
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
            /// Tells the user that the current mode is unexpected and does not exist
            /// </summary>
            public static string DoesntExist = "Error: Mode does not exist";

            /// <summary>
            /// Class reminding the user that their attempts at changing the current mode
            /// is futile, as it is already that mode which is being used
            /// </summary>
            public class Already
            {
                public static string Emergency = "Network is already in emergency";
                public static string Operating = "Network is already operating";
                public static string Paused = "Network is already paused";
                public static string Maintenance = "network is already in maintnance";
                public static string Testing = "Network is already in Technician mode";
                public static string Initialising = "Network is already initialising";
                public static string Calibrating = "network is already ongoing calibration";
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
        /// <summary>
        /// UserInfo displayed to the user which are
        /// specific to the Technician mode
        /// </summary>
        public class Technician
        {
            public static string hasStarted = "Enabled technician mode";
            public static string userStopped = "Disabled technician mode";
            public static string unexpectedTermination = "Error: Tech mode TERMINATED";

            public static string nowSimulatingModes = "Mode simulation enabled";
            public static string stoppedSimulatingModes = "Mode simulation has stopped";

            public static string configSending = "Sending configuration...";
            public static string configSent = "Config has been sent!";

            public static string nowClearingConfigAfterSending = "Continously sending config";
            public static string stoppedConstantSending = "Continuous config sending stopped";

            public static string nowKeepingCanOn = "Can network is kept online";
            public static string stoppedKeepingCanON = "Can network only ON when sending";

            public static string CanVisualisationClosed = "--,--,--,--,--,--,--,--";
            public static string CanVisualisationInEmergency = "-EMERGENCY-";
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
                    public static string MoveLeft = " asked modules to move left";
                    public static string MoveRight = " asked modules to move right";
                    public static string MoveForwards = " asked modules to move forwards";
                    public static string MoveBackwards = " asked modules to move backwards";
                    public static string MoveUp = " asked modules to move upwards";
                    public static string MoveDown = " asked modules to move downwards";
                    #endregion Movements
                    #region Suction
                    public static string SuctionOn = " has asked to turn ON suction";
                    public static string SuctionOff = " has asked to turn OFF suction";
                    #endregion Suction
                    #region Lights
                    public static string LightAOn = " has sent Light A ON.";
                    public static string LightAOff = " has sent Light A OFF.";
                    public static string LightBOn = " has sent Light B ON.";
                    public static string LightBOff = " has sent Light B OFF.";
                    public static string LightCOn = " has sent Light C ON.";
                    public static string LightCOff = " has sent Light C OFF.";
                    public static string LightDOn = " has sent Light D ON.";
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
                        public static string Emergency = " is now supposed to be in it's emergency proceedure";
                        public static string Paused = " is now supposed to have paused ongoing processes";
                        public static string Maintenance = " should start it's proceedure to be safe for maintenance";
                        public static string Testing = " should have entered Technician Mode";
                        public static string Operating = " should now start standard operations";
                        public static string Initialising = " should be initialising itself";
                        public static string Calibrating = " should start self calibation proceedure";
                    }
                }
            }
        }
        /// <summary>
        /// 
        /// </summary>
        public static class Technician
        {
            public static string NowEmergency = "Technician debugging tools has detetected an Emergency";
            public static string ClosingForSafety = "Debug tools are closing for safety reasons";
            public static string NowDebugging = "Technician debugging and simulations started";
            public static string userStopped = "User has closed Technician debug session";
            public static string UnexpectedEnd = "Technician session came to an unexpected end";
            /// <summary>
            /// Logged in the technician terminal each time a CAN tram is sent
            /// once. 
            /// </summary>
            public static string HasSentOnce = "CAN config successfully sent";
            /// <summary>
            /// logged message each time the CAN data being sent changes from
            /// the previous values. keep a whitespace before the last quote
            /// to pervent the printed data from sticking to your string
            /// </summary>
            public static string DataChangedAnsIsNow = "Data being sent is now: ";
            /// <summary>
            /// Logged message each time the dropdowns are reset to their
            /// original values because of the checkbox for that setting
            /// being enabled
            /// </summary>
            public static string ConfigCleared = "Config reset to default values";
            /// <summary>
            /// Tells the user through the logs that continuous sending is now
            /// enabled through Keep CAN online.
            /// </summary>
            public static string NowSendingConstantly = "Periodic sending has been enabled";
            public static string NoLongerSendingConstantly = "Periodic sending has been disabled";
            /// <summary>
            /// Message logged in the console when the setting for the Technician mode
            /// changes for the Clear Config button.
            /// </summary>
            public static string NowClearingConfigWhenSending = "CAN config will now reset after each Send Once";
            public static string NoLongerClearingConfig = "CAN config no longer resets after each Send Once";
            /// <summary>
            /// Message sent to the user in the Technician terminal to indicate that 
            /// Mode simulation started from there on.
            /// </summary>
            public static string NowSimulatingModes = "Program is now simulating modes to modules";
            public static string NoLongerSimulatingModes = "Program is no longer simulating modes";
        }
    }
    /// <summary>
    /// Class which contains the text to display as pop ups
    /// in different situations.
    /// </summary>
    public static class PopUpInfos
    {
        public static class Header
        {
            /// <summary>
            /// Pop up header shown when the pop up's
            /// purpose in life is to warn the user
            /// of something, or to ask for 
            /// caution
            /// </summary>
            public static string Warning = "Warning";
        }
        public static class ModeSwitching
        {
            /// <summary>
            /// Popup displayed when the user
            /// is trying to change the current CAN bus mode
            /// to an other without putting the latter to
            /// pause initially.
            /// </summary>
            public static string IsNotPaused = "Are you sure you want to change the command center's current mode? It is not currently paused and doing this may cause issues";
            public static string DisablingEmergency = "Are you sure you want to disable the ongoing emergency proceedure? Some modules may trigger it back ON if they have not been hard reset manually";
        }

        public static class Technician
        {
            public static string DoYouWantToPrintInfo = "Do you want to print this module's current data in the terminal? This will clear the terminal first";
            public static string DoYouWantToSaveInstead = "Do you want to save the current terminal instead of just clearing it?";
        }
    }

    /// <summary>
    /// 3 letters or less for each state that
    /// a scale can be in inside of this application
    /// </summary>
    public static class WeightInfos
    {
        /// <summary>
        /// Displayed when the facilities used
        /// to get the scale weight are offline,
        /// or if the scale itself is offline.
        /// </summary>
        public static string isOffline = "OFF";

        public static string isEmpty = "Empt";
        /// <summary>
        /// Class containing units used when
        /// displaying measurement to the user
        /// of this application
        /// </summary>
        public static class Units
        {
            /// <summary>
            /// The number prior is in Grams
            /// </summary>
            public static string Metric = "g";
            /// <summary>
            /// The number prior is in ounces
            /// </summary>
            public static string Imperial = "oz";
            /// <summary>
            /// The unit of measurement of the number
            /// prior is undefined or unknown
            /// </summary>
            public static string UnknownUnit = "?";
        }
        /// <summary>
        /// No values is given by the scale
        /// </summary>
        public static string isOnlineButNoValue = "--";
        /// <summary>
        /// Something went wrong with the scale.
        /// If the latter is not giving the correct unit
        /// in comparaison with the wanted one, this
        /// message is shown
        /// </summary>
        public static string isError = "ERR";
    }


    public static class ListsInfos
    {
        public static class BaudRates
        {

        }

        public static class Units
        {

        }
        /// <summary>
        /// List of all the possible modes.
        /// On the left is how the code accesses this
        /// dictionary, on the right is what the end
        /// user will know these modes as. Do not
        /// change the left side of this table.
        /// </summary>
        public static Dictionary<int, string> Modes = new Dictionary<int, string>
        {
            {0,"Emergency Stop" },
            {1,"Pause" },
            {2,"Technician" },
            {3,"Maintenance" },
            {4,"Stand. Operations" },
            {5,"Calibration" },
            {6,"Initialisations" },
            {250,"[Inexisting Mode]" },
        };

        public static Dictionary<int, string> DataTypes = new Dictionary<int, string>
        {
            {0,        "None" },
            {1,    "Command" },
            {2,      "Value" },
            {3,      "State" },
        };

        public static Dictionary<int, string> EmptyData = new Dictionary<int, string>
        {
            {0,        "" },
        };

        public static Dictionary<int, string> States = new Dictionary<int, string>
        {
            {0,     "In emergency" },
            {1,     "Is paused" },
            {2,     "Self diagnosing" },
            {3,     "Is processing" },
            {4,     "In operation" },
            {5,     "Is calibrating" },
            {6,     "Is calibrated" },
            {7,     "Is waiting" },
            {8,     "Is safe" },
            {9,     "Has an Error" },
            {10,    "At sorting station" },
            {11,    "At weight station" },
            {12,    "Finished sorting and loaded" },
            {13,    "Is waiting to sort" },
            {14,    "Is waiting to weight" },
            {15,    "Has finished weighting" },
            {16,    "Is empty" },
            {250,   "[Inexisting State]" },
        };

        public static Dictionary<int, string> Values = new Dictionary<int, string>
        {
            {0,     "Has an orange disc" },
            {1,     "Has a metallic disc" },
            {2,     "Has a black disc" },
            {3,     "No longer see colors" },
            {4,     "Has detected a disc" },
            {5,     "No longer detects discs" },
            {6,     "Couldn't detect discs" },
            {7,     "Is using Metric" },
            {8,     "Is using Imperial" },
            {250,   "[Inexisting Value]" },
        };

        public static Dictionary<int, string> Commands = new Dictionary<int, string>
        {
            {0x00,     "Move left" },
            {0x01,     "Move right" },
            {0x02,     "Move forwards" },
            {0x03,     "Move backwards" },
            {0x04,     "Move upwards" },
            {0x05,     "Move downwards" },
            {0x06,     "Activate sucking" },
            {0x07,     "Deactivate sucking" },
            {0x08,     "[A] Light ON" },
            {0x09,     "[A] Light OFF" },
            {0x0A,     "[B] Light ON" },
            {0x0B,     "[B] Light OFF" },
            {0x0C,     "[C] Light ON"},
            {0x0D,     "[C] Light OFF" },
            {0x0E,     "[D] Light ON"  },
            {0x0F,     "[D] Light OFF"},
            {0x10,     "Go to the sorting station" },
            {0x11,     "Go to the weight station" },
            {0x12,     "Start sorting process" },
            {0x13,     "Start weighting process" },
            {0x14,     "Discharge" },
            {0x15,     "UNUSED" },
            {0x16,     "Use metric units" },
            {0x17,     "Use imperial units" },

            {250,       "[Inexisting Command]" },
        };
    }

    /// <summary>
    /// Distinctive class used by the Module Classes
    /// when the specific function: LogAllIn is called.
    /// </summary>
    public static class ModuleLogging
    {
        /// <summary>
        /// Data displayed infront of the logged comments
        /// </summary>
        public static class Headers
        {
            /// <summary>
            /// Header which below it will be all the current data of the module
            /// Leave a white space at the end of your string
            /// </summary>
            public static string Current = "The last, currently stored data of: ";
            /// <summary>
            /// Header which below it will be all the received data of the module
            /// Leave a white space at the end of your string
            /// </summary>
            public static string Received = "All the seen by this module since last print ";
        }

        public static class Types
        {
            public static string Mode = "[MODE]:\t";
            public static string State = "[STATE]:\t";
            public static string Value = "[VALUE]:\t";
            public static string Weight = "[WEIGHT]:\t";
            public static string Command = "[COMMAND]:\t";
        }

        public static class Separators
        {
            public static string Mode = "///////////////////////////////// - [MODES]";
            public static string States = "///////////////////////////////// - [STATES]";
            public static string Values = "///////////////////////////////// - [VALUES]";
            public static string Weight = "///////////////////////////////// - [WEIGHTS]";
            public static string Commands = "///////////////////////////////// - [COMMANDS]";
        }
    }
}
