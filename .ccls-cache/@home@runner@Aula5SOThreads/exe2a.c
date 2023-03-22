#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int n, i;
    pid_t pid;

    printf("Digite o número de processos filhos a serem criados: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Erro na criação do processo filho");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Processo filho
            printf("Filho com PID=%d criado\n", getpid());
            sleep(2);
            printf("Filho com PID=%d finalizado\n", getpid());
            exit(EXIT_SUCCESS);
        }
    }

    // Processo pai
    for (i = 0; i < n; i++) {
        wait(NULL);
    }
    printf("Pai finalizado\n");

    return 0;
}
