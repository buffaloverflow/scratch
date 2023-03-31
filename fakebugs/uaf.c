/* Use after free bug example */

#include <stdint.h>
#include <stdio.h>

typedef struct node_t {
    struct node_t *prev;
    struct node_t *next;
    char           line[1024];
} node;

typedef struct list_t {
    node head;
    node tail;
    char name[255];
} list;




int main(int argc, char **argv) {
    char buf[1024]; 
    while (true) {
        
        fgets(buf, 1024, stdin);
    }
}
