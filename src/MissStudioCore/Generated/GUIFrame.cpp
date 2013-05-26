///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../Widget/wxKeyMonitorTextCtrl.h"

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

PluginOptionBase::PluginOptionBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerFilter;
	bSizerFilter = new wxBoxSizer( wxHORIZONTAL );
	
	lblFilter = new wxStaticText( this, wxID_ANY, _("过滤器:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblFilter->Wrap( -1 );
	bSizerFilter->Add( lblFilter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString choFilterChoices;
	choFilter = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choFilterChoices, 0 );
	choFilter->SetSelection( 0 );
	bSizerFilter->Add( choFilter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerMain->Add( bSizerFilter, 0, wxEXPAND, 5 );
	
	lbOption = new wxListbook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_DEFAULT|wxLB_LEFT );
	wxSize lbOptionImageSize = wxSize( 32,32 );
	int lbOptionIndex = 0;
	wxImageList* lbOptionImages = new wxImageList( lbOptionImageSize.GetWidth(), lbOptionImageSize.GetHeight() );
	lbOption->AssignImageList( lbOptionImages );
	wxBitmap lbOptionBitmap;
	wxImage lbOptionImage;
	panProperty = new wxPanel( lbOption, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	sizerProperty = new wxBoxSizer( wxVERTICAL );
	
	
	panProperty->SetSizer( sizerProperty );
	panProperty->Layout();
	sizerProperty->Fit( panProperty );
	lbOption->AddPage( panProperty, _("参数设置"), true );
	panHotKey = new wxPanel( lbOption, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	sizerHotKey = new wxBoxSizer( wxVERTICAL );
	
	
	panHotKey->SetSizer( sizerHotKey );
	panHotKey->Layout();
	sizerHotKey->Fit( panHotKey );
	lbOption->AddPage( panHotKey, _("热键设置"), false );
	
	bSizerMain->Add( lbOption, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
}

PluginOptionBase::~PluginOptionBase()
{
}

HotKeySettingBase::HotKeySettingBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerTop;
	bSizerTop = new wxBoxSizer( wxHORIZONTAL );
	
	btnClear = new wxButton( this, wxID_ANY, _("C"), wxDefaultPosition, wxDefaultSize, 0 );
	btnClear->SetMinSize( wxSize( 25,-1 ) );
	btnClear->SetMaxSize( wxSize( 25,-1 ) );
	
	bSizerTop->Add( btnClear, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	kedtHotKey = new wxKeyMonitorTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	kedtHotKey->SetMaxLength( 0 ); 
	bSizerTop->Add( kedtHotKey, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizerMain->Add( bSizerTop, 1, wxEXPAND, 5 );
	
	sdbSizerBottom = new wxStdDialogButtonSizer();
	sdbSizerBottomOK = new wxButton( this, wxID_OK );
	sdbSizerBottom->AddButton( sdbSizerBottomOK );
	sdbSizerBottomCancel = new wxButton( this, wxID_CANCEL );
	sdbSizerBottom->AddButton( sdbSizerBottomCancel );
	sdbSizerBottom->Realize();
	sdbSizerBottom->SetMinSize( wxSize( 150,-1 ) ); 
	
	bSizerMain->Add( sdbSizerBottom, 0, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	
	this->Centre( wxBOTH );
}

HotKeySettingBase::~HotKeySettingBase()
{
}

DesktopToolsBase::DesktopToolsBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxHORIZONTAL );
	
	splMain = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	splMain->Connect( wxEVT_IDLE, wxIdleEventHandler( DesktopToolsBase::splMainOnIdle ), NULL, this );
	
	panInstalled = new wxPanel( splMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizerInstalled = new wxStaticBoxSizer( new wxStaticBox( panInstalled, wxID_ANY, _("已安装") ), wxVERTICAL );
	
	
	panInstalled->SetSizer( bSizerInstalled );
	panInstalled->Layout();
	bSizerInstalled->Fit( panInstalled );
	panRuning = new wxPanel( splMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizerRuning = new wxStaticBoxSizer( new wxStaticBox( panRuning, wxID_ANY, _("运行中") ), wxVERTICAL );
	
	
	panRuning->SetSizer( bSizerRuning );
	panRuning->Layout();
	bSizerRuning->Fit( panRuning );
	splMain->SplitVertically( panInstalled, panRuning, 195 );
	bSizerMain->Add( splMain, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
}

DesktopToolsBase::~DesktopToolsBase()
{
}

WidgetOptionBase::WidgetOptionBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerPosition;
	sbSizerPosition = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("位置") ), wxVERTICAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* lblX;
	lblX = new wxStaticText( this, wxID_ANY, _("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblX->Wrap( -1 );
	bSizer9->Add( lblX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	spinX = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	spinX->SetMinSize( wxSize( 30,-1 ) );
	
	bSizer9->Add( spinX, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxStaticText* lblY;
	lblY = new wxStaticText( this, wxID_ANY, _("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblY->Wrap( -1 );
	bSizer9->Add( lblY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	spinY = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000, 0 );
	spinY->SetMinSize( wxSize( 30,-1 ) );
	
	bSizer9->Add( spinY, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	cbtnPin = new wxCheckBox( this, wxID_ANY, _("固定位置"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( cbtnPin, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerPosition->Add( bSizer9, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	lblZ = new wxStaticText( this, wxID_ANY, _("Z:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblZ->Wrap( -1 );
	bSizer10->Add( lblZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString choZChoices[] = { _("置顶"), _("正常") };
	int choZNChoices = sizeof( choZChoices ) / sizeof( wxString );
	choZ = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choZNChoices, choZChoices, 0 );
	choZ->SetSelection( 1 );
	bSizer10->Add( choZ, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerPosition->Add( bSizer10, 1, wxEXPAND, 5 );
	
	
	bSizerMain->Add( sbSizerPosition, 1, wxTOP|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerZoom;
	sbSizerZoom = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("缩放") ), wxVERTICAL );
	
	wxBoxSizer* sbSizerZoom1;
	sbSizerZoom1 = new wxBoxSizer( wxVERTICAL );
	
	cbtnAllowZoom = new wxCheckBox( this, wxID_ANY, _("允许缩放"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerZoom1->Add( cbtnAllowZoom, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	
	sbSizerZoom->Add( sbSizerZoom1, 0, wxEXPAND|wxALIGN_RIGHT, 5 );
	
	wxBoxSizer* sbSizerZoom2;
	sbSizerZoom2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* lblZoomOut;
	lblZoomOut = new wxStaticText( this, wxID_ANY, _("×0.5"), wxDefaultPosition, wxDefaultSize, 0 );
	lblZoomOut->Wrap( -1 );
	sbSizerZoom2->Add( lblZoomOut, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sldZoom = new wxSlider( this, wxID_ANY, 100, 50, 200, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizerZoom2->Add( sldZoom, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxStaticText* lblZoomIn;
	lblZoomIn = new wxStaticText( this, wxID_ANY, _("×2"), wxDefaultPosition, wxDefaultSize, 0 );
	lblZoomIn->Wrap( -1 );
	sbSizerZoom2->Add( lblZoomIn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerZoom->Add( sbSizerZoom2, 1, wxEXPAND, 5 );
	
	
	bSizerMain->Add( sbSizerZoom, 1, wxEXPAND|wxTOP, 5 );
	
	wxStaticBoxSizer* sbSizerTransparency;
	sbSizerTransparency = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("透明度") ), wxVERTICAL );
	
	wxBoxSizer* sbSizerTransparency1;
	sbSizerTransparency1 = new wxBoxSizer( wxVERTICAL );
	
	cbtnShadow = new wxCheckBox( this, wxID_ANY, _("有影无形"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerTransparency1->Add( cbtnShadow, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	
	sbSizerTransparency->Add( sbSizerTransparency1, 0, wxEXPAND, 5 );
	
	wxBoxSizer* sbSizerTransparency2;
	sbSizerTransparency2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* lblTransparency;
	lblTransparency = new wxStaticText( this, wxID_ANY, _("80%"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTransparency->Wrap( -1 );
	sbSizerTransparency2->Add( lblTransparency, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sldOpacity = new wxSlider( this, wxID_ANY, 255, 50, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizerTransparency2->Add( sldOpacity, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxStaticText* lblOpacity;
	lblOpacity = new wxStaticText( this, wxID_ANY, _("0%"), wxDefaultPosition, wxDefaultSize, 0 );
	lblOpacity->Wrap( -1 );
	sbSizerTransparency2->Add( lblOpacity, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizerTransparency->Add( sbSizerTransparency2, 1, wxEXPAND, 5 );
	
	
	bSizerMain->Add( sbSizerTransparency, 1, wxEXPAND|wxTOP, 5 );
	
	wxBoxSizer* bSizerClose;
	bSizerClose = new wxBoxSizer( wxVERTICAL );
	
	btnClose = new wxButton( this, wxID_ANY, _("关闭"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerClose->Add( btnClose, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	
	bSizerMain->Add( bSizerClose, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	spinX->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( WidgetOptionBase::OnSpinXCtrl ), NULL, this );
	spinY->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( WidgetOptionBase::OnSpinYCtrl ), NULL, this );
	cbtnPin->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( WidgetOptionBase::OnCheckPinBox ), NULL, this );
	choZ->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( WidgetOptionBase::OnChoZ ), NULL, this );
	cbtnAllowZoom->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( WidgetOptionBase::OnCheckAllowZoomBox ), NULL, this );
	sldZoom->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( WidgetOptionBase::OnScrollZoomChanged ), NULL, this );
	cbtnShadow->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( WidgetOptionBase::OnCheckShadowBox ), NULL, this );
	sldOpacity->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( WidgetOptionBase::OnScrollOpacityChanged ), NULL, this );
	btnClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WidgetOptionBase::OnBtnCloseClick ), NULL, this );
}

WidgetOptionBase::~WidgetOptionBase()
{
	// Disconnect Events
	spinX->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( WidgetOptionBase::OnSpinXCtrl ), NULL, this );
	spinY->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( WidgetOptionBase::OnSpinYCtrl ), NULL, this );
	cbtnPin->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( WidgetOptionBase::OnCheckPinBox ), NULL, this );
	choZ->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( WidgetOptionBase::OnChoZ ), NULL, this );
	cbtnAllowZoom->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( WidgetOptionBase::OnCheckAllowZoomBox ), NULL, this );
	sldZoom->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( WidgetOptionBase::OnScrollZoomChanged ), NULL, this );
	cbtnShadow->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( WidgetOptionBase::OnCheckShadowBox ), NULL, this );
	sldOpacity->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( WidgetOptionBase::OnScrollOpacityChanged ), NULL, this );
	btnClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WidgetOptionBase::OnBtnCloseClick ), NULL, this );
	
}

CoreOptionBase::CoreOptionBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	m_listbook3 = new wxListbook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_TOP );
	m_panel7 = new wxPanel( m_listbook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_panel7, wxID_ANY, _("常规") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText10 = new wxStaticText( m_panel7, wxID_ANY, _("开机自动运行"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer1->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_checkBox4 = new wxCheckBox( m_panel7, wxID_ANY, _("启用"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox4->SetValue(true); 
	fgSizer1->Add( m_checkBox4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText11 = new wxStaticText( m_panel7, wxID_ANY, _("选择语言"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer1->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice4Choices;
	m_choice4 = new wxChoice( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice4Choices, 0 );
	m_choice4->SetSelection( 0 );
	fgSizer1->Add( m_choice4, 0, wxALL, 5 );
	
	m_staticText12 = new wxStaticText( m_panel7, wxID_ANY, _("配置文件"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer1->Add( m_staticText12, 0, wxALL, 5 );
	
	wxString m_choice3Choices[] = { _("全局用户"), _("当前用户") };
	int m_choice3NChoices = sizeof( m_choice3Choices ) / sizeof( wxString );
	m_choice3 = new wxChoice( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice3NChoices, m_choice3Choices, 0 );
	m_choice3->SetSelection( 0 );
	fgSizer1->Add( m_choice3, 0, wxALL, 5 );
	
	
	sbSizer10->Add( fgSizer1, 1, wxEXPAND, 5 );
	
	
	bSizer24->Add( sbSizer10, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( m_panel7, wxID_ANY, _("其他") ), wxVERTICAL );
	
	m_checkBox5 = new wxCheckBox( m_panel7, wxID_ANY, _("自动检测新版本"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer12->Add( m_checkBox5, 0, wxALL, 5 );
	
	m_checkBox6 = new wxCheckBox( m_panel7, wxID_ANY, _("隐藏托盘图标"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer12->Add( m_checkBox6, 0, wxALL, 5 );
	
	
	bSizer24->Add( sbSizer12, 1, wxEXPAND, 5 );
	
	
	m_panel7->SetSizer( bSizer24 );
	m_panel7->Layout();
	bSizer24->Fit( m_panel7 );
	m_listbook3->AddPage( m_panel7, _("全局设置"), false );
	m_panel10 = new wxPanel( m_listbook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter2 = new wxSplitterWindow( m_panel10, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter2->Connect( wxEVT_IDLE, wxIdleEventHandler( CoreOptionBase::m_splitter2OnIdle ), NULL, this );
	
	m_panel12 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_panel12, wxID_ANY, _("插件列表") ), wxVERTICAL );
	
	m_listCtrl2 = new wxListCtrl( m_panel12, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	sbSizer8->Add( m_listCtrl2, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panel12->SetSizer( sbSizer8 );
	m_panel12->Layout();
	sbSizer8->Fit( m_panel12 );
	m_panel13 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_panel13, wxID_ANY, _("插件信息") ), wxVERTICAL );
	
	
	m_panel13->SetSizer( sbSizer9 );
	m_panel13->Layout();
	sbSizer9->Fit( m_panel13 );
	m_splitter2->SplitVertically( m_panel12, m_panel13, 223 );
	bSizer18->Add( m_splitter2, 1, wxEXPAND, 5 );
	
	
	m_panel10->SetSizer( bSizer18 );
	m_panel10->Layout();
	bSizer18->Fit( m_panel10 );
	m_listbook3->AddPage( m_panel10, _("插件管理"), true );
	#ifndef __WXGTK__ // Small icon style not supported in GTK
	wxListView* m_listbook3ListView = m_listbook3->GetListView();
	long m_listbook3Flags = m_listbook3ListView->GetWindowStyleFlag();
	m_listbook3Flags = ( m_listbook3Flags & ~wxLC_ICON ) | wxLC_SMALL_ICON;
	m_listbook3ListView->SetWindowStyleFlag( m_listbook3Flags );
	#endif
	
	bSizer16->Add( m_listbook3, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer16 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

CoreOptionBase::~CoreOptionBase()
{
}

AboutBase::AboutBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	m_panel14 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer26->Add( m_panel14, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer27->Add( bSizer28, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer29->Add( m_staticText13, 0, wxALL, 5 );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, _("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer29->Add( m_staticText14, 0, wxALL, 5 );
	
	m_staticText15 = new wxStaticText( this, wxID_ANY, _("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer29->Add( m_staticText15, 0, wxALL, 5 );
	
	m_staticText16 = new wxStaticText( this, wxID_ANY, _("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer29->Add( m_staticText16, 0, wxALL, 5 );
	
	
	bSizer27->Add( bSizer29, 1, wxEXPAND, 5 );
	
	
	bSizer26->Add( bSizer27, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer26 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

AboutBase::~AboutBase()
{
}
