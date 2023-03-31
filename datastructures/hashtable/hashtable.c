#include <stdlib.h>
#include <sys/types.h>

static size_t _sizes[] = {
    5, 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717,
    51437, 102877, 205759, 411527, 823117, 1646237, 3292489, 6584983,
    13169977, 26339969, 52679969, 105359939, 210719881, 421439783,
    842879579, 1685759167, 0
}; 
#define SIZE(x) (_sizes[x])

/*
    [
        [0] -> [0, 10];
        [1] -> [0, 10]; 
        ...
    ]
*/
typedef struct bucket_t {
    void *bucket;
    size_t size;
} bucket;

typedef struct ht_t {
    bucket **buckets;
    size_t size;
} ht_t; 

/*
    Add
    Get
    Remove
    List
*/

ht_t *ht_create(size_t table_factor, size_t bucket_factor) {
    ht_t *ht = (ht_t *) calloc(1, sizeof(ht_t));
    ht->size = table_factor;
    ht->buckets = (bucket **) calloc(SIZE(table_factor), sizeof(bucket *));
    for (int i=0; i < SIZE(table_factor); i++) {
        bucket *b = (bucket *) calloc(SIZE(bucket_factor), sizeof(bucket));
        b->size = bucket_factor;
        b->bucket = (void **) calloc(1, sizeof(void *));
        ht->buckets[i] = b;
    }
    return ht;
}

