#include "rectangle.hpp"
#include <cmath>


template<Scalar T>
Rectangle<T>::Rectangle()
    : Figure<T>()
{
}


template<Scalar T>
void Rectangle<T>::printFigure(std::ostream& os) const {
    os << "Rectangle has points:\n";
    for (size_t i = 0; i < this->m_point_array.getSize(); ++i) {
        os << "Point " << i + 1 << " " << this->m_point_array.takeByIndex(i) << "\n";
    }
}


template<Scalar T>
void Rectangle<T>::setFigure(std::istream& is) {
    T x1, y1, x2, y2, x3, y3, x4, y4;
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    
    Point<T> p1, p2, p3, p4;
    p1.setPoint(x1, y1);
    p2.setPoint(x2, y2);
    p3.setPoint(x3, y3);
    p4.setPoint(x4, y4);
    
    this->m_point_array.push_back(p1);
    this->m_point_array.push_back(p2);
    this->m_point_array.push_back(p3);
    this->m_point_array.push_back(p4);
}


template<Scalar T>
Point<T> Rectangle<T>::geometricCenter() const {
    if (this->m_point_array.getSize() == 0) {
        Point<T> result_dot;
        result_dot.setPoint(0, 0);
        return result_dot;
    }
    
    const Point<T>& dot1 = this->m_point_array.takeByIndex(0);
    const Point<T>& dot2 = this->m_point_array.takeByIndex(1);
    const Point<T>& dot3 = this->m_point_array.takeByIndex(2);
    const Point<T>& dot4 = this->m_point_array.takeByIndex(3);
    
    T center_x = (dot1.getX() + dot2.getX() + dot3.getX() + dot4.getX()) / 4;
    T center_y = (dot1.getY() + dot2.getY() + dot3.getY() + dot4.getY()) / 4;
    
    Point<T> result_dot;
    result_dot.setPoint(center_x, center_y);
    return result_dot;
}


template<Scalar T>
Rectangle<T>::operator double() const {
    if (this->m_point_array.getSize() == 0) {
        return 0;
    }
    
    const Point<T>& dot1 = this->m_point_array.takeByIndex(0);
    const Point<T>& dot2 = this->m_point_array.takeByIndex(1);
    const Point<T>& dot3 = this->m_point_array.takeByIndex(2);
    
    double side1 = std::sqrt(
        std::pow(dot2.getX() - dot1.getX(), 2) + 
        std::pow(dot2.getY() - dot1.getY(), 2)
    );
    
    double side2 = std::sqrt(
        std::pow(dot3.getX() - dot2.getX(), 2) + 
        std::pow(dot3.getY() - dot2.getY(), 2)
    );
    
    return side1 * side2;
}