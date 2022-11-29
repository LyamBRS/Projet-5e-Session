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
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Attempting to clear the terminal");
            CommandCenter.terminal.Clear();
            BRS.Debug.Header(false);
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
                    MasterProtocol.Send.ToBeagleBone.Quit();
                    MasterProtocol_Stop();
                    CommandCenter.terminal.Log_Comment("Closing BeagleBone Program",Color.HotPink);
                }
                catch
                {
                    Debug.Error("Could not send END to beaglebone.");
                    NewUserTextInfo("CAN'T CLOSE PROGRAM", 2);
                    CommandCenter.terminal.Log_Error("Could not close the BeagleBone program");
                }
            }
            else
            {
                Debug.Aborted("UART Port is closed!");
                CommandCenter.terminal.Log_Error("UART is closed, you cannot close BeagleBone program");
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
        //#############################################################//
        //#############################################################//
    }
}
