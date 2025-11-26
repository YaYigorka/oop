#include <cmath>


template<Scalar T>
Triangle<T>::Triangle()
    : Figure<T>()
{
}


template<Scalar T>
void Triangle<T>::printFigure(std::ostream& os) const {
    os << "Triangle has points:\n";
    for (size_t i = 0; i < this->m_point_array.getSize(); ++i) {
        os << "Point " << i + 1 << " " << this->m_point_array.takeByIndex(i) << "\n";
    }
}


template<Scalar T>
void Triangle<T>::setFigure(std::istream& is) {
    T x1, x2, x3, y1, y2, y3;
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    
    Point<T> p1, p2, p3;
    p1.setPoint(x1, y1);
    p2.setPoint(x2, y2);
    p3.setPoint(x3, y3);
    
    this->m_point_array.push_back(p1);
    this->m_point_array.push_back(p2);
    this->m_point_array.push_back(p3);
}


template<Scalar T>
Point<T> Triangle<T>::geometricCenter() const {
    if (this->m_point_array.getSize() == 0) {
        Point<T> result_dot;
        result_dot.setPoint(0, 0);
        return result_dot;
    }
    
    const Point<T>& dot1 = this->m_point_array.takeByIndex(0);
    const Point<T>& dot2 = this->m_point_array.takeByIndex(1);
    const Point<T>& dot3 = this->m_point_array.takeByIndex(2);
    
    T center_x = (dot1.getX() + dot2.getX() + dot3.getX()) / 3;
    T center_y = (dot1.getY() + dot2.getY() + dot3.getY()) / 3;
    
    Point<T> result_dot;
    result_dot.setPoint(center_x, center_y);
    return result_dot;
}


template<Scalar T>
Triangle<T>::operator double() const {
    if (this->m_point_array.getSize() == 0) {
        return 0;
    }
    
    const Point<T>& dot1 = this->m_point_array.takeByIndex(0);
    const Point<T>& dot2 = this->m_point_array.takeByIndex(1);
    const Point<T>& dot3 = this->m_point_array.takeByIndex(2);
    
    double area = 0.5 * std::abs(
        (dot1.getX() * (dot2.getY() - dot3.getY()) +
         dot2.getX() * (dot3.getY() - dot1.getY()) +
         dot3.getX() * (dot1.getY() - dot2.getY()))
    );
    
    return area;
}