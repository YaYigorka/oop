#include "../include/trapezoid.hpp"



Trapezoid::Trapezoid()
    : Figure()
{    
}


Trapezoid::Trapezoid(const Trapezoid& other)
    : Figure(other)
{
}


Trapezoid::Trapezoid(Trapezoid&& other) noexcept
    : Figure(std::move(other))
{
}


Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        Figure::operator=(other);
    }

    return *this;
}


Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        Figure::operator=(std::move(other));
    }

    return *this;
}


void Trapezoid::setFigure(std::istream& is) {
    int x1, y1, x2, y2, x3, y3, x4, y4;
    is >> x1 >> y1 >>
          x2 >> y2 >>
          x3 >> y3 >>
          x4 >> y4;
    Dot2D xy1, xy2, xy3, xy4;
    xy1.setDot(x1, y1);
    xy2.setDot(x2, y2);
    xy3.setDot(x3, y3);
    xy4.setDot(x4, y4);

    coordinates_vector.push_back(xy1);
    coordinates_vector.push_back(xy2);
    coordinates_vector.push_back(xy3);
    coordinates_vector.push_back(xy4);
}


void Trapezoid::printFigure(std::ostream& os) const {
    int x1, y1, x2, y2, x3, y3, x4, y4;
    const Dot2D& dot1 = coordinates_vector.takeByIndex(0);
    const Dot2D& dot2 = coordinates_vector.takeByIndex(1);
    const Dot2D& dot3 = coordinates_vector.takeByIndex(2);
    const Dot2D& dot4 = coordinates_vector.takeByIndex(3);

    os << "Trapezoid: (" << dot1.getX() << ", " << dot1.getY() << "), " <<
                     "(" << dot2.getX() << ", " << dot2.getY() << "), " <<
                     "(" << dot3.getX() << ", " << dot3.getY() << "), " <<
                     "(" << dot4.getX() << ", " << dot4.getY() << ")";
}


Dot2D Trapezoid::geometricCenter() const {
    if (coordinates_vector.getSize() == 0) {
        Dot2D result_dot;
        result_dot.setDot(0, 0);
        return result_dot;
    }
    const Dot2D& dot1 = coordinates_vector.takeByIndex(0);
    const Dot2D& dot2 = coordinates_vector.takeByIndex(1);
    const Dot2D& dot3 = coordinates_vector.takeByIndex(2);
    const Dot2D& dot4 = coordinates_vector.takeByIndex(3);
    double area_amount = dot1.getX() * dot2.getY() + dot2.getX() * dot3.getY() +
                      dot3.getX() * dot4.getY() + dot4.getX() * dot1.getY() -
                      dot1.getY() * dot2.getX() - dot2.getY() * dot3.getX() -
                      dot3.getY() * dot4.getX() - dot4.getY() * dot1.getX();

    area_amount *= 0.5;
    
    double Cx, Cy;
    Cx = (1.0 / (6 * area_amount)) *
         ((dot1.getX() + dot2.getX()) * (dot1.getX() * dot2.getY() - dot2.getX() * dot1.getY())) +
         ((dot2.getX() + dot3.getX()) * (dot2.getX() * dot3.getY() - dot3.getX() * dot2.getY())) +
         ((dot3.getX() + dot4.getX()) * (dot3.getX() * dot4.getY() - dot4.getX() * dot3.getY())) +
         ((dot4.getX() + dot1.getX()) * (dot4.getX() * dot1.getY() - dot1.getX() * dot4.getY()));

    Cy = (1.0 / (6 * area_amount)) *
         ((dot1.getY() + dot2.getY()) * (dot1.getX() * dot2.getY() - dot2.getX() * dot1.getY())) +
         ((dot2.getY() + dot3.getY()) * (dot2.getX() * dot3.getY() - dot3.getX() * dot2.getY())) +
         ((dot3.getY() + dot4.getY()) * (dot3.getX() * dot4.getY() - dot4.getX() * dot3.getY())) +
         ((dot4.getY() + dot1.getY()) * (dot4.getX() * dot1.getY() - dot1.getX() * dot4.getY()));

    Dot2D result_dot;
    result_dot.setDot(Cx, Cy);
    return result_dot;
}


Trapezoid::operator double() const {
    if (coordinates_vector.getSize() == 0) {
        return 0;
    }
    const Dot2D& dot1 = coordinates_vector.takeByIndex(0);
    const Dot2D& dot2 = coordinates_vector.takeByIndex(1);
    const Dot2D& dot3 = coordinates_vector.takeByIndex(2);
    const Dot2D& dot4 = coordinates_vector.takeByIndex(3);
    double area_amount = dot1.getX() * dot2.getY() + dot2.getX() * dot3.getY() +
                      dot3.getX() * dot4.getY() + dot4.getX() * dot1.getY() -
                      dot1.getY() * dot2.getX() - dot2.getY() * dot3.getX() -
                      dot3.getY() * dot4.getX() - dot4.getY() * dot1.getX();

    return area_amount * 0.5;
}


bool operator==(const Trapezoid& left, const Trapezoid& right) {
    if (left.coordinates_vector.getSize() == 0 || right.coordinates_vector.getSize() == 0) {
        return false;
    }
    Dot2D l_dot1 = left.coordinates_vector.takeByIndex(0);
    Dot2D l_dot2 = left.coordinates_vector.takeByIndex(1);
    Dot2D l_dot3 = left.coordinates_vector.takeByIndex(2);
    Dot2D l_dot4 = left.coordinates_vector.takeByIndex(3);
    Dot2D r_dot1 = right.coordinates_vector.takeByIndex(0);
    Dot2D r_dot2 = right.coordinates_vector.takeByIndex(1);
    Dot2D r_dot3 = right.coordinates_vector.takeByIndex(2);
    Dot2D r_dot4 = right.coordinates_vector.takeByIndex(3);

    return l_dot1.getX() == r_dot1.getX() && l_dot1.getY() == r_dot1.getY() &&
           l_dot2.getX() == r_dot2.getX() && l_dot2.getY() == r_dot2.getY() &&
           l_dot3.getX() == r_dot3.getX() && l_dot3.getY() == r_dot3.getY() &&
           l_dot4.getX() == r_dot4.getX() && l_dot4.getY() == r_dot4.getY();
}