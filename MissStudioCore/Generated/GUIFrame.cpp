///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 10 2012)
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
	wxMenuItem* m_mitemWidgetsSetting;
	m_mitemWidgetsSetting = new wxMenuItem( m_mnuMain, wxID_ANY, wxString( wxT("小工具管理") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuMain->Append( m_mitemWidgetsSetting );
	
	wxMenuItem* m_mitemHotKeySetting;
	m_mitemHotKeySetting = new wxMenuItem( m_mnuMain, wxID_ANY, wxString( wxT("热键设置") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuMain->Append( m_mitemHotKeySetting );
	
	m_mnuMain->AppendSeparator();
	
	m_mnuPluginAbout = new wxMenu();
	m_mnuMain->Append( -1, wxT("插件关于"), m_mnuPluginAbout );
	
	wxMenuItem* m_mitemAbout;
	m_mitemAbout = new wxMenuItem( m_mnuMain, wxID_ANY, wxString( wxT("关于(&A)...") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuMain->Append( m_mitemAbout );
	
	m_mnuMain->AppendSeparator();
	
	wxMenuItem* m_mitemExit;
	m_mitemExit = new wxMenuItem( m_mnuMain, wxID_ANY, wxString( wxT("退出(&x)") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuMain->Append( m_mitemExit );
	
	this->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIFrame::GUIFrameOnContextMenu ), NULL, this ); 
	
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( m_mitemWidgetsSetting->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuWidgetsSettingSelection ) );
	this->Connect( m_mitemHotKeySetting->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuHotKeySettingSelection ) );
	this->Connect( m_mitemAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuAboutSelection ) );
	this->Connect( m_mitemExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuExitSelection ) );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuWidgetsSettingSelection ) );
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
	
	m_listHotKey = new wxTreeListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_COLUMN_LINES|wxTR_DEFAULT_STYLE|wxTR_FULL_ROW_HIGHLIGHT|wxTR_HIDE_ROOT|wxTR_ROW_LINES|wxTR_TWIST_BUTTONS );
	
	m_listHotKey->AddColumn( wxT("插件名称"), 170, wxALIGN_LEFT, -1, true, false); 
	m_listHotKey->AddColumn( wxT("快捷键"), 100, wxALIGN_LEFT, -1, true, false); 
	m_listHotKey->AddColumn( wxT("功能描述"), 185, wxALIGN_LEFT, -1, true, false); 
	
	sbSizer1->Add( m_listHotKey, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer2->Add( sbSizer1, 1, wxEXPAND|wxALL, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_listHotKey->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( MissHotKeyFrameBase::OnHotKeyTreeItemActivated ), NULL, this );
}

MissHotKeyFrameBase::~MissHotKeyFrameBase()
{
	// Disconnect Events
	m_listHotKey->Disconnect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( MissHotKeyFrameBase::OnHotKeyTreeItemActivated ), NULL, this );
	
}

MissWidgetFrameBase::MissWidgetFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( MissWidgetFrameBase::m_splitter1OnIdle ), NULL, this );
	
	m_panel1 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("小工具列表") ), wxVERTICAL );
	
	m_listWidgets = new wxTreeListCtrl( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_FULL_ROW_HIGHLIGHT|wxTR_HIDE_ROOT|wxTR_TWIST_BUTTONS );
	
	m_listWidgets->AddColumn( wxT("小工具名称"), 184, wxALIGN_LEFT, -1, true, false); 
	
	sbSizer2->Add( m_listWidgets, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panel1->SetSizer( sbSizer2 );
	m_panel1->Layout();
	sbSizer2->Fit( m_panel1 );
	m_panel2 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxT("正在运行的小工具") ), wxVERTICAL );
	
	m_listRunWidgets = new wxTreeListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_COLUMN_LINES|wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT|wxTR_ROW_LINES|wxTR_TWIST_BUTTONS );
	
	m_listRunWidgets->AddColumn( wxT("小工具名称"), 100, wxALIGN_LEFT, -1, true, false); 
	m_listRunWidgets->AddColumn( wxT("坐标"), 50, wxALIGN_LEFT, -1, true, false); 
	m_listRunWidgets->AddColumn( wxT("透明度"), 50, wxALIGN_LEFT, -1, true, false); 
	m_listRunWidgets->AddColumn( wxT("缩放"), 50, wxALIGN_LEFT, -1, true, false); 
	
	sbSizer4->Add( m_listRunWidgets, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panel2->SetSizer( sbSizer4 );
	m_panel2->Layout();
	sbSizer4->Fit( m_panel2 );
	m_mnuRunWidget = new wxMenu();
	wxMenuItem* m_mitemDelete;
	m_mitemDelete = new wxMenuItem( m_mnuRunWidget, wxID_ANY, wxString( wxT("移除小工具") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuRunWidget->Append( m_mitemDelete );
	
	wxMenuItem* m_mitemReset;
	m_mitemReset = new wxMenuItem( m_mnuRunWidget, wxID_ANY, wxString( wxT("重置") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuRunWidget->Append( m_mitemReset );
	
	m_panel2->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( MissWidgetFrameBase::m_panel2OnContextMenu ), NULL, this ); 
	
	m_splitter1->SplitVertically( m_panel1, m_panel2, 180 );
	bSizer4->Add( m_splitter1, 1, wxEXPAND|wxALL, 5 );
	
	
	this->SetSizer( bSizer4 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_listWidgets->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( MissWidgetFrameBase::OnWidgetsListTreeItemActivated ), NULL, this );
}

MissWidgetFrameBase::~MissWidgetFrameBase()
{
	// Disconnect Events
	m_listWidgets->Disconnect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( MissWidgetFrameBase::OnWidgetsListTreeItemActivated ), NULL, this );
	
	delete m_mnuRunWidget; 
}

SetHotKeyBase::SetHotKeyBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnClear = new wxButton( this, wxID_ANY, wxT("清除"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_btnClear, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_kedtHotKey = new wxKeyMonitorTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer3->Add( m_kedtHotKey, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
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

MissStudioAbout::MissStudioAbout( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bitmap1 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_bitmap1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer7->Add( m_staticText1, 0, wxALL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer7->Add( m_staticText2, 0, wxALL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer7->Add( m_staticText3, 0, wxALL, 5 );
	
	
	bSizer6->Add( bSizer7, 1, wxEXPAND, 5 );
	
	
	bSizer5->Add( bSizer6, 1, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2->Realize();
	
	bSizer5->Add( m_sdbSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxBOTTOM, 5 );
	
	
	this->SetSizer( bSizer5 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

MissStudioAbout::~MissStudioAbout()
{
}
