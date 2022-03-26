///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainFrame.h"

///////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE( MainFrame, wxFrame )
	EVT_ACTIVATE_APP( MainFrame::_wxFB_MainFrameOnActivate )
	EVT_COMBOBOX( wxID_ANY, MainFrame::_wxFB_SubBoxOnCombobox )
	EVT_BUTTON( wxID_ANY, MainFrame::_wxFB_MoreButtonOnButtonClick )
END_EVENT_TABLE()

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	bSizer3 = new wxBoxSizer( wxVERTICAL );

	NoteBook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	FeedPanel = new wxPanel( NoteBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_scrolledWindow1 = new wxScrolledWindow( FeedPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	PostBoxArea = new wxBoxSizer( wxVERTICAL );


	m_scrolledWindow1->SetSizer( PostBoxArea );
	m_scrolledWindow1->Layout();
	PostBoxArea->Fit( m_scrolledWindow1 );
	bSizer6->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );


	FeedPanel->SetSizer( bSizer6 );
	FeedPanel->Layout();
	bSizer6->Fit( FeedPanel );
	NoteBook->AddPage( FeedPanel, wxT("Feed"), true );
	PostPanel = new wxPanel( NoteBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	m_scrolledWindow2 = new wxScrolledWindow( PostPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow2->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	PostTitle = new wxStaticText( m_scrolledWindow2, wxID_ANY, wxT("Post Title"), wxDefaultPosition, wxDefaultSize, 0 );
	PostTitle->Wrap( -1 );
	PostTitle->SetFont( wxFont( 24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer9->Add( PostTitle, 0, wxALL|wxEXPAND, 5 );

	PostPic = new wxStaticBitmap( m_scrolledWindow2, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( PostPic, 0, wxALL|wxEXPAND, 5 );

	PostContent = new wxStaticText( m_scrolledWindow2, wxID_ANY, wxT("Content"), wxDefaultPosition, wxDefaultSize, 0 );
	PostContent->Wrap( -1 );
	bSizer9->Add( PostContent, 0, wxALL|wxEXPAND, 5 );


	bSizer7->Add( bSizer9, 1, wxEXPAND, 5 );

	CommentControl = new wxTreeCtrl( m_scrolledWindow2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	bSizer7->Add( CommentControl, 4, wxALL|wxEXPAND, 5 );


	m_scrolledWindow2->SetSizer( bSizer7 );
	m_scrolledWindow2->Layout();
	bSizer7->Fit( m_scrolledWindow2 );
	bSizer8->Add( m_scrolledWindow2, 1, wxEXPAND | wxALL, 5 );


	PostPanel->SetSizer( bSizer8 );
	PostPanel->Layout();
	bSizer8->Fit( PostPanel );
	NoteBook->AddPage( PostPanel, wxT("Post"), false );

	bSizer3->Add( NoteBook, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer3 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 1, 0, wxID_ANY );
	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	SubBox = new wxComboBox( m_toolBar1, wxID_ANY, wxT("All"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	SubBox->Append( wxT("All") );
	SubBox->SetSelection( 0 );
	m_toolBar1->AddControl( SubBox );
	MoreButton = new wxButton( m_toolBar1, wxID_ANY, wxT("More"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar1->AddControl( MoreButton );
	m_toolBar1->Realize();


	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
}

BEGIN_EVENT_TABLE( PostBox, wxPanel )
	EVT_BUTTON( wxID_ANY, PostBox::_wxFB_GoButtonOnButtonClick )
END_EVENT_TABLE()

PostBox::PostBox( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	FeedThumb = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( FeedThumb, 3, wxALL, 5 );

	TitleLabel = new wxStaticText( this, wxID_ANY, wxT("Title"), wxDefaultPosition, wxDefaultSize, 0 );
	TitleLabel->Wrap( -1 );
	bSizer4->Add( TitleLabel, 1, wxALL, 5 );

	AuthorLabel = new wxStaticText( this, wxID_ANY, wxT("Author"), wxDefaultPosition, wxDefaultSize, 0 );
	AuthorLabel->Wrap( -1 );
	bSizer4->Add( AuthorLabel, 1, wxALL, 5 );

	SubredditLabel = new wxStaticText( this, wxID_ANY, wxT("Subreddit"), wxDefaultPosition, wxDefaultSize, 0 );
	SubredditLabel->Wrap( -1 );
	bSizer4->Add( SubredditLabel, 1, wxALL, 5 );

	GoButton = new wxButton( this, wxID_ANY, wxT("Go"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( GoButton, 0, wxALL, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();
}

PostBox::~PostBox()
{
}
