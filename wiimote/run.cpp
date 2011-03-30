#include <windows.h>
#include "run.h"
//#include "mmsystem.h"
#include <mmsystem.h>
#include "wiimote.h"
#include <QtGui/QApplication>
//#include "wmainwindow.h"

void on_state_change (wiimote			  &remote,
                                          state_change_flags  changed,
                                          const wiimote_state &new_state)
        {
        // we use this callback to set report types etc. to respond to key events
        //  (like the wiimote connecting or extensions (dis)connecting).

        // NOTE: don't access the public state from the 'remote' object here, as it will
        //		  be out-of-date (it's only updated via RefreshState() calls, and these
        //		  are reserved for the main application so it can be sure the values
        //		  stay consistent between calls).  Instead query 'new_state' only.

        // the wiimote just connected
        if(changed & CONNECTED)
                {
                // ask the wiimote to report everything (using the 'non-continous updates'
                //  default mode - updates will be frequent anyway due to the acceleration/IR
                //  values changing):

                // note1: you don't need to set a report type for Balance Boards - the
                //		   library does it automatically.

                // note2: for wiimotes, the report mode that includes the extension data
                //		   unfortunately only reports the 'BASIC' IR info (ie. no dot sizes),
                //		   so let's choose the best mode based on the extension status:
                if(new_state.ExtensionType != wiimote::BALANCE_BOARD)
                        {
                        if(new_state.bExtension)
                                remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT); // no IR dots
                        else
                                remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);		//    IR dots
                        }
                }
        // a MotionPlus was detected
        if(changed & MOTIONPLUS_DETECTED)
                {
                // enable it if there isn't a normal extension plugged into it
                // (MotionPlus devices don't report like normal extensions until
                //  enabled - and then, other extensions attached to it will no longer be
                //  reported (so disable the M+ when you want to access them again).
                if(remote.ExtensionType == wiimote_state::NONE) {
                        bool res = remote.EnableMotionPlus();
                        _ASSERT(res);
                        }
                }
        // an extension is connected to the MotionPlus
        else if(changed & MOTIONPLUS_EXTENSION_CONNECTED)
                {
                // We can't read it if the MotionPlus is currently enabled, so disable it:
                if(remote.MotionPlusEnabled())
                        remote.DisableMotionPlus();
                }
        // an extension disconnected from the MotionPlus
        else if(changed & MOTIONPLUS_EXTENSION_DISCONNECTED)
                {
                // enable the MotionPlus data again:
                if(remote.MotionPlusConnected())
                        remote.EnableMotionPlus();
                }
        // another extension was just connected:
        else if(changed & EXTENSION_CONNECTED)
                {
#ifdef USE_BEEPS_AND_DELAYS
                Beep(1000, 200);
#endif
                // switch to a report mode that includes the extension data (we will
                //  loose the IR dot sizes)
                // note: there is no need to set report types for a Balance Board.
                if(!remote.IsBalanceBoard())
                        remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);
                }
        // extension was just disconnected:
        else if(changed & EXTENSION_DISCONNECTED)
                {
#ifdef USE_BEEPS_AND_DELAYS
                Beep(200, 300);
#endif
                // use a non-extension report mode (this gives us back the IR dot sizes)
                remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
                }
        }

Run::Run( QObject *parent) : QThread(parent)
{

}

void Run::run(){
    wiimote remote;

    remote.ChangedCallback		= on_state_change;
    //  notify us only when the wiimote connected sucessfully, or something
    //   related to extensions changes
    remote.CallbackTriggerFlags = (state_change_flags)(CONNECTED |
                                                                                                       EXTENSION_CHANGED |
                                                                                                       MOTIONPLUS_CHANGED);
reconnect:
    COORD pos = { 0, 6 };
    //SetConsoleCursorPosition(console, pos);

    // try to connect the first available wiimote in the system
    //  (available means 'installed, and currently Bluetooth-connected'):
    //WHITE; _tprintf(_T("  Looking for a Wiimote     "));

    static const char* wait_str[] = { (".  "), (".. "), ("...") };
    unsigned count = 0;
    while(!remote.Connect(wiimote::FIRST_AVAILABLE)) {
            //_tprintf(_T("\b\b\b\b%s "), wait_str[count%3]);
            count++;
//#ifdef USE_BEEPS_AND_DELAYS
//                Beep(500, 30); Sleep(1000);
//#endif
            }

    // connected - light all LEDs
    remote.SetLEDs(0x0f);
    //BRIGHT_CYAN; _tprintf(_T("\b\b\b\b... connected!"));
//        if(remote.IsBalanceBoard()) {
//                BRIGHT_WHITE;_tprintf(_T("  (Balance Board)"));
//                }

//#ifdef USE_BEEPS_AND_DELAYS
//        Beep(1000, 300); Sleep(2000);
//#endif

    COORD cursor_pos = { 0, 6 };

#ifdef LOOK_FOR_ADDITIONAL_WIIMOTES
    // try to connect any additional wiimotes (just to show the code)
    //_tprintf(_T("\n\n"));

    wiimote  *extra_motes [7] = { NULL }; // 7 should cover it
    unsigned detected		  = 0;
    while(detected < 7)
            {
            wiimote *next = new wiimote;
            if(!next->Connect(wiimote::FIRST_AVAILABLE))
                    break;
            extra_motes[detected++] = next;

            WHITE		; _tprintf(_T("   also found wiimote "));
            BRIGHT_GREEN; _tprintf(_T("%u"), detected+1);
//                if(next->IsBalanceBoard()) {
//                        WHITE; _tprintf(_T("  (Balance Board)"));
//                        }
//                _tprintf(_T("\n\n"));

//# ifdef USE_BEEPS_AND_DELAYS
//                Beep(1000 + (detected*100), 100);
//                Sleep(500);
//# endif
            }
    //WHITE; _tprintf( ((detected == 7)? _T("     (can't detect any more).") :
                                                                       //_T("    (no more found).")) );
# ifdef USE_BEEPS_AND_DELAYS
    Sleep(2000);
# endif
    // clean up
    for(unsigned index=0; index<detected; index++)
            delete extra_motes[index];

    SetConsoleCursorPosition(console, cursor_pos);
#endif // LOOK_FOR_ADDITIONAL_WIIMOTES

    // print the button event instructions:
  //  BRIGHT_WHITE;
   // _tprintf(_T("\r  -- TRY: B = rumble, A = square, 1 = sine, 2 = daisy, Home = Exit --\n"));

    // (stuff for animations)
    DWORD	 last_rumble_time = timeGetTime(); // for rumble text animation
    DWORD    last_led_time    = timeGetTime(); // for led         animation
    bool	 rumble_text	  = true;
    unsigned lit_led          = 0;

     //display the wiimote state data until 'Home' is pressed:
    while(!remote.Button.Home())// && !GetAsyncKeyState(VK_ESCAPE))
            {
            // IMPORTANT: the wiimote state needs to be refreshed each pass
            while(remote.RefreshState() == NO_CHANGE)
                    Sleep(1); // // don't hog the CPU if nothing changed

            cursor_pos.Y = 8;
            //SetConsoleCursorPosition(console, cursor_pos);

            // did we loose the connection?
            if(remote.ConnectionLost())
                    {
//                        BRIGHT_RED; _tprintf(
//                                _T("   *** connection lost! ***                                          \n")
//                                BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE
//                                BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE BLANK_LINE
//                                BLANK_LINE BLANK_LINE BLANK_LINE);
                    Beep(100, 1000);
                    Sleep(2000);
                    COORD pos = { 0, 6 };
                    //SetConsoleCursorPosition(console, pos);
                   // _tprintf(BLANK_LINE BLANK_LINE BLANK_LINE);
                    goto reconnect;
                    }
        }

}
