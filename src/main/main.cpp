#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "MainApp.h"

int main(int argc, char** argv) {
	wxApp::SetInstance( new MainApp() );
	wxEntryStart(argc, argv);
	wxTheApp->CallOnInit();
	wxTheApp->OnRun();

	return 0;
}
