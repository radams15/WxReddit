//
// Created by rhys on 24/10/2020.
//

#include <iostream>

#include "Table.h"

#include "Util.h"

using namespace std;

int Table::GetNumberRows() {
    return data.size();
}

int Table::GetNumberCols() {
    return headers.size();
}

bool Table::IsEmptyCell(int row, int col) {
    if(!Exists(row, col)){
        return true;
    }else{
        if(GetValue(row, col).empty()){
            return true;
        }
    }

    return false;
}

wxString Table::GetValue(int row, int col) {
    if(Exists(row, col)){
	Post_t* post = data.at(row);

	switch(col){
		case 0:
			return toString(post->title);
		case 1:
			return toString(post->author);
		case 2:
			return toString(post->subreddit);
	}
    }

    return toString("NONE");
}

wxString Table::GetColLabelValue(int col) {
    return headers.at(col);
}

void Table::SetValue(int row, int col, const wxString &value) {
    /*if(Exists(row, col)){
        data.at(row).at(col) = value;
    }*/
}

bool Table::Exists(int row, int col) {
    if(row >= GetNumberRows() || col >= GetNumberCols()){
        return false;
    }

    return true;
}

void Table::append(Post_t* to_add) {
	data.push_back(to_add);
}

void Table::set_headers(vector<wxString> new_headers) {
    headers = new_headers;
}

void Table::Clear() {
    data.clear();
}

Post_t* Table::Tail() {
    return data.at(data.size()-1);
}

Table::Table(wxGrid* grid) : wxGridTableBase(){
    this->grid = grid;
}

void Table::Update() {
    grid->SetTable(this);
}
