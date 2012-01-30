///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  2 2011)
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

///////////////////////////////////////////////////////////////////////////////
/// Class MissWidgetBase
///////////////////////////////////////////////////////////////////////////////
class MissWidgetBase : public wxFrame 
{
	private:
	
	protected:
	
	public:
		
		MissWidgetBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MissWidgetBase();
	
};

#endif //__GUIFRAME_H__
