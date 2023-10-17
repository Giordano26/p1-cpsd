#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void dense_mat_vec(int m, int n, double *x, double *A, double *y) {
    #pragma omp parallel for
    for (int i = 0; i < m; i++) {
        double tmp = 0.0;

        #pragma omp parallel for reduction(+:tmp)
        for (int j = 0; j < n; j++) {
            tmp += A[i * n + j] * y[j];
        }

        x[i] = tmp;
    }
}

int main() {
    int m, n;

    //aceita os valores de m e n da linha de comando em tempo de exec
    printf("Digite o valor de m: ");
    scanf("%d", &m);

    printf("Digite o valor de n: ");
    scanf("%d", &n);

    //aloca a matriz A e os vetores de x e y
    double *A = (double *)malloc(m * n * sizeof(double));
    double *x = (double *)malloc(m * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));

    //inicializar A e y com alguns valores adequados
    #pragma omp parallel for
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i * n + j] = i + j;
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        y[i] = i + 1.57;
    }

    //chama a função dense_mat_vec com 4 threads
    #pragma omp parallel num_threads(4)
    dense_mat_vec(m, n, x, A, y);

    //imprimir os resultados de dense_mat_vec
    printf("Resultado:\n");
    for (int i = 0; i < m; i++) {
        printf("%.2f\n", x[i]);
    }

    //liberar espaço de memória
    free(A);
    free(x);
    free(y);

    return 0;
}
