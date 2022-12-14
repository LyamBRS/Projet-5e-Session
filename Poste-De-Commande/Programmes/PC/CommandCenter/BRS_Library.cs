//#############################################//
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Threading.Tasks;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;
using System.IO.Ports;
using System.Management;
using System.Management.Instrumentation;
using System.Threading;
using static System.Windows.Forms.AxHost;
using static System.Net.Mime.MediaTypeNames;
using System.Collections.ObjectModel;
//#############################################//
namespace BRS
{
    /// <summary>
    /// Debugging class. Toggle debugging on using ToggleDebug(true).
    /// Use Header to start and end a main function's debugging.
    /// Don't use headers in functions you know will be called by others.
    /// Use Comment to describe what your code is either about to do, or has done.
    /// </summary>
    public partial class Debug
    {
        public static bool DEBBUG_CONSOLE = false;
        private static bool oldDebugState = false;
        private static int InitialStackSize = 0;
        private static int PreviousIndent = 0;
        private static int RemoveIndent = 0;
        /// <summary>
        /// For different printings.
        /// </summary>
        private static bool InsideAStray = false;
        //#########################################################//
        /// <summary>
        /// Enables all the BRS.Debug.Comment to print in
        /// Console.WriteLine(). DISABLED BY DEFAULT
        /// </summary>
        /// <param name="debugToggled">default to false, set to true to enable comment's printing</param>
        //#########################################################//
        public static void ToggleDebug(bool debugToggled)
        {
            DEBBUG_CONSOLE = debugToggled;
        }
        //#########################################################//
        /// <summary>
        /// Returns true if the toggledebug was initialised at
        /// some point
        /// </summary>
        /// <returns></returns>
        //#########################################################// 
        public static bool CheckIfDebugging()
        {
            return DEBBUG_CONSOLE;
        }
        #region Comments
        //#########################################################//
        /// <summary>
        /// Debug comment shown, and automatically indented in console
        /// if ToggleDebug was set to true.
        /// Used as a standard //Comment replacement. Which allows
        /// a live debugging of your code's current execution step.
        /// This function automatically adds the name of the function
        /// it was called in.
        /// </summary>
        /// <param name="message">What is your code doing</param>
        //#########################################################//
        public static void Comment(string message)
        {
            if (DEBBUG_CONSOLE)
            {
                //Check to see where we are in the stack
                StackTrace stackTrace = new StackTrace();
                StackFrame[] stackFrames = stackTrace.GetFrames();

                //Get how deep we are in the form stack
                int tabs = stackFrames.Length - InitialStackSize - RemoveIndent;

                //Get the function name
                string functionName = "";
                try
                {
                    functionName = stackFrames[1 + RemoveIndent].GetMethod().Name;

                    if(functionName.Equals(".ctor"))
                    {
                        functionName = stackFrames[2 + RemoveIndent].GetMethod().Name;
                    }
                }
                catch
                {
                }

                //Create debugging indentation
                string indentation = "";
                for (int i = 0; i < tabs; i++)
                {
                    indentation = indentation + "|\t";
                }

                //See if we need a empty seperator because stack got smaller
                if (PreviousIndent > tabs)
                {
                    Console.Write(indentation + "|\t\n");
                }

                // Stack increased, show function name
                //if (PreviousIndent < tabs)
                //{
                //   Console.Write(indentation + "[" + functionName + "]:\n");
                //}

                if (PreviousIndent != tabs)
                {
                    PreviousIndent = tabs;
                }

                // Create the string
                Console.Write(indentation + "|\t" + "[" + functionName + "]:\t" + message + "\n");
            }
        }
        //#########################################################//
        /// <summary>
        /// used like a regular comment, however, this overload is to
        /// be used for debugs which can occur in a thread to avoid
        /// confusion with a regular function using a header which
        /// might be printing on the screen as it is called.
        /// </summary>
        /// <param name="message">What is your code doing</param>
        /// <param name="isStray">true: Your function is a Stray function thus needs a special indent</param> 
        //#########################################################//
        public static void Comment(string message, bool isStray)
        {
            if (DEBBUG_CONSOLE)
            {
                //Check to see where we are in the stack
                StackTrace stackTrace = new StackTrace();
                StackFrame[] stackFrames = stackTrace.GetFrames();

                //Get how deep we are in the form stack
                int tabs = stackFrames.Length - InitialStackSize - RemoveIndent;

                //Get the function name
                string functionName = "";
                try
                {
                    functionName = stackFrames[1 + RemoveIndent].GetMethod().Name;

                    if (functionName.Equals(".ctor"))
                    {
                        functionName = stackFrames[2 + RemoveIndent].GetMethod().Name;
                    }
                }
                catch
                {
                }

                //Create debugging indentation
                string indentation = "";
                for (int i = 0; i < tabs; i++)
                {
                    indentation = indentation + "-\t";
                }

                //See if we need a empty seperator because stack got smaller
                if (PreviousIndent > tabs)
                {
                    Console.Write(indentation + "-\t\n");
                }

                // Stack increased, show function name
                //if (PreviousIndent < tabs)
                //{
                //   Console.Write(indentation + "[" + functionName + "]:\n");
                //}

                if (PreviousIndent != tabs)
                {
                    PreviousIndent = tabs;
                }

                // Create the string
                Console.Write(indentation + "-\t" + "[STRAY]:(" + functionName + "):\t" + message + "\n");
            }
        }
        #endregion Comments
        #region Function_States
        //#########################################################//
        /// <summary>
        /// Comment with automatically added [! SUCCESS !]:
        /// to remove some text from your debug comment in your
        /// script. This is to say your process was Success,
        /// and not aborted nor was there an error.
        /// </summary>
        /// <param name="message">What is your code doing</param>
        //#########################################################//
        public static void Success(string message)
        {
            if (DEBBUG_CONSOLE)
            {
                Console.ForegroundColor = ConsoleColor.Green;

                RemoveIndent = 1;
                Debug.Comment("[! SUCCESS !]: " + message);
                RemoveIndent = 0;
                Console.ForegroundColor = ConsoleColor.White;
            }
        }
        //#########################################################//
        /// <summary>
        /// Comment [! SUCCESS !]
        /// This is to say your process was Success.
        /// Not aborted nor was there an error.
        /// </summary>
        //#########################################################//
        public static void Success()
        {
            if (DEBBUG_CONSOLE)
            {
                Console.ForegroundColor = ConsoleColor.Green;

                RemoveIndent = 1;
                Debug.Comment("[! SUCCESS !]");
                RemoveIndent = 0;
                Console.ForegroundColor = ConsoleColor.White;
            }
        }
        //#########################################################//
        /// <summary>
        /// Comment with automatically added [* ABORTED *]:
        /// to remove some text from your debug comment in your
        /// script. This is to say your process was aborted.
        /// </summary>
        /// <param name="message">Why was it aborted</param>
        //#########################################################//
        public static void Aborted(string message)
        {
            if (DEBBUG_CONSOLE)
            {
                Console.ForegroundColor = ConsoleColor.DarkYellow;

                RemoveIndent = 1;
                Debug.Comment("[* ABORTED *]: " + message);
                RemoveIndent = 0;
                Console.ForegroundColor = ConsoleColor.White;
            }
        }
        //#########################################################//
        /// <summary>
        /// Comments [* ABORTED *]
        /// This is to say your process was aborted, without any
        /// message
        /// </summary>
        //#########################################################//
        public static void Aborted()
        {
            if (DEBBUG_CONSOLE)
            {
                Console.ForegroundColor = ConsoleColor.DarkYellow;
                RemoveIndent = 1;
                Debug.Comment("[* ABORTED *]:");
                RemoveIndent = 0;
                Console.ForegroundColor = ConsoleColor.White;
            }
        }
        //#########################################################//
        /// <summary>
        /// Comment with automatically added [? ERROR ?]:
        /// to remove some text from your debug comment in your
        /// script.  This is to say your process ran in an error.
        /// </summary>
        /// <param name="message">Why is there an error?</param>
        //#########################################################//
        public static void Error(string message)
        {
            if (DEBBUG_CONSOLE)
            {
                Console.ForegroundColor = ConsoleColor.Red;

                RemoveIndent = 1;
                Debug.Comment("[## ERROR ##]: " + message);
                RemoveIndent = 0;
                Console.ForegroundColor = ConsoleColor.White;
            }
        }
        //#########################################################//
        /// <summary>
        /// Displays [? ERROR ?]
        /// This is to say your process ran in an error.
        /// </summary>
        //#########################################################//
        public static void Error()
        {
            if (DEBBUG_CONSOLE)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                RemoveIndent = 1;
                Debug.Comment("[## ERROR ##]");
                RemoveIndent = 0;
                Console.ForegroundColor = ConsoleColor.White;
            }
        }
        #endregion Function_States
        //#########################################################//
        /// <summary>
        /// Break lines at the start and end of a big function.
        /// Avoid placing these in functions called by multiple functions.
        /// </summary>
        /// <param name="start"> set to true when starting your main function debug. Set to false to close the debug</param>
        //#########################################################//
        public static void Header(bool start)
        {
            if (DEBBUG_CONSOLE)
            {
                //Check to see where we are in the stack
                StackTrace stackTrace = new StackTrace();
                StackFrame[] stackFrames = stackTrace.GetFrames();

                InitialStackSize = stackFrames.Length;
                PreviousIndent = 0;

                string functionName = stackFrames[1].GetMethod().Name;

                string header = start ? "\\/#\\/#\\/#\\/#\\/#\\/#\\/#\\/#\\/#\\/#\\/#\\/#\\/#\\/#\\/#\\/#\\/#" :
                                        "/\\#/\\#/\\#/\\#/\\#/\\#/\\#/\\#/\\#/\\#/\\#/\\#/\\#/\\#/\\#/\\#/\\#";

                // Create the string
                Console.WriteLine(header + "[" + functionName + "]: " + (start ? "START" : "END"));

                //line return on header end
                if (start == false)
                {
                    Console.WriteLine("");
                }
            }
        }
        #region LocalDebug
        //#########################################################//
        /// <summary>
        /// Function allowing the user to debug a single main function
        /// or turn off it's debugging. Turning off ToggleDebug will
        /// also turn off local debugs. Place this at the very
        /// beginning of your functions.
        /// </summary>
        /// <param name="state">Setting to false will turn off this function's debug. ToggleDebug must have been set to true to be used.</param>
        //#########################################################//
        public static void LocalStart(bool state)
        {
            oldDebugState = DEBBUG_CONSOLE;
            BRS.Debug.ToggleDebug(state && Debug.DEBBUG_CONSOLE);
        }
        //#########################################################//
        /// <summary>
        /// Used as a closing statement for LocalStart debugging.
        /// Place this at the end of a function before return
        /// statements.
        /// </summary>
        //#########################################################//
        public static void LocalEnd()
        {
            BRS.Debug.ToggleDebug(oldDebugState);
        }
        #endregion LocalDebug
        /*
        #region StrayFunctionsHeaders
        //#########################################################//
        /// <summary>
        /// A stray function is a function which runs parralel to the
        /// main functions but still wants to be debugged.
        /// Exemple being temporary threads.
        /// Basically, use this for functions which can call themselves
        /// while others are already being displayed
        /// </summary>
        /// <param name="start"> set to true when starting your main function debug. Set to false to close the debug</param>
        //#########################################################//
        public static void StrayHeader(bool start)
        {
            if (DEBBUG_CONSOLE)
            {
                //Check to see where we are in the stack
                StackTrace stackTrace = new StackTrace();
                StackFrame[] stackFrames = stackTrace.GetFrames();

                InitialStackSize = stackFrames.Length;
                PreviousIndent = 0;

                string functionName = stackFrames[1].GetMethod().Name;

                string header = start ? "(STRAY)____________________________________________________________________" :
                                        "(STRAY)____________________________________________________________________";

                // Create the string
                Console.WriteLine(header + "[" + functionName + "]: " + (start ? "(START)" : "(END)"));

                //line return on header end
                if (start == false)
                {
                    Console.WriteLine("");
                }
            }
        }
        #endregion StrayFunctionsHeaders
        */
    }
    //#########################################################//
    /// <summary>
    /// Class handling pop up messages.
    /// Made using MessageBox.
    /// Those are prefab message boxes that helps uniformize
    /// standard pop up messages in your applications
    /// while reducing the amount of shown code in your scripts.
    /// </summary>
    //#########################################################//
    public class PopUp
    {
        //#########################################################//
        /// <summary>
        /// Displays an error textbox, with an OK button.
        /// First parameter is the error message wanted for display
        /// and the second is the pop up header
        /// </summary>
        /// <param name="message">Message inside the box</param>
        /// <param name="caption">Box title or header</param>
        //#########################################################//
        public static void Error(string message, string caption)
        {
            BRS.Debug.Comment("[BRS]: Poping error box on user screen...");
            MessageBox.Show(message, caption, MessageBoxButtons.OK, MessageBoxIcon.Error);
            BRS.Debug.Comment("[BRS]: Error box closed!");
        }
        //#########################################################//
        /// <summary>
        /// Pop up a warning box for your user.
        /// Has a warning icon
        /// and returns true if the user pressed on "OK"
        /// Buttons shown are "OK" and "Cancel"
        /// </summary>
        /// <param name="message">Message inside the box</param>
        /// <param name="caption">Box title or header</param>
        /// <returns> true if used clicked on OK</returns>
        //#########################################################//        
        public static bool UserWarning(string message, string caption)
        {
            BRS.Debug.Comment("[BRS]: Poping warning messagebox on user screen...");
            return (MessageBox.Show(message, caption, MessageBoxButtons.OKCancel, MessageBoxIcon.Warning) == DialogResult.OK);
        }
        //#########################################################//
        /// <summary>
        /// Pop up an information box for your user.
        /// Has an "i" information icon
        /// does not return true.
        /// Button showed is "OK"
        /// </summary>
        /// <param name="message">Message inside the box</param>
        /// <param name="caption">Box title or header</param>
        //#########################################################//
        public static void Info(string message, string caption)
        {
            BRS.Debug.Comment("[BRS]: Poping information box on user screen...");
            MessageBox.Show(message, caption, MessageBoxButtons.OK, MessageBoxIcon.Information);
            BRS.Debug.Comment("[BRS]: Info box closed!");
        }
        //#########################################################//
        /// <summary>
        /// Pop up a question box for your user.
        /// Has an "?" question icon
        /// returns true if user selected "yes"
        /// Button showed is "Yes" and "No"
        /// </summary>
        /// <param name="message">Message inside the box</param>
        /// <param name="caption">Box title or header</param>
        //#########################################################//
        public static bool Question(string message, string caption)
        {
            BRS.Debug.Comment("[BRS]: Poping question box on user screen...");
            return (MessageBox.Show(message, caption, MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes);
        }
    }
    //#########################################################//
    /// <summary>
    ///  Class handling windows file saving or opening window.
    ///  They do not handle paths, they will return the file
    ///  path or ABORT if the user ended their dialogs
    /// </summary>
    //#########################################################//
    public class Dialog
    {
        //#########################################################//
        /// <summary>
        /// Handles the entire save file dialog event for you.
        /// The input filter will define the type of file ot save.
        /// And will create the path returned. If ABORT is returned
        /// it means the user canceled the saving process
        /// </summary>
        /// <param name="header">Title of your windows pop up window</param>
        /// <param name="filter">string being the filter your dialog will have when looking through files</param>
        /// <returns>file path or "ABORT"</returns>
        //#########################################################// 
        public static string SaveTextFile(string header, string filter)
        {
            BRS.Debug.Comment("Creating a new SaveFileDialog");
            SaveFileDialog SFD = new SaveFileDialog();

            BRS.Debug.Comment("Setting dialogs settings to:");
            BRS.Debug.Comment("Filter: " + filter);
            SFD.Filter = filter;
            BRS.Debug.Comment("Header: " + header);
            SFD.Title = header;

            //////////////////////////////////////////////////////////////////////////// - [ checks ]
            BRS.Debug.Comment("Showing dialog and waiting for user confirmation...");
            if (SFD.ShowDialog() == DialogResult.OK)
            {
                BRS.Debug.Success("Dialog processed by user");
                BRS.Debug.Comment("Executing precautionary checks on the file path...");
                // Check if directory path exist
                if (SFD.CheckPathExists)
                {
                    if (!SFD.CheckFileExists)
                    {
                        // If name was empty
                        if (SFD.FileName.Contains("among us"))
                        {
                            BRS.Debug.Aborted("Unallowed file name used. among us is not valid");
                            BRS.PopUp.Error("Your file cannot be an imposter", "Saving Error");
                        }
                        else
                        {
                            BRS.Debug.Success("Path tests is correct.");
                            BRS.Debug.Comment("Returning the file's path name.");

                            return (SFD.FileName);
                        }
                    }
                    else
                    {
                        BRS.Debug.Error("File is a duplicate");
                        BRS.PopUp.Error("This file already exist", "Saving Error");
                    }
                }
                else
                {
                    BRS.Debug.Error("Specified path is invalid");
                    BRS.PopUp.Error("Invalid directory path", "Saving Error");
                }
            }

            BRS.Debug.Aborted("Dialog terminated by user. Returning: ABORT");
            return ("ABORT");
        }
        //#########################################################//
        /// <summary>
        /// Handles the entire open file dialog event for you.
        /// The input filter will define the type of file that can be opened.
        /// Will get the path of said file and return it. 
        /// If aborted by user, "ABORT" is returned
        /// </summary>
        /// <param name="header">Title of your windows pop up window</param>
        /// <param name="filter">string being the filter your dialog will have when looking through files</param>
        /// <returns>file path or "ABORT"</returns>
        //#########################################################// 
        public static string OpenFile(string header, string filter)
        {
            string result = "ABORT";

            BRS.Debug.Comment("Creating new open file dialog");
            OpenFileDialog OFD = new OpenFileDialog();

            // Set filters for an RTF documents
            BRS.Debug.Comment("Setting dialogs settings to:");
            BRS.Debug.Comment("Setting filter to: " + filter);
            try
            {
                OFD.Filter = filter;
                BRS.Debug.Success("");
            }
            catch
            {
                BRS.Debug.Error("FILTER IS NOT VALID");
                BRS.Debug.Error("FILTER IS NOT VALID");
                BRS.Debug.Error("FILTER IS NOT VALID");
                return ("ABORT");
            }
            BRS.Debug.Comment("Header: " + header);
            OFD.Title = header;

            BRS.Debug.Comment("Poping up dialog to the user. Awaiting input");
            //////////////////////////////////////////////////////////////////////////// - [ checks ]
            if (OFD.ShowDialog() == DialogResult.OK)
            {
                BRS.Debug.Success("Dialog processed by user");
                BRS.Debug.Comment("Executing precautionary checks on the file path...");

                // If name was sus
                if (OFD.FileName.Contains("among us"))
                {
                    BRS.Debug.Aborted("Unallowed file name used. among us is not valid");
                    BRS.PopUp.Error("Your file cannot be an imposter", "Saving Error");
                }
                else
                {
                    //Check if file is .rtf
                    if (true)
                    {
                        BRS.Debug.Success("Precautionary tests on path");
                        BRS.Debug.Comment("Setting result to file path");
                        //////////////////////////////////////////////////////////// - [Create new RTF file]
                        result = OFD.FileName;
                        ////////////////////////////////////////////////////////////
                    }
                    else
                    {
                        BRS.PopUp.Error("If you see this, cry.", "if(true) was false...");
                        return ("ABORT");
                    }
                }
            }
            BRS.Debug.Comment("Returning: " + result);
            return (result);
        }
    }
    //#########################################################//
    /// <summary>
    ///  Class helping the handling of FTDI communication ports
    ///  Especially for DS89C450
    /// </summary>
    //#########################################################//
    public class FTDI
    {
        public static SerialPort FTDIPort = new SerialPort();
        /// <summary>
        /// The full name of the found serial port.
        /// "USB Serial Com port (COM 4)"
        /// </summary>
        public static string ConnectedFTDI = "No Device";
        /// <summary>
        /// The com number string of the found FTDI port.
        /// "COM 4"
        /// </summary>
        public static string FTDIComName = "No Device"; //COM4 COM5 ect
        /// <summary>
        /// String resulted after an HEX file has been
        /// send to the FTDI in a programming attempt.
        /// </summary>
        public static string ProgrammingResult = "";

        private static string LastHexFile = "";

        static ManagementClass processClass = new ManagementClass("Win32_PnPEntity");

        //#########################################################//
        /// <summary>
        /// Lists all the USB ports, no matter their types for 
        /// debugging purposes
        /// </summary>
        //#########################################################//
        public static void ListUSBPorts()
        {
            //####################################################################### From Gaurav Sangwan 2017
            ManagementObjectCollection Ports = processClass.GetInstances();

            BRS.Debug.Comment("[BRS]: Printing all available ports:");
            foreach (ManagementObject prop in Ports)
            {
                if (prop.GetPropertyValue("Name") != null)
                {
                    if (prop.GetPropertyValue("Name").ToString().Contains("USB") ||
                        prop.GetPropertyValue("Name").ToString().Contains("COM"))
                    {
                        BRS.Debug.Comment("\t" + prop.GetPropertyValue("Name").ToString() + "\t" + Convert.ToString(prop));
                    }
                }
            }
            //#######################################################################
            BRS.Debug.Comment("[BRS]: Printing all available properties:");
            PropertyDataCollection properties = processClass.Properties;
            foreach (PropertyData property in properties)
            {
                BRS.Debug.Comment("\t" + property.Name);

                foreach (QualifierData q in property.Qualifiers)
                {
                    BRS.Debug.Comment("\t\t" + Convert.ToString(q.Name));
                    if (q.Name.Equals("Description"))
                    {
                        BRS.Debug.Comment(Convert.ToString(q));
                    }
                }
            }
        }
        //#########################################################//
        /// <summary>
        /// Creates the thread which checks for changes in the serial ports
        /// and then calls LookForFTDI once a change occured
        /// </summary>
        //#########################################################// 
        public static void startFTDIUpdater()
        {
            BRS.Debug.Comment("Creating FTDI thread");
            Thread FTDIThread = new Thread(LookForSerialChanges);
            BRS.Debug.Comment("Starting thread!");
            FTDIThread.Start();
        }
        //#########################################################//
        /// <summary>
        /// Thread function looking for changes in serial ports
        /// </summary>
        //#########################################################// 
        private static void LookForSerialChanges()
        {
            WqlEventQuery query = new WqlEventQuery("SELECT * FROM Win32_DeviceChangeEvent");
            ManagementEventWatcher watcher = new ManagementEventWatcher(query);

            watcher.EventArrived += new EventArrivedEventHandler(HandleSerialChanges);

            // Start listening for events
            watcher.Start();

            // Do something while waiting for events
            System.Threading.Thread.Sleep(500);

            // Stop listening for events
            //watcher.Stop();
        }
        private static void HandleSerialChanges(object sender, EventArrivedEventArgs e)
        {
            ConnectedFTDI = LookForFTDI();
            try
            {
                FTDIComName = ConnectedFTDI.Split('(', ')')[1];
            }
            catch
            {
                FTDIComName = "No Device";
            }
        }
        //#########################################################// 
        /// <summary>
        /// Updates ComPort.ConnectedFTDI
        /// aswell as
        /// ComPort.FTDIComName
        /// manually.
        /// </summary>
        //#########################################################// 
        public static void UpdateFTDIInfo()
        {
            ConnectedFTDI = LookForFTDI();
            try
            {
                FTDIComName = ConnectedFTDI.Split('(', ')')[1];
            }
            catch
            {
                FTDIComName = "No Device";
            }
        }
        //#########################################################//
        /// <summary>
        /// Searches all PnPEntities and returns the com port name
        /// of the first detected port which has FTDI as the
        /// manufacturer.
        /// </summary>
        /// <returns>Name of the FTDI port, or "No Device"</returns>
        //#########################################################// 
        public static string LookForFTDI()
        {
            ManagementObjectCollection Ports = processClass.GetInstances();

            //Update the list of  ports
            processClass = new ManagementClass("Win32_PnPEntity");

            //ittering the list of USB ports
            foreach (ManagementObject prop in Ports)
            {
                if (prop.GetPropertyValue("Name") != null)
                {
                    if (prop.GetPropertyValue("Manufacturer") != null)
                    {
                        if (prop.GetPropertyValue("Name").ToString().Contains("USB") &&
                            prop.GetPropertyValue("Name").ToString().Contains("COM") &&
                            prop.GetPropertyValue("Manufacturer").Equals("FTDI")
                            )
                        {
                            //BRS.Debug.Success("[BRS]: FTDI found: " + prop.GetPropertyValue("Name").ToString());
                            return (prop.GetPropertyValue("Name").ToString());
                        }
                    }
                }
            }
            // No device with FTDI as a manufacturer was found.
            return ("No Device");
        }
        //#########################################################// 
        /// <summary>
        /// Sends an hex file on serial port, and calls a function
        /// after sending :. (received a G).
        /// </summary>
        /// <param name="HexString"></param>
        /// <param name="ToDoWhenGReceived">Executed returnless function everytime a G is received</param>
        /// <returns>String. "Programmed","No Replies","Error"</returns>
        //#########################################################// 
        public static string SendHexFileDS89(string HexString, Action ToDoWhenGReceived)
        {
            BRS.Debug.Comment("Checking if FTDI Port is opened");
            if(FTDIPort.IsOpen)
            {
                BRS.Debug.Comment("Saving HEX file");
                BRS.FTDI.LastHexFile = HexString;

                string result = "";
                BRS.FTDI.FTDIPort.ReadExisting();
                BRS.Debug.Comment("Sending ENTER...");
                FTDIPort.Write("\r");
                Thread.Sleep(100);

                result = BRS.FTDI.ReadPort(FTDIPort,10,100);
                BRS.Debug.Comment(result);

                BRS.Debug.Comment("Sending KILL value");
                FTDIPort.Write("K\r");
                Thread.Sleep(100);

                BRS.Debug.Comment("Parsing Dallas's response...");
                result = BRS.FTDI.ReadPort(FTDIPort, 10, 100);
                BRS.Debug.Comment(result);
                BRS.Debug.Comment("[FINISHED]");

                BRS.Debug.Comment("Checking for >");
                if(!result.Contains(">"))
                {
                    BRS.Debug.Error("No appropriate answers from FTDI");
                    return("No Replies");
                }
                BRS.Debug.Success("[FINISHED]");

                Thread.Sleep(100);
                BRS.Debug.Comment("Sending L value");
                FTDIPort.Write("L\r");
                Thread.Sleep(100);

                BRS.Debug.Comment("Parsing Dallas's response...");
                result = BRS.FTDI.ReadPort(FTDIPort, 10, 100);
                BRS.Debug.Comment(result);
                BRS.Debug.Comment("[FINISHED]");

                //////////////////////////////////////////////////////////
                BRS.Debug.Comment("Splitting Hex file into G's");
                string[] parsedHex = HexString.Split('\r');

                result = "";
                BRS.Debug.Comment("Sending hex file...");
                foreach(string separation in parsedHex)
                {
                    FTDIPort.Write(separation);
                    BRS.Debug.Comment(separation.Replace("\n",""));

                    ToDoWhenGReceived();
                }

                Thread.Sleep(100);
                //Check if bad command is received
                result = BRS.FTDI.FTDIPort.ReadExisting();
                if (result.Contains("BAD"))
                {
                    BRS.Debug.Error("Fatal error while sending file");
                    return ("Error");
                }

                BRS.Debug.Success("Sent!");
                BRS.FTDI.ProgrammingResult = result;
                return ("Programmed");
            }
            return ("No Replies");
        }
        //#########################################################// 
        /// <summary>
        /// verifies the string received from the programmed device
        /// and parses it to find ERROR characters such as:
        /// A,H,L,S,F,V
        /// </summary>
        /// <returns>found error</returns>
        //#########################################################// 
        public static string VerifyLastProgramming()
        {
            BRS.Debug.Comment("Removing random characters from programming results...");
            BRS.FTDI.ProgrammingResult = BRS.FTDI.ProgrammingResult.Replace("\r","");
            BRS.FTDI.ProgrammingResult = BRS.FTDI.ProgrammingResult.Replace(" ", "");
            BRS.FTDI.ProgrammingResult = BRS.FTDI.ProgrammingResult.Replace("\n", "");
            BRS.FTDI.ProgrammingResult = BRS.FTDI.ProgrammingResult.Replace(">", "");

            BRS.Debug.Comment("Programming result was: ");
            BRS.Debug.Comment(BRS.FTDI.ProgrammingResult);

            if (BRS.FTDI.GetHexFileSize(BRS.FTDI.LastHexFile) != BRS.FTDI.ProgrammingResult.Length)
            {
                BRS.Debug.Comment(BRS.FTDI.GetHexFileSize(BRS.FTDI.LastHexFile).ToString());
                BRS.Debug.Comment(BRS.FTDI.ProgrammingResult.Length.ToString());
                BRS.Debug.Comment(BRS.FTDI.ProgrammingResult);
                return ("File not fully programmed");
            }
            else // Correct amount of Gs
            {
                // Check if the button was flipped during programming
                if (BRS.FTDI.ProgrammingResult.Contains("89"))
                {
                    return ("Programming was turned off");
                }

                // Check sum did not match
                if (BRS.FTDI.ProgrammingResult.Contains("S"))
                {
                    return ("S:Checksum Error");
                }

                // Critical flash memory error
                if (BRS.FTDI.ProgrammingResult.Contains("F"))
                {
                    return ("F:Flash Memory error!");
                }

                // Invalid address in Intel Hex record.
                if (BRS.FTDI.ProgrammingResult.Contains("A"))
                {
                    return ("A:Address exeeded flash memory");
                }

                // Invalid Intel hex record format: contains non hex character
                if (BRS.FTDI.ProgrammingResult.Contains("H"))
                {
                    return ("H:Invalid HEX was sent!");
                }

                // Invalid Intel Hex record type
                if (BRS.FTDI.ProgrammingResult.Contains("L"))
                {
                    return ("L:Hex lenght error");
                }

                // Programming bytes more than once.
                if (BRS.FTDI.ProgrammingResult.Contains("P"))
                {
                    return ("P:Bytes programmed more than once");
                }

                return ("Success!");
            }
        }
        //#########################################################// 
        /// <summary>
        /// Reads a com port, and outputs a string as the result.
        /// This will continuously read until said com port
        /// stops sending values, or this process times out.
        /// TimeOut IS AN AMOUNT OF INTERVALS
        /// </summary>
        /// <param name="port"> defined and initialised serial port to read from </param>
        /// <param name="readingIntervals">intervals in ms at which readings are done</param>
        /// <param name="TimeOut"> amount of intervals before exiting while loop</param>
        /// <returns></returns>
        //#########################################################//  
        public static string ReadPort(SerialPort port, int readingIntervals, int TimeOut)
        {
            string result = "";
            if (port.IsOpen)
            {
                BRS.Debug.Comment("Starting COM reading...");
                if (readingIntervals > 0)
                {
                    if (TimeOut > readingIntervals)
                    {
                        BRS.Debug.Success("Passed reading tests");
                        BRS.Debug.Comment("Initiating while loop...");

                        string buffer = "A";
                        while (!buffer.Equals(""))
                        {
                            buffer = port.ReadExisting();

                            if (!buffer.Equals(""))
                            {
                                result = result + buffer;
                            }

                            Thread.Sleep(readingIntervals);
                            TimeOut--;

                            if (TimeOut <= 0)
                            {
                                BRS.Debug.Error("Reading timedOut!");
                                buffer = "";
                            }
                        }
                        BRS.Debug.Success("Exited while loop, sending result...");
                        return (result);
                    }
                    else
                    {
                        BRS.Debug.Error("TimeOut Cannot be 0");
                        result = "[ERROR] TimeOut can't be 0";
                        return (result);
                    }
                }
                else
                {
                    BRS.Debug.Error("Interval cannot be below 0ms");
                    result = "[ERROR] Interval can't be 0";
                    return (result);
                }
            }
            else
            {
                BRS.Debug.Error("Attempted to read closed port");
                return ("");
            }
            result = "[ERROR] COM reading never occured.";
            BRS.Debug.Error("Something went wrong");
            return (result);
        }
        //#########################################################//  
        /// <summary>
        /// returns the amount of Gs a file is going to send when
        /// sent for programming (:) in an HEX file.
        /// </summary>
        /// <param name="HexString">Hex file converted to a string</param>
        /// <returns></returns>
        //#########################################################//   
        public static int GetHexFileSize(string HexString)
        {
            BRS.Debug.Comment("Parsing hex file...");
            BRS.Debug.Comment("Counting :'s ");

            return (HexString.Length - HexString.Replace(":","").Length);
        }
    }
    //#########################################################//
    /// <summary>
    ///  Class helping the handling of a communication port
    ///  Allows it to be referenced globally without the need
    ///  for references.
    /// </summary>
    //#########################################################//
    public class ComPort
    {
        /// <summary>
        /// Global generic SerialPort class accessible to all files using BRS namespace
        /// </summary>
        public static SerialPort Port = new SerialPort();

        private static SerialPort TemporaryPort = new SerialPort();
        /// <summary>
        /// The full name of the found serial port.
        /// "USB Serial Com port (COM 4)"
        /// </summary>
        public static string LinkedFullName = "No Device";
        /// <summary>
        /// The com number string of the wanted port.
        /// "COM 4"
        /// </summary>
        public static string LinkedComName = "No Device"; //COM4 COM5 ect

        /// <summary>
        /// Collection to check using a delegate in your form
        /// </summary>
        public static ObservableCollection<string> ListOfPortChanged = new ObservableCollection<string>();

        /// <summary>
        /// List of the full names of ComPort available for linking attempts.
        /// </summary>
        public static List<string> AvailableComsFullName = new List<string>();

        /// <summary>
        /// Set this to be a called function when RX buffer receives data.
        /// </summary>
        public static Action DataReceivedAction;

        static ManagementClass processClass = new ManagementClass("Win32_PnPEntity");

        //#########################################################//
        /// <summary>
        /// Lists all the USB ports, no matter their types, for 
        /// debugging purposes
        /// </summary>
        //#########################################################//
        public static void ListUSBPorts()
        {
            //####################################################################### From Gaurav Sangwan 2017
            ManagementObjectCollection Ports = processClass.GetInstances();

            BRS.Debug.Comment("[BRS]: Printing all available ports:");
            foreach (ManagementObject prop in Ports)
            {
                if (prop.GetPropertyValue("Name") != null)
                {
                    if (prop.GetPropertyValue("Name").ToString().Contains("USB") ||
                        prop.GetPropertyValue("Name").ToString().Contains("COM"))
                    {
                        BRS.Debug.Comment("\t" + prop.GetPropertyValue("Name").ToString() + "\t" + Convert.ToString(prop));
                    }
                }
            }
            //#######################################################################
            BRS.Debug.Comment("[BRS]: Printing all available properties:");
            PropertyDataCollection properties = processClass.Properties;
            foreach (PropertyData property in properties)
            {
                BRS.Debug.Comment("\t" + property.Name);

                foreach (QualifierData q in property.Qualifiers)
                {
                    BRS.Debug.Comment("\t\t" + Convert.ToString(q.Name));
                    if (q.Name.Equals("Description"))
                    {
                        BRS.Debug.Comment(Convert.ToString(q));
                    }
                }
            }
        }
        //#########################################################//
        /// <summary>
        /// Creates the thread which checks for changes in the serial ports
        /// and then calls CheckIfAvailable once a change occured
        /// </summary>
        //#########################################################// 
        public static void startPortUpdater()
        {
            BRS.Debug.Comment("Creating standard serial port thread");
            Thread PortThread = new Thread(LookForSerialChanges);
            BRS.Debug.Comment("Starting thread!");
            PortThread.Start();
        }
        //#########################################################//
        /// <summary>
        /// Creates the event that checks when ComPort.Port
        /// receives any data.
        /// Place a function in this class for it to be executed
        /// each time data is received
        /// </summary>
        //#########################################################// 
        public static void createInfoReceivedEvent()
        {
            BRS.Debug.Comment("Creating new event watcher for received data over serial port");
            ComPort.Port.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
            Debug.Success("");
        }

        private static void DataReceivedHandler(object sender,SerialDataReceivedEventArgs e)
        {
            DataReceivedAction();
        }
        //#########################################################//
        /// <summary>
        /// Thread function looking for changes in serial ports
        /// </summary>
        //#########################################################// 
        private static void LookForSerialChanges()
        {
            WqlEventQuery query = new WqlEventQuery("SELECT * FROM Win32_DeviceChangeEvent");
            ManagementEventWatcher watcher = new ManagementEventWatcher(query);

            watcher.EventArrived += new EventArrivedEventHandler(HandleSerialChanges);

            // Start listening for events
            watcher.Start();

            // Checking each 500ms
            System.Threading.Thread.Sleep(500);
        }
        //#########################################################// 
        /// <summary>
        /// Executed when DeviceChangeEvent occurs
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#########################################################//  
        private static void HandleSerialChanges(object sender, EventArrivedEventArgs e)
        {
            StoreAllAvailableComs();
        }
        //#########################################################// 
        /// <summary>
        /// Updates Full name and com name by searching if the
        /// selected port is still available for use.
        /// </summary>
        //#########################################################// 
        public static void UpdatePortInfo()
        {
            try
            {
                LinkedComName = LinkedFullName.Split('(', ')')[1];
            }
            catch
            {
                LinkedComName = "No Device";
            }
        }
        //#########################################################//
        /// <summary>
        /// Stores a list of all available SerialPorts in
        /// AvailableComsFullName
        /// Note that you need to parse the given names to extract
        /// COMX from them.
        /// </summary>
        //#########################################################// 
        public static void StoreAllAvailableComs()
        {
            //####################################################################### From Gaurav Sangwan 2017
            ManagementObjectCollection Ports = processClass.GetInstances();

            AvailableComsFullName.Clear();

            foreach (ManagementObject prop in Ports)
            {
                if (prop.GetPropertyValue("Manufacturer") != null && prop.GetPropertyValue("Name") != null)
                {
                    if (prop.GetPropertyValue("Name").ToString().Contains("COM"))
                    {
                        AvailableComsFullName.Add(prop.GetPropertyValue("Name").ToString() + "  \t  " + prop.GetPropertyValue("Manufacturer").ToString());
                    }
                }
            }
            ListOfPortChanged.Clear();
        }
        //#########################################################// 
        /// <summary>
        /// Sends an hex/txt file on serial port seperated, by \r
        /// </summary>
        /// <param name="FileString">Your file, as a string</param>
        /// <returns>TX reply 100ms after file was sent.</returns>
        //#########################################################// 
        public static string SendFile(string FileString)
        {
            BRS.Debug.Comment("Checking if Port is opened");
            if (Port.IsOpen)
            {
                //////////////////////////////////////////////////////////
                BRS.Debug.Comment("Splitting Hex file into G's");
                string[] parsedFile = FileString.Split('\r');

                string result = "";
                BRS.Debug.Comment("Sending hex file...");
                foreach (string separation in parsedFile)
                {
                    Port.Write(separation);
                    BRS.Debug.Comment(separation.Replace("\n", ""));
                }

                BRS.Debug.Success("Sent!");
                return ("Sent");
            }
            return ("No Replies");
        }
        //#########################################################// 
        /// <summary>
        /// Checks if your inputed serial port is available or not
        /// for opening.
        /// </summary>
        /// <param name="ComName">COM1 COM2 ect</param>
        /// <returns>Exception names or "Available"</returns>
        //#########################################################//  
        public static string CheckAvailability(string ComName)
        {
            BRS.Debug.Comment("Seting temporary port as " + ComName);
            ComPort.TemporaryPort.PortName = ComName;
            Debug.Success("");

            BRS.Debug.Comment("Verifying if opened...");
            try
            {
                BRS.Debug.Comment("Attempting connection...");
                ComPort.TemporaryPort.Open();
                Debug.Success("");

                BRS.Debug.Comment("Closing connection...");
                ComPort.TemporaryPort.Close();
                Debug.Success("");

                return ("Available");
            }
            catch(IOException error)
            {
                string errorName = error.GetType().Name;
                Debug.Error(errorName.ToString());
                return (errorName);
            }
            return ("ERROR");
        }    
    }
    //#########################################################//
    /// <summary>
    ///  Class handling windows file saving or opening window.
    ///  They do not handle paths, they will return the file
    ///  path or ABORT if the user ended their dialogs
    /// </summary>
    //#########################################################//
    public class FileWatcher
    {
        private static string FileLocation = "empty";
        private static FileSystemWatcher watcher;

        /// <summary>
        /// Flag raised when the files at the specified location
        /// changed
        /// </summary>
        public static bool FileChanged = false;
        //#########################################################//
        /// <summary>
        /// Sets the file path that will be checked for change
        /// events
        /// </summary>
        /// <param name="path">File path</param>
        //#########################################################// 
        public static void SetFileLocation(string path)
        {
            FileLocation = path;
        }
        //#########################################################// 
        /// <summary>
        /// Start FileWatcher thread
        /// be sure to have a specifed Path.
        /// Do this using SetFileLocation
        /// </summary>
        //#########################################################// 
        public static void CreateFileWatcher()
        {
            string result = "";
            BRS.Debug.Comment("Checking if path is valid...");
            if(File.Exists(FileLocation))
            {
                BRS.Debug.Success("Path is valid, getting directory path");
                result = Path.GetDirectoryName(FileLocation);
            }
            else
            {
                BRS.Debug.Error("Path invalid");

                return;
            }

            BRS.Debug.Comment("Overwriting file watcher using new location");
            watcher = new FileSystemWatcher(@result);

            BRS.Debug.Comment("Setting notification parameters...");
            watcher.NotifyFilter = NotifyFilters.LastWrite;

            BRS.Debug.Comment("Creating watcher handler...");
            watcher.Changed += OnChanged;
            watcher.Filter = "*.hex";

            watcher.IncludeSubdirectories = true;
            watcher.EnableRaisingEvents = true;
        }
        //#########################################################// 
        /// <summary>
        /// PRIVATE. Handler for file changed event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#########################################################// 
        private static void OnChanged(object sender, FileSystemEventArgs e)
        {
            if (e.ChangeType != WatcherChangeTypes.Changed)
            {
                return;
            }
            BRS.Debug.Comment("File has changed");
            FileChanged = true;
        }
    }
    //#########################################################//
    /// <summary>
    /// Class used to handle a fake terminal which uses 
    /// </summary>
    //#########################################################//
    public class Terminal
    {
        #region Variables
        /// <summary>
        /// This variable decides if the terminal should log
        /// what the user sends. If false, TX inputs won't be
        /// saved. (Default to false)
        /// </summary>
        public bool ShowTX = false;
        /// <summary>
        /// Defines if the control should automatically scroll
        /// to the end of the richtextbox whenever this one is
        /// focused and TextChanges
        /// </summary>
        public bool AutoScroll = true;
        /// <summary>
        /// This variable allows you to hide received data
        /// if it is exactly equal to what was just previously sent
        /// manually.
        /// </summary>
        public bool HideAllTX = true;
        /// <summary>
        /// Stop the terminal from showing inputs.
        /// </summary>
        public bool PauseDrawing = false;
        /// <summary>
        /// Maximum amount of lines your terminal can reach
        /// </summary>
        public int MaxLines = 150;
        /// <summary>
        /// Saves and clears the terminal when the maximum is reached
        /// </summary>
        public bool SaveAutomaticallyIfMaxReached = false;
        /// <summary>
        /// Specific the name of the folder where the logs of this
        /// terminal will be saved into.
        /// </summary>
        public string SavingFolder = "default";

        /// <summary>
        /// Will replace regular parsing with a special one made
        /// specifically to remove stupid data from the terminal.
        /// </summary>
        public bool UseCANRX = false;
        /// <summary>
        /// Internal class representing default colors for
        /// the various Log functions
        /// </summary>
        public class Colors
        {
            /// <summary>
            /// Log_Error
            /// </summary>
            public static Color Error = Color.Red;
            /// <summary>
            /// Log_Warning
            /// </summary>
            public static Color Warning = Color.Yellow;
            /// <summary>
            /// Log_Comment
            /// </summary>
            public static Color Comment = Color.LightGray;
            /// <summary>
            /// The color your logged headers made with Log_Header will be.
            /// </summary>
            public static Color Header = Color.Magenta;
            /// <summary>
            /// Color used to display userInputs
            /// </summary>
            public static Color userInputs = Color.LightGreen;
            /// <summary>
            /// Color used to display received data from the serial port
            /// </summary>
            public static Color receivedData = Color.Aqua;
        }

        /// <summary>
        /// The richtextbox inside the form which will be used
        /// as a fake terminal.
        /// </summary>
        public RichTextBox Window = new RichTextBox();

        private static Form terminalForm;

        private static SerialPort referencedSerialPort = new SerialPort();
        /// <summary>
        /// Set this to whatever you just sent on the SerialPort you referenced
        /// when creating this terminal. This way, when parsing receptions,
        /// it won't re-display in the terminal what you just sent seconds ago.
        /// </summary>
        public string justSentData = "";

        /// <summary>
        /// If StopDrawingUntil is called, received inputs will never be seen
        /// inside the terminal until the received input is equal to this.
        /// </summary>
        public string comparingWith = "";
        /// <summary>
        /// RX data received delegate
        /// </summary>
        /// <param name="Result">RX string</param>
        public delegate void dlgThread(String Result);
        /// <summary>
        /// The RX delegate
        /// </summary>
        public dlgThread Delegate;
        public dlgThread CANDelegate;
        /// <summary>
        /// Contains all the possible state that your terminal window can have
        /// </summary>
        public enum States
        {
            /// <summary>
            /// The terminal is operational and can be accessed.
            /// </summary>
            Active,
            /// <summary>
            /// The terminal is not active and cant be accessed in any ways.
            /// </summary>
            Disabled,
            /// <summary>
            /// Potential problems with the terminal.
            /// </summary>
            Warning,
            /// <summary>
            /// Something critical hapenned to the terminal.
            /// </summary>
            Error,
            /// <summary>
            /// Terminal window is inactive but can still be accessed.
            /// Normally, in this state, interaction with it leads to
            /// nothing.
            /// </summary>
            Inactive

        }
        /// <summary>
        /// Your terminal's current state as defined by States
        /// </summary>
        public States state;
        #endregion Variables
        #region Constructor
        //#########################################################//
        /// <summary>
        /// This forms constructor. Put your RichTextBox in the
        /// input parameters that you want to use as a terminal
        /// </summary>
        //#########################################################//
        public Terminal(RichTextBox terminalRichTextBox, Form formHostingTerminal, SerialPort forTXOutput)
        {
            BRS.Debug.Comment("Creating terminal handler...");
            terminalForm = formHostingTerminal;
            BRS.Debug.Comment("Referencing RichTextBox from form...");
            Window = terminalRichTextBox;
            Debug.Success();

            BRS.Debug.Comment("Referencing SerialPort...");
            referencedSerialPort = forTXOutput;
            Debug.Success();

            BRS.Debug.Comment("Defaulting terminal state to Inactive...");
            state = States.Inactive;
            Debug.Success();

            BRS.Debug.Comment("Creating Event handlers...");
            try
            {
                terminalRichTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(KeyPressEvent);
                terminalRichTextBox.TextChanged += new System.EventHandler(TextChangedEvent);
                Debug.Success();
            }
            catch
            {
                Debug.Error("Something went wrong during event creation for KeyPress");
            }

            BRS.Debug.Comment("Creating delegate for RX data received event...");
            Delegate = new dlgThread(ParseReceivedData);
            CANDelegate = new dlgThread(ParseCANData);
            Debug.Success();
            Debug.Success("terminal handler was successfully created!");
        }
        //#########################################################//
        /// <summary>
        /// This forms constructor. Put your RichTextBox in the
        /// input parameters that you want to use as a terminal.
        /// This makes it so no serial port is necessary for the
        /// terminal to work.
        /// </summary>
        //#########################################################//
        public Terminal(RichTextBox terminalRichTextBox, Form formHostingTerminal)
        {
            BRS.Debug.Comment("Creating terminal handler...");
            terminalForm = formHostingTerminal;
            BRS.Debug.Comment("Referencing RichTextBox from form...");
            Window = terminalRichTextBox;
            Debug.Success();

            BRS.Debug.Comment("Defaulting terminal state to Inactive...");
            state = States.Inactive;
            Debug.Success();

            BRS.Debug.Comment("Creating Event handlers...");
            try
            {
                terminalRichTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(KeyPressEvent);
                terminalRichTextBox.TextChanged += new System.EventHandler(TextChangedEvent);
                Debug.Success();
            }
            catch
            {
                Debug.Error("Something went wrong during event creation for KeyPress");
            }

            //BRS.Debug.Comment("Creating delegate for RX data received event...");
            //Delegate = new dlgThread(ParseReceivedData);
            //CANDelegate = new dlgThread(ParseCANData);
            Debug.Success();
            Debug.Success("terminal handler was successfully created!");
        }
        #endregion Constructor
        #region Drawing
        //#########################################################//
        /// <summary>
        /// This function will immediately stop this class from
        /// drawing received inputs until the received input
        /// is equal to the specified string.
        /// </summary>
        /// <param name="thisIsReceived"></param>
        //#########################################################//
        public void StopDrawingUntil(string thisIsReceived)
        {
            receivingRX = false;
            comparingWith = thisIsReceived;
            PauseDrawing = true;
        }
        //#########################################################//
        /// <summary>
        /// Clears the terminal or PopUp a message in the event where
        /// the terminal is either in Error mode or Warning mode
        /// </summary>
        //#########################################################//
        public void Clear()
        {
            BRS.Debug.LocalStart(true);
            if (state == States.Error)
            {
                if (BRS.PopUp.UserWarning("Clearing the terminal may cause potential issues to your program... proceed?", "Terminal Error"))
                {
                    Window.Text = "";
                }
            }
            else
            {
                if (state == States.Warning)
                {
                    if (BRS.PopUp.UserWarning("Clearing the terminal may cause potential issues to your program... proceed?", "caution"))
                    {
                        Window.Text = "";
                    }
                }
                else
                {
                    Window.Text = "";
                }
            }
            BRS.Debug.LocalEnd();
        }
        //#########################################################//
        /// <summary>
        /// Log function allowing you to store logs inside the
        /// terminal window along with a special color to put the text
        /// as.
        /// </summary>
        /// <param name="comment"></param>
        /// <param name="colorToUse"></param>
        //#########################################################//
        public void Log_Comment(string comment, Color colorToUse)
        {
            PrintTime();
            Window.SelectionStart = Window.Text.Length;
            Window.SelectionColor = colorToUse;
            Window.SelectedText = comment + "\n";
            Window.SelectionStart = Window.Text.Length;

            CheckLines();
        }
        //#########################################################//
        /// <summary>
        /// Log function allowing you to store logs inside the
        /// terminal window using the predefined Colors value.
        /// </summary>
        /// <param name="comment">Your comment to log into the terminal</param>
        //#########################################################//
        public void Log_Comment(string comment)
        {
            PrintTime();
            Window.SelectionStart = Window.Text.Length;
            Window.SelectionColor = Colors.Comment;
            Window.SelectedText = comment + "\n";
            Window.SelectionStart = Window.Text.Length;

            CheckLines();
        }
        //#########################################################//
        /// <summary>
        /// Function used to log errors inside the Window /
        /// RichTextBox uniformly.
        /// </summary>
        /// <param name="error">String stating what error to log</param>
        //#########################################################//
        public void Log_Error(string error)
        {
            PrintTime();
            Window.SelectionStart = Window.Text.Length;
            Window.SelectionColor = Colors.Error;
            Window.SelectedText = " [!ERROR!]: " + error + "\n";
            Window.SelectionStart = Window.Text.Length;

            CheckLines();
        }
        //#########################################################//
        /// <summary>
        /// Function used to log errors inside the Window /
        /// RichTextBox uniformly.
        /// </summary>
        /// <param name="warning">String stating what warning to log</param>
        //#########################################################//
        public void Log_Warning(string warning)
        {
            PrintTime();
            Window.SelectionStart = Window.Text.Length;
            Window.SelectionColor = Colors.Warning;
            Window.SelectedText = " [-WARNING-]: " + warning + "\n";
            Window.SelectionStart = Window.Text.Length;

            CheckLines();
        }
        //#########################################################//
        /// <summary>
        /// Function used to log a page break or Header inside of
        /// your terminal using the predefined color inside of
        /// Colors
        /// </summary>
        /// <param name="header">String representing your header's name</param>
        //#########################################################//
        public void Log_header(string nameOfHeader)
        {
            Window.SelectionStart = Window.Text.Length;
            Window.SelectionColor = Colors.Header;
            Window.SelectedText = "\n==================================================\n" + nameOfHeader + "\n ==================================================\n";
            Window.SelectionStart = Window.Text.Length;

            CheckLines();
        }
        //#########################################################//
        /// <summary>
        /// This private function automatically prints the time
        /// in hours, without days, without carriage returns at the
        /// end. It automatically puts the time within square brackets
        /// and adds a tabulation after printing it.
        /// </summary>
        //#########################################################//
        private void PrintTime()
        {
            Window.SelectionStart = Window.Text.Length;
            Window.SelectionColor = Colors.Comment;
            Window.SelectedText = "[" + DateTime.Now.ToString("T") + "]\t";
            Window.SelectionStart = Window.Text.Length;
        }
        #endregion Drawing
        #region Events
        //#########################################################//
        /// <summary>
        /// Function executed each time a keypress happens inside of
        /// the referenced RichTextBox (terminal.Window).
        /// Usually, this sends text over SerialPort
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#########################################################//
        private void KeyPressEvent(object sender, KeyPressEventArgs e)
        {
            if(referencedSerialPort.IsOpen)
            {
                if (ShowTX)
                 {
                    Window.SelectionStart = Window.Text.Length;
                    Window.SelectionColor = Colors.userInputs;
                    Window.SelectedText = e.KeyChar.ToString();
                    Window.SelectionStart = Window.Text.Length;
                }

                // Send text
                justSentData = justSentData + e.KeyChar.ToString();
                PauseDrawing = false;
                BRS.ComPort.Port.Write(e.KeyChar.ToString());
            }
            else
            {
                BRS.PopUp.Error("Serial port is closed!","Terminal Error");
            }
        }
        //#########################################################//
        /// <summary>
        /// Function executed when the text inside of the referenced
        /// RichTextBox changes.
        /// </summary>
        //#########################################################//
        private void TextChangedEvent(object sender, EventArgs e)
        {
            if (AutoScroll)
            {
                Window.SelectionStart = Window.Text.Length;
            }
        }
        #endregion Events
        #region DataReception
        //#########################################################//
        /// <summary>
        /// Counts the amount of lines and handles the terminal
        /// accordingly
        /// </summary>
        /// <returns></returns>
        //#########################################################//
        private void CheckLines()
        {
            if (MaxLines > 0)
            {
                if (Window.Lines.Count() > MaxLines)
                {
                    if (SaveAutomaticallyIfMaxReached)
                    {
                        SaveTerminal();
                    }
                    else
                    {
                        /*
                        int lineDifference = Window.Lines.Count() - MaxLines;
                        Window.SelectionStart = 0;
                        Window.SelectionLength = Window.Text.IndexOf("\n",0)+1;
                        Window.SelectedText = "";
                        */
                        Clear();
                    }
                }
            }
        }
        private bool receivingRX = false;
        //#############################################################//
        /// <summary>
        /// Parses the received text from ComPort.Port in the console
        /// rich text box.
        /// Raises the receiving flag so the textchanged event does not
        /// occur.
        /// </summary>
        /// <param name="received">serial buffer</param>
        //#############################################################//
        private void ParseCANData(string received)
        {
            if(received.Contains("[") && received.Contains("]"))
            {
                //-----------------------------------------------------// SYNC 
                if(received.Contains("SYNC"))
                {
                    Log_Comment("[TX]: SYNC", Color.SlateGray);
                    receivingRX = false;
                }
                else
                {
                    if(received.Contains("[-QUIT-]"))
                    {
                        Log_Comment("[- QUITTING -]", Color.Red);
                        receivingRX = false;
                    }
                    else
                    {
                        if(received.Contains("[-RESET-]"))
                        {
                            Log_Comment("[- QUITTING -]", Color.Yellow);
                            receivingRX = false;
                        }
                        else
                        {
                            if (received.Contains("[RX]") || receivingRX)
                            {
                                receivingRX = true;
                                Window.SelectionStart = Window.Text.Length;
                                Window.SelectionColor = Colors.receivedData;
                                Window.SelectedText = received;
                                Window.SelectionStart = Window.Text.Length;
                            }
                        }
                    }
                }
            }
            justSentData = "";
            CheckLines();
        }
        //#############################################################//
        /// <summary>
        /// Parses the received text from ComPort.Port in the console
        /// rich text box.
        /// Raises the receiving flag so the textchanged event does not
        /// occur.
        /// </summary>
        /// <param name="received">serial buffer</param>
        //#############################################################//
        private void ParseReceivedData(string received)
        {
            if (justSentData.Length > 0 && received.Contains(justSentData) && HideAllTX || PauseDrawing)
            {
                received = "";
                justSentData = "";
            }
            justSentData = "";
            Window.SelectionStart = Window.Text.Length;
            Window.SelectionColor = Colors.receivedData;

            /*
            if (received.StartsWith("\r"))
            {
                int LineIndex = ConsoleArea.GetLineFromCharIndex(ConsoleArea.SelectionStart);
                int firstFromLine = ConsoleArea.GetFirstCharIndexFromLine(LineIndex);

                ConsoleArea.SelectionStart = firstFromLine;
                ConsoleArea.SelectionLength = ConsoleArea.Text.Length - firstFromLine;
                ConsoleArea.SelectedText = "";

                received = received.Replace('\r', ' ');
                received = received.Replace('\n', ' ');
            }
            */

            Window.SelectedText = received;
            Window.SelectionStart = Window.Text.Length;
            
            CheckLines();
        }
        //#############################################################//
        /// <summary>
        /// Function called when ComPort serial receives data.
        /// </summary>
        //#############################################################//
        public void DataReceiverHandling()
        {
            //Gather stored data in the buffer
            string result = "";

            try
            {
                result = referencedSerialPort.ReadExisting();

                if (UseCANRX)
                {
                    terminalForm.BeginInvoke(CANDelegate, result);
                    //terminalForm.BeginInvoke(Delegate, result);
                }
                else
                {
                    terminalForm.BeginInvoke(Delegate, result);
                }
            }
            catch
            {   // The form is closed, and the function could not be called
                // Therefor, it is replaced by this empty function.
                BRS.ComPort.DataReceivedAction = EmptyReceivingHandler;
            }
        }
        //#############################################################//
        /// <summary>
        /// Function to replace ComPort.DataReceivedAction so an empty
        /// function is called rather than putting text in an
        /// inexisting console rich text box.
        /// </summary>
        //#############################################################//
        public void EmptyReceivingHandler()
        {

        }
        #endregion DataReception
        #region DataSaving
        //#########################################################//
        /// <summary>
        /// Saves the content of the terminal inside an rtf file.
        /// This will pop up a file dialog
        /// </summary>
        //#########################################################//
        public void SaveTerminal()
        {
            BRS.Debug.Comment("Attempting to save the terminal's content in a file");
            #region Variables
            string path = "";
            bool LogsDirectoryFound = false;
            bool SavingDirectoryFound = false;
            #endregion Variables

            BRS.Debug.Comment("Loading settings from XML file...");
            ///////////////////////////////////////////////////////// - GETTING DIRECTORY PATH
            BRS.Debug.Comment("Navigating directories to the logs emplacement...");
            path = Directory.GetCurrentDirectory();
            BRS.Debug.Success("Directory: " + path);
            //////////////////////////////////////////////////////// - CHECK IF FULL PATH EXISTS
            Directory.CreateDirectory(path + @"\Logs\" + SavingFolder);
            path = path + @"\Logs\" + SavingFolder;
            //////////////////////////////////////////////////////// - FILE DIALOG HANDLING
            Window.Name = DateTime.Now.ToString();
            Window.Name = Window.Name.Replace(':', ';');
            BRS.Debug.Comment(path);
            BRS.Debug.Comment(Window.Name);
            try
            {
                Window.SaveFile(path + @"\" + Window.Name + ".rtf", RichTextBoxStreamType.RichText);
            }
            catch(Exception fuckUp)
            {
                BRS.PopUp.Error(fuckUp.Message,"Saving error");
            }
        }
        #endregion DataSaving
    }
}
