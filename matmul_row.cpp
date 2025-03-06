#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

const int M = 512;  // Número de linhas de A e C
const int N = 512;  // Número de colunas de A e linhas de B
const int X = 512;  // Número de colunas de B e C

int main() {
    // Aloca as matrizes em blocos contíguos de memória
    double* A = new double[M * N];
    double* B = new double[N * X];
    double* C = new double[M * X];

    // Inicializa as matrizes com números aleatórios
    srand(static_cast<unsigned>(time(NULL)));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = rand() % 10;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < X; j++) {
            B[i * X + j] = rand() % 10;
        }
    }
    
    // Zera a matriz de resultado
    for (int i = 0; i < M * X; i++) {
        C[i] = 0.0;
    }

    // Multiplicação em ordem de linha
    auto start = high_resolution_clock::now();
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < X; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * X + j];
            }
            C[i * X + j] = sum;
        }
    }
    auto end = high_resolution_clock::now();
    duration<double> diff = end - start;
    cout << "Row order multiplication time: " << diff.count() << " seconds" << endl;

    // Evita que o compilador elimine o código (soma final dos elementos de C)
    double total = 0.0;
    for (int i = 0; i < M * X; i++) total += C[i];
    cout << "Total: " << total << endl;

    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}
