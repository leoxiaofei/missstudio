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

	void InitMSW();
	void DestroyMSW();
	virtual WXLRESULT MSWWindowProc( WXUINT message, WXWPARAM wParam, WXLPARAM lParam );

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

extern wxFrame* wxAppFrame;

wxDECLARE_EVENT(wxEVT_INITIALIZE, wxEvent);


#endif // __MissCoreFrame__
