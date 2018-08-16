#include "ordered_array.h"
#include "common.h"
#include "mm.h"


u8 standard_comparator(element_t a, element_t b){
    return a < b? 1:0;
}

ordered_array_t create_ordered_array(u32 max, comparator_t comparator){
    ordered_array_t result;

    result.array = (void *)kmalloc(max*sizeof(element_t));
    memset(result.array, 0, max * sizeof(element_t));
    result.size = 0;
    result.max = max;
    result.comparator = comparator;
    return result;
}

ordered_array_t place_ordered_array(void *addr, u32 max, comparator_t comparator){
    ordered_array_t result;
    result.array = (void *)addr;
    memset(result.array, 0, max * sizeof(element_t));
    result.size = 0;
    result.max = max;
    result.comparator = comparator;
    return result;
}

void destory_ordered_array(ordered_array_t *array){
    // kfree
}

void insert_ordered_array(element_t element, ordered_array_t *array){
    u32 itr = 0;
    while(itr < array->size && array->comparator(array->array[itr], element)){
        itr++;
    }

    if(itr == array->size){
        array->array[array->size++] = element;
    }else{
        element_t temp = array->array[itr];
        array->array[itr] = element;
        while(itr < array->size){
            element_t v = array->array[itr];
            array->array[itr] = temp;
            temp = v;
            itr++;
        }
        array->size++;
    }
}


element_t lookup_ordered_array(u32 i, ordered_array_t *array){
    return array->array[i];
}

void remove_ordered_array(u32 i, ordered_array_t *array){
    while(i < array->size){
        array->array[i] = array->array[i+1];
        i++;
    }
    array->size--;
}

