#include <stdlib.h>
#include <stdio.h>
#include "priority_array.h"


array_t* init_array(u_int32_t max, comparator comparator){
    array_t *array = malloc(sizeof(array_t));
    array->datas = malloc(sizeof(type_t)*max);
    array->max = max;
    array->compare = comparator;
    return array;
}

void destory_array(array_t *array){
    free(array->datas);
    free(array->compare);
    free(array);
}

void array_insert(type_t item, array_t *array){
    if(array->size == array->max){
        printf("max=%d, size=%d limit", array->max, array->size);
        return;
    }

    u_int32_t pos = 0;
    type_t *datas = array->datas;
    while((pos < array->size) && array->compare(datas[pos], item)){
        pos++;
    }
    if(pos == array->size){
        array->datas[array->size++] = item;
    }else{
        u_int32_t end = array->size;
        while(end > pos){
            array->datas[end] = array->datas[end-1];
            end--; 
        }
        array->datas[pos] = item;
        array->size++;
    }
}

type_t array_get(u_int32_t i, array_t *array){
    if(array->size == 0 || array->size <= i){
        printf("get failed, array->size=%d, i=%d", array->size, i);
        return -1;
    }
    u_int32_t itr = 0;
    while(itr < array->size){
        if(itr == i)
            return array->datas[itr];
        itr++;
    }

    return -1;
}

void array_remove(u_int32_t i, array_t *array){
    if(array->size == 0 || array->size <= i){
        printf("get failed, array->size=%d, i=%d", array->size, i);
        return;
    }       
    free(array->datas[i]);

    u_int32_t t = i;
    while(t < (array->size-1)){
        array->datas[t] = array->datas[t+1];
        t++;
    }
    array->datas[t] = 0;
    array->size--;
}


void main(){
    array_t *array = init_array(10, default_comparator);
    array_insert(5, array);
    array_insert(2, array);
    array_insert(7, array);
    array_insert(3, array);
    u_int32_t itr = 0;
    while(itr<array->size){
        printf("array[%d]=%d\r\n",itr, array->datas[itr]);
        itr++;
    }
}

