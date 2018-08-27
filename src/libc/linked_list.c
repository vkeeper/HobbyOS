#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list_t* init_list(){
    list_t *list = (list_t*)malloc(sizeof(list_t));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void destory_list(list_t *origin){
    list_node_t *node = NULL;
    while(NULL!=origin->head){
        node = origin->head->next;
        free(origin->head);
        origin->head = node;
    }
    free(origin);
}

int list_size(list_t *list){
    return list->size;
}

void remove_data(list_t *list, int index){
    list_node_t *temp = list->head;
    if(list->size == 0){
        printf("\r\nlist is empty, must not remove\r\n");
        return;
    }

    if(index >= list->size){
        printf("\r\nindex %d is valid, must less than size %d!\r\n", index, list->size);
        return;
    }

    int i = 0;
    while(NULL != temp){
        if(i == index){
            list_node_t *n = temp->next;
            list_node_t *p = temp->prev;
            if(p == NULL){
                list->head = n;
            }else{
                p->next = n;
            }

            if(n == NULL){
                list->tail = p;
            }else{
                n->prev = p;
            }
            list->size--;
            free(temp);
            break;
        }
        i++;
        temp = temp->next; 
    }

}


void* get(list_t *list, int index){
    if(list->head == NULL){
        printf("list is empty");
        return -1;
    }

    list_node_t *node = list->head;
    int i = 0;
    while(node!=NULL){
        if(index == i){
            return node->data;
        }
        node = node->next;
        i++;
    }
    printf("not found value");
    return -1;
}

void list_print(list_t *list){
    if(list->head == NULL){
        printf("\r\nlist is empty,print failed\r\n");
    }else{
        printf("\r\nlist->size=%d\r\n", list->size);
        list_node_t *node = list->head;
        while(node!=NULL){
            printf("%d, ", (int)node->data);
            node = node->next;
        }
        printf("\r\n");
    }
}

void add_head(list_t *list, void *data){
    list_node_t *node = (list_node_t*)malloc(sizeof(list_node_t));
    if(list->head == NULL){
        list->head = list->tail = node;
    }else{
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->size++;
}


void add_last(list_t *list, void *data){
    list_node_t *node = (list_node_t*)malloc(sizeof(list_node_t));
    node->data = data;
    if(list->head == NULL){
        list->head = list->tail = node;
    }else{
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

void remove_head(list_t *list){
    if(list->size == 0){
        printf("\r\nlist is empty, must not remove\r\n");
        return;
    }

    list_node_t *h = list->head;
    list_node_t *node = h->next;
    if(node == NULL){
        list->head = list->tail = NULL;
    }else{
        node->prev = NULL;
        list->head = node;
    }
    free(h);
    list->size--;
}

void remove_last(list_t *list){
    if(list->size == 0){
        printf("\r\nlist is empty, must not remove\r\n");
        return;
    }

    list_node_t *t = list->tail;
    list_node_t *node = t->prev;
    if(node == NULL){
        list->head = list->tail = NULL;
    }else{
        node->next = NULL;
        list->tail = node;
    }

    free(t);
    list->size--;
}

void main(){
    list_t *list = init_list();
    list_print(list);

    add_last(list, 3);
    add_last(list, 2);
    add_last(list, 1);
    list_print(list);

    remove_data(list, 1);
    list_print(list);

    remove_data(list, 0);
    remove_data(list, 1);

//    remove_data(list, 0);
    list_print(list);
}
