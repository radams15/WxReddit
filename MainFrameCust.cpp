#include "MainFrameCust.h"

#include "Table.h"

#include "Util.h"

#include <cstdio>

void post_adder(Post_t* post, void* ptr){
    MainFrameCust* frame = (MainFrameCust*) ptr;
    frame->NewPostPanel(post);
}

void comment_adder(Comment_t* comment, void* ptr, int is_title){
    MainFrameCust* frame = (MainFrameCust*) ptr;

    if(is_title){
        frame->AddPostMainComment(comment);
    }else{
        frame->AddComment(comment, frame->comment_root);
    }
}

void MainFrameCust::AddComment(Comment_t *comment, wxTreeItemId parent) {
    if(parent != NULL){
        wxTreeItemId id = CommentControl->AppendItem(parent, comment->body);

        for(int i=0 ; i<comment->no_children ; i++){
            AddComment(comment->children[i], id);
        }
    }
}

void MainFrameCust::AddPostMainComment(Comment *comment) {
    comment_root = CommentControl->AddRoot(comment->title);

    printf("Image: %s\n", comment->thumbnail);

    CommentControl->Expand(comment_root);
}

extern "C" void tweak(void* window);

MainFrameCust::MainFrameCust(Reddit_t* reddit, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : MainFrame(parent, id, title, pos, size, style) {
    this->reddit = reddit;

#ifdef MAC_OS_X_VERSION_10_10
    NSWindow* win = MacGetTopLevelWindowRef();
    tweak((void*)win);
#endif
#ifdef __WXGTK3__
    tweak((void*) wxWindow::GetHandle());
#endif

    reddit_get_posts_hot(reddit, -1, NULL, post_adder, this);

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
        reddit_get_posts_hot(reddit, -1, NULL, post_adder, this);

    }else {
        Subreddit_t* sub = (Subreddit_t*) subs->data[i-1];

        subreddit_get_posts(reddit, sub, "hot", -1, NULL, post_adder, this);
    }

    Refresh();
}

void MainFrameCust::LoadSubs() {
    subs = reddit_get_subbed_list(reddit);

    for(int i=0 ; i<subs->length ; i++) {
        Subreddit_t* sub = (Subreddit_t *) subs->data[i];

        SubBox->Append(toString(sub->name));
    }
}

void MainFrameCust::MoreButtonOnButtonClick(wxCommandEvent &event) {
    Post_t* prev = posts.at(posts.size()-1);

    int i = SubBox->GetSelection();

    const char* fullname = post_fullname(prev);

    if(i == 0 || i == -1){
        reddit_get_posts_hot(reddit, -1, fullname, post_adder, this);

    }else {
        Subreddit_t* sub = (Subreddit_t*) subs->data[i-1];

        subreddit_get_posts(reddit, sub, "hot", -1, fullname, post_adder, this);
    }

    Refresh();
}

void MainFrameCust::NewPostPanel(Post_t *post) {
    posts.push_back(post);

    PostPanel* out = new PostPanelCust(m_scrolledWindow1, this, post);

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
    if(comment_root != NULL) {
        CommentControl->Delete(comment_root);
        comment_root = NULL;
    }

    PostTitle->SetLabel(toString(post->title));
    PostContent->SetLabel(toString(post->text));

    post_get_comments(reddit, post, -1, NULL, comment_adder, this);
}

PostPanelCust::PostPanelCust(wxWindow* parent, wxWindow* window, Post_t* post) : PostPanel(parent){
    this->post = post;
    this->window = window;

    TitleLabel->SetLabel(toString(post->title));
    AuthorLabel->SetLabel(toString(post->author));
    SubredditLabel->SetLabel(toString(post->subreddit));
}

void PostPanelCust::GoButtonOnButtonClick(wxCommandEvent &event) {
    ((MainFrameCust*) window)->LoadPost(post);
}
