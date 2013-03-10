#ifndef WXKEYMONITORTEXTCTRL_H
#define WXKEYMONITORTEXTCTRL_H

#include <wx/textctrl.h>

class wxKeyMonitorTextCtrl : public wxTextCtrl
{
public:
    wxKeyMonitorTextCtrl(
        wxWindow* parent,
        wxWindowID id,
        const wxString& value = wxEmptyString,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxTE_PROCESS_ENTER,
        const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxTextCtrlNameStr) :
        wxTextCtrl(parent, id, value, pos, size, style, validator, name) {}

    virtual ~wxKeyMonitorTextCtrl() {}

public:

    //! Handles the keypresses and changes accordingly
    //! the text displayed in text ctrl.
    void OnKey(wxKeyEvent &event);

    //! Returns TRUE if this window is containing a valid key combination.
    bool IsValidKeyComb() const
    {
        return !GetValue().IsEmpty() && GetValue().Last() != '+';
    }

private:
    DECLARE_CLASS(wxKeyMonitorTextCtrl)
    DECLARE_EVENT_TABLE()
};

class wxKeyBind
{
public:
    static wxString GetKeyStrokeString(wxKeyEvent &event);
    static int GetKeyModifier(wxKeyEvent &event);
    static wxString KeyCodeToString(int keyCode);
    static wxString KeyModifierToString(int keyModifier);
    static wxString NumpadKeyCodeToString(int keyCode);

    static int StringToKeyCode(const wxString &keyName);
    static int StringToKeyModifier(const wxString &keyModifier);
};


#endif // WXKEYMONITORTEXTCTRL_H
