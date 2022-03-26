//
// Created by rhys on 24/10/2020.
//

#ifndef WXWIDGETS_TABLE_H
#define WXWIDGETS_TABLE_H


#include <wx/grid.h>

#include <vector>

#include "Post.h"

class Table : public wxGridTableBase{

private:
    std::vector< wxString > headers;
    std::vector< Post_t* > data;

    bool Exists(int row, int col);

    wxGrid* grid;

public:
    Table(wxGrid* grid);

    int GetNumberRows();

    void Clear();

    int GetNumberCols();

    bool IsEmptyCell(int row, int col);

    wxString GetValue(int row, int col);

    wxString GetColLabelValue(int col);

    Post_t* Tail();

    void SetValue(int row, int col, const wxString &value);

    void append(Post_t* to_add);

    void set_headers(std::vector<wxString> new_headers);

    void Update();
};


#endif //WXWIDGETS_TABLE_H
