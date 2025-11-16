#pragma once

#include "../include/figure.hpp"


class Trapezoid : public Figure {
protected:
    void setFigure(std::istream& is) override;
    void printFigure(std::ostream& os) const override;
public:
    //The rule of five + constructor
    Trapezoid();
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;
    ~Trapezoid() = default;

    Dot2D geometricCenter() const override;
    operator double() const override;
    friend bool operator==(const Trapezoid& left, const Trapezoid& right);
};