///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainFrame.h"

#include "../../res/load.png.h"

///////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE( MainFrame, wxFrame )
	EVT_ACTIVATE_APP( MainFrame::_wxFB_MainFrameOnActivate )
	EVT_TOOL( ID_MORE_BTN, MainFrame::_wxFB_MoreButtonOnButtonClick )
	EVT_MENU( wxID_EXIT, MainFrame::_wxFB_ExitBtnPressed )
	EVT_MENU( ID_GOSUB, MainFrame::_wxFB_GoSubBtnPressed )
	EVT_MENU( ID_NEWSUB, MainFrame::_wxFB_NewSubBtnPressed )
	EVT_MENU( wxID_ABOUT, MainFrame::_wxFB_AboutBtnPressed )
END_EVENT_TABLE()

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	PostBoxArea = new wxBoxSizer( wxVERTICAL );


	m_scrolledWindow1->SetSizer( PostBoxArea );
	m_scrolledWindow1->Layout();
	PostBoxArea->Fit( m_scrolledWindow1 );
	bSizer3->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer3 );
	this->Layout();
	StatusBar1 = this->CreateStatusBar( 1, 0, wxID_ANY );
	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL|wxTB_TEXT, wxID_ANY );
	MoreBtn = m_toolBar1->AddTool( ID_MORE_BTN, wxT("More"), load_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Loads more posts"), NULL );

	m_toolBar1->Realize();

	m_menubar1 = new wxMenuBar( 0 );
	FileMenu = new wxMenu();
	wxMenuItem* ExitBtn;
	ExitBtn = new wxMenuItem( FileMenu, wxID_EXIT, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	FileMenu->Append( ExitBtn );

	m_menubar1->Append( FileMenu, wxT("File") );

	SubredditMenu = new wxMenu();
	wxMenuItem* GoSubBtn;
	GoSubBtn = new wxMenuItem( SubredditMenu, ID_GOSUB, wxString( wxT("Go To Sub") ) , wxEmptyString, wxITEM_NORMAL );
	SubredditMenu->Append( GoSubBtn );

	wxMenuItem* NewSubBtn;
	NewSubBtn = new wxMenuItem( SubredditMenu, ID_NEWSUB, wxString( wxT("Add New Subscription") ) , wxEmptyString, wxITEM_NORMAL );
	SubredditMenu->Append( NewSubBtn );

	m_menubar1->Append( SubredditMenu, wxT("Subreddit") );

	HelpMenu = new wxMenu();
	wxMenuItem* AboutBtn;
	AboutBtn = new wxMenuItem( HelpMenu, wxID_ABOUT, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	HelpMenu->Append( AboutBtn );

	m_menubar1->Append( HelpMenu, wxT("Help") );

	this->SetMenuBar( m_menubar1 );


	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
}

BEGIN_EVENT_TABLE( PostBox, wxPanel )
	EVT_BUTTON( ID_THUMB, PostBox::_wxFB_ThumbClicked )
	EVT_HYPERLINK( wxID_ANY, PostBox::_wxFB_SubClicked )
	EVT_BUTTON( ID_GO_BTN, PostBox::_wxFB_GoButtonOnButtonClick )
END_EVENT_TABLE()

PostBox::PostBox( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	FeedThumb = new wxBitmapButton( this, ID_THUMB, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );
	bSizer4->Add( FeedThumb, 5, wxALIGN_CENTER|wxALL|wxSHAPED, 5 );

	TitleLabel = new wxStaticText( this, wxID_ANY, wxT("Title"), wxDefaultPosition, wxDefaultSize, 0 );
	TitleLabel->Wrap( 200 );
	bSizer4->Add( TitleLabel, 2, wxALL, 5 );

	AuthorLabel = new wxStaticText( this, wxID_ANY, wxT("Author"), wxDefaultPosition, wxDefaultSize, 0 );
	AuthorLabel->Wrap( -1 );
	bSizer4->Add( AuthorLabel, 0, wxALL, 5 );

	SubredditLabel = new wxHyperlinkCtrl( this, wxID_ANY, wxT("Subreddit"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer4->Add( SubredditLabel, 0, wxALL, 5 );

	GoButton = new wxButton( this, ID_GO_BTN, wxT("Go"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( GoButton, 0, wxALL, 5 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer4->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();
}

PostBox::~PostBox()
{
}

BEGIN_EVENT_TABLE( GoSubDlg, wxDialog )
	EVT_BUTTON( ID_CANCEL, GoSubDlg::_wxFB_CancelBtnPressed )
	EVT_BUTTON( ID_SUB_DLG_OK, GoSubDlg::_wxFB_OkBtnPressed )
END_EVENT_TABLE()

GoSubDlg::GoSubDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Subreddit:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer9->Add( m_staticText6, 1, wxALL, 5 );

	SubBox = new wxComboBox( this, wxID_ANY, wxT("All"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer9->Add( SubBox, 3, wxALL, 5 );


	bSizer8->Add( bSizer9, 1, wxEXPAND, 5 );


	bSizer8->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );


	bSizer10->Add( 0, 0, 1, wxEXPAND, 5 );

	CancelBtn = new wxButton( this, ID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( CancelBtn, 0, wxALL, 5 );

	OkBtn = new wxButton( this, ID_SUB_DLG_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( OkBtn, 0, wxALL, 5 );


	bSizer8->Add( bSizer10, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer8 );
	this->Layout();

	this->Centre( wxBOTH );
}

GoSubDlg::~GoSubDlg()
{
}

HtmlDlg::HtmlDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	HtmlDisp = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_NO_SELECTION|wxHW_SCROLLBAR_AUTO );
	bSizer11->Add( HtmlDisp, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer11 );
	this->Layout();

	this->Centre( wxBOTH );
}

HtmlDlg::~HtmlDlg()
{
}

PostFrame::PostFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	m_scrolledWindow2 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow2->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	PostTitle = new wxStaticText( m_scrolledWindow2, wxID_ANY, wxT("Post Title"), wxDefaultPosition, wxDefaultSize, 0 );
	PostTitle->Wrap( 200 );
	PostTitle->SetFont( wxFont( 24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer9->Add( PostTitle, 0, wxALL|wxEXPAND, 5 );

	PostPic = new wxStaticBitmap( m_scrolledWindow2, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( PostPic, 5, wxALIGN_CENTER_HORIZONTAL|wxALL|wxRESERVE_SPACE_EVEN_IF_HIDDEN|wxSHAPED, 5 );

	PostContent = new wxStaticText( m_scrolledWindow2, wxID_ANY, wxT("Content"), wxDefaultPosition, wxDefaultSize, 0 );
	PostContent->Wrap( 200 );
	bSizer9->Add( PostContent, 2, wxALL|wxEXPAND, 5 );


	bSizer7->Add( bSizer9, 2, wxEXPAND, 5 );

	CommentControl = new wxTreeCtrl( m_scrolledWindow2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	bSizer7->Add( CommentControl, 1, wxALL|wxEXPAND, 5 );


	m_scrolledWindow2->SetSizer( bSizer7 );
	m_scrolledWindow2->Layout();
	bSizer7->Fit( m_scrolledWindow2 );
	bSizer8->Add( m_scrolledWindow2, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer8 );
	this->Layout();

	this->Centre( wxBOTH );
}

PostFrame::~PostFrame()
{
}
