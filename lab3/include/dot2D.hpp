#pragma once


class Dot2D {
private:
    double m_x;
    double m_y;
public:
    void setDot(double x, double y);
    double getX() const;
    double getY() const;
    
    //The rule of five + constructor
    Dot2D() = default;
    Dot2D(const Dot2D& other) = default;
    Dot2D(Dot2D&& other) noexcept = default;
    Dot2D& operator=(const Dot2D& other) = default;
    Dot2D& operator=(Dot2D&& other) noexcept = default;
    ~Dot2D() = default;
};