//
// Created by Rhys on 24/07/2022.
//

#ifndef WXREDDIT_POSTFRAMECUST_H
#define WXREDDIT_POSTFRAMECUST_H

#include "MainFrame.h"

#include "Reddit.h"

class PostFrameCust : public PostFrame {
private:

public:
    PostFrameCust(wxFrame* parent);

    void AddComment(Comment* comment, wxTreeItemId);

    void AddPostMainComment(Comment* comment);

    void LoadPost(Post* post);

    wxTreeItemId comment_root;


};


#endif //WXREDDIT_POSTFRAMECUST_H
