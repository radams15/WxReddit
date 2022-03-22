//
// Created by rhys on 22/01/2022.
//

#include "MainApp.h"
#include "MainFrameCust.h"

MainApp::MainApp(Reddit_t* reddit) : wxApp(){
	this->reddit = reddit;
}

bool MainApp::OnInit() {
    MainFrameCust *frame = new MainFrameCust(reddit, NULL);
    frame->Show(true);

    return true;
}
