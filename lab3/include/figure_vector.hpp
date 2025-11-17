#pragma once

#include <cstddef>

#include "figure.hpp"
#include "trapezoid.hpp"
#include "rhombus.hpp"
#include "pentagon.hpp"


class FigureVector {
private:
    Figure** m_data;
    size_t m_size;
    size_t m_capacity;
public:
    //The rule of five + constructor
    FigureVector();
    FigureVector(const FigureVector& other);
    FigureVector(FigureVector&& other) noexcept;
    FigureVector& operator=(const FigureVector& other);
    FigureVector& operator=(FigureVector&& other) noexcept;
    ~FigureVector() noexcept;
    
    FigureVector(size_t size);

    size_t getCapacity() const;
    size_t getSize() const;
    Figure& get_link() const;

    Figure& takeByIndex(size_t index);
    const Figure& takeByIndex(size_t index) const;

    void upSize();
    void downSize();
    bool empty() const;
    void clear();

    Figure& back();
    const Figure& back() const;
    Figure& front();
    const Figure& front() const;
    void push_back(Figure& object);
    void pop_back();

    void figureInfo(size_t index);
    double totalArea();
};