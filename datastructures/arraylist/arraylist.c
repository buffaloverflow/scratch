#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union container_t {
    uint64_t i;
    char s[7];
    void *data;
} container;


typedef struct list_t {
    container **array;
    uint32_t max;
    uint32_t size;
} list;

list *create() {
    list *l = (list *) calloc(1, sizeof(list));
    l->array = (container **) calloc(10, sizeof(container));
    l->max = 10;
    l->size = 0;
    return l;
}

void destroy(list *l) {
    free(l->array);
    memset(l, 0, sizeof(list));
    free(l);
}

void slide_right(list *l, uint32_t idx) { for (uint32_t i=l->size; i > idx; i--) l->array[i] = l->array[i-1]; }
void slide_left(list *l, uint32_t idx) { for (uint32_t i=idx; i < l->size; i++) l->array[i] = l->array[i+1]; }

void insert(list *l, container *c, uint32_t i) {
    if (i+1 >= l->size) { // Resize if only one spot left.
        l->array = (container **) reallocarray(l->array, l->max * 2, sizeof(container *));
        // if null, do not update max, set errno, but not really
        l->max *= 2;
    }
    
    if (i < l->size)
        slide_right(l, i);  //memmove(l->array+i+sizeof(container *)
                            //      , l->array+i
                            //      , (l->size-i) * sizeof(container *));
    l->array[i > l->size ? l->size : i] = c;
    l->size++;
    return;
}

container *get(list *l, uint32_t i) {
    if (i < l->size) {
        l->size--;
        return l->array[i];
    }
    return NULL;
}

container *del(list *l, uint32_t i) {
    container *c = get(l, i);
    slide_left(l, i);
    return c;
}

void add(list *l, container *c) { insert(l, c, 0); }
container *poll(list *l) { 
    container *c = get(l, 0);
    del(l, 0);
    return c;
}
void push(list *l, container *c) { insert(l, c, l->size); }
container *pop(list *l) {
    container *c = get(l, l->size-1); 
    del(l, l->size-1);
    return c;
}

void print_ints(list *l) {
    printf("[");
    for (int i=0; i < l->size; i++)
        printf("%ld, ", l->array[i]->i);
    printf("]\n");
}

int main(int argc, char **argv) {
    container c[9] = {
        {.i = 1},
        {.i = 2},
        {.i = 3},
        {.i = 4},
        {.i = 5},
        {.i = 6},
        {.i = 7},
        {.i = 8},
        {.i = 9},
    };


    //while (__AFL_LOOP(0xffff)) {
        for (int i=0; i<1024; i++) {
            list *l = create();
            int f = getc(stdin);
            if (f == EOF) break;
            if (f == '0') {
                insert(l, &c[getc(stdin)-0x30], getc(stdin)-0x30);
            } else if ( f == '1' ){
                del(l, getc(stdin)-0x30);
            } else {
                continue;
            }
            print_ints(l);
        }
    //}
}
