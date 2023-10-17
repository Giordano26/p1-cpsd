#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Defina o tamanho do vetor
    int n = 6;
    int local_n = n / size;

    // Crie o vetor e inicialize valores (pode ser personalizado)
    double vetor[n];
    for (int i = 0; i < n; i++) {
        vetor[i] = i + 1.0;  // Usando double
    }

    // Distribua partes do vetor para cada processo
    double local_vetor[local_n];
    MPI_Scatter(vetor, local_n, MPI_DOUBLE, local_vetor, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Calcule a soma local
    double local_sum = 0.0;
    for (int i = 0; i < local_n; i++) {
        local_sum += local_vetor[i];
    }

    // Realize a redução de soma para obter a soma total
    double global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calcule a média global
    double media = global_sum / n;

    if (rank == 0) {
        printf("Média Aritmética: %.2f\n", media);
    }

    MPI_Finalize();
    return 0;
}
