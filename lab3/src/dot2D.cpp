#include <iostream>

#include "dot2D.hpp"


void Dot2D::setDot(double x, double y) {
    m_x = x;
    m_y = y;
}


double Dot2D::getX() const{
    return m_x;
}


double Dot2D::getY() const {
    return m_y;
}