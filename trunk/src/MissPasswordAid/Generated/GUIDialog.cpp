///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
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
	
	m_lblPassword = new wxStaticText( this, wxID_ANY, _("密码:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblPassword->Wrap( -1 );
	bSizer3->Add( m_lblPassword, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_edtPassword = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	m_edtPassword->SetMaxLength( 0 ); 
	bSizer3->Add( m_edtPassword, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_lblLen = new wxStaticText( this, wxID_ANY, _("输出长度:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLen->Wrap( -1 );
	bSizer3->Add( m_lblLen, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spLen = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS, 1, 32, 8 );
	bSizer3->Add( m_spLen, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_cboxAutoClose = new wxCheckBox( this, wxID_ANY, _("自动关闭"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cboxAutoClose->SetValue(true); 
	bSizer3->Add( m_cboxAutoClose, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblPassType = new wxStaticText( this, wxID_ANY, _("密码类型:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblPassType->Wrap( -1 );
	bSizer41->Add( m_lblPassType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_cboxPassTypeChoices[] = { _("默认(22种符号)"), _("纯数字") };
	int m_cboxPassTypeNChoices = sizeof( m_cboxPassTypeChoices ) / sizeof( wxString );
	m_cboxPassType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cboxPassTypeNChoices, m_cboxPassTypeChoices, 0 );
	m_cboxPassType->SetSelection( 0 );
	bSizer41->Add( m_cboxPassType, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_lblVersion = new wxStaticText( this, wxID_ANY, _("密码版本:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblVersion->Wrap( -1 );
	bSizer41->Add( m_lblVersion, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spVersion = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS, 1, 255, 1 );
	bSizer41->Add( m_spVersion, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( bSizer41, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnGenerate = new wxButton( this, wxID_ANY, _("生成"), wxDefaultPosition, wxDefaultSize, 0 );
	m_btnGenerate->SetDefault(); 
	bSizer4->Add( m_btnGenerate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_cboxShowPass = new wxCheckBox( this, wxID_ANY, _("显示密码"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_cboxShowPass, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_edtOut = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_edtOut->SetMaxLength( 0 ); 
	m_edtOut->Hide();
	
	bSizer4->Add( m_edtOut, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( bSizer4, 1, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	//this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIDialog::GUIDialogOnClose ) );
	m_cboxAutoClose->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIDialog::OnCheckAutoCloseBox ), NULL, this );
	m_btnGenerate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnBtnGenerateClick ), NULL, this );
	m_cboxShowPass->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIDialog::OnCheckShowPassBox ), NULL, this );
}

GUIDialog::~GUIDialog()
{
	// Disconnect Events
	//this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIDialog::GUIDialogOnClose ) );
	m_cboxAutoClose->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIDialog::OnCheckAutoCloseBox ), NULL, this );
	m_btnGenerate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnBtnGenerateClick ), NULL, this );
	m_cboxShowPass->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIDialog::OnCheckShowPassBox ), NULL, this );
	
}
