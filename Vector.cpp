#include "Vector.h"

Vector::Vector(size_t size, ValueType value) {
    _data = new ValueType[size];
    for (int i = 0; i < size; i++) {
        _data[i] = value;
    }
    _capacity = _size = size;
}


ValueType& Vector::at(size_t idx) {
    return _data[idx];
}

const ValueType& Vector::at(size_t idx) const {
    return _data[idx];
}

ValueType& Vector::operator[](const size_t i) {
    return at(i);
}

const ValueType& Vector::operator[](const size_t i) const {
    return at(i);
}


void Vector::pushBack(const ValueType& value) {
    _data[_size + 1] = value;
}

void Vector::pushFront(const ValueType& value) {
    _size++;
    _data[_size];
    for(int i = 1; i < _size; i++) {
        _data[i] = _data[i - 1];
    }
    _data[0] = value;
}

void Vector::insert(const ValueType& value, size_t idx) {
    _size++;
    _data[_size];
    for (int i = idx + 1; i < _size; i++) {
        _data[i] = _data[i - 1];
    }
    _data[idx] = value;
}


void Vector::clear() {
    _data = nullptr;
    _size = 0;
}

void Vector::erase(size_t i) {
    for (int j = i; j < _size - i - 1; j++) {
        _data[j] = _data[j + 1]; 
    }
    _data[_size] = 0;
    _size--;
}

void Vector::erase(size_t i, size_t len) {
    for (int j = i; j < _size - len - 1; j++) {
        _data[j] = _data[j + 1];
    }
    _size -= len;
    for (int j = _size; j < _size + len; j++) {
        _data[j] = 0;
    }
}

void Vector::popBack() {
    _data[_size] = 0;
    _size--;
}


size_t Vector::size() const {
    return _size;
}


size_t Vector::find(const ValueType& value) const {
    int i = 0;
    while (_data[i] != value) {
        i++;
    }
    return i;
}


Vector::~Vector() {
    _size = 0;
    _data = nullptr;
}
