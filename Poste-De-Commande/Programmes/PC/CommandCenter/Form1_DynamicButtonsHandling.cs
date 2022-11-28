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
        /// Tick timer function executed each 10 milliseconds to update
        /// BRS Dynamic buttons.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void ButtonUpdateTimer_Tick(object sender, EventArgs e)
        {
            CommandCenter.Buttons.USB.Update();
            CommandCenter.Buttons.Mode.Update();
            CommandCenter.Buttons.Link.Update();
            CommandCenter.Buttons.Terminal.Update();
            CommandCenter.Buttons.AutoConnection.Update();
            CommandCenter.Buttons.CloseBeagle.Update();
            #region UserInfo
            int R = UserInfo.ForeColor.R;
            int G = UserInfo.ForeColor.G;
            int B = UserInfo.ForeColor.B;

            //Defines up to which point the color must fade out.
            // Always return to gray in a linear fashion.
            int minimum = 50;
            if (R > minimum) { R -= 2; }
            if (G > minimum) { G -= 2; }
            if (B > minimum) { B -= 2; }
            if (R < minimum) { R += 2; }
            if (G < minimum) { G += 2; }
            if (B < minimum) { B += 2; }

            UserInfo.ForeColor = Color.FromArgb(R, G, B);
            //ConsoleArea.Focus();
            #endregion UserInfo
        }
        //#############################################################//
        /// <summary>
        /// Resize function updating the size of referenced containers
        /// for BRS Dynamic buttons.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //#############################################################//
        private void Form_MainMenu_Resize(object sender, EventArgs e)
        {
            ButtonUpdateTimer.Enabled = false;
            if (HasStartedResize == 0)
            {
                ButtonUpdateTimer.Enabled = false;
                CommandCenter.Buttons.Mode.UpdateOriginalPositions(Button_Mode.Location);
                CommandCenter.Buttons.USB.UpdateOriginalPositions(Button_USB.Location);
                CommandCenter.Buttons.Link.UpdateOriginalPositions(Button_Link.Location);
                CommandCenter.Buttons.Terminal.UpdateOriginalPositions(Button_Terminal.Location);
                CommandCenter.Buttons.AutoConnection.UpdateOriginalPositions(Button_AutoConnect.Location);
                CommandCenter.Buttons.CloseBeagle.UpdateOriginalPositions(Button_CloseBeagleBone.Location);
                ButtonUpdateTimer.Enabled = true;
            }
        }
        private void Form_MainMenu_ResizeBegin(object sender, EventArgs e)
        {
            ButtonUpdateTimer.Enabled = false;
            CommandCenter.Buttons.Mode.UpdateOriginalPositions(Button_Mode.Location);
            CommandCenter.Buttons.USB.UpdateOriginalPositions(Button_USB.Location);
            CommandCenter.Buttons.Link.UpdateOriginalPositions(Button_Link.Location);
            CommandCenter.Buttons.Terminal.UpdateOriginalPositions(Button_Terminal.Location);
            CommandCenter.Buttons.AutoConnection.UpdateOriginalPositions(Button_AutoConnect.Location);
            CommandCenter.Buttons.CloseBeagle.UpdateOriginalPositions(Button_CloseBeagleBone.Location);
            HasStartedResize = 1;
        }
        private void Form_MainMenu_ResizeEnd(object sender, EventArgs e)
        {
            CommandCenter.Buttons.Mode.UpdateOriginalPositions(Button_Mode.Location);
            CommandCenter.Buttons.USB.UpdateOriginalPositions(Button_USB.Location);
            CommandCenter.Buttons.Link.UpdateOriginalPositions(Button_Link.Location);
            CommandCenter.Buttons.Terminal.UpdateOriginalPositions(Button_Terminal.Location);
            CommandCenter.Buttons.AutoConnection.UpdateOriginalPositions(Button_AutoConnect.Location);
            CommandCenter.Buttons.CloseBeagle.UpdateOriginalPositions(Button_CloseBeagleBone.Location);
            ButtonUpdateTimer.Enabled = true;
            HasStartedResize = 0;
        }
    }
}
