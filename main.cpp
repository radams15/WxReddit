#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Reddit.h"

#include "MainApp.h"

#include "SECRETS.h"

int main(int argc, char** argv) {
	Reddit_t* reddit = reddit_new(USERNAME, PASSWD, CID, SECRET);
	//Reddit_t* reddit = reddit_new_with_token(USERNAME, "68425471-L7942dQX2B5WsKTNNa0r6NfcgYFtYQ");

    if(!reddit->authenticated){
        fprintf(stderr, "Failed to login!\n");
        exit(1);
    }
	
	wxApp::SetInstance( new MainApp(reddit) );
	wxEntryStart(argc, argv);
	wxTheApp->CallOnInit();
	wxTheApp->OnRun();

	return 0;
}
