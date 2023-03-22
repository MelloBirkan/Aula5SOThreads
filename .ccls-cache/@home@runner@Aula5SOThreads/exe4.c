#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

int contador = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *update(void *args) {
    int *input = (int *)args;
    int nome = input[0];
    int valor = input[1];
    int contador_local;
    struct timeval now;
    char buffer[30];
    struct tm *tm_info;

    gettimeofday(&now, NULL);
    tm_info = localtime(&now.tv_sec);
    strftime(buffer, 30, "%H:%M:%S", tm_info);
    printf("%s - Thread %d: lendo o contador\n", buffer, nome);

    pthread_mutex_lock(&mutex);
    contador_local = contador;
    contador_local += valor;
    sleep(1);
    contador = contador_local;
    pthread_mutex_unlock(&mutex);

    gettimeofday(&now, NULL);
    tm_info = localtime(&now.tv_sec);
    strftime(buffer, 30, "%H:%M:%S", tm_info);
    printf("%s - Thread %d: modificou o contador\n", buffer, nome);

    return NULL;
}

int main() {
    pthread_t threads[5];
    int i, args[5][2] = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};

    for (i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, update, (void *)&args[i]);
    }

    for (i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    sleep(3);
    printf("Valor do contador: %d\n", contador);
    return 0;
}
