#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

void *thread_f(void *args) {
    int nome = *((int *)args);
    struct timeval now;
    char buffer[30];
    struct tm *tm_info;

    gettimeofday(&now, NULL);
    tm_info = localtime(&now.tv_sec);
    strftime(buffer, 30, "%H:%M:%S", tm_info);
    printf("%s - Thread %d: iniciada\n", buffer, nome);

    sleep(5);

    gettimeofday(&now, NULL);
    tm_info = localtime(&now.tv_sec);
    strftime(buffer, 30, "%H:%M:%S", tm_info);
    printf("%s - Thread %d: finalizada\n", buffer, nome);

    return NULL;
}

int main() {
    pthread_t threads[5];
    int i, ids[5];

    for (i = 0; i < 5; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, thread_f, (void *)&ids[i]);
    }

    for (i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Programa principal finalizado\n");
    return 0;
}
