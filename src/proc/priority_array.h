#ifndef PRIORITY_ARRAY
#define PRIORITY_ARRAY

typedef void* type_t;
typedef u_int8_t (*comparator)(type_t, type_t);
typedef struct{
    type_t *datas;
    u_int32_t size;
    u_int32_t max;
    comparator compare;
} array_t;

u_int8_t default_comparator(type_t a, type_t b){
    return a < b ? 1 : 0;
}


array_t* init_array(u_int32_t max, comparator comparator);

void destory_array(array_t *array);

void array_insert(type_t item, array_t *array);

type_t array_get(u_int32_t i, array_t *array);

void array_remove(u_int32_t i, array_t *array);
#endif
