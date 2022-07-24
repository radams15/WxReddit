//
// Created by rhys on 22/01/2022.
//

#ifndef YOUTUBECLI_MAINAPP_H
#define YOUTUBECLI_MAINAPP_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Reddit.h"

#include "Client.h"

class MainApp : public wxApp {
private:
	Client client;

public:
    virtual bool OnInit();

	MainApp();
};


#endif //YOUTUBECLI_MAINAPP_H
