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
	lbOption->AddPage( panProperty, _("参数设置"), false );
	lbOptionBitmap = wxNullBitmap;
	if ( lbOptionBitmap.Ok() )
	{
		lbOptionImage = lbOptionBitmap.ConvertToImage();
		lbOptionImages->Add( lbOptionImage.Scale( lbOptionImageSize.GetWidth(), lbOptionImageSize.GetHeight() ) );
		lbOption->SetPageImage( lbOptionIndex, lbOptionIndex );
		lbOptionIndex++;
	}
	panHotKey = new wxPanel( lbOption, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	sizerHotKey = new wxBoxSizer( wxVERTICAL );
	
	
	panHotKey->SetSizer( sizerHotKey );
	panHotKey->Layout();
	sizerHotKey->Fit( panHotKey );
	lbOption->AddPage( panHotKey, _("热键设置"), true );
	
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
