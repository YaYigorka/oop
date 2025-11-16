#include <exception>

#include "../include/figure.hpp"


Figure::Figure()
    : coordinates_vector()
{
}


Figure::Figure(const Figure& other)
    : coordinates_vector{other.coordinates_vector}
{
}


Figure::Figure(Figure&& other) noexcept
    : coordinates_vector{std::move(other.coordinates_vector)}
{
}


Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        coordinates_vector = other.coordinates_vector;
    }

    return *this;
}


Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        coordinates_vector = std::move(other.coordinates_vector);
    }

    return *this;
}


Figure::Figure(size_t point_count)
    : coordinates_vector(point_count)
{
}


std::ostream& operator<<(std::ostream& os, const Figure& f) {
    f.printFigure(os);
    return os;
}


std::istream& operator>>(std::istream& is, Figure& f) {
    f.setFigure(is);
    return is;
}