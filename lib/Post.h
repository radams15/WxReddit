//
// Created by Rhys on 13/03/2022.
//

#ifndef LIBREDDIT_POST_H
#define LIBREDDIT_POST_H

#include <defs.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct Post{
    const char* title;
    const char* author;
    const char* subreddit;
    const char* text;
    size_t upvotes;
    size_t downvotes;
    size_t score;
    const char* id;
#ifdef PRIVATE
    const char* type;
#endif
} Post_t;

typedef void (*post_cb)(Post_t*, void*);

const char* post_fullname(Post_t* post);
const char* post_url(Post_t* post);

#ifdef __cplusplus
}
#endif

#endif //LIBREDDIT_POST_H
