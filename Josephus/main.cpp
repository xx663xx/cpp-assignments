#include <iostream>
#include <ctime>
#include <fstream>
#include "Array.h"

int josephus(Array& arr, int k) {
    int current = 0;
    while (arr.getSize() > 1) {
        current = (current + k - 1) % arr.getSize();
        arr.remove(current);
    }
    return arr[0];
}

int main() {
    setlocale(LC_ALL, "Russian");
    int k = 2;
    int testValues[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    std::ofstream file("results.csv");
    int size = sizeof(testValues) / sizeof(testValues[0]);

    file << "N,Result,Time\n";

    for (int t = 0; t < size; ++t) {
        int N = testValues[t];
        Array arr(N);
        for (int i = 1; i <= N; ++i) {
            arr.insert(i);
        }

        clock_t start = clock();
        int result = josephus(arr, k);
        clock_t end = clock();
        double elapsed = double(end - start) / CLOCKS_PER_SEC;

        std::cout << "N = " << N << std::endl;
        std::cout << "Результат: " << result << std::endl;
        std::cout << "Посчитано за " << elapsed << " секунд\n" << std::endl;
        file << N << "," << result << "," << elapsed << "\n";
    }
    file.close();
    return 0;
}