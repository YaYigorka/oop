#pragma once

#include <iostream>

#include "coordinates_vector.hpp"


class Figure {
protected:
    virtual void setFigure(std::istream& is) = 0;
    virtual void printFigure(std::ostream& os) const = 0;
    CoordinatesVector coordinates_vector;
public:
    //The rule of five + constructor
    Figure();
    Figure(const Figure& other);
    Figure(Figure&& other) noexcept;
    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;
    virtual ~Figure() = default;
    
    Figure(size_t point_count);

    friend std::ostream& operator<<(std::ostream& os, const Figure& f);
    friend std::istream& operator>>(std::istream& is, Figure& f);

    virtual Dot2D geometricCenter() const = 0;
    virtual operator double() const = 0;
    // friend bool operator==(const Figure& left, const Figure& right);
    // This functions should be implemented in the successor classes.
};