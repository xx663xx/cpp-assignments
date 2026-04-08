#ifndef LINELIST_H
#define LINELIST_H

#include <iostream>
using namespace std;

class LineListException {};

template <class T>
class LineListElem {
private:
    T data;
    LineListElem* next;

public:
    LineListElem(const T& adata, LineListElem* anext);
    const T& getData() const;
    LineListElem* getNext();

    template <class U> friend class LineList;
};

template <class T>
class LineList {
private:
    LineListElem<T>* start;

    LineList(const LineList& list);
    LineList& operator=(const LineList& list);

public:
    LineList();
    ~LineList();

    LineListElem<T>* getStart() const;

    void insertFirst(const T& data);
    void deleteFirst();

    void insertAfter(LineListElem<T>* ptr, const T& data);
    void deleteAfter(LineListElem<T>* ptr);

    template <class U>
    friend ostream& operator<<(ostream& out, const LineList<U>& list);
};

template <class T>
LineListElem<T>::LineListElem(const T& adata, LineListElem* anext) {
    data = adata;
    next = anext;
}

template <class T>
const T& LineListElem<T>::getData() const {
    return data;
}

template <class T>
LineListElem<T>* LineListElem<T>::getNext() {
    return next;
}

template <class T>
LineList<T>::LineList() {
    start = nullptr;
}

template <class T>
LineList<T>::~LineList() {
    while (start) {
        deleteFirst();
    }
}

template <class T>
LineListElem<T>* LineList<T>::getStart() const {
    return start;
}

template <class T>
void LineList<T>::insertFirst(const T& data) {
    LineListElem<T>* second = start;
    start = new LineListElem<T>(data, second);
}

template <class T>
void LineList<T>::deleteFirst() {
    if (start) {
        LineListElem<T>* temp = start->next;
        delete start;
        start = temp;
    } else {
        throw LineListException();
    }
}

template <class T>
void LineList<T>::insertAfter(LineListElem<T>* ptr, const T& data) {
    if (ptr) {
        LineListElem<T>* temp = ptr->next;
        ptr->next = new LineListElem<T>(data, temp);
    } else {
        throw LineListException();
    }
}

template <class T>
void LineList<T>::deleteAfter(LineListElem<T>* ptr) {
    if (ptr && ptr->next) {
        LineListElem<T>* temp = ptr->next;
        ptr->next = ptr->next->next;
        delete temp;
    } else {
        throw LineListException();
    }
}

template <class T>
ostream& operator<<(ostream& out, const LineList<T>& list) {
    LineListElem<T>* ptr = list.start;
    if (!ptr) {
        out << "EMPTY";
    } else {
        while (ptr) {
            out << ptr->getData();
            if (ptr->getNext()) out << " ";
            ptr = ptr->getNext();
        }
    }
    return out;
}

#endif