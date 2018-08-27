#include <stdio.h>
#include <stdlib.h>

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

void remove_data(list_t *list, int index);

void add_data(list_t *list, void *data);


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


void add_data(list_t *list, void* data){
    list_node_t *temp = list->head;
    list_node_t *r = (list_node_t*)malloc(sizeof(list_node_t));
    r->data = data;
    if(NULL == temp){
        list->head = list->tail = r;
    }else{
        list->tail->next = r;
        r->prev = list->tail;
        list->tail = r;
    }
    list->size++;
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
        printf("list is empty");
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

void main(){
    list_t *list = init_list();
    list_print(list);

    add_data(list, 3);
    add_data(list, 2);
    add_data(list, 1);
    list_print(list);

    remove_data(list, 1);
    list_print(list);

    remove_data(list, 0);
    remove_data(list, 1);

//    remove_data(list, 0);
    list_print(list);
}
