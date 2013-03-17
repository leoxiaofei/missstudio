///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFRAME_H__
#define __GUIFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class wxKeyMonitorTextCtrl;

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/notebook.h>
#include <wx/statbox.h>
#include <wx/splitter.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class PluginOptionBase
///////////////////////////////////////////////////////////////////////////////
class PluginOptionBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* lblFilter;
		wxChoice* choFilter;
		wxListbook* lbOption;
		wxPanel* panProperty;
		wxBoxSizer* sizerProperty;
		wxPanel* panHotKey;
		wxBoxSizer* sizerHotKey;
	
	public:
		
		PluginOptionBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("插件设置"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 598,388 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~PluginOptionBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class HotKeySettingBase
///////////////////////////////////////////////////////////////////////////////
class HotKeySettingBase : public wxDialog 
{
	private:
	
	protected:
		wxButton* btnClear;
		wxKeyMonitorTextCtrl* kedtHotKey;
		wxStdDialogButtonSizer* sdbSizerBottom;
		wxButton* sdbSizerBottomOK;
		wxButton* sdbSizerBottomCancel;
	
	public:
		
		HotKeySettingBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("设置热键"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~HotKeySettingBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DesktopToolsBase
///////////////////////////////////////////////////////////////////////////////
class DesktopToolsBase : public wxDialog 
{
	private:
	
	protected:
		wxSplitterWindow* splMain;
		wxPanel* panTree;
		wxNotebook* noteTree;
		wxPanel* panRuning;
		wxBoxSizer* bSizerRuning;
		wxPanel* panInstalled;
		wxBoxSizer* bSizerInstalled;
		wxPanel* panViewer;
	
	public:
		
		DesktopToolsBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("桌面工具管理"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 564,412 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~DesktopToolsBase();
		
		void splMainOnIdle( wxIdleEvent& )
		{
			splMain->SetSashPosition( 195 );
			splMain->Disconnect( wxEVT_IDLE, wxIdleEventHandler( DesktopToolsBase::splMainOnIdle ), NULL, this );
		}
	
};

#endif //__GUIFRAME_H__
