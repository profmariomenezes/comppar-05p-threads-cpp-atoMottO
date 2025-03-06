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
    double* A = new double[M * N];
    double* B = new double[N * X];
    double* C = new double[M * X];

    // Inicializa com números aleatórios
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
    
    // Zera a matriz C
    for (int i = 0; i < M * X; i++) {
        C[i] = 0.0;
    }

    int blockSize = 64;  // Tamanho do bloco – pode ser ajustado conforme a arquitetura

    auto start = high_resolution_clock::now();
    for (int i = 0; i < M; i += blockSize) {
        for (int j = 0; j < X; j += blockSize) {
            for (int k = 0; k < N; k += blockSize) {
                // Multiplica o bloco atual
                for (int ii = i; ii < i + blockSize && ii < M; ii++) {
                    for (int kk = k; kk < k + blockSize && kk < N; kk++) {
                        double a_val = A[ii * N + kk];
                        for (int jj = j; jj < j + blockSize && jj < X; jj++) {
                            C[ii * X + jj] += a_val * B[kk * X + jj];
                        }
                    }
                }
            }
        }
    }
    auto end = high_resolution_clock::now();
    duration<double> diff = end - start;
    cout << "Blocked multiplication time: " << diff.count() << " seconds" << endl;

    double total = 0.0;
    for (int i = 0; i < M * X; i++) total += C[i];
    cout << "Total: " << total << endl;

    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}
