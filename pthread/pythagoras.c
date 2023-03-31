#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
2 threads 
    square a, update c
    square b, update c
*/

typedef struct thread_args_t {
    double side;
    double *hyp;
    pthread_mutex_t *mutex;
} thread_args;


static void *square(void *arg) {
    thread_args *targs = (thread_args *) arg;
    sleep(1);
    pthread_mutex_lock(targs->mutex);
    float hyp = *(targs->hyp);
    hyp += (targs->side)*(targs->side);
    *targs->hyp = hyp;
    pthread_mutex_unlock(targs->mutex);
    printf("%f %f %f\n", targs->side,  (targs->side)*(targs->side), *targs->hyp);
    return NULL;
}


float pyth(float *lengths, int floats) {
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    double hyp=0;
    
    pthread_t threads[floats];
    thread_args targs[floats];
    for (int i=0; i<floats; i++) {
        targs[i].side = lengths[i];
        targs[i].hyp = &hyp;
        targs[i].mutex = &mutex;
        pthread_create(&(threads[i]), NULL, square, &targs[i]);
    }
    for (int i=0; i<floats; i++) {
        pthread_join(threads[i], NULL);
    } 
    hyp = sqrt(hyp);
    printf("%f^2\n", hyp);
    pthread_mutex_destroy(&mutex);
    return hyp;
}

int main(int argc, char **argv) {
    float l[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
    pyth(l, 12);
}
