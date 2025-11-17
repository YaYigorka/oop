#pragma once

#include <cstddef>

#include "dot2D.hpp"


class CoordinatesVector {
private:
    Dot2D** m_data;
    size_t m_size;
    size_t m_capacity;
public:
    //The rule of five + constructor
    CoordinatesVector();
    CoordinatesVector(const CoordinatesVector& other);
    CoordinatesVector(CoordinatesVector&& other) noexcept;
    CoordinatesVector& operator=(const CoordinatesVector& other);
    CoordinatesVector& operator=(CoordinatesVector&& other) noexcept;
    ~CoordinatesVector() noexcept;
    
    CoordinatesVector(size_t size);

    size_t getCapacity() const;
    size_t getSize() const;
    Dot2D& get_link() const;

    Dot2D& takeByIndex(size_t index);
    const Dot2D& takeByIndex(size_t index) const;

    void upSize();
    void downSize();
    bool empty() const;
    void clear();

    Dot2D& back();
    const Dot2D& back() const;
    Dot2D& front();
    const Dot2D& front() const;
    void push_back(Dot2D& object);
    void pop_back();
};