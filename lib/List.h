//
// Created by Rhys on 13/03/2022.
//

#ifndef LIBREDDIT_LIST_H
#define LIBREDDIT_LIST_H

#include <defs.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef void(* freer_cb)(void*);

typedef struct List{
    void** data;
    size_t length;
    freer_cb freer;
#ifdef PRIVATE
    size_t elem_size;
#endif
} List_t;

List_t* list_new(size_t elem_size, freer_cb freer);

void list_append(List_t *lst, void* data);

void list_free(List_t* lst);

#define LIST(type, freer) list_new(sizeof(type), freer)

#define LIST_FREE(lst, type) for(size_t i=0 ; i<lst->length ; i++){ lst->freer((type *)lst->data[i]); }

#ifdef __cplusplus
}
#endif

#endif //LIBREDDIT_LIST_H
