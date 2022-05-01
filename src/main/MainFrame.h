///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/sizer.h>
#include <wx/gdicmn.h>
#include <wx/scrolwin.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/hyperlink.h>
#include <wx/statline.h>
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/html/htmlwin.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
	DECLARE_EVENT_TABLE()
	private:

		// Private event handlers
		void _wxFB_MainFrameOnActivate( wxActivateEvent& event ){ MainFrameOnActivate( event ); }
		void _wxFB_MoreButtonOnButtonClick( wxCommandEvent& event ){ MoreButtonOnButtonClick( event ); }
		void _wxFB_ExitBtnPressed( wxCommandEvent& event ){ ExitBtnPressed( event ); }
		void _wxFB_GoSubBtnPressed( wxCommandEvent& event ){ GoSubBtnPressed( event ); }
		void _wxFB_NewSubBtnPressed( wxCommandEvent& event ){ NewSubBtnPressed( event ); }
		void _wxFB_AboutBtnPressed( wxCommandEvent& event ){ AboutBtnPressed( event ); }


	protected:
		enum
		{
			ID_MORE_BTN = 1000,
			ID_GOSUB,
			ID_NEWSUB
		};

		wxBoxSizer* bSizer3;
		wxNotebook* NoteBook;
		wxPanel* FeedPanel;
		wxScrolledWindow* m_scrolledWindow1;
		wxPanel* PostPanel;
		wxScrolledWindow* m_scrolledWindow2;
		wxStaticText* PostTitle;
		wxStaticBitmap* PostPic;
		wxStaticText* PostContent;
		wxTreeCtrl* CommentControl;
		wxStatusBar* StatusBar1;
		wxToolBar* m_toolBar1;
		wxToolBarToolBase* MoreBtn;
		wxMenuBar* m_menubar1;
		wxMenu* FileMenu;
		wxMenu* SubredditMenu;
		wxMenu* HelpMenu;

		// Virtual event handlers, override them in your derived class
		virtual void MainFrameOnActivate( wxActivateEvent& event ) { event.Skip(); }
		virtual void MoreButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ExitBtnPressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void GoSubBtnPressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void NewSubBtnPressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void AboutBtnPressed( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxBoxSizer* PostBoxArea;

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Reddit"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 790,549 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PostBox
///////////////////////////////////////////////////////////////////////////////
class PostBox : public wxPanel
{
	DECLARE_EVENT_TABLE()
	private:

		// Private event handlers
		void _wxFB_ThumbClicked( wxCommandEvent& event ){ ThumbClicked( event ); }
		void _wxFB_SubClicked( wxHyperlinkEvent& event ){ SubClicked( event ); }
		void _wxFB_GoButtonOnButtonClick( wxCommandEvent& event ){ GoButtonOnButtonClick( event ); }


	protected:
		enum
		{
			ID_THUMB = 1000,
			ID_GO_BTN
		};

		wxBitmapButton* FeedThumb;
		wxHyperlinkCtrl* SubredditLabel;
		wxButton* GoButton;
		wxStaticLine* m_staticline1;

		// Virtual event handlers, override them in your derived class
		virtual void ThumbClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void SubClicked( wxHyperlinkEvent& event ) { event.Skip(); }
		virtual void GoButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxStaticText* TitleLabel;
		wxStaticText* AuthorLabel;

		PostBox( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 299,426 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~PostBox();

};

///////////////////////////////////////////////////////////////////////////////
/// Class GoSubDlg
///////////////////////////////////////////////////////////////////////////////
class GoSubDlg : public wxDialog
{
	DECLARE_EVENT_TABLE()
	private:

		// Private event handlers
		void _wxFB_CancelBtnPressed( wxCommandEvent& event ){ CancelBtnPressed( event ); }
		void _wxFB_OkBtnPressed( wxCommandEvent& event ){ OkBtnPressed( event ); }


	protected:
		enum
		{
			ID_CANCEL = 1000,
			ID_SUB_DLG_OK
		};

		wxStaticText* m_staticText6;
		wxComboBox* SubBox;
		wxButton* CancelBtn;
		wxButton* OkBtn;

		// Virtual event handlers, override them in your derived class
		virtual void CancelBtnPressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void OkBtnPressed( wxCommandEvent& event ) { event.Skip(); }


	public:

		GoSubDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Go To Subreddit"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 418,214 ), long style = wxDEFAULT_DIALOG_STYLE );

		~GoSubDlg();

};

///////////////////////////////////////////////////////////////////////////////
/// Class HtmlDlg
///////////////////////////////////////////////////////////////////////////////
class HtmlDlg : public wxDialog
{
	private:

	protected:

	public:
		wxHtmlWindow* HtmlDisp;

		HtmlDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Image Viewer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 390,242 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~HtmlDlg();

};

