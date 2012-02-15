#ifndef __MissWidget__
#define __MissWidget__

class MissWidgetFuncBase;

class MissWidget : public wxFrame
{
	public:
		/** Constructor */
		MissWidget( MissWidgetFuncBase * pFunc,
             wxWindow* parent, wxWindowID id = wxID_ANY,
             const wxString& title = wxT("MissWidget"),
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxSize( 200,200 ),
             long style = 0|wxTAB_TRAVERSAL );

	private:
	    HWND m_hWnd;
        virtual void OnLeftDown( wxMouseEvent& event );
        virtual void OnRightUp( wxMouseEvent& event );
    private:
        std::tr1::shared_ptr<MissWidgetFuncBase> m_pFunc;

};

#endif // __MissWidget__
