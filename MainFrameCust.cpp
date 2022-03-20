#include "MainFrameCust.h"

#include "Table.h"

#include "Util.h"

#include <cstdio>

void adder(Post_t* post, void* ptr){
	Table* table = (Table*) ptr;

	table->append(post);
}

MainFrameCust::MainFrameCust(Reddit_t* reddit, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : MainFrame(parent, id, title, pos, size, style){
    this->reddit = reddit;
	table = new Table(MainGrid);

	std::vector<wxString> headers;
	headers.push_back(("Title"));
	headers.push_back(("Author"));
	headers.push_back(("Subreddit"));
	table->set_headers(headers);

	table->Update();

	reddit_get_posts_hot(reddit, -1, NULL, adder, table);

    table->Update();

    LoadSubs();
}

void MainFrameCust::MainFrameOnActivate( wxActivateEvent& event ) {
	printf("OK!\n");
}

void MainFrameCust::SubBoxOnCombobox(wxCommandEvent &event) {
    int i = SubBox->GetSelection();

    table->Clear();

    if(i == 0){
        reddit_get_posts_hot(reddit, -1, NULL, adder, table);

    }else {
        Subreddit_t* sub = (Subreddit_t*) subs->data[i-1];

        subreddit_get_posts(reddit, sub, "hot", -1, NULL, adder, table);
    }

    table->Update();
}

void MainFrameCust::LoadSubs() {
    subs = reddit_get_subbed_list(reddit);

    for(int i=0 ; i<subs->length ; i++) {
        Subreddit_t* sub = (Subreddit_t *) subs->data[i];

        SubBox->Append(sub->name);
    }
}

void MainFrameCust::MoreButtonOnButtonClick(wxCommandEvent &event) {
    Post_t* prev = table->Tail();

    int i = SubBox->GetSelection();

    const char* fullname = post_fullname(prev);

    if(i == 0 || i == -1){
        reddit_get_posts_hot(reddit, -1, fullname, adder, table);

    }else {
        Subreddit_t* sub = (Subreddit_t*) subs->data[i-1];

        subreddit_get_posts(reddit, sub, "hot", -1, fullname, adder, table);
    }

    table->Update();
}
