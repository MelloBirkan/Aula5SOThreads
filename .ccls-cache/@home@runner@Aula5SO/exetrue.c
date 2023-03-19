#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void *minhathread(void *args){
  int valor = *((int *) args);
  sleep(0.5);
  printf("\nOlá thread %d", valor);
  return (NULL);
}
int main (){
  pthread_t threads[5];
  int vet_i[5];
  printf("Iniciando");
  for(int i=0;i<5;i++){
  vet_i[i] = i;
  pthread_create(&threads[i], NULL, minhathread, (void *)&vet_i[i]);
  }
  sleep(2);
  printf("Thread principal esperando as demais finalizarem \n");
  exit(0);
}
