#include "MainFrameCust.h"

#include <wx/aboutdlg.h>

#include "Table.h"

#include "Util.h"

#include <cstdio>

extern "C" size_t req_get_dl(const char* url, const char* path, int use_proxy, const char* proxy, void* headers);

#ifdef USE_THREADING
pthread_mutex_t post_mutex;
pthread_mutex_t comment_mutex;

#define reddit_get_posts_hot reddit_get_posts_hot_t
#define subreddit_get_posts subreddit_get_posts_t
#define post_get_comments post_get_comments_t
#endif

wxString getFile(const char* url){
    if(toString(url) == wxT("default")){
        return wxT("");
    }

    char file_name[256];
    size_t secs = clock();
    const char* tmpDir = getTmpDir();
    sprintf(file_name, "%s%d.jpg", tmpDir, secs);

    req_get_dl(url, file_name, 0, NULL, NULL);

    return toString((char*) file_name);
}

wxBitmap* GetBmp(const char* url){
    wxString fileName = getFile(url);

    if(fileName == wxT("")){
        return NULL;
    }

    wxImage* img = new wxImage;
    img->LoadFile(fileName, wxBITMAP_TYPE_ANY);

    if(img->IsOk()) {
        wxBitmap *bmp = new wxBitmap(*img, -1);
        return bmp;
    }

    return NULL;
}

void post_adder(Post_t* post, void* ptr){
    MainFrameCust* frame = (MainFrameCust*) ptr;

#ifdef USE_THREADING
    pthread_mutex_lock(&post_mutex);
#endif

    frame->NewPostPanel(post);

#ifdef USE_THREADING
    pthread_mutex_unlock(&post_mutex);
#endif
}

void comment_adder(Comment_t* comment, void* ptr, int is_title){
    MainFrameCust* frame = (MainFrameCust*) ptr;

#ifdef USE_THREADING
    pthread_mutex_lock(&comment_mutex);
#endif

    if(is_title){
        frame->AddPostMainComment(comment);
    }else{
        frame->AddComment(comment, frame->comment_root);
    }

#ifdef USE_THREADING
    pthread_mutex_unlock(&comment_mutex);
#endif
}

void MainFrameCust::AddComment(Comment_t *comment, wxTreeItemId parent) {
    if(parent){
        wxTreeItemId id = CommentControl->AppendItem(parent, toString(comment->body));

        for(int i=0 ; i<comment->no_children ; i++){
            AddComment((Comment_t*) comment->children[i], id);
        }
    }
}

void MainFrameCust::AddPostMainComment(Comment *comment) {
    comment_root = CommentControl->AddRoot(toString(comment->title));

    /*if(! comment->thumbnail){
        return;
    }

    wxBitmap* bmp = GetBmp(comment->thumbnail);
    PostPic->SetBitmap(*bmp);*/

    CommentControl->Expand(comment_root);
}

extern "C" void tweak(void* window);

MainFrameCust::MainFrameCust(Reddit_t* reddit, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : MainFrame(parent, id, title, pos, size, style) {
    this->reddit = reddit;
	
	comment_root = NULL;
    selectedSub = wxT("All");

#ifdef MAC_OS_X_VERSION_10_10
    NSWindow* win = MacGetTopLevelWindowRef();
    tweak((void*)win);
#endif
#ifdef __WXGTK3__
    tweak((void*) wxWindow::GetHandle());
#endif

#ifdef __WXQT__
    tweak((void*) GetQMainWindow());
#endif

    reddit_get_posts_hot(reddit, 100, NULL, post_adder, this);

    LoadSubs();

    Refresh();
}

void MainFrameCust::MainFrameOnActivate( wxActivateEvent& event ) {

}


void MainFrameCust::LoadSubs() {
    subs = reddit_get_subbed_list(reddit);
}

void MainFrameCust::MoreButtonOnButtonClick(wxCommandEvent &event) {
    Post_t* prev = posts.at(posts.size()-1);

    const char* fullname = post_fullname(prev);

    if(selectedSub == wxT("All")){
        reddit_get_posts_hot(reddit, 100, fullname, post_adder, this);

    }else {
        Subreddit_t* sub = subreddit_new(toChars(selectedSub));

        subreddit_get_posts(reddit, sub, "hot", 100, fullname, post_adder, this);
    }

    Refresh();
}

void MainFrameCust::NewPostPanel(Post_t *post) {
    posts.push_back(post);

    PostBox* out = new PostBoxCust(m_scrolledWindow1, this, post);

    PostBoxArea->Add(out, 1, wxEXPAND, 0);

    m_scrolledWindow1->GetParent()->Layout();
}

void MainFrameCust::Refresh() {
    PostBoxArea->Layout();
    bSizer3->Layout();

    m_scrolledWindow1->SetSizer( PostBoxArea );
    m_scrolledWindow1->FitInside();
}

void MainFrameCust::LoadPost(Post_t* post) {
    if(comment_root) {
        CommentControl->Delete(comment_root);
        comment_root = NULL;
    }

    PostTitle->SetLabel(toString(post->title));
    PostContent->SetLabel(toString(post->text));

    NoteBook->ChangeSelection(1);

    post_get_comments(reddit, post, 100, NULL, comment_adder, this);
}

void MainFrameCust::ExitBtnPressed(wxCommandEvent &event) {
    wxTopLevelWindowBase::Destroy();
}

void MainFrameCust::GoSubBtnPressed(wxCommandEvent &event) {
    GoSubDlgCust entry(this, subs);

    int ret = entry.ShowModal();

    if(ret == wxID_OK) {
        posts.clear();
        PostBoxArea->Clear(true);

        wxString subName = entry.GetValue();

        if(subName == wxT("All")){
            reddit_get_posts_hot(reddit, 100, NULL, post_adder, this);
        }else {
            Subreddit_t* sub = subreddit_new(toChars(subName));

            subreddit_get_posts(reddit, sub, "hot", 100, NULL, post_adder, this);
        }

        Refresh();
    }
}

void MainFrameCust::NewSubBtnPressed(wxCommandEvent &event) {

}

void MainFrameCust::AboutBtnPressed(wxCommandEvent &event) {
    wxAboutDialogInfo infobox;
    infobox.SetName(toString("WxReddit"));
    infobox.SetVersion(toString("0.1"));
    infobox.SetDescription(toString("This is a simple reddit client written in wxWidgets and c++ that aims to be able to be run on very old hardware."));

    infobox.SetCopyright(toString("(C) 2022"));
    infobox.AddDeveloper(toString("Rhys Adams"));

    wxAboutBox(infobox);
}

PostBoxCust::PostBoxCust(wxWindow* parent, wxWindow* window, Post_t* post) : PostBox(parent){
    this->post = post;
    this->window = window;

    TitleLabel->SetLabel(toString(post->title));
    AuthorLabel->SetLabel(toString(post->author));
    SubredditLabel->SetLabel(toString(post->subreddit));

    if(post_is_img(post)) {
        wxBitmap *bmp = GetBmp(post->url);

        if(bmp != NULL){
            FeedThumb->SetBitmapLabel(*bmp);
        }
    }
}

void PostBoxCust::GoButtonOnButtonClick(wxCommandEvent &event) {
    ((MainFrameCust*) window)->LoadPost(post);
}

void PostBoxCust::ThumbClicked(wxCommandEvent &event) {
    if(post_is_img(post)) {
        wxString toOpen = getFile(post->url);

        HtmlDlg viewer(this);

        viewer.HtmlDisp->SetPage(wxString::Format(wxT("<center><img src='%s'></center>"), toOpen));

        viewer.ShowModal();
    }
}

void PostBoxCust::SubClicked(wxHyperlinkEvent &event) {

}

GoSubDlgCust::GoSubDlgCust(wxWindow *parent, List_t* subs) : GoSubDlg(parent) {
    for(int i=0 ; i<subs->length ; i++) {
        Subreddit_t* sub = (Subreddit_t *) subs->data[i];

        SubBox->Append(toString(sub->name));
    }
}

void GoSubDlgCust::CancelBtnPressed(wxCommandEvent &event) {
    wxDialog::EndModal(wxID_CANCEL);
}

void GoSubDlgCust::OkBtnPressed(wxCommandEvent &event) {
    wxDialog::EndModal(wxID_OK);
}

wxString GoSubDlgCust::GetValue() {
    return SubBox->GetValue();
}
