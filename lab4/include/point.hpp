#pragma once

#include <iostream>
#include "concepts.hpp"


template<Scalar T>
class Point {
private:
    T m_x;
    T m_y;
public:
    Point() : m_x{0}, m_y{0} {};
    Point(T x, T y);

    void setPoint(T x, T y);

    T getX() const;
    T getY() const;

    Point(const Point<T>& other) = default;
    Point(Point<T>&& other) noexcept = default;
    Point& operator=(const Point<T>& other) = default;
    Point& operator=(Point<T>&& other) noexcept = default;
    ~Point() = default;
};


template<Scalar T>
std::istream& operator>>(std::istream& is, Point<T>& p);

template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p);

template<Scalar T>
bool operator==(const Point<T>& left, const Point<T>& right);

template<Scalar T>
bool operator!=(const Point<T>& left, const Point<T>& right);


#include "point.ipp"