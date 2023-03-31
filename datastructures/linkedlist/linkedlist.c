#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


list* lnew(void (*free_fn)(void *)) {
    list *l = (list *) calloc(1, sizeof(list));
    l->free_fn = free_fn;
    return l;
}


void ldel(list* l) {
    if (NULL == l) return;
    node *curr = l->head;
    while(curr) {
        node *next = curr->next;
        free_data(curr->data);
        free(curr);
        memset(curr, 0, sizeof(node));
        curr = next;
    }
}


node *ladd(list *l, void *data, uint32_t pos) {
    node* n = (node *) calloc(1, sizeof(node));
    n->data = data;
    l->count++;

    if (l->count == 1) {
        l->head = n;
        l->tail = n;
        return n;
    }

    if (l->count <= pos) {
        l->tail->next = n;
        n->prev = l->tail;
        l->tail = n;
        return n;
    }
    
    if (pos == 0) {
        n->next = l->head;
        l->head = n;
        return n;
    }
 
    node *curr = l->head;
    for (int i=1; i<pos && curr; i++)
        curr = curr->next;

    n->prev = curr;
    n->next = curr->next;
    curr->next = n;

    return n;
}


void lremove(list *l, void* data) {
    if (l->count == 0) return; 
    if (l->count == 1) {
        free_data(l->head->data);
        free(l->head);
        memset(l, 0, sizeof(list));
        return;
    }

    for (node *curr = l->head; curr; curr = curr->next) {
        if (curr->data == data) {
            l->count--;
            free_data(curr->data);

            if (curr == l->head) {
                l->head = l->head->next;
                l->head->prev = NULL;
                free(curr);
                return;
            }

            if (curr == l->tail) {
                l->tail = l->tail->prev;
                l->tail->next = NULL;
                free(curr);
                return;
            }

            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            free(curr);
        }
    }
}


void lremove_at(list *l, uint32_t pos) {
    if (l->count == 0) return; 
    l->count--;
    if (l->count+1 == 1) {
        free_data(l->head->data);
        free(l->head);
        memset(l, 0, sizeof(list));
        return;
    }
    
    if (pos == 0) {
        free_data(l->head->data);
        l->head = l->head->next;
        l->head->prev = NULL;
        return;
    }
        
    if (l->count+1 <= pos) {
        node *n = l->tail;
        free_data(l->tail->data);
        free(n);
        l->tail = l->tail->prev;
        l->tail->next = NULL;
        return;
    }

    node *curr = lget(l, pos);
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    free_data(curr->data);
    free(curr);
}

node *lget(list *l, uint32_t pos) {
    node *curr = l->head;
    for (int i=0; i<pos ; i++)
        curr = curr->next;
    return curr;
}

void lprint(list *l) {
    printf("[");
    for(node *n = l->head; n; n = n->next)
        printf("%p, ", n->data);
    printf("]\n");
}

int main(int argc, char** argv) {
    list *l = lnew(NULL);
    lprint(l);
    ladd(l, (void *)main, END);
    lprint(l);
    ladd(l, (void *)ladd, END);
    lprint(l);
    ladd(l, (void *)ladd, 0);
    lprint(l);
    ladd(l, (void *)lprint, 1);
    lprint(l);
    lremove_at(l, 1);
    lprint(l);
    lremove(l, (void *)ladd);
    lprint(l);
}
