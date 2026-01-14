#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0)
            cout << "Uso: mpirun -np <p> " << argv[0] << " <N>\n";
        MPI_Finalize();
        return 1;
    }

    int n = atoi(argv[1]);

    // Distribuição das linhas (N pode NÃO ser múltiplo de p)
    int rows = n / size;
    int remainder = n % size;

    // Processos iniciais recebem 1 linha extra
    int my_rows = rows + (rank < remainder ? 1 : 0);

    // Offset da parte de cada processo
    int start_row = rank * rows + min(rank, remainder);

    vector<double> x(n);
    vector<double> local_A(my_rows * n);
    vector<double> local_y(my_rows);

    vector<double> A;
    vector<int> sendcounts(size), displs(size);
    vector<int> recvcounts(size), rdispls(size);

    if (rank == 0) {
        // alocar matriz inteira só no rank 0
        A.resize(n * n);

        // inicialização
        for (int i = 0; i < n; i++) {
            x[i] = 1.0;
            for (int j = 0; j < n; j++)
                A[i*n + j] = (i + j) % 10;
        }

        // preparar scatterv/gatherv
        int offset = 0;
        for (int p = 0; p < size; p++) {
            int r = rows + (p < remainder ? 1 : 0);

            sendcounts[p] = r * n;
            displs[p] = offset;

            recvcounts[p] = r;
            rdispls[p] = offset / n;

            offset += r * n;
        }
    }

    // enviar vetor x completo
    MPI_Bcast(x.data(), n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // scatter distribuindo tamanhos diferentes
    MPI_Scatterv(rank == 0 ? A.data() : nullptr, sendcounts.data(), displs.data(),
                 MPI_DOUBLE, local_A.data(), my_rows*n,
                 MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double total_time = 0;

    for (int k = 0; k < 5; k++) {
        double start = MPI_Wtime();

        // cálculo local
        for (int i = 0; i < my_rows; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++)
                sum += local_A[i*n + j] * x[j];
            local_y[i] = sum;
        }

        double end = MPI_Wtime();
        total_time += (end - start);

        if (rank == 0)
            cout << "Execução " << k+1 << ": " << (end - start) << " s\n";
    }

    if (rank == 0)
        cout << "Média final p=" << size << ": " << total_time / 5.0 << " s\n";

    MPI_Finalize();
    return 0;
}
