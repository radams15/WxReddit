///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
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
#include <wx/notebook.h>
#include <wx/statusbr.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/toolbar.h>
#include <wx/frame.h>

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
		void _wxFB_SubBoxOnCombobox( wxCommandEvent& event ){ SubBoxOnCombobox( event ); }
		void _wxFB_MoreButtonOnButtonClick( wxCommandEvent& event ){ MoreButtonOnButtonClick( event ); }


	protected:
		wxBoxSizer* bSizer3;
		wxNotebook* m_notebook1;
		wxPanel* m_panel1;
		wxScrolledWindow* m_scrolledWindow1;
		wxPanel* m_panel2;
		wxScrolledWindow* m_scrolledWindow2;
		wxStaticText* PostTitle;
		wxStaticBitmap* PostPic;
		wxStaticText* PostContent;
		wxStatusBar* m_statusBar1;
		wxToolBar* m_toolBar1;
		wxComboBox* SubBox;
		wxButton* MoreButton;

		// Virtual event handlers, override them in your derived class
		virtual void MainFrameOnActivate( wxActivateEvent& event ) { event.Skip(); }
		virtual void SubBoxOnCombobox( wxCommandEvent& event ) { event.Skip(); }
		virtual void MoreButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxBoxSizer* PostBox;

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Reddit"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 790,549 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PostPanel
///////////////////////////////////////////////////////////////////////////////
class PostPanel : public wxPanel
{
	DECLARE_EVENT_TABLE()
	private:

		// Private event handlers
		void _wxFB_GoButtonOnButtonClick( wxCommandEvent& event ){ GoButtonOnButtonClick( event ); }


	protected:
		wxButton* GoButton;

		// Virtual event handlers, override them in your derived class
		virtual void GoButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxStaticBitmap* FeedThumb;
		wxStaticText* TitleLabel;
		wxStaticText* AuthorLabel;
		wxStaticText* SubredditLabel;

		PostPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,155 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~PostPanel();

};

