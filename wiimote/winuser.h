#ifndef _WINUSER_
#define _WINUSER_

#if !defined(_ENABLE_AUTODEPEND)
  #pragma read_only_file;
#endif

#include <tvout.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Macro to specify user functions */
#define WINUSERAPI  DECLSPEC_IMPORT

/* Handle data type used with DeferWindowPos(), etc. */
typedef HANDLE  HDWP;

/* Handle to a device notification */
#if (WINVER >= 0x0500)
typedef PVOID       HDEVNOTIFY;
typedef HDEVNOTIFY  *PHDEVNOTIFY;
#endif

/* Handle to a power notification */
#if (_WIN32_WINNT >= 0x0502)
typedef PVOID           HPOWERNOTIFY;
typedef HPOWERNOTIFY    *PHPOWERNOTIFY;
#endif

/* Raw input handle */
#if (_WIN32_WINNT >= 0x0501)
DECLARE_HANDLE( HRAWINPUT );
#endif

/* Macro to define a resource identifier */
#define MAKEINTRESOURCEA( x )   ((LPSTR)(ULONG_PTR)(WORD)(x))
#define MAKEINTRESOURCEW( x )   ((LPWSTR)(ULONG_PTR)(WORD)(x))
#ifdef UNICODE
    #define MAKEINTRESOURCE MAKEINTRESOURCEW
#else
    #define MAKEINTRESOURCE MAKEINTRESOURCEA
#endif

/* Macros to manipulate the parameters to WM_APPCOMMAND */
#if (_WIN32_WINNT >= 0x0500)
    #define GET_APPCOMMAND_LPARAM( x )  ((short)(HIWORD( x ) & ~FAPPCOMMAND_MASK))
    #define GET_DEVICE_LPARAM( x )      ((WORD)(HIWORD( x ) & FAPPCOMMAND_MASK))
    #define GET_MOUSEORKEY_LPARAM( x )  GET_DEVICE_LPARAM( x )
    #define GET_FLAGS_LPARAM( x )       LOWORD( x )
    #define GET_KEYSTATE_LPARAM( x )    GET_FLAGS_LPARAM( x )
#endif

/* Macros to convert between the POINT and POINTS structures */
#define POINTSTOPOINT( p1, p2 ) \
    { \
        (p1).x = (LONG)(SHORT)LOWORD( *(LONG *)&p2 ); \
        (p2).y = (LONG)(SHORT)HIWORD( *(LONG *)&p2 ); \
    }
#define POINTTOPOINTS( p )  MAKELONG( (short)((p).x), (short)((p).y) )

/* Macros to construct message parameters and results */
#define MAKEWPARAM( p1, p2 )    ((WPARAM)(DWORD)MAKELONG( p1, p2 ))
#define MAKELPARAM( p1, p2 )    ((LPARAM)(DWORD)MAKELONG( p1, p2 ))
#define MAKELRESULT( p1, p2 )   ((LRESULT)(DWORD)MAKELONG( p1, p2 ))

/* Macro to manipulate the parameters to WM_MOUSEWHEEL */
#if (_WIN32_WINNT >= 0x0400)
    #define GET_WHEEL_DELTA_WPARAM( x ) ((short)HIWORD( x ))
#endif

/* Macros to manipulate the parameters to the mouse message and WM_NCHITTEST */
#if (_WIN32_WINNT >= 0x0500)
    #define GET_KEYSTATE_WPARAM( x )    LOWORD( x )
    #define GET_NCHITTEST_WPARAM( x )   ((short)LOWORD( x ))
    #define GET_XBUTTON_WPARAM( x )     HIWORD( x )
#endif

/* Macro to manipulate the parameters to WM_INPUT */
#if (_WIN32_WINNT >= 0x0501)
    #define GET_RAWINPUT_CODE_WPARAM( x )   ((x) & 0xFF)
#endif

/* Macro to manipulate the parameters to WM_INPUT_DEVICE_CHANGE */
#if (_WIN32_WINNT >= 0x0501)
    #define GET_DEVICE_CHANGE_LPARAM( x )   LOWORD( x )
#endif

/* Resource types */
#define RT_CURSOR           MAKEINTRESOURCE( 1 )
#define RT_BITMAP           MAKEINTRESOURCE( 2 )
#define RT_ICON             MAKEINTRESOURCE( 3 )
#define RT_MENU             MAKEINTRESOURCE( 4 )
#define RT_DIALOG           MAKEINTRESOURCE( 5 )
#define RT_STRING           MAKEINTRESOURCE( 6 )
#define RT_FONTDIR          MAKEINTRESOURCE( 7 )
#define RT_FONT             MAKEINTRESOURCE( 8 )
#define RT_ACCELERATOR      MAKEINTRESOURCE( 9 )
#define RT_RCDATA           MAKEINTRESOURCE( 10 )
#define RT_MESSAGETABLE     MAKEINTRESOURCE( 11 )
#define RT_GROUP_CURSOR     MAKEINTRESOURCE( 12 )
#define RT_GROUP_ICON       MAKEINTRESOURCE( 14 )
#define RT_VERSION          MAKEINTRESOURCE( 16 )
#define RT_DLGINCLUDE       MAKEINTRESOURCE( 17 )
#if (WINVER >= 0x0400)
    #define RT_PLUGPLAY     MAKEINTRESOURCE( 19 )
    #define RT_VXD          MAKEINTRESOURCE( 20 )
    #define RT_ANICURSOR    MAKEINTRESOURCE( 21 )
    #define RT_ANIICON      MAKEINTRESOURCE( 22 )
#endif
#define RT_HTML             MAKEINTRESOURCE( 23 )
#define RT_MANIFEST         MAKEINTRESOURCE( 24 )

/* Manifest resource identifiers */
#define CREATEPROCESS_MANIFEST_RESOURCE_ID                  MAKEINTRESOURCE( 1 )
#define ISOLATIONAWARE_MANIFEST_RESOURCE_ID                 MAKEINTRESOURCE( 2 )
#define ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID  MAKEINTRESOURCE( 3 )
#define MINIMUM_RESERVED_MANIFEST_RESOURCE_ID               MAKEINTRESOURCE( 1 )
#define MAXIMUM_RESERVED_MANIFEST_RESOURCE_ID               MAKEINTRESOURCE( 16 )

/* Constant used with SPI_SETDESKWALLPAPER */
#define SETWALLPAPER_DEFAULT    ((LPWSTR)-1)

/* Scroll bar identifiers */
#define SB_HORZ 0
#define SB_VERT 1
#define SB_CTL  2
#define SB_BOTH 3

/* Scroll bar commands */
#define SB_LINEUP           0
#define SB_LINELEFT         0
#define SB_LINEDOWN         1
#define SB_LINERIGHT        1
#define SB_PAGEUP           2
#define SB_PAGELEFT         2
#define SB_PAGEDOWN         3
#define SB_PAGERIGHT        3
#define SB_THUMBPOSITION    4
#define SB_THUMBTRACK       5
#define SB_TOP              6
#define SB_LEFT             6
#define SB_BOTTOM           7
#define SB_RIGHT            7
#define SB_ENDSCROLL        8

/* ShowWindow() commands */
#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_NORMAL           1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_MAXIMIZE         3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9
#define SW_SHOWDEFAULT      10
#define SW_FORCEMINIMIZE    11
#define SW_MAX              11

/* Old names for ShowWindow() commands */
#define HIDE_WINDOW         0
#define SHOW_OPENWINDOW     1
#define SHOW_ICONWINDOW     2
#define SHOW_FULLSCREEN     3
#define SHOW_OPENNOACTIVATE 4

/* WM_SHOWWINDOW identifiers */
#define SW_PARENTCLOSING    1
#define SW_OTHERZOOM        2
#define SW_PARENTOPENING    3
#define SW_OTHERUNZOOM      4

/* AnimateWindow() commands */
#if (WINVER >= 0x0500)
    #define AW_HOR_POSITIVE 0x00000001L
    #define AW_HOR_NEGATIVE 0x00000002L
    #define AW_VER_POSITIVE 0x00000004L
    #define AW_VER_NEGATIVE 0x00000008L
    #define AW_CENTER       0x00000010L
    #define AW_HIDE         0x00010000L
    #define AW_ACTIVATE     0x00020000L
    #define AW_SLIDE        0x00040000L
    #define AW_BLEND        0x00080000L
#endif

/* Keyboard message flags */
#define KF_EXTENDED 0x0100
#define KF_DLGMODE  0x0800
#define KF_MENUMODE 0x1000
#define KF_ALTDOWN  0x2000
#define KF_REPEAT   0x4000
#define KF_UP       0x8000

/* Virtual key codes */
#define VK_LBUTTON                  0x01
#define VK_RBUTTON                  0x02
#define VK_CANCEL                   0x03
#define VK_MBUTTON                  0x04
#if (_WIN32_WINNT >= 0x0500)
    #define VK_XBUTTON1             0x05
    #define VK_XBUTTON2             0x06
#endif
#define VK_BACK                     0x08
#define VK_TAB                      0x09
#define VK_CLEAR                    0x0C
#define VK_RETURN                   0x0D
#define VK_SHIFT                    0x10
#define VK_CONTROL                  0x11
#define VK_MENU                     0x12
#define VK_PAUSE                    0x13
#define VK_CAPITAL                  0x14
#define VK_KANA                     0x15
#define VK_HANGEUL                  0x15
#define VK_HANGUL                   0x15
#define VK_JUNJA                    0x17
#define VK_FINAL                    0x18
#define VK_HANJA                    0x19
#define VK_KANJI                    0x19
#define VK_ESCAPE                   0x1B
#define VK_CONVERT                  0x1C
#define VK_NONCONVERT               0x1D
#define VK_ACCEPT                   0x1E
#define VK_MODECHANGE               0x1F
#define VK_SPACE                    0x20
#define VK_PRIOR                    0x21
#define VK_NEXT                     0x22
#define VK_END                      0x23
#define VK_HOME                     0x24
#define VK_LEFT                     0x25
#define VK_UP                       0x26
#define VK_RIGHT                    0x27
#define VK_DOWN                     0x28
#define VK_SELECT                   0x29
#define VK_PRINT                    0x2A
#define VK_EXECUTE                  0x2B
#define VK_SNAPSHOT                 0x2C
#define VK_INSERT                   0x2D
#define VK_DELETE                   0x2E
#define VK_HELP                     0x2F
#define VK_LWIN                     0x5B
#define VK_RWIN                     0x5C
#define VK_APPS                     0x5D
#define VK_SLEEP                    0x5F
#define VK_NUMPAD0                  0x60
#define VK_NUMPAD1                  0x61
#define VK_NUMPAD2                  0x62
#define VK_NUMPAD3                  0x63
#define VK_NUMPAD4                  0x64
#define VK_NUMPAD5                  0x65
#define VK_NUMPAD6                  0x66
#define VK_NUMPAD7                  0x67
#define VK_NUMPAD8                  0x68
#define VK_NUMPAD9                  0x69
#define VK_MULTIPLY                 0x6A
#define VK_ADD                      0x6B
#define VK_SEPARATOR                0x6C
#define VK_SUBTRACT                 0x6D
#define VK_DECIMAL                  0x6E
#define VK_DIVIDE                   0x6F
#define VK_F1                       0x70
#define VK_F2                       0x71
#define VK_F3                       0x72
#define VK_F4                       0x73
#define VK_F5                       0x74
#define VK_F6                       0x75
#define VK_F7                       0x76
#define VK_F8                       0x77
#define VK_F9                       0x78
#define VK_F10                      0x79
#define VK_F11                      0x7A
#define VK_F12                      0x7B
#define VK_F13                      0x7C
#define VK_F14                      0x7D
#define VK_F15                      0x7E
#define VK_F16                      0x7F
#define VK_F17                      0x80
#define VK_F18                      0x81
#define VK_F19                      0x82
#define VK_F20                      0x83
#define VK_F21                      0x84
#define VK_F22                      0x85
#define VK_F23                      0x86
#define VK_F24                      0x87
#define VK_NUMLOCK                  0x90
#define VK_SCROLL                   0x91
#define VK_OEM_NEC_EQUAL            0x92
#define VK_OEM_FJ_JISHO             0x92
#define VK_OEM_FJ_MASSHOU           0x93
#define VK_OEM_FJ_TOUROKU           0x94
#define VK_OEM_FJ_LOYA              0x95
#define VK_OEM_FJ_ROYA              0x96
#define VK_LSHIFT                   0xA0
#define VK_RSHIFT                   0xA1
#define VK_LCONTROL                 0xA2
#define VK_RCONTROL                 0xA3
#define VK_LMENU                    0xA4
#define VK_RMENU                    0xA5
#if (_WIN32_WINNT >= 0x0500)
    #define VK_BROWSER_BACK         0xA6
    #define VK_BROWSER_FORWARD      0xA7
    #define VK_BROWSER_REFRESH      0xA8
    #define VK_BROWSER_STOP         0xA9
    #define VK_BROWSER_SEARCH       0xAA
    #define VK_BROWSER_FAVORITES    0xAB
    #define VK_BROWSER_HOME         0xAC
    #define VK_VOLUME_MUTE          0xAD
    #define VK_VOLUME_DOWN          0xAE
    #define VK_VOLUME_UP            0xAF
    #define VK_MEDIA_NEXT_TRACK     0xB0
    #define VK_MEDIA_PREV_TRACK     0xB1
    #define VK_MEDIA_STOP           0xB2
    #define VK_MEDIA_PLAY_PAUSE     0xB3
    #define VK_LAUNCH_MAIL          0xB4
    #define VK_LAUNCH_MEDIA_SELECT  0xB5
    #define VK_LAUNCH_APP1          0xB6
    #define VK_LAUNCH_APP2          0xB7
#endif
#define VK_OEM_1                    0xBA
#define VK_OEM_PLUS                 0xBB
#define VK_OEM_COMMA                0xBC
#define VK_OEM_MINUS                0xBD
#define VK_OEM_PERIOD               0xBE
#define VK_OEM_2                    0xBF
#define VK_OEM_3                    0xC0
#define VK_OEM_4                    0xDB
#define VK_OEM_5                    0xDC
#define VK_OEM_6                    0xDD
#define VK_OEM_7                    0xDE
#define VK_OEM_8                    0xDF
#define VK_OEM_AX                   0xE1
#define VK_OEM_102                  0xE2
#define VK_ICO_HELP                 0xE3
#define VK_ICO_00                   0xE4
#if (WINVER >= 0x0400)
    #define VK_PROCESSKEY           0xE5
#endif
#define VK_ICO_CLEAR                0xE6
#if (_WIN32_WINNT >= 0x0500)
    #define VK_PACKET               0xE7
#endif
#define VK_OEM_RESET                0xE9
#define VK_OEM_JUMP                 0xEA
#define VK_OEM_PA1                  0xEB
#define VK_OEM_PA2                  0xEC
#define VK_OEM_PA3                  0xED
#define VK_OEM_WSCTRL               0xEE
#define VK_OEM_CUSEL                0xEF
#define VK_OEM_ATTN                 0xF0
#define VK_OEM_FINISH               0xF1
#define VK_OEM_COPY                 0xF2
#define VK_OEM_AUTO                 0xF3
#define VK_OEM_ENLW                 0xF4
#define VK_OEM_BACKTAB              0xF5
#define VK_ATTN                     0xF6
#define VK_CRSEL                    0xF7
#define VK_EXSEL                    0xF8
#define VK_EREOF                    0xF9
#define VK_PLAY                     0xFA
#define VK_ZOOM                     0xFB
#define VK_NONAME                   0xFC
#define VK_PA1                      0xFD
#define VK_OEM_CLEAR                0xFE

/* Hook types */
#define WH_MIN                  (-1)
#define WH_MSGFILTER            (-1)
#define WH_JOURNALRECORD        0
#define WH_JOURNALPLAYBACK      1
#define WH_KEYBOARD             2
#define WH_GETMESSAGE           3
#define WH_CALLWNDPROC          4
#define WH_CBT                  5
#define WH_SYSMSGFILTER         6
#define WH_MOUSE                7
#define WH_HARDWARE             8
#define WH_DEBUG                9
#define WH_SHELL                10
#define WH_FOREGROUNDIDLE       11
#if (WINVER >= 0x0400)
    #define WH_CALLWNDPROCRET   12
#endif
#if (_WIN32_WINNT >= 0x0400)
    #define WH_KEYBOARD_LL      13
    #define WH_MOUSE_LL         14
    #define WH_MAX              14
#elif (WINVER >= 0x0400)
    #define WH_MAX              12
#else
    #define WH_MAX              11
#endif
#define WH_MINHOOK              WH_MIN
#define WH_MAXHOOK              WH_MAX

/* Hook codes */
#define HC_ACTION       0
#define HC_GETNEXT      1
#define HC_SKIP         2
#define HC_NOREMOVE     3
#define HC_NOREM        HC_NOREMOVE
#define HC_SYSMODALON   4
#define HC_SYSMODALOFF  5

/* CBT hook codes */
#define HCBT_MOVESIZE       0
#define HCBT_MINMAX         1
#define HCBT_QS             2
#define HCBT_CREATEWND      3
#define HCBT_DESTROYWND     4
#define HCBT_ACTIVATE       5
#define HCBT_CLICKSKIPPED   6
#define HCBT_KEYSKIPPED     7
#define HCBT_SYSCOMMAND     8
#define HCBT_SETFOCUS       9

/* WM_WTSSESSION_CHANGE codes */
#if (_WIN32_WINNT >= 0x0501)
    #define WTS_CONSOLE_CONNECT         0x00000001
    #define WTS_CONSOLE_DISCONNECT      0x00000002
    #define WTS_REMOTE_CONNECT          0x00000003
    #define WTS_REMOTE_DISCONNECT       0x00000004
    #define WTS_SESSION_LOGON           0x00000005
    #define WTS_SESSION_LOGOFF          0x00000006
    #define WTS_SESSION_LOCK            0x00000007
    #define WTS_SESSION_UNLOCK          0x00000008
    #define WTS_SESSION_REMOTE_CONTROL  0x00000009
#endif

/* Message filter codes */
#define MSGF_DIALOGBOX  0
#define MSGF_MESSAGEBOX 1
#define MSGF_MENU       2
#define MSGF_SCROLLBAR  5
#define MSGF_NEXTWINDOW 6
#define MSGF_MAX        8
#define MSGF_USER       4096

/* Shell hook codes */
#define HSHELL_WINDOWCREATED            1
#define HSHELL_WINDOWDESTROYED          2
#define HSHELL_ACTIVATESHELLWINDOW      3
#if (WINVER >= 0x0400)
    #define HSHELL_WINDOWACTIVATED      4
    #define HSHELL_GETMINRECT           5
    #define HSHELL_REDRAW               6
    #define HSHELL_TASKMAN              7
    #define HSHELL_LANGUAGE             8
    #define HSHELL_SYSMENU              9
    #define HSHELL_ENDTASK              10
#endif
#if (_WIN32_WINNT >= 0x0500)
    #define HSHELL_ACCESSIBILITYSTATE   11
    #define HSHELL_APPCOMMAND           12
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define HSHELL_WINDOWREPLACED       13
    #define HSHELL_WINDOWREPLACING      14
#endif
#define HSHELL_HIGHBIT                  0x8000
#if (WINVER >= 0x0400)
    #define HSHELL_FLASH                (HSHELL_REDRAW | HSHELL_HIGHBIT)
    #define HSHELL_RUDEAPPACTIVATED     (HSHELL_WINDOWACTIVATED | HSHELL_HIGHBIT)
#endif

/* Accessibility state parameters */
#if (_WIN32_WINNT >= 0x0500)
    #define ACCESS_STICKYKEYS   0x0001
    #define ACCESS_FILTERKEYS   0x0002
    #define ACCESS_MOUSEKEYS    0x0003
#endif

/* WM_APPCOMMAND commands */
#if (_WIN32_WINNT >= 0x0500)
    #define APPCOMMAND_BROWSER_BACKWARD                     1
    #define APPCOMMAND_BROWSER_FORWARD                      2
    #define APPCOMMAND_BROWSER_REFRESH                      3
    #define APPCOMMAND_BROWSER_STOP                         4
    #define APPCOMMAND_BROWSER_SEARCH                       5
    #define APPCOMMAND_BROWSER_FAVORITES                    6
    #define APPCOMMAND_BROWSER_HOME                         7
    #define APPCOMMAND_VOLUME_MUTE                          8
    #define APPCOMMAND_VOLUME_DOWN                          9
    #define APPCOMMAND_VOLUME_UP                            10
    #define APPCOMMAND_MEDIA_NEXTTRACK                      11
    #define APPCOMMAND_MEDIA_PREVIOUSTRACK                  12
    #define APPCOMMAND_MEDIA_STOP                           13
    #define APPCOMMAND_MEDIA_PLAY_PAUSE                     14
    #define APPCOMMAND_LAUNCH_MAIL                          15
    #define APPCOMMAND_LAUNCH_MEDIA_SELECT                  16
    #define APPCOMMAND_LAUNCH_APP1                          17
    #define APPCOMMAND_LAUNCH_APP2                          18
    #define APPCOMMAND_BASS_DOWN                            19
    #define APPCOMMAND_BASS_BOOST                           20
    #define APPCOMMAND_BASS_UP                              21
    #define APPCOMMAND_TREBLE_DOWN                          22
    #define APPCOMMAND_TREBLE_UP                            23
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define APPCOMMAND_MICROPHONE_VOLUME_MUTE               24
    #define APPCOMMAND_MICROPHONE_VOLUME_DOWN               25
    #define APPCOMMAND_MICROPHONE_VOLUME_UP                 26
    #define APPCOMMAND_HELP                                 27
    #define APPCOMMAND_FIND                                 28
    #define APPCOMMAND_NEW                                  29
    #define APPCOMMAND_OPEN                                 30
    #define APPCOMMAND_CLOSE                                31
    #define APPCOMMAND_SAVE                                 32
    #define APPCOMMAND_PRINT                                33
    #define APPCOMMAND_UNDO                                 34
    #define APPCOMMAND_REDO                                 35
    #define APPCOMMAND_COPY                                 36
    #define APPCOMMAND_CUT                                  37
    #define APPCOMMAND_PASTE                                38
    #define APPCOMMAND_REPLY_TO_MAIL                        39
    #define APPCOMMAND_FORWARD_MAIL                         40
    #define APPCOMMAND_SEND_MAIL                            41
    #define APPCOMMAND_SPELL_CHECK                          42
    #define APPCOMMAND_DICTATE_OR_COMMAND_CONTROL_TOGGLE    43
    #define APPCOMMAND_MIC_ON_OFF_TOGGLE                    44
    #define APPCOMMAND_CORRECTION_LIST                      45
    #define APPCOMMAND_MEDIA_PLAY                           46
    #define APPCOMMAND_MEDIA_PAUSE                          47
    #define APPCOMMAND_MEDIA_RECORD                         48
    #define APPCOMMAND_MEDIA_FAST_FORWARD                   49
    #define APPCOMMAND_MEDIA_REWIND                         50
    #define APPCOMMAND_MEDIA_CHANNEL_UP                     51
    #define APPCOMMAND_MEDIA_CHANNEL_DOWN                   52
#endif
#if (_WIN32_WINNT >= 0x0600)
    #define APPCOMMAND_DELETE                               53
    #define APPCOMMAND_DWM_FLIP3D                           54
#endif

/* WM_APPCOMMAND device flags */
#if (_WIN32_WINNT >= 0x0500)
    #define FAPPCOMMAND_MOUSE   0x8000
    #define FAPPCOMMAND_KEY     0x0000
    #define FAPPCOMMAND_OEM     0x1000
    #define FAPPCOMMAND_MASK    0xF000
#endif

/* Low level keyboard hook flags */
#if (_WIN32_WINNT >= 0x0400)
    #define LLKHF_EXTENDED  (KF_EXTENDED >> 8)
    #define LLKHF_INJECTED  0x00000010L
    #define LLKHF_ALTDOWN   (KF_ALTDOWN >> 8)
    #define LLKHF_UP        (KF_UP >> 8)
#endif

/* Low level mouse hook flags */
#if (_WIN32_WINNT >= 0x0400)
    #define LLMHF_INJECTED  0x00000001L
#endif

/* Special keyboard layout handle values */
#define HKL_PREV    0
#define HKL_NEXT    1

/* Keyboard layout flags */
#define KLF_ACTIVATE            0x00000001
#define KLF_SUBSTITUTE_OK       0x00000002
#define KLF_REORDER             0x00000008
#if (WINVER >= 0x0400)
    #define KLF_REPLACELANG     0x00000010
    #define KLF_NOTELLSHELL     0x00000080
#endif
#define KLF_SETFORPROCESS       0x00000100
#if (_WIN32_WINNT >= 0x0500)
    #define KLF_SHIFTLOCK       0x00010000
    #define KLF_RESET           0x40000000
#endif

/* WM_INPUTLANGCHANGEREQUEST flags */
#if (WINVER >= 0x0500)
    #define INPUTLANGCHANGE_SYSCHARSET  0x0001
    #define INPUTLANGCHANGE_FORWARD     0x0002
    #define INPUTLANGCHANGE_BACKWARD    0x0004
#endif

/* Keyboard layout name length */
#define KL_NAMELENGTH   9

/* GetMouseMovePointsEx() resolutions */
#if (WINVER >= 0x0500)
    #define GMMP_USE_DISPLAY_POINTS         1L
    #define GMMP_USE_HIGH_RESOLUTION_POINTS 2L
#endif

/* Desktop access rights */
#define DESKTOP_READOBJECTS     0x0001L
#define DESKTOP_CREATEWINDOW    0x0002L
#define DESKTOP_CREATEMENU      0x0004L
#define DESKTOP_HOOKCONTROL     0x0008L
#define DESKTOP_JOURNALRECORD   0x0010L
#define DESKTOP_JOURNALPLAYBACK 0x0020L
#define DESKTOP_ENUMERATE       0x0040L
#define DESKTOP_WRITEOBJECTS    0x0080L
#define DESKTOP_SWITCHDESKTOP   0x0100L

/* CreateDesktop() flags */
#define DF_ALLOWOTHERACCOUNTHOOK    0x00000001L

/* Window station access rights */
#define WINSTA_ENUMDESKTOPS         0x0001L
#define WINSTA_READATTRIBUTES       0x0002L
#define WINSTA_ACCESSCLIPBOARD      0x0004L
#define WINSTA_CREATEDESKTOP        0x0008L
#define WINSTA_WRITEATTRIBUTES      0x0010L
#define WINSTA_ACCESSGLOBALATOMS    0x0020L
#define WINSTA_EXITWINDOWS          0x0040L
#define WINSTA_ENUMERATE            0x0100L
#define WINSTA_READSCREEN           0x0200L
#define WINSTA_ALL_ACCESS \
    (WINSTA_ENUMDESKTOPS | WINSTA_READATTRIBUTES | WINSTA_ACCESSCLIPBOARD | \
    WINSTA_CREATEDESKTOP | WINSTA_WRITEATTRIBUTES | WINSTA_ACCESSGLOBALATOMS | \
    WINSTA_EXITWINDOWS | WINSTA_ENUMERATE | WINSTA_READSCREEN)

/* CreateWindowStation() flags */
#define CWF_CREATE_ONLY 0x00000001L

/* Window station flags */
#define WSF_VISIBLE 0x00000001L

/* User object information types */
#define UOI_FLAGS           1
#define UOI_NAME            2
#define UOI_TYPE            3
#define UOI_USER_SID        4
#if (WINVER >= 0x0600)
    #define UOI_HEAPSIZE    5
    #define UOI_IO          6
#endif

/* GetWindowLong() offsets */
#define GWL_WNDPROC     (-4)
#define GWL_HINSTANCE   (-6)
#define GWL_HWNDPARENT  (-8)
#define GWL_ID          (-12)
#define GWL_STYLE       (-16)
#define GWL_EXSTYLE     (-20)
#define GWL_USERDATA    (-21)

/* GetWindowLongPtr() offsets */
#define GWLP_WNDPROC    (-4)
#define GWLP_HINSTANCE  (-6)
#define GWLP_HWNDPARENT (-8)
#define GWLP_ID         (-12)
#define GWLP_USERDATA   (-21)

/* GetClassLong() and GetClassWord() offsets */
#define GCL_MENUNAME        (-8)
#define GCL_HBRBACKGROUND   (-10)
#define GCL_HCURSOR         (-12)
#define GCL_HICON           (-14)
#define GCL_HMODULE         (-16)
#define GCL_CBWNDEXTRA      (-18)
#define GCL_CBCLSEXTRA      (-20)
#define GCL_WNDPROC         (-24)
#define GCL_STYLE           (-26)
#define GCW_ATOM            (-32)
#if (WINVER >= 0x0400)
    #define GCL_HICONSM     (-34)
#endif

/* GetClassLongPtr() offsets */
#define GCLP_MENUNAME       (-8)
#define GCLP_HBRBACKGROUND  (-10)
#define GCLP_HCURSOR        (-12)
#define GCLP_HICON          (-14)
#define GCLP_HMODULE        (-16)
#define GCLP_WNDPROC        (-24)
#define GCLP_HICONSM        (-34)

/* Window messages */
#define WM_NULL                             0x0000
#define WM_CREATE                           0x0001
#define WM_DESTROY                          0x0002
#define WM_MOVE                             0x0003
#define WM_SIZE                             0x0005
#define WM_ACTIVATE                         0x0006
#define WM_SETFOCUS                         0x0007
#define WM_KILLFOCUS                        0x0008
#define WM_ENABLE                           0x000A
#define WM_SETREDRAW                        0x000B
#define WM_SETTEXT                          0x000C
#define WM_GETTEXT                          0x000D
#define WM_GETTEXTLENGTH                    0x000E
#define WM_PAINT                            0x000F
#define WM_CLOSE                            0x0010
#define WM_QUERYENDSESSION                  0x0011
#define WM_QUIT                             0x0012
#define WM_QUERYOPEN                        0x0013
#define WM_ERASEBKGND                       0x0014
#define WM_SYSCOLORCHANGE                   0x0015
#define WM_ENDSESSION                       0x0016
#define WM_SHOWWINDOW                       0x0018
#define WM_WININICHANGE                     0x001A
#if (WINVER >= 0x0400)
    #define WM_SETTINGCHANGE                WM_WININICHANGE
#endif
#define WM_DEVMODECHANGE                    0x001B
#define WM_ACTIVATEAPP                      0x001C
#define WM_FONTCHANGE                       0x001D
#define WM_TIMECHANGE                       0x001E
#define WM_CANCELMODE                       0x001F
#define WM_SETCURSOR                        0x0020
#define WM_MOUSEACTIVATE                    0x0021
#define WM_CHILDACTIVATE                    0x0022
#define WM_QUEUESYNC                        0x0023
#define WM_GETMINMAXINFO                    0x0024
#define WM_PAINTICON                        0x0026
#define WM_ICONERASEBKGND                   0x0027
#define WM_NEXTDLGCTL                       0x0028
#define WM_SPOOLERSTATUS                    0x002A
#define WM_DRAWITEM                         0x002B
#define WM_MEASUREITEM                      0x002C
#define WM_DELETEITEM                       0x002D
#define WM_VKEYTOITEM                       0x002E
#define WM_CHARTOITEM                       0x002F
#define WM_SETFONT                          0x0030
#define WM_GETFONT                          0x0031
#define WM_SETHOTKEY                        0x0032
#define WM_GETHOTKEY                        0x0033
#define WM_QUERYDRAGICON                    0x0037
#define WM_COMPAREITEM                      0x0039
#if (WINVER >= 0x0500)
    #define WM_GETOBJECT                    0x003D
#endif
#define WM_COMPACTING                       0x0041
#define WM_COMMNOTIFY                       0x0044
#define WM_WINDOWPOSCHANGING                0x0046
#define WM_WINDOWPOSCHANGED                 0x0047
#define WM_POWER                            0x0048
#define WM_COPYDATA                         0x004A
#define WM_CANCELJOURNAL                    0x004B
#if (WINVER >= 0x0400)
    #define WM_NOTIFY                       0x004E
    #define WM_INPUTLANGCHANGEREQUEST       0x0050
    #define WM_INPUTLANGCHANGE              0x0051
    #define WM_TCARD                        0x0052
    #define WM_HELP                         0x0053
    #define WM_USERCHANGED                  0x0054
    #define WM_NOTIFYFORMAT                 0x0055
    #define WM_CONTEXTMENU                  0x007B
    #define WM_STYLECHANGING                0x007C
    #define WM_STYLECHANGED                 0x007D
    #define WM_DISPLAYCHANGE                0x007E
    #define WM_GETICON                      0x007F
    #define WM_SETICON                      0x0080
#endif
#define WM_NCCREATE                         0x0081
#define WM_NCDESTROY                        0x0082
#define WM_NCCALCSIZE                       0x0083
#define WM_NCHITTEST                        0x0084
#define WM_NCPAINT                          0x0085
#define WM_NCACTIVATE                       0x0086
#define WM_GETDLGCODE                       0x0087
#define WM_SYNCPAINT                        0x0088
#define WM_NCMOUSEMOVE                      0x00A0
#define WM_NCLBUTTONDOWN                    0x00A1
#define WM_NCLBUTTONUP                      0x00A2
#define WM_NCLBUTTONDBLCLK                  0x00A3
#define WM_NCRBUTTONDOWN                    0x00A4
#define WM_NCRBUTTONUP                      0x00A5
#define WM_NCRBUTTONDBLCLK                  0x00A6
#define WM_NCMBUTTONDOWN                    0x00A7
#define WM_NCMBUTTONUP                      0x00A8
#define WM_NCMBUTTONDBLCLK                  0x00A9
#if (_WIN32_WINNT >= 0x0500)
    #define WM_NCXBUTTONDOWN                0x00AB
    #define WM_NCXBUTTONUP                  0x00AC
    #define WM_NCXBUTTONDBLCLK              0x00AD
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define WM_INPUT_DEVICE_CHANGE          0x00FE
    #define WM_INPUT                        0x00FF
#endif
#define WM_KEYFIRST                         0x0100
#define WM_KEYDOWN                          0x0100
#define WM_KEYUP                            0x0101
#define WM_CHAR                             0x0102
#define WM_DEADCHAR                         0x0103
#define WM_SYSKEYDOWN                       0x0104
#define WM_SYSKEYUP                         0x0105
#define WM_SYSCHAR                          0x0106
#define WM_SYSDEADCHAR                      0x0107
#if (_WIN32_WINNT >= 0x0501)
    #define WM_UNICHAR                      0x0109
    #define WM_KEYLAST                      0x0109
#else
    #define WM_KEYLAST                      0x0108
#endif
#if (WINVER >= 0x0400)
    #define WM_IME_STARTCOMPOSITION         0x010D
    #define WM_IME_ENDCOMPOSITION           0x010E
    #define WM_IME_COMPOSITION              0x010F
    #define WM_IME_KEYLAST                  0x010F
#endif
#define WM_INITDIALOG                       0x0110
#define WM_COMMAND                          0x0111
#define WM_SYSCOMMAND                       0x0112
#define WM_TIMER                            0x0113
#define WM_HSCROLL                          0x0114
#define WM_VSCROLL                          0x0115
#define WM_INITMENU                         0x0116
#define WM_INITMENUPOPUP                    0x0117
#define WM_MENUSELECT                       0x011F
#define WM_MENUCHAR                         0x0120
#define WM_ENTERIDLE                        0x0121
#if (WINVER >= 0x0500)
    #define WM_MENURBUTTONUP                0x0122
    #define WM_MENUDRAG                     0x0123
    #define WM_MENUGETOBJECT                0x0124
    #define WM_UNINITMENUPOPUP              0x0125
    #define WM_MENUCOMMAND                  0x0126
#endif
#if (_WIN32_WINNT >= 0x0500)
    #define WM_CHANGEUISTATE                0x0127
    #define WM_UPDATEUISTATE                0x0128
    #define WM_QUERYUISTATE                 0x0129
#endif
#define WM_CTLCOLORMSGBOX                   0x0132
#define WM_CTLCOLOREDIT                     0x0133
#define WM_CTLCOLORLISTBOX                  0x0134
#define WM_CTLCOLORBTN                      0x0135
#define WM_CTLCOLORDLG                      0x0136
#define WM_CTLCOLORSCROLLBAR                0x0137
#define WM_CTLCOLORSTATIC                   0x0138
#define MN_GETHMENU                         0x01E1
#define WM_MOUSEFIRST                       0x0200
#define WM_MOUSEMOVE                        0x0200
#define WM_LBUTTONDOWN                      0x0201
#define WM_LBUTTONUP                        0x0202
#define WM_LBUTTONDBLCLK                    0x0203
#define WM_RBUTTONDOWN                      0x0204
#define WM_RBUTTONUP                        0x0205
#define WM_RBUTTONDBLCLK                    0x0206
#define WM_MBUTTONDOWN                      0x0207
#define WM_MBUTTONUP                        0x0208
#define WM_MBUTTONDBLCLK                    0x0209
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
    #define WM_MOUSEWHEEL                   0x020A
#endif
#if (_WIN32_WINNT >= 0x0500)
    #define WM_XBUTTONDOWN                  0x020B
    #define WM_XBUTTONUP                    0x020C
    #define WM_XBUTTONDBLCLK                0x020D
#endif
#if (_WIN32_WINNT >= 0x0600)
    #define WM_MOUSEHWHEEL                  0x020E
    #define WM_MOUSELAST                    0x020E
#elif (_WIN32_WINNT >= 0x0500)
    #define WM_MOUSELAST                    0x020D
#elif (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
    #define WM_MOUSELAST                    0x020A
#else
    #define WM_MOUSELAST                    0x0209
#endif
#define WM_PARENTNOTIFY                     0x0210
#define WM_ENTERMENULOOP                    0x0211
#define WM_EXITMENULOOP                     0x0212
#if (WINVER >= 0x0400)
    #define WM_NEXTMENU                     0x0213
    #define WM_SIZING                       0x0214
    #define WM_CAPTURECHANGED               0x0215
    #define WM_MOVING                       0x0216
    #define WM_POWERBROADCAST               0x0218
    #define WM_DEVICECHANGE                 0x0219
#endif
#define WM_MDICREATE                        0x0220
#define WM_MDIDESTROY                       0x0221
#define WM_MDIACTIVATE                      0x0222
#define WM_MDIRESTORE                       0x0223
#define WM_MDINEXT                          0x0224
#define WM_MDIMAXIMIZE                      0x0225
#define WM_MDITILE                          0x0226
#define WM_MDICASCADE                       0x0227
#define WM_MDIICONARRANGE                   0x0228
#define WM_MDIGETACTIVE                     0x0229
#define WM_MDISETMENU                       0x0230
#define WM_ENTERSIZEMOVE                    0x0231
#define WM_EXITSIZEMOVE                     0x0232
#define WM_DROPFILES                        0x0233
#define WM_MDIREFRESHMENU                   0x0234
#if (WINVER >= 0x0400)
    #define WM_IME_SETCONTEXT               0x0281
    #define WM_IME_NOTIFY                   0x0282
    #define WM_IME_CONTROL                  0x0283
    #define WM_IME_COMPOSITIONFULL          0x0284
    #define WM_IME_SELECT                   0x0285
    #define WM_IME_CHAR                     0x0286
#endif
#if (WINVER >= 0x0500)
    #define WM_IME_REQUEST                  0x0288
#endif
#if (WINVER >= 0x0400)
    #define WM_IME_KEYDOWN                  0x0290
    #define WM_IME_KEYUP                    0x0291
#endif
#if (WINVER >= 0x0500)
    #define WM_NCMOUSEHOVER                 0x02A0
#endif
#if (_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500)
    #define WM_MOUSEHOVER                   0x02A1
#endif
#if (WINVER >= 0x0500)
    #define WM_NCMOUSELEAVE                 0x02A2
#endif
#if (_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500)
    #define WM_MOUSELEAVE                   0x02A3
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define WM_WTSSESSION_CHANGE            0x02B1
    #define WM_TABLET_FIRST                 0x02C0
    #define WM_TABLET_LAST                  0x02DF
#endif
#define WM_CUT                              0x0300
#define WM_COPY                             0x0301
#define WM_PASTE                            0x0302
#define WM_CLEAR                            0x0303
#define WM_UNDO                             0x0304
#define WM_RENDERFORMAT                     0x0305
#define WM_RENDERALLFORMATS                 0x0306
#define WM_DESTROYCLIPBOARD                 0x0307
#define WM_DRAWCLIPBOARD                    0x0308
#define WM_PAINTCLIPBOARD                   0x0309
#define WM_VSCROLLCLIPBOARD                 0x030A
#define WM_SIZECLIPBOARD                    0x030B
#define WM_ASKCBFORMATNAME                  0x030C
#define WM_CHANGECBCHAIN                    0x030D
#define WM_HSCROLLCLIPBOARD                 0x030E
#define WM_QUERYNEWPALETTE                  0x030F
#define WM_PALETTEISCHANGING                0x0310
#define WM_PALETTECHANGED                   0x0311
#define WM_HOTKEY                           0x0312
#if (WINVER >= 0x0400)
    #define WM_PRINT                        0x0317
    #define WM_PRINTCLIENT                  0x0318
#endif
#if (_WIN32_WINNT >= 0x0500)
    #define WM_APPCOMMAND                   0x0319
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define WM_THEMECHANGED                 0x031A
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define WM_CLIPBOARDUPDATE              0x031D
#endif
#if (_WIN32_WINNT >= 0x0600)
    #define WM_DWMCOMPOSITIONCHANGED        0x031E
    #define WM_DWMNCRENDERINGCHANGED        0x031F
    #define WM_DWMCOLORIZATIONCOLORCHANGED  0x0320
    #define WM_DWMWINDOWMAXIMIZEDCHANGED    0x0321
#endif
#if (WINVER >= 0x0600)
    #define WM_GETTITLEBARINFOEX            0x033F
#endif
#if (WINVER >= 0x0400)
    #define WM_HANDHELDFIRST                0x0358
    #define WM_HANDHELDLAST                 0x035F
    #define WM_AFXFIRST                     0x0360
    #define WM_AFXLAST                      0x037F
#endif
#define WM_PENWINFIRST                      0x0380
#define WM_PENWINLAST                       0x038F
#define WM_USER                             0x0400
#if (WINVER >= 0x0400)
    #define WM_APP                          0x8000
#endif

/* WM_ACTIVATE states */
#define WA_INACTIVE     0
#define WA_ACTIVE       1
#define WA_CLICKACTIVE  2

/* WM_POWER return values */
#define PWR_OK      1
#define PWR_FAIL    (-1)

/* WM_POWER notification codes */
#define PWR_SUSPENDREQUEST  1
#define PWR_SUSPENDRESUME   2
#define PWR_CRITICALRESUME  3

/* WM_NOTIFYFORMAT return values */
#if (WINVER >= 0x0400)
    #define NFR_ANSI    1
    #define NFR_UNICODE 2
#endif

/* WM_NOTIFYFORMAT notification codes */
#if (WINVER >= 0x0400)
    #define NF_QUERY    3
    #define NF_REQUERY  4
#endif

/* WM_UNICHAR special value */
#if (_WIN32_WINNT >= 0x0501)
    #define UNICODE_NOCHAR  0xFFFF
#endif

/* UI states */
#if (_WIN32_WINNT >= 0x0500)
    #define UIS_SET         1
    #define UIS_CLEAR       2
    #define UIS_INITIALIZE  3
#endif

/* UI state flags */
#if (_WIN32_WINNT >= 0x0500)
    #define UISF_HIDEFOCUS  0x0001
    #define UISF_HIDEACCEL  0x0002
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define UISF_ACTIVE     0x0004
#endif

/* Constant used with WM_MOUSEWHEEL */
#if (_WIN32_WINNT >= 0x0400)
    #define WHEEL_DELTA 120
#endif

/* Constant used with SPI_GETWHEELSCROLLLINES and SPI_SETWHEELSCROLLLINES */
#if (_WIN32_WINNT >= 0x0400)
    #define WHEEL_PAGESCROLL    UINT_MAX
#endif

/* X button identifiers */
#if (_WIN32_WINNT >= 0x0500)
    #define XBUTTON1    0x0001
    #define XBUTTON2    0x0002
#endif

/* Power management events */
#if (WINVER >= 0x0400)
    #define PBT_APMQUERYSUSPEND         0x0000
    #define PBT_APMQUERYSTANDBY         0x0001
    #define PBT_APMQUERYSUSPENDFAILED   0x0002
    #define PBT_APMQUERYSTANDBYFAILED   0x0003
    #define PBT_APMSUSPEND              0x0004
    #define PBT_APMSTANDBY              0x0005
    #define PBT_APMRESUMECRITICAL       0x0006
    #define PBT_APMRESUMESUSPEND        0x0007
    #define PBT_APMRESUMESTANDBY        0x0008
    #define PBT_APMBATTERYLOW           0x0009
    #define PBT_APMPOWERSTATUSCHANGE    0x000A
    #define PBT_APMOEMEVENT             0x000B
    #define PBT_APMRESUMEAUTOMATIC      0x0012
    #if (_WIN32_WINNT >= 0x0502)
        #define PBT_POWERSETTINGCHANGE  0x8013
    #endif
#endif

/* WM_POWERBROADCAST flags */
#if (WINVER >= 0x0400)
    #define PBTF_APMRESUMEFROMFAILURE   0x00000001L
#endif

/* WM_SIZING codes */
#if (WINVER >= 0x0400)
    #define WMSZ_LEFT           1
    #define WMSZ_RIGHT          2
    #define WMSZ_TOP            3
    #define WMSZ_TOPLEFT        4
    #define WMSZ_TOPRIGHT       5
    #define WMSZ_BOTTOM         6
    #define WMSZ_BOTTOMLEFT     7
    #define WMSZ_BOTTOMRIGHT    8
#endif

/* WM_NCHITTEST codes */
#define HTERROR         (-2)
#define HTTRANSPARENT   (-1)
#define HTNOWHERE       0
#define HTCLIENT        1
#define HTCAPTION       2
#define HTSYSMENU       3
#define HTGROWBOX       4
#define HTSIZE          HTGROWBOX
#define HTMENU          5
#define HTHSCROLL       6
#define HTVSCROLL       7
#define HTMINBUTTON     8
#define HTMAXBUTTON     9
#define HTLEFT          10
#define HTRIGHT         11
#define HTTOP           12
#define HTTOPLEFT       13
#define HTTOPRIGHT      14
#define HTBOTTOM        15
#define HTBOTTOMLEFT    16
#define HTBOTTOMRIGHT   17
#define HTBORDER        18
#define HTREDUCE        HTMINBUTTON
#define HTZOOM          HTMAXBUTTON
#define HTSIZEFIRST     HTLEFT
#define HTSIZELAST      HTBOTTOMRIGHT
#if (WINVER >= 0x0400)
    #define HTOBJECT    19
    #define HTCLOSE     20
    #define HTHELP      21
#endif

/* SendMessageTimeout() flags */
#define SMTO_NORMAL                 0x0000
#define SMTO_BLOCK                  0x0001
#define SMTO_ABORTIFHUNG            0x0002
#if (WINVER >= 0x0500)
    #define SMTO_NOTIMEOUTIFNOTHUNG 0x0008
#endif
#if (WINVER >= 0x0600)
    #define SMTO_ERRORONEXIT        0x0020
#endif

/* WM_MOUSEACTIVATE return values */
#define MA_ACTIVATE         1L
#define MA_ACTIVATEANDEAT   2L
#define MA_NOACTIVATE       3L
#define MA_NOACTIVATEANDEAT 4L

/* Icon types */
#define ICON_SMALL      0
#define ICON_BIG        1
#if (_WIN32_WINNT >= 0x0501)
    #define ICON_SMALL2 2
#endif

/* WM_SIZE codes */
#define SIZE_RESTORED   0
#define SIZE_MINIMIZED  1
#define SIZE_MAXIMIZED  2
#define SIZE_MAXSHOW    3
#define SIZE_MAXHIDE    4

/* Old names for WM_SIZE codes */
#define SIZENORMAL      SIZE_RESTORED
#define SIZEICONIC      SIZE_MINIMIZED
#define SIZEFULLSCREEN  SIZE_MAXIMIZED
#define SIZEZOOMSHOW    SIZE_MAXSHOW
#define SIZEZOOMHIDE    SIZE_MAXHIDE

/* WM_NCCALCSIZE return values */
#define WVR_ALIGNTOP    0x00000010L
#define WVR_ALIGNLEFT   0x00000020L
#define WVR_ALIGNBOTTOM 0x00000040L
#define WVR_ALIGNRIGHT  0x00000080L
#define WVR_HREDRAW     0x00000100L
#define WVR_VREDRAW     0x00000200L
#define WVR_REDRAW      (WVR_HREDRAW | WVR_VREDRAW)
#define WVR_VALIDRECTS  0x00000400L

/* Key states used with mouse messages */
#define MK_LBUTTON      0x0001
#define MK_RBUTTON      0x0002
#define MK_SHIFT        0x0004
#define MK_CONTROL      0x0008
#define MK_MBUTTON      0x0010
#if (_WIN32_WINNT >= 0x0500)
    #define MK_XBUTTON1 0x0020
    #define MK_XBUTTON2 0x0040
#endif

/* TrackMouseEvent() flags */
#if (_WIN32_WINNT >= 0x0400)
    #define TME_HOVER           0x00000001L
    #define TME_LEAVE           0x00000002L
    #if (WINVER >= 0x0500)
        #define TME_NONCLIENT   0x00000010L
    #endif
    #define TME_QUERY           0x40000000L
    #define TME_CANCEL          0x80000000L
#endif

/* Hover time special value */
#if (_WIN32_WINNT >= 0x0400)
    #define HOVER_DEFAULT   0xFFFFFFFFL
#endif

/* Window styles */
#define WS_OVERLAPPED       0x00000000L
#define WS_POPUP            0x80000000L
#define WS_CHILD            0x40000000L
#define WS_MINIMIZE         0x20000000L
#define WS_VISIBLE          0x10000000L
#define WS_DISABLED         0x08000000L
#define WS_CLIPSIBLINGS     0x04000000L
#define WS_CLIPCHILDREN     0x02000000L
#define WS_MAXIMIZE         0x01000000L
#define WS_CAPTION          0x00C00000L
#define WS_BORDER           0x00800000L
#define WS_DLGFRAME         0x00400000L
#define WS_VSCROLL          0x00200000L
#define WS_HSCROLL          0x00100000L
#define WS_SYSMENU          0x00080000L
#define WS_THICKFRAME       0x00040000L
#define WS_GROUP            0x00020000L
#define WS_TABSTOP          0x00010000L
#define WS_MINIMIZEBOX      0x00020000L
#define WS_MAXIMIZEBOX      0x00010000L
#define WS_OVERLAPPEDWINDOW \
    (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | \
    WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW      (WS_POPUP | WS_BORDER | WS_SYSMENU)
#define WS_CHILDWINDOW      (WS_CHILD)

/* Old names for window styles */
#define WS_TILED        WS_OVERLAPPED
#define WS_ICONIC       WS_MINIMIZE
#define WS_SIZEBOX      WS_THICKFRAME
#define WS_TILEDWINDOW  WS_OVERLAPPEDWINDOW

/* Extended window styles */
#define WS_EX_DLGMODALFRAME         0x00000001L
#define WS_EX_NOPARENTNOTIFY        0x00000004L
#define WS_EX_TOPMOST               0x00000008L
#define WS_EX_ACCEPTFILES           0x00000010L
#define WS_EX_TRANSPARENT           0x00000020L
#if (WINVER >= 0x0400)
    #define WS_EX_MDICHILD          0x00000040L
    #define WS_EX_TOOLWINDOW        0x00000080L
    #define WS_EX_WINDOWEDGE        0x00000100L
    #define WS_EX_CLIENTEDGE        0x00000200L
    #define WS_EX_CONTEXTHELP       0x00000400L
    #define WS_EX_RIGHT             0x00001000L
    #define WS_EX_LEFT              0x00000000L
    #define WS_EX_RTLREADING        0x00002000L
    #define WS_EX_LTRREADING        0x00000000L
    #define WS_EX_LEFTSCROLLBAR     0x00004000L
    #define WS_EX_RIGHTSCROLLBAR    0x00000000L
    #define WS_EX_CONTROLPARENT     0x00010000L
    #define WS_EX_STATICEDGE        0x00020000L
    #define WS_EX_APPWINDOW         0x00040000L
    #define WS_EX_OVERLAPPEDWINDOW  (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
    #define WS_EX_PALETTEWINDOW     (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)
#endif
#if (_WIN32_WINNT >= 0x0500)
    #define WS_EX_LAYERED           0x00080000L
#endif
#if (WINVER >= 0x0500)
    #define WS_EX_NOINHERITLAYOUT   0x00100000L
    #define WS_EX_LAYOUTRTL         0x00400000L
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define WS_EX_COMPOSITED        0x02000000L
#endif
#if (_WIN32_WINNT >= 0x0500)
    #define WS_EX_NOACTIVATE        0x08000000L
#endif

/* Class styles */
#define CS_VREDRAW          0x00000001
#define CS_HREDRAW          0x00000002
#define CS_DBLCLKS          0x00000008
#define CS_OWNDC            0x00000020
#define CS_CLASSDC          0x00000040
#define CS_PARENTDC         0x00000080
#define CS_NOCLOSE          0x00000200
#define CS_SAVEBITS         0x00000800
#define CS_BYTEALIGNCLIENT  0x00001000
#define CS_BYTEALIGNWINDOW  0x00002000
#define CS_GLOBALCLASS      0x00004000
#define CS_IME              0x00010000
#if (_WIN32_WINNT >= 0x0501)
    #define CS_DROPSHADOW   0x00020000
#endif

/* WM_PRINT flags */
#if (WINVER >= 0x0400)
    #define PRF_CHECKVISIBLE    0x00000001L
    #define PRF_NONCLIENT       0x00000002L
    #define PRF_CLIENT          0x00000004L
    #define PRF_ERASEBKGND      0x00000008L
    #define PRF_CHILDREN        0x00000010L
    #define PRF_OWNED           0x00000020L
#endif

/* DrawEdge() styles */
#if (WINVER >= 0x0400)
    #define BDR_RAISEDOUTER 0x0001
    #define BDR_SUNKENOUTER 0x0002
    #define BDR_RAISEDINNER 0x0004
    #define BDR_SUNKENINNER 0x0008
    #define BDR_OUTER       (BDR_RAISEDOUTER | BDR_SUNKENOUTER)
    #define BDR_INNER       (BDR_RAISEDINNER | BDR_SUNKENINNER)
    #define BDR_RAISED      (BDR_RAISEDOUTER | BDR_RAISEDINNER)
    #define BDR_SUNKEN      (BDR_SUNKENOUTER | BDR_SUNKENINNER)
    #define EDGE_RAISED     (BDR_RIASEDOUTER | BDR_RAISEDINNER)
    #define EDGE_SUNKEN     (BDR_SUNKENOUTER | BDR_SUNKENINNER)
    #define EDGE_ETCHED     (BDR_SUNKENOUTER | BDR_RAISEDINNER)
    #define EDGE_BUMP       (BDR_RAISEDOUTER | BDR_SUNKENINNER)
#endif

/* DrawEdge() flags */
#if (WINVER >= 0x0400)
    #define BF_LEFT                     0x0001
    #define BF_TOP                      0x0002
    #define BF_RIGHT                    0x0004
    #define BF_BOTTOM                   0x0008
    #define BF_TOPLEFT                  (BF_TOP | BF_LEFT)
    #define BF_TOPRIGHT                 (BF_TOP | BF_RIGHT)
    #define BF_BOTTOMLEFT               (BF_BOTTOM | BF_LEFT)
    #define BF_BOTTOMRIGHT              (BF_BOTTOM | BF_RIGHT)
    #define BF_RECT                     (BF_LEFT | BF_TOP | BF_RIGHT | BF_BOTTOM)
    #define BF_DIAGONAL                 0x0010
    #define BF_DIAGONAL_ENDTOPRIGHT     (BF_DIAGONAL | BF_TOP | BF_RIGHT)
    #define BF_DIAGONAL_ENDTOPLEFT      (BF_DIAGONAL | BF_TOP | BF_LEFT)
    #define BF_DIAGONAL_ENDBOTTOMLEFT   (BF_DIAGONAL | BF_BOTTOM | BF_LEFT)
    #define BF_DIAGONAL_ENDBOTTOMRIGHT  (BF_DIAGONAL | BF_BOTTOM | BF_RIGHT)
    #define BF_MIDDLE                   0x0800
    #define BF_SOFT                     0x1000
    #define BF_ADJUST                   0x2000
    #define BF_FLAT                     0x4000
    #define BF_MONO                     0x8000
#endif

/* DrawFrameControl() types */
#if (WINVER >= 0x0400)
    #define DFC_CAPTION     1
    #define DFC_MENU        2
    #define DFC_SCROLL      3
    #define DFC_BUTTON      4
#endif
#if (WINVER >= 0x0500)
    #define DFC_POPUPMENU   5
#endif

/* DrawFrameControl() state flags */
#if (WINVER >= 0x0400)
    #define DFCS_CAPTIONCLOSE           0x0000
    #define DFCS_CAPTIONMIN             0x0001
    #define DFCS_CAPTIONMAX             0x0002
    #define DFCS_CAPTIONRESTORE         0x0003
    #define DFCS_CAPTIONHELP            0x0004
    #define DFCS_MENUARROW              0x0000
    #define DFCS_MENUCHECK              0x0001
    #define DFCS_MENUBULLET             0x0002
    #define DFCS_MENUARROWRIGHT         0x0004
    #define DFCS_SCROLLUP               0x0000
    #define DFCS_SCROLLDOWN             0x0001
    #define DFCS_SCROLLLEFT             0x0002
    #define DFCS_SCROLLRIGHT            0x0003
    #define DFCS_SCROLLCOMBOBOX         0x0005
    #define DFCS_SCROLLSIZEGRIP         0x0008
    #define DFCS_SCROLLSIZEGRIPRIGHT    0x0010
    #define DFCS_BUTTONCHECK            0x0000
    #define DFCS_BUTTONRADIOIMAGE       0x0001
    #define DFCS_BUTTONRADIOMASK        0x0002
    #define DFCS_BUTTONRADIO            0x0004
    #define DFCS_BUTTON3STATE           0x0008
    #define DFCS_BUTTONPUSH             0x0010
    #define DFCS_INACTIVE               0x0100
    #define DFCS_PUSHED                 0x0200
    #define DFCS_CHECKED                0x0400
#endif
#if (WINVER >= 0x0500)
    #define DFCS_TRANSPARENT            0x0800
    #define DFCS_HOT                    0x1000
#endif
#if (WINVER >= 0x0400)
    #define DFCS_ADJUSTRECT             0x2000
    #define DFCS_FLAT                   0x4000
    #define DFCS_MONO                   0x8000
#endif

/* DrawCaption() flags */
#if (WINVER >= 0x0400)
    #define DC_ACTIVE       0x0001
    #define DC_SMALLCAP     0x0002
    #define DC_ICON         0x0004
    #define DC_TEXT         0x0008
    #define DC_INBUTTON     0x0010
#endif
#if (WINVER >= 0x0500)
    #define DC_GRADIENT     0x0020
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define DC_BUTTONS      0x1000
#endif

/* DrawAnimatedRects() animation identifiers */
#if (WINVER >= 0x0400)
    #define IDANI_OPEN      1
    #define IDANI_CAPTION   3
#endif

/* Clipboard formats */
#define CF_TEXT             0x0001
#define CF_BITMAP           0x0002
#define CF_METAFILEPICT     0x0003
#define CF_SYLK             0x0004
#define CF_DIF              0x0005
#define CF_TIFF             0x0006
#define CF_OEMTEXT          0x0007
#define CF_DIB              0x0008
#define CF_PALETTE          0x0009
#define CF_PENDATA          0x000A
#define CF_RIFF             0x000B
#define CF_WAVE             0x000C
#define CF_UNICODETEXT      0x000D
#define CF_ENHMETAFILE      0x000E
#if (WINVER >= 0x0400)
    #define CF_HDROP        0x000F
    #define CF_LOCALE       0x0010
#endif
#if (WINVER >= 0x0500)
    #define CF_DIBV5        0x0011
    #define CF_MAX          0x0012
#elif (WINVER >= 0x0400)
    #define CF_MAX          0x0011
#else
    #define CF_MAX          0x000F
#endif
#define CF_OWNERDISPLAY     0x0080
#define CF_DSPTEXT          0x0081
#define CF_DSPBITMAP        0x0082
#define CF_DSPMETAFILEPICT  0x0083
#define CF_DSPENHMETAFILE   0x008E
#define CF_PRIVATEFIRST     0x0200
#define CF_PRIVATELAST      0x02FF
#define CF_GDIOBJFIRST      0x0300
#define CF_GDIOBJLAST       0x03FF

/* Accelerator flags */
#define FVIRTKEY    0x01
#define FNOINVERT   0x02
#define FSHIFT      0x04
#define FCONTROL    0x08
#define FALT        0x10

/* Window placement flags */
#define WPF_SETMINPOSITION              0x0001
#define WPF_RESTORETOMAXIMIZED          0x0002
#if (_WIN32_WINNT >= 0x0500)
    #define WPF_ASYNCWINDOWPLACEMENT    0x0004
#endif

/* Owner draw types */
#define ODT_MENU        1
#define ODT_LISTBOX     2
#define ODT_COMBOBOX    3
#define ODT_BUTTON      4
#if (WINVER >= 0x0400)
    #define ODT_STATIC  5
#endif

/* Owner draw actions */
#define ODA_DRAWENTIRE  0x0001
#define ODA_SELECT      0x0002
#define ODA_FOCUS       0x0004

/* Owner draw states */
#define ODS_SELECTED            0x0001
#define ODS_GRAYED              0x0002
#define ODS_DISABLED            0x0004
#define ODS_CHECKED             0x0008
#define ODS_FOCUS               0x0010
#if (WINVER >= 0x0400)
    #define ODS_DEFAULT         0x0020
#endif
#if (WINVER >= 0x0500)
    #define ODS_HOTLIGHT        0x0040
    #define ODS_INACTIVE        0x0080
#endif
#if (_WIN32_WINNT >= 0x0500)
    #define ODS_NOACCEL         0x0100
    #define ODS_NOFOCUSRECT     0x0200
#endif
#if (WINVER >= 0x0400)
    #define ODS_COMBOBOXEDIT    0x1000
#endif

/* GetQueueStatus() return values */
#define QS_KEY              0x00000001L
#define QS_MOUSEMOVE        0x00000002L
#define QS_MOUSEBUTTON      0x00000004L
#define QS_POSTMESSAGE      0x00000008L
#define QS_TIMER            0x00000010L
#define QS_PAINT            0x00000020L
#define QS_SENDMESSAGE      0x00000040L
#define QS_HOTKEY           0x00000080L
#define QS_ALLPOSTMESSAGE   0x00000100L
#if (_WIN32_WINNT >= 0x0501)
    #define QS_RAWINPUT     0x00000400L
#endif
#define QS_MOUSE            (QS_MOUSEMOVE | QS_MOUSEBUTTON)
#if (_WIN32_WINNT >= 0x0501)
    #define QS_INPUT        (QS_MOUSE | QS_KEY | QS_RAWINPUT)
#else
    #define QS_INPUT        (QS_MOUSE | QS_KEY)
#endif
#define QS_ALLEVENTS        (QS_INPUT | QS_POSTMESSAGE | QS_TIMER | QS_PAINT | QS_HOTKEY)
#define QS_ALLINPUT \
    (QS_INPUT | QS_POSTMESSAGE | QS_TIMER | QS_PAINT | QS_HOTKEY | QS_SENDMESSAGE)

/* PeekMessage() flags */
#define PM_NOREMOVE             0x0000
#define PM_REMOVE               0x0001
#define PM_NOYIELD              0x0002
#if (WINVER >= 0x0500)
    #define PM_QS_INPUT         (QS_INPUT << 16)
    #define PM_QS_POSTMESSAGE   ((QS_POSTMESSAGE | QS_HOTKEY | QS_TIMER) << 16)
    #define PM_QS_PAINT         (QS_PAINT << 16)
    #define PM_QS_SENDMESSAGE   (QS_SENDMESSAGE << 16)
#endif

/* Hot key modifiers */
#define MOD_ALT     0x0001
#define MOD_CONTROL 0x0002
#define MOD_SHIFT   0x0004
#define MOD_WIN     0x0008

/* Special hotkey identifiers */
#define IDHOT_SNAPWINDOW    (-1)
#define IDHOT_SNAPDESKTOP   (-2)

/* Flag used with WM_QUERYENDSESSION and WM_ENDSESSION */
#if (WINVER >= 0x0400)
    #define ENDSESSION_LOGOFF   0x80000000L
    #define ENDSESSION_CRITICAL 0x40000000L
    #define ENDSESSION_CLOSEAPP 0x00000001L
#endif

/* ExitWindowsEx() flags */
#define EWX_LOGOFF          0x00000000L
#define EWX_SHUTDOWN        0x00000001L
#define EWX_REBOOT          0x00000002L
#define EWX_FORCE           0x00000004L
#define EWX_POWEROFF        0x00000008L
#if (_WIN32_WINNT >= 0x0500)
    #define EWX_FORCEIFHUNG 0x00000010L
#endif
#define EWX_QUICKRESOLVE    0x00000020L
#if (_WIN32_WINNT >= 0x0600)
    #define EWX_RESTARTAPPS 0x00000040L
#endif

/* BroadcastSystemMessage() recipients */
#if (WINVER >= 0x0400)
    #define BSM_ALLCOMPONENTS       0x00000000L
    #define BSM_VXDS                0x00000001L
    #define BSM_NETDRIVER           0x00000002L
    #define BSM_INSTALLABLEDRIVERS  0x00000004L
    #define BSM_APPLICATIONS        0x00000008L
    #define BSM_ALLDESKTOPS         0x00000010L
#endif

/* BroadcastSystemMessage() flags */
#if (WINVER >= 0x0400)
    #define BSF_QUERY                   0x00000001L
    #define BSF_IGNORECURRENTTASK       0x00000002L
    #define BSF_FLUSHDISK               0x00000004L
    #define BSF_NOHANG                  0x00000008L
    #define BSF_POSTMESSAGE             0x00000010L
    #define BSF_FORCEIFHUNG             0x00000020L
    #define BSF_NOTIMEOUTIFNOTHUNG      0x00000040L
    #if (_WIN32_WINNT >= 0x0500)
        #define BSF_ALLOWSFW            0x00000080L
        #define BSF_SENDNOTIFYMESSAGE   0x00000100L
    #endif
    #if (_WIN32_WINNT >= 0x0501)
        #define BSF_RETURNHDESK         0x00000200L
        #define BSF_LUID                0x00000400L
    #endif
#endif

/* Value returned in response to system messages */
#if (WINVER >= 0x0400)
    #define BROADCAST_QUERY_DENY    0x424D5144L
#endif

/* Device notification flags */
#if (WINVER >= 0x0500)
    #define DEVICE_NOTIFY_WINDOW_HANDLE             0x00000000L
    #define DEVICE_NOTIFY_SERVICE_HANDLE            0x00000001L
    #if (_WIN32_WINNT >= 0x0501)
        #define DEVICE_NOTIFY_ALL_INTERFACE_CLASSES 0x00000004L
    #endif
#endif

/* Special window handle value used with PostMessage() and SendMessage() */
#define HWND_BROADCAST  ((HWND)0xFFFF)

/* Special window handle specified as a parent for message-only windows */
#if (WINVER >= 0x0500)
    #define HWND_MESSAGE    ((HWND)-3)
#endif

/* InSendMessageEx() return values */
#if (WINVER >= 0x0500)
    #define ISMEX_NOSEND    0x00000000L
    #define ISMEX_SEND      0x00000001L
    #define ISMEX_NOTIFY    0x00000002L
    #define ISMEX_CALLBACK  0x00000004L
    #define ISMEX_REPLIED   0x00000008L
#endif

/* Special value used with CreateWindow() */
#define CW_USEDEFAULT   0x80000000

/* Window handle for the desktop */
#define HWND_DESKTOP    0

/* PrintWindow() flags */
#if (_WIN32_WINNT >= 0x0501)
    #define PW_CLIENTONLY   0x00000001
#endif

/* Layered window attributes */
#if (_WIN32_WINNT >= 0x0500)
    #define LWA_COLORKEY    0x00000001L
    #define LWA_ALPHA       0x00000002L
#endif

/* UpdateLayeredWindow() flags */
#if (_WIN32_WINNT >= 0x0500)
    #define ULW_COLORKEY    0x00000001L
    #define ULW_ALPHA       0x00000002L
    #define ULW_OPAQUE      0x00000004L
    #define ULW_EX_NORESIZE 0x00000008L
#endif

/* FlashWindowEx() flags */
#if (WINVER >= 0x0500)
    #define FLASHW_STOP         0x00000000L
    #define FLASHW_CAPTION      0x00000001L
    #define FLASHW_TRAY         0x00000002L
    #define FLASHW_ALL          (FLASHW_CAPTION | FLASHW_TRAY)
    #define FLASHW_TIMER        0x00000004L
    #define FLASHW_TIMERNOFG    0x0000000CL
#endif

/* SetWindowPos() flags */
#define SWP_NOSIZE              0x0001
#define SWP_NOMOVE              0x0002
#define SWP_NOZORDER            0x0004
#define SWP_NOREDRAW            0x0008
#define SWP_NOACTIVATE          0x0010
#define SWP_FRAMECHANGED        0x0020
#define SWP_SHOWWINDOW          0x0040
#define SWP_HIDEWINDOW          0x0080
#define SWP_NOCOPYBITS          0x0100
#define SWP_NOOWNERZORDER       0x0200
#define SWP_NOSENDCHANGING      0x0400
#define SWP_DRAWFRAME           SWP_FRAMECHANGED
#define SWP_NOREPOSITION        SWP_NOOWNERZORDER
#if (WINVER >= 0x0400)
    #define SWP_DEFERERASE      0x2000
    #define SWP_ASYNCWINDOWPOS  0x4000
#endif

/* Special window handles used with SetWindowPos() */
#define HWND_TOP        ((HWND)0)
#define HWND_BOTTOM     ((HWND)1)
#define HWND_TOPMOST    ((HWND)-1)
#define HWND_NOTOPMOST  ((HWND)-2)

/* Extra bytes for dialog window classes */
#define DLGWINDOWEXTRA  30

/* keybd_event() flags */
#define KEYEVENTF_EXTENDEDKEY   0x00000001L
#define KEYEVENTF_KEYUP         0x00000002L
#if (_WIN32_WINNT >= 0x0500)
    #define KEYEVENTF_UNICODE   0x00000004L
    #define KEYEVENTF_SCANCODE  0x00000008L
#endif

/* mouse_event() flags */
#define MOUSEEVENTF_MOVE                0x00000001L
#define MOUSEEVENTF_LEFTDOWN            0x00000002L
#define MOUSEEVENTF_LEFTUP              0x00000004L
#define MOUSEEVENTF_RIGHTDOWN           0x00000008L
#define MOUSEEVENTF_RIGHTUP             0x00000010L
#define MOUSEEVENTF_MIDDLEDOWN          0x00000020L
#define MOUSEEVENTF_MIDDLEUP            0x00000040L
#define MOUSEEVENTF_XDOWN               0x00000080L
#define MOUSEEVENTF_XUP                 0x00000100L
#define MOUSEEVENTF_WHEEL               0x00000800L
#if (_WIN32_WINNT >= 0x0600)
    #define MOUSEEVENTF_HWHEEL          0x00001000L
#endif
#if (WINVER >= 0x0600)
    #define MOUSEEVENTF_MOVE_NOCOALESCE 0x00002000L
#endif
#define MOUSEEVENTF_VIRTUALDESK         0x00004000L
#define MOUSEEVENTF_ABSOLUTE            0x00008000L

/* Input types */
#if (_WIN32_WINNT > 0x0400)
    #define INPUT_MOUSE     0L
    #define INPUT_KEYBOARD  1L
    #define INPUT_HARDWARE  2L
#endif

/* MapVirtualKeyEx() mapping types */
#define MAPVK_VK_TO_VSC         0
#define MAPVK_VSC_TO_VK         1
#define MAPVK_VK_TO_CHAR        2
#define MAPVK_VSC_TO_VK_EX      3
#if (WINVER >= 0x0600)
    #define MAPVK_VK_TO_VSC_EX  4
#endif

/* MsgWaitForMultipleObjects() flags */
#define MWMO_WAITALL        0x00000001L
#define MWMO_ALERTABLE      0x00000002L
#define MWMO_INPUTAVAILABLE 0x00000004L

/* Minimum and maximum timer durations */
#define USER_TIMER_MAXIMUM  0x7FFFFFFFL
#define USER_TIMER_MINUMUM  0x0000000AL

/* GetSystemMetrics() indices */
#define SM_CXSCREEN                         0
#define SM_CYSCREEN                         1
#define SM_CXVSCROLL                        2
#define SM_CYHSCROLL                        3
#define SM_CYCAPTION                        4
#define SM_CXBORDER                         5
#define SM_CYBORDER                         6
#define SM_CXDLGFRAME                       7
#define SM_CYDLGFRAME                       8
#define SM_CYVTHUMB                         9
#define SM_CXHTHUMB                         10
#define SM_CXICON                           11
#define SM_CYICON                           12
#define SM_CXCURSOR                         13
#define SM_CYCURSOR                         14
#define SM_CYMENU                           15
#define SM_CXFULLSCREEN                     16
#define SM_CYFULLSCREEN                     17
#define SM_CYKANJIWINDOW                    18
#define SM_MOUSEPRESENT                     19
#define SM_CYVSCROLL                        20
#define SM_CXHSCROLL                        21
#define SM_DEBUG                            22
#define SM_SWAPBUTTON                       23
#define SM_CXMIN                            28
#define SM_CYMIN                            29
#define SM_CXSIZE                           30
#define SM_CYSIZE                           31
#define SM_CXFRAME                          32
#define SM_CYFRAME                          33
#define SM_CXMINTRACK                       34
#define SM_CYMINTRACK                       35
#define SM_CXDOUBLECLK                      36
#define SM_CYDOUBLECLK                      37
#define SM_CXICONSPACING                    38
#define SM_CYICONSPACING                    39
#define SM_MENUDROPALIGNMENT                40
#define SM_PENWINDOWS                       41
#define SM_DBCSENABLED                      42
#define SM_CMOUSEBUTTONS                    43
#if (WINVER >= 0x0400)
    #define SM_CXFIXEDFRAME                 SM_CXDLGFRAME
    #define SM_CYFIXEDFRAME                 SM_CYDLGFRAME
    #define SM_CXSIZEFRAME                  SM_CXFRAME
    #define SM_CYSIZEFRAME                  SM_CYFRAME
    #define SM_SECURE                       44
    #define SM_CXEDGE                       45
    #define SM_CYEDGE                       46
    #define SM_CXMINSPACING                 47
    #define SM_CYMINSPACING                 48
    #define SM_CXSMICON                     49
    #define SM_CYSMICON                     50
    #define SM_CYSMCAPTION                  51
    #define SM_CXSMSIZE                     52
    #define SM_CYSMSIZE                     53
    #define SM_CXMENUSIZE                   54
    #define SM_CYMENUSIZE                   55
    #define SM_ARRANGE                      56
    #define SM_CXMINIMIZED                  57
    #define SM_CYMINIMIZED                  58
    #define SM_CXMAXTRACK                   59
    #define SM_CYMAXTRACK                   60
    #define SM_CXMAXIMIZED                  61
    #define SM_CYMAXIMIZED                  62
    #define SM_NETWORK                      63
    #define SM_CLEANBOOT                    67
    #define SM_CXDRAG                       68
    #define SM_CYDRAG                       69
#endif
#define SM_SHOWSOUNDS                       70
#if (WINVER >= 0x0400)
    #define SM_CXMENUCHECK                  71
    #define SM_CYMENUCHECK                  72
    #define SM_SLOWMACHINE                  73
    #define SM_MIDEASTENABLED               74
#endif
#if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
    #define SM_MOUSEWHEELPRESENT            75
#endif
#if (WINVER >= 0x0500)
    #define SM_XVIRTUALSCREEN               76
    #define SM_YVIRTUALSCREEN               77
    #define SM_CXVIRTUALSCREEN              78
    #define SM_CYVIRTUALSCREEN              79
    #define SM_CMONITORS                    80
    #define SM_SAMEDISPLAYFORMAT            81
#endif
#if (_WIN32_WINNT >= 0x0500)
    #define SM_IMMENABLED                   82
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define SM_CXFOCUSBORDER                83
    #define SM_CYFOCUSBORDER                84
    #define SM_TABLETPC                     86
    #define SM_MEDIACENTER                  87
    #define SM_STARTER                      88
    #define SM_SERVERR2                     89
#endif
#if (_WIN32_WINNT >= 0x0600)
    #define SM_MOUSEHORIZONTALWHEELPRESENT  91
    #define SM_CXPADDEDBORDER               92
#endif
#if (WINVER >= 0x0600)
    #define SM_CMETRICS                     93
#elif (WINVER >= 0x0501)
    #define SM_CMETRICS                     90
#elif (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
    #define SM_CMETRICS                     83
#else
    #define SM_CMETRICS                     76
#endif
#if (WINVER >= 0x0500)
    #define SM_REMOTESESSION                0x1000
    #if (_WIN32_WINNT >= 0x0501)
        #define SM_SHUTTINGDOWN             0x2000
    #endif
#endif
#if (WINVER >= 0x0501)
    #define SM_REMOTECONTROL                0x2001
    #define SM_CARETBLINKINGENABLED         0x2002
#endif

/* WM_MENUCHAR return values */
#if (WINVER >= 0x0400)
    #define MNC_IGNORE  0
    #define MNC_CLOSE   1
    #define MNC_EXECUTE 2
    #define MNC_SELECT  3
#endif

/* Menu styles */
#if (WINVER >= 0x0500)
    #define MNS_NOCHECK     0x80000000L
    #define MNS_MODELESS    0x40000000L
    #define MNS_DRAGDROP    0x20000000L
    #define MNS_AUTODISMISS 0x10000000L
    #define MNS_NOTIFYBYPOS 0x08000000L
    #define MNS_CHECKORBMP  0x04000000L
#endif

/* Menu information mask flags */
#if (WINVER >= 0x0500)
    #define MIM_MAXHEIGHT       0x00000001L
    #define MIM_BACKGROUND      0x00000002L
    #define MIM_HELPID          0x00000004L
    #define MIM_MENUDATA        0x00000008L
    #define MIM_STYLE           0x00000010L
    #define MIM_APPLYTOSUBMENUS 0x80000000L
#endif

/* WM_MENUDRAG return values */
#if (WINVER >= 0x0500)
    #define MND_CONTINUE    0L
    #define MND_ENDMENU     1L
#endif

/* WM_MENUGETOBJECT flags */
#if (WINVER >= 0x0500)
    #define MNGOF_TOPGAP    0x00000001L
    #define MNGOF_BOTTOMGAP 0x00000002L
#endif

/* WM_MENUGETOBJECT return values */
#if (WINVER >= 0x0500)
    #define MNGO_NOINTERFACE    0x00000000L
    #define MNGO_NOERROR        0x00000001L
#endif

/* Menu item information mask flags */
#if (WINVER >= 0x0400)
    #define MIIM_STATE      0x00000001L
    #define MIIM_ID         0x00000002L
    #define MIIM_SUBMENU    0x00000004L
    #define MIIM_CHECKMARKS 0x00000008L
    #define MIIM_TYPE       0x00000010L
    #define MIIM_DATA       0x00000020L
#endif
#if (WINVER >= 0x0500)
    #define MIIM_STRING     0x00000040L
    #define MIIM_BITMAP     0x00000080L
    #define MIIM_FTYPE      0x00000100L
#endif

/* Special bitmap handles used with menu items */
#if (WINVER >= 0x0500)
    #define HBMMENU_CALLBACK        ((HBITMAP)-1)
    #define HBMMENU_SYSTEM          ((HBITMAP)1)
    #define HBMMENU_MBAR_RESTORE    ((HBITMAP)2)
    #define HBMMENU_MBAR_MINIMIZE   ((HBITMAP)3)
    #define HBMMENU_MBAR_CLOSE      ((HBITMAP)5)
    #define HBMMENU_MBAR_CLOSE_D    ((HBITMAP)6)
    #define HBMMENU_MBAR_MINIMIZE_D ((HBITMAP)7)
    #define HBMMENU_POPUP_CLOSE     ((HBITMAP)8)
    #define HBMMENU_POPUP_RESTORE   ((HBITMAP)9)
    #define HBMMENU_POPUP_MAXIMIZE  ((HBITMAP)10)
    #define HBMMENU_POPUP_MINIMIZE  ((HBITMAP)11)
#endif

/* GetMenuDefaultItem() flags */
#if (WINVER >= 0x0400)
    #define GMDI_USEDISABLED    0x00000001
    #define GMDI_GOINTOPOPUPS   0x00000002
#endif

/* TrackPopupMenu() flags */
#define TPM_LEFTBUTTON          0x0000
#define TPM_RIGHTBUTTON         0x0002
#define TPM_LEFTALIGN           0x0000
#define TPM_CENTERALIGN         0x0004
#define TPM_RIGHTALIGN          0x0008
#if (WINVER >= 0x0400)
    #define TPM_TOPALIGN        0x0000
    #define TPM_VCENTERALIGN    0x0010
    #define TPM_BOTTOMALIGN     0x0020
    #define TPM_HORIZONTAL      0x0000
    #define TPM_VERTICAL        0x0040
    #define TPM_NONOTIFY        0x0080
    #define TPM_RETURNCMD       0x0100
#endif
#if (WINVER >= 0x0500)
    #define TPM_RECURSE         0x0001
    #define TPM_HORPOSANIMATION 0x0400
    #define TPM_HORNEGANIMATION 0x0800
    #define TPM_VERPOSANIMATION 0x1000
    #define TPM_VERNEGANIMATION 0x2000
    #if (_WIN32_WINNT >= 0x0500)
        #define TPM_NOANIMATION 0x4000
    #endif
    #if (_WIN32_WINNT >= 0x0501)
        #define TPM_LAYOUTRTL   0x8000
    #endif
#endif

/* DragObject() flags */
#if (WINVER >= 0x0400)
    #define DOF_EXECUTABLE  0x00008001L
    #define DOF_DOCUMENT    0x00008002L
    #define DOF_DIRECTORY   0x00008003L
    #define DOF_MULTIPLE    0x00008004L
    #define DOF_PROGMAN     0x00000001L
    #define DOF_SHELLDATA   0x00000002L
#endif

/* DragObject() data formats */
#if (WINVER >= 0x0400)
    #define DO_DROPFILE     0x454C4946
    #define DO_PRINTFILE    0x544E5250
#endif

/* DrawText() flags */
#define DT_TOP                      0x00000000
#define DT_LEFT                     0x00000000
#define DT_CENTER                   0x00000001
#define DT_RIGHT                    0x00000002
#define DT_VCENTER                  0x00000004
#define DT_BOTTOM                   0x00000008
#define DT_WORDBREAK                0x00000010
#define DT_SINGLELINE               0x00000020
#define DT_EXPANDTABS               0x00000040
#define DT_TABSTOP                  0x00000080
#define DT_NOCLIP                   0x00000100
#define DT_EXTERNALLEADING          0x00000200
#define DT_CALCRECT                 0x00000400
#define DT_NOPREFIX                 0x00000800
#define DT_INTERNAL                 0x00001000
#if (WINVER >= 0x0400)
    #define DT_EDITCONTROL          0x00002000
    #define DT_PATH_ELLIPSIS        0x00004000
    #define DT_END_ELLIPSIS         0x00008000
    #define DT_MODIFYSTRING         0x00010000
    #define DT_RTLREADING           0x00020000
    #define DT_WORD_ELLIPSIS        0x00040000
#endif
#if (WINVER >= 0x0500)
    #define DT_NOFULLWIDTHCHARBREAK 0x00080000
    #if (_WIN32_WINNT >= 0x0500)
        #define DT_HIDEPREFIX       0x00100000
        #define DT_PREFIXONLY       0x00200000
    #endif
#endif

/* DrawState() types */
#if (WINVER >= 0x0400)
    #define DST_COMPLEX     0x0000
    #define DST_TEXT        0x0001
    #define DST_PREFIXTEXT  0x0002
    #define DST_ICON        0x0003
    #define DST_BITMAP      0x0004
#endif

/* DrawState() states */
#if (WINVER >= 0x0400)
    #define DSS_NORMAL          0x0000
    #define DSS_UNION           0x0010
    #define DSS_DISABLED        0x0020
    #define DSS_MONO            0x0080
    #if (_WIN32_WINNT >= 0x0500)
        #define DSS_HIDEPREFIX  0x0200
        #define DSS_PREFIXONLY  0x0400
    #endif
    #define DSS_RIGHT           0x8000
#endif

/* LockSetForegroundWindow() lock codes */
#if (_WIN32_WINNT >= 0x0500)
    #define LSFW_LOCK   1
    #define LSFW_UNLOCK 2
#endif

/* GetDCEx() flags */
#define DCX_WINDOW              0x00000001L
#define DCX_CACHE               0x00000002L
#define DCX_NORESETATTRS        0x00000004L
#define DCX_CLIPCHILDREN        0x00000008L
#define DCX_CLIPSIBLINGS        0x00000010L
#define DCX_PARENTCLIP          0x00000020L
#define DCX_EXCLUDERGN          0x00000040L
#define DCX_INTERSECTRGN        0x00000080L
#define DCX_EXCLUDEUPDATE       0x00000100L
#define DCX_INTERSECTUPDATE     0x00000200L
#define DCX_LOCKWINDOWUPDATE    0x00000400L
#define DCX_VALIDATE            0x00200000L

/* Maximum number of monitors */
#if (WINVER >= 0x0600)
    #define MONITORS_MAX    10
#endif

/* RedrawWindow() flags */
#define RDW_INVALIDATE      0x0001
#define RDW_INTERNALPAINT   0x0002
#define RDW_ERASE           0x0004
#define RDW_VALIDATE        0x0008
#define RDW_NOINTERNALPAINT 0x0010
#define RDW_NOERASE         0x0020
#define RDW_NOCHILDREN      0x0040
#define RDW_ALLCHILDREN     0x0080
#define RDW_UPDATENOW       0x0100
#define RDW_ERASENOW        0x0200
#define RDW_FRAME           0x0400
#define RDW_NOFRAME         0x0800

/* ScrollWindowEx() flags */
#define SW_SCROLLCHILDREN   0x0001
#define SW_INVALIDATE       0x0002
#define SW_ERASE            0x0004
#if (WINVER >= 0x0500)
    #define SW_SMOOTHSCROLL 0x0010
#endif

/* EnableScrollBar() flags */
#define ESB_ENABLE_BOTH     0x0000
#define ESB_DISABLE_BOTH    0x0003
#define ESB_DISABLE_LEFT    0x0001
#define ESB_DISABLE_RIGHT   0x0002
#define ESB_DISABLE_UP      0x0001
#define ESB_DISABLE_DOWN    0x0002
#define ESB_DISABLE_LTUP    ESB_DISABLE_LEFT
#define ESB_DISABLE_RTDN    ESB_DISABLE_RIGHT

/* Help context types */
#define HELPINFO_WINDOW     0x0001
#define HELPINFO_MENUITEM   0x0002

/* MessageBox() flags */
#define MB_OK                           0x00000000L
#define MB_OKCANCEL                     0x00000001L
#define MB_ABORTRETRYIGNORE             0x00000002L
#define MB_YESNOCANCEL                  0x00000003L
#define MB_YESNO                        0x00000004L
#define MB_RETRYCANCEL                  0x00000005L
#if (WINVER >= 0x0500)
    #define MB_CANCELTRYCONTINUE        0x00000006L
#endif
#define MB_ICONHAND                     0x00000010L
#define MB_ICONQUESTION                 0x00000020L
#define MB_ICONEXCLAMATION              0x00000030L
#define MB_ICONASTERISK                 0x00000040L
#if (WINVER >= 0x0400)
    #define MB_USERICON                 0x00000080L
    #define MB_ICONWARNING              MB_ICONEXCLAMATION
    #define MB_ICONERROR                MB_ICONHAND
#endif
#define MB_ICONINFORMATION              MB_ICONASTERISK
#define MB_ICONSTOP                     MB_ICONHAND
#define MB_DEFBUTTON1                   0x00000000L
#define MB_DEFBUTTON2                   0x00000100L
#define MB_DEFBUTTON3                   0x00000200L
#if (WINVER >= 0x0400)
    #define MB_DEFBUTTON4               0x00000300L
#endif
#define MB_APPLMODAL                    0x00000000L
#define MB_SYSTEMMODAL                  0x00001000L
#define MB_TASKMODAL                    0x00002000L
#if (WINVER >= 0x0400)
    #define MB_HELP                     0x00004000L
#endif
#define MB_NOFOCUS                      0x00008000L
#define MB_SETFOREGROUND                0x00010000L
#define MB_DEFAULT_DESKTOP_ONLY         0x00020000L
#if (WINVER >= 0x0400)
    #define MB_TOPMOST                  0x00040000L
    #define MB_RIGHT                    0x00080000L
    #define MB_RTLREADING               0x00100000L
#endif
#if (_WIN32_WINNT >= 0x0400)
    #define MB_SERVICE_NOTIFICATION     0x00200000L
#else
    #define MB_SERVICE_NOTIFICATION     0x00040000L
#endif
#define MB_SERVICE_NOTIFICATION_NT3X    0x00040000L
#define MB_TYPEMASK                     0x0000000FL
#define MB_ICONMASK                     0x000000F0L
#define MB_DEFMASK                      0x00000F00L
#define MB_MODEMASK                     0x00003000L
#define MB_MISCMASK                     0x0000C000L

/* ChildWindowFromPointEx() flags */
#if (WINVER >= 0x0400)
    #define CWP_ALL             0x0000
    #define CWP_SKIPINVISIBLE   0x0001
    #define CWP_SKIPDISABLED    0x0002
    #define CWP_SKIPTRANSPARENT 0x0004
#endif

/* Control color types for compatibility */
#define CTLCOLOR_MSGBOX     0
#define CTLCOLOR_EDIT       1
#define CTLCOLOR_LISTBOX    2
#define CTLCOLOR_BTN        3
#define CTLCOLOR_DLG        4
#define CTLCOLOR_SCROLLBAR  5
#define CTLCOLOR_STATIC     6
#define CTLCOLOR_MAX        7

/* System color indices */
#define COLOR_SCROLLBAR                     0
#define COLOR_BACKGROUND                    1
#define COLOR_ACTIVECAPTION                 2
#define COLOR_INACTIVECAPTION               3
#define COLOR_MENU                          4
#define COLOR_WINDOW                        5
#define COLOR_WINDOWFRAME                   6
#define COLOR_MENUTEXT                      7
#define COLOR_WINDOWTEXT                    8
#define COLOR_CAPTIONTEXT                   9
#define COLOR_ACTIVEBORDER                  10
#define COLOR_INACTIVEBORDER                11
#define COLOR_APPWORKSPACE                  12
#define COLOR_HIGHLIGHT                     13
#define COLOR_HIGHLIGHTTEXT                 14
#define COLOR_BTNFACE                       15
#define COLOR_BTNSHADOW                     16
#define COLOR_GRAYTEXT                      17
#define COLOR_BTNTEXT                       18
#define COLOR_INACTIVECAPTIONTEXT           19
#define COLOR_BTNHIGHLIGHT                  20
#if (WINVER >= 0x0400)
    #define COLOR_3DDKSHADOW                21
    #define COLOR_3DLIGHT                   22
    #define COLOR_INFOTEXT                  23
    #define COLOR_INFOBK                    24
#endif
#if (WINVER >= 0x0500)
    #define COLOR_HOTLIGHT                  26
    #define COLOR_GRADIENTACTIVECAPTION     27
    #define COLOR_GARDIENTINACTIVECAPTION   28
#endif
#if (WINVER >= 0x0501)
    #define COLOR_MENUHILIGHT               29
    #define COLOR_MENUBAR                   30
#endif
#if (WINVER >= 0x0400)
    #define COLOR_DESKTOP                   COLOR_BACKGROUND
    #define COLOR_3DFACE                    COLOR_BTNFACE
    #define COLOR_3DSHADOW                  COLOR_BTNSHADOW
    #define COLOR_3DHIGHLIGHT               COLOR_BTNHIGHLIGHT
    #define COLOR_3DHILIGHT                 COLOR_BTNHIGHLIGHT
    #define COLOR_BTNHILIGHT                COLOR_BTNHIGHLIGHT
#endif

/* GetWindow() commands */
#define GW_HWNDFIRST        0
#define GW_HWNDLAST         1
#define GW_HWNDNEXT         2
#define GW_HWNDPREV         3
#define GW_OWNER            4
#define GW_CHILD            5
#if (WINVER >= 0x0500)
    #define GW_ENABLEDPOPUP 6
    #define GW_MAX          6
#else
    #define GW_MAX          5
#endif

/* Menu flags */
#define MF_INSERT           0x00000000
#define MF_CHANGE           0x00000080
#define MF_APPEND           0x00000100
#define MF_DELETE           0x00000200
#define MF_REMOVE           0x00001000
#define MF_BYCOMMAND        0x00000000
#define MF_BYPOSITION       0x00000400
#define MF_SEPARATOR        0x00000800
#define MF_ENABLED          0x00000000
#define MF_GRAYED           0x00000001
#define MF_DISABLED         0x00000002
#define MF_UNCHECKED        0x00000000
#define MF_CHECKED          0x00000008
#define MF_USECHECKBITMAPS  0x00000200
#define MF_STRING           0x00000000
#define MF_BITMAP           0x00000004
#define MF_OWNERDRAW        0x00000100
#define MF_POPUP            0x00000010
#define MF_MENUBARBREAK     0x00000020
#define MF_MENUBREAK        0x00000040
#define MF_UNHILITE         0x00000000
#define MF_HILITE           0x00000080
#if (WINVER >= 0x0400)
    #define MF_DEFAULT      0x00001000
#endif
#define MF_SYSMENU          0x00002000
#define MF_HELP             0x00004000
#if (WINVER >= 0x0400)
    #define MF_RIGHTJUSTIFY 0x00004000
#endif
#define MF_MOUSESELECT      0x00008000
#if (WINVER >= 0x0400)
    #define MF_END          0x00000080
#endif

/* Menu types */
#if (WINVER >= 0x0400)
    #define MFT_STRING          MF_STRING
    #define MFT_BITMAP          MF_BITMAP
    #define MFT_MENUBARBREAK    MF_MENUBARBREAK
    #define MFT_MENUBREAK       MF_MENUBREAK
    #define MFT_OWNERDRAW       MF_OWNERDRAW
    #define MFT_RADIOCHECK      0x00000200
    #define MFT_SEPARATOR       MF_SEPARATOR
    #define MFT_RIGHTORDER      0x00002000
    #define MFT_RIGHTJUSTIFY    MF_RIGHTJUSTIFY
#endif

/* Menu states */
#if (WINVER >= 0x0400)
    #define MFS_GRAYED      0x00000003L
    #define MFS_DISABLED    MFS_GRAYED
    #define MFS_CHECKED     MF_CHECKED
    #define MFS_HILITE      MF_HILITE
    #define MFS_ENABLED     MF_ENABLED
    #define MFS_UNCHECKED   MF_UNCHECKED
    #define MFS_UNHILITE    MF_UNHILITE
    #define MFS_DEFAULT     MF_DEFAULT
#endif

/* Special values used in menu resources */
#define MF_END  0x00000080

/* System command identifiers */
#define SC_SIZE             0xF000
#define SC_MOVE             0xF010
#define SC_MINIMIZE         0xF020
#define SC_MAXIMIZE         0xF030
#define SC_NEXTWINDOW       0xF040
#define SC_PREVWINDOW       0xF050
#define SC_CLOSE            0xF060
#define SC_VSCROLL          0xF070
#define SC_HSCROLL          0xF080
#define SC_MOUSEMENU        0xF090
#define SC_KEYMENU          0xF100
#define SC_ARRANGE          0xF110
#define SC_RESTORE          0xF120
#define SC_TASKLIST         0xF130
#define SC_SCREENSAVE       0xF140
#define SC_HOTKEY           0xF150
#if (WINVER >= 0x0400)
    #define SC_DEFAULT      0xF160
    #define SC_MONITORPOWER 0xF170
    #define SC_CONTEXTHELP  0xF180
    #define SC_SEPARATOR    0xF00F
#endif
#define SC_ICON             SC_MINIMIZE
#define SC_ZOOM             SC_MAXIMIZE

/* System command flags */
#if (WINVER >= 0x0600)
    #define SCF_ISSECURE    0x00000001
#endif

/* Standard cursor identifiers */
#define IDC_ARROW       MAKEINTRESOURCE( 32512 )
#define IDC_IBEAM       MAKEINTRESOURCE( 32513 )
#define IDC_WAIT        MAKEINTRESOURCE( 32514 )
#define IDC_CROSS       MAKEINTRESOURCE( 32515 )
#define IDC_UPARROW     MAKEINTRESOURCE( 32516 )
#define IDC_SIZE        MAKEINTRESOURCE( 32640 )
#define IDC_ICON        MAKEINTRESOURCE( 32641 )
#define IDC_SIZENWSE    MAKEINTRESOURCE( 32642 )
#define IDC_SIZENESW    MAKEINTRESOURCE( 32643 )
#define IDC_SIZEWE      MAKEINTRESOURCE( 32644 )
#define IDC_SIZENS      MAKEINTRESOURCE( 32645 )
#define IDC_SIZEALL     MAKEINTRESOURCE( 32646 )
#define IDC_NO          MAKEINTRESOURCE( 32648 )
#if (WINVER >= 0x0500)
    #define IDC_HAND    MAKEINTRESOURCE( 32649 )
#endif
#define IDC_APPSTARTING MAKEINTRESOURCE( 32650 )
#if (WINVER >= 0x0400)
    #define IDC_HELP    MAKEINTRESOURCE( 32651 )
#endif

/* Image types */
#define IMAGE_BITMAP            0
#define IMAGE_ICON              1
#define IMAGE_CURSOR            2
#if (WINVER >= 0x0400)
    #define IMAGE_ENHMETAFILE   3
#endif

/* LoadImage() flags */
#if (WINVER >= 0x0400)
    #define LR_DEFAULTCOLOR     0x0000
    #define LR_MONOCHROME       0x0001
    #define LR_COLOR            0x0002
    #define LR_COPYRETURNORG    0x0004
    #define LR_COPYDELETEORG    0x0008
    #define LR_LOADFROMFILE     0x0010
    #define LR_LOADTRANSPARENT  0x0020
    #define LR_DEFAULTSIZE      0x0040
    #define LR_VGACOLOR         0x0080
    #define LR_LOADMAP3DCOLORS  0x1000
    #define LR_CREATEDIBSECTION 0x2000
    #define LR_COPYFROMRESOURCE 0x4000
    #define LR_SHARED           0x8000
#endif

/* DrawIconEx() flags */
#if (WINVER >= 0x0400)
    #define DI_MASK         0x0001
    #define DI_IMAGE        0x0002
    #define DI_NORMAL       0x0003
    #define DI_COMPAT       0x0004
    #define DI_DEFAULTSIZE  0x0008
    #if (_WIN32_WINNT >= 0x0501)
        #define DI_NOMIRROR 0x0010
    #endif
#endif

/* Values used to distinguish between icon and cursor files */
#if (WINVER >= 0x0400)
    #define RES_ICON    1
    #define RES_CURSOR  2
#endif

/* OEM bitmap resource identifiers */
#ifdef OEMRESOURCE
    #define OBM_CLOSE       32754
    #define OBM_UPARROW     32753
    #define OBM_DNARROW     32752
    #define OBM_RGARROW     32751
    #define OBM_LFARROW     32750
    #define OBM_REDUCE      32749
    #define OBM_ZOOM        32748
    #define OBM_RESTORE     32747
    #define OBM_REDUCED     32746
    #define OBM_ZOOMD       32745
    #define OBM_RESTORED    32744
    #define OBM_UPARROWD    32743
    #define OBM_DNARROWD    32742
    #define OBM_RGARROWD    32741
    #define OBM_LFARROWD    32740
    #define OBM_MNARROW     32739
    #define OBM_COMBO       32738
    #define OBM_UPARROWI    32737
    #define OBM_DNARROWI    32736
    #define OBM_RGARROWI    32735
    #define OBM_LFARROWI    32734
    #define OBM_OLD_CLOSE   32767
    #define OBM_SIZE        32766
    #define OBM_OLD_UPARROW 32765
    #define OBM_OLD_DNARROW 32764
    #define OBM_OLD_RGARROW 32763
    #define OBM_OLD_LFARROW 32762
    #define OBM_BTSIZE      32761
    #define OBM_CHECK       32760
    #define OBM_CHECKBOXES  32759
    #define OBM_BTNCORNERS  32758
    #define OBM_OLD_REDUCE  32757
    #define OBM_OLD_ZOOM    32756
    #define OBM_OLD_RESTORE 32755
#endif

/* OEM cursor resource identifiers */
#ifdef OEMRESOURCE
    #define OCR_NORMAL          32512
    #define OCR_IBEAM           32513
    #define OCR_WAIT            32514
    #define OCR_CROSS           32515
    #define OCR_UP              32516
    #define OCR_SIZE            32640
    #define OCR_ICON            32641
    #define OCR_SIZENWSE        32642
    #define OCR_SIZENESW        32643
    #define OCR_SIZEWE          32644
    #define OCR_SIZENS          32645
    #define OCR_SIZEALL         32646
    #define OCR_ICOCUR          32647
    #define OCR_NO              32648
    #if (WINVER >= 0x0500)
        #define OCR_HAND        32649
    #endif
    #if (WINVER >= 0x0400)
        #define OCR_APPSTARTING 32650
    #endif
#endif

/* OEM icon resource identifiers */
#ifdef OEMRESOURCE
    #define OIC_SAMPLE          32512
    #define OIC_HAND            32513
    #define OIC_QUES            32514
    #define OIC_BANG            32515
    #define OIC_NOTE            32516
    #if (WINVER >= 0x0400)
        #define OIC_WINLOGO     32517
        #define OIC_WARNING     OIC_BANG
        #define OIC_ERROR       OIC_HAND
        #define OIC_INFORMATION OIC_NOTE
    #endif
    #if (WINVER >= 0x0600)
        #define OIC_SHIELD      32518
    #endif
#endif

/* Entry point ordinal for language drivers */
#define ORD_LANGDRIVER  1

/* Standard icon identifiers */
#define IDI_APPLICATION     MAKEINTRESOURCE( 32512 )
#define IDI_HAND            MAKEINTRESOURCE( 32513 )
#define IDI_QUESTION        MAKEINTRESOURCE( 32514 )
#define IDI_EXCLAMATION     MAKEINTRESOURCE( 32515 )
#define IDI_ASTERISK        MAKEINTRESOURCE( 32516 )
#if (WINVER >= 0x0400)
    #define IDI_WINLOGO     MAKEINTRESOURCE( 32517 )
    #define IDI_WARNING     IDI_EXCLAMATION
    #define IDI_ERROR       IDI_HAND
    #define IDI_INFORMATION IDI_ASTERISK
#endif
#if (WINVER >= 0x0600)
    #define IDI_SHIELD      MAKEINTRESOURCE( 32518 )
#endif

/* Dialog box button identifiers */
#define IDOK            1
#define IDCANCEL        2
#define IDABORT         3
#define IDRETRY         4
#define IDIGNORE        5
#define IDYES           6
#define IDNO            7
#if (WINVER >= 0x0400)
    #define IDCLOSE     8
    #define IDHELP      9
#endif
#if (WINVER >= 0x0500)
    #define IDTRYAGAIN  10
    #define IDCONTINUE  11
#endif

/* Edit control styles */
#define ES_LEFT         0x0000L
#define ES_CENTER       0x0001L
#define ES_RIGHT        0x0002L
#define ES_MULTILINE    0x0004L
#define ES_UPPERCASE    0x0008L
#define ES_LOWERCASE    0x0010L
#define ES_PASSWORD     0x0020L
#define ES_AUTOVSCROLL  0x0040L
#define ES_AUTOHSCROLL  0x0080L
#define ES_NOHIDESEL    0x0100L
#define ES_OEMCONVERT   0x0400L
#define ES_READONLY     0x0800L
#define ES_WANTRETURN   0x1000L
#if (WINVER >= 0x0400)
    #define ES_NUMBER   0x2000L
#endif

/* Edit control notification codes */
#define EN_SETFOCUS         0x0100
#define EN_KILLFOCUS        0x0200
#define EN_CHANGE           0x0300
#define EN_UPDATE           0x0400
#define EN_ERRSPACE         0x0500
#define EN_MAXTEXT          0x0501
#define EN_HSCROLL          0x0601
#define EN_VSCROLL          0x0602
#if (_WIN32_WINNT >= 0x0500)
    #define EN_ALIGN_LTR_EC 0x0700
    #define EN_ALIGN_RTL_EC 0x0701
#endif

/* EM_SETMARGINS parameter values */
#if (WINVER >= 0x0400)
    #define EC_LEFTMARGIN   0x0001
    #define EC_RIGHTMARGIN  0x0002
    #define EC_USEFONTINFO  0xFFFF
#endif

/* EM_SETIMESTATUS types */
#if (WINVER >= 0x0500)
    #define EMSIS_COMPOSITIONSTRING 0x0001
#endif

/* EMSIS_COMPOSITIONSTRING flags */
#if (WINVER >= 0x0500)
    #define EIMES_GETCOMPSTRATONCE          0x0001
    #define EIMES_CANCELCOMPSTRINFOCUS      0x0002
    #define EIMES_COMPLETECOMPSTRKILLFOCUS  0x0004
#endif

/* Edit control messages */
#define EM_GETSEL               0x00B0
#define EM_SETSEL               0x00B1
#define EM_GETRECT              0x00B2
#define EM_SETRECT              0x00B3
#define EM_SETRECTNP            0x00B4
#define EM_SCROLL               0x00B5
#define EM_LINESCROLL           0x00B6
#define EM_SCROLLCARET          0x00B7
#define EM_GETMODIFY            0x00B8
#define EM_SETMODIFY            0x00B9
#define EM_GETLINECOUNT         0x00BA
#define EM_LINEINDEX            0x00BB
#define EM_SETHANDLE            0x00BC
#define EM_GETHANDLE            0x00BD
#define EM_GETTHUMB             0x00BE
#define EM_LINELENGTH           0x00C1
#define EM_REPLACESEL           0x00C2
#define EM_GETLINE              0x00C4
#define EM_LIMITTEXT            0x00C5
#define EM_CANUNDO              0x00C6
#define EM_UNDO                 0x00C7
#define EM_FMTLINES             0x00C8
#define EM_LINEFROMCHAR         0x00C9
#define EM_SETTABSTOPS          0x00CB
#define EM_SETPASSWORDCHAR      0x00CC
#define EM_EMPTYUNDOBUFFER      0x00CD
#define EM_GETFIRSTVISIBLELINE  0x00CE
#define EM_SETREADONLY          0x00CF
#define EM_SETWORDBREAKPROC     0x00D0
#define EM_GETWORDBREAKPROC     0x00D1
#define EM_GETPASSWORDCHAR      0x00D2
#if (WINVER >= 0x0400)
    #define EM_SETMARGINS       0x00D3
    #define EM_GETMARGINS       0x00D4
    #define EM_SETLIMITTEXT     EM_LIMITTEXT
    #define EM_GETLIMITTEXT     0x00D5
    #define EM_POSFROMCHAR      0x00D6
    #define EM_CHARFROMPOS      0x00D7
#endif
#if (WINVER >= 0x0500)
    #define EM_SETIMESTATUS     0x00D8
    #define EM_GETIMESTATUS     0x00D9
#endif

/* Word break procedure codes */
#define WB_LEFT         0
#define WB_RIGHT        1
#define WB_ISDELIMITER  2

/* Button control styles */
#define BS_PUSHBUTTON       0x0000L
#define BS_DEFPUSHBUTTON    0x0001L
#define BS_CHECKBOX         0x0002L
#define BS_AUTOCHECKBOX     0x0003L
#define BS_RADIOBUTTON      0x0004L
#define BS_3STATE           0x0005L
#define BS_AUTO3STATE       0x0006L
#define BS_GROUPBOX         0x0007L
#define BS_USERBUTTON       0x0008L
#define BS_AUTORADIOBUTTON  0x0009L
#define BS_PUSHBOX          0x000AL
#define BS_OWNERDRAW        0x000BL
#define BS_TYPEMASK         0x000FL
#define BS_LEFTTEXT         0x0020L
#if (WINVER >= 0x0400)
    #define BS_TEXT         0x0000L
    #define BS_ICON         0x0040L
    #define BS_BITMAP       0x0080L
    #define BS_LEFT         0x0100L
    #define BS_RIGHT        0x0200L
    #define BS_CENTER       0x0300L
    #define BS_TOP          0x0400L
    #define BS_BOTTOM       0x0800L
    #define BS_VCENTER      0x0C00L
    #define BS_PUSHLIKE     0x1000L
    #define BS_MULTILINE    0x2000L
    #define BS_NOTIFY       0x4000L
    #define BS_FLAT         0x8000L
    #define BS_RIGHTBUTTON  BS_LEFTTEXT
#endif

/* Button control notification codes */
#define BN_CLICKED          0
#define BN_PAINT            1
#define BN_HILITE           2
#define BN_UNHILITE         3
#define BN_DISABLE          4
#define BN_DOUBLECLICKED    5
#if (WINVER >= 0x0400)
    #define BN_PUSHED       BN_HILITE
    #define BN_UNPUSHED     BN_UNHILITE
    #define BN_DBLCLK       BN_DOUBLECLICKED
    #define BN_SETFOCUS     6
    #define BN_KILLFOCUS    7
#endif

/* Button control messages */
#define BM_GETCHECK         0x00F0
#define BM_SETCHECK         0x00F1
#define BM_GETSTATE         0x00F2
#define BM_SETSTATE         0x00F3
#define BM_SETSTYLE         0x00F4
#if (WINVER >= 0x0400)
    #define BM_CLICK        0x00F5
    #define BM_GETIMAGE     0x00F6
    #define BM_SETIMAGE     0x00F7
#endif
#if (WINVER >= 0x0600)
    #define BM_SETDONTCLICK 0x00F8
#endif

/* Button control states */
#if (WINVER >= 0x0400)
    #define BST_UNCHECKED       0x0000
    #define BST_CHECKED         0x0001
    #define BST_INDETERMINATE   0x0002
    #define BST_PUSHED          0x0004
    #define BST_FOCUS           0x0008
#endif

/* Static control styles */
#define SS_LEFT                 0x0000L
#define SS_CENTER               0x0001L
#define SS_RIGHT                0x0002L
#define SS_ICON                 0x0003L
#define SS_BLACKRECT            0x0004L
#define SS_GRAYRECT             0x0005L
#define SS_WHITERECT            0x0006L
#define SS_BLACKFRAME           0x0007L
#define SS_GRAYFRAME            0x0008L
#define SS_WHITEFRAME           0x0009L
#define SS_USERITEM             0x000AL
#define SS_SIMPLE               0x000BL
#define SS_LEFTNOWORDWRAP       0x000CL
#if (WINVER >= 0x0400)
    #define SS_OWNERDRAW        0x000DL
    #define SS_BITMAP           0x000EL
    #define SS_ENHMETAFILE      0x000FL
    #define SS_ETCHEDHORZ       0x0010L
    #define SS_ETCHEDVERT       0x0011L
    #define SS_ETCHEDFRAME      0x0012L
    #define SS_TYPEMASK         0x001FL
#endif
#if (WINVER >= 0x0501)
    #define SS_REALSIZECONTROL  0x0040L
#endif
#define SS_NOPREFIX             0x0080L
#if (WINVER >= 0x0400)
    #define SS_NOTIFY           0x0100L
    #define SS_CENTERIMAGE      0x0200L
    #define SS_RIGHTJUST        0x0400L
    #define SS_REALSIZEIMAGE    0x0800L
    #define SS_SUNKEN           0x1000L
    #define SS_EDITCONTROL      0x2000L
    #define SS_ENDELLIPSIS      0x4000L
    #define SS_PATHELLIPSIS     0x8000L
    #define SS_WORDELLIPSIS     0xC000L
    #define SS_ELLIPSISMASK     0xC000L
#endif

/* Static control messages */
#define STM_SETICON         0x0170
#define STM_GETICON         0x0171
#if (WINVER >= 0x0400)
    #define STM_SETIMAGE    0x0172
    #define STM_GETIMAGE    0x0173
#endif
#define STM_MSGMAX          0x0174

/* Static control notification codes */
#if (WINVER >= 0x0400)
    #define STN_CLICKED 0
    #define STN_DBLCLK  1
    #define STN_ENABLE  2
    #define STN_DISABLE 3
#endif

/* Window classes for dialog boxes */
#define WC_DIALOG   MAKEINTATOM( 0x8002 )

/* GetWindowLong() offsets for dialog boxes */
#define DWL_MSGRESULT   0
#define DWL_DLGPROC     4
#define DWL_USER        8

/* GetWindowLongPtr() offsets for dialog boxes */
#define DWLP_MSGRESULT  0
#define DWLP_DLGPROC    (DWLP_MSGRESULT + sizeof( LRESULT ))
#define DWLP_USER       (DWLP_DLGPROC + sizeof( FARPROC ))

/* DlgDirList() flags */
#define DDL_READWRITE   0x0000
#define DDL_READONLY    0x0001
#define DDL_HIDDEN      0x0002
#define DDL_SYSTEM      0x0004
#define DDL_DIRECTORY   0x0010
#define DDL_ARCHIVE     0x0020
#define DDL_POSTMSGS    0x2000
#define DDL_DRIVES      0x4000
#define DDL_EXCLUSIVE   0x8000

/* Dialog box styles */
#define DS_ABSALIGN         0x0001L
#define DS_SYSMODAL         0x0002L
#define DS_LOCALEDIT        0x0020L
#define DS_SETFONT          0x0040L
#define DS_MODALFRAME       0x0080L
#define DS_NOIDLEMSG        0x0100L
#define DS_SETFOREGROUND    0x0200L
#if (WINVER >= 0x0400)
    #define DS_3DLOOK       0x0004L
    #define DS_FIXEDSYS     0x0008L
    #define DS_NOFAILCREATE 0x0010L
    #define DS_CONTROL      0x0400L
    #define DS_CENTER       0x0800L
    #define DS_CENTERMOUSE  0x1000L
    #define DS_CONTEXTHELP  0x2000L
    #define DS_SHELLFONT    (DS_SETFONT | DS_FIXEDSYS)
#endif

/* Dialog box messages */
#define DM_GETDEFID         (WM_USER + 0)
#define DM_SETDEFID         (WM_USER + 1)
#if (WINVER >= 0x0400)
    #define DM_REPOSITION   (WM_USER + 2)
#endif

/* Constant returned in high word by DM_GETDEFID */
#define DC_HASDEFID 0x534B

/* Dialog codes */
#define DLGC_WANTARROWS         0x0001
#define DLGC_WANTTAB            0x0002
#define DLGC_WANTALLKEYS        0x0004
#define DLGC_WANTMESSAGE        0x0004
#define DLGC_HASSETSEL          0x0008
#define DLGC_DEFPUSHBUTTON      0x0010
#define DLGC_UNDEFPUSHBUTTON    0x0020
#define DLGC_RADIOBUTTON        0x0040
#define DLGC_WANTCHARS          0x0080
#define DLGC_STATIC             0x0100
#define DLGC_BUTTON             0x2000

/* List box control message return values */
#define LB_OKAY     0
#define LB_ERR      (-1)
#define LB_ERRSPACE (-2)

/* List box control notification codes */
#define LBN_ERRSPACE    (-2)
#define LBN_SELCHANGE   1
#define LBN_DBLCLK      2
#define LBN_SELCANCEL   3
#define LBN_SETFOCUS    4
#define LBN_KILLFOCUS   5

/* List box control messages */
#define LB_ADDSTRING            0x0180
#define LB_INSERTSTRING         0x0181
#define LB_DELETESTRING         0x0182
#define LB_SELITEMRANGEEX       0x0183
#define LB_RESETCONTENT         0x0184
#define LB_SETSEL               0x0185
#define LB_SETCURSEL            0x0186
#define LB_GETSEL               0x0187
#define LB_GETCURSEL            0x0188
#define LB_GETTEXT              0x0189
#define LB_GETTEXTLEN           0x018A
#define LB_GETCOUNT             0x018B
#define LB_SELECTSTRING         0x018C
#define LB_DIR                  0x018D
#define LB_GETTOPINDEX          0x018E
#define LB_FINDSTRING           0x018F
#define LB_GETSELCOUNT          0x0190
#define LB_GETSELITEMS          0x0191
#define LB_SETTABSTOPS          0x0192
#define LB_GETHORIZONTALEXTENT  0x0193
#define LB_SETHORIZONTALEXTENT  0x0194
#define LB_SETCOLUMNWIDTH       0x0195
#define LB_ADDFILE              0x0196
#define LB_SETTOPINDEX          0x0197
#define LB_GETITEMRECT          0x0198
#define LB_GETITEMDATA          0x0199
#define LB_SETITEMDATA          0x019A
#define LB_SELITEMRANGE         0x019B
#define LB_SETANCHORINDEX       0x019C
#define LB_GETANCHORINDEX       0x019D
#define LB_SETCARETINDEX        0x019E
#define LB_GETCARETINDEX        0x019F
#define LB_SETITEMHEIGHT        0x01A0
#define LB_GETITEMHEIGHT        0x01A1
#define LB_FINDSTRINGEXACT      0x01A2
#define LB_SETLOCALE            0x01A5
#define LB_GETLOCALE            0x01A6
#define LB_SETCOUNT             0x01A7
#if (WINVER >= 0x0400)
    #define LB_INITSTORAGE      0x01A8
    #define LB_ITEMFROMPOINT    0x01A9
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define LB_GETLISTBOXINFO   0x01B2
    #define LB_MSGMAX           0x01B3
#elif (WINVER >= 0x0400)
    #define LB_MSGMAX           0x01B0
#else
    #define LB_MSGMAX           0x01A8
#endif

/* List box control styles */
#define LBS_NOTIFY              0x0001L
#define LBS_SORT                0x0002L
#define LBS_NOREDRAW            0x0004L
#define LBS_MULTIPLESEL         0x0008L
#define LBS_OWNERDRAWFIXED      0x0010L
#define LBS_OWNERDRAWVARIABLE   0x0020L
#define LBS_HASSTRINGS          0x0040L
#define LBS_USETABSTOPS         0x0080L
#define LBS_NOINTEGRALHEIGHT    0x0100L
#define LBS_MULTICOLUMN         0x0200L
#define LBS_WANTKEYBOARDINPUT   0x0400L
#define LBS_EXTENDEDSEL         0x0800L
#define LBS_DISABLENOSCROLL     0x1000L
#define LBS_NODATA              0x2000L
#if (WINVER >= 0x0400)
    #define LBS_NOSEL           0x4000L
#endif
#define LBS_COMBOBOX            0x8000L
#define LBS_STANDARD            (LBS_NOTIFY | LBS_SORT | WS_VSCROLL | WS_BORDER)

/* Combo box control message return values */
#define CB_OKAY     0
#define CB_ERR      (-1)
#define CB_ERRSPACE (-2)

/* Combo box control notification codes */
#define CBN_ERRSPACE        (-1)
#define CBN_SELCHANGE       1
#define CBN_DBLCLK          2
#define CBN_SETFOCUS        3
#define CBN_KILLFOCUS       4
#define CBN_EDITCHANGE      5
#define CBN_EDITUPDATE      6
#define CBN_DROPDOWN        7
#define CBN_CLOSEUP         8
#define CBN_SELENDOK        9
#define CBN_SELENDCANCEL    10

/* Combo box control styles */
#define CBS_SIMPLE              0x0001L
#define CBS_DROPDOWN            0x0002L
#define CBS_DROPDOWNLIST        0x0003L
#define CBS_OWNERDRAWFIXED      0x0010L
#define CBS_OWNERDRAWVARIABLE   0x0020L
#define CBS_AUTOHSCROLL         0x0040L
#define CBS_OEMCONVERT          0x0080L
#define CBS_SORT                0x0100L
#define CBS_HASSTRINGS          0x0200L
#define CBS_NOINTEGRALHEIGHT    0x0400L
#define CBS_DISABLENOSCROLL     0x0800L
#if (WINVER >= 0x0400)
    #define CBS_UPPERCASE       0x2000L
    #define CBS_LOWERCASE       0x4000L
#endif

/* Combo box control messages */
#define CB_GETEDITSEL               0x0140
#define CB_LIMITTEXT                0x0141
#define CB_SETEDITSEL               0x0142
#define CB_ADDSTRING                0x0143
#define CB_DELETESTRING             0x0144
#define CB_DIR                      0x0145
#define CB_GETCOUNT                 0x0146
#define CB_GETCURSEL                0x0147
#define CB_GETLBTEXT                0x0148
#define CB_GETLBTEXTLEN             0x0149
#define CB_INSERTSTRING             0x014A
#define CB_RESETCONTENT             0x014B
#define CB_FINDSTRING               0x014C
#define CB_SELECTSTRING             0x014D
#define CB_SETCURSEL                0x014E
#define CB_SHOWDROPDOWN             0x014F
#define CB_GETITEMDATA              0x0150
#define CB_SETITEMDATA              0x0151
#define CB_GETDROPPEDCONTROLRECT    0x0152
#define CB_SETITEMHEIGHT            0x0153
#define CB_GETITEMHEIGHT            0x0154
#define CB_SETEXTENDEDUI            0x0155
#define CB_GETEXTENDEDUI            0x0156
#define CB_GETDROPPEDSTATE          0x0157
#define CB_FINDSTRINGEXACT          0x0158
#define CB_SETLOCALE                0x0159
#define CB_GETLOCALE                0x015A
#if (WINVER >= 0x0400)
    #define CB_GETTOPINDEX          0x015B
    #define CB_SETTOPINDEX          0x015C
    #define CB_GETHORIZONTALEXTENT  0x015D
    #define CB_SETHORIZONTALEXTENT  0x015E
    #define CB_GETDROPPEDWIDTH      0x015F
    #define CB_SETDROPPEDWIDTH      0x0160
    #define CB_INITSTORAGE          0x0161
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define CB_GETCOMBOBOXINFO      0x0164
    #define CB_MSGMAX               0x0165
#elif (WINVER >= 0x0400)
    #define CB_MSGMAX               0x0162
#else
    #define CB_MSGMAX               0x015B
#endif

/* Scroll bar control styles */
#define SBS_HORZ                    0x0000L
#define SBS_VERT                    0x0001L
#define SBS_TOPALIGN                0x0002L
#define SBS_LEFTALIGN               0x0002L
#define SBS_BOTTOMALIGN             0x0004L
#define SBS_RIGHTALIGN              0x0004L
#define SBS_SIZEBOXTOPLEFTALIGN     0x0002L
#define SBS_SIZEBOXBOTTOMRIGHTALIGN 0x0004L
#define SBS_SIZEBOX                 0x0008L
#if (WINVER >= 0x0400)
    #define SBS_SIZEGRIP            0x0010L
#endif

/* Scroll bar control messages */
#define SBM_SETPOS                  0x00E0
#define SBM_GETPOS                  0x00E1
#define SBM_SETRANGE                0x00E2
#define SBM_SETRANGEREDRAW          0x00E6
#define SBM_GETRANGE                0x00E3
#define SBM_ENABLE_ARROWS           0x00E4
#if (WINVER >= 0x0400)
    #define SBM_SETSCROLLINFO       0x00E9
    #define SBM_GETSCROLLINFO       0x00EA
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define SBM_GETSCROLLBARINFO    0x00EB
#endif

/* Scroll information mask flags */
#if (WINVER >= 0x0400)
    #define SIF_RANGE           0x0001
    #define SIF_PAGE            0x0002
    #define SIF_POS             0x0004
    #define SIF_DISABLENOSCROLL 0x0008
    #define SIF_TRACKPOS        0x0010
    #define SIF_ALL             (SIF_RANGE | SIF_PAGE | SIF_POS | SIF_TRACKPOS)
#endif

/* MDI client styles */
#define MDIS_ALLCHILDSTYLES 0x0001L

/* WM_MDITILE/WM_MDICASCADE flags */
#define MDITILE_VERTICAL        0x0000
#define MDITILE_HORIZONTAL      0x0001
#define MDITILE_SKIPDISABLED    0x0002
#if (_WIN32_WINNT >= 0x0500)
    #define MDITILE_ZORDER      0x0004
#endif

/* WinHelp() commands */
#define HELP_CONTEXT                0x00000001L
#define HELP_QUIT                   0x00000002L
#define HELP_INDEX                  0x00000003L
#define HELP_CONTENTS               0x00000003L
#define HELP_HELPONHELP             0x00000004L
#define HELP_SETINDEX               0x00000005L
#define HELP_SETCONTENTS            0x00000005L
#define HELP_CONTEXTPOPUP           0x00000008L
#define HELP_FORCEFILE              0x00000009L
#define HELP_KEY                    0x00000101L
#define HELP_COMMAND                0x00000102L
#define HELP_PARTIALKEY             0x00000105L
#define HELP_MULTIKEY               0x00000201L
#define HELP_SETWINPOS              0x00000203L
#if (WINVER >= 0x0400)
    #define HELP_CONTEXTMENU        0x0000000AL
    #define HELP_FINDER             0x0000000BL
    #define HELP_WM_HELP            0x0000000CL
    #define HELP_SETPOPUP_POS       0x0000000DL
    #define HELP_TCARD              0x00008000L
    #define HELP_TCARD_DATA         0x00000010L
    #define HELP_TCARD_OTHER_CALLER 0x00000011L
#endif

/* Help identifiers */
#if (WINVER >= 0x0400)
    #define IDH_NO_HELP             28440
    #define IDH_MISSING_CONTEXT     28441
    #define IDH_GENERIC_HELP_BUTTON 28442
    #define IDH_OK                  28443
    #define IDH_CANCEL              28444
    #define IDH_HELP                28445
#endif

/* GetGuiResources() flags */
#if (WINVER >= 0x0500)
    #define GR_GDIOBJECTS   0L
    #define GR_USEROBJECTS  1L
#endif

/* SystemParametersInfo() commands */
#define SPI_GETBEEP                             0x0001
#define SPI_SETBEEP                             0x0002
#define SPI_GETMOUSE                            0x0003
#define SPI_SETMOUSE                            0x0004
#define SPI_GETBORDER                           0x0005
#define SPI_SETBORDER                           0x0006
#define SPI_GETKEYBOARDSPEED                    0x000A
#define SPI_SETKEYBOARDSPEED                    0x000B
#define SPI_LANGDRIVER                          0x000C
#define SPI_ICONHORIZONTALSPACING               0x000D
#define SPI_GETSCREENSAVETIMEOUT                0x000E
#define SPI_SETSCREENSAVETIMEOUT                0x000F
#define SPI_GETSCREENSAVEACTIVE                 0x0010
#define SPI_SETSCREENSAVEACTIVE                 0x0011
#define SPI_GETGRIDGRANULARITY                  0x0012
#define SPI_SETGRIDGRANULARITY                  0x0013
#define SPI_SETDESKWALLPAPER                    0x0014
#define SPI_SETDESKPATTERN                      0x0015
#define SPI_GETKEYBOARDDELAY                    0x0016
#define SPI_SETKEYBOARDDELAY                    0x0017
#define SPI_ICONVERTICALSPACING                 0x0018
#define SPI_GETICONTITLEWRAP                    0x0019
#define SPI_SETICONTITLEWRAP                    0x001A
#define SPI_GETMENUDROPALIGNMENT                0x001B
#define SPI_SETMENUDROPALIGNMENT                0x001C
#define SPI_SETDOUBLECLKWIDTH                   0x001D
#define SPI_SETDOUBLECLKHEIGHT                  0x001E
#define SPI_GETICONTITLELOGFONT                 0x001F
#define SPI_SETDOUBLECLICKTIME                  0x0020
#define SPI_SETMOUSEBUTTONSWAP                  0x0021
#define SPI_SETICONTITLELOGFONT                 0x0022
#define SPI_GETFASTTASKSWITCH                   0x0023
#define SPI_SETFASTTASKSWITCH                   0x0024
#if (WINVER >= 0x0400)
    #define SPI_SETDRAGFULLWINDOWS              0x0025
    #define SPI_GETDRAGFULLWINDOWS              0x0026
    #define SPI_GETNONCLIENTMETRICS             0x0029
    #define SPI_SETNONCLIENTMETRICS             0x002A
    #define SPI_GETMINIMIZEDMETRICS             0x002B
    #define SPI_SETMINIMIZEDMETRICS             0x002C
    #define SPI_GETICONMETRICS                  0x002D
    #define SPI_SETICONMETRICS                  0x002E
    #define SPI_SETWORKAREA                     0x002F
    #define SPI_GETWORKAREA                     0x0030
    #define SPI_SETPENWINDOWS                   0x0031
    #define SPI_GETHIGHCONTRAST                 0x0042
    #define SPI_SETHIGHCONTRAST                 0x0043
    #define SPI_GETKEYBOARDPREF                 0x0044
    #define SPI_SETKEYBOARDPREF                 0x0045
    #define SPI_GETSCREENREADER                 0x0046
    #define SPI_SETSCREENREADER                 0x0047
    #define SPI_GETANIMATION                    0x0048
    #define SPI_SETANIMATION                    0x0049
    #define SPI_GETFONTSMOOTHING                0x004A
    #define SPI_SETFONTSMOOTHING                0x004B
    #define SPI_SETDRAGWIDTH                    0x004C
    #define SPI_SETDRAGHEIGHT                   0x004D
    #define SPI_SETHANDHELD                     0x004E
    #define SPI_GETLOWPOWERTIMEOUT              0x004F
    #define SPI_GETPOWEROFFTIMEOUt              0x0050
    #define SPI_SETLOWPOWERTIMEOUT              0x0051
    #define SPI_SETPOWEROFFTIMEOUT              0x0052
    #define SPI_GETLOWPOWERACTIVE               0x0053
    #define SPI_GETPOWEROFFACTIVE               0x0054
    #define SPI_SETLOWPOWERACTIVE               0x0055
    #define SPI_SETPOWEROFFACTIVE               0x0056
    #define SPI_SETCURSORS                      0x0057
    #define SPI_SETICONS                        0x0058
    #define SPI_GETDEFAULTINPUTLANG             0x0059
    #define SPI_SETDEFAULTINPUTLANG             0x005A
    #define SPI_SETLANGTOGGLE                   0x005B
    #define SPI_GETWINDOWSEXTENSION             0x005C
    #define SPI_SETMOUSETRAILS                  0x005D
    #define SPI_GETMOUSETRAILS                  0x005E
    #define SPI_SETSCREENSAVERRUNNING           0x0061
    #define SPI_SCREENSAVERRUNNING              SPI_SETSCREENSAVERRUNNING
#endif
#define SPI_GETFILTERKEYS                       0x0032
#define SPI_SETFILTERKEYS                       0x0033
#define SPI_GETTOGGLEKEYS                       0x0034
#define SPI_SETTOGGLEKEYS                       0x0035
#define SPI_GETMOUSEKEYS                        0x0036
#define SPI_SETMOUSEKEYS                        0x0037
#define SPI_GETSHOWSOUNDS                       0x0038
#define SPI_SETSHOWSOUNDS                       0x0039
#define SPI_GETSTICKYKEYS                       0x003A
#define SPI_SETSTICKYKEYS                       0x003B
#define SPI_GETACCESSTIMEOUT                    0x003C
#define SPI_SETACCESSTIMEOUT                    0x003D
#if (WINVER >= 0x0400)
    #define SPI_GETSERIALKEYS                   0x003E
    #define SPI_SETSERIALKEYS                   0x003F
#endif
#define SPI_GETSOUNDSENTRY                      0x0040
#define SPI_SETSOUNDSENTRY                      0x0041
#if (_WIN32_WINNT >= 0x0400)
    #define SPI_GETSNAPTODEFBUTTON              0x005F
    #define SPI_SETSNAPTODEFBUTTON              0x0060
#endif
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
    #define SPI_GETMOUSEHOVERWIDTH              0x0062
    #define SPI_SETMOUSEHOVERWIDTH              0x0063
    #define SPI_GETMOUSEHOVERHEIGHT             0x0064
    #define SPI_SETMOUSEHOVERHEIGHT             0x0065
    #define SPI_GETMOUSEHOVERTIME               0x0066
    #define SPI_SETMOUSEHOVERTIME               0x0067
    #define SPI_GETWHEELSCROLLLINES             0x0068
    #define SPI_SETWHEELSCROLLLINES             0x0069
    #define SPI_GETMENUSHOWDELAY                0x006A
    #define SPI_SETMENUSHOWDELAY                0x006B
#endif
#if (_WIN32_WINNT >= 0x0600)
    #define SPI_GETWHEELSCROLLCHARS             0x006C
    #define SPI_SETWHEELSCROLLCHARS             0x006D
#endif
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
    #define SPI_GETSHOWIMEUI                    0x006E
    #define SPI_SETSHOWIMEUI                    0x006F
#endif
#if (WINVER >= 0x0500)
    #define SPI_GETMOUSESPEED                   0x0070
    #define SPI_SETMOUSESPEED                   0x0071
    #define SPI_GETSCREENSAVERRUNNING           0x0072
    #define SPI_GETDESKWALLPAPER                0x0073
#endif
#if (WINVER >= 0x0600)
    #define SPI_GETAUDIODESCRIPTION             0x0074
    #define SPI_SETAUDIODESCRIPTION             0x0075
    #define SPI_GETSCREENSAVESECURE             0x0076
    #define SPI_SETSCREENSAVESECURE             0x0077
#endif
#if (WINVER >= 0x0500)
    #define SPI_GETACTIVEWINDOWTRACKING         0x1000
    #define SPI_SETACTIVEWINDOWTRACKING         0x1001
    #define SPI_GETMENUANIMATION                0x1002
    #define SPI_SETMENUANIMATION                0x1003
    #define SPI_GETCOMBOBOXANIMATION            0x1004
    #define SPI_SETCOMBOBOXANIMATION            0x1005
    #define SPI_GETLISTBOXSMOOTHSCROLLING       0x1006
    #define SPI_SETLISTBOXSMOOTHSCROLLING       0x1007
    #define SPI_GETGRADIENTCAPTIONS             0x1008
    #define SPI_SETGRADIENTCAPTIONS             0x1009
    #define SPI_GETKEYBOARDCUES                 0x100A
    #define SPI_SETKEYBOARDCUES                 0x100B
    #define SPI_GETMENUUNDERLINES               SPI_GETKEYBOARDCUES
    #define SPI_SETMENUUNDERLINES               SPI_SETKEYBOARDCUES
    #define SPI_GETACTIVEWNDTRKZORDER           0x100C
    #define SPI_SETACTIVEWNDTRKZORDER           0x100D
    #define SPI_GETHOTTRACKING                  0x100E
    #define SPI_SETHOTTRACKING                  0x100F
    #define SPI_GETMENUFADE                     0x1012
    #define SPI_SETMENUFADE                     0x1013
    #define SPI_GETSELECTIONFADE                0x1014
    #define SPI_SETSELECTIONFADE                0x1015
    #define SPI_GETTOOLTIPANIMATION             0x1016
    #define SPI_SETTOOLTIPANIMATION             0x1017
    #define SPI_GETTOOLTIPFADE                  0x1018
    #define SPI_SETTOOLTIPFADE                  0x1019
    #define SPI_GETCURSORSHADOW                 0x101A
    #define SPI_SETCURSORSHADOW                 0x101B
    #if (_WIN32_WINNT >= 0x0501)
        #define SPI_GETMOUSESONAR               0x101C
        #define SPI_SETMOUSESONAR               0x101D
        #define SPI_GETMOUSECLICKLOCK           0x101E
        #define SPI_SETMOUSECLICKLOCK           0x101F
        #define SPI_GETMOUSEVANISH              0x1020
        #define SPI_SETMOUSEVANISH              0x1021
        #define SPI_GETFLATMENU                 0x1022
        #define SPI_SETFLATMENU                 0x1023
        #define SPI_GETDROPSHADOW               0x1024
        #define SPI_SETDROPSHADOW               0x1025
        #define SPI_GETBLOCKSENDINPUTRESETS     0x1026
        #define SPI_SETBLOCKSENDINPUTRESETS     0x1027
    #endif
    #define SPI_GETUIEFFECTS                    0x103E
    #define SPI_SETUIEFFECTS                    0x103F
    #if (_WIN32_WINNT >= 0x0600)
        #define SPI_GETDISABLEOVERLAPPEDCONTENT 0x1040
        #define SPI_SETDISABLEOVERLAPPEDCONTENT 0x1041
        #define SPI_GETCLIENTAREANIMATION       0x1042
        #define SPI_SETCLIENTAREANIMATION       0x1043
        #define SPI_GETCLEARTYPE                0x1048
        #define SPI_SETCLEARTYPE                0x1049
        #define SPI_GETSPEECHRECOGNITION        0x104A
        #define SPI_SETSPEECHRECOGNITION        0x104B
    #endif
    #define SPI_GETFOREGROUNDLOCKTIMEOUT        0x2000
    #define SPI_SETFOREGROUNDLOCKTIMEOUT        0x2001
    #define SPI_GETACTIVEWNDTRKTIMEOUT          0x2002
    #define SPI_SETACTIVEWNDTRKTIMEOUT          0x2003
    #define SPI_GETFOREGROUNDFLASHCOUNT         0x2004
    #define SPI_SETFOREGROUNDFLASHCOUNT         0x2005
    #define SPI_GETCARETWIDTH                   0x2006
    #define SPI_SETCARETWIDTH                   0x2007
    #if (_WIN32_WINNT >= 0x0501)
        #define SPI_GETMOUSECLICKLOCKTIME       0x2008
        #define SPI_SETMOUSECLICKLOCKTIME       0x2009
        #define SPI_GETFONTSMOOTHINGTYPE        0x200A
        #define SPI_SETFONTSMOOTHINGTYPE        0x200B
        #define SPI_GETFONTSMOOTHINGCONTRAST    0x200C
        #define SPI_SETFONTSMOOTHINGCONTRAST    0x200D
        #define SPI_GETFOCUSBORDERWIDTH         0x200E
        #define SPI_SETFOCUSBORDERWIDTH         0x200F
        #define SPI_GETFOCUSBORDERHEIGHT        0x2010
        #define SPI_SETFOCUSBORDERHEIGHT        0x2011
        #define SPI_GETFONTSMOOTHINGORIENTATION 0x2012
        #define SPI_SETFONTSMOOTHINGORIENTATION 0x2013
    #endif
    #if (_WIN32_WINNT >= 0x0600)
        #define SPI_GETMINIMUMHITRADIUS         0x2014
        #define SPI_SETMINIMUMHITRADUIS         0x2015
        #define SPI_GETMESSAGEDURATION          0x2016
        #define SPI_SETMESSAGEDURATION          0x2017
    #endif
#endif

/* SystemParametersInfo() flags */
#define SPIF_UPDATEINIFILE      0x0001
#define SPIF_SENDWININICHANGE   0x0002
#define SPIF_SENDCHANGE         SPIF_SENDWININICHANGE

/* Font smoothing types */
#if (WINVER >= 0x0500) && (_WIN32_WINNT >= 0x0501)
    #define FE_FONTSMOOTHINGSTANDARD    0x0001
    #define FE_FONTSMOOTHINGCLEARTYPE   0x0002
    #define FE_FONTSMOOTHINGDOCKING     0x8000
#endif

/* Font smoothing orientations */
#if (WINVER >= 0x0500) && (_WIN32_WINNT >= 0x0501)
    #define FE_FONTSMOOTHINGORIENTATIONBGR  0x0000
    #define FE_FONTSMMOTHINGORIENTATIONRGB  0x0001
#endif

/* Minimized window arrangements */
#define ARW_BOTTOMLEFT  0x0000
#define ARW_BOTTOMRIGHT 0x0001
#define ARW_TOPLEFT     0x0002
#define ARW_TOPRIGHT    0x0003
#define ARW_STARTMASK   0x0003
#define ARW_STARTRIGHT  0x0001
#define ARW_STARTTOP    0x0002
#define ARW_LEFT        0x0000
#define ARW_RIGHT       0x0000
#define ARW_UP          0x0004
#define ARW_DOWN        0x0004
#define ARW_HIDE        0x0008

/* SerialKeys flags */
#define SERKF_SERIALKEYSON  0x00000001L
#define SERKF_AVAILABLE     0x00000002L
#define SERKF_INDICATOR     0x00000004L

/* High contrast flags */
#define HCF_HIGHCONTRASTON  0x00000001L
#define HCF_AVAILABLE       0x00000002L
#define HCF_HOTKEYACTIVE    0x00000004L
#define HCF_CONFIRMHOTKEY   0x00000008L
#define HCF_HOTKEYSOUND     0x00000010L
#define HCF_INDICATOR       0x00000020L
#define HCF_HOTKEYAVAILABLE 0x00000040L
#define HCF_LOGONDESKTOP    0x00000100L
#define HCF_DEFAULTDESKTOP  0x00000200L

/* ChangeDisplaySettings() flags */
#define CDS_UPDATEREGISTRY              0x00000001L
#define CDS_TEST                        0x00000002L
#define CDS_FULLSCREEN                  0x00000004L
#define CDS_GLOBAL                      0x00000008L
#define CDS_SETPRIMARY                  0x00000010L
#define CDS_VIDEOPARAMETERS             0x00000020L
#if (WINVER >= 0x0600)
    #define CDS_ENABLE_UNSAFE_MODES     0x00000100L
    #define CDS_DISABLE_UNSAFE_MODES    0x00000200L
#endif
#define CDS_RESET                       0x40000000L
#define CDS_NORESET                     0x10000000L

/* ChangeDisplaySettings() return values */
#define DISP_CHANGE_SUCCESSFUL      0
#define DISP_CHANGE_RESTART         1
#define DISP_CHANGE_FAILED          (-1)
#define DISP_CHANGE_BADMODE         (-2)
#define DISP_CHANGE_NOTUPDATED      (-3)
#define DISP_CHANGE_BADFLAGS        (-4)
#define DISP_CHANGE_BADPARAM        (-5)
#if (_WIN32_WINNT >= 0x0501)
    #define DISP_CHANGE_BADDUALVIEW (-6)
#endif

/* EnumDisplaySettings() modes */
#ifdef _WINGDI_
    #define ENUM_CURRENT_SETTINGS   0xFFFFFFFFL
    #define ENUM_REGISTRY_SETTINGS  0xFFFFFFFEL
#endif

/* EnumDisplaySettingsEx() flags */
#if (WINVER >= 0x0500)
    #ifdef _WINGDI_
        #define EDS_RAWMODE     0x00000002L
        #define EDS_ROTATEDMODE 0x00000004L
    #endif
#endif

/* EnumDisplayDevices() flags */
#if (WINVER >= 0x0500)
    #ifdef _WINGDI_
        #define EDD_GET_DEVICE_INTERFACE_NAME   0x00000001L
    #endif
#endif

/* FilterKeys flags */
#define FKF_FILTERKEYSON    0x00000001L
#define FKF_AVAILABLE       0x00000002L
#define FKF_HOTKEYACTIVE    0x00000004L
#define FKF_CONFIRMHOTKEY   0x00000008L
#define FKF_HOTKEYSOUND     0x00000010L
#define FKF_INDICATOR       0x00000020L
#define FKF_CLICKON         0x00000040L

/* StickyKeys flags */
#define SKF_STICKYKEYSON        0x00000001L
#define SKF_AVAILABLE           0x00000002L
#define SKF_HOTKEYACTIVE        0x00000004L
#define SKF_CONFIRMHOTKEY       0x00000008L
#define SKF_HOTKEYSOUND         0x00000010L
#define SKF_INDICATOR           0x00000020L
#define SKF_AUDIBLEFEEDBACK     0x00000040L
#define SKF_TRISTATE            0x00000080L
#define SKF_TWOKEYSOFF          0x00000100L
#if (_WIN32_WINNT >= 0x0500)
    #define SKF_LALTLATCHED     0x10000000L
    #define SKF_LCTLLATCHED     0x04000000L
    #define SKF_LSHIFTLATCHED   0x01000000L
    #define SKF_RALTLATCHED     0x20000000L
    #define SKF_RCTLLATCHED     0x08000000L
    #define SKF_RSHIFTLATCHED   0x02000000L
    #define SKF_LWINLATCHED     0x40000000L
    #define SKF_RWINLATCHED     0x80000000L
    #define SKF_LALTLOCKED      0x00100000L
    #define SKF_LCTLLOCKED      0x00040000L
    #define SKF_LSHIFTLOCKED    0x00010000L
    #define SKF_RALTLOCKED      0x00200000L
    #define SKF_RCTLLOCKED      0x00080000L
    #define SKF_RSHIFTLOCKED    0x00020000L
    #define SKF_LWINLOCKED      0x00400000L
    #define SKF_RWINLOCKED      0x00800000L
#endif

/* MouseKeys flags */
#define MKF_MOUSEKEYSON         0x00000001L
#define MKF_AVAILABLE           0x00000002L
#define MKF_HOTKEYACTIVE        0x00000004L
#define MKF_CONFIRMHOTKEY       0x00000008L
#define MKF_HOTKEYSOUND         0x00000010L
#define MKF_INDICATOR           0x00000020L
#define MKF_MODIFIERS           0x00000040L
#define MKF_REPLACENUMBERS      0x00000080L
#if (_WIN32_WINNT >= 0x0500)
    #define MKF_LEFTBUTTONSEL   0x10000000L
    #define MKF_RIGHTBUTTONSEL  0x20000000L
    #define MKF_LEFTBUTTONDOWN  0x01000000L
    #define MKF_RIGHTBUTTONDOWN 0x02000000L
    #define MKF_MOUSEMODE       0x80000000L
#endif

/* Access timeout flags */
#define ATF_TIMEOUTON       0x00000001L
#define ATF_ONOFFFEEDBACK   0x00000002L

/* SoundSentry graphical effects */
#define SSGF_NONE       0
#define SSGF_DISPLAY    3

/* SoundSentry text effects */
#define SSTF_NONE       0
#define SSTF_CHARS      1
#define SSTF_BORDER     2
#define SSTF_DISPLAY    3

/* SoundSentry window effects */
#define SSWF_NONE       0
#define SSWF_TITLE      1
#define SSWF_WINDOW     2
#define SSWF_DISPLAY    3
#define SSWF_CUSTOM     4

/* SoundSentry flags */
#define SSF_SOUNDSENTRYON   0x00000001L
#define SSF_AVAILABLE       0x00000002L
#define SSF_INDICATOR       0x00000004L

/* ToggleKeys flags */
#define TKF_TOGGLEKEYSON    0x00000001L
#define TKF_AVAILABLE       0x00000002L
#define TKF_HOTKEYACTIVE    0x00000004L
#define TKF_CONFIRMHOTKEY   0x00000008L
#define TKF_HOTKEYSOUND     0x00000010L
#define TKF_INDICATOR       0x00000020L

/* SetLastErrorEx() error types */
#define SLE_ERROR       0x00000001L
#define SLE_MINORERROR  0x00000002L
#define SLE_WARNING     0x00000003L

/* MonitorFromPoint()/MonitorFromRect()/MonitorFromWindow() flags */
#if (WINVER >= 0x0500)
    #define MONITOR_DEFAULTTONULL       0x00000000L
    #define MONITOR_DEFAULTTOPRIMARY    0x00000001L
    #define MONITOR_DEFAULTTONEAREST    0x00000002L
#endif

/* Monitor information flags */
#if (WINVER >= 0x0500)
    #define MONITORINFOF_PRIMARY    0x00000001L
#endif

/* Maximum length of a device name */
#if (WINVER >= 0x0500)
    #ifndef CCHDEVICENAME
        #define CCHDEVICENAME   32
    #endif
#endif

/* SetWinEventHook() flags */
#if (WINVER >= 0x0500)
    #define WINEVENT_OUTOFCONTEXT   0x00000000L
    #define WINEVENT_SKIPOWNTHREAD  0x00000001L
    #define WINEVENT_SKIPOWNPROCESS 0x00000002L
    #define WINEVENT_INCONTEXT      0x00000004L
#endif

/* Common object identifiers */
#if (WINVER >= 0x0500)
    #define CHILDID_SELF        0
    #define INDEXID_OBJECT      0
    #define INDEXID_CONTAINER   0
#endif

/* System object identifiers */
#if (WINVER >= 0x0500)
    #define OBJID_WINDOW            0x00000000L
    #define OBJID_SYSMENU           0xFFFFFFFFL
    #define OBJID_TITLEBAR          0xFFFFFFFEL
    #define OBJID_MENU              0xFFFFFFFDL
    #define OBJID_CLIENT            0xFFFFFFFCL
    #define OBJID_VSCROLL           0xFFFFFFFBL
    #define OBJID_HSCROLL           0xFFFFFFFAL
    #define OBJID_SIZEGRIP          0xFFFFFFF9L
    #define OBJID_CARET             0xFFFFFFF8L
    #define OBJID_CURSOR            0xFFFFFFF7L
    #define OBJID_ALERT             0xFFFFFFF6L
    #define OBJID_SOUND             0xFFFFFFF5L
    #define OBJID_QUERYCLASSNAMEIDX 0xFFFFFFF4L
    #define OBJID_NATIVEOM          0xFFFFFFF0L
#endif

/* Accessibility events */
#if (WINVER >= 0x0500)
    #define EVENT_MIN                               0x00000001L
    #define EVENT_MAX                               0x7FFFFFFFL
    #define EVENT_SYSTEM_SOUND                      0x00000001L
    #define EVENT_SYSTEM_ALERT                      0x00000002L
    #define EVENT_SYSTEM_FOREGROUND                 0x00000003L
    #define EVENT_SYSTEM_MENUSTART                  0x00000004L
    #define EVENT_SYSTEM_MENUEND                    0x00000005L
    #define EVENT_SYSTEM_MENUPOPUPSTART             0x00000006L
    #define EVENT_SYSTEM_MENUPOPUPEND               0x00000007L
    #define EVENT_SYSTEM_CAPTURESTART               0x00000008L
    #define EVENT_SYSTEM_CAPTUREEND                 0x00000009L
    #define EVENT_SYSTEM_MOVESIZESTART              0x0000000AL
    #define EVENT_SYSTEM_MOVESIZEEND                0x0000000BL
    #define EVENT_SYSTEM_CONTEXTHELPSTART           0x0000000CL
    #define EVENT_SYSTEM_CONTEXTHELPEND             0x0000000DL
    #define EVENT_SYSTEM_DRAGDROPSTART              0x0000000EL
    #define EVENT_SYSTEM_DRAGDROPEND                0x0000000FL
    #define EVENT_SYSTEM_DIALOGSTART                0x00000010L
    #define EVENT_SYSTEM_DIALOGEND                  0x00000011L
    #define EVENT_SYSTEM_SCROLLINGSTART             0x00000012L
    #define EVENT_SYSTEM_SCROLLINGEND               0x00000013L
    #define EVENT_SYSTEM_SWITCHSTART                0x00000014L
    #define EVENT_SYSTEM_SWITCHEND                  0x00000015L
    #define EVENT_SYSTEM_MINIMIZESTART              0x00000016L
    #define EVENT_SYSTEM_MINIMIZEEND                0x00000017L
    #if (_WIN32_WINNT >= 0x0600)
        #define EVENT_SYSTEM_DESKTOPSWITCH          0x00000020L
    #endif
    #if (_WIN32_WINNT >= 0x0501)
        #define EVENT_CONSOLE_CARET                 0x00004001L
        #define EVENT_CONSOLE_UPDATE_REGION         0x00004002L
        #define EVENT_CONSOLE_UPDATE_SIMPLE         0x00004003L
        #define EVENT_CONSOLE_UPDATE_SCROLL         0x00004004L
        #define EVENT_CONSOLE_LAYOUT                0x00004005L
        #define EVENT_CONSOLE_START_APPLICATION     0x00004006L
        #define EVENT_CONSOLE_END_APPLICATION       0x00004007L
    #endif
    #define EVENT_OBJECT_CREATE                     0x00008000L
    #define EVENT_OBJECT_DESTROY                    0x00008001L
    #define EVENT_OBJECT_SHOW                       0x00008002L
    #define EVENT_OBJECT_HIDE                       0x00008003L
    #define EVENT_OBJECT_REORDER                    0x00008004L
    #define EVENT_OBJECT_FOCUS                      0x00008005L
    #define EVENT_OBJECT_SELECTION                  0x00008006L
    #define EVENT_OBJECT_SELECTIONADD               0x00008007L
    #define EVENT_OBJECT_SELECTIONREMOVE            0x00008008L
    #define EVENT_OBJECT_SELECTIONWITHIN            0x00008009L
    #define EVENT_OBJECT_STATECHANGE                0x0000800AL
    #define EVENT_OBJECT_LOCATIONCHANGE             0x0000800BL
    #define EVENT_OBJECT_NAMECHANGE                 0x0000800CL
    #define EVENT_OBJECT_DESCRIPTIONCHANGE          0x0000800DL
    #define EVENT_OBJECT_VALUECHANGE                0x0000800EL
    #define EVENT_OBJECT_PARENTCHANGE               0x0000800FL
    #define EVENT_OBJECT_HELPCHANGE                 0x00008010L
    #define EVENT_OBJECT_DEFACTIONCHANGE            0x00008011L
    #define EVENT_OBJECT_ACCELERATORCHANGE          0x00008012L
    #if (_WIN32_WINNT >= 0x0600)
        #define EVENT_OBJECT_INVOKED                0x00008013L
        #define EVENT_OBJECT_TEXTSELECTIONCHANGED   0x00008014L
        #define EVENT_OBJECT_CONTENTSCROLLED        0x00008015L
    #endif
#endif

/* Console application flags */
#if (WINVER >= 0x0500) && (_WIN32_WINNT >= 0x0501)
    #define CONSOLE_APPLICATION_16BIT   0x00000001L
#endif

/* Console caret flags */
#if (WINVER >= 0x0500) && (_WIN32_WINNT >= 0x0501)
    #define CONSOLE_CARET_SELECTION 0x00000001L
    #define CONSOLE_CARET_VISIBLE   0x00000002L
#endif

/* System sounds */
#if (WINVER >= 0x0500)
    #define SOUND_SYSTEM_STARTUP        1L
    #define SOUND_SYSTEM_SHUTDOWN       2L
    #define SOUND_SYSTEM_BEEP           3L
    #define SOUND_SYSTEM_ERROR          4L
    #define SOUND_SYSTEM_QUESTION       5L
    #define SOUND_SYSTEM_WARNING        6L
    #define SOUND_SYSTEM_INFORMATION    7L
    #define SOUND_SYSTEM_MAXIMIZE       8L
    #define SOUND_SYSTEM_MINIMIZE       9L
    #define SOUND_SYSTEM_RESTOREUP      10L
    #define SOUND_SYSTEM_RESTOREDOWN    11L
    #define SOUND_SYSTEM_APPSTART       12L
    #define SOUND_SYSTEM_FAULT          13L
    #define SOUND_SYSTEM_APPEND         14L
    #define SOUND_SYSTEM_MENUCOMMAND    15L
    #define SOUND_SYSTEM_MENUPOPUP      16L
    #define CSOUND_SYSTEM               16L
#endif

/* System alerts */
#if (WINVER >= 0x0500)
    #define ALERT_SYSTEM_INFORMATIONAL  1L
    #define ALERT_SYSTEM_WARNING        2L
    #define ALERT_SYSTEM_ERROR          3L
    #define ALERT_SYSTEM_QUERY          4L
    #define ALERT_SYSTEM_CRITICAL       5L
    #define CALERT_SYSTEM               6L
#endif

/* GUI thread information flags */
#if (WINVER >= 0x0500)
    #define GUI_CARETBLINKING   0x00000001L
    #define GUI_INMOVESIZE      0x00000002L
    #define GUI_INMENUMODE      0x00000004L
    #define GUI_SYSTEMMENUMODE  0x00000008L
    #define GUI_POPUPMENUMODE   0x00000010L
    #if (_WIN32_WINNT >= 0x0501)
        #define GUI_16BITTASK   0x00000020L
    #endif
#endif

/* Default screen DPI */
#if (_WIN32_WINNT >= 0x0600)
    #define USER_DEFAULT_SCREEN_DPI 96
#endif

/* System state flags */
#if (WINVER >= 0x0500)
    #define STATE_SYSTEM_UNAVAILABLE        0x00000001L
    #define STATE_SYSTEM_SELECTED           0x00000002L
    #define STATE_SYSTEM_FOCUSED            0x00000004L
    #define STATE_SYSTEM_PRESSED            0x00000008L
    #define STATE_SYSTEM_CHECKED            0x00000010L
    #define STATE_SYSTEM_MIXED              0x00000020L
    #define STATE_SYSTEM_INDETERMINATE      STATE_SYSTEM_MIXED
    #define STATE_SYSTEM_READONLY           0x00000040L
    #define STATE_SYSTEM_HOTTRACKED         0x00000080L
    #define STATE_SYSTEM_DEFAULT            0x00000100L
    #define STATE_SYSTEM_EXPANDED           0x00000200L
    #define STATE_SYSTEM_COLLAPSED          0x00000400L
    #define STATE_SYSTEM_BUSY               0x00000800L
    #define STATE_SYSTEM_FLOATING           0x00001000L
    #define STATE_SYSTEM_MARQUEED           0x00002000L
    #define STATE_SYSTEM_ANIMATED           0x00004000L
    #define STATE_SYSTEM_INVISIBLE          0x00008000L
    #define STATE_SYSTEM_OFFSCREEN          0x00010000L
    #define STATE_SYSTEM_SIZEABLE           0x00020000L
    #define STATE_SYSTEM_MOVEABLE           0x00040000L
    #define STATE_SYSTEM_SELFVOICING        0x00080000L
    #define STATE_SYSTEM_FOCUSABLE          0x00100000L
    #define STATE_SYSTEM_SELECTABLE         0x00200000L
    #define STATE_SYSTEM_LINKED             0x00400000L
    #define STATE_SYSTEM_TRAVERSED          0x00800000L
    #define STATE_SYSTEM_MULTISELECTABLE    0x01000000L
    #define STATE_SYSTEM_EXTSELECTABLE      0x02000000L
    #define STATE_SYSTEM_ALERT_LOW          0x04000000L
    #define STATE_SYSTEM_ALERT_MEDIUM       0x08000000L
    #define STATE_SYSTEM_ALERT_HIGH         0x10000000L
    #define STATE_SYSTEM_PROTECTED          0x20000000L
    #define STATE_SYSTEM_VALID              0x3FFFFFFFL
#endif

/* Number of children of title bars and scroll bars */
#if (WINVER >= 0x0500)
    #define CCHILDREN_TITLEBAR  5
    #define CCHILDREN_SCROLLBAR 5
#endif

/* Cursor information flags */
#if (WINVER >= 0x0500)
    #define CURSOR_SHOWING  0x00000001L
#endif

/* Window status flags */
#if (WINVER >= 0x0500)
    #define WS_ACTIVECAPTION    0x00000001L
#endif

/* GetAncestor() flags */
#if (WINVER >= 0x0500)
    #define GA_PARENT       1
    #define GA_ROOT         2
    #define GA_ROOTOWNER    3
#endif

/* Raw input codes */
#if (_WIN32_WINNT >= 0x0501)
    #define RIM_INPUT       0
    #define RIM_INPUTSINK   1
#endif

/* Raw input types */
#if (_WIN32_WINNT >= 0x0501)
    #define RIM_TYPEMOUSE       0L
    #define RIM_TYPEKEYBOARD    1L
    #define RIM_TYPEHID         2L
#endif

/* Raw input mouse button state flags */
#if (_WIN32_WINNT >= 0x0501)
    #define RI_MOUSE_LEFT_BUTTON_DOWN   0x00000001L
    #define RI_MOUSE_LEFT_BUTTON_UP     0x00000002L
    #define RI_MOUSE_RIGHT_BUTTON_DOWN  0x00000004L
    #define RI_MOUSE_RIGHT_BUTTON_UP    0x00000008L
    #define RI_MOUSE_MIDDLE_BUTTON_DOWN 0x00000010L
    #define RI_MOUSE_MIDDLE_BUTTON_UP   0x00000020L
    #define RI_MOUSE_BUTTON_1_DOWN      RI_MOUSE_LEFT_BUTTON_DOWN
    #define RI_MOUSE_BUTTON_1_UP        RI_MOUSE_LEFT_BUTTON_UP
    #define RI_MOUSE_BUTTON_2_DOWN      RI_MOUSE_RIGHT_BUTTON_DOWN
    #define RI_MOUSE_BUTTON_2_UP        RI_MOUSE_RIGHT_BUTTON_UP
    #define RI_MOUSE_BUTTON_3_DOWN      RI_MOUSE_MIDDLE_BUTTON_DOWN
    #define RI_MOUSE_BUTTON_3_UP        RI_MOUSE_MIDDLE_BUTTON_UP
    #define RI_MOUSE_BUTTON_4_DOWN      0x00000040L
    #define RI_MOUSE_BUTTON_4_UP        0x00000080L
    #define RI_MOUSE_BUTTON_5_DOWN      0x00000100L
    #define RI_MOUSE_BUTTON_5_UP        0x00000200L
    #define RI_MOUSE_WHEEL              0x00000400L
#endif

/* Raw input mouse state flags */
#if (_WIN32_WINNT >= 0x0501)
    #define MOUSE_MOVE_RELATIVE         0x00000000L
    #define MOUSE_MOVE_ABSOLUTE         0x00000001L
    #define MOUSE_VIRTUAL_DESKTOP       0x00000002L
    #define MOUSE_ATTRIBUTES_CHANGED    0x00000004L
    #if (WINVER >= 0x0600)
        #define MOUSE_MOVE_NOCOALESCE   0x00000008L
    #endif
#endif

/* Keyboard overrun make code */
#if (_WIN32_WINNT >= 0x0501)
    #define KEYBOARD_OVERRUN_MAKE_CODE  0x00FF
#endif

/* Raw input keyboard flags */
#if (_WIN32_WINNT >= 0x0501)
    #define RI_KEY_MAKE             0x0000
    #define RI_KEY_BREAK            0x0001
    #define RI_KEY_E0               0x0002
    #define RI_KEY_E1               0x0004
    #define RI_KEY_TERMSRV_SET_LED  0x0008
    #define RI_KEY_TERMSRV_SHADOW   0x0010
#endif

/* GetRawInputData() flags */
#if (_WIN32_WINNT >= 0x0501)
    #define RID_INPUT   0x10000003L
    #define RID_HEADER  0x10000005L
#endif

/* Raw input device information flags */
#if (_WIN32_WINNT >= 0x0501)
    #define RIDI_PREPARSEDDATA  0x20000005L
    #define RIDI_DEVICENAME     0x20000007L
    #define RIDI_DEVICEINFO     0x2000000BL
#endif

/* Raw input device flags */
#if (_WIN32_WINNT >= 0x0501)
    #define RIDEV_REMOVE        0x00000001L
    #define RIDEV_EXCLUDE       0x00000010L
    #define RIDEV_PAGEONLY      0x00000020L
    #define RIDEV_NOLEGACY      0x00000030L
    #define RIDEV_INPUTSINK     0x00000100L
    #define RIDEV_CAPTUREMOUSE  0x00000200L
    #define RIDEV_NOHOTKEYS     0x00000200L
    #define RIDEV_APPKEYS       0x00000400L
    #define RIDEV_EXINPUTSINK   0x00001000L
    #define RIDEV_DEVNOTIFY     0x00002000L
    #define RIDEV_EXMODEMASK    0x000000F0L
#endif

/* WM_INPUT_DEVICE_CHANGE flags */
#if (_WIN32_WINNT >= 0x0501)
    #define GIDC_ARRIVAL    1
    #define GIDC_REMOVAL    2
#endif

/* ChangeWindowMessageFilter() flags */
#if (WINVER >= 0x0600)
    #define MSGFLT_ADD      1
    #define MSGFLT_REMOVE   2
#endif

/* Maximum shutdown block reason length */
#define MAX_STR_BLOCKREASON 256

/* Menu template data type */
typedef VOID            MENUTEMPLATEA;
typedef VOID            MENUTEMPLATEW;
typedef PVOID           LPMENUTEMPLATEA;
typedef PVOID           LPMENUTEMPLATEW;
#ifdef UNICODE
typedef MENUTEMPLATEW   MENUTEMPLATE;
typedef LPMENUTEMPLATEW LPMENUTEMPLATE;
#else
typedef MENUTEMPLATEA   MENUTEMPLATE;
typedef LPMENUTEMPLATEA LPMENUTEMPLATE;
#endif

/* Callback functions */
typedef INT_PTR (CALLBACK *DLGPROC)( HWND, UINT, WPARAM, LPARAM );
typedef int (CALLBACK *EDITWORDBREAKPROCA)( LPSTR, int, int, int );
typedef int (CALLBACK *EDITWORDBREAKPROCW)( LPWSTR, int, int, int );
typedef BOOL (CALLBACK *GRAYSTRINGPROC)( HDC, LPARAM, int );
typedef LRESULT (CALLBACK *HOOKPROC)( int, WPARAM, LPARAM );
typedef BOOL (CALLBACK *NAMEENUMPROCA)( LPSTR, LPARAM );
typedef BOOL (CALLBACK *NAMEENUMPROCW)( LPWSTR, LPARAM );
typedef BOOL (CALLBACK *PROPENUMPROCA)( HWND, LPCSTR, HANDLE );
typedef BOOL (CALLBACK *PROPENUMPROCEXA)( HWND, LPSTR, HANDLE, ULONG_PTR );
typedef BOOL (CALLBACK *PROPENUMPROCEXW)( HWND, LPWSTR, HANDLE, ULONG_PTR );
typedef BOOL (CALLBACK *PROPENUMPROCW)( HWND, LPCWSTR, HANDLE );
typedef VOID (CALLBACK *SENDASYNCPROC)( HWND, UINT, ULONG_PTR, LRESULT );
typedef VOID (CALLBACK *TIMERPROC)( HWND, UINT, UINT_PTR, DWORD );
typedef BOOL (CALLBACK *WNDENUMPROC)( HWND, LPARAM );
typedef LRESULT (CALLBACK *WNDPROC)( HWND, UINT, WPARAM, LPARAM );
#if (WINVER >= 0x0400)
typedef BOOL (CALLBACK *DRAWSTATEPROC)( HDC, LPARAM, WPARAM, int, int );
#endif
typedef NAMEENUMPROCA   DESKTOPENUMPROCA;
typedef NAMEENUMPROCW   DESKTOPENUMPROCW;
typedef NAMEENUMPROCA   WINSTAENUMPROCA;
typedef NAMEENUMPROCW   WINSTAENUMPROCW;
#ifdef UNICODE
    #define DESKTOPENUMPROC     DESKTOPENUMPROCW
    #define EDITWORDBREAKPROC   EDITWORDBREAKPROCW
    #define PROPENUMPROC        PROPENUMPROCW
    #define PROPENUMPROCEX      PROPENUMPROCEXW
    #define WINSTAENUMPROC      WINSTAENUMPROCW
#else
    #define DESKTOPENUMPROC     DESKTOPENUMPROCA
    #define EDITWORDBREAKPROC   EDITWORDBREAKPROCA
    #define PROPENUMPROC        PROPENUMPROCA
    #define PROPENUMPROCEX      PROPENUMPROCEXA
    #define WINSTAENUMPROC      WINSTAENUMPROCA
#endif

/* Parameters to HCBT_CREATEWND */
typedef struct tagCBT_CREATEWNDA {
    struct tagCREATESTRUCTA *lpcs;
    HWND                    hwndInsertAfter;
} CBT_CREATEWNDA;
typedef CBT_CREATEWNDA      *LPCBT_CREATEWNDA;
typedef struct tagCBT_CREATEWNDW {
    struct tagCREATESTRUCTW *lpcs;
    HWND                    hwndInsertAfter;
} CBT_CREATEWNDW;
typedef CBT_CREATEWNDW      *LPCBT_CREATEWNDW;
#ifdef UNICODE
typedef CBT_CREATEWNDW      CBT_CREATEWND;
typedef LPCBT_CREATEWNDW    LPCBT_CREATEWND;
#else
typedef CBT_CREATEWNDA      CBT_CREATEWND;
typedef LPCBT_CREATEWNDA    LPCBT_CREATEWND;
#endif

/* Parameters to HCBT_ACTIVATE */
typedef struct tagCBTACTIVATESTRUCT {
    BOOL    fMouse;
    HWND    hWndActive;
} CBTACTIVATESTRUCT;
typedef CBTACTIVATESTRUCT   *LPCBTACTIVATESTRUCT;

/* Parameters to WM_WTSSESSION_CHANGE */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagWTSSESSION_NOTIFICATION {
    DWORD   cbSize;
    DWORD   dwSessionId;
} WTSSESSION_NOTIFICATION;
typedef WTSSESSION_NOTIFICATION *PWTSSESSION_NOTIFICATION;
#endif

/* Shell hook information */
typedef struct {
    HWND    hwnd;
    RECT    rc;
} SHELLHOOKINFO;
typedef SHELLHOOKINFO   *LPSHELLHOOKINFO;

/* Event message */
typedef struct tagEVENTMSG {
    UINT    message;
    UINT    paramL;
    UINT    paramH;
    DWORD   time;
    HWND    hwnd;
} EVENTMSG;
typedef EVENTMSG    *PEVENTMSG;
typedef EVENTMSG    *NPEVENTMSG;
typedef EVENTMSG    *LPEVENTMSG;

/* Parameters to WH_CALLWNDPROC */
typedef struct tagCWPSTRUCT {
    LPARAM  lParam;
    WPARAM  wParam;
    UINT    message;
    HWND    hwnd;
} CWPSTRUCT;
typedef CWPSTRUCT   *PCWPSTRUCT;
typedef CWPSTRUCT   *NPCWPSTRUCT;
typedef CWPSTRUCT   *LPCWPSTRUCT;

/* Parameters to WH_CALLWNDPROCRET */
#if (WINVER >= 0x0400)
typedef struct tagCWPRETSTRUCT {
    LRESULT lResult;
    LPARAM  lParam;
    WPARAM  wParam;
    UINT    message;
    HWND    hwnd;
} CWPRETSTRUCT;
typedef CWPRETSTRUCT    *PCWPRETSTRUCT;
typedef CWPRETSTRUCT    *NPCWPRETSTRUCT;
typedef CWPRETSTRUCT    *LPCWPRETSTRUCT;
#endif

/* Parameters to WH_KEYBOARD_LL */
#if (_WIN32_WINNT >= 0x0400)
typedef struct tagKBDLLHOOKSTRUCT {
    DWORD       vkCode;
    DWORD       scanCode;
    DWORD       flags;
    DWORD       time;
    ULONG_PTR   dwExtraInfo;
} KBDLLHOOKSTRUCT;
typedef KBDLLHOOKSTRUCT *PKBDLLHOOKSTRUCT;
typedef KBDLLHOOKSTRUCT *LPKBDLLHOOKSTRUCT;
#endif

/* Parameters to WH_MOUSE_LL */
#if (_WIN32_WINNT >= 0x0400)
typedef struct tagMSLLHOOKSTRUCT {
    POINT       pt;
    DWORD       mouseData;
    DWORD       flags;
    DWORD       time;
    ULONG_PTR   dwExtraInfo;
} MSLLHOOKSTRUCT;
typedef MSLLHOOKSTRUCT  *PMSLLHOOKSTRUCT;
typedef MSLLHOOKSTRUCT  *LPMSLLHOOKSTRUCT;
#endif

/* Parameters to WH_DEBUG */
typedef struct tagDEBUGHOOKINFO {
    DWORD   idThread;
    DWORD   idThreadInstaller;
    LPARAM  lParam;
    WPARAM  wParam;
    int     code;
} DEBUGHOOKINFO;
typedef DEBUGHOOKINFO   *PDEBUGHOOKINFO;
typedef DEBUGHOOKINFO   *NPDEBUGHOOKINFO;
typedef DEBUGHOOKINFO   *LPDEBUGHOOKINFO;

/* Parameters to WH_MOUSE */
typedef struct tagMOUSEHOOKSTRUCT {
    POINT       pt;
    HWND        hwnd;
    UINT        wHitTestCode;
    ULONG_PTR   dwExtraInfo;
} MOUSEHOOKSTRUCT;
typedef MOUSEHOOKSTRUCT *PMOUSEHOOKSTRUCT;
typedef MOUSEHOOKSTRUCT *LPMOUSEHOOKSTRUCT;

/* Parameters to WH_MOUSE (extended version) */
#if (_WIN32_WINNT >= 0x0500)
#ifdef __cplusplus
typedef struct tagMOUSEHOOKSTRUCTEX : public tagMOUSEHOOKSTRUCT {
#else
typedef struct tagMOUSEHOOKSTRUCTEX {
    MOUSEHOOKSTRUCT;
#endif
    DWORD mouseData;
} MOUSEHOOKSTRUCTEX;
typedef MOUSEHOOKSTRUCTEX   *PMOUSEHOOKSTRUCTEX;
typedef MOUSEHOOKSTRUCTEX   *LPMOUSEHOOKSTRUCTEX;
#endif

/* Parameters to WH_HARDWARE */
#if (WINVER >= 0x0400)
typedef struct tagHARDWAREHOOKSTRUCT {
    HWND    hwnd;
    UINT    message;
    WPARAM  wParam;
    LPARAM  lParam;
} HARDWAREHOOKSTRUCT;
typedef HARDWAREHOOKSTRUCT  *PHARDWAREHOOKSTRUCT;
typedef HARDWAREHOOKSTRUCT  *LPHARDWAREHOOKSTRUCT;
#endif

/* Mouse move point */
#if (WINVER >= 0x0500)
typedef struct tagMOUSEMOVEPOINT {
    int         x;
    int         y;
    DWORD       time;
    ULONG_PTR   dwExtraInfo;
} MOUSEMOVEPOINT;
typedef MOUSEMOVEPOINT  *PMOUSEMOVEPOINT;
typedef MOUSEMOVEPOINT  *LPMOUSEMOVEPOINT;
#endif

/* User object flag information */
typedef struct tagUSEROBJECTFLAGS {
    BOOL    fInherit;
    BOOL    fReserved;
    DWORD   dwFlags;
} USEROBJECTFLAGS;
typedef USEROBJECTFLAGS *PUSEROBJECTFLAGS;

/* Window class information */
typedef struct tagWNDCLASSA {
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCSTR      lpszMenuName;
    LPCSTR      lpszClassName;
} WNDCLASSA;
typedef WNDCLASSA   *PWNDCLASSA;
typedef WNDCLASSA   *NPWNDCLASSA;
typedef WNDCLASSA   *LPWNDCLASSA;
typedef struct tagWNDCLASSW {
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCWSTR     lpszMenuName;
    LPCWSTR     lpszClassName;
} WNDCLASSW;
typedef WNDCLASSW   *PWNDCLASSW;
typedef WNDCLASSW   *NPWNDCLASSW;
typedef WNDCLASSW   *LPWNDCLASSW;
#ifdef UNICODE
typedef WNDCLASSW   WNDCLASS;
typedef PWNDCLASSW  PWNDCLASS;
typedef NPWNDCLASSW NPWNDCLASS;
typedef LPWNDCLASSW LPWNDCLASS;
#else
typedef WNDCLASSA   WNDCLASS;
typedef PWNDCLASSA  PWNDCLASS;
typedef NPWNDCLASSA NPWNDCLASS;
typedef LPWNDCLASSA LPWNDCLASS;
#endif

/* Window class information (extended version) */
#if (WINVER >= 0x0400)
typedef struct tagWNDCLASSEXA {
    UINT        cbSize;
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCSTR      lpszMenuName;
    LPCSTR      lpszClassName;
    HICON       hIconSm;
} WNDCLASSEXA;
typedef WNDCLASSEXA     *PWNDCLASSEXA;
typedef WNDCLASSEXA     *NPWNDCLASSEXA;
typedef WNDCLASSEXA     *LPWNDCLASSEXA;
typedef struct tagWNDCLASSEXW {
    UINT        cbSize;
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCWSTR     lpszMenuName;
    LPCWSTR     lpszClassName;
    HICON       hIconSm;
} WNDCLASSEXW;
typedef WNDCLASSEXW     *PWNDCLASSEXW;
typedef WNDCLASSEXW     *NPWNDCLASSEXW;
typedef WNDCLASSEXW     *LPWNDCLASSEXW;
#ifdef UNICODE
typedef WNDCLASSEXW     WNDCLASSEX;
typedef PWNDCLASSEXW    PWNDCLASSEX;
typedef NPWNDCLASSEXW   NPWNDCLASSEX;
typedef LPWNDCLASSEXW   LPWNDCLASSEX;
#else
typedef WNDCLASSEXA     WNDCLASSEX;
typedef PWNDCLASSEXA    PWNDCLASSEX;
typedef NPWNDCLASSEXA   NPWNDCLASSEX;
typedef LPWNDCLASSEXA   LPWNDCLASSEX;
#endif
#endif

/* Message */
typedef struct tagMSG {
    HWND    hwnd;
    UINT    message;
    WPARAM  wParam;
    LPARAM  lParam;
    DWORD   time;
    POINT   pt;
} MSG;
typedef MSG *PMSG;
typedef MSG *NPMSG;
typedef MSG *LPMSG;

/* Minimum and maximum window size information */
typedef struct tagMINMAXINFO {
    POINT   ptReserved;
    POINT   ptMaxSize;
    POINT   ptMaxPosition;
    POINT   ptMinTrackSize;
    POINT   ptMaxTrackSize;
} MINMAXINFO;
typedef MINMAXINFO  *PMINMAXINFO;
typedef MINMAXINFO  *LPMINMAXINFO;

/* WM_COPYDATA parameters */
typedef struct tagCOPYDATASTRUCT {
    ULONG_PTR   dwData;
    DWORD       cbData;
    PVOID       lpData;
} COPYDATASTRUCT;
typedef COPYDATASTRUCT  *PCOPYDATASTRUCT;

/* WM_NEXTMENU parameters */
#if (WINVER >= 0x0400)
typedef struct tagMDINEXTMENU {
    HMENU   hmenuIn;
    HMENU   hmenuNext;
    HWND    hwndNext;
} MDINEXTMENU;
typedef MDINEXTMENU *PMDINEXTMENU;
typedef MDINEXTMENU *LPMDINEXTMENU;
#endif

/* Power broadcast setting */
#if (_WIN32_WINNT >= 0x0502)
typedef struct {
    GUID    PowerSetting;
    DWORD   DataLength;
    UCHAR   Data[1];
} POWERBROADCAST_SETTING;
typedef POWERBROADCAST_SETTING  *PPOWERBROADCAST_SETTING;
#endif

/* WM_WINDOWPOSCHANGING/WM_WINDOWPOSCHANGED parameters */
typedef struct tagWINDOWPOS {
    HWND    hwnd;
    HWND    hwndInsertAfter;
    int     x;
    int     y;
    int     cx;
    int     cy;
    UINT    flags;
} WINDOWPOS;
typedef WINDOWPOS   *PWINDOWPOS;
typedef WINDOWPOS   *LPWINDOWPOS;

/* WM_NCCALCSIZE parameters */
typedef struct tagNCCALCSIZE_PARAMS {
    RECT        rgrc[3];
    PWINDOWPOS  lppos;
} NCCALCSIZE_PARAMS;
typedef NCCALCSIZE_PARAMS   *LPNCCALCSIZE_PARAMS;

/* TrackMouseEvent() parameters */
#if (_WIN32_WINNT >= 0x0400)
typedef struct tagTRACKMOUSEEVENT {
    DWORD   cbSize;
    DWORD   dwFlags;
    HWND    hwndTrack;
    DWORD   dwHoverTime;
} TRACKMOUSEEVENT;
typedef TRACKMOUSEEVENT *LPTRACKMOUSEEVENT;
#endif

/* Accelerator information */
typedef struct tagACCEL {
    WORD    fVirt;
    WORD    key;
    DWORD   cmd;
} ACCEL;
typedef ACCEL   *LPACCEL;

/* Painting information */
typedef struct tagPAINTSTRUCT {
    HDC     hdc;
    BOOL    fErase;
    RECT    rcPaint;
    BOOL    fRestore;
    BOOL    fIncUpdate;
    BYTE    rgbReserved[32];
} PAINTSTRUCT;
typedef PAINTSTRUCT *PPAINTSTRUCT;
typedef PAINTSTRUCT *NPPAINTSTRUCT;
typedef PAINTSTRUCT *LPPAINTSTRUCT;

/* WM_CREATE parameters */
typedef struct tagCREATESTRUCTA {
    LPVOID      lpCreateParams;
    HINSTANCE   hInstance;
    HMENU       hMenu;
    HWND        hwndParent;
    int         cy;
    int         cx;
    int         y;
    int         x;
    LONG        style;
    LPCSTR      lpszName;
    LPCSTR      lpszClass;
    DWORD       dwExStyle;
} CREATESTRUCTA;
typedef CREATESTRUCTA   *LPCREATESTRUCTA;
typedef struct tagCREATESTRUCTW {
    LPVOID      lpCreateParams;
    HINSTANCE   hInstance;
    HMENU       hMenu;
    HWND        hwndParent;
    int         cy;
    int         cx;
    int         y;
    int         x;
    LONG        style;
    LPCWSTR     lpszName;
    LPCWSTR     lpszClass;
    DWORD       dwExStyle;
} CREATESTRUCTW;
typedef CREATESTRUCTW   *LPCREATESTRUCTW;
#ifdef UNICODE
typedef CREATESTRUCTW   CREATESTRUCT;
typedef LPCREATESTRUCTW LPCREATESTRUCT;
#else
typedef CREATESTRUCTA   CREATESTRUCT;
typedef LPCREATESTRUCTA LPCREATESTRUCT;
#endif

/* Window placement */
typedef struct tagWINDOWPLACEMENT {
    UINT    length;
    UINT    flags;
    UINT    showCmd;
    POINT   ptMinPosition;
    POINT   ptMaxPosition;
    RECT    rcNormalPosition;
} WINDOWPLACEMENT;
typedef WINDOWPLACEMENT *PWINDOWPLACEMENT;
typedef WINDOWPLACEMENT *LPWINDOWPLACEMENT;

/* Notification header */
#if (WINVER >= 0x0400)
typedef struct tagNMHDR {
    HWND        hwndFrom;
    UINT_PTR    idFrom;
    UINT        code;
} NMHDR;
typedef NMHDR   *LPNMHDR;
#endif

/* WM_STYLECHANGED/WM_STYLECHANGING parameters */
#if (WINVER >= 0x0400)
typedef struct tagSTYLESTRUCT {
    DWORD   styleOld;
    DWORD   styleNew;
} STYLESTRUCT;
typedef STYLESTRUCT *LPSTYLESTRUCT;
#endif

/* WM_MEASUREITEM parameters */
typedef struct tagMEASUREITEMSTRUCT {
    UINT        CtlType;
    UINT        CtlID;
    UINT        itemID;
    UINT        itemWidth;
    UINT        itemHeight;
    ULONG_PTR   itemData;
} MEASUREITEMSTRUCT;
typedef MEASUREITEMSTRUCT   *PMEASUREITEMSTRUCT;
typedef MEASUREITEMSTRUCT   *LPMEASUREITEMSTRUCT;

/* WM_DRAWITEM parameters */
typedef struct tagDRAWITEMSTRUCT {
    UINT        CtlType;
    UINT        CtlID;
    UINT        itemID;
    UINT        itemAction;
    UINT        itemState;
    HWND        hwndItem;
    HDC         hDC;
    RECT        rcItem;
    ULONG_PTR   itemData;
} DRAWITEMSTRUCT;
typedef DRAWITEMSTRUCT  *PDRAWITEMSTRUCT;
typedef DRAWITEMSTRUCT  *LPDRAWITEMSTRUCT;

/* WM_DELETEITEM parameters */
typedef struct tagDELETEITEMSTRUCT {
    UINT        CtlType;
    UINT        CtlID;
    UINT        itemID;
    HWND        hwndItem;
    ULONG_PTR   itemData;
} DELETEITEMSTRUCT;
typedef DELETEITEMSTRUCT    *PDELETEITEMSTRUCT;
typedef DELETEITEMSTRUCT    *LPDELETEITEMSTRUCT;

/* WM_COMPAREITEM parameters */
typedef struct tagCOMPAREITEMSTRUCT {
    UINT        CtlType;
    UINT        CtlID;
    HWND        hwndItem;
    UINT        itemID1;
    ULONG_PTR   itemData1;
    UINT        itemID2;
    ULONG_PTR   itemData2;
    DWORD       dwLocaleId;
} COMPAREITEMSTRUCT;
typedef COMPAREITEMSTRUCT   *PCOMPAREITEMSTRUCT;
typedef COMPAREITEMSTRUCT   *LPCOMPAREITEMSTRUCT;

/* BroadcastSystemMessageEx() information */
#if (_WIN32_WINNT >= 0x0501)
typedef struct {
    UINT    cbSize;
    HDESK   hdesk;
    HWND    hwnd;
    LUID    luid;
} BSMINFO;
typedef BSMINFO *PBSMINFO;
#endif

/* UpdateLayeredWindowIndirect() parameters */
#if (_WIN32_WINNT >= 0x0500)
#ifdef _WINGDI_
typedef struct tagUPDATELAYEREDWINDOWINFO {
    DWORD               cbSize;
    HDC                 hdcDst;
    POINT CONST         *pptDst;
    SIZE CONST          *psize;
    HDC                 hdcSrc;
    POINT CONST         *pptSrc;
    COLORREF            crKey;
    BLENDFUNCTION CONST *pblend;
    DWORD               dwFlags;
    RECT CONST          *prcDirty;
} UPDATELAYEREDWINDOWINFO;
typedef UPDATELAYEREDWINDOWINFO *PUPDATELAYEREDWINDOWINFO;
#endif
#endif

/* FlashWindowEx() parameters */
#if (WINVER >= 0x0500)
typedef struct {
    UINT    cbSize;
    HWND    hwnd;
    DWORD   dwFlags;
    UINT    uCount;
    DWORD   dwTimeout;
} FLASHWINFO;
typedef FLASHWINFO  *PFLASHWINFO;
#endif

/* Dialog structures use 2-byte packing. */
#include <pshpack2.h>

/* Dialog box template */
typedef struct {
    DWORD   style;
    DWORD   dwExtendedStyle;
    WORD    cdit;
    short   x;
    short   y;
    short   cx;
    short   cy;
} DLGTEMPLATE;
typedef DLGTEMPLATE         *LPDLGTEMPLATEA;
typedef DLGTEMPLATE         *LPDLGTEMPLATEW;
typedef CONST DLGTEMPLATE   *LPCDLGTEMPLATEA;
typedef CONST DLGTEMPLATE   *LPCDLGTEMPLATEW;
#ifdef UNICODE
typedef LPDLGTEMPLATEW      LPDLGTEMPLATE;
typedef LPCDLGTEMPLATEW     LPCDLGTEMPLATE;
#else
typedef LPDLGTEMPLATEA      LPDLGTEMPLATE;
typedef LPCDLGTEMPLATEA     LPCDLGTEMPLATE;
#endif

/* Dialog item template */
typedef struct {
    DWORD   style;
    DWORD   dwExtendedStyle;
    short   x;
    short   y;
    short   cx;
    short   cy;
    WORD    id;
} DLGITEMTEMPLATE;
typedef DLGITEMTEMPLATE     *PDLGITEMTEMPLATEA;
typedef DLGITEMTEMPLATE     *PDLGITEMTEMPLATEW;
typedef DLGITEMTEMPLATE     *LPDLGITEMTEMPLATEA;
typedef DLGITEMTEMPLATE     *LPDLGITEMTEMPLATEW;
#ifdef UNICODE
typedef PDLGITEMTEMPLATEW   PDLGITEMTEMPLATE;
typedef LPDLGITEMTEMPLATEW  LPDLGITEMTEMPLATE;
#else
typedef PDLGITEMTEMPLATEA   PDLGITEMTEMPLATE;
typedef LPDLGITEMTEMPLATEA  LPDLGITEMTEMPLATE;
#endif

/* Revert to default packing. */
#include <poppack.h>

/* Mouse input information */
#if (_WIN32_WINNT > 0x0400)
typedef struct tagMOUSEINPUT {
    LONG        dx;
    LONG        dy;
    DWORD       mouseData;
    DWORD       dwFlags;
    DWORD       time;
    ULONG_PTR   dwExtraInfo;
} MOUSEINPUT;
typedef MOUSEINPUT  *PMOUSEINPUT;
typedef MOUSEINPUT  *LPMOUSEINPUT;
#endif

/* Keyboard input information */
#if (_WIN32_WINNT > 0x0400)
typedef struct tagKEYBDINPUT {
    WORD        wVk;
    WORD        wScan;
    DWORD       dwFlags;
    DWORD       time;
    ULONG_PTR   dwExtraInfo;
} KEYBDINPUT;
typedef KEYBDINPUT  *PKEYBDINPUT;
typedef KEYBDINPUT  *LPKEYBDINPUT;
#endif

/* Hardware input information */
#if (_WIN32_WINNT > 0x0400)
typedef struct tagHARDWAREINPUT {
    DWORD   uMsg;
    WORD    wParamL;
    WORD    wParamH;
} HARDWAREINPUT;
typedef HARDWAREINPUT   *PHARDWAREINPUT;
typedef HARDWAREINPUT   *LPHARDWAREINPUT;
#endif

/* Input information */
#if (_WIN32_WINNT > 0x0400)
typedef struct tagINPUT {
    DWORD   type;
    union {
        MOUSEINPUT      mi;
        KEYBDINPUT      ki;
        HARDWAREINPUT   hi;
    };
} INPUT;
typedef INPUT   *PINPUT;
typedef INPUT   *LPINPUT;
#endif

/* Last input information */
#if (_WIN32_WINNT >= 0x0500)
typedef struct tagLASTINPUTINFO {
    UINT    cbSize;
    DWORD   dwTime;
} LASTINPUTINFO;
typedef LASTINPUTINFO   *PLASTINPUTINFO;
#endif

/* TrackPopupMenuEx() parameters */
#if (WINVER >= 0x0400)
typedef struct tagTPMPARAMS {
    UINT    cbSize;
    RECT    rcExclude;
} TPMPARAMS;
typedef TPMPARAMS   *LPTPMPARAMS;
#endif

/* Menu information */
#if (WINVER >= 0x0500)
typedef struct tagMENUINFO {
    DWORD       cbSize;
    DWORD       fMask;
    DWORD       dwStyle;
    UINT        cyMax;
    HBRUSH      hbrBack;
    DWORD       dwContextHelpID;
    ULONG_PTR   dwMenuData;
} MENUINFO;
typedef MENUINFO        *LPMENUINFO;
typedef CONST MENUINFO  *LPCMENUINFO;
#endif

/* WM_MENUGETOBJECT parameters */
#if (WINVER >= 0x0500)
typedef struct tagMENUGETOBJECTINFO {
    DWORD   dwFlags;
    UINT    uPos;
    HMENU   hmenu;
    PVOID   riid;
    PVOID   pvObj;
} MENUGETOBJECTINFO;
typedef MENUGETOBJECTINFO   *PMENUGETOBJECTINFO;
#endif

/* Menu item information */
#if (WINVER >= 0x0400)
typedef struct tagMENUITEMINFOA {
    UINT        cbSize;
    UINT        fMask;
    UINT        fType;
    UINT        fState;
    UINT        wID;
    HMENU       hSubMenu;
    HBITMAP     hbmpChecked;
    HBITMAP     hbmpUnchecked;
    ULONG_PTR   dwItemData;
    LPSTR       dwTypeData;
    UINT        cch;
#if (WINVER >= 0x0500)
    HBITMAP     hbmpItem;
#endif
} MENUITEMINFOA;
typedef MENUITEMINFOA       *LPMENUITEMINFOA;
typedef CONST MENUITEMINFOA *LPCMENUITEMINFOA;
typedef struct tagMENUITEMINFOW {
    UINT        cbSize;
    UINT        fMask;
    UINT        fType;
    UINT        fState;
    UINT        wID;
    HMENU       hSubMenu;
    HBITMAP     hbmpChecked;
    HBITMAP     hbmpUnchecked;
    ULONG_PTR   dwItemData;
    LPWSTR      dwTypeData;
    UINT        cch;
#if (WINVER >= 0x0500)
    HBITMAP     hbmpItem;
#endif
} MENUITEMINFOW;
typedef MENUITEMINFOW       *LPMENUITEMINFOW;
typedef MENUITEMINFOW       *LPCMENUITEMINFOW;
#ifdef UNICODE
typedef MENUITEMINFOW       MENUITEMINFO;
typedef LPMENUITEMINFOW     LPMENUITEMINFO;
typedef LPCMENUITEMINFOW    LPCMENUITEMINFO;
#else
typedef MENUITEMINFOA       MENUITEMINFO;
typedef LPMENUITEMINFOA     LPMENUITEMINFO;
typedef LPCMENUITEMINFOA    LPCMENUITEMINFO;
#endif
#endif

/* Drop information */
#if (WINVER >= 0x0400)
typedef struct tagDROPSTRUCT {
    HWND        hwndSource;
    HWND        hwndSink;
    DWORD       wFmt;
    ULONG_PTR   dwData;
    POINT       ptDrop;
    DWORD       dwControlData;
} DROPSTRUCT;
typedef DROPSTRUCT  *PDROPSTRUCT;
typedef DROPSTRUCT  *LPDROPSTRUCT;
#endif

/* DrawTextEx() parameters */
#if (WINVER >= 0x0400)
typedef struct tagDRAWTEXTPARAMS {
    UINT    cbSize;
    int     iTabLength;
    int     iLeftMargin;
    int     iRightMargin;
    UINT    uiLengthDrawn;
} DRAWTEXTPARAMS;
typedef DRAWTEXTPARAMS  *LPDRAWTEXTPARAMS;
#endif

/* Help information */
#if (WINVER >= 0x0400)
typedef struct tagHELPINFO {
    UINT        cbSize;
    int         iContextType;
    int         iCtrlId;
    int         hItemHandle;
    DWORD_PTR   dwContextId;
    POINT       MousePos;
} HELPINFO;
typedef HELPINFO    *LPHELPINFO;
#endif

/* Callback for MessageBoxIndirect() */
#if (WINVER >= 0x0400)
typedef VOID (CALLBACK *MSGBOXCALLBACK)( LPHELPINFO );
#endif

/* MessageBoxIndirect() parameters */
#if (WINVER >= 0x0400)
typedef struct tagMSGBOXPARAMSA {
    UINT            cbSize;
    HWND            hwndOwner;
    HINSTANCE       hInstance;
    LPCSTR          lpszText;
    LPCSTR          lpszCaption;
    DWORD           dwStyle;
    LPCSTR          lpszIcon;
    DWORD_PTR       dwContextHelpId;
    MSGBOXCALLBACK  lpfnMsgBoxCallback;
    DWORD           dwLanguageId;
} MSGBOXPARAMSA;
typedef MSGBOXPARAMSA   *PMSGBOXPARAMSA;
typedef MSGBOXPARAMSA   *LPMSGBOXPARAMSA;
typedef struct tagMSGBOXPARAMSW {
    UINT            cbSize;
    HWND            hwndOwner;
    HINSTANCE       hInstance;
    LPCWSTR         lpszText;
    LPCWSTR         lpszCaption;
    DWORD           dwStyle;
    LPCWSTR         lpszIcon;
    DWORD_PTR       dwContextHelpId;
    MSGBOXCALLBACK  lpfnMsgBoxCallback;
    DWORD           dwLanguageId;
} MSGBOXPARAMSW;
typedef MSGBOXPARAMSW   *PMSGBOXPARAMSW;
typedef MSGBOXPARAMSW   *LPMSGBOXPARAMSW;
#ifdef UNICODE
typedef MSGBOXPARAMSW   MSGBOXPARAMS;
typedef PMSGBOXPARAMSW  PMSGBOXPARAMS;
typedef LPMSGBOXPARAMSW LPMSGBOXPARAMS;
#else
typedef MSGBOXPARAMSA   MSGBOXPARAMS;
typedef PMSGBOXPARAMSA  PMSGBOXPARAMS;
typedef LPMSGBOXPARAMSA LPMSGBOXPARAMS;
#endif
#endif

/* Menu item template header */
typedef struct {
    WORD    versionNumber;
    WORD    offset;
} MENUITEMTEMPLATEHEADER;
typedef MENUITEMTEMPLATEHEADER  *PMENUITEMTEMPLATEHEADER;

/* Menu item template */
typedef struct {
    WORD    mtOption;
    WORD    mtID;
    WCHAR   mtString[1];
} MENUITEMTEMPLATE;
typedef MENUITEMTEMPLATE    *PMENUITEMTEMPLATE;

/* Icon information */
typedef struct _ICONINFO {
    BOOL    fIcon;
    DWORD   xHotspot;
    DWORD   yHotspot;
    HBITMAP hbmMask;
    HBITMAP hbmColor;
} ICONINFO;
typedef ICONINFO    *PICONINFO;

/* Icon information (extended version) */
#if (_WIN32_WINNT >= 0x0600)
typedef struct _ICONINFOEXA {
    DWORD   cbSize;
    BOOL    fIcon;
    DWORD   xHotspot;
    DWORD   yHotspot;
    HBITMAP hbmMask;
    HBITMAP hbmColor;
    WORD    wResID;
    CHAR    szModName[MAX_PATH];
    CHAR    szResName[MAX_PATH];
} ICONINFOEXA;
typedef ICONINFOEXA     *PICONINFOEXA;
typedef struct _ICONINFOEXW {
    DWORD   cbSize;
    BOOL    fIcon;
    DWORD   xHotspot;
    DWORD   yHotspot;
    HBITMAP hbmMask;
    HBITMAP hbmColor;
    WORD    wResID;
    WCHAR   szModName[MAX_PATH];
    WCHAR   szResName[MAX_PATH];
} ICONINFOEXW;
typedef ICONINFOEXW     *PICONINFOEXW;
#ifdef UNICODE
typedef ICONINFOEXW     ICONINFOEX;
typedef PICONINFOEXW    PICONINFOEX;
#else
typedef ICONINFOEXA     ICONINFOEX;
typedef PICONINFOEXA    PICONINFOEX;
#endif
#endif

/* Cursor shape */
typedef struct tagCURSORSHAPE {
    int     xHotspot;
    int     yHotspot;
    int     cx;
    int     cy;
    int     cbWidth;
    BYTE    Planes;
    BYTE    BitsPixel;
} CURSORSHAPE;
typedef CURSORSHAPE *LPCURSORSHAPE;

/* Scrolling information */
#if (WINVER >= 0x0400)
typedef struct tagSCROLLINFO {
    UINT    cbSize;
    UINT    fMask;
    int     nMin;
    int     nMax;
    UINT    nPage;
    int     nPos;
    int     nTrackPos;
} SCROLLINFO;
typedef SCROLLINFO          *LPSCROLLINFO;
typedef CONST SCROLLINFO    *LPCSCROLLINFO;
#endif

/* WM_MDICREATE parameters */
typedef struct tagMDICREATESTRUCTA {
    LPCSTR  szClass;
    LPCSTR  szTitle;
    HANDLE  hOwner;
    int     x;
    int     y;
    int     cx;
    int     cy;
    DWORD   style;
    LPARAM  lParam;
} MDICREATESTRUCTA;
typedef MDICREATESTRUCTA    *LPMDICREATESTRUCTA;
typedef struct tagMDICREATESTRUCTW {
    LPCWSTR szClass;
    LPCWSTR szTitle;
    HANDLE  hOwner;
    int     x;
    int     y;
    int     cx;
    int     cy;
    DWORD   style;
    LPARAM  lParam;
} MDICREATESTRUCTW;
typedef MDICREATESTRUCTW    *LPMDICREATESTRUCTW;
#ifdef UNICODE
typedef MDICREATESTRUCTW    MDICREATESTRUCT;
typedef LPMDICREATESTRUCTW  LPMDICREATESTRUCT;
#else
typedef MDICREATESTRUCTA    MDICREATESTRUCT;
typedef LPMDICREATESTRUCTA  LPMDICREATESTRUCT;
#endif

/* MDICLIENT creation parameters */
typedef struct tagCLIENTCREATESTRUCT {
    HANDLE  hWindowMenu;
    UINT    idFirstChild;
} CLIENTCREATESTRUCT;
typedef CLIENTCREATESTRUCT  *LPCLIENTCREATESTRUCT;

/* Help keyword information */
typedef struct tagMULTIKEYHELPA {
    DWORD   mkSize;
    CHAR    mkKeylist;
    CHAR    mkKeyphrase[1];
} MULTIKEYHELPA;
typedef MULTIKEYHELPA   *PMULTIKEYHELPA;
typedef MULTIKEYHELPA   *LPMULTIKEYHELPA;
typedef struct tagMULTIKEYHELPW {
    DWORD   mkSize;
    WCHAR   mkKeylist;
    WCHAR   mkKeyphrase[1];
} MULTIKEYHELPW;
typedef MULTIKEYHELPW   *PMULTIKEYHELPW;
typedef MULTIKEYHELPW   *LPMULTIKEYHELPW;
#ifdef UNICODE
typedef MULTIKEYHELPW   MULTIKEYHELP;
typedef PMULTIKEYHELPW  PMULTIKEYHELP;
typedef LPMULTIKEYHELPW LPMULTIKEYHELP;
#else
typedef MULTIKEYHELPA   MULTIKEYHELP;
typedef PMULTIKEYHELPA  PMULTIKEYHELP;
typedef LPMULTIKEYHELPA LPMULTIKEYHELP;
#endif

/* Help window information */
typedef struct tagHELPWININFOA {
    int     wStructSize;
    int     x;
    int     y;
    int     dx;
    int     dy;
    int     wMax;
    CHAR    rgchMember[2];
} HELPWININFOA;
typedef HELPWININFOA    *PHELPWININFOA;
typedef HELPWININFOA    *LPHELPWININFOA;
typedef struct tagHELPWININFOW {
    int     wStructSize;
    int     x;
    int     y;
    int     dx;
    int     dy;
    int     wMax;
    WCHAR   rgchMember[2];
} HELPWININFOW;
typedef HELPWININFOW    *PHELPWININFOW;
typedef HELPWININFOW    *LPHELPWININFOW;
#ifdef UNICODE
typedef HELPWININFOW    HELPWININFO;
typedef PHELPWININFOW   PHELPWININFO;
typedef LPHELPWININFOW  LPHELPWININFO;
#else
typedef HELPWININFOA    HELPWININFO;
typedef PHELPWININFOA   PHELPWININFO;
typedef LPHELPWININFOA  LPHELPWININFO;
#endif

/* Nonclient metrics */
#ifdef _WINGDI_
typedef struct tagNONCLIENTMETRICSA {
    UINT        cbSize;
    int         iBorderWidth;
    int         iScrollWidth;
    int         iScrollHeight;
    int         iCaptionWidth;
    int         iCaptionHeight;
    LOGFONTA    lfCaptionFont;
    int         iSmCaptionWidth;
    int         iSmCaptionHeight;
    LOGFONTA    lfSmCaptionFont;
    int         iMenuWidth;
    int         iMenuHeight;
    LOGFONTA    lfMenuFont;
    LOGFONTA    lfStatusFont;
    LOGFONTA    lfMessageFont;
#if (WINVER >= 0x0600)
    int         iPaddedBorderWidth;
#endif
} NONCLIENTMETRICSA;
typedef NONCLIENTMETRICSA   *PNONCLIENTMETRICSA;
typedef NONCLIENTMETRICSA   *LPNONCLIENTMETRICSA;
typedef struct tagNONCLIENTMETRICSW {
    UINT        cbSize;
    int         iBorderWidth;
    int         iScrollWidth;
    int         iScrollHeight;
    int         iCaptionWidth;
    int         iCaptionHeight;
    LOGFONTW    lfCaptionFont;
    int         iSmCaptionWidth;
    int         iSmCaptionHeight;
    LOGFONTW    lfSmCaptionFont;
    int         iMenuWidth;
    int         iMenuHeight;
    LOGFONTW    lfMenuFont;
    LOGFONTW    lfStatusFont;
    LOGFONTW    lfMessageFont;
#if (WINVER >= 0x0600)
    int         iPaddedBorderWidth;
#endif
} NONCLIENTMETRICSW;
typedef NONCLIENTMETRICSW   *PNONCLIENTMETRICSW;
typedef NONCLIENTMETRICSW   *LPNONCLIENTMETRICSW;
#ifdef UNICODE
typedef NONCLIENTMETRICSW   NONCLIENTMETRICS;
typedef PNONCLIENTMETRICSW  PNONCLIENTMETRICS;
typedef LPNONCLIENTMETRICSW LPNONCLIENTMETRICS;
#else
typedef NONCLIENTMETRICSA   NONCLIENTMETRICS;
typedef PNONCLIENTMETRICSA  PNONCLIENTMETRICS;
typedef LPNONCLIENTMETRICSA LPNONCLIENTMETRICS;
#endif
#endif

/* Minimized metrics */
typedef struct tagMINIMIZEDMETRICS {
    UINT    cbSize;
    int     iWidth;
    int     iHorzGap;
    int     iVertGap;
    int     iArrange;
} MINIMIZEDMETRICS;
typedef MINIMIZEDMETRICS    *PMINIMIZEDMETRICS;
typedef MINIMIZEDMETRICS    *LPMINIMIZEDMETRICS;

/* Icon metrics */
#ifdef _WINGDI_
typedef struct tagICONMETRICSA {
    UINT        cbSize;
    int         iHorzSpacing;
    int         iVertSpacing;
    int         iTitleWrap;
    LOGFONTA    lfFont;
} ICONMETRICSA;
typedef ICONMETRICSA    *PICONMETRICSA;
typedef ICONMETRICSA    *LPICONMETRICSA;
typedef struct tagICONMETRICSW {
    UINT        cbSize;
    int         iHorzSpacing;
    int         iVertSpacing;
    int         iTitleWrap;
    LOGFONTW    lfFont;
} ICONMETRICSW;
typedef ICONMETRICSW    *PICONMETRICSW;
typedef ICONMETRICSW    *LPICONMETRICSW;
#ifdef UNICODE
typedef ICONMETRICSW    ICONMETRICS;
typedef PICONMETRICSW   PICONMETRICS;
typedef LPICONMETRICSW  LPICONMETRICS;
#else
typedef ICONMETRICSA    ICONMETRICS;
typedef PICONMETRICSA   PICONMETRICS;
typedef LPICONMETRICSA  LPICONMETRICS;
#endif
#endif

/* Animation information */
typedef struct tagANIMATIONINFO {
    UINT    cbSize;
    int     iMinAnimate;
} ANIMATIONINFO;
typedef ANIMATIONINFO   *LPANIMATIONINFO;

/* SerialKeys information */
typedef struct tagSERIALKEYSA {
    UINT    cbSize;
    DWORD   dwFlags;
    LPSTR   lpszActivePort;
    LPSTR   lpszPort;
    UINT    iBaudRate;
    UINT    iPortState;
    UINT    iActive;
} SERIALKEYSA;
typedef SERIALKEYSA     *LPSERIALKEYSA;
typedef struct tagSERIALKEYSW {
    UINT    cbSize;
    DWORD   dwFlags;
    LPWSTR  lpszActivePort;
    LPWSTR  lpszPort;
    UINT    iBaudRate;
    UINT    iPortState;
    UINT    iActive;
} SERIALKEYSW;
typedef SERIALKEYSW     *LPSERIALKEYSW;
#ifdef UNICODE
typedef SERIALKEYSW     SERIALKEYS;
typedef LPSERIALKEYSW   LPSERIALKEYS;
#else
typedef SERIALKEYSA     SERIALKEYS;
typedef LPSERIALKEYSA   LPSERIALKEYS;
#endif

/* High contrast information */
typedef struct tagHIGHCONTRASTA {
    UINT    cbSize;
    DWORD   dwFlags;
    LPSTR   lpszDefaultScheme;
} HIGHCONTRASTA;
typedef HIGHCONTRASTA   *LPHIGHCONTRASTA;
typedef struct tagHIGHCONTRASTW {
    UINT    cbSize;
    DWORD   dwFlags;
    LPWSTR  lpszDefaultScheme;
} HIGHCONTRASTW;
typedef HIGHCONTRASTW   *LPHIGHCONTRASTW;
#ifdef UNICODE
typedef HIGHCONTRASTW   HIGHCONTRAST;
typedef LPHIGHCONTRASTW LPHIGHCONTRAST;
#else
typedef HIGHCONTRASTA   HIGHCONTRAST;
typedef LPHIGHCONTRASTA LPHIGHCONTRAST;
#endif

/* FilterKeys information */
typedef struct tagFILTERKEYS {
    UINT    cbSize;
    DWORD   dwFlags;
    DWORD   iWaitMSec;
    DWORD   iDelayMSec;
    DWORD   iRepeatMSec;
    DWORD   iBounceMSec;
} FILTERKEYS;
typedef FILTERKEYS  *LPFILTERKEYS;

/* StickyKeys information */
typedef struct tagSTICKYKEYS {
    UINT    cbSize;
    DWORD   dwFlags;
} STICKYKEYS;
typedef STICKYKEYS  *LPSTICKYKEYS;

/* MouseKeys information */
typedef struct tagMOUSEKEYS {
    UINT    cbSize;
    DWORD   dwFlags;
    DWORD   iMaxSpeed;
    DWORD   iTimeToMaxSpeed;
    DWORD   iCtrlSpeed;
    DWORD   dwReserved1;
    DWORD   dwReserved2;
} MOUSEKEYS;
typedef MOUSEKEYS   *LPMOUSEKEYS;

/* Access timeout information */
typedef struct tagACCESSTIMEOUT {
    UINT    cbSize;
    DWORD   dwFlags;
    DWORD   iTimeOutMSec;
} ACCESSTIMEOUT;
typedef ACCESSTIMEOUT   *LPACCESSTIMEOUT;

/* SoundSentry information */
typedef struct tagSOUNDSENTRYA {
    UINT    cbSize;
    DWORD   dwFlags;
    DWORD   iFSTextEffect;
    DWORD   iFSTextEffectMSec;
    DWORD   iFSTextEffectColorBits;
    DWORD   iFSGrafEffect;
    DWORD   iFSGrafEffectMSec;
    DWORD   iFSGrafEffectColor;
    DWORD   iWindowsEffect;
    DWORD   iWindowsEffectMSec;
    LPSTR   lpszWindowsEffectDLL;
    DWORD   iWindowsEffectOrdinal;
} SOUNDSENTRYA;
typedef SOUNDSENTRYA    *LPSOUNDSENTRYA;
typedef struct tagSOUNDSENTRYW {
    UINT    cbSize;
    DWORD   dwFlags;
    DWORD   iFSTextEffect;
    DWORD   iFSTextEffectMSec;
    DWORD   iFSTextEffectColorBits;
    DWORD   iFSGrafEffect;
    DWORD   iFSGrafEffectMSec;
    DWORD   iFSGrafEffectColor;
    DWORD   iWindowsEffect;
    DWORD   iWindowsEffectMSec;
    LPWSTR  lpszWindowsEffectDLL;
    DWORD   iWindowsEffectOrdinal;
} SOUNDSENTRYW;
typedef SOUNDSENTRYW    *LPSOUNDSENTRYW;
#ifdef UNICODE
typedef SOUNDSENTRYW    SOUNDSENTRY;
typedef LPSOUNDSENTRYW  LPSOUNDSENTRY;
#else
typedef SOUNDSENTRYA    SOUNDSENTRY;
typedef LPSOUNDSENTRYA  LPSOUNDSENTRY;
#endif

/* ToggleKeys information */
typedef struct tagTOGGLEKEYS {
    UINT    cbSize;
    DWORD   dwFlags;
} TOGGLEKEYS;
typedef TOGGLEKEYS  *LPTOGGLEKEYS;

/* Audio description */
#if (_WIN32_WINNT >= 0x0600)
typedef struct tagAUDIODESCRIPTION {
    UINT    cbSize;
    BOOL    Enabled;
    LCID    Locale;
} AUDIODESCRIPTION;
typedef AUDIODESCRIPTION    *LPAUDIODESCRIPTION;
#endif

/* Monitor information */
#if (WINVER >= 0x0500)
typedef struct tagMONITORINFO {
    DWORD   cbSize;
    RECT    rcMonitor;
    RECT    rcWork;
    DWORD   dwFlags;
} MONITORINFO;
typedef MONITORINFO *LPMONITORINFO;
#endif

/* Monitor information (extended version) */
#if (WINVER >= 0x0500)
#ifdef __cplusplus
typedef struct tagMONITORINFOEXA : public tagMONITORINFO {
#else
typedef struct tagMONITORINFOEXA {
    MONITORINFO;
#endif
    CHAR            szDevice[CCHDEVICENAME];
} MONITORINFOEXA;
typedef MONITORINFOEXA      *LPMONITORINFOEXA;
#ifdef __cplusplus
typedef struct tagMONITORINFOEXW : public tagMONITORINFO {
#else
typedef struct tagMONITORINFOEXW {
    MONITORINFO;
#endif
    WCHAR           szDevice[CCHDEVICENAME];
} MONITORINFOEXW;
typedef MONITORINFOEXW      *LPMONITORINFOEXW;
#ifdef UNICODE
typedef MONITORINFOEXW      MONITORINFOEX;
typedef LPMONITORINFOEXW    LPMONITORINFOEX;
#else
typedef MONITORINFOEXA      MONITORINFOEX;
typedef LPMONITORINFOEXA    LPMONITORINFOEX;
#endif
#endif

/* Monitor enumeration callback */
#if (WINVER >= 0x0500)
typedef BOOL (CALLBACK *MONITORENUMPROC)( HMONITOR, HDC, LPRECT, LPARAM );
#endif

/* WinEvent hook callback */
#if (WINVER >= 0x0500)
typedef VOID (CALLBACK *WINEVENTPROC)( HWINEVENTHOOK, DWORD, HWND, LONG, LONG, DWORD, DWORD );
#endif

/* GUI thread information */
#if (WINVER >= 0x0500)
typedef struct tagGUITHREADINFO {
    DWORD   cbSize;
    DWORD   flags;
    HWND    hwndActive;
    HWND    hwndFocus;
    HWND    hwndCapture;
    HWND    hwndMenuOwner;
    HWND    hwndMoveSize;
    HWND    hwndCaret;
    RECT    rcCaret;
} GUITHREADINFO;
typedef GUITHREADINFO   *PGUITHREADINFO;
typedef GUITHREADINFO   *LPGUITHREADINFO;
#endif

/* Cursor information */
#if (WINVER >= 0x0500)
typedef struct tagCURSORINFO {
    DWORD   cbSize;
    DWORD   flags;
    HCURSOR hCursor;
    POINT   ptScreenPos;
} CURSORINFO;
typedef CURSORINFO  *PCURSORINFO;
typedef CURSORINFO  *LPCURSORINFO;
#endif

/* Window information */
#if (WINVER >= 0x0500)
typedef struct tagWINDOWINFO {
    DWORD   cbSize;
    RECT    rcWindow;
    RECT    rcClient;
    DWORD   dwStyle;
    DWORD   dwExStyle;
    DWORD   dwWindowStatus;
    UINT    cxWindowBorders;
    UINT    cyWindowBorders;
    ATOM    atomWindowType;
    WORD    wCreatorVersion;
} WINDOWINFO;
typedef WINDOWINFO  *PWINDOWINFO;
typedef WINDOWINFO  *LPWINDOWINFO;
#endif

/* Title bar information */
#if (WINVER >= 0x0500)
typedef struct tagTITLEBARINFO {
    DWORD   cbSize;
    RECT    rcTitleBar;
    DWORD   rgstate[CCHILDREN_TITLEBAR + 1];
} TITLEBARINFO;
typedef TITLEBARINFO    *PTITLEBARINFO;
typedef TITLEBARINFO    *LPTITLEBARINFO;
#endif

/* Title bar information (extended version) */
#if (WINVER >= 0x0600)
typedef struct tagTITLEBARINFOEX {
    DWORD   cbSize;
    RECT    rcTitleBar;
    DWORD   rgstate[CCHILDREN_TITLEBAR + 1];
    RECT    rgrect[CCHILDREN_TITLEBAR + 1];
} TITLEBARINFOEX;
typedef TITLEBARINFOEX  *PTITLEBARINFOEX;
typedef TITLEBARINFOEX  *LPTITLEBARINFOEX;
#endif

/* Menu bar information */
#if (WINVER >= 0x0500)
typedef struct tagMENUBARINFO {
    DWORD   cbSize;
    RECT    rcBar;
    HMENU   hMenu;
    HWND    hwndMenu;
    BOOL    fBarFocused : 1;
    BOOL    fFocused    : 1;
} MENUBARINFO;
typedef MENUBARINFO *PMENUBARINFO;
typedef MENUBARINFO *LPMENUBARINFO;
#endif

/* Scroll bar information */
#if (WINVER >= 0x0500)
typedef struct tagSCROLLBARINFO {
    DWORD   cbSize;
    RECT    rcScrollBar;
    int     dxyLineButton;
    int     xyThumbTop;
    int     xyThumbBottom;
    int     reserved;
    DWORD   rgstate[CCHILDREN_SCROLLBAR + 1];
} SCROLLBARINFO;
typedef SCROLLBARINFO   *PSCROLLBARINFO;
typedef SCROLLBARINFO   *LPSCROLLBARINFO;
#endif

/* Combo box information */
#if (WINVER >= 0x0500)
typedef struct tagCOMBOBOXINFO {
    DWORD   cbSize;
    RECT    rcItem;
    RECT    rcButton;
    DWORD   stateButton;
    HWND    hwndCombo;
    HWND    hwndItem;
    HWND    hwndList;
} COMBOBOXINFO;
typedef COMBOBOXINFO    *PCOMBOBOXINFO;
typedef COMBOBOXINFO    *LPCOMBOBOXINFO;
#endif

/* ALT+TAB information */
#if (WINVER >= 0x0500)
typedef struct tagALTTABINFO {
    DWORD   cbSize;
    int     cItems;
    int     cColumns;
    int     cRows;
    int     iColFocus;
    int     iRowFocus;
    int     cxItem;
    int     cyItem;
    POINT   ptStart;
} ALTTABINFO;
typedef ALTTABINFO  *PALTTABINFO;
typedef ALTTABINFO  *LPALTTABINFO;
#endif

/* Raw input header */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagRAWINPUTHEADER {
    DWORD   dwType;
    DWORD   dwSize;
    HANDLE  hDevice;
    WPARAM  wParam;
} RAWINPUTHEADER;
typedef RAWINPUTHEADER  *PRAWINPUTHEADER;
typedef RAWINPUTHEADER  *LPRAWINPUTHEADER;
#endif

/* Raw mouse input */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagRAWMOUSE {
    USHORT  usFlags;
    union {
        ULONG   ulButtons;
        struct {
            USHORT  usButtonFlags;
            USHORT  usButtonData;
        };
    };
    ULONG   ulRawButtons;
    LONG    lLastX;
    LONG    lLastY;
    ULONG   ulExtraInformation;
} RAWMOUSE;
typedef RAWMOUSE    *PRAWMOUSE;
typedef RAWMOUSE    *LPRAWMOUSE;
#endif

/* Raw keyboard input */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagRAWKEYBOARD {
    USHORT  MakeCode;
    USHORT  Flags;
    USHORT  Reserved;
    USHORT  VKey;
    UINT    Message;
    ULONG   ExtraInformation;
} RAWKEYBOARD;
typedef RAWKEYBOARD *PRAWKEYBOARD;
typedef RAWKEYBOARD *LPRAWKEYBOARD;
#endif

/* Raw Human Interface Device (HID) input */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagRAWHID {
    DWORD   dwSizeHid;
    DWORD   dwCount;
    BYTE    bRawData[1];
} RAWHID;
typedef RAWHID  *PRAWHID;
typedef RAWHID  *LPRAWHID;
#endif

/* Raw input */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagRAWINPUT {
    RAWINPUTHEADER  header;
    union {
        RAWMOUSE    mouse;
        RAWKEYBOARD keyboard;
        RAWHID      hid;
    } data;
} RAWINPUT;
typedef RAWINPUT    *PRAWINPUT;
typedef RAWINPUT    *LPRAWINPUT;
#endif

/* Raw input device information for a mouse */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagRID_DEVICE_INFO_MOUSE {
    DWORD   dwId;
    DWORD   dwNumberOfButtons;
    DWORD   dwSampleRate;
    BOOL    fHasHorizontalWheel;
} RID_DEVICE_INFO_MOUSE;
typedef RID_DEVICE_INFO_MOUSE   *PRID_DEVICE_INFO_MOUSE;
#endif

/* Raw input device information for a keyboard */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagRID_DEVICE_INFO_KEYBOARD {
    DWORD   dwType;
    DWORD   dwSubType;
    DWORD   dwKeyboardMode;
    DWORD   dwNumberOfFunctionKeys;
    DWORD   dwNumberOfIndicators;
    DWORD   dwNumberOfKeysTotal;
} RID_DEVICE_INFO_KEYBOARD;
typedef RID_DEVICE_INFO_KEYBOARD    *PRID_DEVICE_INFO_KEYBOARD;
#endif

/* Raw input device information for a Human Interface Device */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagRID_DEVICE_INFO_HID {
    DWORD   dwVendorId;
    DWORD   dwProductId;
    DWORD   dwVersionNumber;
    USHORT  usUsagePage;
    USHORT  usUsage;
} RID_DEVICE_INFO_HID;
typedef RID_DEVICE_INFO_HID *PRID_DEVICE_INFO_HID;
#endif

/* Raw input device information */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagRID_DEVICE_INFO {
    DWORD   cbSize;
    DWORD   dwType;
    union {
        RID_DEVICE_INFO_MOUSE       mouse;
        RID_DEVICE_INFO_KEYBOARD    keyboard;
        RID_DEVICE_INFO_HID         hid;
    };
} RID_DEVICE_INFO;
typedef RID_DEVICE_INFO *PRID_DEVICE_INFO;
typedef RID_DEVICE_INFO *LPRID_DEVICE_INFO;
#endif

/* Raw input device */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagRAWINPUTDEVICE {
    USHORT  usUsagePage;
    USHORT  usUsage;
    DWORD   dwFlags;
    HWND    hwndTarget;
} RAWINPUTDEVICE;
typedef RAWINPUTDEVICE          *PRAWINPUTDEVICE;
typedef RAWINPUTDEVICE          *LPRAWINPUTDEVICE;
typedef CONST RAWINPUTDEVICE    *PCRAWINPUTDEVICE;
#endif

/* Raw input device list */
#if (_WIN32_WINNT >= 0x0501)
typedef struct tagRAWINPUTDEVICELIST {
    HANDLE  hDevice;
    DWORD   dwType;
} RAWINPUTDEVICELIST;
typedef RAWINPUTDEVICELIST  *PRAWINPUTDEVICELIST;
#endif

/* Functions in USER32.DLL */
WINUSERAPI BOOL WINAPI          AdjustWindowRect( LPRECT, DWORD, BOOL );
WINUSERAPI BOOL WINAPI          AdjustWindowRectEx( LPRECT, DWORD, BOOL, DWORD );
WINUSERAPI BOOL WINAPI          AnyPopup( VOID );
WINUSERAPI BOOL WINAPI          AppendMenuA( HMENU, UINT, UINT_PTR, LPCSTR );
WINUSERAPI BOOL WINAPI          AppendMenuW( HMENU, UINT, UINT_PTR, LPCWSTR );
WINUSERAPI UINT WINAPI          ArrangeIconicWindows( HWND );
WINUSERAPI BOOL WINAPI          AttachThreadInput( DWORD, DWORD, BOOL );
WINUSERAPI HDWP WINAPI          BeginDeferWindowPos( int );
WINUSERAPI HDC WINAPI           BeginPaint( HWND, LPPAINTSTRUCT );
WINUSERAPI BOOL WINAPI          BlockInput( BOOL );
WINUSERAPI BOOL WINAPI          BringWindowToTop( HWND );
WINUSERAPI BOOL WINAPI          CallMsgFilterA( LPMSG, int );
WINUSERAPI BOOL WINAPI          CallMsgFilterW( LPMSG, int );
WINUSERAPI LRESULT WINAPI       CallNextHookEx( HHOOK, int, WPARAM, LPARAM );
WINUSERAPI LRESULT WINAPI       CallWindowProcA( WNDPROC, HWND, UINT, WPARAM, LPARAM );
WINUSERAPI LRESULT WINAPI       CallWindowProcW( WNDPROC, HWND, UINT, WPARAM, LPARAM );
WINUSERAPI BOOL WINAPI          CancelShutdown( VOID );
WINUSERAPI BOOL WINAPI          ChangeClipboardChain( HWND, HWND );
WINUSERAPI BOOL WINAPI          ChangeMenuA( HMENU, UINT, LPCSTR, UINT, UINT );
WINUSERAPI BOOL WINAPI          ChangeMenuW( HMENU, UINT, LPCWSTR, UINT, UINT );
WINUSERAPI LPSTR WINAPI         CharLowerA( LPSTR );
WINUSERAPI DWORD WINAPI         CharLowerBuffA( LPSTR, DWORD );
WINUSERAPI DWORD WINAPI         CharLowerBuffW( LPWSTR, DWORD );
WINUSERAPI LPWSTR WINAPI        CharLowerW( LPWSTR );
WINUSERAPI LPSTR WINAPI         CharNextA( LPCSTR );
WINUSERAPI LPWSTR WINAPI        CharNextW( LPCWSTR );
WINUSERAPI LPSTR WINAPI         CharPrevA( LPCSTR, LPCSTR );
WINUSERAPI LPWSTR WINAPI        CharPrevW( LPCWSTR, LPCWSTR );
WINUSERAPI BOOL WINAPI          CharToOemA( LPCSTR, LPSTR );
WINUSERAPI BOOL WINAPI          CharToOemBuffA( LPCSTR, LPSTR, DWORD );
WINUSERAPI BOOL WINAPI          CharToOemBuffW( LPCWSTR, LPSTR, DWORD );
WINUSERAPI BOOL WINAPI          CharToOemW( LPCWSTR, LPSTR );
WINUSERAPI LPSTR WINAPI         CharUpperA( LPSTR );
WINUSERAPI DWORD WINAPI         CharUpperBuffA( LPSTR, DWORD );
WINUSERAPI DWORD WINAPI         CharUpperBuffW( LPWSTR, DWORD );
WINUSERAPI LPWSTR WINAPI        CharUpperW( LPWSTR );
WINUSERAPI BOOL WINAPI          CheckDlgButton( HWND, int, UINT );
WINUSERAPI DWORD WINAPI         CheckMenuItem( HMENU, UINT, UINT );
WINUSERAPI BOOL WINAPI          CheckRadioButton( HWND, int, int, int );
WINUSERAPI HWND WINAPI          ChildWindowFromPoint( HWND, POINT );
WINUSERAPI BOOL WINAPI          ClientToScreen( HWND, LPPOINT );
WINUSERAPI BOOL WINAPI          ClipCursor( CONST RECT * );
WINUSERAPI BOOL WINAPI          CloseClipboard( VOID );
WINUSERAPI BOOL WINAPI          CloseDesktop( HDESK );
WINUSERAPI BOOL WINAPI          CloseWindow( HWND );
WINUSERAPI BOOL WINAPI          CloseWindowStation( HWINSTA );
WINUSERAPI int WINAPI           CopyAcceleratorTableA( HACCEL, LPACCEL, int );
WINUSERAPI int WINAPI           CopyAcceleratorTableW( HACCEL, LPACCEL, int );
WINUSERAPI HICON WINAPI         CopyIcon( HICON );
WINUSERAPI BOOL WINAPI          CopyRect( LPRECT, CONST RECT * );
WINUSERAPI int WINAPI           CountClipboardFormats( VOID );
WINUSERAPI HACCEL WINAPI        CreateAcceleratorTableA( LPACCEL, int );
WINUSERAPI HACCEL WINAPI        CreateAcceleratorTableW( LPACCEL, int );
WINUSERAPI BOOL WINAPI          CreateCaret( HWND, HBITMAP, int, int );
WINUSERAPI HCURSOR WINAPI       CreateCursor( HINSTANCE, int, int, int, int, CONST VOID *, CONST VOID * );
WINUSERAPI HWND WINAPI          CreateDialogIndirectParamA( HINSTANCE, LPCDLGTEMPLATEA, HWND, DLGPROC, LPARAM );
WINUSERAPI HWND WINAPI          CreateDialogIndirectParamW( HINSTANCE, LPCDLGTEMPLATEW, HWND, DLGPROC, LPARAM );
WINUSERAPI HWND WINAPI          CreateDialogParamA( HINSTANCE, LPCSTR, HWND, DLGPROC, LPARAM );
WINUSERAPI HWND WINAPI          CreateDialogParamW( HINSTANCE, LPCWSTR, HWND, DLGPROC, LPARAM );
WINUSERAPI HICON WINAPI         CreateIcon( HINSTANCE, int, int, BYTE, BYTE, CONST BYTE *, CONST BYTE * );
WINUSERAPI HICON WINAPI         CreateIconFromResource( PBYTE, DWORD, BOOL, DWORD );
WINUSERAPI HICON WINAPI         CreateIconIndirect( PICONINFO );
WINUSERAPI HWND WINAPI          CreateMDIWindowA( LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HINSTANCE, LPARAM );
WINUSERAPI HWND WINAPI          CreateMDIWindowW( LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HINSTANCE, LPARAM );
WINUSERAPI HMENU WINAPI         CreateMenu( VOID );
WINUSERAPI HMENU WINAPI         CreatePopupMenu( VOID );
WINUSERAPI HWND WINAPI          CreateWindowExA( DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID );
WINUSERAPI HWND WINAPI          CreateWindowExW( DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID );
WINUSERAPI HWINSTA WINAPI       CreateWindowStationA( LPCSTR, DWORD, ACCESS_MASK, LPSECURITY_ATTRIBUTES );
WINUSERAPI HWINSTA WINAPI       CreateWindowStationW( LPCWSTR, DWORD, ACCESS_MASK, LPSECURITY_ATTRIBUTES );
WINUSERAPI LRESULT WINAPI       DefDlgProcA( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI LRESULT WINAPI       DefDlgProcW( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI LRESULT WINAPI       DefFrameProcA( HWND, HWND, UINT, WPARAM, LPARAM );
WINUSERAPI LRESULT WINAPI       DefFrameProcW( HWND, HWND, UINT, WPARAM, LPARAM );
WINUSERAPI LRESULT WINAPI       DefMDIChildProcA( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI LRESULT WINAPI       DefMDIChildProcW( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI LRESULT WINAPI       DefWindowProcA( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI LRESULT WINAPI       DefWindowProcW( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI HDWP WINAPI          DeferWindowPos( HDWP, HWND, HWND, int, int, int, int, UINT );
WINUSERAPI BOOL WINAPI          DeleteMenu( HMENU, UINT, UINT );
WINUSERAPI BOOL WINAPI          DeregisterShellHookWindow( HWND );
WINUSERAPI BOOL WINAPI          DestroyAcceleratorTable( HACCEL );
WINUSERAPI BOOL WINAPI          DestroyCaret( VOID );
WINUSERAPI BOOL WINAPI          DestroyCursor( HCURSOR );
WINUSERAPI BOOL WINAPI          DestroyIcon( HICON );
WINUSERAPI BOOL WINAPI          DestroyMenu( HMENU );
WINUSERAPI BOOL WINAPI          DestroyWindow( HWND );
WINUSERAPI INT_PTR WINAPI       DialogBoxIndirectParamA( HINSTANCE, LPCDLGTEMPLATEA, HWND, DLGPROC, LPARAM );
WINUSERAPI INT_PTR WINAPI       DialogBoxIndirectParamW( HINSTANCE, LPCDLGTEMPLATEW, HWND, DLGPROC, LPARAM );
WINUSERAPI INT_PTR WINAPI       DialogBoxParamA( HINSTANCE, LPCSTR, HWND, DLGPROC, LPARAM );
WINUSERAPI INT_PTR WINAPI       DialogBoxParamW( HINSTANCE, LPCWSTR, HWND, DLGPROC, LPARAM );
WINUSERAPI LRESULT WINAPI       DispatchMessageA( CONST MSG * );
WINUSERAPI LRESULT WINAPI       DispatchMessageW( CONST MSG * );
WINUSERAPI int WINAPI           DlgDirListA( HWND, LPSTR, int, int, UINT );
WINUSERAPI int WINAPI           DlgDirListComboBoxA( HWND, LPSTR, int, int, UINT );
WINUSERAPI int WINAPI           DlgDirListComboBoxW( HWND, LPWSTR, int, int, UINT );
WINUSERAPI int WINAPI           DlgDirListW( HWND, LPWSTR, int, int, UINT );
WINUSERAPI BOOL WINAPI          DlgDirSelectComboBoxExA( HWND, LPSTR, int, int );
WINUSERAPI BOOL WINAPI          DlgDirSelectComboBoxExW( HWND, LPWSTR, int, int );
WINUSERAPI BOOL WINAPI          DlgDirSelectExA( HWND, LPSTR, int, int );
WINUSERAPI BOOL WINAPI          DlgDirSelectExW( HWND, LPWSTR, int, int );
WINUSERAPI BOOL WINAPI          DrawFocusRect( HDC, CONST RECT * );
WINUSERAPI BOOL WINAPI          DrawIcon( HDC, int, int, HICON );
WINUSERAPI BOOL WINAPI          DrawMenuBar( HWND );
WINUSERAPI int WINAPI           DrawTextA( HDC, LPCSTR, int, LPRECT, UINT );
WINUSERAPI int WINAPI           DrawTextW( HDC, LPCWSTR, int, LPRECT, UINT );
WINUSERAPI BOOL WINAPI          EmptyClipboard( VOID );
WINUSERAPI BOOL WINAPI          EnableMenuItem( HMENU, UINT, UINT );
WINUSERAPI BOOL WINAPI          EnableScrollBar( HWND, UINT, UINT );
WINUSERAPI BOOL WINAPI          EnableWindow( HWND, BOOL );
WINUSERAPI BOOL WINAPI          EndDeferWindowPos( HDWP );
WINUSERAPI BOOL WINAPI          EndDialog( HWND, INT_PTR );
WINUSERAPI BOOL WINAPI          EndPaint( HWND, CONST PAINTSTRUCT * );
WINUSERAPI BOOL WINAPI          EndTask( HWND, BOOL, BOOL );
WINUSERAPI BOOL WINAPI          EnumChildWindows( HWND, WNDENUMPROC, LPARAM );
WINUSERAPI UINT WINAPI          EnumClipboardFormats( UINT );
WINUSERAPI BOOL WINAPI          EnumDesktopWindows( HDESK, WNDENUMPROC, LPARAM );
WINUSERAPI BOOL WINAPI          EnumDesktopsA( HWINSTA, DESKTOPENUMPROCA, LPARAM );
WINUSERAPI BOOL WINAPI          EnumDesktopsW( HWINSTA, DESKTOPENUMPROCW, LPARAM );
WINUSERAPI int WINAPI           EnumPropsA( HWND, PROPENUMPROCA );
WINUSERAPI int WINAPI           EnumPropsExA( HWND, PROPENUMPROCEXA, LPARAM );
WINUSERAPI int WINAPI           EnumPropsExW( HWND, PROPENUMPROCEXW, LPARAM );
WINUSERAPI int WINAPI           EnumPropsW( HWND, PROPENUMPROCW );
WINUSERAPI BOOL WINAPI          EnumThreadWindows( DWORD, WNDENUMPROC, LPARAM );
WINUSERAPI BOOL WINAPI          EnumWindowStationsA( WINSTAENUMPROCA, LPARAM );
WINUSERAPI BOOL WINAPI          EnumWindowStationsW( WINSTAENUMPROCW, LPARAM );
WINUSERAPI BOOL WINAPI          EnumWindows( WNDENUMPROC, LPARAM );
WINUSERAPI BOOL WINAPI          EqualRect( CONST RECT *, CONST RECT * );
WINUSERAPI int WINAPI           ExcludeUpdateRgn( HDC, HWND );
WINUSERAPI BOOL WINAPI          ExitWindowsEx( UINT, DWORD );
WINUSERAPI int WINAPI           FillRect( HDC, CONST RECT *, HBRUSH );
WINUSERAPI HWND WINAPI          FindWindowA( LPCSTR, LPCSTR );
WINUSERAPI HWND WINAPI          FindWindowW( LPCWSTR, LPCWSTR );
WINUSERAPI BOOL WINAPI          FlashWindow( HWND, BOOL );
WINUSERAPI int WINAPI           FrameRect( HDC, CONST RECT *, HBRUSH );
WINUSERAPI HWND WINAPI          GetActiveWindow( VOID );
WINUSERAPI SHORT WINAPI         GetAsyncKeyState( int );
WINUSERAPI HWND WINAPI          GetCapture( VOID );
WINUSERAPI UINT WINAPI          GetCaretBlinkTime( VOID );
WINUSERAPI BOOL WINAPI          GetCaretPos( LPPOINT );
WINUSERAPI BOOL WINAPI          GetClassInfoA( HINSTANCE, LPCSTR, LPWNDCLASSA );
WINUSERAPI BOOL WINAPI          GetClassInfoW( HINSTANCE, LPCWSTR, LPWNDCLASSW );
WINUSERAPI DWORD WINAPI         GetClassLongA( HWND, int );
WINUSERAPI DWORD WINAPI         GetClassLongW( HWND, int );
WINUSERAPI int WINAPI           GetClassNameA( HWND, LPSTR, int );
WINUSERAPI int WINAPI           GetClassNameW( HWND, LPWSTR, int );
WINUSERAPI WORD WINAPI          GetClassWord( HWND, int );
WINUSERAPI BOOL WINAPI          GetClientRect( HWND, LPRECT );
WINUSERAPI BOOL WINAPI          GetClipCursor( LPRECT );
WINUSERAPI HANDLE WINAPI        GetClipboardData( UINT );
WINUSERAPI int WINAPI           GetClipboardFormatNameA( UINT, LPSTR, int );
WINUSERAPI int WINAPI           GetClipboardFormatNameW( UINT, LPWSTR, int );
WINUSERAPI HWND WINAPI          GetClipboardOwner( VOID );
WINUSERAPI HWND WINAPI          GetClipboardViewer( VOID );
WINUSERAPI HCURSOR WINAPI       GetCursor( VOID );
WINUSERAPI BOOL WINAPI          GetCursorPos( LPPOINT );
WINUSERAPI HDC WINAPI           GetDC( HWND );
WINUSERAPI HDC WINAPI           GetDCEx( HWND, HRGN, DWORD );
WINUSERAPI HWND WINAPI          GetDesktopWindow( VOID );
WINUSERAPI long WINAPI          GetDialogBaseUnits( VOID );
WINUSERAPI int WINAPI           GetDlgCtrlID( HWND );
WINUSERAPI HWND WINAPI          GetDlgItem( HWND, int );
WINUSERAPI UINT WINAPI          GetDlgItemInt( HWND, int, BOOL *, BOOL );
WINUSERAPI UINT WINAPI          GetDlgItemTextA( HWND, int, LPSTR, int );
WINUSERAPI UINT WINAPI          GetDlgItemTextW( HWND, int, LPWSTR, int );
WINUSERAPI UINT WINAPI          GetDoubleClickTime( VOID );
WINUSERAPI HWND WINAPI          GetFocus( VOID );
WINUSERAPI HWND WINAPI          GetForegroundWindow( VOID );
WINUSERAPI BOOL WINAPI          GetIconInfo( HICON, PICONINFO );
WINUSERAPI BOOL WINAPI          GetInputState( VOID );
WINUSERAPI UINT WINAPI          GetKBCodePage( VOID );
WINUSERAPI int WINAPI           GetKeyNameTextA( LONG, LPSTR, int );
WINUSERAPI int WINAPI           GetKeyNameTextW( LONG, LPWSTR, int );
WINUSERAPI SHORT WINAPI         GetKeyState( int );
WINUSERAPI BOOL WINAPI          GetKeyboardLayoutNameA( LPSTR );
WINUSERAPI BOOL WINAPI          GetKeyboardLayoutNameW( LPWSTR );
WINUSERAPI BOOL WINAPI          GetKeyboardState( PBYTE );
WINUSERAPI int WINAPI           GetKeyboardType( int );
WINUSERAPI HWND WINAPI          GetLastActivePopup( HWND );
WINUSERAPI HMENU WINAPI         GetMenu( HWND );
WINUSERAPI LONG WINAPI          GetMenuCheckMarkDimensions( VOID );
WINUSERAPI int WINAPI           GetMenuItemCount( HMENU );
WINUSERAPI UINT WINAPI          GetMenuItemID( HMENU, int );
WINUSERAPI UINT WINAPI          GetMenuState( HMENU, UINT, UINT );
WINUSERAPI int WINAPI           GetMenuStringA( HMENU, UINT, LPSTR, int, UINT );
WINUSERAPI int WINAPI           GetMenuStringW( HMENU, UINT, LPWSTR, int, UINT );
WINUSERAPI BOOL WINAPI          GetMessageA( LPMSG, HWND, UINT, UINT );
WINUSERAPI LPARAM WINAPI        GetMessageExtraInfo( VOID );
WINUSERAPI DWORD WINAPI         GetMessagePos( VOID );
WINUSERAPI LONG WINAPI          GetMessageTime( VOID );
WINUSERAPI BOOL WINAPI          GetMessageW( LPMSG, HWND, UINT, UINT );
WINUSERAPI HWND WINAPI          GetNextDlgGroupItem( HWND, HWND, BOOL );
WINUSERAPI HWND WINAPI          GetNextDlgTabItem( HWND, HWND, BOOL );
WINUSERAPI HWND WINAPI          GetOpenClipboardWindow( VOID );
WINUSERAPI HWND WINAPI          GetParent( HWND );
WINUSERAPI BOOL WINAPI          GetPhysicalCursorPos( LPPOINT );
WINUSERAPI int WINAPI           GetPriorityClipboardFormat( UINT *, int );
WINUSERAPI HWINSTA WINAPI       GetProcessWindowStation( VOID );
WINUSERAPI HANDLE WINAPI        GetPropA( HWND, LPCSTR );
WINUSERAPI HANDLE WINAPI        GetPropW( HWND, LPCWSTR );
WINUSERAPI DWORD WINAPI         GetQueueStatus( UINT );
WINUSERAPI int WINAPI           GetScrollPos( HWND, int );
WINUSERAPI BOOL WINAPI          GetScrollRange( HWND, int, LPINT, LPINT );
WINUSERAPI HMENU WINAPI         GetSubMenu( HMENU, int );
WINUSERAPI DWORD WINAPI         GetSysColor( int );
WINUSERAPI HMENU WINAPI         GetSystemMenu( HWND, BOOL );
WINUSERAPI int WINAPI           GetSystemMetrics( int );
WINUSERAPI DWORD WINAPI         GetTabbedTextExtentA( HDC, LPCSTR, int, int, CONST INT * );
WINUSERAPI DWORD WINAPI         GetTabbedTextExtentW( HDC, LPCWSTR, int, int, CONST INT * );
WINUSERAPI HDESK WINAPI         GetThreadDesktop( DWORD );
WINUSERAPI HWND WINAPI          GetTopWindow( HWND );
WINUSERAPI BOOL WINAPI          GetUpdateRect( HWND, LPRECT, BOOL );
WINUSERAPI int WINAPI           GetUpdateRgn( HWND, HRGN, BOOL );
WINUSERAPI BOOL WINAPI          GetUserObjectInformationA( HANDLE, int, PVOID, DWORD, LPDWORD );
WINUSERAPI BOOL WINAPI          GetUserObjectInformationW( HANDLE, int, PVOID, DWORD, LPDWORD );
WINUSERAPI BOOL WINAPI          GetUserObjectSecurity( HANDLE, PSECURITY_INFORMATION, PSECURITY_DESCRIPTOR, DWORD, LPDWORD );
WINUSERAPI HWND WINAPI          GetWindow( HWND, UINT );
WINUSERAPI HDC WINAPI           GetWindowDC( HWND );
WINUSERAPI LONG WINAPI          GetWindowLongA( HWND, int );
WINUSERAPI LONG WINAPI          GetWindowLongW( HWND, int );
WINUSERAPI BOOL WINAPI          GetWindowPlacement( HWND, WINDOWPLACEMENT * );
WINUSERAPI BOOL WINAPI          GetWindowRect( HWND, LPRECT );
WINUSERAPI int WINAPI           GetWindowRgn( HWND, HRGN );
WINUSERAPI int WINAPI           GetWindowTextA( HWND, LPSTR, int );
WINUSERAPI int WINAPI           GetWindowTextLengthA( HWND );
WINUSERAPI int WINAPI           GetWindowTextLengthW( HWND );
WINUSERAPI int WINAPI           GetWindowTextW( HWND, LPWSTR, int );
WINUSERAPI DWORD WINAPI         GetWindowThreadProcessId( HWND, LPDWORD );
WINUSERAPI WORD WINAPI          GetWindowWord( HWND, int );
WINUSERAPI BOOL WINAPI          GrayStringA( HDC, HBRUSH, GRAYSTRINGPROC, LPARAM, int, int, int, int, int );
WINUSERAPI BOOL WINAPI          GrayStringW( HDC, HBRUSH, GRAYSTRINGPROC, LPARAM, int, int, int, int, int );
WINUSERAPI BOOL WINAPI          HideCaret( HWND );
WINUSERAPI BOOL WINAPI          HiliteMenuItem( HWND, HMENU, UINT, UINT );
WINUSERAPI BOOL WINAPI          InSendMessage( VOID );
WINUSERAPI BOOL WINAPI          InflateRect( LPRECT, int, int );
WINUSERAPI BOOL WINAPI          InsertMenuA( HMENU, UINT, UINT, UINT_PTR, LPCSTR );
WINUSERAPI BOOL WINAPI          InsertMenuW( HMENU, UINT, UINT, UINT_PTR, LPCWSTR );
WINUSERAPI int WINAPI           InternalGetWindowText( HWND, LPWSTR, int );
WINUSERAPI BOOL WINAPI          IntersectRect( LPRECT, CONST RECT *, CONST RECT * );
WINUSERAPI BOOL WINAPI          InvalidateRect( HWND, CONST RECT *, BOOL );
WINUSERAPI BOOL WINAPI          InvalidateRgn( HWND, HRGN, BOOL );
WINUSERAPI BOOL WINAPI          InvertRect( HDC, CONST RECT * );
WINUSERAPI BOOL WINAPI          IsCharAlphaA( CHAR );
WINUSERAPI BOOL WINAPI          IsCharAlphaNumericA( CHAR );
WINUSERAPI BOOL WINAPI          IsCharAlphaNumericW( WCHAR );
WINUSERAPI BOOL WINAPI          IsCharAlphaW( WCHAR );
WINUSERAPI BOOL WINAPI          IsCharLowerA( CHAR );
WINUSERAPI BOOL WINAPI          IsCharLowerW( WCHAR );
WINUSERAPI BOOL WINAPI          IsCharUpperA( CHAR );
WINUSERAPI BOOL WINAPI          IsCharUpperW( WCHAR );
WINUSERAPI BOOL WINAPI          IsChild( HWND, HWND );
WINUSERAPI BOOL WINAPI          IsClipboardFormatAvailable( UINT );
WINUSERAPI BOOL WINAPI          IsDialogMessageA( HWND, LPMSG );
WINUSERAPI BOOL WINAPI          IsDialogMessageW( HWND, LPMSG );
WINUSERAPI UINT WINAPI          IsDlgButtonChecked( HWND, int );
WINUSERAPI BOOL WINAPI          IsHungAppWindow( HWND );
WINUSERAPI BOOL WINAPI          IsIconic( HWND );
WINUSERAPI BOOL WINAPI          IsMenu( HMENU );
WINUSERAPI BOOL WINAPI          IsRectEmpty( CONST RECT * );
WINUSERAPI BOOL WINAPI          IsWindow( HWND );
WINUSERAPI BOOL WINAPI          IsWindowEnabled( HWND );
WINUSERAPI BOOL WINAPI          IsWindowUnicode( HWND );
WINUSERAPI BOOL WINAPI          IsWindowVisible( HWND );
WINUSERAPI BOOL WINAPI          IsZoomed( HWND );
WINUSERAPI BOOL WINAPI          KillTimer( HWND, UINT_PTR );
WINUSERAPI HACCEL WINAPI        LoadAcceleratorsA( HINSTANCE, LPCSTR );
WINUSERAPI HACCEL WINAPI        LoadAcceleratorsW( HINSTANCE, LPCWSTR );
WINUSERAPI HBITMAP WINAPI       LoadBitmapA( HINSTANCE, LPCSTR );
WINUSERAPI HBITMAP WINAPI       LoadBitmapW( HINSTANCE, LPCWSTR );
WINUSERAPI HCURSOR WINAPI       LoadCursorA( HINSTANCE, LPCSTR );
WINUSERAPI HCURSOR WINAPI       LoadCursorFromFileA( LPCSTR );
WINUSERAPI HCURSOR WINAPI       LoadCursorFromFileW( LPCWSTR );
WINUSERAPI HCURSOR WINAPI       LoadCursorW( HINSTANCE, LPCWSTR );
WINUSERAPI HICON WINAPI         LoadIconA( HINSTANCE, LPCSTR );
WINUSERAPI HICON WINAPI         LoadIconW( HINSTANCE, LPCWSTR );
WINUSERAPI HKL WINAPI           LoadKeyboardLayoutA( LPCSTR, UINT );
WINUSERAPI HKL WINAPI           LoadKeyboardLayoutW( LPCWSTR, UINT );
WINUSERAPI HMENU WINAPI         LoadMenuA( HINSTANCE, LPCSTR );
WINUSERAPI HMENU WINAPI         LoadMenuIndirectA( CONST MENUTEMPLATEA * );
WINUSERAPI HMENU WINAPI         LoadMenuIndirectW( CONST MENUTEMPLATEW * );
WINUSERAPI HMENU WINAPI         LoadMenuW( HINSTANCE, LPCWSTR );
WINUSERAPI int WINAPI           LoadStringA( HINSTANCE, UINT, LPSTR, int );
WINUSERAPI int WINAPI           LoadStringW( HINSTANCE, UINT, LPWSTR, int );
WINUSERAPI BOOL WINAPI          LockWindowUpdate( HWND );
WINUSERAPI int WINAPI           LookupIconIdFromDirectory( PBYTE, BOOL );
WINUSERAPI BOOL WINAPI          MapDialogRect( HWND, LPRECT );
WINUSERAPI UINT WINAPI          MapVirtualKeyA( UINT, UINT );
WINUSERAPI UINT WINAPI          MapVirtualKeyW( UINT, UINT );
WINUSERAPI int WINAPI           MapWindowPoints( HWND, HWND, LPPOINT, UINT );
WINUSERAPI BOOL WINAPI          MessageBeep( UINT );
WINUSERAPI int WINAPI           MessageBoxA( HWND, LPCSTR, LPCSTR, UINT );
WINUSERAPI int WINAPI           MessageBoxExA( HWND, LPCSTR, LPCSTR, UINT, WORD );
WINUSERAPI int WINAPI           MessageBoxExW( HWND, LPCWSTR, LPCWSTR, UINT, WORD );
WINUSERAPI int WINAPI           MessageBoxW( HWND, LPCWSTR, LPCWSTR, UINT );
WINUSERAPI BOOL WINAPI          ModifyMenuA( HMENU, UINT, UINT, UINT_PTR, LPCSTR );
WINUSERAPI BOOL WINAPI          ModifyMenuW( HMENU, UINT, UINT, UINT_PTR, LPCWSTR );
WINUSERAPI BOOL WINAPI          MoveWindow( HWND, int, int, int, int, BOOL );
WINUSERAPI DWORD WINAPI         MsgWaitForMultipleObjects( DWORD, CONST HANDLE *, BOOL, DWORD, DWORD );
WINUSERAPI DWORD WINAPI         MsgWaitForMultipleObjectsEx( DWORD, CONST HANDLE *, DWORD, DWORD, DWORD );
WINUSERAPI DWORD WINAPI         OemKeyScan( WORD );
WINUSERAPI BOOL WINAPI          OemToCharA( LPCSTR, LPSTR );
WINUSERAPI BOOL WINAPI          OemToCharBuffA( LPCSTR, LPSTR, DWORD );
WINUSERAPI BOOL WINAPI          OemToCharBuffW( LPCWSTR, LPWSTR, DWORD );
WINUSERAPI BOOL WINAPI          OemToCharW( LPCSTR, LPWSTR );
WINUSERAPI BOOL WINAPI          OffsetRect( LPRECT, int, int );
WINUSERAPI BOOL WINAPI          OpenClipboard( HWND );
WINUSERAPI HDESK WINAPI         OpenDesktopA( LPCSTR, DWORD, BOOL, ACCESS_MASK );
WINUSERAPI HDESK WINAPI         OpenDesktopW( LPCWSTR, DWORD, BOOL, ACCESS_MASK );
WINUSERAPI BOOL WINAPI          OpenIcon( HWND );
WINUSERAPI HDESK WINAPI         OpenInputDesktop( DWORD, BOOL, ACCESS_MASK );
WINUSERAPI HWINSTA WINAPI       OpenWindowStationA( LPCSTR, BOOL, ACCESS_MASK );
WINUSERAPI HWINSTA WINAPI       OpenWindowStationW( LPCWSTR, BOOL, ACCESS_MASK );
WINUSERAPI BOOL WINAPI          PeekMessageA( LPMSG, HWND, UINT, UINT, UINT );
WINUSERAPI BOOL WINAPI          PeekMessageW( LPMSG, HWND, UINT, UINT, UINT );
WINUSERAPI BOOL WINAPI          PostMessageA( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI BOOL WINAPI          PostMessageW( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI VOID WINAPI          PostQuitMessage( int );
WINUSERAPI BOOL WINAPI          PostThreadMessageA( DWORD, UINT, WPARAM, LPARAM );
WINUSERAPI BOOL WINAPI          PostThreadMessageW( DWORD, UINT, WPARAM, LPARAM );
WINUSERAPI UINT WINAPI          PrivateExtractIconsA( LPCSTR, int, int, int, HICON *, UINT *, UINT, UINT );
WINUSERAPI UINT WINAPI          PrivateExtractIconsW( LPCWSTR, int, int, int, HICON *, UINT *, UINT, UINT );
WINUSERAPI BOOL WINAPI          PtInRect( CONST RECT *, POINT );
WINUSERAPI BOOL WINAPI          RedrawWindow( HWND, CONST RECT *, HRGN, UINT );
WINUSERAPI ATOM WINAPI          RegisterClassA( CONST WNDCLASSA * );
WINUSERAPI ATOM WINAPI          RegisterClassW( CONST WNDCLASSW * );
WINUSERAPI UINT WINAPI          RegisterClipboardFormatA( LPCSTR );
WINUSERAPI UINT WINAPI          RegisterClipboardFormatW( LPCWSTR );
WINUSERAPI BOOL WINAPI          RegisterHotKey( HWND, int, UINT, UINT );
WINUSERAPI BOOL WINAPI          RegisterShellHookWindow( HWND );
WINUSERAPI UINT WINAPI          RegisterWindowMessageA( LPCSTR );
WINUSERAPI UINT WINAPI          RegisterWindowMessageW( LPCWSTR );
WINUSERAPI BOOL WINAPI          ReleaseCapture( VOID );
WINUSERAPI int WINAPI           ReleaseDC( HWND, HDC );
WINUSERAPI BOOL WINAPI          RemoveMenu( HMENU, UINT, UINT );
WINUSERAPI HANDLE WINAPI        RemovePropA( HWND, LPCSTR );
WINUSERAPI HANDLE WINAPI        RemovePropW( HWND, LPCWSTR );
WINUSERAPI BOOL WINAPI          ReplyMessage( LRESULT );
WINUSERAPI BOOL WINAPI          ScreenToClient( HWND, LPPOINT );
WINUSERAPI BOOL WINAPI          ScrollDC( HDC, int, int, CONST RECT *, CONST RECT *, HRGN, LPRECT );
WINUSERAPI BOOL WINAPI          ScrollWindow( HWND, int, int, CONST RECT *, CONST RECT * );
WINUSERAPI int WINAPI           ScrollWindowEx( HWND, int, int, CONST RECT *, CONST RECT *, HRGN, LPRECT, UINT );
WINUSERAPI LRESULT WINAPI       SendDlgItemMessageA( HWND, int, UINT, WPARAM, LPARAM );
WINUSERAPI LRESULT WINAPI       SendDlgItemMessageW( HWND, int, UINT, WPARAM, LPARAM );
WINUSERAPI LRESULT WINAPI       SendMessageA( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI BOOL WINAPI          SendMessageCallbackA( HWND, UINT, WPARAM, LPARAM, SENDASYNCPROC, ULONG_PTR );
WINUSERAPI BOOL WINAPI          SendMessageCallbackW( HWND, UINT, WPARAM, LPARAM, SENDASYNCPROC, ULONG_PTR );
WINUSERAPI LRESULT WINAPI       SendMessageTimeoutA( HWND, UINT, WPARAM, LPARAM, UINT, UINT, PDWORD_PTR );
WINUSERAPI LRESULT WINAPI       SendMessageTimeoutW( HWND, UINT, WPARAM, LPARAM, UINT, UINT, PDWORD_PTR );
WINUSERAPI LRESULT WINAPI       SendMessageW( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI BOOL WINAPI          SendNotifyMessageA( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI BOOL WINAPI          SendNotifyMessageW( HWND, UINT, WPARAM, LPARAM );
WINUSERAPI HWND WINAPI          SetActiveWindow( HWND );
WINUSERAPI HWND WINAPI          SetCapture( HWND );
WINUSERAPI BOOL WINAPI          SetCaretBlinkTime( UINT );
WINUSERAPI BOOL WINAPI          SetCaretPos( int, int );
WINUSERAPI DWORD WINAPI         SetClassLongA( HWND, int, LONG );
WINUSERAPI DWORD WINAPI         SetClassLongW( HWND, int, LONG );
WINUSERAPI WORD WINAPI          SetClassWord( HWND, int, WORD );
WINUSERAPI HANDLE WINAPI        SetClipboardData( UINT, HANDLE );
WINUSERAPI HWND WINAPI          SetClipboardViewer( HWND );
WINUSERAPI HCURSOR WINAPI       SetCursor( HCURSOR );
WINUSERAPI BOOL WINAPI          SetCursorPos( int, int );
WINUSERAPI VOID WINAPI          SetDebugErrorLevel( DWORD );
WINUSERAPI BOOL WINAPI          SetDlgItemInt( HWND, int, UINT, BOOL );
WINUSERAPI BOOL WINAPI          SetDlgItemTextA( HWND, int, LPCSTR );
WINUSERAPI BOOL WINAPI          SetDlgItemTextW( HWND, int, LPCWSTR );
WINUSERAPI BOOL WINAPI          SetDoubleClickTime( UINT );
WINUSERAPI HWND WINAPI          SetFocus( HWND );
WINUSERAPI BOOL WINAPI          SetForegroundWindow( HWND );
WINUSERAPI BOOL WINAPI          SetKeyboardState( LPBYTE );
WINUSERAPI VOID WINAPI          SetLastErrorEx( DWORD, DWORD );
WINUSERAPI BOOL WINAPI          SetMenu( HWND, HMENU );
WINUSERAPI BOOL WINAPI          SetMenuItemBitmaps( HMENU, UINT, UINT, HBITMAP, HBITMAP );
WINUSERAPI BOOL WINAPI          SetMessageQueue( int );
WINUSERAPI HWND WINAPI          SetParent( HWND, HWND );
WINUSERAPI BOOL WINAPI          SetPhysicalCursorPos( int, int );
WINUSERAPI BOOL WINAPI          SetProcessWindowStation( HWINSTA );
WINUSERAPI BOOL WINAPI          SetPropA( HWND, LPCSTR, HANDLE );
WINUSERAPI BOOL WINAPI          SetPropW( HWND, LPCWSTR, HANDLE );
WINUSERAPI BOOL WINAPI          SetRect( LPRECT, int, int, int, int );
WINUSERAPI BOOL WINAPI          SetRectEmpty( LPRECT );
WINUSERAPI int WINAPI           SetScrollPos( HWND, int, int, BOOL );
WINUSERAPI int WINAPI           SetScrollRange( HWND, int, int, int, BOOL );
WINUSERAPI BOOL WINAPI          SetSysColors( int, CONST INT *, CONST COLORREF * );
WINUSERAPI BOOL WINAPI          SetSystemCursor( HCURSOR, DWORD );
WINUSERAPI BOOL WINAPI          SetThreadDesktop( HDESK );
WINUSERAPI UINT_PTR WINAPI      SetTimer( HWND, UINT_PTR, UINT, TIMERPROC );
WINUSERAPI BOOL WINAPI          SetUserObjectInformationA( HANDLE, int, PVOID, DWORD );
WINUSERAPI BOOL WINAPI          SetUserObjectInformationW( HANDLE, int, PVOID, DWORD );
WINUSERAPI BOOL WINAPI          SetUserObjectSecurity( HANDLE, PSECURITY_INFORMATION, PSECURITY_DESCRIPTOR );
WINUSERAPI LONG WINAPI          SetWindowLongA( HWND, int, LONG );
WINUSERAPI LONG WINAPI          SetWindowLongW( HWND, int, LONG );
WINUSERAPI BOOL WINAPI          SetWindowPlacement( HWND, CONST WINDOWPLACEMENT * );
WINUSERAPI BOOL WINAPI          SetWindowPos( HWND, HWND, int, int, int, int, UINT );
WINUSERAPI int WINAPI           SetWindowRgn( HWND, HRGN, BOOL );
WINUSERAPI BOOL WINAPI          SetWindowTextA( HWND, LPCSTR );
WINUSERAPI BOOL WINAPI          SetWindowTextW( HWND, LPCWSTR );
WINUSERAPI WORD WINAPI          SetWindowWord( HWND, int, WORD );
WINUSERAPI HHOOK WINAPI         SetWindowsHookA( int, HOOKPROC );
WINUSERAPI HHOOK WINAPI         SetWindowsHookExA( int, HOOKPROC, HINSTANCE, DWORD );
WINUSERAPI HHOOK WINAPI         SetWindowsHookExW( int, HOOKPROC, HINSTANCE, DWORD );
WINUSERAPI HHOOK WINAPI         SetWindowsHookW( int, HOOKPROC );
WINUSERAPI BOOL WINAPI          ShowCaret( HWND );
WINUSERAPI int WINAPI           ShowCursor( BOOL );
WINUSERAPI BOOL WINAPI          ShowScrollBar( HWND, int, BOOL );
WINUSERAPI BOOL WINAPI          ShowOwnedPopups( HWND, BOOL );
WINUSERAPI BOOL WINAPI          ShowWindow( HWND, int );
WINUSERAPI BOOL WINAPI          ShutdownBlockReasonCreate( HWND, LPCWSTR );
WINUSERAPI BOOL WINAPI          ShutdownBlockReasonDestroy( HWND );
WINUSERAPI BOOL WINAPI          ShutdownBlockReasonQuery( HWND, LPWSTR, DWORD * );
WINUSERAPI BOOL WINAPI          SubtractRect( LPRECT, CONST RECT *, CONST RECT * );
WINUSERAPI BOOL WINAPI          SwapMouseButton( BOOL );
WINUSERAPI BOOL WINAPI          SwitchDesktop( HDESK );
WINUSERAPI BOOL WINAPI          SystemParametersInfoA( UINT, UINT, PVOID, UINT );
WINUSERAPI BOOL WINAPI          SystemParametersInfoW( UINT, UINT, PVOID, UINT );
WINUSERAPI LONG WINAPI          TabbedTextOutA( HDC, int, int, LPCSTR, int, int, CONST INT *, int );
WINUSERAPI LONG WINAPI          TabbedTextOutW( HDC, int, int, LPCWSTR, int, int, CONST INT *, int );
WINUSERAPI int WINAPI           ToAscii( UINT, UINT, CONST BYTE *, LPWORD, UINT );
WINUSERAPI int WINAPI           ToUnicode( UINT, UINT, CONST BYTE *, LPWSTR, int, UINT );
WINUSERAPI BOOL WINAPI          TrackPopupMenu( HMENU, UINT, int, int, int, HWND, CONST RECT * );
WINUSERAPI int WINAPI           TranslateAcceleratorA( HWND, HACCEL, LPMSG );
WINUSERAPI int WINAPI           TranslateAcceleratorW( HWND, HACCEL, LPMSG );
WINUSERAPI BOOL WINAPI          TranslateMDISysAccel( HWND, LPMSG );
WINUSERAPI BOOL WINAPI          TranslateMessage( CONST MSG * );
WINUSERAPI BOOL WINAPI          UnhookWindowsHook( int, HOOKPROC );
WINUSERAPI BOOL WINAPI          UnhookWindowsHookEx( HHOOK );
WINUSERAPI BOOL WINAPI          UnionRect( LPRECT, CONST RECT *, CONST RECT * );
WINUSERAPI BOOL WINAPI          UnloadKeyboardLayout( HKL );
WINUSERAPI BOOL WINAPI          UnregisterClassA( LPCSTR, HINSTANCE );
WINUSERAPI BOOL WINAPI          UnregisterClassW( LPCWSTR, HINSTANCE );
WINUSERAPI BOOL WINAPI          UnregisterHotKey( HWND, int );
WINUSERAPI BOOL WINAPI          UpdateWindow( HWND );
WINUSERAPI BOOL WINAPI          ValidateRect( HWND, CONST RECT * );
WINUSERAPI BOOL WINAPI          ValidateRgn( HWND, HRGN );
WINUSERAPI SHORT WINAPI         VkKeyScanA( CHAR );
WINUSERAPI SHORT WINAPI         VkKeyScanW( WCHAR );
WINUSERAPI DWORD WINAPI         WaitForInputIdle( HANDLE, DWORD );
WINUSERAPI BOOL WINAPI          WaitMessage( VOID );
WINUSERAPI BOOL WINAPI          WinHelpA( HWND, LPCSTR, UINT, ULONG_PTR );
WINUSERAPI BOOL WINAPI          WinHelpW( HWND, LPCWSTR, UINT, ULONG_PTR );
WINUSERAPI HWND WINAPI          WindowFromDC( HDC );
WINUSERAPI HWND WINAPI          WindowFromPoint( POINT );
WINUSERAPI VOID WINAPI          keybd_event( BYTE, BYTE, DWORD, ULONG_PTR );
WINUSERAPI VOID WINAPI          mouse_event( DWORD, DWORD, DWORD, DWORD, ULONG_PTR );
WINUSERAPI int WINAPIV          wsprintfA( LPSTR, LPCSTR, ... );
WINUSERAPI int WINAPIV          wsprintfW( LPWSTR, LPCWSTR, ... );
WINUSERAPI int WINAPI           wvsprintfA( LPSTR, LPCSTR, va_list );
WINUSERAPI int WINAPI           wvsprintfW( LPWSTR, LPCWSTR, va_list );
#ifdef _WINGDI_
WINUSERAPI LONG WINAPI          ChangeDisplaySettingsA( LPDEVMODEA, DWORD );
WINUSERAPI LONG WINAPI          ChangeDisplaySettingsExA( LPCSTR, LPDEVMODEA, HWND, DWORD, LPVOID );
WINUSERAPI LONG WINAPI          ChangeDisplaySettingsExW( LPCWSTR, LPDEVMODEW, HWND, DWORD, LPVOID );
WINUSERAPI LONG WINAPI          ChangeDisplaySettingsW( LPDEVMODEW, DWORD );
WINUSERAPI HDESK WINAPI         CreateDesktopA( LPCSTR, LPCSTR, LPDEVMODEA, DWORD, ACCESS_MASK, LPSECURITY_ATTRIBUTES );
WINUSERAPI HDESK WINAPI         CreateDesktopExA( LPCSTR, LPCSTR, LPDEVMODEA, DWORD, ACCESS_MASK, LPSECURITY_ATTRIBUTES, ULONG, PVOID );
WINUSERAPI HDESK WINAPI         CreateDesktopExW( LPCWSTR, LPCWSTR, LPDEVMODEW, DWORD, ACCESS_MASK, LPSECURITY_ATTRIBUTES, ULONG, PVOID );
WINUSERAPI HDESK WINAPI         CreateDesktopW( LPCWSTR, LPCWSTR, LPDEVMODEW, DWORD, ACCESS_MASK, LPSECURITY_ATTRIBUTES );
WINUSERAPI BOOL WINAPI          EnumDisplaySettingsA( LPCSTR, DWORD, LPDEVMODEA );
WINUSERAPI BOOL WINAPI          EnumDisplaySettingsW( LPCWSTR, DWORD, LPDEVMODEW );
#endif
#if (WINVER >= 0x0400)
WINUSERAPI WORD WINAPI          CascadeWindows( HWND, UINT, CONST RECT *, UINT, const HWND * );
WINUSERAPI LPSTR WINAPI         CharNextExA( WORD, LPCSTR, DWORD );
WINUSERAPI LPSTR WINAPI         CharPrevExA( WORD, LPCSTR, LPCSTR, DWORD );
WINUSERAPI BOOL WINAPI          CheckMenuRadioItem( HMENU, UINT, UINT, UINT, UINT );
WINUSERAPI HWND WINAPI          ChildWindowFromPointEx( HWND, POINT, UINT );
WINUSERAPI HANDLE WINAPI        CopyImage( HANDLE, UINT, int, int, UINT );
WINUSERAPI HICON WINAPI         CreateIconFromResourceEx( PBYTE, DWORD, BOOL, DWORD, int, int, UINT );
WINUSERAPI BOOL WINAPI          DragDetect( HWND, POINT );
WINUSERAPI DWORD WINAPI         DragObject( HWND, HWND, UINT, ULONG_PTR, HCURSOR );
WINUSERAPI BOOL WINAPI          DrawAnimatedRects( HWND, int, CONST RECT *, CONST RECT * );
WINUSERAPI BOOL WINAPI          DrawCaption( HWND, HDC, CONST RECT *, UINT );
WINUSERAPI BOOL WINAPI          DrawEdge( HDC, LPRECT, UINT, UINT );
WINUSERAPI BOOL WINAPI          DrawFrameControl( HDC, LPRECT, UINT, UINT );
WINUSERAPI BOOL WINAPI          DrawIconEx( HDC, int, int, HICON, int, int, UINT, HBRUSH, UINT );
WINUSERAPI BOOL WINAPI          DrawStateA( HDC, HBRUSH, DRAWSTATEPROC, LPARAM, WPARAM, int, int, int, int, UINT );
WINUSERAPI BOOL WINAPI          DrawStateW( HDC, HBRUSH, DRAWSTATEPROC, LPARAM, WPARAM, int, int, int, int, UINT );
WINUSERAPI int WINAPI           DrawTextExA( HDC, LPSTR, int, LPRECT, UINT, LPDRAWTEXTPARAMS );
WINUSERAPI int WINAPI           DrawTextExW( HDC, LPWSTR, int, LPRECT, UINT, LPDRAWTEXTPARAMS );
WINUSERAPI HWND WINAPI          FindWindowExA( HWND, HWND, LPCSTR, LPCSTR );
WINUSERAPI HWND WINAPI          FindWindowExW( HWND, HWND, LPCWSTR, LPCWSTR );
WINUSERAPI BOOL WINAPI          GetClassInfoExA( HINSTANCE, LPCSTR, LPWNDCLASSEXA );
WINUSERAPI BOOL WINAPI          GetClassInfoExW( HINSTANCE, LPCWSTR, LPWNDCLASSEXW );
WINUSERAPI HKL WINAPI           GetKeyboardLayout( DWORD );
WINUSERAPI int WINAPI           GetKeyboardLayoutList( int, HKL * );
WINUSERAPI DWORD WINAPI         GetMenuContextHelpId( HMENU );
WINUSERAPI UINT WINAPI          GetMenuDefaultItem( HMENU, UINT, UINT );
WINUSERAPI BOOL WINAPI          GetMenuItemInfoA( HMENU, UINT, BOOL, LPMENUITEMINFOA );
WINUSERAPI BOOL WINAPI          GetMenuItemInfoW( HMENU, UINT, BOOL, LPMENUITEMINFOW );
WINUSERAPI BOOL WINAPI          GetMenuItemRect( HWND, HMENU, UINT, LPRECT );
WINUSERAPI BOOL WINAPI          GetScrollInfo( HWND, int, LPSCROLLINFO );
WINUSERAPI HWND WINAPI          GetShellWindow( VOID );
WINUSERAPI HBRUSH WINAPI        GetSysColorBrush( int );
WINUSERAPI DWORD WINAPI         GetWindowContextHelpId( HWND );
WINUSERAPI BOOL WINAPI          InsertMenuItemA( HMENU, UINT, BOOL, LPCMENUITEMINFOA );
WINUSERAPI BOOL WINAPI          InsertMenuItemW( HMENU, UINT, BOOL, LPCMENUITEMINFOW );
WINUSERAPI HANDLE WINAPI        LoadImageA( HINSTANCE, LPCSTR, UINT, int, int, UINT );
WINUSERAPI HANDLE WINAPI        LoadImageW( HINSTANCE, LPCWSTR, UINT, int, int, UINT );
WINUSERAPI int WINAPI           LookupIconIdFromDirectoryEx( PBYTE, BOOL, int, int, UINT );
WINUSERAPI UINT WINAPI          MapVirtualKeyExA( UINT, UINT, HKL );
WINUSERAPI UINT WINAPI          MapVirtualKeyExW( UINT, UINT, HKL );
WINUSERAPI int WINAPI           MenuItemFromPoint( HWND, HMENU, POINT );
WINUSERAPI int WINAPI           MessageBoxIndirectA( CONST MSGBOXPARAMSA * );
WINUSERAPI int WINAPI           MessageBoxIndirectW( CONST MSGBOXPARAMSW * );
WINUSERAPI BOOL WINAPI          PaintDesktop( HDC );
WINUSERAPI ATOM WINAPI          RegisterClassExA( CONST WNDCLASSEXA * );
WINUSERAPI ATOM WINAPI          RegisterClassExW( CONST WNDCLASSEXW * );
WINUSERAPI BOOL WINAPI          SetMenuContextHelpId( HMENU, DWORD );
WINUSERAPI BOOL WINAPI          SetMenuDefaultItem( HMENU, UINT, UINT );
WINUSERAPI BOOL WINAPI          SetMenuItemInfoA( HMENU, UINT, BOOL, LPCMENUITEMINFOA );
WINUSERAPI BOOL WINAPI          SetMenuItemInfoW( HMENU, UINT, BOOL, LPCMENUITEMINFOW );
WINUSERAPI LPARAM WINAPI        SetMessageExtraInfo( LPARAM );
WINUSERAPI int WINAPI           SetScrollInfo( HWND, int, LPCSCROLLINFO, BOOL );
WINUSERAPI BOOL WINAPI          SetWindowContextHelpId( HWND, DWORD );
WINUSERAPI BOOL WINAPI          ShowWindowAsync( HWND, int );
WINUSERAPI VOID WINAPI          SwitchToThisWindow( HWND, BOOL );
WINUSERAPI WORD WINAPI          TileWindows( HWND, UINT, CONST RECT *, UINT, const HWND * );
WINUSERAPI int WINAPI           ToAsciiEx( UINT, UINT, CONST BYTE *, LPWORD, UINT, HKL );
WINUSERAPI int WINAPI           ToUnicodeEx( UINT, UINT, CONST BYTE *, LPWSTR, int, UINT, HKL );
WINUSERAPI BOOL WINAPI          TrackPopupMenuEx( HMENU, UINT, int, int, HWND, LPTPMPARAMS );
WINUSERAPI SHORT WINAPI         VkKeyScanExA( CHAR, HKL );
WINUSERAPI SHORT WINAPI         VkKeyScanExW( WCHAR, HKL );
#endif
#if (WINVER >= 0x0500)
WINUSERAPI BOOL WINAPI          AnimateWindow( HWND, DWORD, DWORD );
WINUSERAPI BOOL WINAPI          EndMenu( VOID );
WINUSERAPI BOOL WINAPI          EnumDisplayMonitors( HDC, LPCRECT, MONITORENUMPROC, LPARAM );
WINUSERAPI BOOL WINAPI          FlashWindowEx( PFLASHWINFO );
WINUSERAPI BOOL WINAPI          GetAltTabInfoA( HWND, int, PALTTABINFO, LPSTR, UINT );
WINUSERAPI BOOL WINAPI          GetAltTabInfoW( HWND, int, PALTTABINFO, LPWSTR, UINT );
WINUSERAPI HWND WINAPI          GetAncestor( HWND, UINT );
WINUSERAPI DWORD WINAPI         GetClipboardSequenceNumber( VOID );
WINUSERAPI BOOL WINAPI          GetComboBoxInfo( HWND, PCOMBOBOXINFO );
WINUSERAPI BOOL WINAPI          GetCursorInfo( PCURSORINFO );
WINUSERAPI BOOL WINAPI          GetGUIThreadInfo( DWORD, PGUITHREADINFO );
WINUSERAPI DWORD WINAPI         GetGuiResources( HANDLE, DWORD );
WINUSERAPI DWORD WINAPI         GetListBoxInfo( HWND );
WINUSERAPI BOOL WINAPI          GetMenuBarInfo( HWND, LONG, LONG, PMENUBARINFO );
WINUSERAPI BOOL WINAPI          GetMenuInfo( HMENU, LPMENUINFO );
WINUSERAPI BOOL WINAPI          GetMonitorInfoA( HMONITOR, LPMONITORINFO );
WINUSERAPI BOOL WINAPI          GetMonitorInfoW( HMONITOR, LPMONITORINFO );
WINUSERAPI int WINAPI           GetMouseMovePointsEx( UINT, LPMOUSEMOVEPOINT, LPMOUSEMOVEPOINT, int, DWORD );
WINUSERAPI BOOL WINAPI          GetProcessDefaultLayout( DWORD * );
WINUSERAPI BOOL WINAPI          GetScrollBarInfo( HWND, LONG, PSCROLLBARINFO );
WINUSERAPI BOOL WINAPI          GetTitleBarInfo( HWND, PTITLEBARINFO );
WINUSERAPI BOOL WINAPI          GetWindowInfo( HWND, PWINDOWINFO );
WINUSERAPI UINT WINAPI          GetWindowModuleFileNameA( HWND, LPSTR, UINT );
WINUSERAPI UINT WINAPI          GetWindowModuleFileNameW( HWND, LPWSTR, UINT );
WINUSERAPI DWORD WINAPI         InSendMessageEx( LPVOID );
WINUSERAPI HMONITOR WINAPI      MonitorFromPoint( POINT, DWORD );
WINUSERAPI HMONITOR WINAPI      MonitorFromRect( LPCRECT, DWORD );
WINUSERAPI HMONITOR WINAPI      MonitorFromWindow( HWND, DWORD );
WINUSERAPI VOID WINAPI          NotifyWinEvent( DWORD, HWND, LONG, LONG );
WINUSERAPI HWND WINAPI          RealChildWindowFromPoint( HWND, POINT );
WINUSERAPI UINT WINAPI          RealGetWindowClassA( HWND, LPSTR, UINT );
WINUSERAPI UINT WINAPI          RealGetWindowClassW( HWND, LPWSTR, UINT );
WINUSERAPI HDEVNOTIFY WINAPI    RegisterDeviceNotificationA( HANDLE, LPVOID, DWORD );
WINUSERAPI HDEVNOTIFY WINAPI    RegisterDeviceNotificationW( HANDLE, LPVOID, DWORD );
WINUSERAPI BOOL WINAPI          SetMenuInfo( HMENU, LPCMENUINFO );
WINUSERAPI BOOL WINAPI          SetProcessDefaultLayout( DWORD );
WINUSERAPI HWINEVENTHOOK WINAPI SetWinEventHook( DWORD, DWORD, HMODULE, WINEVENTPROC, DWORD, DWORD, DWORD );
WINUSERAPI BOOL WINAPI          UnhookWinEvent( HWINEVENTHOOK );
WINUSERAPI BOOL WINAPI          UnregisterDeviceNotification( HDEVNOTIFY );
#ifdef _WINGDI_
WINUSERAPI BOOL WINAPI          EnumDisplayDevicesA( LPCSTR, DWORD, PDISPLAY_DEVICEA, DWORD );
WINUSERAPI BOOL WINAPI          EnumDisplayDevicesW( LPCWSTR, DWORD, PDISPLAY_DEVICEW, DWORD );
WINUSERAPI BOOL WINAPI          EnumDisplaySettingsExA( LPCSTR, DWORD, LPDEVMODEA, DWORD );
WINUSERAPI BOOL WINAPI          EnumDisplaySettingsExW( LPCWSTR, DWORD, LPDEVMODEW, DWORD );
#endif
#endif
#if (WINVER >= 0x0500) && (_WIN32_WINNT >= 0x0501)
WINUSERAPI BOOL WINAPI          IsWinEventHookInstalled( DWORD );
#endif
#if (WINVER >= 0x0501)
WINUSERAPI VOID WINAPI          DisableProcessWindowsGhosting( VOID );
#endif
#if (WINVER >= 0x0600)
WINUSERAPI BOOL WINAPI          AddClipboardFormatListener( HWND );
WINUSERAPI BOOL WINAPI          ChangeWindowMessageFilter( UINT, DWORD );
WINUSERAPI BOOL WINAPI          GetUpdatedClipboardFormats( PUINT, UINT, PUINT );
WINUSERAPI BOOL WINAPI          LogicalToPhysicalPoint( HWND, LPPOINT );
WINUSERAPI BOOL WINAPI          PhysicalToLogicalPoint( HWND, LPPOINT );
WINUSERAPI BOOL WINAPI          RemoveClipboardFormatListener( HWND );
WINUSERAPI HWND WINAPI          WindowFromPhysicalPoint( POINT );
#endif
#if (_WIN32_WINNT >= 0x0400)
WINUSERAPI BOOL WINAPI          TrackMouseEvent( LPTRACKMOUSEEVENT );
#endif
#if (_WIN32_WINNT > 0x0400)
WINUSERAPI UINT WINAPI          SendInput( UINT, LPINPUT, int );
#endif
#if (_WIN32_WINNT >= 0x0500)
WINUSERAPI BOOL WINAPI          AllowSetForegroundWindow( DWORD );
WINUSERAPI BOOL WINAPI          GetLastInputInfo( PLASTINPUTINFO );
WINUSERAPI BOOL WINAPI          LockSetForegroundWindow( UINT );
WINUSERAPI BOOL WINAPI          LockWorkStation( VOID );
WINUSERAPI BOOL WINAPI          SetLayeredWindowAttributes( HWND, COLORREF, BYTE, DWORD );
WINUSERAPI BOOL WINAPI          UserHandleGrantAccess( HANDLE, HANDLE, BOOL );
#ifdef _WINGDI_
WINUSERAPI BOOL WINAPI          UpdateLayeredWindow( HWND, HDC, POINT *, SIZE *, HDC, POINT *, COLORREF, BLENDFUNCTION *, DWORD );
#endif
#endif
#if (_WIN32_WINNT >= 0x0501)
WINUSERAPI long WINAPI          BroadcastSystemMessageExA( DWORD, LPDWORD, UINT, WPARAM, LPARAM, PBSMINFO );
WINUSERAPI long WINAPI          BroadcastSystemMessageExW( DWORD, LPDWORD, UINT, WPARAM, LPARAM, PBSMINFO );
WINUSERAPI LRESULT WINAPI       DefRawInputProc( PRAWINPUT *, INT, UINT );
WINUSERAPI BOOL WINAPI          GetLayeredWindowAttributes( HWND, COLORREF *, BYTE *, DWORD * );
WINUSERAPI UINT WINAPI          GetRawInputBuffer( PRAWINPUT, PUINT, UINT );
WINUSERAPI UINT WINAPI          GetRawInputData( HRAWINPUT, UINT, LPVOID, PUINT, UINT );
WINUSERAPI UINT WINAPI          GetRawInputDeviceInfoA( HANDLE, UINT, LPVOID, PUINT );
WINUSERAPI UINT WINAPI          GetRawInputDeviceInfoW( HANDLE, UINT, LPVOID, PUINT );
WINUSERAPI UINT WINAPI          GetRawInputDeviceList( PRAWINPUTDEVICELIST, PUINT, UINT );
WINUSERAPI UINT WINAPI          GetRegisteredRawInputDevices( PRAWINPUTDEVICE, PUINT, UINT );
WINUSERAPI int WINAPI           GetWindowRgnBox( HWND, LPRECT );
WINUSERAPI BOOL WINAPI          IsGUIThread( BOOL );
WINUSERAPI BOOL WINAPI          IsWow64Message( VOID );
WINUSERAPI BOOL WINAPI          PrintWindow( HWND, HDC, UINT );
WINUSERAPI BOOL WINAPI          RegisterRawInputDevices( PCRAWINPUTDEVICE, UINT, UINT );
#endif
#if (_WIN32_WINNT >= 0x0502)
WINUSERAPI HPOWERNOTIFY WINAPI  RegisterPowerSettingNotification( HANDLE, LPCGUID, DWORD );
WINUSERAPI BOOL WINAPI          UnregisterPowerSettingNotification( HPOWERNOTIFY );
#ifdef _WINGDI_
WINUSERAPI BOOL WINAPI          UpdateLayeredWindowIndirect( HWND, CONST UPDATELAYEREDWINDOWINFO * );
#endif
#endif
#if (_WIN32_WINNT >= 0x0600)
WINUSERAPI BOOL WINAPI          GetIconInfoExA( HICON, PICONINFOEXA );
WINUSERAPI BOOL WINAPI          GetIconInfoExW( HICON, PICONINFOEXW );
WINUSERAPI BOOL WINAPI          IsProcessDPIAware( VOID );
WINUSERAPI BOOL WINAPI          SetProcessDPIAware( VOID );
WINUSERAPI BOOL WINAPI          SoundSentry( VOID );
#endif

/* Functions in USER32.DLL that are defined differently on different versions
 * of Windows.
 */
#if (WINVER >= 0x0400)
WINUSERAPI HKL WINAPI   ActivateKeyboardLayout( HKL, UINT );
#if defined(_WIN32_WINNT)
WINUSERAPI long WINAPI  BroadcastSystemMessageA( DWORD, LPDWORD, UINT, WPARAM, LPARAM );
WINUSERAPI long WINAPI  BroadcastSystemMessageW( DWORD, LPDWORD, UINT, WPARAM, LPARAM );
#elif defined (_WIN32_WINDOWS)
WINUSERAPI long WINAPI  BroadcastSystemMessage( DWORD, LPDWORD, UINT, WPARAM, LPARAM );
#endif
#else
WINUSERAPI BOOL WINAPI  ActivateKeyboardLayout( HKL, UINT );
#endif

/* Functions implemented as macros */
#define CopyCursor( x )                     ((HCURSOR)CopyIcon( (HICON)(x) ))
#define CreateDialogA( p1, p2, p3, p4 ) \
    CreateDialogParamA( p1, p2, p3, p4, 0L )
#define CreateDialogIndirectA( p1, p2, p3, p4 ) \
    CreateDialogIndirectParamA( p1, p2, p3, p4, 0L )
#define CreateDialogIndirectW( p1, p2, p3, p4 ) \
    CreateDialogIndirectParamW( p1, p2, p3, p4, 0L )
#define CreateDialogW( p1, p2, p3, p4 ) \
    CreateDialogParamW( p1, p2, p3, p4, 0L )
#define CreateWindowA( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) \
    CreateWindowExA( 0L, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define CreateWindowW( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) \
    CreateWindowExW( 0L, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define DefHookProc( p1, p2, p3, p4 )       CallNextHookEx( *p4, p1, p2, p3 )
#define DialogBoxA( p1, p2, p3, p4 )        DialogBoxParamA( p1, p2, p3, p4, 0L )
#define DialogBoxIndirectA( p1, p2, p3, p4 ) \
    DialogBoxIndirectParamA( p1, p2, p3, p4, 0L )
#define DialogBoxIndirectW( p1, p2, p3, p4 ) \
    DialogBoxIndirectParamW( p1, p2, p3, p4, 0L )
#define DialogBoxW( p1, p2, p3, p4 )        DialogBoxParamW( p1, p2, p3, p4, 0L )
#define EnumTaskWindows( p1, p2, p3 ) \
    EnumThreadWindows( HandleToUlong( p1 ), p2, p3 )
#define ExitWindows( p1, p2 )               ExitWindowsEx( EWX_LOGOFF, 0xFFFFFFFFL )
#define GetClassLongPtrA( p1, p2 )          GetClassLongA( p1, p2 )
#define GetClassLongPtrW( p1, p2 )          GetClassLongW( p1, p2 )
#define GetNextWindow( p1, p2 )             GetWindow( p1, p2 )
#define GetSysModalWindow()                 NULL
#define GetWindowLongPtrA( p1, p2 )         GetWindowLongA( p1, p2 )
#define GetWindowLongPtrW( p1, p2 )         GetWindowLongW( p1, p2 )
#define GetWindowTask( x ) \
    ((HANDLE)(DWORD_PTR)GetWindowThreadProcessId( x, NULL ))
#define PostAppMessageA( p1, p2, p3, p4 )   PostThreadMessageA( (DWORD)(p1), p2, p3, p4 )
#define PostAppMessageW( p1, p2, p3, p4 )   PostThreadMessageW( (DWORD)(p1), p2, p3, p4 )
#define SetClassLongPtrA( p1, p2, p3 )      SetClassLongA( p1, p2, p3 )
#define SetClassLongPtrW( p1, p2, p3 )      SetClassLongW( p1, p2, p3 )
#define SetSysModalWindow( x )              NULL
#define SetWindowLongPtrA( p1, p2, p3 )     SetWindowLongA( p1, p2, p3 )
#define SetWindowLongPtrW( p1, p2, p3 )     SetWindowLongW( p1, p2, p3 )

/* Aliases for compatibility with Win16 */
#define AnsiLower       CharLowerA
#define AnsiLowerBuff   CharLowerBuffA
#define AnsiNext        CharNextA
#define AnsiPrev        CharPrevA
#define AnsiToOem       CharToOemA
#define AnsiToOemBuff   CharToOemBuffA
#define AnsiUpper       CharUpperA
#define AnsiUpperBuff   CharUpperBuffA
#define OemToAnsi       OemToCharA
#define OemToAnsiBuff   OemToCharBuffA

/* Map generic function names to the appropriate ANSI or Unicode version. */
#ifdef UNICODE
    #define AppendMenu                      AppendMenuW
    #define CallMsgFilter                   CallMsgFilterW
    #define CallWindowProc                  CallWindowProcW
    #define ChangeMenu                      ChangeMenuW
    #define CharLower                       CharLowerW
    #define CharLowerBuff                   CharLowerBuffW
    #define CharNext                        CharNextW
    #define CharPrev                        CharPrevW
    #define CharToOem                       CharToOemW
    #define CharToOemBuff                   CharToOemBuffW
    #define CharUpper                       CharUpperW
    #define CharUpperBuff                   CharUpperBuffW
    #define CopyAcceleratorTable            CopyAcceleratorTableW
    #define CreateAcceleratorTable          CreateAcceleratorTableW
    #define CreateDialog                    CreateDialogW
    #define CreateDialogIndirect            CreateDialogIndirectW
    #define CreateDialogIndirectParam       CreateDialogIndirectParamW
    #define CreateDialogParam               CreateDialogParamW
    #define CreateMDIWindow                 CreateMDIWindowW
    #define CreateWindow                    CreateWindowW
    #define CreateWindowEx                  CreateWindowExW
    #define CreateWindowStation             CreateWindowStationW
    #define DefDlgProc                      DefDlgProcW
    #define DefFrameProc                    DefFrameProcW
    #define DefMDIChildProc                 DefMDIChildProcW
    #define DefWindowProc                   DefWindowProcW
    #define DialogBox                       DialogBoxW
    #define DialogBoxIndirect               DialogBoxIndirectW
    #define DialogBoxIndirectParam          DialogBoxIndirectParamW
    #define DialogBoxParam                  DialogBoxParamW
    #define DispatchMessage                 DispatchMessageW
    #define DlgDirList                      DlgDirListW
    #define DlgDirListComboBox              DlgDirListComboBoxW
    #define DlgDirSelectComboBoxEx          DlgDirSelectComboBoxExW
    #define DlgDirSelectEx                  DlgDirSelectExW
    #define DrawText                        DrawTextW
    #define EnumDesktops                    EnumDesktopsW
    #define EnumProps                       EnumPropsW
    #define EnumPropsEx                     EnumPropsExW
    #define EnumWindowStations              EnumWindowStationsW
    #define FindWindow                      FindWindowW
    #define GetClassInfo                    GetClassInfoW
    #define GetClassLong                    GetClassLongW
    #define GetClassLongPtr                 GetClassLongPtrW
    #define GetClassName                    GetClassNameW
    #define GetClipboardFormatName          GetClipboardFormatNameW
    #define GetDlgItemText                  GetDlgItemTextW
    #define GetKeyNameText                  GetKeyNameTextW
    #define GetKeyboardLayoutName           GetKeyboardLayoutNameW
    #define GetMenuString                   GetMenuStringW
    #define GetMessage                      GetMessageW
    #define GetProp                         GetPropW
    #define GetTabbedTextExtent             GetTabbedTextExtentW
    #define GetUserObjectInformation        GetUserObjectInformationW
    #define GetWindowLong                   GetWindowLongW
    #define GetWindowLongPtr                GetWindowLongPtrW
    #define GetWindowText                   GetWindowTextW
    #define GetWindowTextLength             GetWindowTextLengthW
    #define GrayString                      GrayStringW
    #define InsertMenu                      InsertMenuW
    #define IsCharAlpha                     IsCharAlphaW
    #define IsCharAlphaNumeric              IsCharAlphaNumericW
    #define IsCharLower                     IsCharLowerW
    #define IsCharUpper                     IsCharUpperW
    #define IsDialogMessage                 IsDialogMessageW
    #define LoadAccelerators                LoadAcceleratorsW
    #define LoadBitmap                      LoadBitmapW
    #define LoadCursor                      LoadCursorW
    #define LoadCursorFromFile              LoadCursorFromFileW
    #define LoadIcon                        LoadIconW
    #define LoadKeyboardLayout              LoadKeyboardLayoutW
    #define LoadMenu                        LoadMenuW
    #define LoadMenuIndirect                LoadMenuIndirectW
    #define LoadString                      LoadStringW
    #define MapVirtualKey                   MapVirtualKeyW
    #define MessageBox                      MessageBoxW
    #define MessageBoxEx                    MessageBoxExW
    #define ModifyMenu                      ModifyMenuW
    #define OemToChar                       OemToCharW
    #define OemToCharBuff                   OemToCharBuffW
    #define OpenDesktop                     OpenDesktopW
    #define OpenWindowStation               OpenWindowStationW
    #define PeekMessage                     PeekMessageW
    #define PostAppMessage                  PostAppMessageW
    #define PostMessage                     PostMessageW
    #define PostThreadMessage               PostThreadMessageW
    #define PrivateExtractIcons             PrivateExtractIconsW
    #define RegisterClass                   RegisterClassW
    #define RegisterClipboardFormat         RegisterClipboardFormatW
    #define RegisterWindowMessage           RegisterWindowMessageW
    #define RemoveProp                      RemovePropW
    #define SendDlgItemMessage              SendDlgItemMessageW
    #define SendMessage                     SendMessageW
    #define SendMessageCallback             SendMessageCallbackW
    #define SendMessageTimeout              SendMessageTimeoutW
    #define SendNotifyMessage               SendNotifyMessageW
    #define SetClassLong                    SetClassLongW
    #define SetClassLongPtr                 SetClassLongPtrW
    #define SetDlgItemText                  SetDlgItemTextW
    #define SetProp                         SetPropW
    #define SetUserObjectInformation        SetUserObjectInformationW
    #define SetWindowLong                   SetWindowLongW
    #define SetWindowLongPtr                SetWindowLongPtrW
    #define SetWindowText                   SetWindowTextW
    #define SetWindowsHook                  SetWindowsHookW
    #define SetWindowsHookEx                SetWindowsHookExW
    #define SystemParametersInfo            SystemParametersInfoW
    #define TabbedTextOut                   TabbedTextOutW
    #define TranslateAccelerator            TranslateAcceleratorW
    #define UnregisterClass                 UnregisterClassW
    #define VkKeyScan                       VkKeyScanW
    #define WinHelp                         WinHelpW
    #define wsprintf                        wsprintfW
    #define wvsprintf                       wvsprintfW
    #ifdef _WINGDI_
        #define ChangeDisplaySettings       ChangeDisplaySettingsW
        #define ChangeDisplaySettingsEx     ChangeDisplaySettingsExW
        #define CreateDesktop               CreateDesktopW
        #define CreateDesktopEx             CreateDesktopExW
        #define EnumDisplaySettings         EnumDisplaySettingsW
    #endif
    #if (WINVER >= 0x0400)
        #define DrawState                   DrawStateW
        #define DrawTextEx                  DrawTextExW
        #define FindWindowEx                FindWindowExW
        #define GetClassInfoEx              GetClassInfoExW
        #define GetMenuItemInfo             GetMenuItemInfoW
        #define InsertMenuItem              InsertMenuItemW
        #define LoadImage                   LoadImageW
        #define MapVirtualKeyEx             MapVirtualKeyExW
        #define MessageBoxIndirect          MessageBoxIndirectW
        #define RegisterClassEx             RegisterClassExW
        #define SetMenuItemInfo             SetMenuItemInfoW
        #define VkKeyScanEx                 VkKeyScanExW
    #endif
    #if (WINVER >= 0x0400) && defined(_WIN32_WINNT)
        #define BroadcastSystemMessage      BroadcastSystemMessageW
    #endif
    #if (WINVER >= 0x0500)
        #define GetAltTabInfo               GetAltTabInfoW
        #define GetMonitorInfo              GetMonitorInfoW
        #define GetWindowModuleFileName     GetWindowModuleFileNameW
        #define RealGetWindowClass          RealGetWindowClassW
        #define RegisterDeviceNotification  RegisterDeviceNotificationW
        #ifdef _WINGDI_
            #define EnumDisplayDevices      EnumDisplayDevicesW
            #define EnumDisplaySettingsEx   EnumDisplaySettingsExW
        #endif
    #endif
    #if (_WIN32_WINNT >= 0x0501)
        #define BroadcastSystemMessageEx    BroadcastSystemMessageExW
        #define GetRawInputDeviceInfo       GetRawInputDeviceInfoW
    #endif
    #if (_WIN32_WINNT >= 0x0600)
        #define GetIconInfoEx               GetIconInfoExW
    #endif
#else
    #define AppendMenu                      AppendMenuA
    #define CallMsgFilter                   CallMsgFilterA
    #define CallWindowProc                  CallWindowProcA
    #define ChangeMenu                      ChangeMenuA
    #define CharLower                       CharLowerA
    #define CharLowerBuff                   CharLowerBuffA
    #define CharNext                        CharNextA
    #define CharPrev                        CharPrevA
    #define CharToOem                       CharToOemA
    #define CharToOemBuff                   CharToOemBuffA
    #define CharUpper                       CharUpperA
    #define CharUpperBuff                   CharUpperBuffA
    #define CopyAcceleratorTable            CopyAcceleratorTableA
    #define CreateAcceleratorTable          CreateAcceleratorTableA
    #define CreateDialog                    CreateDialogA
    #define CreateDialogIndirect            CreateDialogIndirectA
    #define CreateDialogIndirectParam       CreateDialogIndirectParamA
    #define CreateDialogParam               CreateDialogParamA
    #define CreateMDIWindow                 CreateMDIWindowA
    #define CreateWindow                    CreateWindowA
    #define CreateWindowEx                  CreateWindowExA
    #define CreateWindowStation             CreateWindowStationA
    #define DefDlgProc                      DefDlgProcA
    #define DefFrameProc                    DefFrameProcA
    #define DefMDIChildProc                 DefMDIChildProcA
    #define DefWindowProc                   DefWindowProcA
    #define DialogBox                       DialogBoxA
    #define DialogBoxIndirect               DialogBoxIndirectA
    #define DialogBoxIndirectParam          DialogBoxIndirectParamA
    #define DialogBoxParam                  DialogBoxParamA
    #define DlgDirList                      DlgDirListA
    #define DlgDirListComboBox              DlgDirListComboBoxA
    #define DlgDirSelectComboBoxEx          DlgDirSelectComboBoxExA
    #define DlgDirSelectEx                  DlgDirSelectExA
    #define DispatchMessage                 DispatchMessageA
    #define DrawText                        DrawTextA
    #define EnumDesktops                    EnumDesktopsA
    #define EnumProps                       EnumPropsA
    #define EnumPropsEx                     EnumPropsExA
    #define EnumWindowStations              EnumWindowStationsA
    #define FindWindow                      FindWindowA
    #define GetClassInfo                    GetClassInfoA
    #define GetClassLong                    GetClassLongA
    #define GetClassLongPtr                 GetClassLongPtrA
    #define GetClassName                    GetClassNameA
    #define GetClipboardFormatName          GetClipboardFormatNameA
    #define GetDlgItemText                  GetDlgItemTextA
    #define GetKeyNameText                  GetKeyNameTextA
    #define GetKeyboardLayoutName           GetKeyboardLayoutNameA
    #define GetMenuString                   GetMenuStringA
    #define GetMessage                      GetMessageA
    #define GetProp                         GetPropA
    #define GetTabbedTextExtent             GetTabbedTextExtentA
    #define GetUserObjectInformation        GetUserObjectInformationA
    #define GetWindowLong                   GetWindowLongA
    #define GetWindowLongPtr                GetWindowLongPtrA
    #define GetWindowText                   GetWindowTextA
    #define GetWindowTextLength             GetWindowTextLengthA
    #define GrayString                      GrayStringA
    #define InsertMenu                      InsertMenuA
    #define IsCharAlpha                     IsCharAlphaA
    #define IsCharAlphaNumeric              IsCharAlphaNumericA
    #define IsCharLower                     IsCharLowerA
    #define IsCharUpper                     IsCharUpperA
    #define IsDialogMessage                 IsDialogMessageA
    #define LoadAccelerators                LoadAcceleratorsA
    #define LoadBitmap                      LoadBitmapA
    #define LoadCursor                      LoadCursorA
    #define LoadCursorFromFile              LoadCursorFromFileA
    #define LoadIcon                        LoadIconA
    #define LoadImage                       LoadImageA
    #define LoadKeyboardLayout              LoadKeyboardLayoutA
    #define LoadMenu                        LoadMenuA
    #define LoadMenuIndirect                LoadMenuIndirectA
    #define LoadString                      LoadStringA
    #define MapVirtualKey                   MapVirtualKeyA
    #define MessageBox                      MessageBoxA
    #define MessageBoxEx                    MessageBoxExA
    #define ModifyMenu                      ModifyMenuA
    #define OemToChar                       OemToCharA
    #define OemToCharBuff                   OemToCharBuffA
    #define OpenDesktop                     OpenDesktopA
    #define OpenWindowStation               OpenWindowStationA
    #define PeekMessage                     PeekMessageA
    #define PostAppMessage                  PostAppMessageA
    #define PostMessage                     PostMessageA
    #define PostThreadMessage               PostThreadMessageA
    #define PrivateExtractIcons             PrivateExtractIconsA
    #define RegisterClass                   RegisterClassA
    #define RegisterClipboardFormat         RegisterClipboardFormatA
    #define RegisterWindowMessage           RegisterWindowMessageA
    #define RemoveProp                      RemovePropA
    #define SendDlgItemMessage              SendDlgItemMessageA
    #define SendMessage                     SendMessageA
    #define SendMessageCallback             SendMessageCallbackA
    #define SendMessageTimeout              SendMessageTimeoutA
    #define SendNotifyMessage               SendNotifyMessageA
    #define SetClassLong                    SetClassLongA
    #define SetClassLongPtr                 SetClassLongPtrA
    #define SetDlgItemText                  SetDlgItemTextA
    #define SetProp                         SetPropA
    #define SetUserObjectInformation        SetUserObjectInformationA
    #define SetWindowLong                   SetWindowLongA
    #define SetWindowLongPtr                SetWindowLongPtrA
    #define SetWindowText                   SetWindowTextA
    #define SetWindowsHook                  SetWindowsHookA
    #define SetWindowsHookEx                SetWindowsHookExA
    #define SystemParametersInfo            SystemParametersInfoA
    #define TabbedTextOut                   TabbedTextOutA
    #define TranslateAccelerator            TranslateAcceleratorA
    #define UnregisterClass                 UnregisterClassA
    #define VkKeyScan                       VkKeyScanA
    #define WinHelp                         WinHelpA
    #define wsprintf                        wsprintfA
    #define wvsprintf                       wvsprintfA
    #ifdef _WINGDI_
        #define ChangeDisplaySettings       ChangeDisplaySettingsA
        #define ChangeDisplaySettingsEx     ChangeDisplaySettingsExA
        #define CreateDesktop               CreateDesktopA
        #define CreateDesktopEx             CreateDesktopExA
        #define EnumDisplaySettings         EnumDisplaySettingsA
    #endif
    #if (WINVER >= 0x0400)
        #define DrawState                   DrawStateA
        #define DrawTextEx                  DrawTextExA
        #define FindWindowEx                FindWindowExA
        #define GetClassInfoEx              GetClassInfoExA
        #define GetMenuItemInfo             GetMenuItemInfoA
        #define InsertMenuItem              InsertMenuItemA
        #define RegisterClassEx             RegisterClassExA
        #define MapVirtualKeyEx             MapVirtualKeyExA
        #define MessageBoxIndirect          MessageBoxIndirectA
        #define SetMenuItemInfo             SetMenuItemInfoA
        #define VkKeyScanEx                 VkKeyScanExA
    #endif
    #if (WINVER >= 0x0400) && defined(_WIN32_WINNT)
        #define BroadcastSystemMessage      BroadcastSystemMessageA
    #endif
    #if (WINVER >= 0x0500)
        #define GetAltTabInfo               GetAltTabInfoA
        #define GetMonitorInfo              GetMonitorInfoA
        #define GetWindowModuleFileName     GetWindowModuleFileNameA
        #define RealGetWindowClass          RealGetWindowClassA
        #define RegisterDeviceNotification  RegisterDeviceNotificationA
        #ifdef _WINGDI_
            #define EnumDisplayDevices      EnumDisplayDevicesA
            #define EnumDisplaySettingsEx   EnumDisplaySettingsExA
        #endif
    #endif
    #if (_WIN32_WINNT >= 0x0501)
        #define BroadcastSystemMessageEx    BroadcastSystemMessageExA
        #define GetRawInputDeviceInfo       GetRawInputDeviceInfoA
    #endif
    #if (_WIN32_WINNT >= 0x0600)
        #define GetIconInfoEx               GetIconInfoExA
    #endif
#endif

#ifdef __cplusplus
} /* End of extern "C" */
#endif

#endif /* _WINUSER_ */
