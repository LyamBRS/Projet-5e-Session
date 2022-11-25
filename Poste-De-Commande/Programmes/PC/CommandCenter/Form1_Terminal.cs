using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using BRS;
using BRS.Buttons;

namespace CommandCenter
{
    public partial class Form_MainMenu : Form
    {
        /// <summary>
        /// Reference of this form, for the setting form to use.
        /// </summary>
        public Form_MainMenu FormConsoleRef;
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
                result = BRS.ComPort.Port.ReadExisting();
                FormConsoleRef.BeginInvoke(FormConsoleRef.Delegate, result);
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
        //#############################################################//
        /// <summary>
        /// Parses the received text from ComPort.Port in the console
        /// rich text box.
        /// Raises the receiving flag so the textchanged event does not
        /// occur.
        /// </summary>
        /// <param name="received">serial buffer</param>
        //#############################################################//
        private void RXConsoleText(string received)
        {
            ConsoleArea.SelectionStart = ConsoleArea.Text.Length;
            ConsoleArea.SelectionColor = Color.LightGreen;

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

            ConsoleArea.SelectedText = received;
            ConsoleArea.SelectionStart = ConsoleArea.Text.Length;
            ConsoleArea.SelectionColor = Color.Aqua;
        }
        //#############################################################//
        /// <summary>
        /// Clears the terminal, or warns the user about a potential fuck
        /// up that it might cause.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Button_Terminal_Click(object sender, EventArgs e)
        {

        }
        //#############################################################//
        /// <summary>
        /// Sends Closing parameters to the BeagleBoneBlue
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Button_CloseBeagleBone_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Attempting to quit the beaglebone's running application...");

            if(BRS.ComPort.Port.IsOpen)
            {
                BRS.Debug.Success("Comport is opened.");
                BRS.Debug.Comment("Sending END condition to the BeagleBone's terminal...");

                try
                {
                    byte[] END_0 = BitConverter.GetBytes(0xFF);
                    byte[] END_1 = BitConverter.GetBytes(0xBF);
                    
                    byte[] END = Encoding.UTF8.GetBytes("ÿ");
                    BRS.Debug.Comment(END[0].ToString());
                    BRS.Debug.Comment(END[1].ToString());
                    BRS.ComPort.Port.Write(END_0, 0, 1);
                    BRS.ComPort.Port.Write(END, 0, 2);
                    BRS.ComPort.Port.Write(END, 0, 2);
                    BRS.ComPort.Port.Write("ÿÿ\n"); // 0xFF,0xFF,0xFF,\n
                    Debug.Success();
                    NewUserTextInfo("Closing BBB progam...",2);
                }
                catch
                {
                    Debug.Error("Could not send END to beaglebone.");
                    NewUserTextInfo("Error: Cant send END", 2);
                }
            }
            else
            {
                Debug.Aborted("UART Port is closed!");
            }

            BRS.Debug.Header(false);
        }
        //#############################################################//
        /// <summary>
        /// Adds an error log in red text at the end of the terminal.
        /// </summary>
        /// <param name="error">Text to display in the console</param>
        //#############################################################//
        public void ConsoleArea_LogError(string error)
        {
            ConsoleArea.SelectionStart = ConsoleArea.Text.Length;
            ConsoleArea.SelectionColor = Color.Red;
            ConsoleArea.SelectedText = "\n[!ERROR!]: " + error + "\n";
            ConsoleArea.SelectionStart = ConsoleArea.Text.Length;
        }
    }
}
