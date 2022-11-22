using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using BRS;
using System.Diagnostics.Eventing.Reader;
using System.IO.Ports;

namespace BRS
{
    //#########################################################//
    /// <summary>
    /// Class storing functions such as Lerp,
    /// BounceIN, BounceOUT ect.
    /// </summary>
    //#########################################################//
    public class Smoothing
    {
        public static float Lerp(float a, float b, float t)
        {
            return a + (b - a) * t;
        }
    }

    //#########################################################//
    /// <summary>
    /// Builder class used to specify background images to use
    /// when a mouse event occurs in a control.
    /// </summary>
    //#########################################################//
    public class EventsBitmaps
    {
        /// <summary>
        /// <see cref="Bitmap"/>  used while the cursor is actively 
        /// pressing on the control.
        /// </summary>
        public Bitmap Pressing;

        /// <summary>
        /// <see cref="Bitmap"/>  used when the cursor is actively 
        /// hovering above the control.
        /// </summary>
        public Bitmap Hovering;

        /// <summary>
        /// <see cref="Bitmap"/> used by default when no mouse 
        /// events occurs.
        /// </summary>
        public Bitmap Default;

        /// ------------------------------------------- <summary>
        /// Set all this event/state <see cref="Bitmap"/>
        /// to an universal <see cref="Bitmap"/> <br /> <br /> 
        /// (<see cref="Default"/>, 
        /// <see cref="Hovering"/>, 
        /// <see cref="Pressing"/>)
        /// <param name="Global"></param>
        /// </summary> ----------------------------------------//
        public void SetAll(Bitmap Global)
        {
            Pressing = Global;
            Hovering = Global;
            Default = Global;
        }
        /// ------------------------------------------- <summary>
        /// Set all this state's event <see cref="Bitmap"/>
        /// to an already defined <see cref="EventsBitmaps"/>
        /// <param name="events"></param>
        /// </summary> ----------------------------------------//
        public void SetAll(EventsBitmaps events)
        {
            Pressing = events.Pressing;
            Hovering = events.Hovering;
            Default = events.Default;
        }
        /// ------------------------------------------- <summary>
        /// Set all individual events to specifics <see cref="Bitmap"/>.
        /// <param name="normal"></param>
        /// <param name="hovering"></param>
        /// <param name="pressing"></param>
        /// </summary> ----------------------------------------//
        public void SetAll(Bitmap normal, Bitmap hovering, Bitmap pressing)
        {
            Pressing = pressing;
            Hovering = hovering;
            Default = normal;
        }

        //#####################################################//
        /// <summary>
        /// Default constructor. Set all event 
        /// <see cref="Bitmap"/> to the
        /// same <see cref="Bitmap"/>.
        /// </summary>
        /// <param name="universalImage"></param>
        //#####################################################// 
        public EventsBitmaps(Bitmap universalImage)
        {
            Pressing = universalImage;
            Hovering = universalImage;
            Default = universalImage;
        }
        //#####################################################//
        /// <summary>
        /// Constructor used to define each <see cref="Bitmap"/>
        /// individually
        /// </summary>
        /// <param name="normal"></param>
        /// <param name="hovering"></param>
        /// <param name="pressing"></param>
        //#####################################################// 
        public EventsBitmaps(Bitmap normal, Bitmap hovering, Bitmap pressing)
        {
            Pressing = pressing;
            Hovering = hovering;
            Default = normal;
        }
        //#####################################################//
        /// <summary>
        /// Constructor used to copy an already existing 
        /// <see cref="EventsBitmaps"/>
        /// into a new <see cref="EventsBitmaps"/>.
        /// </summary>
        /// <param name="bitmaps"></param>
        //#####################################################// 
        public EventsBitmaps(EventsBitmaps bitmaps)
        {
            Pressing = bitmaps.Pressing;
            Hovering = bitmaps.Hovering;
            Default = bitmaps.Default;
        }
    }

    //#########################################################//
    /// <summary>
    /// Builder class used to specify a control's background colors
    /// during a specific mouse event.
    /// </summary>
    //#########################################################//
    public class EventsColors
    {
        /// ------------------------------------------- <summary>
        /// <see cref="Color"/> used when the control is being 
        /// actively pressed on.
        /// </summary>------------------------------------------//
        public Color Pressing = Color.Empty;
        /// ------------------------------------------- <summary>
        /// <see cref="Color"/> used when the cursor is hovering 
        /// above the control. Is overwritten by 
        /// <paramref name="Pressing"/>
        /// </summary>------------------------------------------//
        public Color Hovering = Color.Empty;
        /// ------------------------------------------- <summary>
        /// <see cref="Color"/> used when the control is being 
        /// actively pressed on.
        /// </summary>------------------------------------------//
        public Color Default = Color.Empty;


        /// ------------------------------------------- <summary>
        /// Set all this event/state <see cref="Color"/>
        /// to a universal <see cref="Color"/> 
        /// (<see cref="Default"/>, 
        /// <see cref="Hovering"/>, 
        /// <see cref="Pressing"/>)
        /// <param name="Global"></param>
        /// </summary> ----------------------------------------//
        public void SetAll(Color Global)
        {
            Pressing = Global;
            Hovering = Global;
            Default = Global;
        }
        /// ------------------------------------------- <summary>
        /// Set all this event's <see cref="Color"/> to an already 
        /// existing instance of <see cref="EventsColors"/>
        /// <param name="events"></param>
        /// </summary> ----------------------------------------//
        public void SetAll(EventsColors events)
        {
            Pressing = events.Pressing;
            Hovering = events.Hovering;
            Default = events.Default;
        }
        /// ------------------------------------------- <summary>
        /// Set all individual events <see cref="Color"/>
        /// <param name="normal"></param>
        /// <param name="hovering"></param>
        /// <param name="pressing"></param>
        /// </summary> ----------------------------------------//
        public void SetAll(Color normal, Color hovering, Color pressing)
        {
            Pressing = pressing;
            Hovering = hovering;
            Default = normal;
        }

        //#####################################################//
        /// <summary>
        /// Default constructor. <br /> 
        /// Set all events <see cref="Color"/>  to the
        /// same <see cref="Color"/>.
        /// </summary>
        /// <param name="universalColor"></param>
        //#####################################################// 
        public EventsColors(Color universalColor)
        {
            Pressing = universalColor;
            Hovering = universalColor;
            Default = universalColor;
        }
        //#####################################################//
        /// <summary>
        /// Constructor used to define each events <see cref="Color"/> individually
        /// </summary>
        /// <param name="normal"></param>
        /// <param name="hovering"></param>
        /// <param name="pressing"></param>
        //#####################################################// 
        public EventsColors(Color normal, Color hovering, Color pressing)
        {
            Pressing = pressing;
            Hovering = hovering;
            Default = normal;
        }
        //#####################################################//
        /// <summary>
        /// Constructor used to copy existing <see cref="EventsColors"/>
        /// into a new <see cref="EventsColors"/>.
        /// </summary>
        /// <param name="colors"></param>
        //#####################################################// 
        public EventsColors(EventsColors colors)
        {
            Pressing = colors.Pressing;
            Hovering = colors.Hovering;
            Default = colors.Default;
        }
    }

    //#########################################################//
    /// <summary>
    /// Enum containing possible states of a control
    /// </summary>
    //#########################################################//
    public enum ControlState
    {
        /// <summary>
        /// Control.Enabled is set to <see langword="false"/>.
        /// </summary>
        Disabled,

        /// <summary>
        /// Control is active/ON/Checked ect
        /// </summary>
        Active,

        /// <summary>
        /// Control is inactive/Off/Unchecked ect
        /// </summary>
        Inactive,

        /// <summary>
        /// Control is indicating an error/ critical problem
        /// </summary>
        Error,

        /// <summary>
        /// Control is indicating a warning
        /// </summary>
        Warning,

        /// <summary>
        /// Control is loading/downloading/uploading
        /// </summary>
        Loading
    }

    //=============================================================//
    // Holds buttons classes
    //=============================================================//
    namespace Buttons
    {
        //#########################################################//
        /// <summary>
        /// Builder class used to specify background images used
        /// on a button in specific conditions, such as: <br /> while
        /// pressing, while hovering, when disabled, when ON, when
        /// OFF... ect. 
        /// <br /><br />
        /// You can build individual states by using 
        /// <see cref="EventsBitmaps"/>
        /// </summary>
        //#########################################################//
        public class StatesBitmaps
        {
            //#####################################################//
            /// ------------------------------------------- <summary>
            /// <see cref="EventsBitmaps"/> used when a button 
            /// state is == <see cref="ControlState.disabled"/>
            /// </summary> ----------------------------------------//
            public EventsBitmaps Disabled;
            /// ------------------------------------------- <summary>
            /// <see cref="EventsBitmaps"/> used when a button 
            /// state is == <see cref="ControlState.active"/>
            /// </summary> ----------------------------------------//
            public EventsBitmaps Active;
            /// ------------------------------------------- <summary>
            /// <see cref="EventsBitmaps"/> used when a button 
            /// state is == <see cref="ControlState.error"/>
            /// </summary> ----------------------------------------//
            public EventsBitmaps Error;
            /// ------------------------------------------- <summary>
            /// <see cref="EventsBitmaps"/> used when a button 
            /// state is == <see cref="ControlState.warning"/>
            /// </summary> ----------------------------------------//
            public EventsBitmaps Warning;
            /// ------------------------------------------- <summary>
            /// <see cref="EventsBitmaps"/> used when a button 
            /// state is == <see cref="ControlState.loading"/>
            /// </summary> ----------------------------------------//
            public EventsBitmaps Loading;
            /// ------------------------------------------- <summary>
            /// <see cref="EventsBitmaps"/> used when a button 
            /// state is == <see cref="ControlState.inactive"/>
            /// </summary> ----------------------------------------//
            public EventsBitmaps Inactive;
            //#####################################################//

            //#####################################################//
            /// <summary>
            /// Default constructor. <br /> Sets all button's 
            /// <see cref="EventsBitmaps"/> to 1 single universal
            /// <see cref="Bitmap"/>
            /// </summary>
            /// <param name="Global"></param>
            //#####################################################//
            public StatesBitmaps(Bitmap Global)
            {
                Disabled = new EventsBitmaps(Global);
                Active = new EventsBitmaps(Global);
                Error = new EventsBitmaps(Global);
                Warning = new EventsBitmaps(Global);
                Loading = new EventsBitmaps(Global);
                Inactive = new EventsBitmaps(Global);
            }
            //#####################################################//
            /// <summary>
            /// Copy already existing <see cref="EventsBitmaps"/> of
            /// an existing instance of
            /// <see cref="StatesBitmaps"/>
            /// into a new <see cref="StatesBitmaps"/>.
            /// </summary>
            /// <param name="statesBitmaps"></param>
            //#####################################################//
            public StatesBitmaps(StatesBitmaps statesBitmaps)
            {
                Disabled = new EventsBitmaps(statesBitmaps.Disabled);
                Active = new EventsBitmaps(statesBitmaps.Active);
                Error = new EventsBitmaps(statesBitmaps.Error);
                Warning = new EventsBitmaps(statesBitmaps.Warning);
                Loading = new EventsBitmaps(statesBitmaps.Loading);
                Inactive = new EventsBitmaps(statesBitmaps.Inactive);
            }
            //#####################################################//
            /// <summary>
            /// Copy already existing <see cref="EventsBitmaps"/> 
            /// and use it for all States bitmaps.
            /// </summary>
            /// <param name="Global"></param>
            //#####################################################//
            public StatesBitmaps(EventsBitmaps Global)
            {
                Disabled = new EventsBitmaps(Global);
                Active = new EventsBitmaps(Global);
                Error = new EventsBitmaps(Global);
                Warning = new EventsBitmaps(Global);
                Loading = new EventsBitmaps(Global);
                Inactive = new EventsBitmaps(Global);
            }
            //#####################################################//
            /// <summary>
            /// Individually define each button state's <see cref="EventsBitmaps"/> 
            /// </summary>
            /// <param name="disabled">When the button's Enabled is false</param>
            /// <param name="active">When the button state is active</param>
            /// <param name="error">When the button state is error</param>
            /// <param name="warning">When the button state is warning</param>
            /// <param name="loading">When the button state is loading</param>
            /// <param name="inactive">When the button state is inactive</param>
            //#####################################################//
            public StatesBitmaps(EventsBitmaps disabled, EventsBitmaps active, EventsBitmaps error, EventsBitmaps warning, EventsBitmaps loading, EventsBitmaps inactive)
            {
                Disabled = new EventsBitmaps(disabled);
                Active = new EventsBitmaps(active);
                Error = new EventsBitmaps(error);
                Warning = new EventsBitmaps(warning);
                Loading = new EventsBitmaps(loading);
                Inactive = new EventsBitmaps(inactive);
            }

        }

        //#########################################################//
        /// <summary>
        /// Builder class used to specify background images used
        /// on a button in specific conditions, such as: <br /> while
        /// pressing, while hovering, when disabled, when ON, when
        /// OFF... ect. 
        /// <br /><br />
        /// You can build individual states by using 
        /// <see cref="EventsColors"/>
        /// </summary>
        //#########################################################//
        public class StatesColors
        {
            //#####################################################//
            /// ------------------------------------------- <summary>
            /// <see cref="EventsColors"/> used when a button 
            /// state is == <see cref="ControlState.disabled"/>
            /// </summary> ----------------------------------------//
            public EventsColors Disabled;
            /// ------------------------------------------- <summary>
            /// <see cref="EventsColors"/> used when a button 
            /// state is == <see cref="ControlState.active"/>
            /// </summary> ----------------------------------------//
            public EventsColors Active;
            /// ------------------------------------------- <summary>
            /// <see cref="EventsColors"/> used when a button 
            /// state is == <see cref="ControlState.error"/>
            /// </summary> ----------------------------------------//
            public EventsColors Error;
            /// ------------------------------------------- <summary>
            /// <see cref="EventsColors"/> used when a button 
            /// state is == <see cref="ControlState.warning"/>
            /// </summary> ----------------------------------------//
            public EventsColors Warning;
            /// ------------------------------------------- <summary>
            /// <see cref="EventsColors"/> used when a button 
            /// state is == <see cref="ControlState.loading"/>
            /// </summary> ----------------------------------------//
            public EventsColors Loading;
            /// ------------------------------------------- <summary>
            /// <see cref="EventsColors"/> used when a button 
            /// state is == <see cref="ControlState.inactive"/>
            /// </summary> ----------------------------------------//
            public EventsColors Inactive;
            //#####################################################//

            //#####################################################//
            /// <summary>
            /// Default constructor. <br /> Sets all button's 
            /// <see cref="EventsColors"/> to 1 single universal
            /// <see cref="Color"/>
            /// </summary>
            /// <param name="Global"></param>
            //#####################################################//
            public StatesColors(Color Global)
            {
                Disabled = new EventsColors(Global);
                Active = new EventsColors(Global);
                Error = new EventsColors(Global);
                Warning = new EventsColors(Global);
                Loading = new EventsColors(Global);
                Inactive = new EventsColors(Global);
            }
            //#####################################################//
            /// <summary>
            /// Copy already existing <see cref="EventsColors"/> of
            /// an existing instance of
            /// <see cref="StatesColors"/>
            /// into a new <see cref="StatesColors"/>.
            /// </summary>
            /// <param name="statesColors"></param>
            //#####################################################//
            public StatesColors(StatesColors statesColors)
            {
                Disabled = new EventsColors(statesColors.Disabled);
                Active = new EventsColors(statesColors.Active);
                Error = new EventsColors(statesColors.Error);
                Warning = new EventsColors(statesColors.Warning);
                Loading = new EventsColors(statesColors.Loading);
                Inactive = new EventsColors(statesColors.Inactive);
            }
            //#####################################################//
            /// <summary>
            /// Copy already existing <see cref="EventsColors"/> 
            /// and use it for all States bitmaps.
            /// </summary>
            /// <param name="Global"></param>
            //#####################################################//
            public StatesColors(EventsColors Global)
            {
                Disabled = new EventsColors(Global);
                Active = new EventsColors(Global);
                Error = new EventsColors(Global);
                Warning = new EventsColors(Global);
                Loading = new EventsColors(Global);
                Inactive = new EventsColors(Global);
            }
            //#####################################################//
            /// <summary>
            /// Individually define each button state's <see cref="EventsColors"/> 
            /// </summary>
            /// <param name="disabled">When the button's Enabled is false</param>
            /// <param name="active">When the button state is active</param>
            /// <param name="error">When the button state is error</param>
            /// <param name="warning">When the button state is warning</param>
            /// <param name="loading">When the button state is loading</param>
            /// <param name="inactive">When the button state is inactive</param>
            //#####################################################//
            public StatesColors(EventsColors disabled, EventsColors active, EventsColors error, EventsColors warning, EventsColors loading, EventsColors inactive)
            {
                Disabled = new EventsColors(disabled);
                Active = new EventsColors(active);
                Error = new EventsColors(error);
                Warning = new EventsColors(warning);
                Loading = new EventsColors(loading);
                Inactive = new EventsColors(inactive);
            }

        }

        //#########################################################//
        /// <summary>
        /// Class used to transform a standard, pre-generated button
        /// into a BRS animated button. Allowing size changes, easy
        /// background colour animations, and Bitmaps changes to be
        /// applied automatically or manually.
        /// This also creates mouse event handlers for these animations
        /// for you.
        /// </summary>
        //#########################################################//
        public partial class GenericButton
        {
            /// <summary>
            /// Enables or disable the button.
            /// While disabled, no actions are done with the button.
            /// IconDisabled will be shown until re-enabled
            /// </summary>
            private bool enabled = true;

            /// <summary>
            /// Zoom in on the button when the cursor enters the button
            /// while it is enabled
            /// </summary>
            public bool ChangeSizeWhenMouseHover = false;
            /// <summary>
            /// By how much the button's size should change when the mouse is hovering above.
            /// 0.5 = half, 1 = Same, 2 = 2 times... ect
            /// </summary>
            public float SizeMultiplier_MouseHover = 1.2f;

            /// <summary>
            /// Change the button's size while the cursor is pressed on the button
            /// until it is released.
            /// </summary>
            public bool ChangeSizeWhenClicked = false;

            /// <summary>
            ///  Target size for the button when clicking on it.
            ///  0.5 = Half, 1 = Same, 2 = 2 times... ect
            /// </summary>
            public float SizeMultiplier_Clicking = 0.9f;

            /// <summary>
            /// Third parameter of a lerp function. You'll need to tune it according to your timer's intervals
            /// 1 = Instant.
            /// </summary>
            public float LerpingSpeed = 0.25f;

            /// <summary>
            /// Decides if your button should animate using Lerps.
            /// IF TRUE, CALL BUTTON IN A PERIODIC TIMER
            /// </summary>
            public bool Animated = false;

            /// <summary>
            /// List of <see cref="Bitmap"/>s stored as <see cref="EventsBitmaps"/>
            /// <br />
            /// <br /> 
            /// Defines background <see cref="Bitmap"/> depending on <see cref="State"/>
            /// </summary>
            public StatesBitmaps Bitmaps;

            /// <summary>
            /// List of <see cref="Color"/>s stored as <see cref="EventsColors"/>
            /// <br />
            /// <br /> 
            /// Defines background <see cref="Color"/> depending on <see cref="State"/>
            /// </summary>
            public StatesColors Colors;

            /// <summary>
            /// referenced Form's generic button
            /// </summary>
            public Button FormButton;

            /// <summary>
            /// The size of whichever container is hosting your dynamic button. Can be the form.
            /// This is solely necessary for anchor points.
            /// If you are using animated functions, please update this whenever your control
            /// is resized.
            /// </summary>
            public Size ButtonContainer;

            //#############################################################//
            private float currentR = 0;
            private float currentG = 0;
            private float currentB = 0;

            private Color wantedColor = Color.Empty;
            private Bitmap wantedImage;


            private EventsColors currentColors;
            private EventsBitmaps currentBitmaps;

            private EventsBitmaps oldBitmaps;

            /// <summary>
            /// Defines the state of the button. This will select appropriated image and colors to use.
            /// </summary>
            private ControlState currentState = ControlState.Inactive;

            private float currentSizeMultiplier = 1;
            private float wantedSizeMultiplier = 1;

            private int OriginalWidth;
            private int OriginalHeight;
            private int OriginalX;
            private int OriginalY;

            private bool Pressed = false;
            private bool Hovering = false;

            //#############################################################//
            /// <summary>
            /// Constructor transforming a standard form's generic button
            /// into a BRS animated button allowing event colors and bitmaps
            /// to be automatically changed depending on button state.
            /// </summary>
            /// <param name="referencedButton"></param>
            /// <param name="referencedColors"></param>
            /// <param name="bitmaps"></param>
            //#############################################################//
            public GenericButton(Button referencedButton, StatesColors colors, StatesBitmaps bitmaps)
            {
                BRS.Debug.LocalStart(true);
                BRS.Debug.Comment("Creating GenericButton. Gathering referenced button's information");

                FormButton = referencedButton;
                Bitmaps = bitmaps;
                Colors = colors;

                OriginalWidth = FormButton.Size.Width;
                OriginalHeight = FormButton.Size.Height;
                OriginalX = FormButton.Location.X;
                OriginalY = FormButton.Location.Y;

                FormButton.BackgroundImageLayout = ImageLayout.Stretch;

                currentColors = Colors.Inactive;
                currentBitmaps = Bitmaps.Inactive;
                oldBitmaps = Bitmaps.Inactive;

                FormButton.MouseEnter += (sender, args) => { Button_MouseEnter(); };
                FormButton.MouseLeave += (sender, args) => { Button_MouseLeave(); };
                FormButton.MouseDown += (sender, args) => { Button_MouseDown(); };
                FormButton.MouseUp += (sender, args) => { Button_MouseUp(); };

                Debug.Success("");
                BRS.Debug.LocalEnd();
            }
            //#############################################################//
            /// <summary>
            /// The state of the button. Defines what bitmap and colours will
            /// be used when interacting with it.
            /// </summary>
            //#############################################################//
            public ControlState State
            {
                get 
                {
                    return currentState; 
                }
                set 
                {
                    currentState = value;
                    switch (currentState)
                    {
                        //-------------------------------------------// Button was disabled
                        case(ControlState.Disabled):
                            currentColors = Colors.Disabled;
                            currentBitmaps = Bitmaps.Disabled;
                            FormButton.Enabled = false;
                            break;

                        //-------------------------------------------// Button was set to Active
                        case (ControlState.Active):
                            currentColors = Colors.Active;
                            currentBitmaps = Bitmaps.Active;
                            FormButton.Enabled = true;
                            break;

                        //-------------------------------------------// Button was set to Inactive
                        case (ControlState.Inactive):
                            currentColors = Colors.Inactive;
                            currentBitmaps = Bitmaps.Inactive;
                            FormButton.Enabled = true;
                            break;

                        //-------------------------------------------// Button was set to Error
                        case (ControlState.Error):
                            currentColors = Colors.Error;
                            currentBitmaps = Bitmaps.Error;
                            FormButton.Enabled = true;
                            break;

                        //-------------------------------------------// Button was set to Warning
                        case (ControlState.Warning):
                            currentColors = Colors.Warning;
                            currentBitmaps = Bitmaps.Warning;
                            FormButton.Enabled = true;
                            break;

                        //-------------------------------------------// Button was set to Loading
                        case (ControlState.Loading):
                            currentColors = Colors.Loading;
                            currentBitmaps = Bitmaps.Loading;
                            FormButton.Enabled = true;
                            break;

                        //-------------------------------------------// Button was set to Warning
                        default:
                            currentColors = Colors.Disabled;
                            currentBitmaps = Bitmaps.Disabled;
                            currentState = ControlState.Disabled;
                            FormButton.Enabled = false;
                            Debug.Error("Potential error occured when trying to set the state of this GenericButton");
                            break;
                    }
                }
            }
            //#############################################################//
            /// <summary>
            /// A function called when using Button.Animate = true.
            /// Place this function in a timer executed by default each 10ms.
            /// </summary>
            //#############################################################//
            public void Update()
            {
                //BRS.Debug.Comment(FormButton.BackColor.ToString());

                if (Animated)
                {
                    if (!Pressed)
                    {
                        // Lerp colour to wanted colour
                        int R = wantedColor.R;
                        int G = wantedColor.G;
                        int B = wantedColor.B;

                        float wR = (float)R;
                        float wG = (float)G;
                        float wB = (float)B;

                        currentR = Smoothing.Lerp(currentR, wR, LerpingSpeed);
                        currentG = Smoothing.Lerp(currentG, wG, LerpingSpeed);
                        currentB = Smoothing.Lerp(currentB, wB, LerpingSpeed);

                        R = (int)currentR;
                        G = (int)currentG;
                        B = (int)currentB;

                        FormButton.BackColor = Color.FromArgb(R, G, B);
                    }
                    //////////////////////////////////////////////////////
                    currentSizeMultiplier = Smoothing.Lerp(currentSizeMultiplier, wantedSizeMultiplier, LerpingSpeed);

                    float originalHeight = (float)OriginalHeight;
                    float originalWidth = (float)OriginalWidth;
                    float originalPositionX = (float)OriginalX;
                    float originalPositionY = (float)OriginalY;

                    float newHeight = originalHeight * currentSizeMultiplier;
                    float newWidth = originalWidth * currentSizeMultiplier;

                    float heightDifference = originalHeight - newHeight;
                    float widthDifference = originalWidth - newWidth;

                    float newX = originalPositionX + widthDifference / 2;
                    float newY = originalPositionY + heightDifference / 2;

                    FormButton.Location = new Point((int)newX, (int)newY);
                    FormButton.Size = new Size((int)newWidth, (int)newHeight);

                }
                else //////////////////////////////////////////////////////
                {

                    FormButton.BackColor = wantedColor;
                }

                if(oldBitmaps != currentBitmaps)
                {
                    oldBitmaps = currentBitmaps;
                    if (Pressed || Hovering)
                    {
                        if(Pressed)
                        {
                            FormButton.BackgroundImage = currentBitmaps.Pressing;
                        }
                        else
                        {
                            FormButton.BackgroundImage = currentBitmaps.Hovering;
                        }
                    }
                    else
                    {
                        FormButton.BackgroundImage = currentBitmaps.Default;
                    }
                }
            }
            //#############################################################//
            //#############################################################//
            public void UpdateOriginalPositions(Point ButtonPos)
            {
                //reset to no size changes before updating original position to avoid small changes
                currentSizeMultiplier = 1;
                Update();

                OriginalX = ButtonPos.X;
                OriginalY = ButtonPos.Y;
            }
            //#############################################################//
            //#############################################################//
            private void Button_MouseEnter()
            {
                if (enabled)
                {
                    wantedColor = currentColors.Hovering;
                    FormButton.BackgroundImage = currentBitmaps.Hovering;

                    currentR = (float)wantedColor.R;
                    currentG = (float)wantedColor.G;
                    currentB = (float)wantedColor.B;

                    Pressed = false;
                    Hovering = true;
                    // size
                    wantedSizeMultiplier = SizeMultiplier_MouseHover;
                    Update();
                }
            }
            //#############################################################//
            //#############################################################//
            private void Button_MouseLeave()
            {
                Pressed = false;
                Hovering = false;
                wantedColor = currentColors.Default;
                FormButton.BackgroundImage = currentBitmaps.Default;

                // size
                wantedSizeMultiplier = 1;
            }
            //#############################################################//
            //#############################################################//
            private void Button_MouseDown()
            {
                if (FormButton.Enabled)
                {
                    Pressed = true;
                    Hovering = false;

                    wantedColor = currentColors.Pressing;
                    FormButton.BackgroundImage = currentBitmaps.Pressing;

                    // size
                    wantedSizeMultiplier = SizeMultiplier_Clicking;
                    currentSizeMultiplier = wantedSizeMultiplier;

                    currentR = (float)wantedColor.R;
                    currentG = (float)wantedColor.G;
                    currentB = (float)wantedColor.B;

                    FormButton.BackColor = wantedColor;
                    Update();
                }
            }
            //#############################################################//
            //#############################################################//
            private void Button_MouseUp()
            {
                if (FormButton.Enabled)
                {
                    Pressed = false;
                    Hovering = true;
                    wantedColor = currentColors.Hovering;
                    FormButton.BackgroundImage = currentBitmaps.Hovering;

                    // size
                    wantedSizeMultiplier = SizeMultiplier_MouseHover;
                    Pressed = false;
                    Update();
                }
            }
        }
    }
}
