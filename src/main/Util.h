//
// Created by Rhys on 19/02/2022.
//

#ifndef MACTUBE_UTIL_H
#define MACTUBE_UTIL_H

#include <string>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

wxString toString(const char* in);

wxString toString(std::string in);

const char* toChars(wxString in);

const char* getTmpDir();

#endif //MACTUBE_UTIL_H
