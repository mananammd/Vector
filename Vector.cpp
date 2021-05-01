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
    _size++;
    ValueType* newData = new ValueType[_size];
    for (int i = 0; i < _size - 1; i++) {
        newData[i] = _data[i];
    }
    newData[_size - 1] = value;
    delete _data;
    _data = newData;
}

void Vector::pushFront(const ValueType& value) {
    _size++;
    ValueType* newData = new ValueType[_size];
    for(int i = 1; i < _size; i++) {
        newData[i] = _data[i - 1];
    }
    newData[0] = value;
    delete[] _data;
    _data = newData;
}

void Vector::insert(const ValueType& value, size_t idx) {
    _size++;
    ValueType* newData = new ValueType[_size];
    for (int i = 0; i < idx; i++) {
        newData[i] = _data[i];
    }
    newData[idx] = value;
    for (int i = idx + 1; i < _size; i++) {
        newData[i] = _data[i-1];
    }
    delete[] _data;
    _data = newData;
}


void Vector::clear() {
    delete[] _data;
    _size = 0;
}

void Vector::erase(size_t i) {
    _size--;
    ValueType* newData = new ValueType[_size];
    for (int j = 0; j < i; j++) {
        newData[j] = _data[j]; 
    }
    for (int j = i + 1; j < _size + 1; j++) {
        newData[j - 1] = _data[j];
    }
    delete[] _data;
    _data = newData;
}

void Vector::erase(size_t i, size_t len) {
    _size -= len;
    ValueType* newData = new ValueType[_size];
    for (int j = 0; j < i; j++) {
        newData[j] = _data[j];
    }
    for (int j = i + len ; j < _size + len; j++) {
        newData[j - len] = _data[j];
    }
    delete[] _data;
    _data = newData;
}

void Vector::popBack() {
    _size--;
    ValueType* newData = new ValueType[_size];
    for (int i = 0; i < _size; i++) {
        newData[i] = _data[i];
    }
    delete[] _data;
    _data = newData;
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
    delete[] _data;
}
