///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  2 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIDialog.h"

///////////////////////////////////////////////////////////////////////////

GUIDialog::GUIDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("密码:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer3->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_edtPassword = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	bSizer3->Add( m_edtPassword, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("输出长度:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer3->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spLen = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS, 1, 32, 8 );
	bSizer3->Add( m_spLen, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("密码版本:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer3->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spVersion = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS, 1, 255, 1 );
	bSizer3->Add( m_spVersion, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_btnGenerate = new wxButton( this, wxID_ANY, wxT("生成"), wxDefaultPosition, wxDefaultSize, 0 );
	m_btnGenerate->SetDefault(); 
	bSizer4->Add( m_btnGenerate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_edtOut = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_edtOut, 0, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( bSizer4, 1, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	m_btnGenerate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnBtnGenerateClick ), NULL, this );
}

GUIDialog::~GUIDialog()
{
	// Disconnect Events
	m_btnGenerate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnBtnGenerateClick ), NULL, this );
	
}
