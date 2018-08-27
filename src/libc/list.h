#ifndef LIST_H
#define LIST_H

typedef struct list_node{
    struct list_node *next;
    struct list_node *prev;
    void *data;
} list_node_t;

typedef struct list{
    struct list_node *head;
    struct list_node *tail;
    int size;
} list_t;

list_t* init_list();

void destory_list(list_t *origin);

int list_size(list_t *list);

void* list_get(list_t *list, int index);

void list_print(list_t *list);

void add_head(list_t *list, void *data);
void add_last(list_t *list, void *data);

void remove_data(list_t *list, int index);
void remove_head(list_t *list);
void remove_last(list_t *list);
#endif
