#include <iostream>
#include <fstream>
#include <ctime>
#include "linelist.h"

using namespace std;

LineListElem<int>* getLast(LineList<int>& list) {
    LineListElem<int>* p = list.getStart();
    if (!p) {
        return nullptr;
    }

    while (p->getNext()) {
        p = p->getNext();
    }

    return p;
}

void goNext(LineList<int>& list, LineListElem<int>*& prev, LineListElem<int>*& cur, int step, int k) {
    if (step == k) {
        return;
    }

    prev = cur;
    cur = cur->getNext();
    if (!cur) {
        cur = list.getStart();
    }

    goNext(list, prev, cur, step + 1, k);
}

int josephus(int N, int k) {
    LineList<int> list;

    for (int i = N; i >= 1; i--) {
        list.insertFirst(i);
    }

    LineListElem<int>* cur = list.getStart();
    LineListElem<int>* prev = getLast(list);

    while (N > 1) {
        goNext(list, prev, cur, 1, k);

        if (cur == list.getStart()) {
            list.deleteFirst();
            cur = list.getStart();
        } else {
            list.deleteAfter(prev);
            cur = prev->getNext();
            if (!cur) {
                cur = list.getStart();
            }
        }

        N--;
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
