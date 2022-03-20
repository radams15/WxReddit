#include "MainFrame.h"

#include "Table.h"

#include "Reddit.h"

class MainFrameCust : public MainFrame{
private:

    void LoadSubs();

protected:
    void MainFrameOnActivate( wxActivateEvent& event );
    void SubBoxOnCombobox( wxCommandEvent& event );
    void MoreButtonOnButtonClick( wxCommandEvent& event );

    Table* table;
    Reddit_t* reddit;
    List_t* subs;


public:
		MainFrameCust( Reddit_t* reddit, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Reddit"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 790,549 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
};

