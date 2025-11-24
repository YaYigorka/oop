#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>


template<typename T>
class Array {
private:
    std::shared_ptr<T>[] m_data;
    size_t m_size;
    size_t m_capacity;
public:
    Array();
    Array(size_t size);

    Array(const Array<T>& other);
    Array(Array<T>&& other) noexcept;
    Array<T>& operator=(const Array<T>& other);
    Array<T>& operator=(Array<T>&& other) noexcept;
    ~Array() noexcept;

    size_t getCapacity() const { return m_capacity; }
    size_t getSize() const { return m_size; }

    T& takeByIndex(size_t index);
    const T& takeByIndex(size_t index) const;

    void resize(size_t new_capacity);
    bool empty() const { return m_size == 0; }
    void clear();

    T& back();
    const T& back() const;
    T& front();
    const T& front() const;
    void push_back(const T& object);
    void pop_back();
};


#include "array.ipp"
