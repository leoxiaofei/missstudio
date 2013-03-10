#include "wxKeyMonitorTextCtrl.h"

//#include <iostream>

// event table for wxKeyMonitorTextCtrl
IMPLEMENT_CLASS(wxKeyMonitorTextCtrl, wxTextCtrl)
BEGIN_EVENT_TABLE(wxKeyMonitorTextCtrl, wxTextCtrl)

    // keydown events
    EVT_KEY_DOWN(wxKeyMonitorTextCtrl::OnKey)
    EVT_KEY_UP(wxKeyMonitorTextCtrl::OnKey)

END_EVENT_TABLE()

#ifdef _WINDOWS

#include "../Common/Targetver.h"
#include <windows.h>

#endif

// ----------------------------------------------------------------------------
// wxKeyMonitorTextCtrl
// ----------------------------------------------------------------------------

void wxKeyMonitorTextCtrl::OnKey(wxKeyEvent &event)
{
    // backspace cannot be used as shortcut key...
    if (event.GetKeyCode() == WXK_BACK)
    {

        // this text ctrl contains something and the user pressed backspace...
        // we must delete the keypress...
        Clear();
        return;
    }

    if (event.GetEventType() == wxEVT_KEY_DOWN ||
            (event.GetEventType() == wxEVT_KEY_UP && !IsValidKeyComb()))
    {

        // the user pressed some key combination which must be displayed
        // in this text control.... or he has just stopped pressing a
        // modifier key like shift, ctrl or alt without adding any
        // other alphanumeric char, thus generating an invalid keystroke
        // which must be cleared out...
        SetValue(wxKeyBind::GetKeyStrokeString(event));
        SetInsertionPointEnd();
    }
}

wxString wxKeyBind::GetKeyStrokeString(wxKeyEvent& event)
{
    // key stroke string = key modifiers (Ctrl, Alt or Shift) + key code
    return KeyModifierToString(GetKeyModifier(event)) +
           KeyCodeToString(event.GetKeyCode());
}

int wxKeyBind::GetKeyModifier(wxKeyEvent& event)
{
    int mod = 0;
    if (event.AltDown())
        mod |= wxACCEL_ALT;

    if (event.ControlDown())
        mod |= wxACCEL_CTRL;

    if (event.ShiftDown())
        mod |= wxACCEL_SHIFT;

    #ifdef _WINDOWS
    if(GetAsyncKeyState(VK_LWIN)||GetAsyncKeyState(VK_RWIN))
        mod |= wxMOD_WIN;
    #endif

//     std::cout<<event.GetKeyCode()<<std::endl;
//     std::cout<<event.GetRawKeyCode()<<std::endl;
//     std::cout<<event.GetRawKeyFlags()<<std::endl;
//     std::cout<<event.GetModifiers()<<std::endl;
    return mod;
}

wxString wxKeyBind::KeyCodeToString(int keyCode)
{
    wxString res;

    switch (keyCode)
    {
        // IGNORED KEYS
        // ---------------------------
    case WXK_START:
    case WXK_LBUTTON:
    case WXK_RBUTTON:
    case WXK_MBUTTON:
    case WXK_CLEAR:

    case WXK_PAUSE:
    case WXK_NUMLOCK:
    case WXK_SCROLL :
        //wxKBLogDebug(wxT("wxKeyBind::KeyCodeToString - ignored key: [%d]"), keyCode);
        return wxEmptyString;

        // these must be ABSOLUTELY ignored: they are key modifiers
        // we won't output any LOG message since these keys could be pressed
        // for long time while the user choose its preferred keycombination:
        // this would result into a long long queue of "ignored key" messages
        // which would be useless even in debug builds...
    case WXK_SHIFT:
    case WXK_ALT:
    case WXK_CONTROL:
    case WXK_WINDOWS_LEFT:
    case WXK_WINDOWS_RIGHT:
        return wxEmptyString;




        // FUNCTION KEYS
        // ---------------------------

    case WXK_F1:
    case WXK_F2:
    case WXK_F3:
    case WXK_F4:
    case WXK_F5:
    case WXK_F6:
    case WXK_F7:
    case WXK_F8:
    case WXK_F9:
    case WXK_F10:
    case WXK_F11:
    case WXK_F12:
    case WXK_F13:
    case WXK_F14:
    case WXK_F15:
    case WXK_F16:
    case WXK_F17:
    case WXK_F18:
    case WXK_F19:
    case WXK_F20:
    case WXK_F21:
    case WXK_F22:
    case WXK_F23:
    case WXK_F24:
        res << wxT('F') << keyCode - WXK_F1 + 1;
        break;



        // MISCELLANEOUS KEYS
        // ---------------------------

    case WXK_BACK:
        res << wxT("BACK");
        break;
    case WXK_TAB:
        res << wxT("TAB");
        break;
    case WXK_RETURN:
        res << wxT("RETURN");
        break;
    case WXK_ESCAPE:
        res << wxT("ESCAPE");
        break;
    case WXK_SPACE:
        res << wxT("SPACE");
        break;
    case WXK_DELETE:
        res << wxT("DELETE");
        break;
    case WXK_MULTIPLY:
        res << wxT("*");
        break;
    case WXK_ADD:
        res << wxT("+");
        break;
    case WXK_SEPARATOR:
        res << wxT("SEPARATOR");
        break;
    case WXK_SUBTRACT:
        res << wxT("-");
        break;
    case WXK_DECIMAL:
        res << wxT(".");
        break;
    case WXK_DIVIDE:
        res << wxT("/");
        break;
    case WXK_PAGEUP:
        res << wxT("PAGEUP");
        break;
    case WXK_PAGEDOWN:
        res << wxT("PAGEDOWN");
        break;
    case WXK_LEFT:
        res << wxT("LEFT");
        break;
    case WXK_UP:
        res << wxT("UP");
        break;
    case WXK_RIGHT:
        res << wxT("RIGHT");
        break;
    case WXK_DOWN:
        res << wxT("DOWN");
        break;
    case WXK_SELECT:
        res << wxT("SELECT");
        break;
    case WXK_PRINT:
        res << wxT("PRINT");
        break;
    case WXK_EXECUTE:
        res << wxT("EXECUTE");
        break;
    case WXK_SNAPSHOT:
        res << wxT("SNAPSHOT");
        break;
    case WXK_INSERT:
        res << wxT("INSERT");
        break;
    case WXK_HELP:
        res << wxT("HELP");
        break;
    case WXK_CANCEL:
        res << wxT("CANCEL");
        break;
    case WXK_MENU:
        res << wxT("MENU");
        break;
    case WXK_CAPITAL:
        res << wxT("CAPITAL");
        break;
    case WXK_END:
        res << wxT("END");
        break;
    case WXK_HOME:
        res << wxT("HOME");
        break;



    default:

        // ASCII chars...
        if (wxIsalnum(keyCode))
        {
            res << (wxChar)keyCode;
            break;

        }
        else if ((res=NumpadKeyCodeToString(keyCode)) != wxEmptyString)
        {

            res << wxT(" (numpad)");        // so it is clear it's different from other keys
            break;

        }
        else
        {

            // we couldn't create a description for the given keycode...
            //wxKBLogDebug(wxT("wxKeyBind::KeyCodeToString - unknown key: [%d]"), keyCode);
            return wxEmptyString;
        }
    }

    return res;
}

wxString wxKeyBind::KeyModifierToString(int keyModifier)
{
    wxString result;

    if (keyModifier & wxACCEL_CTRL)
        result += wxT("Ctrl+");
    if (keyModifier & wxACCEL_ALT)
        result += wxT("Alt+");
    if (keyModifier & wxACCEL_SHIFT)
        result += wxT("Shift+");
    if (keyModifier & wxMOD_WIN)
        result += wxT("Win+");
    return result;
}

wxString wxKeyBind::NumpadKeyCodeToString(int keyCode)
{
    wxString res;

    switch (keyCode)
    {
        // NUMPAD KEYS
        // ---------------------------

    case WXK_NUMPAD0:
    case WXK_NUMPAD1:
    case WXK_NUMPAD2:
    case WXK_NUMPAD3:
    case WXK_NUMPAD4:
    case WXK_NUMPAD5:
    case WXK_NUMPAD6:
    case WXK_NUMPAD7:
    case WXK_NUMPAD8:
    case WXK_NUMPAD9:
        res << keyCode - WXK_NUMPAD0;
        break;

    case WXK_NUMPAD_SPACE:
        res << wxT("SPACE");
        break;
    case WXK_NUMPAD_TAB:
        res << wxT("TAB");
        break;
    case WXK_NUMPAD_ENTER:
        res << wxT("ENTER");
        break;

    case WXK_NUMPAD_F1:
    case WXK_NUMPAD_F2:
    case WXK_NUMPAD_F3:
    case WXK_NUMPAD_F4:
        res << wxT("F") << keyCode - WXK_NUMPAD_F1;
        break;

    case WXK_NUMPAD_LEFT:
        res << wxT("LEFT");
        break;
    case WXK_NUMPAD_UP:
        res << wxT("UP");
        break;
    case WXK_NUMPAD_RIGHT:
        res << wxT("RIGHT");
        break;
    case WXK_NUMPAD_DOWN:
        res << wxT("DOWN");
        break;

    case WXK_NUMPAD_HOME:
        res << wxT("HOME");
        break;
    case WXK_NUMPAD_PAGEUP:
        res << wxT("PAGEUP");
        break;
    case WXK_NUMPAD_PAGEDOWN:
        res << wxT("PAGEDOWN");
        break;
    case WXK_NUMPAD_END:
        res << wxT("END");
        break;
    case WXK_NUMPAD_BEGIN:
        res << wxT("BEGIN");
        break;
    case WXK_NUMPAD_INSERT:
        res << wxT("INSERT");
        break;
    case WXK_NUMPAD_DELETE:
        res << wxT("DELETE");
        break;
    case WXK_NUMPAD_EQUAL:
        res << wxT("=");
        break;
    case WXK_NUMPAD_MULTIPLY:
        res << wxT("*");
        break;
    case WXK_NUMPAD_ADD:
        res << wxT("+");
        break;
    case WXK_NUMPAD_SEPARATOR:
        res << wxT("SEPARATOR");
        break;
    case WXK_NUMPAD_SUBTRACT:
        res << wxT("-");
        break;
    case WXK_NUMPAD_DECIMAL:
        res << wxT(".");
        break;
    case WXK_NUMPAD_DIVIDE:
        res << wxT("/");
        break;
    }

    return res;
}

int wxKeyBind::StringToKeyCode(const wxString& keys)
{
    wxString keyName = keys.AfterLast('+').AfterLast('-');
    // a function key ?
    if (keyName.StartsWith(wxT("F")) && keyName.Len() > 1)
    {

        long n;
        keyName.Right(keyName.Len()-1).ToLong(&n);
        return WXK_F1+n-1;
    }

    // a special key ?
    if (keyName == wxT("BACK")) return WXK_BACK;
    if (keyName == wxT("ENTER")) return WXK_RETURN;
    if (keyName == wxT("RETURN")) return WXK_RETURN;
    if (keyName == wxT("TAB")) return WXK_TAB;
    if (keyName == wxT("ESCAPE")) return WXK_ESCAPE;
    if (keyName == wxT("SPACE")) return WXK_SPACE;
    if (keyName == wxT("DELETE")) return WXK_DELETE;

    // it should be an ASCII key...
    return (int)keyName.GetChar(0);
}

int wxKeyBind::StringToKeyModifier(const wxString& keyModifier)
{
    int mod = 0;

    // this search must be case-insensitive
    wxString str = keyModifier;
    str.MakeUpper();

    if (str.Contains(wxT("ALT")))
        mod |= wxACCEL_ALT;

    if (str.Contains(wxT("CTRL")))
        mod |= wxACCEL_CTRL;

    if (str.Contains(wxT("SHIFT")))
        mod |= wxACCEL_SHIFT;

    if (str.Contains(wxT("WIN")))
        mod |= wxMOD_WIN;

    return mod;
}

