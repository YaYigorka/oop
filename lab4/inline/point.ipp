template<Scalar T>
Point<T>::Point(T x, T y)
    : m_x{x}
    , m_y{y}
{
}


template<Scalar T>
void Point<T>::setPoint(T x, T y) {
    m_x = x;
    m_y = y;
}


template<Scalar T>
T Point<T>::getX() const {
    return m_x;
}


template<Scalar T>
T Point<T>::getY() const {
    return m_y;
}


template<Scalar T>
std::istream& operator>>(std::istream& is, Point<T>& p) {
    T x, y;
    is >> x >> y;
    p.setPoint(x, y);
    return is;
}


template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << "has coordinates (" << p.getX() << ", " << p.getY() << ").";
    return os;
}


template<Scalar T>
bool operator==(const Point<T>& left, const Point<T>& right) {
    return left.getX() == right.getX() && left.getY() == right.getY();
}


template<Scalar T>
bool operator!=(const Point<T>& left, const Point<T>& right) {
    return !(left == right);
}