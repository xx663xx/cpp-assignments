#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int josephus(int N, int k) {
    int winner = 0;
    for (int i = 2; i <= N; i++) {
        winner = (winner + k) % i;
    }
    return winner + 1;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int tests[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int k = 2;

    ofstream outFile("results.csv");
    outFile << "N,Result,Time" << endl;

    for (int i = 0; i < 7; i++) {
        int N = tests[i];
        clock_t start_time = clock();
        int result = josephus(N, k);
        clock_t end_time = clock();
        double elapsed = double(end_time - start_time) / CLOCKS_PER_SEC;
        outFile << N << "," << result << "," << elapsed << endl;
        cout << "N = " << N << " Результат: " << result << " Время: " << elapsed << endl;
    }

    outFile.close();

    return 0;
}