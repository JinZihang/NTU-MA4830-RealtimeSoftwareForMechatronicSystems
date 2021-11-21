#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int condition = 0, count = 0;

void consume() {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (condition == 0) pthread_cond_wait(&cond, &mutex);
        printf("Consumed %d\n", --count);

        condition = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
}

void *produce() {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (condition == 1) pthread_cond_wait(&cond, &mutex);
        printf("Produced %d\n", ++count);

        condition = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
}

int main(void) {
    pthread_create(NULL, NULL, &produce, NULL);
    return consume();
}