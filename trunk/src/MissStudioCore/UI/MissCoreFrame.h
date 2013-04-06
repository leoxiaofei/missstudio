#ifndef __MissCoreFrame__
#define __MissCoreFrame__

#include <wx/frame.h>
#include <memory>

class wxTimerEvent;

class MissCoreFrame : public wxFrame
{
	class Impl;
public:
	/** Constructor */
	MissCoreFrame();
    ~MissCoreFrame();

    void OnHotKey(wxKeyEvent& event);

protected:
    void OnClose(wxCloseEvent& event);
    void OnTimer(wxTimerEvent& event);

    ///自定义事件
    void OnInitWindow(wxEvent& event);

    
    void BindEvent();
    void UnbindEvent();

    void InitPlugin();
    //DECLARE_EVENT_TABLE()
private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

extern wxFrame* wxAppFrame;

wxDECLARE_EVENT(wxEVT_INITIALIZE, wxEvent);


#endif // __MissCoreFrame__
