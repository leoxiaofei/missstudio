///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb  9 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFRAME_H__
#define __GUIFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/button.h>
#include "../Widget/wxKeyMonitorTextCtrl.h"
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenu* m_mnuMain;
		wxMenu* m_mnuPluginAbout;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMenuWidgetsSettingSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuHotKeySettingSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuAboutSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuExitSelection( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Miss Studio Core"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = 0|wxTAB_TRAVERSAL );
		
		~GUIFrame();
		
		void GUIFrameOnContextMenu( wxMouseEvent &event )
		{
			this->PopupMenu( m_mnuMain, event.GetPosition() );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MissHotKeyFrameBase
///////////////////////////////////////////////////////////////////////////////
class MissHotKeyFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxListCtrl* m_listHotKey;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnListItemActivated( wxListEvent& event ) { event.Skip(); }
		
	
	public:
		
		MissHotKeyFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("全局快捷键编辑器"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MissHotKeyFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MissWidgetFrameBase
///////////////////////////////////////////////////////////////////////////////
class MissWidgetFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel1;
		wxListCtrl* m_listWidgets;
		wxPanel* m_panel2;
		wxListCtrl* m_listRunWidgets;
		wxMenu* m_mnuRunWidget;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnWidgetsListItemActivated( wxListEvent& event ) { event.Skip(); }
		virtual void OnRunWidgetsListItemActivated( wxListEvent& event ) { event.Skip(); }
		virtual void OnRunWidgetsListItemRightClick( wxListEvent& event ) { event.Skip(); }
		
	
	public:
		
		MissWidgetFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("小工具管理器"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 515,391 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MissWidgetFrameBase();
		
		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 180 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MissWidgetFrameBase::m_splitter1OnIdle ), NULL, this );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SetHotKeyBase
///////////////////////////////////////////////////////////////////////////////
class SetHotKeyBase : public wxDialog 
{
	private:
	
	protected:
		wxButton* m_btnClear;
		wxKeyMonitorTextCtrl* m_kedtHotKey;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnBtnClearClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		SetHotKeyBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("设置热键"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 264,96 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~SetHotKeyBase();
	
};

#endif //__GUIFRAME_H__
