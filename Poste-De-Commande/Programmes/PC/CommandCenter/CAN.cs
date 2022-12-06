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
        #region Variables
        /// <summary>
        /// Set the state of a virtual module to this to
        /// tell the command center that no state were
        /// received from this module during MasterProtocol communications.
        /// </summary>
        public static byte State_Offline = 0xFF;
        /// <summary>
        /// State of a virtual module which means it's object has
        /// been reset. This is usually the case when the current mode
        /// of itself changes for an other.
        /// </summary>
        //public static byte State_ClassReset = 0xFE;
        /// <summary>
        /// State of a virtual module which means it has just been initialised.
        /// it is set to that at the application's launch, and when the
        /// MasterProtocol begins.
        /// </summary>
        public static byte State_ClassInitialised = 0xFD;
        #endregion Variables
        #region TIMER
        //#############################################################//
        /// <summary>
        /// This function handles the slot allocation aswell as what
        /// needs to be sent each time the master is allowed to talk.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        public void CAN_TIMER_Tick(object sender, EventArgs e)
        {
            if(BRS.ComPort.Port.IsOpen)
            {
                //----------------------------------------------------//
                if (Old.CanTimer.MasterProtocol.Mode != MasterProtocol.mode)
                {
                    Old.CanTimer.MasterProtocol.Mode = MasterProtocol.mode;
                    ModuleData_SortingStation.SetNewMode(MasterProtocol.mode);
                    ModuleData_Vehicle.SetNewMode(MasterProtocol.mode);
                    ModuleData_WeightStation.SetNewMode(MasterProtocol.mode);
                }
                switch (MasterProtocol.slot)
                {
                    ////////////////////////////////////////// - RESERVED B - //
                    case (CAN_Slot.ReservedB):
                        //BRS.Debug.Comment("[RESERVED B]", true);
                        MasterProtocol.slot = CAN_Slot.Master;

                        //----------------------------------// Get last lines until SYNC is seen
                        string[] lines = { "[RX]", "", "", "", "", "", "", "" };

                        BRS.Debug.Comment("\n");
                        for (int i=0; i<8; ++i)
                        {
                            int lineCount = CommandCenter.terminal.Window.Lines.Length;
                            string lastLine = "";
                            try
                            {
                                lastLine = CommandCenter.terminal.Window.Lines[lineCount - (1 + i)];
                            }
                            catch
                            {

                            }

                            if (lastLine.Contains("SYNC") && i <= 1)
                            {
                                //Increases their connection attempt by 1
                                ModuleData_SortingStation.ParseFromMasterProtocol("[RX],100");
                                ModuleData_Vehicle.ParseFromMasterProtocol("[RX],100");
                                ModuleData_WeightStation.ParseFromMasterProtocol("[RX],100");
                                i = 8;
                                break;
                            }
                            else
                            {
                                if (lastLine.Contains("SYNC") && i > 0)
                                {
                                    //Last line has been parsed
                                    break;
                                }
                                else
                                {
                                    lines[i] = lastLine;
                                }
                            }
                        }


                        for(int i=0; i < lines.Length; ++i)
                        {
                            ModuleData_SortingStation.ParseFromMasterProtocol(lines[i]);
                            ModuleData_Vehicle.ParseFromMasterProtocol(lines[i]);
                            ModuleData_WeightStation.ParseFromMasterProtocol(lines[i]);
                        }

                        break;
                    ////////////////////////////////////////// - RESERVED A - //
                    case (CAN_Slot.ReservedA):
                        //BRS.Debug.Comment("[RESERVED A]", true);
                        MasterProtocol.slot = CAN_Slot.ReservedB;
                        break;
                    ////////////////////////////////////////// - VEHICLE - //
                    case (CAN_Slot.Vehicle):
                        //BRS.Debug.Comment("[VEHICLE]", true);
                        MasterProtocol.slot = CAN_Slot.ReservedA;
                        break;
                    ////////////////////////////////////////// - WEIGHT - //
                    case (CAN_Slot.WeightStation):
                        //BRS.Debug.Comment("[WEIGHT]", true);
                        MasterProtocol.slot = CAN_Slot.Vehicle;
                        break;
                    ////////////////////////////////////////// - SORTING - //
                    case (CAN_Slot.SortingStation):
                        //BRS.Debug.Comment("[SORTING]",true);
                        CommandCenter.terminal.PauseDrawing = false;
                        MasterProtocol.slot = CAN_Slot.WeightStation;
                        break;
                    ////////////////////////////////////////// - MASTER - //
                    case (CAN_Slot.Master):
                        MasterProtocol.Send.CAN.Sync();
                        MasterProtocol.slot = CAN_Slot.SortingStation;
                        break;
                }
                Update_OperationTab();
            }
            else
            {
                BRS.Debug.Error("UNEXPECTED SHIT HAPENNED!");
                BRS.Debug.Comment("Stopping CAN TIMER!");
                NewUserTextInfo(UserInfos.ComPort.UnexpectedTermination,2);

                MasterProtocol.isActive = false;
                MasterProtocol.error = CAN_Errors.uart;
                MasterProtocol.slot = CAN_Slot.Master;
                MasterProtocol.mode = Modes_Ref.pause;
                MasterProtocol.state = States_Ref.error;
                Old.CanTimer.MasterProtocol.Mode = 0xFF;
                CAN_TIMER.Enabled = false;
            }
        }
        //#############################################################//
        /// <summary>
        /// This function is associated with the proceedure executed each
        /// time we need to start the CAN bus protocol for this project.\n
        ///
        /// It handles Class resets, timer starts, slots resets and so on.
        /// </summary>
        //#############################################################//
        public void MasterProtocol_Start()
        {
            BRS.Debug.Comment("Starting CAN communication protocol with BeagleBoneBlue...");
            CommandCenter.terminal.PauseDrawing = false;
            //Check if USB is opened
            if (BRS.ComPort.Port.IsOpen)
            {
                Debug.Success("USB is opened!");
                BRS.Debug.Comment("Starting timer and resetting stored data...");
                if (!MasterProtocol.isActive)
                {
                    CommandCenter.terminal.Log_header("Start of Master Protocol");
                    MasterProtocol.error = CAN_Errors.none;
                    MasterProtocol.slot = CAN_Slot.Master;
                    MasterProtocol.mode = Modes_Ref.pause;
                    MasterProtocol.state = States_Ref.paused;
                    CommandCenter.terminal.UseCANRX = true;
                    Old.CanTimer.MasterProtocol.Mode = 0xFF;

                    MasterProtocol.isActive = true;
                    CAN_TIMER.Enabled = true;
                    Debug.Success();
                }
                else
                {
                    CommandCenter.terminal.UseCANRX = true;
                }
            }
            else
            {
                CommandCenter.terminal.Log_header("Start of Master Protocol Error");
                CommandCenter.terminal.Log_Error("Serial port is not opened!");
                Debug.Error("NO UART PORT IS OPENED!");

                MasterProtocol.error = CAN_Errors.uart;
                MasterProtocol.slot = CAN_Slot.Master;
                MasterProtocol.mode = Modes_Ref.reinitialisation;
                MasterProtocol.state = States_Ref.error;
                Old.CanTimer.MasterProtocol.Mode = 0xFF;

                MasterProtocol.isActive = false;
                CommandCenter.terminal.UseCANRX = false;
                CAN_TIMER.Enabled = false;
                BRS.Debug.Comment("The CAN communication could not Start!");
            }
            Update_OperationTab();
        }
        //#############################################################//
        /// <summary>
        /// This function handles the necessary actions to execute when
        /// we want to properly stop the CAN MASTER from executing each
        /// allocated slots.
        /// </summary>
        //#############################################################//
        public void MasterProtocol_Stop()
        {
            BRS.Debug.Comment("Stopping CAN communication protocol...");
            CommandCenter.terminal.PauseDrawing = false;
            //Check if USB is opened
            if (BRS.ComPort.Port.IsOpen)
            {
                Debug.Success("USB is opened! Sending Quit condition to BeagleBone");
                BRS.Debug.Comment("Stopping timer and resetting stored data...");
                CommandCenter.terminal.Log_header("Closing Master Protocol");

                MasterProtocol.error = CAN_Errors.none;
                MasterProtocol.slot = CAN_Slot.Master;
                MasterProtocol.mode = Modes_Ref.pause;
                MasterProtocol.state = States_Ref.paused;

                MasterProtocol.isActive = false;
                CommandCenter.terminal.UseCANRX = false;
                CAN_TIMER.Enabled = false;
                Old.CanTimer.MasterProtocol.Mode = 0xFF;

                try
                {
                    //BRS.ComPort.Port.Close();
                    Debug.Success();
                }
                catch
                {
                    Debug.Error("- CRITICAL ERROR WHEN ATTEMPTING TO CLOSE SERIAL PORT -");
                    CommandCenter.terminal.Log_Error("Could not close UART");
                }
                Debug.Success();
            }
            else
            {
                Debug.Error("NO UART PORT IS OPENED!");
                MasterProtocol.error = CAN_Errors.uart;
                MasterProtocol.slot = CAN_Slot.Master;
                MasterProtocol.mode = Modes_Ref.reinitialisation;
                MasterProtocol.state = States_Ref.error;

                MasterProtocol.isActive = false;
                CommandCenter.terminal.UseCANRX = false;
                CAN_TIMER.Enabled = false;
                BRS.Debug.Comment("The CAN communication could not STOP!");
                CommandCenter.terminal.Log_Warning("Attempting to shutdown Master Protocol while SerialPort is closed!");
            }

            Update_OperationTab();
        }
        #endregion TIMER
        #region Reference_Classes
        /// <summary>
        /// Holds the referenced value for each modes as defined by
        /// the Google Sheet holding initial values and their in
        /// depth descriptions and applications
        /// </summary>
        static cModes Modes_Ref = new cModes();
        /// <summary>
        /// Holds the referenced value for each state that a module can have,
        /// as defined by the Google Sheet documentation, which holds the
        /// initial values and their indepth descriptions and applications.
        /// </summary>
        static cStates States_Ref = new cStates();
        /// <summary>
        /// Holds the referenced value for each Value that a module can send,
        /// as defined by the Google Sheet documentation, which holds the
        /// initial values and their indepth descriptions and applications.
        /// </summary>
        static cValues Values_Ref = new cValues();
        /// <summary>
        /// Holds the referenced value for each Commands that a module can send,
        /// as defined by the Google Sheet documentation, which holds the
        /// initial values and their indepth descriptions and applications.
        /// </summary>
        static cCommands Commands_Ref = new cCommands();

        //#############################################################//
        /// <summary>
        /// Corresponding CAN slot for each module.
        /// </summary>
        //#############################################################//
        public enum CAN_Slot
        {
            /// <summary>
            /// Command center CAN slot
            /// </summary>
            Master,
            /// <summary>
            /// Allocated CAN time frame used by the Sorting station to transmit their data.
            /// </summary>
            SortingStation,
            /// <summary>
            /// Allocated CAN time frame used by the Weight station to transmit their data.
            /// </summary>
            WeightStation,
            /// <summary>
            /// Allocated CAN time frame used by the Vehicle station to transmit their data.
            /// </summary>
            Vehicle,
            /// <summary>
            /// Spare CAN time frame which can be used by the Master to send excess data
            /// </summary>
            ReservedA,
            /// <summary>
            /// Spare CAN time frame which can be used by the Master to send excess data
            /// </summary>
            ReservedB
        }
        //#############################################################//
        /// <summary>
        /// Reference class used to easily identify and use CAN addresses
        /// for transmissions or to catch receptions.
        /// </summary>
        //#############################################################//
        public static class CAN_Addresses
        {
            /// <summary>
            /// Structure containing the CAN bus address used by modules
            /// to receive incomming data.
            /// </summary>
            public static class RX
            {
                /// <summary>
                /// Specific address used by the command center to receive data.
                /// This address is corresponding to the BeagleBoneBlue's terminal output.
                /// Not the real address.
                /// The real address is 0x100;
                /// </summary>
                public static int CommandCenter = 0x100;
                /// <summary>
                /// Specific address used by the vehicule to receive data.
                /// This address is corresponding to the BeagleBoneBlue's terminal output.
                /// Not the real address.
                /// The real address is 0x200;
                /// </summary>
                public static int Vehicule = 513;
                /// <summary>
                /// Specific address used by the sorting station to receive data.
                /// This address is corresponding to the BeagleBoneBlue's terminal output.
                /// Not the real address.
                /// The real address is 0x300;
                /// </summary>
                public static int SortingStation = 512;
                /// <summary>
                /// Specific address used by the weight station to receive data.
                /// This address is corresponding to the BeagleBoneBlue's terminal output.
                /// Not the real address.
                /// The real address is 0x400;
                /// </summary>
                public static int WeightStation = 1025;
            }
            /// <summary>
            /// Structure containing the CAN bus address used by modules
            /// to transmit their data.
            /// </summary>
            public static class TX
            {
                /// <summary>
                /// Address used as the synchronisation tram for modules.
                /// </summary>
                public static int CommandCenter = 0xFFB;
                /// <summary>
                /// Specific address used by the vehicule to receive data.
                /// This address is corresponding to the BeagleBoneBlue's terminal output.
                /// Not the real address.
                /// The real address is 0x200;
                /// </summary>
                public static int Vehicule = 513;
                /// <summary>
                /// Specific address used by the sorting station to receive data.
                /// This address is corresponding to the BeagleBoneBlue's terminal output.
                /// Not the real address.
                /// The real address is 0x300;
                /// </summary>
                public static int SortingStation = 512;
                /// <summary>
                /// Specific address used by the weight station to receive data.
                /// This address is corresponding to the BeagleBoneBlue's terminal output.
                /// Not the real address.
                /// The real address is 0x400;
                /// </summary>
                public static int WeightStation = 1025;
            }
        }
        //#############################################################//
        /// <summary>
        /// Values used to set CAN classes to the needed state in order
        /// to send or check for received data.
        /// </summary>
        //#############################################################//
        public static class DataState
        {
            /// <summary>
            /// tells you that this Commands is AVAILABLE for a QUEUE request.
            /// </summary>
            public static byte Available = 0xAA;
            /// <summary>
            /// Tells you that you received a request to execute this
            /// specific Commands.
            /// </summary>
            public static byte Received = 0xBB;
            /// <summary>
            /// Tells you that no requests have been received for this specific
            /// command. If there was a request, the command would be equal to RECEIVED.
            /// </summary>
            public static byte NoData = 0x00;
            /// <summary>
            /// Specifies that you want a specific command inside Commands 
            /// queued for the next CAN transmission
            /// </summary>
            public static byte Queue = 0xFE;
            /// <summary>
            /// Indicates that the Commands is already in queue for a transmission.
            /// Do not put your Commands back to QUEUE while it is equal to
            /// this.
            /// </summary>
            public static byte InQueue = 0xFD;
            /// <summary>
            /// Means that the value or commands is not used by this specific module.
            /// This is important as the functions use this to figure out which data needs
            /// to be send when a CAN slot is AVAILABLE for the module
            /// </summary>
            public static byte Unused = 0xFF;
        }
        //#############################################################//
        /// <summary>
        /// Contains values associated to each modes.
        /// </summary>
        //#############################################################//
        public class cModes
        {
            /**
             * @brief Mode sent by the master when in need of an emergency stop proceedure. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D6 @endlink
             */
            public byte emergencyStop = 0x00;
            /**
             * @brief Mode sent by the master to initiate a pause during operations. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D7 @endlink
             */
            public byte pause = 0x01;
            /**
             * @brief Mode sent by the master to initiate the testing mode of modules. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D8 @endlink
             */
            public byte testing = 0x02;
            /**
             * @brief Mode sent by the master to initiate the maintance proceedure. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D9 @endlink
             */
            public byte maintenance = 0x03;
            /**
             * @brief Mode sent by the master to initiate the autonomous operation mode. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D10 @endlink
             */
            public byte operation = 0x04;
            /**
             * @brief Mode sent by the master to initiate a calibration processus. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D11 @endlink
             */
            public byte calibration = 0x05;
            /**
             * @brief Mode sent by the master to reinitialise modules. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D12 @endlink
             */
            public byte reinitialisation = 0x06;
            //#############################################################//
            /// <summary>
            /// Sets all the public byte values of this class to
            /// globalValue
            /// </summary>
            /// <param name="globalValue">Values which all public member needs to be set to.</param>
            //#############################################################//
            public void SetAllTo(byte globalValue)
            {
                BRS.Debug.Comment("Setting all values of this class to: " + globalValue.ToString());
                emergencyStop = globalValue;
                pause = globalValue;
                testing = globalValue;
                maintenance = globalValue;
                operation = globalValue;
                calibration = globalValue;
                reinitialisation = globalValue;
                Debug.Success();
            }
        }
        //#############################################################//
        /// <summary>
        /// Class representing the values associated with states.
        /// </summary>
        //#############################################################//
        public class cStates
        {
            /**
             * @brief Indicates that the module is in an emergency stop proceedure. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D18 @endlink
             */
            public byte emergencyStop = 0x00;
            /**
             * @brief Indicates that the module is paused during autonomous operations. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D19 @endlink
             */
            public byte paused = 0x01;
            /**
             * @brief Indicates that the module is in a testing proceedure. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D20 @endlink
             */
            public byte testing = 0x02;
            /**
             * @brief Indicates that the module is processing an action. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D21 @endlink
             */
            public byte processing = 0x03;
            /**
             * @brief Indicates that the command center is executing the operation mode: 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D21 @endlink
             */
            public byte operating = 0x04;
            /**
             * @brief Indicates that the module is currently calibating itself. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D22 @endlink
             */
            public byte calibrating = 0x05;
            /**
             * @brief Indicates that the module has finished the calibrating proceedure. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D23 @endlink
             */
            public byte calibrated = 0x06;
            /**
             * @brief Indicates that the module is waiting for a command, without being in a peculiar state. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D24 @endlink
             */
            public byte waiting = 0x07;
            /**
             * @brief Indicates that the module is safe to handle (maintenancemode). Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D25 @endlink
             */
            public byte safe = 0x08;
            /**
             * @brief Indicates that the module is in an error state. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D26 @endlink
             */
            public byte error = 0x09;
            /**
             * @brief Indicates that the module has arrived at the sorting factory. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D27 @endlink
             */
            public byte atSortingFactory = 0x0A;
            /**
             * @brief Indicates that the module has arrived at the weight station. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D28 @endlink
             */
            public byte atWeightStation = 0x0B;
            /**
             * @brief Indicates that the module has finished sorting and loaded the moving module with the disc it sorted. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D29 @endlink
             */
            public byte finishedSortingAndHasLoaded = 0x0C;
            /**
             * @brief Indicates that the module is waiting to begin the sorting proceeduer. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D30 @endlink
             */
            public byte waitingToSort = 0x0D;
            /**
             * @brief Indicates that the module is waiting to start the weighting process. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D31 @endlink
             */
            public byte waitingToWeight = 0x0E;
            /**
             * @brief Indicates that the module finished it's weighing process. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D32 @endlink
             */
            public byte finishedWeighting = 0x0F;
            /**
             * @brief Indicates that the module is empty. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D33 @endlink
             */
            public byte empty = 0x10;
            //#############################################################//
            /// <summary>
            /// Sets all the public byte values of this class to
            /// globalValue
            /// </summary>
            /// <param name="globalValue">Values which all public member needs to be set to.</param>
            //#############################################################//
            public void SetAllTo(byte globalValue)
            {
                BRS.Debug.Comment("Setting all values of this class to: " + globalValue.ToString());
                emergencyStop = globalValue;
                paused = globalValue;
                testing = globalValue;
                processing = globalValue;
                calibrating = globalValue;
                calibrated = globalValue;
                waiting = globalValue;
                safe = globalValue;
                error = globalValue;
                atSortingFactory = globalValue;
                atWeightStation = globalValue;
                finishedSortingAndHasLoaded = globalValue;
                waitingToSort = globalValue;
                waitingToWeight = globalValue;
                finishedWeighting = globalValue;
                empty = globalValue;
                Debug.Success();
            }
        }
        //#############################################################//
        /// <summary>
        /// Class representing the values associated with Values
        /// </summary>
        //#############################################################//
        public class cValues
        {
            /**
             * @brief Value outputed on the bus to indicate the detection of a red disc. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D63 @endlink
             */
            public byte disc_Red = 0x00;
            /**
             * @brief Value outputed on the bus to indicate the detection of a silver disc. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D64 @endlink
             */
            public byte disc_Silver = 0x01;
            /**
             * @brief Value outputed on the bus to indicate the detection of a black disc. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D65 @endlink
             */
            public byte disc_Black = 0x02;
            /**
             * @brief Value outputed on the bus to indicate that there is no colour data available. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D66 @endlink
             */
            public byte disc_NoColor = 0x03;
            /**
             * @brief Value outputed on the bus to indicate the detection of a disc by the module. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D67 @endlink
             */
            public byte disc_Detected = 0x04;
            /**
             * @brief Value outputed on the bus to indicate the loss of a previously detected disc. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D68 @endlink
             */
            public byte disc_Lost = 0x05;
            /**
             * @brief Value outputed on the bus to indicate the detection of a disc went wrong as no disc could be detected when needed. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D69 @endlink
             */
            public byte disc_CouldNotBeFound = 0x06;
            /**
             * @brief Value outputed on the bus to indicate that the module is currently using metric units for it's values. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D70 @endlink
             */
            public byte unit_Metric = 0x07;
            /**
             * @brief Value outputed on the bus to indicate that the module is currently using imperial units for it's values. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D71 @endlink
             */
            public byte unit_Imperial = 0x08;
            //#############################################################//
            /// <summary>
            /// Sets all the public byte values of this class to
            /// globalValue
            /// </summary>
            /// <param name="globalValue">Values which all public member needs to be set to.</param>
            //#############################################################//
            public void SetAllTo(byte globalValue)
            {
                BRS.Debug.Comment("Setting all values of this class to: " + globalValue.ToString());
                disc_Red = globalValue;
                disc_Black = globalValue;
                disc_Silver = globalValue;
                disc_Detected = globalValue;
                disc_Lost = globalValue;
                disc_NoColor = globalValue;
                disc_CouldNotBeFound = globalValue;
                unit_Imperial = globalValue;
                unit_Metric = globalValue;
                Debug.Success();
            }
        }
        //#############################################################//
        /// <summary>
        /// Class representing the values associated with commands.
        /// Used to check which commands has been received or 
        /// what value is needed to send it.
        /// </summary>
        //#############################################################//
        public class cCommands
        {
            /**
             * @brief Commands which makes a supportive module move supported hardware to the left. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D36 @endlink
             */
            public byte move_left = 0x00;
            /**
             * @brief Commands which makes a supportive module move supported hardware to the right. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D37 @endlink
             */
            public byte move_right = 0x01;
            /**
             * @brief Commands which makes a supportive module move supported hardware forwards. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D38 @endlink
             */
            public byte move_forward = 0x02;
            /**
             * @brief Commands which makes a supportive module move supported hardware backwards. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D39 @endlink
             */
            public byte move_backward = 0x03;
            /**
             * @brief Commands which makes a supportive module move supported hardware upwards. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D40 @endlink
             */
            public byte move_up = 0x04;
            /**
             * @brief Commands which makes a supportive module move supported hardware downwards. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D41 @endlink
             */
            public byte move_down = 0x05;
            /**
             * @brief Commands which makes a supportive module s u c c. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D42 @endlink
             */
            public byte suction_ON = 0x06;
            /**
             * @brief Commands which makes a supportive module stop sucking. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D43 @endlink
             */
            public byte suction_OFF = 0x07;
            /**
             * @brief Commands which makes a supportive module turn on it's light A. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D44 @endlink
             */
            public byte light_A_ON = 0x08;
            /**
             * @brief Commands which makes a supportive module turn off it's light A. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D45 @endlink
             */
            public byte light_A_OFF = 0x09;
            /**
             * @brief Commands which makes a supportive module turn on it's light B. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D46 @endlink
             */
            public byte light_B_ON = 0x0A;
            /**
             * @brief Commands which makes a supportive module turn off it's light B. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D47 @endlink
             */
            public byte light_B_OFF = 0x0B;
            /**
             * @brief Commands which makes a supportive module turn on it's light C. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D48 @endlink
             */
            public byte light_C_ON = 0x0C;
            /**
             * @brief Commands which makes a supportive module turn off it's light C. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D49 @endlink
             */
            public byte light_C_OFF = 0x0D;
            /**
             * @brief Commands which makes a supportive module turn on it's light D. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D50 @endlink
             */
            public byte light_D_ON = 0x0E;
            /**
             * @brief Commands which makes a supportive module turn off it's light D. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D51 @endlink
             */
            public byte light_D_OFF = 0x0F;
            /**
             * @brief Commands which makes a supportive module go to the sorting station. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D52 @endlink
             */
            public byte goto_SortingStation = 0x10;
            /**
             * @brief Commands which makes a supportive module go to the weight station. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D53 @endlink
             */
            public byte goto_WeightStation = 0x11;
            /**
             * @brief Commands which makes a supportive module force start it's sorting proceedure. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D54 @endlink
             */
            public byte start_Sorting = 0x12;
            /**
             * @brief Commands which makes a supportive module force start it's weighting proceedure. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D55 @endlink
             */
            public byte start_Weighting = 0x13;
            /**
             * @brief Commands which makes a supportive module force discharge it's containers. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D56 @endlink
             */
            public byte discharge = 0x14;
            /**
             * @brief Commands which makes a supportive module switch to outputting values in metric. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D57 @endlink
             */
            public byte units_Metric = 0x16;
            /**
             * @brief Commands which makes a supportive module switch to outputting values in imperial. Full detailed description available at : 
             * @link https://docs.google.com/spreadsheets/d/1BgSps-8e4IBZYXIF8JcprH0LhlybmtSgL7DJWUX4dDQ/edit#gid=977381857&range=D58 @endlink
             */
            public byte units_Imperial = 0x17;
            //#############################################################//
            /// <summary>
            /// Sets all the public byte values of this class to
            /// globalValue
            /// </summary>
            /// <param name="globalValue">Values which all public member needs to be set to.</param>
            //#############################################################//
            public void SetAllTo(byte globalValue)
            {
                BRS.Debug.Comment("Setting all values of this class to: " + globalValue.ToString());
                move_left = globalValue;
                move_right = globalValue;
                move_up = globalValue;
                move_down = globalValue;
                move_forward = globalValue;
                move_backward = globalValue;
                units_Imperial = globalValue;
                units_Metric = globalValue;
                start_Sorting = globalValue;
                start_Weighting = globalValue;
                suction_ON = globalValue;
                suction_OFF = globalValue;
                discharge = globalValue;
                goto_SortingStation = globalValue;
                goto_WeightStation = globalValue;
                light_A_ON = globalValue;
                light_B_ON = globalValue;
                light_C_ON = globalValue;
                light_D_ON = globalValue;
                light_A_OFF = globalValue;
                light_B_OFF = globalValue;
                light_C_OFF = globalValue;
                light_D_OFF = globalValue;
                Debug.Success();
            }
        }
        #endregion Reference_Classes
        #region Modules
        //-------------------------------------------------------------//
        public cModule ModuleData_Vehicle = new cModule("Vehicle",CAN_Addresses.TX.Vehicule, CAN_Addresses.RX.Vehicule);
        public cModule ModuleData_SortingStation = new cModule("Sorting Station", CAN_Addresses.TX.SortingStation, CAN_Addresses.RX.SortingStation);
        public cModule ModuleData_WeightStation = new cModule("Weight Station", CAN_Addresses.TX.WeightStation, CAN_Addresses.RX.WeightStation);
        //-------------------------------------------------------------//

        //#############################################################//
        /// <summary>
        /// List of all the possible errors a virtual module can have.
        /// </summary>
        //#############################################################//
        public enum Module_Errors
        {
            /// <summary>
            /// The virtual module has no errors, and is not sending his
            /// state as an error
            /// </summary>
            none,
            /// <summary>
            /// The module is not seen talking during his allocated CAN
            /// frame
            /// </summary>
            notTalking,
            /// <summary>
            /// The module is sending incoherent modes uncorresponding
            /// to the wanted one
            /// </summary>
            wrongMode,
            /// <summary>
            /// The module is sending a state which do not correspond
            /// to the current sent mode by the master
            /// </summary>
            unexpectedState,
            /// <summary>
            /// The module is sending incoherent data which doesn't
            /// correspond to standard data
            /// </summary>
            unexpectedData,
            /// <summary>
            /// The module is sending Error as it's current State.
            /// </summary>
            inError
        }
        //#############################################################//
        /// <summary>
        /// Class containing sub-classes and data that a module can SEND
        /// or RECEIVE. Each module has it's own classes.
        /// </summary>
        //#############################################################//
        public class cModule
        {
            #region Structures
            /////////////////////////////////////////////////////////////
            /// <summary>
            /// Structure holding the 2 addresses used by this module for
            /// CAN communications.
            /// </summary>
            /////////////////////////////////////////////////////////////
            public struct stAddresses
            {
                /// <summary>
                /// Address that this module uses when talking on the
                /// CAN BUS. This is used by the command center to
                /// identify who is currently talking on the bus, and to
                /// dertermine if a module is responsive or not.
                /// </summary>
                public int CAN_TX;
                /// <summary>
                /// Special, dedicated address that the command center
                /// can use to send data to that specific module
                /// </summary>
                public int CAN_RX;
            }
            /////////////////////////////////////////////////////////////
            /// <summary>
            /// Structure holding the 2 addresses used by this module for
            /// CAN communications.
            /// </summary>
            /////////////////////////////////////////////////////////////
            public stAddresses Addresses;
            /////////////////////////////////////////////////////////////
            /// <summary>
            /// Structure holding all the lastly received data from this
            /// specific module. To see all the data that was sent by this
            /// module during a specific mode, use the struct Seen.
            /// </summary>
            /////////////////////////////////////////////////////////////
            public struct stCurrent
            {
                /// <summary>
                /// Which mode has been sent to this module.
                /// Defaults to reinitialisation.
                /// </summary>
                public byte Mode;
                /// <summary>
                /// The current state of this module. Stores the
                /// last received state from this module during a
                /// MasterCommunication. Is set to waiting by
                /// default
                /// </summary>
                public byte State;
                /// <summary>
                /// Holds the current weight that the module has
                /// sent.
                /// </summary>
                public byte Weight;
                /// <summary>
                /// What state the module is allowed to have in
                /// the Current.Mode
                /// </summary>
                public cStates AllowedStates;
            }
            /////////////////////////////////////////////////////////////
            /// <summary>
            /// Structure holding all the lastly received data from this
            /// specific module. To see all the data that was sent by this
            /// module during a specific mode, use the struct Seen.
            /// </summary>
            /////////////////////////////////////////////////////////////
            public stCurrent Current;
            /////////////////////////////////////////////////////////////
            /// <summary>
            /// Structure grouping and storing all the data intercepted
            /// by the command center that came from this specific module.
            /// </summary>
            /////////////////////////////////////////////////////////////
            public struct stReceived
            {
                /// <summary>
                /// States that the module sent
                /// </summary>
                public cStates States;
                /// <summary>
                /// Commands that the module sent
                /// </summary>
                public cCommands Commands;
                /// <summary>
                /// Values that the module sent
                /// </summary>
                public cValues Values;
            }
            /////////////////////////////////////////////////////////////
            /// <summary>
            /// Structure grouping and storing all the data intercepted
            /// by the command center that came from this specific module.
            /// </summary>
            /////////////////////////////////////////////////////////////
            public stReceived Received;
            #endregion Structures
            #region Variables
            /// <summary>
            /// Holds the current error That the module is currently in.
            /// Use Module_Errors to set this to an oher value.
            /// </summary>
            public Module_Errors error = Module_Errors.none;
            /// <summary>
            /// The name given to your module. Name of which users will
            /// be able to see at run time.
            /// </summary>
            public string name = "NoName";
            /// <summary>
            /// The private variable is used to keep track of the amount
            /// of times you attempted to parse a received string through
            /// ParseFromMasterProtocol(). If the address of the string
            /// which you attempt to parse is corresponding to the ones
            /// stored inside of the address structure, it is reset to
            /// 0. Pass the amount defined by the user of this class,
            /// the module is considered Offline as no string is containing
            /// it's address.
            /// </summary>
            private byte currentAmountOfAttempts = 0;
            /// <summary>
            /// This public variable is used to define how many data parsing
            /// attempts are to be done for the module to be considered offline.
            /// A failed attempt means that the address specified in the parsed
            /// data does not match this module's address stored in it's structure.
            /// </summary>
            public byte AmountOfAttemptsToBeOffline = 20;
            /*
            /// <summary>
            /// Class containing each states that this module can have
            /// depending on it's state.
            /// Switching modes using the method provided will handle
            /// this by itself.
            /// </summary>
            public class cAllowedStates
            {
                /// <summary>
                /// List of all allowed states for this module during
                /// standard operation
                /// </summary>
                public cStates InOperation;
                /// <summary>
                /// List of all allowed states for this module during
                /// Technician debugging mode
                /// </summary>
                public cStates InTech;
                /// <summary>
                /// List of all allowed states for this module during
                /// Calibration
                /// </summary>
                public cStates InCalibration;
                /// <summary>
                /// List of all allowed states for this module during
                /// maintenance
                /// </summary>
                public cStates InMaintenance;
                /// <summary>
                /// List of all allowed states for this module when
                /// paused.
                /// </summary>
                public cStates InPause;

                /// <summary>
                /// Function allowing you to set all the classes in AllowedStates to these defined ones
                /// </summary>
                /// <param name="Operation">Allowed states when InOperation</param>
                /// <param name="Tech">Allowed states when InTech</param>
                /// <param name="Calibration">Allowed states when InCalibration</param>
                /// <param name="Maintenance">Allowed states when InMaintenance</param>
                /// <param name="Paused">Allowed states when InPause</param>
                public void SetAllTo(cStates Operation, cStates Tech, cStates Calibration, cStates Maintenance, cStates Paused)
                {
                    InOperation = Operation;
                    InTech = Tech;
                    InCalibration = Calibration;
                    InMaintenance = Maintenance;
                    InPause = Paused;
                }
                /// <summary>
                /// Sets all classes within cAllowedStates to this one unique value
                /// </summary>
                /// <param name="Global"></param>
                public void SetAllTo(byte Global)
                {
                    InOperation.SetAllTo(Global);
                    InTech.SetAllTo(Global);
                    InCalibration.SetAllTo(Global);
                    InMaintenance.SetAllTo(Global);
                    InPause.SetAllTo(Global);
                }
            }
            /// <summary>
            /// Class containing each states that this module can have
            /// depending on it's state.
            /// Switching modes using the method provided will handle
            /// this by itself.
            /// </summary>
            public cAllowedStates AllowedStates;
            */
            #endregion Variables
            #region Constructor
            /////////////////////////////////////////////////////////////
            /// <summary>
            /// Builds this module's class according to the inputed
            /// parameters
            /// </summary>
            /// <param name="nameOfModule">name that will be displayed to the end user</param>
            /// <param name="canAddressTX">The address used by the module when talking on the CAN bus</param>
            /// <param name="canAddressRX">The module's reception address</param>
            /////////////////////////////////////////////////////////////
            public cModule(string nameOfModule, int canAddressTX, int canAddressRX)
            {
                BRS.Debug.Header(true);
                BRS.Debug.Comment("Building cModule class...");
                Received.Commands = new cCommands();
                Received.States = new cStates();
                Received.Values = new cValues();
                Current.AllowedStates = new cStates();

                BRS.Debug.Comment("Setting Received classes to DataState NoData...");
                Received.Commands.SetAllTo(DataState.NoData);
                Received.Values.SetAllTo(DataState.NoData);
                Received.States.SetAllTo(DataState.NoData);

                BRS.Debug.Comment("Setting Current structure's values to initial parameters");
                Current.Mode = Modes_Ref.reinitialisation;
                Current.State = State_ClassInitialised;
                Current.Weight = 0;
                Current.AllowedStates.SetAllTo(DataState.Unused);

                /*
                BRS.Debug.Comment("Setting AllowedStates to UNUSED");
                AllowedStates.SetAllTo(DataState.Unused);
                */
                BRS.Debug.Comment("Setting up the modules specific data...");
                Addresses.CAN_RX = canAddressRX;
                Addresses.CAN_TX = canAddressTX;
                name = nameOfModule;
                Debug.Success("Initialised " + name + "'s class and CAN addresses correctly!");

                BRS.Debug.Header(false);
            }
            #endregion Constructor
            #region Methods
            //#############################################################//
            /// <summary>
            /// Reset this module's data structures back to initial state.
            /// This does not reset addresses or name of the module.
            /// </summary>
            //#############################################################//
            public void Reset()
            {
                Debug.LocalStart(true);
                BRS.Debug.Comment("Resetting " + name + "'s class");

                BRS.Debug.Comment("Resetting Current structure...");
                Current.Mode = Modes_Ref.reinitialisation;
                Current.Weight = 0;

                BRS.Debug.Comment("Resetting Received structure to DataState.NoData...");
                Received.Commands.SetAllTo(DataState.NoData);
                Received.States.SetAllTo(DataState.NoData);
                Received.Values.SetAllTo(DataState.NoData);

                BRS.Debug.Comment("Resetting variables...");
                error = Module_Errors.none;

                Debug.Success("Command center's " + name + " class has been successfully reset to initial values");
                Debug.LocalEnd();
            }
            //#############################################################//
            /// <summary>
            /// This function allows you to tell this class that a new mode
            /// has been sent to it. This handles resets and expected states
            /// by itself.
            /// </summary>
            /// <param name="newMode"></param>
            //#############################################################//
            public void SetNewMode(byte newMode)
            {
                Debug.LocalStart(true);
                BRS.Debug.Comment("Setting new mode for " + name);

                if (newMode == Current.Mode)
                {
                    Debug.Error("Attempted to set the mode of " + name + " to what it was already!");
                }
                else
                {
                    if (Current.State == State_ClassInitialised)
                    {

                    }
                    else
                    {
                        Reset();
                    }
                    Current.Mode = newMode;

                    if (newMode == Modes_Ref.operation)
                    {
                        Current.AllowedStates.SetAllTo(DataState.Unused);
                        Current.AllowedStates.processing                    = DataState.Available;
                        Current.AllowedStates.waiting                       = DataState.Available;
                        Current.AllowedStates.atSortingFactory              = DataState.Available;
                        Current.AllowedStates.atWeightStation               = DataState.Available;
                        Current.AllowedStates.finishedSortingAndHasLoaded   = DataState.Available;
                        Current.AllowedStates.waitingToSort                 = DataState.Available;
                        Current.AllowedStates.waitingToWeight               = DataState.Available;
                        Current.AllowedStates.finishedWeighting             = DataState.Available;
                        Current.AllowedStates.empty                         = DataState.Available;
                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.VirtualModes.IsNow.Operating);
                    }
                    if (newMode == Modes_Ref.maintenance)
                    {
                        Current.AllowedStates.SetAllTo(DataState.Unused);
                        Current.AllowedStates.processing = DataState.Available;
                        Current.AllowedStates.safe       = DataState.Available;
                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.VirtualModes.IsNow.Maintenance);
                    }
                    if (newMode == Modes_Ref.testing)
                    {
                        Current.AllowedStates.SetAllTo(DataState.Unused);
                        //Current.AllowedStates.testing    = DataState.Available;
                        Current.AllowedStates.processing = DataState.Available;
                        Current.AllowedStates.waiting    = DataState.Available;
                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.VirtualModes.IsNow.Testing);
                    }
                    if (newMode == Modes_Ref.pause)
                    {
                        Current.AllowedStates.SetAllTo(DataState.Unused);
                        Current.AllowedStates.paused     = DataState.Available;
                        Current.AllowedStates.processing = DataState.Available;
                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.VirtualModes.IsNow.Paused);
                    }
                    if (newMode == Modes_Ref.reinitialisation)
                    {
                        Current.AllowedStates.SetAllTo(DataState.Unused);
                        Current.AllowedStates.processing = DataState.Available;
                        Current.AllowedStates.waiting    = DataState.Available;
                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.VirtualModes.IsNow.Initialising);
                    }
                    if (newMode == Modes_Ref.calibration)
                    {
                        Current.AllowedStates.SetAllTo(DataState.Unused);
                        Current.AllowedStates.calibrating = DataState.Available;
                        Current.AllowedStates.calibrated  = DataState.Available;
                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.VirtualModes.IsNow.Calibrating);
                    }
                    if (newMode == Modes_Ref.emergencyStop)
                    {
                        Current.AllowedStates.SetAllTo(DataState.Unused);
                        Current.AllowedStates.emergencyStop = DataState.Available;
                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.VirtualModes.IsNow.Emergency);
                    }
                }

                Debug.LocalEnd();
            }
            //#############################################################//
            /// <summary>
            /// This function takes the incoming data string that the
            /// Command Center received from the BeagleBone and attempts
            /// to parse it according to the data stored in the module's class
            /// </summary>
            /// <param name="receivedCommunication">must have [RX],</param>
            //#############################################################//
            public void ParseFromMasterProtocol(string receivedCommunication)
            {
                int address = 0;
                string[] datas;
                byte[] receivedCanData = {0,0,0,0,0,0,0,0};
                //----------------------------------------------------------//
                //-- First verifications of the string received ------------//
                //----------------------------------------------------------//
                if (receivedCommunication.StartsWith("[RX]"))
                {
                    //----------------------------------------------------------//
                    //-- String decomposing and parsing each commas ------------//
                    //----------------------------------------------------------//
                    try
                    {
                        datas = receivedCommunication.Split(',');
                        //----------------------------------------------------------//
                        //-- Attempting to read the address received ---------------//
                        //----------------------------------------------------------//
                        try
                        {
                            address = Convert.ToInt32(datas[1]);
                        }
                        catch
                        {
                            Debug.Error("RECEIVED COMMUNICATIONS ADDRESS COULD NOT BE CONVERTED TO INT32");
                            return;
                        }

                        if (address == Addresses.CAN_TX)
                        {
                            //BRS.Debug.Comment("IT WAS: " + name, true);
                            //----------------------------------------------------------//
                            //-- Offline detection reset -------------------------------//
                            //----------------------------------------------------------//
                            HandleSuccessfulAttempt();
                            //----------------------------------------------------------//
                            //-- Parsing the table into a byte array -------------------//
                            //----------------------------------------------------------//
                            for (int i=0; i<8; ++i)
                            {
                                receivedCanData[i] = Convert.ToByte(datas[i+2]);
                            }

                            CheckNStoreData(receivedCanData[0], receivedCanData[1]);
                            CheckNStoreData(receivedCanData[2], receivedCanData[3]);
                            CheckNStoreData(receivedCanData[4], receivedCanData[5]);
                            CheckNStoreData(receivedCanData[6], receivedCanData[7]);
                        }
                        else
                        {
                            // IS NOT THE CORRECT ADDRESS FOR THIS MODULE
                            //BRS.Debug.Comment("IT WASN'T: " + name, true);
                            HandleAttemptIncrements();
                            return;
                        }
                    }
                    catch
                    {
                        Debug.Error("RECEIVED COMMUNICATIONS COULD NOT BE SPLITTED");
                        return;
                    }
                }
                else
                {
                    //BRS.Debug.Error("String isn't starting with [RX]; " + receivedCommunication);
                }

            }
            //#############################################################//
            /// <summary>
            /// When called, handles the increments of parsing attempts,
            /// and if applicable, sets the state of this module class
            /// as Offline with a log message.
            /// </summary>
            //#############################################################//
            private void HandleAttemptIncrements()
            {
                //---------------------------------------------------------//
                // Handling increments
                //---------------------------------------------------------//
                currentAmountOfAttempts++;
                BRS.Debug.Comment(name + " Attempts: " + currentAmountOfAttempts.ToString());
                //---------------------------------------------------------//
                // Handling reaching the maximum allowed
                //---------------------------------------------------------//
                if(currentAmountOfAttempts >= AmountOfAttemptsToBeOffline)
                {
                    // Preventing overflowing
                    currentAmountOfAttempts = AmountOfAttemptsToBeOffline;

                    // if there is no stored errors, then set it as not talking.
                    //if(error == Module_Errors.none)
                    //{
                    //    error = Module_Errors.notTalking;
                    //}

                    // Setup new state and log it.
                    if (Current.State != State_ClassInitialised && Current.State != State_Offline)
                    {
                        BRS.Debug.Comment(name + " has been detected as Offline.",true);
                        Current.State = State_Offline;
                        OperationLogs.Window.Log_Warning(name + LogsInfos.Operations.Modules.NoLongerOnline);
                    }
                }
            }
            //#############################################################//
            /// <summary>
            /// When called, attempts reset increments and the module is
            /// now detected as online and operating "correctly", or at the
            /// very least, it's now talking on the CAN bus
            /// </summary>
            //#############################################################//
            private void HandleSuccessfulAttempt()
            {
                // Reset count
                currentAmountOfAttempts = 0;
                HandleAttemptIncrements();

                // Remove unresponsive error
                if (Current.State == State_Offline)
                {
                    OperationLogs.Window.Log_Warning(name + LogsInfos.Operations.Modules.NoLongerOffline);
                    error = Module_Errors.none;
                }
                else
                {
                    // First time being online
                    if(Current.State == State_ClassInitialised)
                    {
                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.FirstTimeOnline, Color.Lime);
                    }
                }

            }
            //#############################################################//
            /// <summary>
            /// Stores data inside of this class (Received structure)
            /// depending on the commandLetter which can be (M,S,V,C,W) in
            /// byte form, and stores the commandNumber at the appropriated
            /// value and location inside of this structure.
            /// </summary>
            /// <param name="commandLetter">(M,S,V,C,W) refer to Google Sheet</param>
            /// <param name="commandNumber">Refer to Google Sheets</param>
            //#############################################################//
            public void CheckNStoreData(byte commandLetter, byte commandNumber)
            {
                switch (commandLetter)
                {
                    case (77): //M
                        BRS.PopUp.Error("A slave module tried to send a Mode! Only the Command Center is allowed to send modes to modules! This is not supposed to happen.","CRITICAL CAN PROBLEMS");
                        break;

                    case (67): // C
                        switch (commandNumber)
                        {
                            // Parsing of received commands in a CAN tram
                            case (0x00): Received.Commands.move_left        = DataState.Received; OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.MoveLeft); break;
                            case (0x01): Received.Commands.move_right       = DataState.Received; OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.MoveRight); break;
                            case (0x02): Received.Commands.move_forward     = DataState.Received; OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.MoveForwards); break;
                            case (0x03): Received.Commands.move_backward    = DataState.Received; OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.MoveBackwards); break;
                            case (0x04): Received.Commands.move_up          = DataState.Received; OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.MoveUp); break;
                            case (0x05): Received.Commands.move_down        = DataState.Received; OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.MoveDown); break;

                            case (0x06):
                                    if (Received.Commands.suction_ON != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.SuctionOn,Color.Lime);
                                    }
                                    Received.Commands.suction_ON  = DataState.Received;
                                    Received.Commands.suction_OFF = DataState.NoData;
                                    break;
                            case (0x07):
                                    if (Received.Commands.suction_OFF != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.SuctionOff, Color.Lime);
                                    }
                                    Received.Commands.suction_OFF = DataState.Received;
                                    Received.Commands.suction_ON  = DataState.NoData;
                                    break;

                            case (0x08):
                                    if (Received.Commands.light_A_ON != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.LightAOn, Color.Lime);
                                    }
                                    Received.Commands.light_A_ON  = DataState.Received;
                                    Received.Commands.light_A_OFF = DataState.NoData;
                                    break;
                            case (0x09):
                                    if (Received.Commands.light_A_OFF != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.LightAOff, Color.Lime);
                                    }
                                    Received.Commands.light_A_OFF = DataState.Received;
                                    Received.Commands.light_A_ON  = DataState.NoData;
                                    break;

                            case (0x0A):
                                    if (Received.Commands.light_B_ON != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.LightBOn, Color.Lime);
                                    }
                                    Received.Commands.light_B_ON  = DataState.Received;
                                    Received.Commands.light_B_OFF = DataState.NoData;
                                    break;
                            case (0x0B):
                                    if (Received.Commands.light_B_OFF != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.LightBOff, Color.Lime);
                                    }
                                    Received.Commands.light_B_OFF = DataState.Received;
                                    Received.Commands.light_B_ON  = DataState.NoData;
                                    break;

                            case (0x0C):
                                    if (Received.Commands.light_C_ON != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.LightCOn, Color.Lime);
                                    }
                                    Received.Commands.light_C_ON  = DataState.Received;
                                    Received.Commands.light_C_OFF = DataState.NoData;
                                    break;
                            case (0x0D):
                                    if (Received.Commands.light_C_ON != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.LightCOff, Color.Lime);
                                    }
                                    Received.Commands.light_C_OFF = DataState.Received;
                                    Received.Commands.light_C_ON  = DataState.NoData;
                                    break;

                            case (0x0E):
                                    if (Received.Commands.light_D_ON != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.LightDOn, Color.Lime);
                                    }
                                    Received.Commands.light_D_ON  = DataState.Received;
                                    Received.Commands.light_D_OFF = DataState.NoData;
                                    break;
                            case (0x0F):
                                    if (Received.Commands.light_D_OFF != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.LightDOff, Color.Lime);
                                    }
                                    Received.Commands.light_D_OFF = DataState.Received;
                                    Received.Commands.light_D_ON = DataState.NoData;
                                break;

                            case (0x10):
                                    if (Received.Commands.goto_SortingStation != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.GotoSortingStation, Color.Lime);
                                    }
                                    Received.Commands.goto_SortingStation = DataState.Received;
                                    Received.Commands.goto_WeightStation  = DataState.NoData;
                                    break;
                            case (0x11):
                                    if (Received.Commands.goto_WeightStation != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.GotoWeightStation, Color.Lime);
                                    }
                                    Received.Commands.goto_WeightStation  = DataState.Received;
                                    Received.Commands.goto_SortingStation = DataState.NoData;
                                break;

                            case (0x12): Received.Commands.start_Sorting   = DataState.Received; OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.StartSorting); break;
                            case (0x13): Received.Commands.start_Weighting = DataState.Received; OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.StartWeighting); break;

                            case (0x14): Received.Commands.discharge = DataState.Received; OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.Discharge); break;

                            case (0x16):
                                    if (Received.Commands.units_Metric != DataState.Received)
                                    {
                                        OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.UseMetric, Color.Lime);
                                    }
                                    Received.Commands.units_Metric   = DataState.Received;
                                    Received.Commands.units_Imperial = DataState.NoData;
                                    break;

                            case (0x17):
                                    if (Received.Commands.units_Imperial != DataState.Received)
                                    {
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Commands.UseImperial, Color.Lime);
                                }
                                    Received.Commands.units_Imperial = DataState.Received;
                                    Received.Commands.units_Metric   = DataState.NoData;
                                    break;
                            default:
                                //If received mode matched nothing, an error occured.
                                OperationLogs.Window.Log_Warning(name + LogsInfos.Operations.Modules.Commands.UnexpectedData);
                                error = Module_Errors.unexpectedData;
                                break;
                        }
                        break;
                    case (86): // V
                        switch (commandNumber)
                        {
                            // Parsing of received values in a CAN tram
                            case (0x00):
                                if (Received.Values.disc_Red != DataState.Received)
                                {
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Values.disc_Red, Color.Orange);
                                }
                                Received.Values.disc_Red        = DataState.Received;
                                Received.Values.disc_Black      = DataState.NoData;
                                Received.Values.disc_Silver     = DataState.NoData;
                                Received.Values.disc_NoColor    = DataState.NoData;
                                break;

                            case (0x01):
                                if (Received.Values.disc_Silver != DataState.Received)
                                {
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Values.disc_Silver, Color.White);
                                }
                                Received.Values.disc_Silver   = DataState.Received;
                                Received.Values.disc_Red      = DataState.NoData;
                                Received.Values.disc_Black    = DataState.NoData;
                                Received.Values.disc_NoColor  = DataState.NoData;
                                break;
                            case (0x02):
                                if (Received.Values.disc_Black != DataState.Received)
                                {
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Values.disc_Black, Color.Black);
                                }
                                Received.Values.disc_Black    = DataState.Received;
                                Received.Values.disc_Red      = DataState.NoData;
                                Received.Values.disc_Silver   = DataState.NoData;
                                Received.Values.disc_NoColor  = DataState.NoData;
                                break;
                            case (0x03):
                                if (Received.Values.disc_NoColor != DataState.Received)
                                {
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Values.disc_NoColor, Color.Yellow);
                                }
                                Received.Values.disc_NoColor  = DataState.Received;
                                Received.Values.disc_Red      = DataState.NoData;
                                Received.Values.disc_Silver   = DataState.NoData;
                                Received.Values.disc_Black    = DataState.NoData;
                                break;

                            case (0x04):
                                if (Received.Values.disc_Detected != DataState.Received)
                                {
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Values.disc_Detected, Color.Lime);
                                }
                                Received.Values.disc_Detected         = DataState.Received;
                                Received.Values.disc_Lost             = DataState.NoData;
                                Received.Values.disc_CouldNotBeFound  = DataState.NoData;
                                break;

                            case (0x05):
                                if (Received.Values.disc_Lost != DataState.Received)
                                {
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Values.disc_Lost, Color.Red);
                                }
                                Received.Values.disc_Lost             = DataState.Received;
                                Received.Values.disc_Detected         = DataState.NoData;
                                Received.Values.disc_CouldNotBeFound  = DataState.NoData;
                                break;
                            case (0x06):
                                if (Received.Values.disc_CouldNotBeFound != DataState.Received)
                                {
                                    OperationLogs.Window.Log_Error(name + LogsInfos.Operations.Modules.Values.disc_CouldNotBeFound);
                                }
                                Received.Values.disc_CouldNotBeFound  = DataState.Received;
                                Received.Values.disc_Detected         = DataState.NoData;
                                Received.Values.disc_Lost             = DataState.NoData;
                                break;

                            case (0x07):
                                if (Received.Values.unit_Metric != DataState.Received)
                                {
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Values.NowInMetric, Color.Lime);
                                }
                                Received.Values.unit_Metric           = DataState.Received;
                                Received.Values.unit_Imperial         = DataState.NoData;
                                break;
                            case (0x08):
                                if (Received.Values.unit_Imperial != DataState.Received)
                                {
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.Values.NowInImperial, Color.Lime);
                                }
                                Received.Values.unit_Metric           = DataState.NoData;
                                Received.Values.unit_Imperial         = DataState.Received;
                                break;
                            default:
                                //If received mode matched nothing, an error occured.
                                OperationLogs.Window.Log_Warning(name + LogsInfos.Operations.Modules.Values.UnexpectedData);
                                error = Module_Errors.unexpectedData;
                                break;
                        }
                        break;
                    case (83): // S
                        switch (commandNumber)
                        {
                            // Parsing of received states from the communicating module
                            case (0x00):
                                // AUTOMATICALLY SWITCH TO EMERGENCY MODE WHEN A MODULE STATE SAYS IT'S IN THIS STATE
                                if (Received.States.emergencyStop != DataState.Received)
                                {
                                    OperationLogs.Window.Log_header(name + LogsInfos.Operations.Modules.States.IsNow.InEmergencyStop);
                                    Current.Mode = Modes_Ref.emergencyStop;
                                    Received.States.emergencyStop = DataState.Received;
                                }
                                break;
                            case (0x01):
                                #region Paused
                                if (Received.States.paused != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.Paused, Color.LightPink);
                                }
                                Received.States.paused = DataState.Received;
                                #endregion Paused
                                break;
                            case (0x02):
                                #region Testing
                                if (Received.States.testing != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.Testing, Color.LightPink);
                                }
                                Received.States.testing = DataState.Received;
                                #endregion Testing
                                break;
                            case (0x03):
                                #region Processing
                                if (Received.States.processing != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.Processing, Color.LightPink);
                                }
                                Received.States.processing = DataState.Received;
                                #endregion Processing
                                break;
                            case (0x04): break;
                            case (0x05):
                                #region Calibrating
                                if (Received.States.calibrating != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.Calibrating, Color.LightPink);
                                }
                                Received.States.calibrating = DataState.Received;
                                #endregion Calibrating 
                                break;
                            case (0x06):
                                #region Calibrated
                                if (Received.States.calibrated != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.Calibrated, Color.LightPink);
                                }
                                Received.States.calibrated = DataState.Received;
                                #endregion Calibrated 
                                break;
                            case (0x07):
                                #region Waiting
                                if (Received.States.waiting != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.Waiting, Color.LightPink);
                                }
                                Received.States.waiting = DataState.Received;
                                #endregion Waiting 
                                break;
                            case (0x08):
                                #region Safe
                                if (Received.States.safe != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.Safe, Color.LightPink);
                                }
                                Received.States.safe = DataState.Received;
                                #endregion Safe 
                                break;
                            case (0x09):
                                #region Error
                                if (Received.States.error != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Error(name + LogsInfos.Operations.Modules.States.IsNow.Error);
                                }
                                Received.States.error = DataState.Received;
                                #endregion Error  
                                break;

                            case (0x0A):
                                #region AtSortingFactory
                                if (Received.States.atSortingFactory != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.AtSortingfactory, Color.Pink);
                                }
                                Received.States.atSortingFactory = DataState.Received;
                                #endregion AtSortingFactory
                                break;
                            case (0x0B):
                                #region atWeightStation
                                if (Received.States.atWeightStation != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.AtWeightStation, Color.Pink);
                                }
                                Received.States.atWeightStation = DataState.Received;
                                #endregion atWeightStation
                                break;
                            case (0x0C):
                                #region finishedSortingAndHasLoaded
                                if (Received.States.finishedSortingAndHasLoaded != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.FinishedSortingAndLoaded, Color.Pink);
                                }
                                Received.States.finishedSortingAndHasLoaded = DataState.Received;
                                #endregion finishedSortingAndHasLoaded
                                break;
                            case (0x0D):
                                #region waitingToSort
                                if (Received.States.waitingToSort != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.WaitingToSort, Color.Pink);
                                }
                                Received.States.waitingToSort = DataState.Received;
                                #endregion waitingToSort
                                break;
                            case (0x0E):
                                #region waitingToWeight
                                if (Received.States.waitingToWeight != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.WaitingToWeight, Color.Pink);
                                }
                                Received.States.waitingToWeight = DataState.Received;
                                #endregion waitingToWeight 
                                break;
                            case (0x0F):
                                #region finishedWeighting
                                if (Received.States.finishedWeighting != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.FinishedWeighting, Color.Pink);
                                }
                                Received.States.finishedWeighting = DataState.Received;
                                #endregion finishedWeighting 
                                break;
                            case (0x10):
                                #region empty
                                if (Received.States.empty != DataState.Received)
                                {
                                    Received.States.SetAllTo(DataState.NoData);
                                    OperationLogs.Window.Log_Comment(name + LogsInfos.Operations.Modules.States.IsNow.Empty, Color.Pink);
                                }
                                Received.States.empty = DataState.Received;
                                #endregion empty 
                                break;
                            default:
                                //If received mode matched nothing, an error occured.
                                OperationLogs.Window.Log_Error(name + LogsInfos.Operations.Modules.States.IsIncoherent + commandNumber.ToString());
                                error = Module_Errors.unexpectedData;
                                break;
                        }
                        Current.State = commandNumber;
                        break;
                    case (87):  // A weight was received.
                        Current.Weight = commandNumber;
                        break;
                }
            }
            //#############################################################//
            /// <summary>
            /// Checks if the class's current state is within the
            /// AllowedStates of this class.
            /// </summary>
            /// <returns>True: is allowed / False: is not allowed</returns>
            //#############################################################//
            public bool IsStateAllowed()
            {
                switch (Current.State)
                {
                    // Parsing of received states from the communicating module
                    case (0x00): return (Current.AllowedStates.emergencyStop == DataState.Available); break;
                    case (0x01): return (Current.AllowedStates.paused == DataState.Available); break;
                    case (0x02): return (Current.AllowedStates.testing == DataState.Available); break;
                    case (0x03): return (Current.AllowedStates.processing == DataState.Available); break;
                    case (0x04): return false; break;
                    case (0x05): return (Current.AllowedStates.calibrating == DataState.Available); break;
                    case (0x06): return (Current.AllowedStates.calibrated == DataState.Available); break;
                    case (0x07): return (Current.AllowedStates.waiting == DataState.Available); break;
                    case (0x08): return (Current.AllowedStates.safe == DataState.Available); break;
                    case (0x09): return (Current.AllowedStates.error == DataState.Available); break;
                    case (0x0A): return (Current.AllowedStates.atSortingFactory == DataState.Available); break;
                    case (0x0B): return (Current.AllowedStates.atWeightStation == DataState.Available); break;
                    case (0x0C): return (Current.AllowedStates.finishedSortingAndHasLoaded == DataState.Available); break;
                    case (0x0D): return (Current.AllowedStates.waitingToSort == DataState.Available); break;
                    case (0x0E): return (Current.AllowedStates.waitingToWeight == DataState.Available); break;
                    case (0x0F): return (Current.AllowedStates.finishedWeighting == DataState.Available); break;
                    case (0x10): return (Current.AllowedStates.empty == DataState.Available); break;
                    //case (0xFF): return true; break; // State_Offline
                    //case (0xFE): return true; break; // State_ClassInitialised
                    //case (0xFD): return true; break; // State_ClassReset
                    default:
                        //If received mode matched nothing, an error occured.
                        return false;
                        break;
                }
            }
            #endregion Methods
            #region Disc_Color
            #region Enum
            /// <summary>
            /// All the possible values of colors that this module can
            /// detect are stored here.
            /// </summary>
            public enum DiscColor
            {
                /// <summary>
                /// Means that this module has received no disc color
                /// related Values since it's last reset
                /// </summary>
                NoData,
                /// <summary>
                /// Means that this module no longer detects a disc of
                /// color but previously was.
                /// </summary>
                NoDisc,
                /// <summary>
                /// Means that this module is detecting an orange/redish
                /// disc at the moment
                /// </summary>
                Red,
                /// <summary>
                /// Means that this module is detecting a black disc at
                /// the moment
                /// </summary>
                Black,
                /// <summary>
                /// Means that this module is detecting a metallic disc at
                /// the moment.
                /// </summary>
                Metallic
            }
            #endregion Enum
            //#############################################################//
            /// <summary>
            /// Function which returns this module's currently detected disc
            /// color.
            /// </summary>
            /// <returns>enum DiscColor</returns>
            //#############################################################//
            public DiscColor DetectedDiscColor()
            {
                if(Received.Values.disc_NoColor == DataState.Received)
                {
                    return DiscColor.NoDisc;
                }

                if (Received.Values.disc_Black == DataState.Received)
                {
                    return DiscColor.Black;
                }

                if (Received.Values.disc_Red == DataState.Received)
                {
                    return DiscColor.Red;
                }

                if (Received.Values.disc_Silver == DataState.Received)
                {
                    return DiscColor.Metallic;
                }

                return DiscColor.NoData;
            }
            //#############################################################//
            /// <summary>
            /// Function which resets detected disc colors
            /// </summary>
            /// <returns>enum DiscColor</returns>
            //#############################################################//
            public void DetectedDiscColor(DiscColor setAll)
            {
                switch(setAll)
                {
                    case (DiscColor.NoData):
                        Received.Values.disc_Black = DataState.NoData;
                        Received.Values.disc_Red = DataState.NoData;
                        Received.Values.disc_Silver = DataState.NoData;
                        Received.Values.disc_NoColor = DataState.NoData;
                        break;
                    default:
                        // Bruh 
                        break;
                }
            }
            #endregion Disc_Color
        }
        #endregion Modules

        #region CAN_Class
        //#############################################################//
        /// <summary>
        /// List of all the possible errors that the CAN protocol can
        /// run into during operation or setup
        /// </summary>
        //#############################################################//
        public enum CAN_Errors
        {
            /// <summary>
            /// No errors are detected in the CAN protocol
            /// </summary>
            none,
            /// <summary>
            /// One or more module is not talking during it's allocated
            /// CAN time frame.
            /// </summary>
            modulesUnresponsive,
            /// <summary>
            /// the CAN sent over USB is not giving any feedback at all
            /// </summary>
            noFeedBack,
            /// <summary>
            /// An error occured with the ComPort / Serial port
            /// </summary>
            uart,
            /// <summary>
            /// The beagleboneblue ran into one of the million errors
            /// and weird stuff that it can run into. It's a beaglebone
            /// after all
            /// </summary>
            beagleBone,
            /// <summary>
            /// This error significates that the emergency button was
            /// pressed.
            /// </summary>
            EmergencyStop

        }
        //#############################################################//
        /// <summary>
        /// The main CAN class associated with this program.
        /// This one is used to control or indicate what is hapenning
        /// on the CAN bus, and where the program currently is in it's
        /// execution CAN wise.
        /// </summary>
        //#############################################################//
        public static class MasterProtocol
        {
            #region Variables
            /// <summary>
            /// The mode which needs to be sent to modules
            /// Initial mode is pause.
            /// </summary>
            public static byte mode = Modes_Ref.pause;
            /// <summary>
            /// The Master's current state
            /// Initial state being processing.
            /// Simply because initially, the master is initialising.
            /// </summary>
            public static byte state = States_Ref.processing;
            /// <summary>
            /// The current CAN slot, or allocated time frame.
            /// </summary>
            public static CAN_Slot slot = CAN_Slot.Master;
            /// <summary>
            /// if true, the CAN protocol is active,
            /// and an active communication is executed between 
            /// the command center, and the beagleboneblue
            /// </summary>
            public static bool isActive = false;
            /// <summary>
            /// Contains the CAN current ERROR state.
            /// Note that this is not necessarely associated to
            /// a Module error.
            /// </summary>
            public static CAN_Errors error = CAN_Errors.none;
            #endregion Variables
            #region Methods
            //#############################################################//
            /// <summary>
            /// Groupe of functions used to send various CAN data
            /// </summary>
            //#############################################################//
            public struct Send
            {
                public struct ToBeagleBone
                {
                    //#############################################################//
                    /// <summary>
                    /// Sends a reset position to the BeagleBoneBlue allowing the
                    /// latter to reset how many bytes of data it has received
                    /// from this program.
                    /// </summary>
                    //#############################################################//
                    public static void Reset()
                    {
                        BRS.Debug.LocalStart(true);
                        BRS.Debug.Comment("Attempting to reset received data in the BeagleBone...");
                        CommandCenter.terminal.PauseDrawing = false;
                        if (BRS.ComPort.Port.IsOpen)
                        {
                            try
                            {
                                BRS.ComPort.Port.Write("\n");
                                BRS.ComPort.Port.Write("\n");
                                BRS.ComPort.Port.Write("\n");
                                BRS.ComPort.Port.Write("\n");
                                BRS.ComPort.Port.Write("\n");
                                BRS.ComPort.Port.Write("\n");
                                BRS.ComPort.Port.Write("\n");
                                BRS.ComPort.Port.Write("\n");
                                BRS.ComPort.Port.Write("\n");
                                BRS.ComPort.Port.Write("\n");
                                BRS.ComPort.Port.Write("\n");
                                BRS.ComPort.Port.Write("\n");
                                Debug.Success();
                            }
                            catch
                            {
                                Debug.Error("CRITICAL ERROR DURING RESET SENDING!!!!");
                            }
                        }
                        else
                        {
                            Debug.Error(" - CANT SEND RESET - (PORT CLOSED)");
                        }
                        BRS.Debug.LocalEnd();
                    }
                    //#############################################################//
                    /// <summary>
                    /// Used to ask the BeagleBone to quit it's currently running
                    /// program.
                    /// </summary>
                    //#############################################################//
                    public static void Quit()
                    {
                        CommandCenter.terminal.PauseDrawing = false;
                        if (BRS.ComPort.Port.IsOpen)
                        {
                            BRS.Debug.Comment("Sending QUIT condition to beagleBone...");
                            ToBeagleBone.StartOfPacket();
                            ToBeagleBone.Value(0xFF);
                            ToBeagleBone.Value(0xFF);
                            ToBeagleBone.EndOfPacket();
                        }
                        else
                        {
                            Debug.Error(" - CANNOT SEND QUIT CONDITION TO BEAGLE BONE BLUE - (Port Closed)");
                        }
                    }
                    //#############################################################//
                    /// <summary>
                    /// Sends to the beagleBone which CAN address to use for the
                    /// upcomming data transfer.
                    /// </summary>
                    /// <param name="address">11 bits CAN address</param>
                    //#############################################################//
                    public static void Address(int address)
                    {
                        string result = address.ToString("X3");

                        try
                        {
                            CommandCenter.terminal.justSentData = CommandCenter.terminal.justSentData + result;
                            BRS.ComPort.Port.Write(result);
                        }
                        catch
                        {
                            Debug.Error("CRITICAL ERROR DURING ADDRESS PARSING & SENDING (" + result + ")");
                        }
                    }
                    //#############################################################//
                    /// <summary>
                    /// tells the BeagleBone that we are about to tell it a CAN
                    /// tram to send.
                    /// </summary>
                    //#############################################################//
                    public static void StartOfPacket()
                    {
                        ToBeagleBone.Value(0xFE);
                    }
                    //#############################################################//
                    /// <summary>
                    /// Function used to send an individual unsigned char to the
                    /// beagleBone
                    /// </summary>
                    /// <param name="value">0 to 255</param>
                    //#############################################################//
                    public static void Value(byte value)
                    {
                        if (BRS.ComPort.Port.IsOpen)
                        {
                            byte[] b;
                            try
                            {
                                if(value == 0x04)
                                {
                                    value = 0xFD;
                                }

                                b = BitConverter.GetBytes(value);
                                CommandCenter.terminal.justSentData = CommandCenter.terminal.justSentData + BitConverter.ToString(b,0);
                                BRS.ComPort.Port.Write(b, 0, 1);
                            }
                            catch
                            {
                                Debug.Error("CRITICAL ERROR DURING VALUE PARSING & SENDING (" + value.ToString() + ")");
                            }
                        }
                        else
                        {
                            Debug.Error(" - CANT SEND " + value.ToString() + " - (PORT CLOSED)");
                        }
                    }
                    //#############################################################//
                    /// <summary>
                    /// Function used to send an individual unsigned char to the
                    /// beagleBone
                    /// </summary>
                    /// <param name="value">0 to 255</param>
                    //#############################################################//
                    public static void Value(char value)
                    {
                        if (BRS.ComPort.Port.IsOpen)
                        {
                            byte[] b;
                            try
                            {
                                b = BitConverter.GetBytes(value);
                                CommandCenter.terminal.justSentData = CommandCenter.terminal.justSentData + BitConverter.ToString(b, 0);
                                BRS.ComPort.Port.Write(b, 0, 1);
                            }
                            catch
                            {
                                Debug.Error("CRITICAL ERROR DURING VALUE PARSING & SENDING (" + value.ToString() + ")");
                            }
                        }
                        else
                        {
                            Debug.Error(" - CANT SEND " + value.ToString() + " - (PORT CLOSED)");
                        }
                    }
                    //#############################################################//
                    /// <summary>
                    /// Tells the beaglebone that it should parse the data previously
                    /// sent to him over UART.
                    /// </summary>
                    //#############################################################//
                    public static void EndOfPacket()
                    {
                        if(BRS.ComPort.Port.IsOpen)
                        {
                            try
                            {
                                CommandCenter.terminal.justSentData = CommandCenter.terminal.justSentData + "\n";
                                BRS.ComPort.Port.Write("\n");
                            }
                            catch
                            {
                                Debug.Error("CRITICAL ERROR DURING END OF PACKET SENDING!!!!");
                            }
                        }
                        else
                        {
                            Debug.Error(" - CANT SEND END OF PACKET - (PORT CLOSED)");
                        }
                    }
                }
                //#############################################################//
                /// <summary>
                /// Structure grouping the CAN functions used to send data
                /// using the beagleBoneBlue
                /// </summary>
                //#############################################################//
                public struct CAN
                {
                    //#############################################################//
                    /// <summary>
                    /// Function used to send the Master CAN tram.
                    /// </summary>
                    //#############################################################//
                    public static void Sync()
                    {
                        //BRS.Debug.Comment("[SYNC]",true);

                        CommandCenter.terminal.PauseDrawing = true;
                        Send.ToBeagleBone.StartOfPacket();
                        Send.ToBeagleBone.Address(CAN_Addresses.TX.CommandCenter);
                        Send.ToBeagleBone.Value('M');
                        Send.ToBeagleBone.Value(mode);
                        Send.ToBeagleBone.Value(0);
                        Send.ToBeagleBone.Value(0);
                        Send.ToBeagleBone.Value(0);
                        Send.ToBeagleBone.Value(0);
                        Send.ToBeagleBone.Value('S');
                        Send.ToBeagleBone.Value(state);
                        Send.ToBeagleBone.EndOfPacket();
                        CommandCenter.terminal.PauseDrawing = false;
                    }
                    //#############################################################//
                    /// <summary>
                    /// Used to send specific commands or values to a specific module
                    /// within the allocated RESERVED CAN time frames
                    /// </summary>
                    /// <param name="targettedAddress">11 bits address to send the address to</param>
                    //#############################################################//
                    public static void ToAddress(int targettedAddress)
                    {

                    }
                }
            }
            //#############################################################//
            /// <summary>
            /// Groups of functions used by this protocol to parse received
            /// data
            /// </summary>
            //#############################################################//
            public struct Received
            {
                //#############################################################//
                /// <summary>
                /// Used to parse a string and store the content in the associated
                /// virtual module.
                /// </summary>
                //#############################################################//
                public static void Parse_Terminal()
                {

                }
            }
            //#############################################################//
            /// <summary>
            /// Group of all small functions used within main functions in
            /// this class.
            /// </summary>
            //#############################################################//
            public struct Functions
            {
                #region Parsing
                #region value
                //#############################################################//
                /// <summary>
                /// Transforms a received string address, and sends the int
                /// value associated with the module which sent that address
                /// </summary>
                /// <param name="value">small string corresponding to who sent the CAN data</param>
                /// <returns>int value of that address</returns>
                //#############################################################//
                public static int ParseValue(string value)
                {
                    BRS.Debug.LocalStart(false);
                    BRS.Debug.Comment("Converting " + value + " into an int");

                    int correspondingData = 0;
                    try
                    {
                        correspondingData = Convert.ToInt32(value);
                        Debug.Success();
                    }
                    catch
                    {
                        Debug.Error(value + "Isn't a valid value!");
                    }
                    BRS.Debug.LocalEnd();
                    return correspondingData;
                }
                //#############################################################//
                /// <summary>
                /// Transform an int address into the string which needs to be
                /// sent on the SerialPort to the beagleboneblue
                /// </summary>
                /// <param name="value"></param>
                /// <returns></returns>
                //#############################################################//
                public static string ParseValue(int value)
                {
                    BRS.Debug.LocalStart(false);
                    BRS.Debug.Comment("Attempting to convert " + value.ToString() + " into a sendable string");
                    string result = "";

                    try
                    {
                        result = value.ToString("X");
                        Debug.Success();
                    }
                    catch
                    {
                        Debug.Error("Could not transform " + value.ToString() + " into hexadcimal");
                    }
                    BRS.Debug.LocalEnd();
                    return result;
                }
                #endregion Value
                #endregion Parsing
            }
            #endregion Methods
        }
        #endregion CAN_Class
    }
}
