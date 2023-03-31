#include <stdint.h>

typedef struct node_t {
    struct node_t *next;
    struct node_t *prev;
    void *data;
} node;

typedef struct list_t {
    uint32_t count;
    node *head;
    node *tail;
    void (*free_fn)(void *);
} list;

list *lnew(void (*free_fn)(void *));
void ldel(list* l);

/************************************************
* If pos >= count, insert at end
************************************************/
node *ladd(list *l, void* data, uint32_t pos);

/************************************************
* Removes first matching node. ToDo:  rremove 
************************************************/
void lremove(list *l, void* data);

/************************************************
* If pos > count, delete end
************************************************/
void lremove_at(list *l, uint32_t pos);
node *lget(list *l, uint32_t pos);
void lprint(list *l);

#define END 0xffffffff
#define free_data(x) {if (l->free_fn) l->free_fn(x);}
