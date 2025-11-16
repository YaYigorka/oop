#pragma once

#include "../include/figure.hpp"


class Pentagon : public Figure {
protected:
    void setFigure(std::istream& is) override;
    void printFigure(std::ostream& os) const override;
public:
    //The rule of five + constructor
    Pentagon();
    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;
    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;
    ~Pentagon() = default;

    Dot2D geometricCenter() const override;
    operator double() const override;
    friend bool operator==(const Pentagon& left, const Pentagon& right);
};