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

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_mnuMain = new wxMenu();
	wxMenuItem* m_mitemHotKeySetting;
	m_mitemHotKeySetting = new wxMenuItem( m_mnuMain, wxID_ANY, wxString( wxT("热键设置") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuMain->Append( m_mitemHotKeySetting );
	
	wxMenuItem* m_separator1;
	m_separator1 = m_mnuMain->AppendSeparator();
	
	m_mnuPluginAbout = new wxMenu();
	m_mnuMain->Append( -1, wxT("插件关于"), m_mnuPluginAbout );
	
	wxMenuItem* m_mitemAbout;
	m_mitemAbout = new wxMenuItem( m_mnuMain, wxID_ANY, wxString( wxT("关于(&A)...") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuMain->Append( m_mitemAbout );
	
	wxMenuItem* m_separator2;
	m_separator2 = m_mnuMain->AppendSeparator();
	
	wxMenuItem* m_mitemExit;
	m_mitemExit = new wxMenuItem( m_mnuMain, wxID_ANY, wxString( wxT("退出(&x)") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuMain->Append( m_mitemExit );
	
	this->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIFrame::GUIFrameOnContextMenu ), NULL, this ); 
	
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( m_mitemHotKeySetting->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuHotKeySettingSelection ) );
	this->Connect( m_mitemAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuAboutSelection ) );
	this->Connect( m_mitemExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuExitSelection ) );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuHotKeySettingSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuAboutSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuExitSelection ) );
	
	delete m_mnuMain; 
}

MissHotKeyFrameBase::MissHotKeyFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("快捷键设置") ), wxVERTICAL );
	
	m_listHotKey = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_VRULES );
	sbSizer1->Add( m_listHotKey, 1, wxALL|wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer1, 1, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_listHotKey->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( MissHotKeyFrameBase::OnListItemActivated ), NULL, this );
}

MissHotKeyFrameBase::~MissHotKeyFrameBase()
{
	// Disconnect Events
	m_listHotKey->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( MissHotKeyFrameBase::OnListItemActivated ), NULL, this );
	
}

SetHotKeyBase::SetHotKeyBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnClear = new wxButton( this, wxID_ANY, wxT("清除"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_btnClear, 0, wxALL, 5 );
	
	m_kedtHotKey = new wxKeyMonitorTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer3->Add( m_kedtHotKey, 1, wxALL, 5 );
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	bSizer2->Add( m_sdbSizer1, 0, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_btnClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SetHotKeyBase::OnBtnClearClick ), NULL, this );
}

SetHotKeyBase::~SetHotKeyBase()
{
	// Disconnect Events
	m_btnClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SetHotKeyBase::OnBtnClearClick ), NULL, this );
	
}

MissWidgetBase::MissWidgetBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	
	this->Centre( wxBOTH );
}

MissWidgetBase::~MissWidgetBase()
{
}
