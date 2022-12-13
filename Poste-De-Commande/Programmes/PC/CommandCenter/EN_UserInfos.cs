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
    public static class Languages
    {
        /// <summary>
        /// Puts the entire form's data in english
        /// </summary>
        public static void SetLanguageToEnglish()
        {
            // This really isn't done properly but im just doing it for the lols with little time on my hands
            #region UserInfos
            #region ComPort
            UserInfos.ComPort.ClosingError = "No serial port linked";
            UserInfos.ComPort.IsOffline = "No serial port linked";
            UserInfos.ComPort.LinkingError = "Failed to link with serial port";
            UserInfos.ComPort.SuccessfulLink = "Serial port linked successfully";
            UserInfos.ComPort.UnexpectedTermination = "Serial port closed unexpectedly";
            UserInfos.ComPort.UserClosed = "User closed serial link";
            UserInfos.ComPort.ClosingError = "Failed to close serial port";
            #endregion ComPort
            #region MasterProtocol
            UserInfos.MasterProtocol.IsOffline = "The CAN bus is offline";
            UserInfos.MasterProtocol.IsOnline = "The CAN bus is online";
            UserInfos.MasterProtocol.IsWaitingForBBB = "Waiting after BeagleBone";
            UserInfos.MasterProtocol.HasStarted = "CAN bus is now operational";
            #endregion MasterProtocol
            #region BeagleBone
            UserInfos.BeagleBone.IsRetryingProcess = "Retrying...";
            UserInfos.BeagleBone.ClosingError = "Failed to close BeagleBone";
            UserInfos.BeagleBone.Closing = "BeagleBone is closing";
            UserInfos.BeagleBone.UserClosed = "BeagleBone Terminated";
            UserInfos.BeagleBone.FatalError = "BeagleBone did a beaglebone";
            UserInfos.BeagleBone.IsNavigatingDirectories = "Navigating BeagleBone's directories";
            UserInfos.BeagleBone.IsLaunchingProgram = "Launching BeagleBone's program";
            UserInfos.BeagleBone.IsAnsweringQuestions = "BeagleBone is answering questions";
            UserInfos.BeagleBone.ProgramLaunching = "Program is launching";
            UserInfos.BeagleBone.SelectedAutomatic = "Program's automatic mode selected";
            UserInfos.BeagleBone.WrongPassword = "BeagleBone's password is invalid";
            UserInfos.BeagleBone.WrongUser = "BeagleBone's user is invalid";
            UserInfos.BeagleBone.WritingUser = "Entering BeagleBone's username";
            UserInfos.BeagleBone.WritingPassword = "Entering BeagleBone's password";
            UserInfos.BeagleBone.WasAlreadyOn = "BeagleBone was already started";
            UserInfos.BeagleBone.WaitingForLifeSignals = "Waiting for a BeagleBone's life signals";
            #endregion BeagleBone
            #region Modules
            UserInfos.Modules.AllAreOnline = "All modules are online";
            UserInfos.Modules.IsUnresponsive = "Not talking on the CAN bus";
            UserInfos.Modules.IsInEmergency = "Module is in emergency mode";
            UserInfos.Modules.WrongStatus = "Module's status is incoherent";
            #region States
            UserInfos.Modules.States.emergencyStop = "Status: In emergency";
            UserInfos.Modules.States.paused = "Status: Paused";
            UserInfos.Modules.States.testing = "Status: self testing";
            UserInfos.Modules.States.processing = "Status: executing a task";
            UserInfos.Modules.States.calibrating = "Status: calibrating";
            UserInfos.Modules.States.calibrated = "Status: is calibrated";
            UserInfos.Modules.States.waiting = "Status: waiting for something";
            UserInfos.Modules.States.safe = "Status: is safe for handling";
            UserInfos.Modules.States.error = "Status: in error";
            UserInfos.Modules.States.atSortingFactory = "Status: at the sorting station";
            UserInfos.Modules.States.atWeightStation = "Status: at the weight station";
            UserInfos.Modules.States.finishedSortingAndHasLoaded = "Status: has loaded the truck";
            UserInfos.Modules.States.waitingToSort = "Status: is waiting to sort";
            UserInfos.Modules.States.waitingToWeight = "Status: is waiting to weight";
            UserInfos.Modules.States.finishedWeighting = "Status: has finished weighting";
            UserInfos.Modules.States.empty = "Status: is empty";
            #endregion States
            #region Specifics_SortingStation
            UserInfos.Modules.SortingStation.emergencyStop = "Sorting station in emergency";
            UserInfos.Modules.SortingStation.paused = "Sorting is paused";
            UserInfos.Modules.SortingStation.testing = "Executing self diagnostic";
            UserInfos.Modules.SortingStation.processing = "Is sorting";
            UserInfos.Modules.SortingStation.calibrating = "Station is calibrating";
            UserInfos.Modules.SortingStation.calibrated = "Station is calibrated";
            UserInfos.Modules.SortingStation.waiting = "Station is not operational";
            UserInfos.Modules.SortingStation.safe = "Station is safe to handle";
            UserInfos.Modules.SortingStation.error = "Status: in error";
            UserInfos.Modules.SortingStation.atSortingFactory = "Error: at the sorting station";
            UserInfos.Modules.SortingStation.atWeightStation = "Error: at the weight station";
            UserInfos.Modules.SortingStation.finishedSortingAndHasLoaded = "Sorting finished, and truck loaded";
            UserInfos.Modules.SortingStation.waitingToSort = "Station is waiting for a truck";
            UserInfos.Modules.SortingStation.waitingToWeight = "Error: is waiting to weight";
            UserInfos.Modules.SortingStation.finishedWeighting = "Error: has finished weighting";
            UserInfos.Modules.SortingStation.empty = "No more discs to sort";
            UserInfos.Modules.SortingStation.DiscIsRed = "Sorting has a red disc";
            UserInfos.Modules.SortingStation.DiscIsBlack = "Sorting has a black disc";
            UserInfos.Modules.SortingStation.DiscIsSilver = "Sorting has a metallic disc";
            UserInfos.Modules.SortingStation.DiscHasNoColor = "Sorting no longer has a disc";
            UserInfos.Modules.SortingStation.DiscNeverDetected = "No disc has been seen";
            #endregion Specifics_SortingStation
            #region Specifics_Vehicle
            UserInfos.Modules.Vehicle.emergencyStop = "Truck in emergency";
            UserInfos.Modules.Vehicle.paused = "Driving is paused";
            UserInfos.Modules.Vehicle.testing = "Error: Executing self test";
            UserInfos.Modules.Vehicle.processing = "Truck is moving";
            UserInfos.Modules.Vehicle.calibrating = "Truck is calibrating";
            UserInfos.Modules.Vehicle.calibrated = "Truck is calibrated";
            UserInfos.Modules.Vehicle.waiting = "Truck is waiting for something";
            UserInfos.Modules.Vehicle.safe = "Truck is safe to handle";
            UserInfos.Modules.Vehicle.error = "Status: in error";
            UserInfos.Modules.Vehicle.atSortingFactory = "Truck is at the sorting station";
            UserInfos.Modules.Vehicle.atWeightStation = "Truck is at the weight station";
            UserInfos.Modules.Vehicle.finishedSortingAndHasLoaded = "Error: Sorting finished";
            UserInfos.Modules.Vehicle.waitingToSort = "Error: waiting to sort";
            UserInfos.Modules.Vehicle.waitingToWeight = "Error: waiting to weight";
            UserInfos.Modules.Vehicle.finishedWeighting = "Error: finished weighting";
            UserInfos.Modules.Vehicle.empty = "Error: is empty";
            #endregion Specifics_Vehicle
            #region Specifics_WeightStation
            UserInfos.Modules.WeightStation.emergencyStop = "Weight station in emergency";
            UserInfos.Modules.WeightStation.paused = "Weighting is paused";
            UserInfos.Modules.WeightStation.testing = "Error: Executing self test";
            UserInfos.Modules.WeightStation.processing = "Weighting blocks";
            UserInfos.Modules.WeightStation.calibrating = "Station is calibrating";
            UserInfos.Modules.WeightStation.calibrated = "Station is calibrated";
            UserInfos.Modules.WeightStation.waiting = "Station is not operational";
            UserInfos.Modules.WeightStation.safe = "Station is safe to handle";
            UserInfos.Modules.WeightStation.error = "Status: in error";
            UserInfos.Modules.WeightStation.atSortingFactory = "Error: at the sorting station";
            UserInfos.Modules.WeightStation.atWeightStation = "Error: at the weight station";
            UserInfos.Modules.WeightStation.finishedSortingAndHasLoaded = "Error: Sorting finished";
            UserInfos.Modules.WeightStation.waitingToSort = "Error: waiting to sort";
            UserInfos.Modules.WeightStation.waitingToWeight = "Station waiting for a loaded truck";
            UserInfos.Modules.WeightStation.finishedWeighting = "Finished weighting discs";
            UserInfos.Modules.WeightStation.empty = "Error: is empty";
            #endregion Specifics_WeightStation
            #endregion Modules
            #region Modes
            UserInfos.Modes.EmergencyDisabled = "Emergency mode disabled";
            UserInfos.Modes.EmergencyEnabled = "EMERGENCY MODE ACTIVATED";
            UserInfos.Modes.OperationStarted = "Standard operation started";
            UserInfos.Modes.NowPaused = "Pausing modules";
            UserInfos.Modes.IsEmergency = "Emergency mode is active!";
            UserInfos.Modes.IsPaused = "Network is paused";
            UserInfos.Modes.IsMaintenance = "Ongoing maintenance";
            UserInfos.Modes.IsTesting = "Ongoing debug";
            UserInfos.Modes.IsOperating = "Network is operating";
            UserInfos.Modes.IsInitialising = "Network is initialising";
            UserInfos.Modes.IsCalibrating = "Ongoing calibration";
            UserInfos.Modes.DoesntExist = "Error: Mode does not exist";
            #region Already
            UserInfos.Modes.Already.Emergency = "Network is already in emergency";
            UserInfos.Modes.Already.Operating = "Network is already operating";
            UserInfos.Modes.Already.Paused = "Network is already paused";
            UserInfos.Modes.Already.Maintenance = "network is already in maintnance";
            UserInfos.Modes.Already.Testing = "Network is already in Technician mode";
            UserInfos.Modes.Already.Initialising = "Network is already initialising";
            UserInfos.Modes.Already.Calibrating = "network is already ongoing calibration";
            #endregion Already
            #endregion Modes
            #region Settings
            UserInfos.Settings.SavingError = "Error occured while saving";
            UserInfos.Settings.SavedAutoConnection = "Saved auto-connecting setting";
            UserInfos.Settings.SavedBaudrate = "Saved baudrate setting";
            UserInfos.Settings.SavedDataBits = "Saved data bit setting";
            UserInfos.Settings.SavedStopBits = "Saved stop bit setting";
            UserInfos.Settings.SavedParity = "Saved parity setting";
            UserInfos.Settings.SavedFlowControl = "Saved flow control setting";
            UserInfos.Settings.SavedRXTimeout = "Saved receiving timeout setting";
            UserInfos.Settings.SavedTXTimeout = "Saved transmitting timeout setting";
            UserInfos.Settings.SavedWeightStationUnit = "Saved unit to use";
            UserInfos.Settings.SavedFilePath = "Saved BeagleBone's program's file path";
            UserInfos.Settings.SavedFileName = "Saved BeagleBone's program's name";
            UserInfos.Settings.SavedPassword = "Saved BeagleBone's password";
            UserInfos.Settings.SavedUser = "Saved BeagleBone's user";
            UserInfos.Settings.SavedLanguage = "Now displayed using english";
            #endregion Settings
            #region Terminal
            UserInfos.Terminal.Cleared = "Terminal has been cleared";
            UserInfos.Terminal.Saved = "New log file created";
            #endregion Terminal
            #region Technician
            UserInfos.Technician.hasStarted = "Enabled technician mode";
            UserInfos.Technician.userStopped = "Disabled technician mode";
            UserInfos.Technician.unexpectedTermination = "Error: Tech mode TERMINATED";
            UserInfos.Technician.nowSimulatingModes = "Mode simulation enabled";
            UserInfos.Technician.stoppedSimulatingModes = "Mode simulation has stopped";
            UserInfos.Technician.configSending = "Sending configuration...";
            UserInfos.Technician.configSent = "Config has been sent!";
            UserInfos.Technician.nowClearingConfigAfterSending = "Continously sending config";
            UserInfos.Technician.stoppedConstantSending = "Continuous config sending stopped";
            UserInfos.Technician.nowKeepingCanOn = "Can network is kept online";
            UserInfos.Technician.stoppedKeepingCanON = "Can network only ON when sending";
            UserInfos.Technician.CanVisualisationClosed = "--,--,--,--,--,--,--,--";
            UserInfos.Technician.CanVisualisationInEmergency = "-EMERGENCY-";
            #endregion Technician
            #endregion UserInfos
            #region LogsInfos
            #region Operation
            LogsInfos.Operations.NowInEmergency = "Network has encountered an emergency stop request";
            LogsInfos.Operations.NoMoreEmergency = "Emergency cancelled from the CommandCenter";
            LogsInfos.Operations.NowOperating = "Operations have started";
            LogsInfos.Operations.NowPaused = "The network has stopped operation and is now waiting to resume";
            LogsInfos.Operations.NowMaintnance = "Maintenance proceedure started";
            LogsInfos.Operations.NowCalibrating = "Calibration proceedure started";
            LogsInfos.Operations.NowTesting = "Debugging session has started";
            LogsInfos.Operations.NowInitialising = "Started initialisation process";
            LogsInfos.Operations.UnexpectedEnd = "Regular operations unexpectedly stopped";
            #region Modules
            LogsInfos.Operations.Modules.NoLongerOnline = " is no longer seen talking on the CAN bus";
            LogsInfos.Operations.Modules.NoLongerOffline = " has started talking on the CAN bus again. This module is potentially experiencing communication errors";
            LogsInfos.Operations.Modules.FirstTimeOnline = " has started talking on the CAN bus";
            LogsInfos.Operations.Modules.YetToBeOnline = " still hasn't been seen communicating on the CAN bus";
            #region Commands
            LogsInfos.Operations.Modules.Commands.UnexpectedData = " tried sending unexisting command";
            LogsInfos.Operations.Modules.Commands.MoveLeft = " asked modules to move left";
            LogsInfos.Operations.Modules.Commands.MoveRight = " asked modules to move right";
            LogsInfos.Operations.Modules.Commands.MoveForwards = " asked modules to move forwards";
            LogsInfos.Operations.Modules.Commands.MoveBackwards = " asked modules to move backwards";
            LogsInfos.Operations.Modules.Commands.MoveUp = " asked modules to move upwards";
            LogsInfos.Operations.Modules.Commands.MoveDown = " asked modules to move downwards";
            LogsInfos.Operations.Modules.Commands.SuctionOn = " has asked to turn ON suction";
            LogsInfos.Operations.Modules.Commands.SuctionOff = " has asked to turn OFF suction";
            LogsInfos.Operations.Modules.Commands.LightAOn = " has sent Light A ON.";
            LogsInfos.Operations.Modules.Commands.LightAOff = " has sent Light A OFF.";
            LogsInfos.Operations.Modules.Commands.LightBOn = " has sent Light B ON.";
            LogsInfos.Operations.Modules.Commands.LightBOff = " has sent Light B OFF.";
            LogsInfos.Operations.Modules.Commands.LightCOn = " has sent Light C ON.";
            LogsInfos.Operations.Modules.Commands.LightCOff = " has sent Light C OFF.";
            LogsInfos.Operations.Modules.Commands.LightDOn = " has sent Light D ON.";
            LogsInfos.Operations.Modules.Commands.LightDOff = " has sent Light D OFF.";
            LogsInfos.Operations.Modules.Commands.GotoSortingStation = " asked modules to go to the sorting station";
            LogsInfos.Operations.Modules.Commands.GotoWeightStation = " asked modules to go to the weight station";
            LogsInfos.Operations.Modules.Commands.UseMetric = "asked modules to now use Metric units";
            LogsInfos.Operations.Modules.Commands.UseImperial = "asked modules to now use Imperial units";
            LogsInfos.Operations.Modules.Commands.Discharge = " has asked modules to discharge";
            LogsInfos.Operations.Modules.Commands.StartSorting = " asked modules to start sorting";
            LogsInfos.Operations.Modules.Commands.StartWeighting = " asked modules to start weighting";
            #endregion Commands
            #region States
            LogsInfos.Operations.Modules.States.IsIncoherent = " is sending a status which does not exist: ";
            LogsInfos.Operations.Modules.States.IsNow.InEmergencyStop = " HAS SEEN OR TRIGGERED THE EMERGENCY PROTOCOL";
            LogsInfos.Operations.Modules.States.IsNow.Paused = " is now paused";
            LogsInfos.Operations.Modules.States.IsNow.Testing = " has started it's self diagnostic proceedure";
            LogsInfos.Operations.Modules.States.IsNow.Processing = " has started executing a task";
            LogsInfos.Operations.Modules.States.IsNow.Calibrating = " has started it's calibration proceedure";
            LogsInfos.Operations.Modules.States.IsNow.Calibrated = " has completed it's calibration";
            LogsInfos.Operations.Modules.States.IsNow.Waiting = " is now waiting for an event";
            LogsInfos.Operations.Modules.States.IsNow.Safe = " is now safe to handle for maintenance";
            LogsInfos.Operations.Modules.States.IsNow.Error = " has encountered an unexpected error. See module for more info";
            LogsInfos.Operations.Modules.States.IsNow.AtSortingfactory = " has arrived at the sorting factory";
            LogsInfos.Operations.Modules.States.IsNow.AtWeightStation = " has arrived at the weight station";
            LogsInfos.Operations.Modules.States.IsNow.WaitingToSort = " is now waiting for an event to start sorting";
            LogsInfos.Operations.Modules.States.IsNow.WaitingToWeight = " is now waiting for an event to start weighting";
            LogsInfos.Operations.Modules.States.IsNow.Empty = " is now empty. Please take the necessary actions";
            LogsInfos.Operations.Modules.States.IsNow.FinishedSortingAndLoaded = " has finished it's sorting proceedure, and loaded the truck";
            LogsInfos.Operations.Modules.States.IsNow.FinishedWeighting = " has finished weighting the given disc";
            #endregion States
            #region Values
            LogsInfos.Operations.Modules.Values.UnexpectedData = " tried sending unexisting value";
            LogsInfos.Operations.Modules.Values.disc_Red = " is now seeing an orange disc";
            LogsInfos.Operations.Modules.Values.disc_Silver = " is now seeing a metallic disc";
            LogsInfos.Operations.Modules.Values.disc_Black = " is now seeing a black disc";
            LogsInfos.Operations.Modules.Values.disc_NoColor = " is no longer seeing any discs";
            LogsInfos.Operations.Modules.Values.disc_Detected = " has detected a disc";
            LogsInfos.Operations.Modules.Values.disc_Lost = " is no longer seeing a previously seen disc";
            LogsInfos.Operations.Modules.Values.disc_CouldNotBeFound = " could not find any discs";
            LogsInfos.Operations.Modules.Values.NowInMetric = " is now using Metric units";
            LogsInfos.Operations.Modules.Values.NowInImperial = " is now using Imperial units";
            #endregion Values
            #region VirtualModes
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Emergency = " is now supposed to be in it's emergency proceedure";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Paused = " is now supposed to have paused ongoing processes";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Maintenance = " should start it's proceedure to be safe for maintenance";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Testing = " should have entered Technician Mode";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Operating = " should now start standard operations";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Initialising = " should be initialising itself";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Calibrating = " should start self calibation proceedure";
            #endregion VirtualModes
            #endregion Modules
            #endregion Operation
            #region Technician
            LogsInfos.Technician.NowEmergency = "Technician debugging tools has detetected an Emergency";
            LogsInfos.Technician.ClosingForSafety = "Debug tools are closing for safety reasons";
            LogsInfos.Technician.NowDebugging = "Technician debugging and simulations started";
            LogsInfos.Technician.userStopped = "User has closed Technician debug session";
            LogsInfos.Technician.UnexpectedEnd = "Technician session came to an unexpected end";
            LogsInfos.Technician.HasSentOnce = "CAN config successfully sent";
            LogsInfos.Technician.DataChangedAnsIsNow = "Data being sent is now: ";
            LogsInfos.Technician.ConfigCleared = "Config reset to default values";
            LogsInfos.Technician.NowSendingConstantly = "Periodic sending has been enabled";
            LogsInfos.Technician.NoLongerSendingConstantly = "Periodic sending has been disabled";
            LogsInfos.Technician.NowClearingConfigWhenSending = "CAN config will now reset after each Send Once";
            LogsInfos.Technician.NoLongerClearingConfig = "CAN config no longer resets after each Send Once";
            LogsInfos.Technician.NowSimulatingModes = "Program is now simulating modes to modules";
            LogsInfos.Technician.NoLongerSimulatingModes = "Program is no longer simulating modes";
            #endregion Technician
            #endregion LogsInfos
            #region PopUpInfos
            #region Header
            PopUpInfos.Header.Warning = "Warning";
            #endregion Header
            PopUpInfos.PleaseReboot = "In order for these changes to take place, please reboot the application";
            PopUpInfos.ThisIsntAvailable = "This mode is not available due to a lack of time and funding, thanks for your understanding";
            #region ModeSwitching
            PopUpInfos.ModeSwitching.DisablingEmergency = "Are you sure you want to disable the ongoing emergency proceedure? Some modules may trigger it back ON if they have not been hard reset manually";
            PopUpInfos.ModeSwitching.IsNotPaused = "Are you sure you want to change the command center's current mode? It is not currently paused and doing this may cause issues";
            #endregion ModeSwitching
            #region Technician
            PopUpInfos.Technician.DoYouWantToPrintInfo = "Do you want to print this module's current data in the terminal? This will clear the terminal first";
            PopUpInfos.Technician.DoYouWantToSaveInstead = "Do you want to save the current terminal instead of just clearing it?";
            #endregion Technician
            #endregion PopUpInfos
            #region WeightInfos
            WeightInfos.isOffline = "OFF";
            WeightInfos.isEmpty = "Empt";
            WeightInfos.Units.Metric = "g";
            WeightInfos.Units.Imperial = "oz";
            WeightInfos.Units.UnknownUnit = "?";
            WeightInfos.isOnlineButNoValue = "--";
            WeightInfos.isError = "ERR";
            #endregion WeightInfos
            #region ListInfos
            #region Modes
            ListsInfos.Modes[0] = "Emergency Stop";
            ListsInfos.Modes[1] = "Pause";
            ListsInfos.Modes[2] = "Technician";
            ListsInfos.Modes[3] = "Maintenance";
            ListsInfos.Modes[4] = "Stand. Operations";
            ListsInfos.Modes[5] = "Calibration";
            ListsInfos.Modes[6] = "Initialisations";
            ListsInfos.Modes[250] = "[Inexisting Mode]";
            #endregion Modes
            #region DataTypes
            ListsInfos.DataTypes[0] = "None";
            ListsInfos.DataTypes[1] = "Command";
            ListsInfos.DataTypes[2] = "Value";
            ListsInfos.DataTypes[3] = "State";
            #endregion DataTypes
            #region States
            ListsInfos.States[0] = "In emergency";
            ListsInfos.States[1] = "Is paused";
            ListsInfos.States[2] = "Self diagnosing";
            ListsInfos.States[3] = "Is processing";
            ListsInfos.States[4] = "In operation";
            ListsInfos.States[5] = "Is calibrating";
            ListsInfos.States[6] = "Is calibrated";
            ListsInfos.States[7] = "Is waiting";
            ListsInfos.States[8] = "Is safe";
            ListsInfos.States[9] = "Has an Error";
            ListsInfos.States[10] = "At sorting station";
            ListsInfos.States[11] = "At weight station";
            ListsInfos.States[12] = "Finished sorting and loaded";
            ListsInfos.States[13] = "Is waiting to sort";
            ListsInfos.States[14] = "Is waiting to weight";
            ListsInfos.States[15] = "Has finished weighting";
            ListsInfos.States[16] = "Is empty";
            ListsInfos.States[250] = "[Inexisting State]";
            #endregion States
            #region Values
            ListsInfos.Values[0] =    "Has an orange disc";
            ListsInfos.Values[1] =    "Has a metallic disc";
            ListsInfos.Values[2] =    "Has a black disc";
            ListsInfos.Values[3] =    "No longer see colors";
            ListsInfos.Values[4] =    "Has detected a disc";
            ListsInfos.Values[5] =    "No longer detects discs";
            ListsInfos.Values[6] =    "Couldn't detect discs";
            ListsInfos.Values[7] =    "Is using Metric";
            ListsInfos.Values[8] =    "Is using Imperial";
            ListsInfos.Values[250] =   "[Inexisting Value]";
            #endregion Values
            #region Commands
            ListsInfos.Commands[0x00] = "Move left";
            ListsInfos.Commands[0x01] = "Move right";
            ListsInfos.Commands[0x02] = "Move forwards";
            ListsInfos.Commands[0x03] = "Move backwards";
            ListsInfos.Commands[0x04] = "Move upwards";
            ListsInfos.Commands[0x05] = "Move downwards";
            ListsInfos.Commands[0x06] = "Activate sucking";
            ListsInfos.Commands[0x07] = "Deactivate sucking";
            ListsInfos.Commands[0x08] = "[A] Light ON";
            ListsInfos.Commands[0x09] = "[A] Light OFF";
            ListsInfos.Commands[0x0A] = "[B] Light ON";
            ListsInfos.Commands[0x0B] = "[B] Light OFF";
            ListsInfos.Commands[0x0C] = "[C] Light ON";
            ListsInfos.Commands[0x0D] = "[C] Light OFF";
            ListsInfos.Commands[0x0E] = "[D] Light ON";
            ListsInfos.Commands[0x0F] = "[D] Light OFF";
            ListsInfos.Commands[0x10] = "Go to the sorting station";
            ListsInfos.Commands[0x11] = "Go to the weight station";
            ListsInfos.Commands[0x12] = "Start sorting process";
            ListsInfos.Commands[0x13] = "Start weighting process";
            ListsInfos.Commands[0x14] = "Discharge";
            ListsInfos.Commands[0x15] = "UNUSED";
            ListsInfos.Commands[0x16] = "Use metric units";
            ListsInfos.Commands[0x17] = "Use imperial units";
            ListsInfos.Commands[250] = "[Inexisting Command]";
            #endregion Commands
            #endregion ListInfos
            #region ModuleLogging
            ModuleLogging.DataResetWarning = "This module's received data has been flushed";
            ModuleLogging.DataUnavaibale = "DISABLED";
            #region Headers
            ModuleLogging.Headers.Current = "The last, currently stored data of: ";
            ModuleLogging.Headers.Received = "All the seen by this module since last print ";
            #endregion Headers
            #region Types
            ModuleLogging.Types.Mode = "[MODE]:\t";
            ModuleLogging.Types.State = "[STATE]:\t";
            ModuleLogging.Types.Value = "[VALUE]:\t";
            ModuleLogging.Types.Weight = "[WEIGHT]:\t";
            ModuleLogging.Types.Command = "[COMMAND]:\t";
            #endregion Types
            #region Separator
            ModuleLogging.Separators.Mode = "///////////////////////////////// - [MODES]";
            ModuleLogging.Separators.States = "///////////////////////////////// - [STATES]";
            ModuleLogging.Separators.Values = "///////////////////////////////// - [VALUES]";
            ModuleLogging.Separators.Weight = "///////////////////////////////// - [WEIGHTS]";
            ModuleLogging.Separators.Commands = "///////////////////////////////// - [COMMANDS]";
            #endregion Separator

            #endregion ModuleLogging
            #region Tab_Names
            Tab_Names.Operation = "Operation";
            Tab_Names.Technician = "Technician";
            Tab_Names.Calibration = "Calibration";
            Tab_Names.Maintenance = "Maintenance";
            Tab_Names.Terminal = "Terminal";
            Tab_Names.Settings = "Settings";
            #endregion Tab_Names
            #region Text_Labels
            Label_Names.Label_User = "User:";
            Label_Names.Label_Password = "Password:";
            Label_Names.Label_FileName = "File name:";
            Label_Names.Label_FilePath = "File path:";
            Label_Names.Label_AutoConnect = "Auto Con.";
            Label_Names.Label_Language = "Language:";
            Label_Names.Label_ScaleUnit = "Scale Unit:";
            Label_Names.Technician_Label_Mode = "Mode";
            Label_Names.Technician_Label_Status = "Status";
            Label_Names.Technician_Label_DataTypeA = "Data type A";
            Label_Names.Technician_Label_DataTypeB = "Data type B";
            Label_Names.Technician_Label_DataA = "Data A";
            Label_Names.Technician_Label_DataB = "Data B";
            Label_Names.Technician_Label_CanOutput = "CAN Output:";
            Label_Names.Technician_Label_SimulateModes = "Simulate Modes";
            Label_Names.Technician_Label_KeepCanOn = "Keep CAN Online";
            Label_Names.Technician_Label_ClearAfterSend = "Clear After";
            Label_Names.Technician_Label_SendOnce = "Send Once";
            #endregion Text_Labels
            #region ToolTips
            #endregion ToolTips
            #region ModuleNames
            Module_Names.SortingStation = "Sorting Station";
            Module_Names.Vehicle = "Vehicle";
            Module_Names.WeightStation = "Weight Station";
            Module_Names.OfflineModules = "Offline modules: ";
            #endregion ModuleNames
        }
        /// <summary>
        /// Puts the entire form's printed data and logged data
        /// in french
        /// </summary>
        public static void SetLanguageToFrench()
        {
            // This really isn't done properly but im just doing it for the lols with little time on my hands
            #region UserInfos
            #region ComPort
            UserInfos.ComPort.ClosingError = "Aucun port série connecté";
            UserInfos.ComPort.IsOffline = "Port série hors ligne";
            UserInfos.ComPort.LinkingError = "Erreur de connection au port série";
            UserInfos.ComPort.SuccessfulLink = "Port série connecté";
            UserInfos.ComPort.UnexpectedTermination = "ERREUR: Port série s'est fermé";
            UserInfos.ComPort.UserClosed = "Le port série à été fermé";
            UserInfos.ComPort.ClosingError = "Le port série ne peut être fermé";
            #endregion ComPort
            #region MasterProtocol
            UserInfos.MasterProtocol.IsOffline = "Le bus CAN est hors ligne";
            UserInfos.MasterProtocol.IsOnline = "Le bus CAN est opérationel";
            UserInfos.MasterProtocol.IsWaitingForBBB = "En attente du BeagleBone";
            UserInfos.MasterProtocol.HasStarted = "Le bus CAN a démarré";
            #endregion MasterProtocol
            #region BeagleBone
            UserInfos.BeagleBone.IsRetryingProcess = "Réessaye...";
            UserInfos.BeagleBone.ClosingError = "Erreur lors de la fermeture du BBB";
            UserInfos.BeagleBone.Closing = "Le BeagleBone se ferme";
            UserInfos.BeagleBone.UserClosed = "Le BeagleBone a été fermé";
            UserInfos.BeagleBone.FatalError = "Le beaglebone a bruh solide";
            UserInfos.BeagleBone.IsNavigatingDirectories = "En recherche d'emplacements...";
            UserInfos.BeagleBone.IsLaunchingProgram = "Essaie de démarrer le programme";
            UserInfos.BeagleBone.IsAnsweringQuestions = "Le program réponds aux questions";
            UserInfos.BeagleBone.ProgramLaunching = "Le program démarre";
            UserInfos.BeagleBone.SelectedAutomatic = "Mode automatique sélectionné";
            UserInfos.BeagleBone.WrongPassword = "Le mot de passe n'est pas valide";
            UserInfos.BeagleBone.WrongUser = "L'utilisateur n'est pas valide";
            UserInfos.BeagleBone.WritingUser = "Écriture de l'utilisateur";
            UserInfos.BeagleBone.WritingPassword = "Écriture du mot de passe";
            UserInfos.BeagleBone.WasAlreadyOn = "Le BeagleBone était déja allumé";
            UserInfos.BeagleBone.WaitingForLifeSignals = "En attente de signaux de vie";
            #endregion BeagleBone
            #region Modules
            UserInfos.Modules.AllAreOnline = "Tous les modules sont en ligne";
            UserInfos.Modules.IsUnresponsive = "Ne réponds pas sur le CAN";
            UserInfos.Modules.IsInEmergency = "En état d'urgence";
            UserInfos.Modules.WrongStatus = "L'état n'est pas cohérent";
            #region States
            UserInfos.Modules.States.emergencyStop = "État: En urgence";
            UserInfos.Modules.States.paused = "État: En arrêt";
            UserInfos.Modules.States.testing = "État: diagnostic de soi-même";
            UserInfos.Modules.States.processing = "État: en traitement";
            UserInfos.Modules.States.calibrating = "État: en calibration";
            UserInfos.Modules.States.calibrated = "État: est calibré";
            UserInfos.Modules.States.waiting = "État: en attente de quelque chose";
            UserInfos.Modules.States.safe = "État: est sécuritaire";
            UserInfos.Modules.States.error = "État: en erreur";
            UserInfos.Modules.States.atSortingFactory = "État: à la station de tri";
            UserInfos.Modules.States.atWeightStation = "État: à la station de peser";
            UserInfos.Modules.States.finishedSortingAndHasLoaded = "État: a charger le camion";
            UserInfos.Modules.States.waitingToSort = "État: en attente de tri";
            UserInfos.Modules.States.waitingToWeight = "État: en attente de peser";
            UserInfos.Modules.States.finishedWeighting = "État: terminé de peser";
            UserInfos.Modules.States.empty = "État: est vide";
            #endregion States
            #region Specifics_SortingStation
            UserInfos.Modules.SortingStation.emergencyStop = "Le centre de tri est en urgence";
            UserInfos.Modules.SortingStation.paused = "Le tri est en arrêt";
            UserInfos.Modules.SortingStation.testing = "En mode de test";
            UserInfos.Modules.SortingStation.processing = "Tri en cours";
            UserInfos.Modules.SortingStation.calibrating = "En calibration";
            UserInfos.Modules.SortingStation.calibrated = "Est calibré";
            UserInfos.Modules.SortingStation.waiting = "Non opérationel";
            UserInfos.Modules.SortingStation.safe = "Est sécuritaire";
            UserInfos.Modules.SortingStation.error = "En erreur";
            UserInfos.Modules.SortingStation.atSortingFactory = "Au centre de tri?";
            UserInfos.Modules.SortingStation.atWeightStation = "A la station de peser?";
            UserInfos.Modules.SortingStation.finishedSortingAndHasLoaded = "Tri terminé et camion chargé";
            UserInfos.Modules.SortingStation.waitingToSort = "En attente d'un camion";
            UserInfos.Modules.SortingStation.waitingToWeight = "En attente de peser??";
            UserInfos.Modules.SortingStation.finishedWeighting = "terminé la peser?";
            UserInfos.Modules.SortingStation.empty = "N'a pas plus de rondelles";
            UserInfos.Modules.SortingStation.DiscIsRed = "Tri une rondelle orange";
            UserInfos.Modules.SortingStation.DiscIsBlack = "Tri une rondelle noir";
            UserInfos.Modules.SortingStation.DiscIsSilver = "Tri une rondelle métallique";
            UserInfos.Modules.SortingStation.DiscHasNoColor = "Aucune couleur détectée";
            UserInfos.Modules.SortingStation.DiscNeverDetected = "Rondelles jamais détectées";
            #endregion Specifics_SortingStation
            #region Specifics_Vehicle
            UserInfos.Modules.Vehicle.emergencyStop = "Camion en urgence";
            UserInfos.Modules.Vehicle.paused = "Conduite en arrêt";
            UserInfos.Modules.Vehicle.testing = "Se test lui-même?";
            UserInfos.Modules.Vehicle.processing = "En conduite";
            UserInfos.Modules.Vehicle.calibrating = "En calibration";
            UserInfos.Modules.Vehicle.calibrated = "Est calibré";
            UserInfos.Modules.Vehicle.waiting = "En attente de quelque chose";
            UserInfos.Modules.Vehicle.safe = "Est sécuritaire";
            UserInfos.Modules.Vehicle.error = "En erreur";
            UserInfos.Modules.Vehicle.atSortingFactory = "Au centre de tri";
            UserInfos.Modules.Vehicle.atWeightStation = "À la station de peser";
            UserInfos.Modules.Vehicle.finishedSortingAndHasLoaded = "Tri terminé???";
            UserInfos.Modules.Vehicle.waitingToSort = "En attente de tri???";
            UserInfos.Modules.Vehicle.waitingToWeight = "En attente de peser???";
            UserInfos.Modules.Vehicle.finishedWeighting = "A terminer de peser";
            UserInfos.Modules.Vehicle.empty = "Est vide??";
            #endregion Specifics_Vehicle
            #region Specifics_WeightStation
            UserInfos.Modules.WeightStation.emergencyStop = "Station de pesé en urgence";
            UserInfos.Modules.WeightStation.paused = "La pesé est en arrêt";
            UserInfos.Modules.WeightStation.testing = "En mode de test";
            UserInfos.Modules.WeightStation.processing = "Pese des rondelles";
            UserInfos.Modules.WeightStation.calibrating = "En calibration";
            UserInfos.Modules.WeightStation.calibrated =  "Est calibré";
            UserInfos.Modules.WeightStation.waiting = "En attente";
            UserInfos.Modules.WeightStation.safe = "Est sécuritaire";
            UserInfos.Modules.WeightStation.error = "En erreur";
            UserInfos.Modules.WeightStation.atSortingFactory = "Au centre de tri???";
            UserInfos.Modules.WeightStation.atWeightStation = "A lui-même???";
            UserInfos.Modules.WeightStation.finishedSortingAndHasLoaded = "A fini de trier???";
            UserInfos.Modules.WeightStation.waitingToSort = "En attente de tri???";
            UserInfos.Modules.WeightStation.waitingToWeight = "En attente d'un camion chargé";
            UserInfos.Modules.WeightStation.finishedWeighting = "Terminé de peser des rondelles";
            UserInfos.Modules.WeightStation.empty = "Est vide?";
            #endregion Specifics_WeightStation
            #endregion Modules
            #region Modes
            UserInfos.Modes.EmergencyDisabled = "Le mode d'urgence est désactivé";
            UserInfos.Modes.EmergencyEnabled = "MODE D'URGENCE ACTIVÉ";
            UserInfos.Modes.OperationStarted = "Les opérations débutent";
            UserInfos.Modes.NowPaused = "Les moduls sont en arrêts";
            UserInfos.Modes.IsEmergency = "Un état d'urgence est activé";
            UserInfos.Modes.IsPaused = "Le réseau est en arrêt";
            UserInfos.Modes.IsMaintenance = "Le réseau est en maintenance";
            UserInfos.Modes.IsTesting = "Le réseau est sous déboggage";
            UserInfos.Modes.IsOperating = "Le réseau opère correctement";
            UserInfos.Modes.IsInitialising = "Le réseau est en initialisation";
            UserInfos.Modes.IsCalibrating = "Le réseau se calibre";
            UserInfos.Modes.DoesntExist = "Le mode n'existe pas";
            #region Already
            UserInfos.Modes.Already.Emergency = "Le réseau est déja en urgence";
            UserInfos.Modes.Already.Operating = "Le réseau est déja en opération";
            UserInfos.Modes.Already.Paused = "Le réseau est déja en arret";
            UserInfos.Modes.Already.Maintenance = "Le réseau est déja en maintenance";
            UserInfos.Modes.Already.Testing = "Le réseau est déja en technicien";
            UserInfos.Modes.Already.Initialising = "le réseau est déja en initialisation";
            UserInfos.Modes.Already.Calibrating = "Le réseau est déja en calibration";
            #endregion Already
            #endregion Modes
            #region Settings
            UserInfos.Settings.SavingError = "Une erreur est survenue lors de la sauvegarde";
            UserInfos.Settings.SavedAutoConnection = "Sauvegarde de la connection automatique";
            UserInfos.Settings.SavedBaudrate = "Sauvegarde du paramètre de baudrate";
            UserInfos.Settings.SavedDataBits = "Sauvegarde du paramètre de data bit";
            UserInfos.Settings.SavedStopBits = "Sauvegarde du bit d'arrêt";
            UserInfos.Settings.SavedParity = "Sauvegarde du paramètre de parité";
            UserInfos.Settings.SavedFlowControl = "Sauvegarde du paramètre de  flow control";
            UserInfos.Settings.SavedRXTimeout = "Sauvegarde du temps limite de récepion";
            UserInfos.Settings.SavedTXTimeout = "Sauvegarde du temps limite de transmission";
            UserInfos.Settings.SavedWeightStationUnit = "Sauvegarde du paramètre de l'unité à utiliser";
            UserInfos.Settings.SavedFilePath = "Sauvegarde du path des fichiers d'execution";
            UserInfos.Settings.SavedFileName = "Sauvegarde du nom de programme";
            UserInfos.Settings.SavedPassword = "Sauvegarde du mot de passe";
            UserInfos.Settings.SavedUser = "Sauvegarde du nom de l'utilisateur";
            UserInfos.Settings.SavedLanguage = "Maintenant affiché en baguette";
            #endregion Settings
            #region Terminal
            UserInfos.Terminal.Cleared = "La console a été réinitialisé";
            UserInfos.Terminal.Saved = "un nouveau fichier de logs à été sauvegardé";
            #endregion Terminal
            #region Technician
            UserInfos.Technician.hasStarted = "Mode technicien activé";
            UserInfos.Technician.userStopped = "Mode technicien arrêté";
            UserInfos.Technician.unexpectedTermination = "Mode technicien résilié";
            UserInfos.Technician.nowSimulatingModes = "La simulation de modes est activée";
            UserInfos.Technician.stoppedSimulatingModes = "Arrêt de la simulation de modes";
            UserInfos.Technician.configSending = "Envoie de la configuration...";
            UserInfos.Technician.configSent = "la configuration a été envoyé";
            UserInfos.Technician.nowClearingConfigAfterSending = "Envoie continuel de la configuration";
            UserInfos.Technician.stoppedConstantSending = "Arrêt de l'envoie continuel";
            UserInfos.Technician.nowKeepingCanOn = "Le bus CAN est maintenant tout le temps en ligne";
            UserInfos.Technician.stoppedKeepingCanON = "Le bus CAN est actif que si l'on envoie";
            UserInfos.Technician.CanVisualisationClosed = "--,--,--,--,--,--,--,--";
            UserInfos.Technician.CanVisualisationInEmergency = "-URGENCE-";
            #endregion Technician
            #endregion UserInfos
            #region LogsInfos
            #region Operation
            LogsInfos.Operations.NowInEmergency = "Le réseau à rencontré une demande de mode d'urgence";
            LogsInfos.Operations.NoMoreEmergency = "le réseau n'est plus en état d'urgence";
            LogsInfos.Operations.NowOperating = "Début des operations standards";
            LogsInfos.Operations.NowPaused = "Le réseau est maintenant en pause et en attente d'une requète";
            LogsInfos.Operations.NowMaintnance = "La maintenance des modules a débuté";
            LogsInfos.Operations.NowCalibrating = "la calibration des modules a débuté";
            LogsInfos.Operations.NowTesting = "La session de deboggage a débuté";
            LogsInfos.Operations.NowInitialising = "La séquence d'initialisation a débuté";
            LogsInfos.Operations.UnexpectedEnd = "Le réseau s'est fermé sans avis";
            #region Modules
            LogsInfos.Operations.Modules.NoLongerOnline = " Ne parle plus sur le CAN";
            LogsInfos.Operations.Modules.NoLongerOffline = " a recommencer a parler sur le réseau CAN. Ce module peut avoir des difficultés de communications";
            LogsInfos.Operations.Modules.FirstTimeOnline = " a commencer à parler sur le réseau CAN";
            LogsInfos.Operations.Modules.YetToBeOnline = " n'a pas encore été vu en ligne depuis le début";
            #region Commands
            LogsInfos.Operations.Modules.Commands.UnexpectedData = " A essayé d'envoyer une commande inexistante";
            LogsInfos.Operations.Modules.Commands.MoveLeft = " A demander aux modules de bouger a gauche";
            LogsInfos.Operations.Modules.Commands.MoveRight = " asked modules to move right";
            LogsInfos.Operations.Modules.Commands.MoveForwards = " asked modules to move forwards";
            LogsInfos.Operations.Modules.Commands.MoveBackwards = " asked modules to move backwards";
            LogsInfos.Operations.Modules.Commands.MoveUp = " asked modules to move upwards";
            LogsInfos.Operations.Modules.Commands.MoveDown = " asked modules to move downwards";
            LogsInfos.Operations.Modules.Commands.SuctionOn = " has asked to turn ON suction";
            LogsInfos.Operations.Modules.Commands.SuctionOff = " has asked to turn OFF suction";
            LogsInfos.Operations.Modules.Commands.LightAOn = " has sent Light A ON.";
            LogsInfos.Operations.Modules.Commands.LightAOff = " has sent Light A OFF.";
            LogsInfos.Operations.Modules.Commands.LightBOn = " has sent Light B ON.";
            LogsInfos.Operations.Modules.Commands.LightBOff = " has sent Light B OFF.";
            LogsInfos.Operations.Modules.Commands.LightCOn = " has sent Light C ON.";
            LogsInfos.Operations.Modules.Commands.LightCOff = " has sent Light C OFF.";
            LogsInfos.Operations.Modules.Commands.LightDOn = " has sent Light D ON.";
            LogsInfos.Operations.Modules.Commands.LightDOff = " has sent Light D OFF.";
            LogsInfos.Operations.Modules.Commands.GotoSortingStation = " asked modules to go to the sorting station";
            LogsInfos.Operations.Modules.Commands.GotoWeightStation = " asked modules to go to the weight station";
            LogsInfos.Operations.Modules.Commands.UseMetric = "asked modules to now use Metric units";
            LogsInfos.Operations.Modules.Commands.UseImperial = "asked modules to now use Imperial units";
            LogsInfos.Operations.Modules.Commands.Discharge = " has asked modules to discharge";
            LogsInfos.Operations.Modules.Commands.StartSorting = " asked modules to start sorting";
            LogsInfos.Operations.Modules.Commands.StartWeighting = " asked modules to start weighting";
            #endregion Commands
            #region States
            LogsInfos.Operations.Modules.States.IsIncoherent = " envoie un état qui n'existe pas: ";
            LogsInfos.Operations.Modules.States.IsNow.InEmergencyStop = " A VU OU DÉCLENCHÉ L'ÉTAT D'URGENCE";
            LogsInfos.Operations.Modules.States.IsNow.Paused = " est maintenant en arrêt";
            LogsInfos.Operations.Modules.States.IsNow.Testing = " A débuter sa procédure de test";
            LogsInfos.Operations.Modules.States.IsNow.Processing = " a débuté l'execution d'une tâche";
            LogsInfos.Operations.Modules.States.IsNow.Calibrating = " A débuter la calibration";
            LogsInfos.Operations.Modules.States.IsNow.Calibrated = " A terminé la calibration";
            LogsInfos.Operations.Modules.States.IsNow.Waiting = " est en attente d'un evenement";
            LogsInfos.Operations.Modules.States.IsNow.Safe = " est maintenant sécuritaire et disponible pour la maintenance";
            LogsInfos.Operations.Modules.States.IsNow.Error = " est tombé sur une erreur comme ça juste de-même";
            LogsInfos.Operations.Modules.States.IsNow.AtSortingfactory = " est arrivé au centre de tri";
            LogsInfos.Operations.Modules.States.IsNow.AtWeightStation = " est arrivé à la station de pesé";
            LogsInfos.Operations.Modules.States.IsNow.WaitingToSort = " est maintenant en attente d'un evenement pour débuter le tri";
            LogsInfos.Operations.Modules.States.IsNow.WaitingToWeight = " est maintenant en attente d'un evenement pour débuter la pesé";
            LogsInfos.Operations.Modules.States.IsNow.Empty = " est maintenant vide. Merci d'effectuer les actions nécessaires afin de remédier à la situation";
            LogsInfos.Operations.Modules.States.IsNow.FinishedSortingAndLoaded = " a terminé son tri et a chargé le camion";
            LogsInfos.Operations.Modules.States.IsNow.FinishedWeighting = " a terminé la pesé";
            #endregion States
            #region Values
            LogsInfos.Operations.Modules.Values.UnexpectedData = " a essayé d'envoyé une valeurs inexistante";
            LogsInfos.Operations.Modules.Values.disc_Red = " a vu une rondelle orange";
            LogsInfos.Operations.Modules.Values.disc_Silver = " a vu une rondelle métallique";
            LogsInfos.Operations.Modules.Values.disc_Black = " a vu une rondelle noir";
            LogsInfos.Operations.Modules.Values.disc_NoColor = " ne voit plus de couleurs";
            LogsInfos.Operations.Modules.Values.disc_Detected = " a détecté une rondelle";
            LogsInfos.Operations.Modules.Values.disc_Lost = " ne détecte plus de rondelles";
            LogsInfos.Operations.Modules.Values.disc_CouldNotBeFound = " n'a pas réussi à détecter une rondelle";
            LogsInfos.Operations.Modules.Values.NowInMetric = " utilise maintenant des unités métriques";
            LogsInfos.Operations.Modules.Values.NowInImperial = " utilise maintenant des unités impériales";
            #endregion Values
            #region VirtualModes
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Emergency = " est maintenant supposé êre en état d'urgence";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Paused = " est maintenant supposé avoir arrêté de faire ce qu'il fesait";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Maintenance = " deverait débuté une maintenance";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Testing = " deverait entré en mode technicien";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Operating = " deverait débuté sa procédure d'opération standard";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Initialising = " deverait être en initialisation";
            LogsInfos.Operations.Modules.VirtualModes.IsNow.Calibrating = " deverait débuté sa procédure de calibration";
            #endregion VirtualModes
            #endregion Modules
            #endregion Operation
            #region Technician
            LogsInfos.Technician.NowEmergency = "Le mode technicien a détecté une requete d'urgence";
            LogsInfos.Technician.ClosingForSafety = "Les outils de déboggage se ferme par mesure de sécurité";
            LogsInfos.Technician.NowDebugging = "Le déboggage a commencé";
            LogsInfos.Technician.userStopped = "L'utilisateur a mis fin a la session de déboggage";
            LogsInfos.Technician.UnexpectedEnd = "Le mode technicien s'est fermé sans aucun avis";
            LogsInfos.Technician.HasSentOnce = "La configuration CAN s'est envoyé sans échec";
            LogsInfos.Technician.DataChangedAnsIsNow = "La trame CAN est maintenant: ";
            LogsInfos.Technician.ConfigCleared = "La configuration s'est initialisé aux valeurs par défaut";
            LogsInfos.Technician.NowSendingConstantly = "L'envoie continuel est maintenant activée";
            LogsInfos.Technician.NoLongerSendingConstantly = "L'envoie continuel est maintenant désactivée";
            LogsInfos.Technician.NowClearingConfigWhenSending = "La configuration CAN sera maintenant initialisé à chaque envoie";
            LogsInfos.Technician.NoLongerClearingConfig = "la configuration CAN ne sera plus initialisé après chaque envoie";
            LogsInfos.Technician.NowSimulatingModes = "Le programme simule maintenant les modes";
            LogsInfos.Technician.NoLongerSimulatingModes = "Le program ne simule plus les modes";
            #endregion Technician
            #endregion LogsInfos
            #region PopUpInfos
            #region Header
            PopUpInfos.Header.Warning = "Attention";
            #endregion Header
            PopUpInfos.PleaseReboot = "Pour que ces changements s'effectuent, veuillez redémarrer l'application";
            PopUpInfos.ThisIsntAvailable = "Il faut accepter que l'on a pas le temps de tout faire!";
            #region ModeSwitching
            PopUpInfos.ModeSwitching.DisablingEmergency = "Voulez vous vraiment terminer la procédure d'urgence actuellement en cours? Certains modules peuvent la réactivé s'il ne sont pas réinitialisé manuellement";
            PopUpInfos.ModeSwitching.IsNotPaused = "Voulez vous vraiment changer le mode envoyé aux modules? Étant donné que vous n'êtes pas en pause, certains modules pourraient tomber dans un mode d'erreur";
            #endregion ModeSwitching
            #region Technician
            PopUpInfos.Technician.DoYouWantToPrintInfo = "Voulez vous imprimer les informations relatif à ce module? Cela vas effacer les donnés actuellement présente dans la console";
            PopUpInfos.Technician.DoYouWantToSaveInstead = "Voulez vous sauvegarder le contenue de la console au lieu de le suprimer?";
            #endregion Technician
            #endregion PopUpInfos
            #region WeightInfos
            WeightInfos.isOffline = "OFF";
            WeightInfos.isEmpty = "Vide";
            WeightInfos.Units.Metric = "g";
            WeightInfos.Units.Imperial = "oz";
            WeightInfos.Units.UnknownUnit = "?";
            WeightInfos.isOnlineButNoValue = "--";
            WeightInfos.isError = "ERR";
            #endregion WeightInfos
            #region ListInfos
            #region Modes
            ListsInfos.Modes[0] = "Arrêt d'urgence";
            ListsInfos.Modes[1] = "Pause";
            ListsInfos.Modes[2] = "Technicien";
            ListsInfos.Modes[3] = "Maintenance";
            ListsInfos.Modes[4] = "Opérations";
            ListsInfos.Modes[5] = "Calibration";
            ListsInfos.Modes[6] = "Initialisations";
            ListsInfos.Modes[250] = "[Mode inexistant]";
            #endregion Modes
            #region DataTypes
            ListsInfos.DataTypes[0] = "Aucun";
            ListsInfos.DataTypes[1] = "Commandes";
            ListsInfos.DataTypes[2] = "Valeur";
            ListsInfos.DataTypes[3] = "État";
            #endregion DataTypes
            #region States
            ListsInfos.States[0] = "En Urgence";
            ListsInfos.States[1] = "En Pause";
            ListsInfos.States[2] = "En diagnostic";
            ListsInfos.States[3] = "En traitement";
            ListsInfos.States[4] = "En opération";
            ListsInfos.States[5] = "En calibration";
            ListsInfos.States[6] = "Est calibré";
            ListsInfos.States[7] = "En attente";
            ListsInfos.States[8] = "Sécuritaire";
            ListsInfos.States[9] = "En erreur";
            ListsInfos.States[10] = "À l'usine de tri";
            ListsInfos.States[11] = "À la station de peser";
            ListsInfos.States[12] = "Fini de trier et chargé";
            ListsInfos.States[13] = "En attente de tri";
            ListsInfos.States[14] = "En attente de pesé";
            ListsInfos.States[15] = "Terminé la pesé";
            ListsInfos.States[16] = "Est vide";
            ListsInfos.States[250] = "[État inexistant]";
            #endregion States
            #region Values
            ListsInfos.Values[0] = "A une rondelle orange";
            ListsInfos.Values[1] = "A une rondelle metallique";
            ListsInfos.Values[2] = "A une rondelle noir";
            ListsInfos.Values[3] = "Ne voit plus de couleurs";
            ListsInfos.Values[4] = "A détecté une rondelle";
            ListsInfos.Values[5] = "A perdu la rondelle";
            ListsInfos.Values[6] = "N'a pas trouvé de rondelle";
            ListsInfos.Values[7] = "Utilise les unités métriques";
            ListsInfos.Values[8] = "Utilise les unités impériaux";
            ListsInfos.Values[250] = "[Valeurs inexistante]";
            #endregion Values
            #region Commands
            ListsInfos.Commands[0x00] = "Bouge à gauche";
            ListsInfos.Commands[0x01] = "Bouge à droite";
            ListsInfos.Commands[0x02] = "Bouge tout droit";
            ListsInfos.Commands[0x03] = "Bouge vers l'arrière";
            ListsInfos.Commands[0x04] = "Bouge vers le haut";
            ListsInfos.Commands[0x05] = "Bouge vers le bas";
            ListsInfos.Commands[0x06] = "Active le succ";
            ListsInfos.Commands[0x07] = "Désactive le succ";
            ListsInfos.Commands[0x08] = "[A] DEL ON";
            ListsInfos.Commands[0x09] = "[A] DEL OFF";
            ListsInfos.Commands[0x0A] = "[B] DEL ON";
            ListsInfos.Commands[0x0B] = "[B] DEL OFF";
            ListsInfos.Commands[0x0C] = "[C] DEL ON";
            ListsInfos.Commands[0x0D] = "[C] DEL OFF";
            ListsInfos.Commands[0x0E] = "[D] DEL ON";
            ListsInfos.Commands[0x0F] = "[D] DEL OFF";
            ListsInfos.Commands[0x10] = "Vas au centre de tri";
            ListsInfos.Commands[0x11] = "Vas à la station de pesé";
            ListsInfos.Commands[0x12] = "Débute un tri";
            ListsInfos.Commands[0x13] = "Débute une pesé";
            ListsInfos.Commands[0x14] = "Décharge";
            ListsInfos.Commands[0x15] = "UNUSED";
            ListsInfos.Commands[0x16] = "Utilise les unités métriques";
            ListsInfos.Commands[0x17] = "Utilise les unités impériaux";
            ListsInfos.Commands[250] = "[Commande inexistante]";
            #endregion Commands
            #endregion ListInfos
            #region ModuleLogging
            ModuleLogging.DataResetWarning = "les données de ce modules ont été supprimés";
            ModuleLogging.DataUnavaibale = "DÉSACTIVÉ";
            #region Headers
            ModuleLogging.Headers.Current = "Les dernières données sauvegardé par ce module: ";
            ModuleLogging.Headers.Received = "Toutes les données de ce module depuis le dernier affichage ";
            #endregion Headers
            #region Types
            ModuleLogging.Types.Mode = "[MODE]:\t";
            ModuleLogging.Types.State = "[ÉTAT]:\t";
            ModuleLogging.Types.Value = "[VALEUR]:\t";
            ModuleLogging.Types.Weight = "[POID]:\t";
            ModuleLogging.Types.Command = "[COMMANDE]:\t";
            #endregion Types
            #region Separator
            ModuleLogging.Separators.Mode = "///////////////////////////////// - [MODES]";
            ModuleLogging.Separators.States = "///////////////////////////////// - [ÉTATS]";
            ModuleLogging.Separators.Values = "///////////////////////////////// - [VALEURS]";
            ModuleLogging.Separators.Weight = "///////////////////////////////// - [POIDS]";
            ModuleLogging.Separators.Commands = "///////////////////////////////// - [COMMANDES]";
            #endregion Separator

            #endregion ModuleLogging
            #region Tab_Names
            Tab_Names.Operation = "Opération";
            Tab_Names.Technician = "Technicien";
            Tab_Names.Calibration = "Calibration";
            Tab_Names.Maintenance = "Maintenance";
            Tab_Names.Terminal = "Console";
            Tab_Names.Settings = "Paramètre";
            #endregion Tab_Names
            #region Text_Labels
            Label_Names.Label_User = "Utilisateur:";
            Label_Names.Label_Password = "mdp:";
            Label_Names.Label_FileName = "Nom du fichier:";
            Label_Names.Label_FilePath = "Path du fichier:";
            Label_Names.Label_AutoConnect = "Con. Auto";
            Label_Names.Label_Language = "Langue:";
            Label_Names.Label_ScaleUnit = "Unité:";
            Label_Names.Technician_Label_Mode = "Mode";
            Label_Names.Technician_Label_Status = "État";
            Label_Names.Technician_Label_DataTypeA = "Type de A";
            Label_Names.Technician_Label_DataTypeB = "Type de B";
            Label_Names.Technician_Label_DataA = "Donnée A";
            Label_Names.Technician_Label_DataB = "Donnée B";
            Label_Names.Technician_Label_CanOutput = "Sortie CAN:";
            Label_Names.Technician_Label_SimulateModes = "Simul. de mode";
            Label_Names.Technician_Label_KeepCanOn = "Garde CAN Actif";
            Label_Names.Technician_Label_ClearAfterSend = "Init après";
            Label_Names.Technician_Label_SendOnce = "Envoie unique";
            #endregion Text_Labels
            #region ToolTips
            #endregion ToolTips
            #region ModuleNames
            Module_Names.SortingStation = "Centre de tri";
            Module_Names.Vehicle = "Camion";
            Module_Names.WeightStation = "Station de pesé";
            Module_Names.OfflineModules = "Module hors ligne: ";
            #endregion ModuleNames
        }
    }
}


