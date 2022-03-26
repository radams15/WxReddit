#include "MainFrame.h"

#include "Table.h"

#include "Reddit.h"

class MainFrameCust : public MainFrame{
private:

    void LoadSubs();

protected:
    void MainFrameOnActivate( wxActivateEvent& event );
    void SubBoxOnCombobox( wxCommandEvent& event );
    void MoreButtonOnButtonClick( wxCommandEvent& event );

    Reddit_t* reddit;
    List_t* subs;

public:
    std::vector< Post_t* > posts;

    wxTreeItemId comment_root = NULL;

    void NewPostPanel(Post_t* post);

    void Refresh();

    MainFrameCust( Reddit_t* reddit, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Reddit"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 790,549 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

    void AddComment(Comment_t* comment, wxTreeItemId);

    void AddPostMainComment(Comment* comment);

    void LoadPost(Post_t* post);
};

class PostBoxCust : public PostBox{
private:
    Post_t* post;
    wxWindow* window;
protected:
    void GoButtonOnButtonClick( wxCommandEvent& event );
public:
    PostBoxCust(wxWindow* parent, wxWindow* window, Post_t* post);
};
