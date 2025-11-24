#pragma once

#include "figure.hpp"
#include "concepts.hpp"


template<Scalar T>
class Rectangle : public Figure<T> {
protected:
    void setFigure(std::istream& is) override;
    void printFigure(std::ostream& os) const override;
    
public:
    Rectangle();
    ~Rectangle() = default;

    Point<T> geometricCenter() const override;
    operator double() const override;

    // Объявляем операторы дружественными и определяем их прямо здесь
    friend std::ostream& operator<<(std::ostream& os, const Rectangle<T>& r) {
        r.printFigure(os);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Rectangle<T>& r) {
        r.setFigure(is);
        return is;
    }
    
    friend bool operator==(const Rectangle<T>& left, const Rectangle<T>& right) {
        if (left.m_point_array.getSize() != right.m_point_array.getSize()) {
            return false;
        }
        
        for (size_t i = 0; i < left.m_point_array.getSize(); ++i) {
            if (left.m_point_array.takeByIndex(i) != right.m_point_array.takeByIndex(i)) {
                return false;
            }
        }
        return true;
    }
    
    friend bool operator!=(const Rectangle<T>& left, const Rectangle<T>& right) {
        return !(left == right);
    }
};


#include "rectangle.ipp"