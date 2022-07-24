#include "MainFrame.h"

#include "Table.h"

#include "Reddit.h"

class MainFrameCust : public MainFrame{
private:

    void LoadSubs();

protected:
    void MainFrameOnActivate( wxActivateEvent& event );
    void MoreButtonOnButtonClick( wxCommandEvent& event );

    void ExitBtnPressed( wxCommandEvent& event );
    void GoSubBtnPressed( wxCommandEvent& event );
    void NewSubBtnPressed( wxCommandEvent& event );
    void AboutBtnPressed( wxCommandEvent& event );

    Reddit* reddit;
    std::vector<Subreddit*> subs;
    wxString selectedSub;

public:
    std::vector< Post* > posts;

    void NewPostPanel(Post* post);

    void Refresh();

    MainFrameCust( Reddit* reddit, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Reddit"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 790,549 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

    void LoadPost(Post* post);
};

class PostBoxCust : public PostBox{
private:
    Post* post;
    wxWindow* window;
protected:
    void GoButtonOnButtonClick( wxCommandEvent& event );
    void ThumbClicked( wxCommandEvent& event );
    void SubClicked( wxHyperlinkEvent& event );
public:
    PostBoxCust(wxWindow* parent, wxWindow* window, Post* post);
};

class GoSubDlgCust : public GoSubDlg {
private:
    wxString value;

protected:
    void CancelBtnPressed( wxCommandEvent& event );
    void OkBtnPressed( wxCommandEvent& event );

public:
    GoSubDlgCust( wxWindow* parent, std::vector<Subreddit*> subs);

    wxString GetValue();

};
