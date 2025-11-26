#pragma once

#include "figure.hpp"
#include "concepts.hpp"

template<Scalar T>
class Square : public Figure<T> {
protected:
    void setFigure(std::istream& is) override;
    void printFigure(std::ostream& os) const override;
    
public:
    Square();
    ~Square() = default;

    Point<T> geometricCenter() const override;
    operator double() const override;

    friend std::ostream& operator<<(std::ostream& os, const Square<T>& s) {
        s.printFigure(os);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Square<T>& s) {
        s.setFigure(is);
        return is;
    }
    
    friend bool operator==(const Square<T>& left, const Square<T>& right) {
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
    
    friend bool operator!=(const Square<T>& left, const Square<T>& right) {
        return !(left == right);
    }
};


#include "square.ipp"