#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 5

void *thread_f(void *arg) {
    int id = *(int*) arg;
    printf("Thread %d: iniciada\n", id);
    sleep(5);
    printf("Thread %d: finalizada\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];
    int i;

    srand(time(NULL));

    for (i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_f, (void*) &ids[i])) {
            printf("Erro ao criar a thread %d.\n", i);
            exit(-1);
        }
    }

    printf("Programa principal finalizado.\n");

    pthread_exit(NULL);
}
