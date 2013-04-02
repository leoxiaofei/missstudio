#ifndef MISSAUTOINPUTTHREAD_H
#define MISSAUTOINPUTTHREAD_H

#include <wx/Thread.h>
#include <wx/event.h>

wxDECLARE_EVENT(wxEVT_COMMAND_AUTOINPUT_COMPLETED, wxThreadEvent);

class MissAutoInputThread : public wxThread
{
    public:
        MissAutoInputThread(wxEvtHandler* pHandler, const wxString& strInput);
        virtual ~MissAutoInputThread();

        static void SendUnicode(wchar_t wch);
        static void SendKey(char ch);

    protected:
        virtual ExitCode Entry();

    private:
        wxEvtHandler* m_pHandler;
		wxString      m_strInput;
};

#endif // MISSAUTOINPUTTHREAD_H
