#include <iostream>
#include <fstream>
#include <ctime>
#include "linelist.h"

using namespace std;

int josephus(int N, int k) {
    LineList<int> list;

    for (int i = N; i >= 1; i--) {
        list.insertFirst(i);
    }

    int size = N;
    int position = 0;

    while (size > 1) {
        position = (position + k - 1) % size;

        if (position == 0) {
            list.deleteFirst();
        } else {
            LineListElem<int>* ptr = list.getStart();
            for (int i = 0; i < position - 1; i++) {
                ptr = ptr->getNext();
            }
            list.deleteAfter(ptr);
        }
        
        size--;
    }

    return list.getStart()->getData();
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
