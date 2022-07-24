//
// Created by Rhys on 24/07/2022.
//

#include "PostFrameCust.h"

#include "Util.h"

PostFrameCust::PostFrameCust(wxFrame* parent) : PostFrame(parent){
    comment_root = NULL;
}

void PostFrameCust::AddComment(Comment *comment, wxTreeItemId parent) {
    if(parent){
        wxTreeItemId id = CommentControl->AppendItem(parent, toString(comment->body));

        for(int i=0 ; i<comment->children.size() ; i++){
            AddComment(comment->children.at(i), id);
        }
    }
}

void PostFrameCust::AddPostMainComment(Comment *comment) {
    comment_root = CommentControl->AddRoot(toString(comment->title));

    /*if(! comment->thumbnail){
        return;
    }

    wxBitmap* bmp = GetBmp(comment->thumbnail);
    PostPic->SetBitmap(*bmp);*/

    CommentControl->Expand(comment_root);
}

void comment_adder(Comment* comment, void* ptr, int is_title){
    PostFrameCust* frame = (PostFrameCust*) ptr;

#ifdef USE_THREADING
    pthread_mutex_lock(&comment_mutex);
#endif

    if(is_title){
        frame->AddPostMainComment(comment);
    }else{
        frame->AddComment(comment, frame->comment_root);
    }

#ifdef USE_THREADING
    pthread_mutex_unlock(&comment_mutex);
#endif
}

void PostFrameCust::LoadPost(Post* post) {
    if(comment_root) {
        CommentControl->Delete(comment_root);
        comment_root = NULL;
    }

    std::string imgPath = post->get_image_path();

    if(imgPath.length() > 0){
        PostPic->SetBitmap(
                *GetBmp(
                        toString(
                                imgPath
                                ),
                                400, 600
                        )
        );
    }

    PostTitle->SetLabel(toString(post->title));
    PostContent->SetLabel(toString(post->text));

    post->get_comments(100, "", comment_adder, this);

    Layout();
}