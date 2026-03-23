#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>

const int DEFAULT_CAPACITY = 10;

class Array {
private:
    int* ptr;
    int size;
    int capacity;

    void resize(int newCapacity);

public:
    explicit Array(int startCapacity = DEFAULT_CAPACITY);
    Array(const Array& other);
    ~Array();

    Array& operator=(const Array& other);

    int& operator[](int index);
    const int& operator[](int index) const;

    void insert(int elem, int index = -1);
    void remove(int index);

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }

    friend std::ostream& operator<<(std::ostream& os, const Array& arr);
};

#endif