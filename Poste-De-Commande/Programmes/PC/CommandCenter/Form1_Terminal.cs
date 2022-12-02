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
        public void Button_Terminal_Click(object sender, EventArgs e)
        {
            BRS.Debug.Header(true);
            BRS.Debug.Comment("Attempting to clear the terminal");
            CommandCenter.terminal.Clear();

            if(CommandCenter.terminal.Window.Text == "")
            {
                Debug.Success("terminal cleared!");
                NewUserTextInfo("Cleared Window", 1);
            }
            else
            {
                Debug.Aborted("terminal cleared!");
                NewUserTextInfo("Canceled clearing", 3);
            }
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

            BRS.Debug.Comment("Checking if Auto connect setting is enabled");
            if(AutoConnect == true)
            {
                BRS.Debug.Comment("Auto connect is enabled, disabling it through click function");
                Button_AutoConnect_Click(sender,e);
                CommandCenter.Buttons.AutoConnection.Update();
                CommandCenter.Buttons.AutoConnection.State = ControlState.Warning;
                Debug.Success();
            }
            else
            {
                Debug.Success("Setting was not enabled");
            }

            if(BRS.ComPort.Port.IsOpen)
            {
                BRS.Debug.Success("Comport is opened.");
                BRS.Debug.Comment("Sending END condition to the BeagleBone's terminal...");

                try
                {
                    MasterProtocol.Send.ToBeagleBone.Quit();
                    MasterProtocol_Stop();
                    CommandCenter.terminal.Log_Comment("Closing BeagleBone Program",Color.HotPink);
                    NewUserTextInfo("Closing BBB",1);
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
