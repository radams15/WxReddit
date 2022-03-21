#include "MainFrameCust.h"

#include "Table.h"

#include "Util.h"

#include <cstdio>

void adder(Post_t* post, void* ptr){
    MainFrameCust* frame = (MainFrameCust*) ptr;
    frame->NewPostPanel(post);
}

#ifdef MAC_OS_X_VERSION_10_10
void set_unified_toolbar(void* ptr);
#endif

#ifdef __WXGTK3__
extern "C" void set_unified_toolbar(void* winptr);
#endif

MainFrameCust::MainFrameCust(Reddit_t* reddit, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : MainFrame(parent, id, title, pos, size, style){
    this->reddit = reddit;

#ifdef MAC_OS_X_VERSION_10_10
    NSWindow* win = MacGetTopLevelWindowRef();
    set_unified_toolbar((void*)win);
#endif

#ifdef __WXGTK3__
    set_unified_toolbar(wxWindow::GetHandle());
#endif

    reddit_get_posts_hot(reddit, -1, NULL, adder, this);

    LoadSubs();

    Refresh();
}

void MainFrameCust::MainFrameOnActivate( wxActivateEvent& event ) {

}

void MainFrameCust::SubBoxOnCombobox(wxCommandEvent &event) {
    int i = SubBox->GetSelection();

    PostBox->Clear(true);
    posts.clear();

    if(i == 0){
        reddit_get_posts_hot(reddit, -1, NULL, adder, this);

    }else {
        Subreddit_t* sub = (Subreddit_t*) subs->data[i-1];

        subreddit_get_posts(reddit, sub, "hot", -1, NULL, adder, this);
    }

    Refresh();
}

void MainFrameCust::LoadSubs() {
    subs = reddit_get_subbed_list(reddit);

    for(int i=0 ; i<subs->length ; i++) {
        Subreddit_t* sub = (Subreddit_t *) subs->data[i];

        SubBox->Append(sub->name);
    }
}

void MainFrameCust::MoreButtonOnButtonClick(wxCommandEvent &event) {
    Post_t* prev = posts.at(posts.size()-1);

    int i = SubBox->GetSelection();

    const char* fullname = post_fullname(prev);

    if(i == 0 || i == -1){
        reddit_get_posts_hot(reddit, -1, fullname, adder, this);

    }else {
        Subreddit_t* sub = (Subreddit_t*) subs->data[i-1];

        subreddit_get_posts(reddit, sub, "hot", -1, fullname, adder, this);
    }

    Refresh();
}

void MainFrameCust::NewPostPanel(Post_t *post) {
    posts.push_back(post);

    PostPanel* out = new PostPanelCust(m_scrolledWindow1, post);

    PostBox->Add(out, 1, wxEXPAND, 0);

    m_scrolledWindow1->GetParent()->Layout();
}

void MainFrameCust::Refresh() {
    PostBox->Layout();
    bSizer3->Layout();

    m_scrolledWindow1->SetSizer( PostBox );
    m_scrolledWindow1->FitInside();
}

void MainFrameCust::LoadPost(Post_t* post) {
    PostTitle->SetLabel(post->title);
    PostContent->SetLabel(post->text);
}

PostPanelCust::PostPanelCust(wxWindow * parent, Post_t* post) : PostPanel(parent){
    this->post = post;

    TitleLabel->SetLabel(post->title);
    AuthorLabel->SetLabel(post->author);
    SubredditLabel->SetLabel(post->subreddit);
}

void PostPanelCust::GoButtonOnButtonClick(wxCommandEvent &event) {
    ((MainFrameCust*) m_parent)->LoadPost(post);
}
