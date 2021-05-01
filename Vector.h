#include "IVector.h"

class Vector: public IVector 
{
private:
    ValueType* _data ;
	size_t _size;

public:
	Vector(ValueType* data);

    ValueType& at(size_t idx) override;
    const ValueType& at(size_t idx) const override;
    ValueType& operator[](const size_t i) override;
    const ValueType& operator[](const size_t i) const override;

    void pushBack(const ValueType& value) override;
    void pushFront(const ValueType& value) override;
    void insert(const ValueType& value, size_t idx) override;
    
    void clear()override ;
    void erase(size_t i) override;
    void erase(size_t i, size_t len) override;
    void popBack() override;
    
    size_t size() const override;
    
    size_t find(const ValueType& value) const override;

    ~Vector() = default;
};