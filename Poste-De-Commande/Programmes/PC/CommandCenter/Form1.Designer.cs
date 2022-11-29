
namespace CommandCenter
{
    partial class Form_MainMenu
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_MainMenu));
            this.TabControl_ModeSelector = new System.Windows.Forms.TabControl();
            this.Tab_Operation = new System.Windows.Forms.TabPage();
            this.Tab_Technician = new System.Windows.Forms.TabPage();
            this.Tab_Calibration = new System.Windows.Forms.TabPage();
            this.Tab_Maintenance = new System.Windows.Forms.TabPage();
            this.Tab_Terminal = new System.Windows.Forms.TabPage();
            this.Button_CloseBeagleBone = new System.Windows.Forms.Button();
            this.Button_Terminal = new System.Windows.Forms.Button();
            this.ConsoleArea = new System.Windows.Forms.RichTextBox();
            this.Tab_Settings = new System.Windows.Forms.TabPage();
            this.Button_AutoConnect = new System.Windows.Forms.Button();
            this.Label_AutoConnect = new System.Windows.Forms.Button();
            this.BeagleBone_FilePath = new System.Windows.Forms.TextBox();
            this.Label_FilePath = new System.Windows.Forms.Button();
            this.BeagleBone_FileName = new System.Windows.Forms.TextBox();
            this.Label_FileName = new System.Windows.Forms.Button();
            this.BeagleBone_Password = new System.Windows.Forms.TextBox();
            this.Label_Password = new System.Windows.Forms.Button();
            this.BeagleBone_User = new System.Windows.Forms.TextBox();
            this.Label_User = new System.Windows.Forms.Button();
            this.DropDown_ScaleUnit = new System.Windows.Forms.ComboBox();
            this.Label_ScaleUnit = new System.Windows.Forms.Button();
            this.Button_Scale = new System.Windows.Forms.Button();
            this.SerialPortText = new System.Windows.Forms.Button();
            this.PortBox1 = new System.Windows.Forms.ComboBox();
            this.FlowControlText = new System.Windows.Forms.Button();
            this.FlowControlBox = new System.Windows.Forms.ComboBox();
            this.TXTimeOutBox = new System.Windows.Forms.TextBox();
            this.RXTimeOutBox = new System.Windows.Forms.TextBox();
            this.TXTimeOutText = new System.Windows.Forms.Button();
            this.RXTimeOutText = new System.Windows.Forms.Button();
            this.ParityText = new System.Windows.Forms.Button();
            this.ParityBox = new System.Windows.Forms.ComboBox();
            this.StopBitsText = new System.Windows.Forms.Button();
            this.StopBitBox = new System.Windows.Forms.ComboBox();
            this.DataBitsText = new System.Windows.Forms.Button();
            this.DataBitBox = new System.Windows.Forms.ComboBox();
            this.BaudRateText = new System.Windows.Forms.Button();
            this.BaudRateBox = new System.Windows.Forms.ComboBox();
            this.Button_Link = new System.Windows.Forms.Button();
            this.TabControl_ImageList = new System.Windows.Forms.ImageList(this.components);
            this.UserInfo = new System.Windows.Forms.Label();
            this.ButtonUpdateTimer = new System.Windows.Forms.Timer(this.components);
            this.Periodic100msTimer = new System.Windows.Forms.Timer(this.components);
            this.UpdatePortList = new System.Windows.Forms.Timer(this.components);
            this.Button_Mode = new System.Windows.Forms.Button();
            this.Button_USB = new System.Windows.Forms.Button();
            this.CAN_TIMER = new System.Windows.Forms.Timer(this.components);
            this.TabControl_ModeSelector.SuspendLayout();
            this.Tab_Terminal.SuspendLayout();
            this.Tab_Settings.SuspendLayout();
            this.SuspendLayout();
            // 
            // TabControl_ModeSelector
            // 
            resources.ApplyResources(this.TabControl_ModeSelector, "TabControl_ModeSelector");
            this.TabControl_ModeSelector.Controls.Add(this.Tab_Operation);
            this.TabControl_ModeSelector.Controls.Add(this.Tab_Technician);
            this.TabControl_ModeSelector.Controls.Add(this.Tab_Calibration);
            this.TabControl_ModeSelector.Controls.Add(this.Tab_Maintenance);
            this.TabControl_ModeSelector.Controls.Add(this.Tab_Terminal);
            this.TabControl_ModeSelector.Controls.Add(this.Tab_Settings);
            this.TabControl_ModeSelector.Cursor = System.Windows.Forms.Cursors.Default;
            this.TabControl_ModeSelector.HotTrack = true;
            this.TabControl_ModeSelector.ImageList = this.TabControl_ImageList;
            this.TabControl_ModeSelector.Multiline = true;
            this.TabControl_ModeSelector.Name = "TabControl_ModeSelector";
            this.TabControl_ModeSelector.SelectedIndex = 0;
            this.TabControl_ModeSelector.SizeMode = System.Windows.Forms.TabSizeMode.FillToRight;
            // 
            // Tab_Operation
            // 
            this.Tab_Operation.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.Tab_Operation, "Tab_Operation");
            this.Tab_Operation.Name = "Tab_Operation";
            this.Tab_Operation.UseVisualStyleBackColor = true;
            // 
            // Tab_Technician
            // 
            this.Tab_Technician.BackColor = System.Drawing.Color.Black;
            this.Tab_Technician.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.Tab_Technician, "Tab_Technician");
            this.Tab_Technician.Name = "Tab_Technician";
            this.Tab_Technician.UseVisualStyleBackColor = true;
            // 
            // Tab_Calibration
            // 
            this.Tab_Calibration.BackColor = System.Drawing.Color.Black;
            this.Tab_Calibration.Cursor = System.Windows.Forms.Cursors.Arrow;
            resources.ApplyResources(this.Tab_Calibration, "Tab_Calibration");
            this.Tab_Calibration.Name = "Tab_Calibration";
            this.Tab_Calibration.UseVisualStyleBackColor = true;
            // 
            // Tab_Maintenance
            // 
            this.Tab_Maintenance.BackColor = System.Drawing.Color.Black;
            this.Tab_Maintenance.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.Tab_Maintenance, "Tab_Maintenance");
            this.Tab_Maintenance.Name = "Tab_Maintenance";
            this.Tab_Maintenance.UseVisualStyleBackColor = true;
            // 
            // Tab_Terminal
            // 
            this.Tab_Terminal.BackColor = System.Drawing.Color.Black;
            this.Tab_Terminal.Controls.Add(this.Button_CloseBeagleBone);
            this.Tab_Terminal.Controls.Add(this.Button_Terminal);
            this.Tab_Terminal.Controls.Add(this.ConsoleArea);
            this.Tab_Terminal.Cursor = System.Windows.Forms.Cursors.Arrow;
            resources.ApplyResources(this.Tab_Terminal, "Tab_Terminal");
            this.Tab_Terminal.Name = "Tab_Terminal";
            // 
            // Button_CloseBeagleBone
            // 
            resources.ApplyResources(this.Button_CloseBeagleBone, "Button_CloseBeagleBone");
            this.Button_CloseBeagleBone.AccessibleRole = System.Windows.Forms.AccessibleRole.PushButton;
            this.Button_CloseBeagleBone.BackgroundImage = global::CommandCenter.Properties.Resources.X_Button_Disabled;
            this.Button_CloseBeagleBone.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Button_CloseBeagleBone.DialogResult = System.Windows.Forms.DialogResult.Retry;
            this.Button_CloseBeagleBone.FlatAppearance.BorderSize = 0;
            this.Button_CloseBeagleBone.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.Button_CloseBeagleBone.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Black;
            this.Button_CloseBeagleBone.Name = "Button_CloseBeagleBone";
            this.Button_CloseBeagleBone.UseVisualStyleBackColor = true;
            this.Button_CloseBeagleBone.Click += new System.EventHandler(this.Button_CloseBeagleBone_Click);
            // 
            // Button_Terminal
            // 
            resources.ApplyResources(this.Button_Terminal, "Button_Terminal");
            this.Button_Terminal.AccessibleRole = System.Windows.Forms.AccessibleRole.Indicator;
            this.Button_Terminal.BackgroundImage = global::CommandCenter.Properties.Resources.Terminal_Inactive_Empty;
            this.Button_Terminal.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Button_Terminal.DialogResult = System.Windows.Forms.DialogResult.Retry;
            this.Button_Terminal.FlatAppearance.BorderSize = 0;
            this.Button_Terminal.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.Button_Terminal.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Black;
            this.Button_Terminal.Name = "Button_Terminal";
            this.Button_Terminal.UseVisualStyleBackColor = true;
            this.Button_Terminal.Click += new System.EventHandler(this.Button_Terminal_Click);
            // 
            // ConsoleArea
            // 
            this.ConsoleArea.AcceptsTab = true;
            resources.ApplyResources(this.ConsoleArea, "ConsoleArea");
            this.ConsoleArea.AutoWordSelection = true;
            this.ConsoleArea.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ConsoleArea.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.ConsoleArea.Cursor = System.Windows.Forms.Cursors.Hand;
            this.ConsoleArea.ForeColor = System.Drawing.Color.Aqua;
            this.ConsoleArea.Name = "ConsoleArea";
            this.ConsoleArea.ReadOnly = true;
            this.ConsoleArea.ShortcutsEnabled = false;
            // 
            // Tab_Settings
            // 
            this.Tab_Settings.BackColor = System.Drawing.Color.Black;
            this.Tab_Settings.Controls.Add(this.Button_AutoConnect);
            this.Tab_Settings.Controls.Add(this.Label_AutoConnect);
            this.Tab_Settings.Controls.Add(this.BeagleBone_FilePath);
            this.Tab_Settings.Controls.Add(this.Label_FilePath);
            this.Tab_Settings.Controls.Add(this.BeagleBone_FileName);
            this.Tab_Settings.Controls.Add(this.Label_FileName);
            this.Tab_Settings.Controls.Add(this.BeagleBone_Password);
            this.Tab_Settings.Controls.Add(this.Label_Password);
            this.Tab_Settings.Controls.Add(this.BeagleBone_User);
            this.Tab_Settings.Controls.Add(this.Label_User);
            this.Tab_Settings.Controls.Add(this.DropDown_ScaleUnit);
            this.Tab_Settings.Controls.Add(this.Label_ScaleUnit);
            this.Tab_Settings.Controls.Add(this.Button_Scale);
            this.Tab_Settings.Controls.Add(this.SerialPortText);
            this.Tab_Settings.Controls.Add(this.PortBox1);
            this.Tab_Settings.Controls.Add(this.FlowControlText);
            this.Tab_Settings.Controls.Add(this.FlowControlBox);
            this.Tab_Settings.Controls.Add(this.TXTimeOutBox);
            this.Tab_Settings.Controls.Add(this.RXTimeOutBox);
            this.Tab_Settings.Controls.Add(this.TXTimeOutText);
            this.Tab_Settings.Controls.Add(this.RXTimeOutText);
            this.Tab_Settings.Controls.Add(this.ParityText);
            this.Tab_Settings.Controls.Add(this.ParityBox);
            this.Tab_Settings.Controls.Add(this.StopBitsText);
            this.Tab_Settings.Controls.Add(this.StopBitBox);
            this.Tab_Settings.Controls.Add(this.DataBitsText);
            this.Tab_Settings.Controls.Add(this.DataBitBox);
            this.Tab_Settings.Controls.Add(this.BaudRateText);
            this.Tab_Settings.Controls.Add(this.BaudRateBox);
            this.Tab_Settings.Controls.Add(this.Button_Link);
            this.Tab_Settings.Cursor = System.Windows.Forms.Cursors.Arrow;
            resources.ApplyResources(this.Tab_Settings, "Tab_Settings");
            this.Tab_Settings.ForeColor = System.Drawing.Color.Transparent;
            this.Tab_Settings.Name = "Tab_Settings";
            // 
            // Button_AutoConnect
            // 
            resources.ApplyResources(this.Button_AutoConnect, "Button_AutoConnect");
            this.Button_AutoConnect.AccessibleRole = System.Windows.Forms.AccessibleRole.CheckButton;
            this.Button_AutoConnect.BackgroundImage = global::CommandCenter.Properties.Resources.CheckBox_Disabled_Empty;
            this.Button_AutoConnect.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Button_AutoConnect.DialogResult = System.Windows.Forms.DialogResult.Retry;
            this.Button_AutoConnect.FlatAppearance.BorderSize = 0;
            this.Button_AutoConnect.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.Button_AutoConnect.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Black;
            this.Button_AutoConnect.Name = "Button_AutoConnect";
            this.Button_AutoConnect.UseVisualStyleBackColor = true;
            this.Button_AutoConnect.Click += new System.EventHandler(this.Button_AutoConnect_Click);
            // 
            // Label_AutoConnect
            // 
            resources.ApplyResources(this.Label_AutoConnect, "Label_AutoConnect");
            this.Label_AutoConnect.FlatAppearance.BorderSize = 0;
            this.Label_AutoConnect.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.Label_AutoConnect.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.Label_AutoConnect.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.Label_AutoConnect.Name = "Label_AutoConnect";
            this.Label_AutoConnect.UseVisualStyleBackColor = true;
            // 
            // BeagleBone_FilePath
            // 
            resources.ApplyResources(this.BeagleBone_FilePath, "BeagleBone_FilePath");
            this.BeagleBone_FilePath.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.BeagleBone_FilePath.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.BeagleBone_FilePath.Name = "BeagleBone_FilePath";
            this.BeagleBone_FilePath.TextChanged += new System.EventHandler(this.BeagleBone_FilePath_TextChanged);
            // 
            // Label_FilePath
            // 
            resources.ApplyResources(this.Label_FilePath, "Label_FilePath");
            this.Label_FilePath.FlatAppearance.BorderSize = 0;
            this.Label_FilePath.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.Label_FilePath.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.Label_FilePath.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.Label_FilePath.Name = "Label_FilePath";
            this.Label_FilePath.UseVisualStyleBackColor = true;
            // 
            // BeagleBone_FileName
            // 
            resources.ApplyResources(this.BeagleBone_FileName, "BeagleBone_FileName");
            this.BeagleBone_FileName.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.BeagleBone_FileName.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.BeagleBone_FileName.Name = "BeagleBone_FileName";
            this.BeagleBone_FileName.TextChanged += new System.EventHandler(this.BeagleBone_FileName_TextChanged);
            // 
            // Label_FileName
            // 
            resources.ApplyResources(this.Label_FileName, "Label_FileName");
            this.Label_FileName.FlatAppearance.BorderSize = 0;
            this.Label_FileName.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.Label_FileName.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.Label_FileName.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.Label_FileName.Name = "Label_FileName";
            this.Label_FileName.UseVisualStyleBackColor = true;
            // 
            // BeagleBone_Password
            // 
            resources.ApplyResources(this.BeagleBone_Password, "BeagleBone_Password");
            this.BeagleBone_Password.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.BeagleBone_Password.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.BeagleBone_Password.Name = "BeagleBone_Password";
            this.BeagleBone_Password.TextChanged += new System.EventHandler(this.BeagleBone_Password_TextChanged);
            // 
            // Label_Password
            // 
            resources.ApplyResources(this.Label_Password, "Label_Password");
            this.Label_Password.FlatAppearance.BorderSize = 0;
            this.Label_Password.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.Label_Password.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.Label_Password.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.Label_Password.Name = "Label_Password";
            this.Label_Password.UseVisualStyleBackColor = true;
            // 
            // BeagleBone_User
            // 
            resources.ApplyResources(this.BeagleBone_User, "BeagleBone_User");
            this.BeagleBone_User.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.BeagleBone_User.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.BeagleBone_User.Name = "BeagleBone_User";
            this.BeagleBone_User.TextChanged += new System.EventHandler(this.BeagleBone_User_TextChanged);
            // 
            // Label_User
            // 
            resources.ApplyResources(this.Label_User, "Label_User");
            this.Label_User.FlatAppearance.BorderSize = 0;
            this.Label_User.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.Label_User.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.Label_User.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.Label_User.Name = "Label_User";
            this.Label_User.UseVisualStyleBackColor = true;
            // 
            // DropDown_ScaleUnit
            // 
            resources.ApplyResources(this.DropDown_ScaleUnit, "DropDown_ScaleUnit");
            this.DropDown_ScaleUnit.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.DropDown_ScaleUnit.Cursor = System.Windows.Forms.Cursors.Hand;
            this.DropDown_ScaleUnit.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.DropDown_ScaleUnit.DropDownWidth = 100;
            this.DropDown_ScaleUnit.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.DropDown_ScaleUnit.Items.AddRange(new object[] {
            resources.GetString("DropDown_ScaleUnit.Items"),
            resources.GetString("DropDown_ScaleUnit.Items1")});
            this.DropDown_ScaleUnit.Name = "DropDown_ScaleUnit";
            this.DropDown_ScaleUnit.SelectedIndexChanged += new System.EventHandler(this.DropDown_ScaleUnit_SelectedIndexChanged);
            // 
            // Label_ScaleUnit
            // 
            resources.ApplyResources(this.Label_ScaleUnit, "Label_ScaleUnit");
            this.Label_ScaleUnit.FlatAppearance.BorderSize = 0;
            this.Label_ScaleUnit.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.Label_ScaleUnit.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.Label_ScaleUnit.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.Label_ScaleUnit.Name = "Label_ScaleUnit";
            this.Label_ScaleUnit.UseVisualStyleBackColor = true;
            // 
            // Button_Scale
            // 
            resources.ApplyResources(this.Button_Scale, "Button_Scale");
            this.Button_Scale.AccessibleRole = System.Windows.Forms.AccessibleRole.Indicator;
            this.Button_Scale.BackgroundImage = global::CommandCenter.Properties.Resources.Balance_Disabled_Empty;
            this.Button_Scale.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Button_Scale.DialogResult = System.Windows.Forms.DialogResult.Retry;
            this.Button_Scale.FlatAppearance.BorderSize = 0;
            this.Button_Scale.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.Button_Scale.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Black;
            this.Button_Scale.Name = "Button_Scale";
            this.Button_Scale.UseVisualStyleBackColor = true;
            // 
            // SerialPortText
            // 
            this.SerialPortText.FlatAppearance.BorderSize = 0;
            this.SerialPortText.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.SerialPortText.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.SerialPortText, "SerialPortText");
            this.SerialPortText.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.SerialPortText.Name = "SerialPortText";
            this.SerialPortText.UseVisualStyleBackColor = true;
            // 
            // PortBox1
            // 
            this.PortBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.PortBox1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.PortBox1.DropDownHeight = 1000;
            this.PortBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.PortBox1.DropDownWidth = 1000;
            resources.ApplyResources(this.PortBox1, "PortBox1");
            this.PortBox1.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.PortBox1.FormattingEnabled = true;
            this.PortBox1.Name = "PortBox1";
            this.PortBox1.Sorted = true;
            this.PortBox1.SelectedIndexChanged += new System.EventHandler(this.PortBox1_SelectedIndexChanged);
            // 
            // FlowControlText
            // 
            this.FlowControlText.FlatAppearance.BorderSize = 0;
            this.FlowControlText.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.FlowControlText.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.FlowControlText, "FlowControlText");
            this.FlowControlText.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.FlowControlText.Name = "FlowControlText";
            this.FlowControlText.UseVisualStyleBackColor = true;
            // 
            // FlowControlBox
            // 
            this.FlowControlBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.FlowControlBox.Cursor = System.Windows.Forms.Cursors.Hand;
            this.FlowControlBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            resources.ApplyResources(this.FlowControlBox, "FlowControlBox");
            this.FlowControlBox.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.FlowControlBox.FormattingEnabled = true;
            this.FlowControlBox.Name = "FlowControlBox";
            this.FlowControlBox.SelectedIndexChanged += new System.EventHandler(this.FlowControlBox_SelectedIndexChanged);
            // 
            // TXTimeOutBox
            // 
            this.TXTimeOutBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            resources.ApplyResources(this.TXTimeOutBox, "TXTimeOutBox");
            this.TXTimeOutBox.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.TXTimeOutBox.Name = "TXTimeOutBox";
            this.TXTimeOutBox.TextChanged += new System.EventHandler(this.TXTimeOutBox_TextChanged);
            // 
            // RXTimeOutBox
            // 
            this.RXTimeOutBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            resources.ApplyResources(this.RXTimeOutBox, "RXTimeOutBox");
            this.RXTimeOutBox.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.RXTimeOutBox.Name = "RXTimeOutBox";
            this.RXTimeOutBox.TextChanged += new System.EventHandler(this.RXTimeOutBox_TextChanged);
            // 
            // TXTimeOutText
            // 
            this.TXTimeOutText.FlatAppearance.BorderSize = 0;
            this.TXTimeOutText.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.TXTimeOutText.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.TXTimeOutText, "TXTimeOutText");
            this.TXTimeOutText.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.TXTimeOutText.Name = "TXTimeOutText";
            this.TXTimeOutText.UseVisualStyleBackColor = true;
            // 
            // RXTimeOutText
            // 
            this.RXTimeOutText.FlatAppearance.BorderSize = 0;
            this.RXTimeOutText.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.RXTimeOutText.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.RXTimeOutText, "RXTimeOutText");
            this.RXTimeOutText.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.RXTimeOutText.Name = "RXTimeOutText";
            this.RXTimeOutText.UseVisualStyleBackColor = true;
            // 
            // ParityText
            // 
            this.ParityText.FlatAppearance.BorderSize = 0;
            this.ParityText.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.ParityText.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.ParityText, "ParityText");
            this.ParityText.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.ParityText.Name = "ParityText";
            this.ParityText.UseVisualStyleBackColor = true;
            // 
            // ParityBox
            // 
            this.ParityBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ParityBox.Cursor = System.Windows.Forms.Cursors.Hand;
            this.ParityBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            resources.ApplyResources(this.ParityBox, "ParityBox");
            this.ParityBox.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.ParityBox.FormattingEnabled = true;
            this.ParityBox.Name = "ParityBox";
            this.ParityBox.SelectedIndexChanged += new System.EventHandler(this.ParityBox_SelectedIndexChanged);
            // 
            // StopBitsText
            // 
            this.StopBitsText.FlatAppearance.BorderSize = 0;
            this.StopBitsText.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.StopBitsText.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.StopBitsText, "StopBitsText");
            this.StopBitsText.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.StopBitsText.Name = "StopBitsText";
            this.StopBitsText.UseVisualStyleBackColor = true;
            // 
            // StopBitBox
            // 
            this.StopBitBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.StopBitBox.Cursor = System.Windows.Forms.Cursors.Hand;
            this.StopBitBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            resources.ApplyResources(this.StopBitBox, "StopBitBox");
            this.StopBitBox.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.StopBitBox.FormattingEnabled = true;
            this.StopBitBox.Name = "StopBitBox";
            this.StopBitBox.SelectedIndexChanged += new System.EventHandler(this.StopBitBox_SelectedIndexChanged);
            // 
            // DataBitsText
            // 
            this.DataBitsText.FlatAppearance.BorderSize = 0;
            this.DataBitsText.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.DataBitsText.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.DataBitsText, "DataBitsText");
            this.DataBitsText.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.DataBitsText.Name = "DataBitsText";
            this.DataBitsText.UseVisualStyleBackColor = true;
            // 
            // DataBitBox
            // 
            this.DataBitBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.DataBitBox.Cursor = System.Windows.Forms.Cursors.Hand;
            this.DataBitBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            resources.ApplyResources(this.DataBitBox, "DataBitBox");
            this.DataBitBox.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.DataBitBox.FormattingEnabled = true;
            this.DataBitBox.Items.AddRange(new object[] {
            resources.GetString("DataBitBox.Items"),
            resources.GetString("DataBitBox.Items1")});
            this.DataBitBox.Name = "DataBitBox";
            this.DataBitBox.SelectedIndexChanged += new System.EventHandler(this.DataBitBox_SelectedIndexChanged);
            // 
            // BaudRateText
            // 
            this.BaudRateText.FlatAppearance.BorderSize = 0;
            this.BaudRateText.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.BaudRateText.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.BaudRateText, "BaudRateText");
            this.BaudRateText.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.BaudRateText.Name = "BaudRateText";
            this.BaudRateText.UseVisualStyleBackColor = true;
            // 
            // BaudRateBox
            // 
            this.BaudRateBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.BaudRateBox.Cursor = System.Windows.Forms.Cursors.Hand;
            this.BaudRateBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            resources.ApplyResources(this.BaudRateBox, "BaudRateBox");
            this.BaudRateBox.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.BaudRateBox.Items.AddRange(new object[] {
            resources.GetString("BaudRateBox.Items"),
            resources.GetString("BaudRateBox.Items1"),
            resources.GetString("BaudRateBox.Items2"),
            resources.GetString("BaudRateBox.Items3"),
            resources.GetString("BaudRateBox.Items4"),
            resources.GetString("BaudRateBox.Items5"),
            resources.GetString("BaudRateBox.Items6"),
            resources.GetString("BaudRateBox.Items7"),
            resources.GetString("BaudRateBox.Items8"),
            resources.GetString("BaudRateBox.Items9"),
            resources.GetString("BaudRateBox.Items10"),
            resources.GetString("BaudRateBox.Items11"),
            resources.GetString("BaudRateBox.Items12"),
            resources.GetString("BaudRateBox.Items13")});
            this.BaudRateBox.Name = "BaudRateBox";
            this.BaudRateBox.SelectedIndexChanged += new System.EventHandler(this.BaudRateBox_SelectedIndexChanged);
            // 
            // Button_Link
            // 
            resources.ApplyResources(this.Button_Link, "Button_Link");
            this.Button_Link.AccessibleRole = System.Windows.Forms.AccessibleRole.Indicator;
            this.Button_Link.BackgroundImage = global::CommandCenter.Properties.Resources.Link_Inactive_Empty;
            this.Button_Link.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Button_Link.DialogResult = System.Windows.Forms.DialogResult.Retry;
            this.Button_Link.FlatAppearance.BorderSize = 0;
            this.Button_Link.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.Button_Link.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Black;
            this.Button_Link.Name = "Button_Link";
            this.Button_Link.UseVisualStyleBackColor = true;
            this.Button_Link.Click += new System.EventHandler(this.Button_Link_Click);
            // 
            // TabControl_ImageList
            // 
            this.TabControl_ImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("TabControl_ImageList.ImageStream")));
            this.TabControl_ImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.TabControl_ImageList.Images.SetKeyName(0, "Calibration_Available_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(1, "Calibration_Available_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(2, "Calibration_Disabled_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(3, "Calibration_Disabled_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(4, "Calibration_Error_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(5, "Calibration_Error_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(6, "Calibration_Warning_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(7, "Calibration_Warning_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(8, "Maintenance_Available_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(9, "Maintenance_Available_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(10, "Maintenance_Disabled_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(11, "Maintenance_Disabled_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(12, "Maintenance_Error_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(13, "Maintenance_Error_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(14, "Maintenance_Warning_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(15, "Maintenance_Warning_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(16, "Operation_Available_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(17, "Operation_Available_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(18, "Operation_Disabled_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(19, "Operation_Disabled_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(20, "Operation_Error_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(21, "Operation_Error_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(22, "Operation_Warning_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(23, "Operation_Warning_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(24, "Tech_Available_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(25, "Tech_Available_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(26, "Tech_Disabled_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(27, "Tech_Disabled_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(28, "Tech_Error_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(29, "Tech_Error_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(30, "Tech_Warning_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(31, "Tech_Warning_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(32, "Settings_Available_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(33, "Settings_Available_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(34, "Settings_Disabled_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(35, "Settings_Disabled_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(36, "Settings_Error_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(37, "Settings_Error_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(38, "Settings_Warning_Empty.png");
            this.TabControl_ImageList.Images.SetKeyName(39, "Settings_Warning_Filled.png");
            this.TabControl_ImageList.Images.SetKeyName(40, "Terminal_Disabled_Filled.png");
            // 
            // UserInfo
            // 
            resources.ApplyResources(this.UserInfo, "UserInfo");
            this.UserInfo.AccessibleRole = System.Windows.Forms.AccessibleRole.Indicator;
            this.UserInfo.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.UserInfo.ForeColor = System.Drawing.SystemColors.ControlLight;
            this.UserInfo.Name = "UserInfo";
            // 
            // ButtonUpdateTimer
            // 
            this.ButtonUpdateTimer.Enabled = true;
            this.ButtonUpdateTimer.Interval = 10;
            this.ButtonUpdateTimer.Tick += new System.EventHandler(this.ButtonUpdateTimer_Tick);
            // 
            // Periodic100msTimer
            // 
            this.Periodic100msTimer.Enabled = true;
            // 
            // UpdatePortList
            // 
            this.UpdatePortList.Enabled = true;
            this.UpdatePortList.Interval = 500;
            this.UpdatePortList.Tick += new System.EventHandler(this.UpdatePortList_Tick);
            // 
            // Button_Mode
            // 
            resources.ApplyResources(this.Button_Mode, "Button_Mode");
            this.Button_Mode.AccessibleRole = System.Windows.Forms.AccessibleRole.PushButton;
            this.Button_Mode.BackgroundImage = global::CommandCenter.Properties.Resources.PowerButton_Disabled_Empty;
            this.Button_Mode.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Button_Mode.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Button_Mode.FlatAppearance.BorderSize = 0;
            this.Button_Mode.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.Button_Mode.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Black;
            this.Button_Mode.Name = "Button_Mode";
            this.Button_Mode.UseVisualStyleBackColor = true;
            // 
            // Button_USB
            // 
            resources.ApplyResources(this.Button_USB, "Button_USB");
            this.Button_USB.AccessibleRole = System.Windows.Forms.AccessibleRole.Indicator;
            this.Button_USB.BackgroundImage = global::CommandCenter.Properties.Resources.USB_Disabled_Empty;
            this.Button_USB.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Button_USB.DialogResult = System.Windows.Forms.DialogResult.Retry;
            this.Button_USB.FlatAppearance.BorderSize = 0;
            this.Button_USB.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Black;
            this.Button_USB.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Black;
            this.Button_USB.Name = "Button_USB";
            this.Button_USB.UseVisualStyleBackColor = true;
            // 
            // CAN_TIMER
            // 
            this.CAN_TIMER.Interval = 20;
            this.CAN_TIMER.Tick += new System.EventHandler(this.CAN_TIMER_Tick);
            // 
            // Form_MainMenu
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.WindowText;
            this.Controls.Add(this.Button_Mode);
            this.Controls.Add(this.UserInfo);
            this.Controls.Add(this.Button_USB);
            this.Controls.Add(this.TabControl_ModeSelector);
            this.ForeColor = System.Drawing.SystemColors.AppWorkspace;
            this.Name = "Form_MainMenu";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
            this.ResizeBegin += new System.EventHandler(this.Form_MainMenu_ResizeBegin);
            this.ResizeEnd += new System.EventHandler(this.Form_MainMenu_ResizeEnd);
            this.Resize += new System.EventHandler(this.Form_MainMenu_Resize);
            this.TabControl_ModeSelector.ResumeLayout(false);
            this.Tab_Terminal.ResumeLayout(false);
            this.Tab_Settings.ResumeLayout(false);
            this.Tab_Settings.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.TabControl TabControl_ModeSelector;
        private System.Windows.Forms.TabPage Tab_Operation;
        private System.Windows.Forms.TabPage Tab_Technician;
        private System.Windows.Forms.ImageList TabControl_ImageList;
        private System.Windows.Forms.TabPage Tab_Calibration;
        private System.Windows.Forms.TabPage Tab_Maintenance;
        private System.Windows.Forms.TabPage Tab_Settings;
        private System.Windows.Forms.TabPage Tab_Terminal;
        private System.Windows.Forms.Button Button_USB;
        private System.Windows.Forms.Label UserInfo;
        private System.Windows.Forms.Timer ButtonUpdateTimer;
        private System.Windows.Forms.Button Button_Mode;
        private System.Windows.Forms.Button Button_Link;
        private System.Windows.Forms.Button SerialPortText;
        private System.Windows.Forms.ComboBox PortBox1;
        private System.Windows.Forms.Button FlowControlText;
        private System.Windows.Forms.ComboBox FlowControlBox;
        private System.Windows.Forms.TextBox TXTimeOutBox;
        private System.Windows.Forms.TextBox RXTimeOutBox;
        private System.Windows.Forms.Button TXTimeOutText;
        private System.Windows.Forms.Button RXTimeOutText;
        private System.Windows.Forms.Button ParityText;
        private System.Windows.Forms.ComboBox ParityBox;
        private System.Windows.Forms.Button StopBitsText;
        private System.Windows.Forms.ComboBox StopBitBox;
        private System.Windows.Forms.Button DataBitsText;
        private System.Windows.Forms.ComboBox DataBitBox;
        private System.Windows.Forms.Button BaudRateText;
        private System.Windows.Forms.ComboBox BaudRateBox;
        private System.Windows.Forms.RichTextBox ConsoleArea;
        private System.Windows.Forms.Button Button_Terminal;
        private System.Windows.Forms.Timer Periodic100msTimer;
        public System.Windows.Forms.Timer UpdatePortList;
        private System.Windows.Forms.Button Button_Scale;
        private System.Windows.Forms.ComboBox DropDown_ScaleUnit;
        private System.Windows.Forms.Button Label_ScaleUnit;
        private System.Windows.Forms.TextBox BeagleBone_User;
        private System.Windows.Forms.Button Label_User;
        private System.Windows.Forms.TextBox BeagleBone_Password;
        private System.Windows.Forms.Button Label_Password;
        private System.Windows.Forms.TextBox BeagleBone_FileName;
        private System.Windows.Forms.Button Label_FileName;
        private System.Windows.Forms.TextBox BeagleBone_FilePath;
        private System.Windows.Forms.Button Label_FilePath;
        private System.Windows.Forms.Button Label_AutoConnect;
        private System.Windows.Forms.Button Button_AutoConnect;
        private System.Windows.Forms.Button Button_CloseBeagleBone;
        private System.Windows.Forms.Timer CAN_TIMER;
    }
}

