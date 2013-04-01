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
#include <wx/statbox.h>
#include <wx/splitter.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/slider.h>
#include <wx/frame.h>

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
		wxPanel* panInstalled;
		wxStaticBoxSizer* bSizerInstalled;
		wxPanel* panRuning;
		wxStaticBoxSizer* bSizerRuning;
	
	public:
		
		DesktopToolsBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("桌面工具管理"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 564,412 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~DesktopToolsBase();
		
		void splMainOnIdle( wxIdleEvent& )
		{
			splMain->SetSashPosition( 195 );
			splMain->Disconnect( wxEVT_IDLE, wxIdleEventHandler( DesktopToolsBase::splMainOnIdle ), NULL, this );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class WidgetOptionBase
///////////////////////////////////////////////////////////////////////////////
class WidgetOptionBase : public wxFrame 
{
	private:
	
	protected:
		wxSpinCtrl* spinX;
		wxSpinCtrl* spinY;
		wxCheckBox* cbtnPin;
		wxStaticText* lblZ;
		wxChoice* choZ;
		wxCheckBox* cbtnAllowZoom;
		wxSlider* sldZoom;
		wxCheckBox* cbtnShadow;
		wxSlider* sldOpacity;
		wxButton* btnClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSpinXCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpinYCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnCheckPinBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoZ( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckAllowZoomBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScrollZoomChanged( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnCheckShadowBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScrollOpacityChanged( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnBtnCloseClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		WidgetOptionBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("设置"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~WidgetOptionBase();
	
};

#endif //__GUIFRAME_H__
