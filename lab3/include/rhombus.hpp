#pragma once

#include "figure.hpp"


class Rhombus : public Figure {
protected:
    void setFigure(std::istream& is) override;
    void printFigure(std::ostream& os) const override;
public:
    //The rule of five + constructor
    Rhombus();
    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other) noexcept;
    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;
    ~Rhombus() = default;

    Dot2D geometricCenter() const override;
    operator double() const override;
    friend bool operator==(const Rhombus& left, const Rhombus& right);
};