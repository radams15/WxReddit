//
// Created by rhys on 22/01/2022.
//

#include "MainApp.h"
#include "MainFrameCust.h"

#include <iostream>

extern "C" void gtk_tweak_setup();

MainApp::MainApp() : wxApp(), client(){
    if(client.getReddit()->authenticated == Reddit::UNAUTHENTICATED){
        std::cerr << "Unable to login to Reddit!" << std::endl;
        exit(1);
    }
}

bool MainApp::OnInit() {
#ifdef __WXGTK3__
    gtk_tweak_setup();
#endif

    wxInitAllImageHandlers();

    MainFrameCust *frame = new MainFrameCust(client.getReddit(), NULL);
    frame->Show(true);

    return true;
}
