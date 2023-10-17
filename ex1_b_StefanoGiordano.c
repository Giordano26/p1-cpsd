#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int x, soma = 0, subtracao = 0, mult = 1, TAM = 10;
    int vet[TAM];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    //limita o programa a rodar apenas a 4 processos p/ logica funcionar
    // -np 4
    if (size != 4) {
        printf("Este programa deve ser executado com 4 processos.\n");
        MPI_Finalize();
        return 1;
    }

    //inicializa o vetor no processo raiz (rank 0)
    if (rank == 0) {
        for (x = 0; x < TAM; x++) {
            vet[x] = x + 1;
        }
    }

    //faz o broadcast do vetor para todos os processos
    MPI_Bcast(vet, TAM, MPI_INT, 0, MPI_COMM_WORLD);


    //p1 -> soma, p2 -> sub, p3-> mult
    if (rank == 1) {
        printf("Sou o processo %d e estou realizando a soma...\n", rank);
        for (x = 0; x < TAM; x++) {
            soma += vet[x];
        }
    } else if (rank == 2) {
        printf("Sou o processo %d e estou realizando a subtração...\n", rank);
        for (x = 0; x < TAM; x++) {
            subtracao -= vet[x];
        }
    } else if (rank == 3) {
        printf("Sou o processo %d e estou realizando a multiplicação...\n", rank);
        for (x = 0; x < TAM; x++) {
            mult *= vet[x];
        }
    }

    //faz o reduce e armazena em cada parte do vetor de resultados
    //os respectivos resultados dos processos
    int results[3];

    MPI_Reduce(&soma, &results[0], 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&subtracao, &results[1], 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&mult, &results[2], 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    //volta para o processo raiz imprimir os resultados
    if (rank == 0) {
        printf("Soma = %d\n", results[0]);
        printf("Subtracao = %d\n", results[1]);
        printf("Multiplicacao = %d\n", results[2]);
    }

    MPI_Finalize();
    return 0;
}
