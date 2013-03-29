///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIDIALOG_H__
#define __GUIDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialog
///////////////////////////////////////////////////////////////////////////////
class GUIDialog : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_lblPassword;
		wxTextCtrl* m_edtPassword;
		wxStaticText* m_lblLen;
		wxSpinCtrl* m_spLen;
		wxCheckBox* m_cboxAutoClose;
		wxStaticText* m_lblPassType;
		wxChoice* m_cboxPassType;
		wxStaticText* m_lblVersion;
		wxSpinCtrl* m_spVersion;
		wxButton* m_btnGenerate;
		wxCheckBox* m_cboxShowPass;
		wxTextCtrl* m_edtOut;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCheckAutoCloseBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBtnGenerateClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckShowPassBox( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("迷失密码加密器 "), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 316,122 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_TOOL_WINDOW|wxSYSTEM_MENU );
		
		~GUIDialog();
	
};

#endif //__GUIDIALOG_H__
