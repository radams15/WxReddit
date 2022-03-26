//
// Created by rhys on 22/01/2022.
//

#include "MainApp.h"
#include "MainFrameCust.h"

extern "C" void gtk_tweak_setup();

MainApp::MainApp(Reddit_t* reddit) : wxApp(){
	this->reddit = reddit;
}

bool MainApp::OnInit() {
    gtk_tweak_setup();

    MainFrameCust *frame = new MainFrameCust(reddit, NULL);
    frame->Show(true);

    return true;
}
