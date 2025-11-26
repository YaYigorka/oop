#pragma once

#include <iostream>

#include "concepts.hpp"
#include "point.hpp"
#include "array.hpp"


template<Scalar T>
class Figure {
protected:
    Array<Point<T>> m_point_array;
    
    virtual void setFigure(std::istream& is) = 0;
    virtual void printFigure(std::ostream& os) const = 0;
    
public:
    Figure() = default;
    virtual ~Figure() = default;

    Figure<T>& operator=(const Figure<T>& other);
    
    Figure<T>& operator=(Figure<T>&& other) noexcept;
    
    virtual Point<T> geometricCenter() const = 0;
    virtual operator double() const = 0;
};


#include "figure.ipp"