#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

int contador = 0;
pthread_mutex_t mutex_contador;

void *update(void *arg) {
  int nome = *(int *)arg;
  int valor = (nome + 1) * 10;
  printf("Thread %d: lendo o contador\n", nome);

  pthread_mutex_lock(&mutex_contador);
  contador += valor;
  pthread_mutex_unlock(&mutex_contador);

  printf("Thread %d: modificou o contador\n", nome);
  pthread_exit(NULL);
}

int main() {
  pthread_t threads[NUM_THREADS];
  int nomes[NUM_THREADS];
  int i;

  pthread_mutex_init(&mutex_contador, NULL);

  for (i = 0; i < NUM_THREADS; i++) {
    nomes[i] = i + 1;
    pthread_create(&threads[i], NULL, update, &nomes[i]);
  }

  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("Valor do contador: %d\n", contador);

  pthread_mutex_destroy(&mutex_contador);

  return 0;
}
