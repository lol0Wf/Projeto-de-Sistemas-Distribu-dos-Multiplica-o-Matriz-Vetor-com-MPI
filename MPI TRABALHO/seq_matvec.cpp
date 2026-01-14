#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

double timestamp() {
    return (double) clock() / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <N>\n";
        return 1;
    }

    int n = atoi(argv[1]);

    // usa memória contígua (igual ao MPI)
    vector<double> A(n * n);
    vector<double> x(n);
    vector<double> y(n);

    // inicializa
    for (int i = 0; i < n; i++) {
        x[i] = 1.0;
        for (int j = 0; j < n; j++) {
            A[i*n + j] = (i + j) % 10;
        }
    }

    double total = 0;
    for (int k = 0; k < 5; k++) {
        double start = timestamp();

        for (int i = 0; i < n; i++) {
            y[i] = 0.0;
            for (int j = 0; j < n; j++) {
                y[i] += A[i*n + j] * x[j];
            }
        }

        double end = timestamp();
        double t = end - start;
        total += t;

        cout << "Execução " << k+1 << ": " << t << " s\n";
    }

    cout << "Média: " << total / 5.0 << " s\n";

    return 0;
}
