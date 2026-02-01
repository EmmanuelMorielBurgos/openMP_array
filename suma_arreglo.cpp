#include <iostream>
#include <omp.h>
#include <vector>

void printArray(const std::vector<float>& arr, int show = 10)
{
    for (int i = 0; i < show && i < arr.size(); i++)
        std::cout << arr[i] << " - ";
    std::cout << std::endl;
}

int main()
{
    // ===== Configuracion =====
    int N = 100;            // Tamano arreglo
    int chunk_size = 10;    // Elementos por hilo
    int num_threads = 4;    // Cantidad de hilos
    

    std::vector<float> a(N), b(N), c(N);

    for (int i = 0; i < N; i++)
    {
        a[i] = i * 1.0f;
        b[i] = (i + 1) * 2.0f;
    }

    omp_set_num_threads(num_threads);

    std::cout << "Parallel array sum using OpenMP\n";
    std::cout << "Array size: " << N << "\n";
    std::cout << "Chunk size: " << chunk_size << "\n";
    std::cout << "Threads: " << num_threads << "\n\n";

    #pragma omp parallel for schedule(static, chunk_size)
    for (int i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i];

        #pragma omp critical
        {
            std::cout << "Thread "
                      << omp_get_thread_num()
                      << " processed index "
                      << i
                      << std::endl;
        }
    }

    std::cout << "\nFirst values of array A:\n";
    printArray(a);

    std::cout << "First values of array B:\n";
    printArray(b);

    std::cout << "First values of array C (sum):\n";
    printArray(c);

    return 0;
}
