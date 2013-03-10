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
	
	panTree = new wxPanel( splMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerTree;
	bSizerTree = new wxBoxSizer( wxVERTICAL );
	
	noteTree = new wxNotebook( panTree, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	panRuning = new wxPanel( noteTree, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizerRuning = new wxBoxSizer( wxVERTICAL );
	
	
	panRuning->SetSizer( bSizerRuning );
	panRuning->Layout();
	bSizerRuning->Fit( panRuning );
	noteTree->AddPage( panRuning, _("运行中"), true );
	panInstalled = new wxPanel( noteTree, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizerInstalled = new wxBoxSizer( wxVERTICAL );
	
	
	panInstalled->SetSizer( bSizerInstalled );
	panInstalled->Layout();
	bSizerInstalled->Fit( panInstalled );
	noteTree->AddPage( panInstalled, _("已安装"), false );
	
	bSizerTree->Add( noteTree, 1, wxEXPAND | wxALL, 5 );
	
	
	panTree->SetSizer( bSizerTree );
	panTree->Layout();
	bSizerTree->Fit( panTree );
	panViewer = new wxPanel( splMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerViewer;
	bSizerViewer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerPreview;
	sbSizerPreview = new wxStaticBoxSizer( new wxStaticBox( panViewer, wxID_ANY, _("预览") ), wxVERTICAL );
	
	
	bSizerViewer->Add( sbSizerPreview, 1, wxEXPAND, 5 );
	
	
	panViewer->SetSizer( bSizerViewer );
	panViewer->Layout();
	bSizerViewer->Fit( panViewer );
	splMain->SplitVertically( panTree, panViewer, 195 );
	bSizerMain->Add( splMain, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
}

DesktopToolsBase::~DesktopToolsBase()
{
}
