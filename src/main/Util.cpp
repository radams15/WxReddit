//
// Created by Rhys on 19/02/2022.
//

#include "Util.h"

#include <iostream>

wxString toString(const char* in){
    /*const wxChar* format = wxT("%s");
    wxString out = wxString::Format(L"%s", in);

    std::cout << in << " (" << format << ") " << " => " << out.c_str() << std::endl;

    return out;*/

    return wxString::FromUTF8(in);
}

wxString toString(std::string in){
    return toString(in.c_str());
}