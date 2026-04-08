#include <iostream>
#include "linelist.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    LineList<int> list;

    cout << "Начало: " << list << endl;

    list.insertFirst(10);
    cout << "После insertFirst(10): " << list << endl;

    LineListElem<int>* ptr = list.getStart();

    list.insertAfter(ptr, 15);
    cout << "После insertAfter(ptr, 15): " << list << endl;

    list.insertAfter(ptr->getNext(), 12);
    cout << "После insertAfter(ptr->getNext(), 12): " << list << endl;

    list.insertFirst(7);
    cout << "После insertFirst(7): " << list << endl;

    list.deleteFirst();
    cout << "После deleteFirst(): " << list << endl;

    ptr = list.getStart();
    list.deleteAfter(ptr);
    cout << "После deleteAfter(ptr): " << list << endl;

    cout << "\nПеребор элементов:" << endl;
    int sum = 0;
    int index = 0;

    for (LineListElem<int>* it = list.getStart(); it; it = it->getNext()) {
        cout << "Элемент " << index << ": " << it->getData() << endl;
        sum += it->getData();
        index++;
    }

    cout << "\nСумма элементов: " << sum << endl;

    return 0;
}