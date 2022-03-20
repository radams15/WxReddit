///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainFrame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	MainGrid = new wxGrid( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	MainGrid->CreateGrid( 5, 5 );
	MainGrid->EnableEditing( false );
	MainGrid->EnableGridLines( true );
	MainGrid->EnableDragGridSize( false );
	MainGrid->SetMargins( 0, 0 );

	// Columns
	MainGrid->EnableDragColMove( false );
	MainGrid->EnableDragColSize( true );
	MainGrid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	MainGrid->EnableDragRowSize( true );
	MainGrid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	MainGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer4->Add( MainGrid, 0, wxALL|wxEXPAND, 5 );


	m_scrolledWindow1->SetSizer( bSizer4 );
	m_scrolledWindow1->Layout();
	bSizer4->Fit( m_scrolledWindow1 );
	bSizer3->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer3 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	SubBox = new wxComboBox( m_toolBar1, wxID_ANY, wxT("All"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	SubBox->Append( wxT("All") );
	SubBox->SetSelection( 0 );
	m_toolBar1->AddControl( SubBox );
	MoreButton = new wxButton( m_toolBar1, wxID_ANY, wxT("More"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar1->AddControl( MoreButton );
	m_toolBar1->Realize();


	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( MainFrame::MainFrameOnActivate ) );
	SubBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( MainFrame::SubBoxOnCombobox ), NULL, this );
	MoreButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::MoreButtonOnButtonClick ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( MainFrame::MainFrameOnActivate ) );
	SubBox->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( MainFrame::SubBoxOnCombobox ), NULL, this );
	MoreButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::MoreButtonOnButtonClick ), NULL, this );

}
