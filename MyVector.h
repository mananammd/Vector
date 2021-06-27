//#pragma once
#include <stdexcept>
#include <utility>
#include <iostream>
#include <iterator>
#include <cstddef>  

// стратегия изменения capacity
enum class ResizeStrategy {
    Additive,
    Multiplicative
};

// тип значений в векторе
// потом будет заменен на шаблон
//using ValueType = double;
template<class T>
class MyVector
{
public:
    // реализовать итераторы
    class VectorIterator
    {
    public:

        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;  
        using reference         = T&;  

        VectorIterator(T* ptr);
		VectorIterator(const VectorIterator& copy);
		VectorIterator operator=(const VectorIterator& copy);

        VectorIterator& operator++();
        VectorIterator operator++(int);
        VectorIterator& operator--();
        VectorIterator operator--(int);
        reference operator*() const;
        pointer operator->();
        bool operator!=(const VectorIterator& other) const;
		bool operator==(const VectorIterator& other) const;

    private:
        T* _ptr;
    };

    class ConstVectorIterator 
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = const T;
        using pointer           = const T*;  
        using reference         = const T&;  

        ConstVectorIterator(T* ptr);
		ConstVectorIterator(const ConstVectorIterator& copy);
		ConstVectorIterator operator=(const ConstVectorIterator& copy);

        ConstVectorIterator& operator++();
        ConstVectorIterator operator++(int);
        ConstVectorIterator& operator--();
        ConstVectorIterator operator--(int);
        reference operator*() const;
        pointer operator->();
        bool operator!=(const ConstVectorIterator& other) const;
		bool operator==(const ConstVectorIterator& other) const;

    private:
        T* _ptr;
    };

    // заполнить вектор значениями ValueType()
    MyVector(size_t size = 0, 
             ResizeStrategy = ResizeStrategy::Multiplicative, 
             float coef = 1.5f);
    // заполнить вектор значениями value
    MyVector(size_t size, 
             T value, 
             ResizeStrategy = ResizeStrategy::Multiplicative, 
             float coef = 1.5f);
    
    MyVector(const MyVector& copy);
    MyVector& operator=(const MyVector& copy);
    
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;
    ~MyVector();
    
    size_t capacity() const;
    size_t size() const;
    float loadFactor() const;
    
    VectorIterator begin();
    ConstVectorIterator cbegin() const;
    VectorIterator end();
    ConstVectorIterator cend() const;

    // доступ к элементу, 
    // должен работать за O(1)
    T& operator[](const size_t i);
    const T& operator[](const size_t i) const;
    
    // добавить в конец,
    // должен работать за amort(O(1))
    void pushBack(const T& value);
    void pushFront(const T& value);
    // вставить,
    // должен работать за O(n)
    void insert(const size_t i, const T& value);     // версия для одного значения
    void insert(const size_t i, const MyVector& value);      // версия для вектора
    void insert(ConstVectorIterator it, const T& value);  // версия для одного значения
    void insert(ConstVectorIterator it, const MyVector& value);   // версия для вектора
    
    // удалить с конца,
    // должен работать за amort(O(1))
    void popBack();
    // удалить
    // должен работать за O(n)
    void erase(const size_t i);
    void erase(const size_t i, const size_t len);            // удалить len элементов начиная с i
    
    // найти элемент,
    // должен работать за O(n)
    // если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
    // если искомого элемента нет, вернуть end
    ConstVectorIterator find(const T& value, bool isBegin = true) const;
    
    // зарезервировать память (принудительно задать capacity)
    void reserve(const size_t capacity);
    
    // изменить размер
    // если новый размер больше текущего, то новые элементы забиваются value
    // если меньше - обрезаем вектор
    void resize(const size_t size, const T& value = T());
    //Расширение _capacity
    void expand();
    void strategyExpand(ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
    // очистка вектора, без изменения capacity
    void clear();
private:
    T* _data;
    size_t _size;
    size_t _capacity;
    ResizeStrategy _strategy;
    float _coef;
};


template<class T>
MyVector<T>::VectorIterator::VectorIterator(T* ptr) {
    _ptr = ptr;
}

template<class T>
MyVector<T>::VectorIterator::VectorIterator(const VectorIterator& copy) {
    _ptr = copy._ptr;
}

template<class T>
typename MyVector<T>::VectorIterator MyVector<T>::VectorIterator::operator=(const VectorIterator& copy) {
    if (*this != copy) {
        _ptr = copy._ptr;
    }
    return *this;
}

template<class T>
typename MyVector<T>::VectorIterator& MyVector<T>::VectorIterator::operator++() {
    _ptr++; 
    return *this; 

}

template<class T>
typename MyVector<T>::VectorIterator MyVector<T>::VectorIterator::operator++(int) {
    VectorIterator tmp = *this;
    ++(*this);
    return tmp;
}

template<class T>
typename MyVector<T>::VectorIterator& MyVector<T>::VectorIterator::operator--() {
    _ptr--;
    return *this;
}

template<class T>
typename MyVector<T>::VectorIterator MyVector<T>::VectorIterator::operator--(int) {
    VectorIterator tmp = *this;
    --(*this);
    return tmp;
}

template<class T>
typename MyVector<T>::VectorIterator::reference MyVector<T>::VectorIterator::operator*() const {
    return *_ptr;
}

template<class T>
typename MyVector<T>::VectorIterator::pointer MyVector<T>::VectorIterator::operator->() {
    return _ptr;
}

template<class T>
bool MyVector<T>::VectorIterator::operator!=(const VectorIterator& other) const {
    return (_ptr != other._ptr);
}

template<class T>
bool MyVector<T>::VectorIterator::operator==(const VectorIterator& other) const {
    return (_ptr == other._ptr);
}



template<class T>
MyVector<T>::ConstVectorIterator::ConstVectorIterator(T* ptr) {
    _ptr = ptr;
}

template<class T>
MyVector<T>::ConstVectorIterator::ConstVectorIterator(const ConstVectorIterator& copy) {
    _ptr = copy._ptr;

}

template<class T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::ConstVectorIterator::operator=(const ConstVectorIterator& copy) {
    if (this != &copy) {
        _ptr = copy._ptr; 
    }
    return *this;
}

template<class T>
typename MyVector<T>::ConstVectorIterator& MyVector<T>::ConstVectorIterator::operator++() {
    _ptr++; 
    return *this; 

}

template<class T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::ConstVectorIterator::operator++(int) {
    ConstVectorIterator tmp = *this;
    ++(*this);
    return tmp;
}

template<class T>
typename MyVector<T>::ConstVectorIterator& MyVector<T>::ConstVectorIterator::operator--() {
    _ptr--;
    return *this;
}

template<class T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::ConstVectorIterator::operator--(int) {
    ConstVectorIterator tmp = *this;
    --(*this);
    return tmp;
}

template<class T>
typename MyVector<T>::ConstVectorIterator::reference MyVector<T>::ConstVectorIterator::operator*() const{
    return *_ptr;
}

template<class T>
typename MyVector<T>::ConstVectorIterator::pointer MyVector<T>::ConstVectorIterator::operator->() {
    return _ptr;
}

template<class T>
bool MyVector<T>::ConstVectorIterator::operator!=(const ConstVectorIterator& other) const {
    return (_ptr != other._ptr);
}

template<class T>
bool MyVector<T>::ConstVectorIterator::operator==(const ConstVectorIterator& other) const {
    return (_ptr == other._ptr);
}

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
    _strategy = copy._strategy;
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
        delete[] other._data;
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
    _size = 0;
    _capacity = 0;
    _coef = 0;
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
    if (idx > _size) {
		throw std::out_of_range("Called [idx] : idx > size of vector");
	}
	return _data[idx];

}

template<class T>
const T& MyVector<T>::operator[](const size_t idx) const {
    if (idx > _size) {
		throw std::out_of_range("Called [idx] : idx > size of vector");
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
    if (idx > _size) {
		throw std::out_of_range("Called insert(idx) : idx > size of vector");
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
    if (idx > _size) {
		throw std::out_of_range("Called insert(idx) : idx > size of vector");
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
    if (idx > _size) {
		throw std::out_of_range("Called erase(idx) : idx > size of vector");
	}
    for (size_t i = idx; i < _size; i++) {
        _data[i] = _data[i + 1];
    }
    _size--;
}

template<class T>
void MyVector<T>::erase(const size_t idx, const size_t len) {
    if (idx > _size) {
		throw std::out_of_range("Called erase(idx) : idx > size of vector");
	}
    if (idx + len > _size) {
		throw std::out_of_range("Called erase(idx) : idx + len > size of vector");
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