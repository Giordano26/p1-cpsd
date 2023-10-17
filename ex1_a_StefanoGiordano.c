#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_num_threads(4); //definir o numero de threads

    int x, soma = 0, sub = 0, mult = 1, TAM = 1000;
    int vet[TAM];

    //popular o vetor
    #pragma omp parallel for
    for (x = 0; x < 10; x++) {
        vet[x] = x + 1;
    }

    #pragma omp parallel for
    for (x = 0; x < 10; x++) {
        printf("vet[%d] = %d\n", x, vet[x]);
    }

    // Paralelizando as operações
    #pragma omp parallel for reduction(+:soma) reduction(-:sub) reduction(*:mult)
    for (x = 0; x < 10; x++) {
        soma = soma + vet[x];
        sub = sub - vet[x];
        mult = mult * vet[x];
    }

    // Imprimindo os resultados
    printf("Soma = %d\n", soma);
    printf("Subtracao = %d\n", sub);
    printf("Multiplicacao = %d\n", mult);

    return 0;
}
