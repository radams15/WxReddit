#include "MainFrameCust.h"

#include <wx/aboutdlg.h>

#include "Table.h"

#include "Util.h"
#include "PostFrameCust.h"

#include <cstdio>

extern "C" size_t req_get_dl(const char* url, const char* path, int use_proxy, const char* proxy, void* headers);

#ifdef USE_THREADING
pthread_mutex_t post_mutex;
pthread_mutex_t comment_mutex;

#define reddit_get_posts_hot reddit_get_posts_hot_t
#define subreddit_get_posts subreddit_get_posts_t
#define post_get_comments post_get_comments_t
#endif

void post_adder(Post* post, void* ptr){
    MainFrameCust* frame = (MainFrameCust*) ptr;

#ifdef USE_THREADING
    pthread_mutex_lock(&post_mutex);
#endif

    frame->NewPostPanel(post);

#ifdef USE_THREADING
    pthread_mutex_unlock(&post_mutex);
#endif
}

extern "C" void tweak(void* window);

MainFrameCust::MainFrameCust(Reddit* reddit, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : MainFrame(parent, id, title, pos, size, style) {
    this->reddit = reddit;
	
    selectedSub = wxT("All");

#ifdef MAC_OS_X_VERSION_10_10
    NSWindow* win = (NSWindow*) MacGetTopLevelWindowRef();
    tweak((void*)win);
#endif
#ifdef __WXGTK3__
    tweak((void*) wxWindow::GetHandle());
#endif

#ifdef __WXQT__
    tweak((void*) GetQMainWindow());
#endif

    reddit->get_posts_hot(100, "", post_adder, this);

    LoadSubs();

    Refresh();
}

void MainFrameCust::MainFrameOnActivate( wxActivateEvent& event ) {

}


void MainFrameCust::LoadSubs() {
    subs = reddit->get_subbed_list();
}

void MainFrameCust::MoreButtonOnButtonClick(wxCommandEvent &event) {
    Post* prev = posts.at(posts.size()-1);

    wxString fullname = wxString::FromUTF8(prev->fullname());

    if(selectedSub == wxT("All")){
        reddit->get_posts_hot(100, fullname.ToStdString(), post_adder, this);

    }else {
        Subreddit* sub = new Subreddit(reddit, selectedSub.ToStdString());

        sub->get_posts("hot", 100, fullname.ToStdString(), post_adder, this);
    }

    Refresh();
}
void MainFrameCust::NewPostPanel(Post* post) {
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

void MainFrameCust::LoadPost(Post* post) {
    PostFrameCust* frame = new PostFrameCust(this);

    frame->LoadPost(post);

    frame->Show();
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
            reddit->get_posts_hot(100, "", post_adder, this);
        }else {
            Subreddit* sub = new Subreddit(reddit, subName.ToStdString());

            sub->get_posts("hot", 100, "", post_adder, this);
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

PostBoxCust::PostBoxCust(wxWindow* parent, wxWindow* window, Post* post) : PostBox(parent){
    this->post = post;
    this->window = window;

    TitleLabel->SetLabel(wxString::FromUTF8(post->title));
    AuthorLabel->SetLabel(wxString::FromUTF8(post->author));
    SubredditLabel->SetLabel(wxString::FromUTF8(post->subreddit->name));

    std::string thumb = post->get_thumb_path();
    if(thumb.length() > 0) {
        wxBitmap *bmp = GetBmp(wxString::FromUTF8(thumb));

        if(bmp != NULL){
            FeedThumb->SetBitmapLabel(*bmp);
        }
    }
}

void PostBoxCust::GoButtonOnButtonClick(wxCommandEvent &event) {
    ((MainFrameCust*) window)->LoadPost(post);
}

void PostBoxCust::ThumbClicked(wxCommandEvent &event) {
    if(post->is_img()) {
        wxString toOpen = wxString::FromUTF8(post->get_image_path());

        HtmlDlg viewer(this);

        viewer.HtmlDisp->SetPage(wxString::Format(wxT("<center><img src='%s'></center>"), toOpen));

        viewer.ShowModal();
    }
}

void PostBoxCust::SubClicked(wxHyperlinkEvent &event) {

}

GoSubDlgCust::GoSubDlgCust(wxWindow *parent, std::vector<Subreddit*> subs) : GoSubDlg(parent) {
    for(int i=0 ; i<subs.size() ; i++) {
        Subreddit* sub =  subs.at(i);

        SubBox->Append(wxString::FromUTF8(sub->name));
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
