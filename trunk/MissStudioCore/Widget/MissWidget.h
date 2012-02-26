#ifndef __MissWidget__
#define __MissWidget__

#include "../../MissAPI/plugin/MissTimerFuncBase.h"

class MissWidgetFuncBase;

typedef std::vector<std::pair<wxString, wxString> > WidgetParas;
struct SWidgetData
{
    double      m_dZome;
    int         m_nOpacity;
    wxPoint     m_ptPos;
    WidgetParas m_vecPata;
};

class MissWidget : public wxFrame, public MissTimerFuncBase
{
	public:
		/** Constructor */
		MissWidget( MissWidgetFuncBase * pFunc,
             wxWindow* parent, wxWindowID id = wxID_ANY,
             const wxString& title = wxT("MissWidget"),
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxSize( 200,200 ),
             long style = 0|wxTAB_TRAVERSAL );

        void InitData(const SWidgetData& data);

        void SetScale(const double& dZoom);
        void SetOpacity(int nOpacity);

        const double& GetScale() const;
        int           GetOpacity() const;

	private:
        virtual void OnLeftDown( wxMouseEvent& event );
        virtual void OnRightUp( wxMouseEvent& event );

        ///实现接口
        virtual void TimeUp(const tm* tmNow, MissTimerType eType = MTT_SEC);

    private:
        std::tr1::shared_ptr<MissWidgetFuncBase> m_pFunc;
        BLENDFUNCTION      m_Blend;
        double             m_dZoom;
        SIZE               m_SizeWindow;
        HWND               m_hWnd;

        wxBitmap           m_bpUI;
        unsigned int      *m_pBitmap;
        int                m_nPixCount;
};

#endif // __MissWidget__
