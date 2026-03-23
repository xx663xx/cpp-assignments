#include "Array.h"

Array::Array(int startCapacity) {
    if (startCapacity <= 0)
        capacity = DEFAULT_CAPACITY;
    else
        capacity = startCapacity;

    ptr = new int[capacity];
    size = 0;
}

Array::Array(const Array& other) {
    capacity = other.capacity;
    size = other.size;
    ptr = new int[capacity];
    for (int i = 0; i < size; ++i) {
        ptr[i] = other.ptr[i];
    }
}

Array::~Array() {
    delete[] ptr;
}

Array& Array::operator=(const Array& other) {
    if (this == &other) {
        return *this;
    }

    if (capacity < other.size) {
        delete[] ptr;
        capacity = other.capacity;
        ptr = new int[capacity];
    }

    size = other.size;
    for (int i = 0; i < size; ++i) {
        ptr[i] = other.ptr[i];
    }

    return *this;
}

int& Array::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс массива вне диапазона");
    }
    return ptr[index];
}

const int& Array::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс массива вне диапазона");
    }
    return ptr[index];
}

void Array::insert(int elem, int index) {
    if (index == -1) {
        index = size;
    }

    if (index < 0 || index > size) {
        throw std::out_of_range("Индекс вставки вне диапазона");
    }

    if (size >= capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity);
    }

    for (int i = size; i > index; --i) {
        ptr[i] = ptr[i - 1];
    }

    ptr[index] = elem;
    ++size;
}

void Array::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс удаления вне диапазона");
    }

    for (int i = index; i < size - 1; ++i) {
        ptr[i] = ptr[i + 1];
    }

    --size;
}

void Array::resize(int newCapacity) {
    if (newCapacity < 0) {
        throw std::invalid_argument("Вместимость не может быть < 0");
    }

    if (newCapacity < size) {
        size = newCapacity;
    }

    int* newPtr = new int[newCapacity];
    for (int i = 0; i < size; ++i) {
        newPtr[i] = ptr[i];
    }

    delete[] ptr;
    ptr = newPtr;
    capacity = newCapacity;
}

std::ostream& operator<<(std::ostream& os, const Array& arr) {
    os << "[";
    for (int i = 0; i < arr.size; ++i) {
        os << arr.ptr[i];
        if (i < arr.size - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}