#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

#include "common.h"

typedef void* element_t;

typedef u8 (*comparator_t)(element_t, element_t);

typedef struct {
    element_t *array;
    u32 size;
    u32 max;
    comparator_t comparator;
} ordered_array_t;

u8 standard_comparator(element_t a, element_t b);

ordered_array_t create_ordered_array(u32 max, comparator_t comparator);

ordered_array_t place_ordered_array(void *addr, u32 max, comparator_t comparator);

// free array
void destory_ordered_array(ordered_array_t *array);

// add element to array
void insert_ordered_array(element_t element, ordered_array_t *array);

// get element from array at index i
element_t lookup_ordered_array(u32 i, ordered_array_t *array);

// delete the element at index i
void remove_ordered_array(u32 i, ordered_array_t *array);

#endif
