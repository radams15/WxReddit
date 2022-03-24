//
// Created by Rhys on 13/03/2022.
//

#ifndef LIBREDDIT_REDDIT_H
#define LIBREDDIT_REDDIT_H

// https://www.reddit.com/dev/api/

#include <List.h>
#include <Post.h>
#include <Subreddit.h>
#include <Comment.h>

#ifdef __cplusplus
extern "C"{
#endif

#define AUTHENTICATED 1
#define UNAUTHENTICATED 0

typedef struct Reddit{
    const char* username;
    int authenticated;
#ifdef PRIVATE
    int use_proxy;
    const char* proxy;
    const char* client_id;
    const char* client_secret;
    const char* password;
    const char* token;
#endif
} Reddit_t;

Reddit_t* reddit_new(const char* username, const char* password, const char* client_id, const char* secret);
Reddit_t* reddit_new_with_token(const char *username, const char* token);

int reddit_get_posts_hot(Reddit_t* reddit, size_t limit, const char* after, post_cb callback, void* ptr);

List_t* reddit_get_subbed_list(Reddit_t* reddit);

int reddit_get_login_status(Reddit_t* reddit);

int subreddit_get_posts(Reddit_t* reddit, Subreddit_t* subreddit, const char* type, size_t limit, const char* after, post_cb callback, void* ptr);

int post_get_comments(Reddit_t* reddit, Post_t* post, size_t limit, const char* after, comment_cb callback, void* ptr);

#ifdef __cplusplus
}
#endif

#endif //LIBREDDIT_REDDIT_H
