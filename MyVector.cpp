#include "MyVector.h"

template<class T>
MyVector<T>::MyVector(size_t size, ResizeStrategy strategy, float coef) {
    _size = size;
    _strategy = strategy;
    _coef = coef;
    strategyExpand(_strategy, _coef);
    _data = new T[_capacity];
    for(size_t i = 0; i < _size; ++i) {
	_data[i] = T();
    }
}

template<class T>
MyVector<T>::MyVector(size_t size, T value, ResizeStrategy strategy, float coef) {
    _size = size;
    _strategy = strategy;
    _coef = coef;
    strategyExpand(_strategy, _coef);
    _data = new T[_capacity];
    for(size_t i = 0; i < _size; ++i) {
	_data[i] = value;
    }
}

template<class T>
MyVector<T>::MyVector(const MyVector& copy) {
    _size = copy._size;
    _capacity = copy._capacity;
    _coef = copy._coef;
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = copy[i];
    }
}

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector& copy) {
    if (this != &copy) {
        MyVector tmp = MyVector(copy);
        std::swap(this->_data, tmp._data);
        std::swap(this->_capacity, tmp._capacity);
        std::swap(this->_size, tmp._size);
        std::swap(this->_coef, tmp._coef);
        std::swap(this->_strategy, tmp._strategy);
    }
    return *this;
}

template<class T>
MyVector<T>::MyVector(MyVector&& other) noexcept {
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _coef = other._coef;
    _strategy = other._strategy;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._coef = 1.5f;
    other._strategy = ResizeStrategy::Multiplicative;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        std::swap(this->_data, other._data);
        std::swap(this->_capacity, other._capacity);
        std::swap(this->_size, other._size);
        std::swap(this->_coef, other._coef);
        std::swap(this->_strategy, other._strategy);
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
        other._coef = 1.5f;
        other._strategy = ResizeStrategy::Multiplicative;
    }
    return *this;
}

template<class T>
MyVector<T>::~MyVector() {
    delete[] _data;
    _data = nullptr;
}

template<class T>
size_t MyVector<T>::capacity() const {
    return _capacity;
}

template<class T>
size_t MyVector<T>::size() const {
    return _size;
}

template<class T>
float MyVector<T>::loadFactor() const {
    return (float)_size / _capacity;
}

template<class T>
typename MyVector<T>::VectorIterator MyVector<T>::begin() {
    return MyVector<T>::VectorIterator(&_data[0]);

}

template<class T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::cbegin() const {
    return MyVector<T>::ConstVectorIterator(&_data[0]);

}

template<class T>
typename MyVector<T>::VectorIterator MyVector<T>::end() {
    return MyVector<T>::VectorIterator(&_data[_size]);

}

template<class T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::cend() const {
    return MyVector<T>::ConstVectorIterator(&_data[_size]);
}

template<class T>
T& MyVector<T>::operator[](const size_t idx) {
    if (idx >= _size) {
	throw std::out_of_range("Called [idx] : idx >= size of vector");
    }
    return _data[idx];

}

template<class T>
const T& MyVector<T>::operator[](const size_t idx) const {
    if (idx >= _size) {
	throw std::out_of_range("Called [idx] : idx >= size of vector");
    }
    return _data[idx];
}

template<class T>
void MyVector<T>::pushBack(const T& value) {
    insert(_size, value);
}

template<class T>
void MyVector<T>::pushFront(const T& value) {
    insert(0, value);
}

template<class T>
void MyVector<T>::insert(const size_t idx, const T& value) {
    if (idx >= _size) {
	throw std::out_of_range("Called insert(idx) : idx >= size of vector");
    }
    _size++;
    if (_size >= _capacity) {
        expand();
    }
    for (size_t i = _size; i > idx; i--) {
        _data[i] = _data[i - 1];
    }
    _data[idx] = value;
}

template<class T>
void MyVector<T>::insert(const size_t idx, const MyVector& value) {
    if (idx >= _size) {
	throw std::out_of_range("Called insert(idx) : idx >= size of vector");
    }
    _size += value._size;
    if (_size >= _capacity) {
        expand();
    }
    for (size_t i = _size; i > idx; i--) {
        _data[i] = _data[i - value._size];
    }
    for (size_t i = 0; i < value._size; i++) {
        _data[idx + i] = value._data[i];
    }
}

template<class T>
void MyVector<T>::insert(ConstVectorIterator it, const T& value) {
    size_t idx = 0;
    MyVector<T>::ConstVectorIterator tmp = cbegin(); 
    while ((tmp != cend()) || (tmp != it)) {
	idx++;
        tmp++;
    }
    insert(idx, value);
}

template<class T>
void MyVector<T>::insert(ConstVectorIterator it, const MyVector& value) {
    size_t idx = 0;
    MyVector<T>::ConstVectorIterator tmp = cbegin(); 
    while ((tmp != cend()) || (tmp != it)) {
	idx++;
        tmp++;
    }
    insert(idx, value);
}


template<class T>
void MyVector<T>::popBack() {
    _size--;
}

template<class T>
void MyVector<T>::erase(const size_t idx) {
    if (idx >= _size) {
	throw std::out_of_range("Called erase(idx) : idx >= size of vector");
    }
    for (size_t i = idx; i < _size; i++) {
        _data[i] = _data[i + 1];
    }
    _size--;
}

template<class T>
void MyVector<T>::erase(const size_t idx, const size_t len) {
    if (idx >= _size) {
	throw std::out_of_range("Called erase(idx) : idx >= size of vector");
    }
    if (idx + len >= _size) {
	throw std::out_of_range("Called erase(idx) : idx + len >= size of vector");
    }
    for (size_t i = idx; i < _size; i++) {
        _data[i] = _data[i + len];
    }
    _size -= len;

}

template<class T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::find(const T& value, bool isBegin) const {
    MyVector<T>::ConstVectorIterator it = cend();
    MyVector<T>::ConstVectorIterator tmp = cbegin();
    while (tmp != cend()) {
	if (*tmp == value) {
	    it = tmp;
	    if (isBegin == true) {
		break;
	    }
	}
    }
    return it;
}


template<class T>
void MyVector<T>::reserve(const size_t capacity) {
    T* newData = new T[capacity];
    for (size_t i = 0; i < _size; i++) {
        newData[i] = _data[i];
    }
    delete[] _data;
    _data = newData;
}

template<class T>
void MyVector<T>::resize(const size_t size, const T& value) {
    if (size > _size) {
        if (size > _capacity) {
            reserve(size);
            for(size_t i = _size; i < size; i++) {
                _data[i + 1] = value;
            }
        }
    }
    _size = size;
}

template<class T>
void MyVector<T>::expand() {
    while (loadFactor() > 0.8) {
        if (loadFactor() > 1.1) {
            strategyExpand(ResizeStrategy::Multiplicative, 1.5 * loadFactor());
        }
        else {
            strategyExpand(ResizeStrategy::Additive, 2 * abs(_capacity - _size));
        }
    }
    reserve(_capacity);
}

template<class T>
void MyVector<T>::strategyExpand(ResizeStrategy strategy, float coef) {
    if (strategy == ResizeStrategy::Additive) {
        _capacity = (_size + coef);
    }
    if (strategy == ResizeStrategy::Multiplicative) {
        _capacity = (_size * coef);
    }
}

template<class T>
void MyVector<T>::clear() {
    delete[] _data;
    _size = 0; 
    _data = new T[_capacity];
}
