#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Definindo constantes para o número de cadeiras e clientes
#define NUM_CADEIRAS 10
#define NUM_CLIENTES 15

int cadeiras[NUM_CADEIRAS]; // Array para armazenar as cadeiras disponíveis
int num_cadeiras;           // Variável para controlar o número de cadeiras disponíveis
pthread_mutex_t lock;       // Mutex para controlar o acesso às cadeiras

// Função a ser executada pelas threads para simular a compra de cadeiras pelos clientes
void *comprar_cadeira(void *cliente_id) {
    int id = *((int *)cliente_id);
    int tempo_gasto = rand() % 9 + 1; // Gera um tempo aleatório entre 1 e 9 segundos
    sleep(tempo_gasto);              // Simula o tempo gasto pelo cliente no guichê

    pthread_mutex_lock(&lock); // Bloqueia o acesso às cadeiras

    // Verifica se há cadeiras disponíveis e realiza a compra
    if (num_cadeiras > 0) {
        int cadeira_comprada = cadeiras[num_cadeiras - 1];
        num_cadeiras -= 1;
        printf("Cliente %d comprou a cadeira %d\n", id, cadeira_comprada);
    } else {
        printf("Cliente %d ficou sem cadeira\n", id);
    }

    pthread_mutex_unlock(&lock); // Libera o acesso às cadeiras

    return NULL;
}

int main() {
    // Executa a simulação 5 vezes
    for (int execucao = 0; execucao < 5; execucao++) {
        printf("Execucao %d:\n", execucao + 1);

        // Inicializa as variáveis e prepara as cadeiras
        num_cadeiras = NUM_CADEIRAS;
        for (int i = 0; i < num_cadeiras; i++) {
            cadeiras[i] = i + 1;
        }

        pthread_t clientes[NUM_CLIENTES]; // Array para armazenar as threads dos clientes
        int id_clientes[NUM_CLIENTES];    // Array para armazenar os IDs dos clientes

        pthread_mutex_init(&lock, NULL); // Inicializa o mutex

        // Cria e inicia as threads dos clientes
        for (int i = 0; i < NUM_CLIENTES; i++) {
            id_clientes[i] = i + 1;
            pthread_create(&clientes[i], NULL, comprar_cadeira, (void *)&id_clientes[i]);
        }

        // Aguarda a conclusão de todas as threads dos clientes
        for (int i = 0; i < NUM_CLIENTES; i++) {
            pthread_join(clientes[i], NULL);
        }

        pthread_mutex_destroy(&lock); // Destroi o mutex

        printf("\n");
    }

    return 0;
}
