#include <cstddef>

using ValueType = double;

class IVector
{
public:
    virtual ValueType& at(size_t idx) = 0;
    virtual const ValueType& at(size_t idx) const = 0;
    virtual ValueType& operator[](const size_t i) = 0;
    virtual const ValueType& operator[](const size_t i) const = 0;

    virtual void pushBack(const ValueType& value) = 0;
    virtual void pushFront(const ValueType& value) = 0;
    virtual void insert(const ValueType& value, size_t idx) = 0;
    
    virtual void clear() = 0;
    virtual void erase(size_t i) = 0;
    virtual void erase(size_t i, size_t len) = 0;
    virtual void popBack() = 0;
    
    virtual size_t size() const = 0;
    
    virtual size_t find(const ValueType& value) const = 0;

    virtual ~IVector() = default;
};