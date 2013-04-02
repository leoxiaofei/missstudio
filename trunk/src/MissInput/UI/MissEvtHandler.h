#ifndef MISSEVTHANDLER_H__
#define MISSEVTHANDLER_H__

#include <wx/event.h>
#include <memory>

class MissEvtHandler : public wxEvtHandler 
{
    class Impl;
public:
    static MissEvtHandler& Instance()
    {
        static MissEvtHandler theSingleton;
        return theSingleton;
    }

    void OpenAutoInput();

protected:
    void BindEvent();
    void UnbindEvent();

    void InputThreadFinished(wxThreadEvent& event);

private:
    MissEvtHandler();
    ~MissEvtHandler();
    MissEvtHandler(const MissEvtHandler&);
    MissEvtHandler& operator=(const MissEvtHandler&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};



#endif // MISSEVTHANDLER_H__
