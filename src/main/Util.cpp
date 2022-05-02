//
// Created by Rhys on 19/02/2022.
//

#include "Util.h"

#include <iostream>

#ifdef __UNIX__
#include <unistd.h>
#elif WIN32
#include <windows.h>
#endif

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

const char* toChars(wxString in){
    return in.mb_str();
}

const char* getTmpDir(){
#ifdef __UNIX__
    mkdir("/tmp/wxreddit/", 0755);

    return "/tmp/wxreddit/";
#elif WIN32
    char* out = (char*) calloc(255, sizeof(char));

    GetTempPathA(255, (LPSTR) out);

    return out;
#endif
}