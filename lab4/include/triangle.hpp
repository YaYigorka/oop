#pragma once

#include "concepts.hpp"
#include "figure.hpp"

template<Scalar T>
class Triangle : public Figure<T> {
protected:
    void setFigure(std::istream& is) override;
    void printFigure(std::ostream& os) const override;
    
public:
    Triangle();
    ~Triangle() = default;

    Point<T> geometricCenter() const override;
    operator double() const override;

    friend std::ostream& operator<<(std::ostream& os, const Triangle<T>& t) {
        t.printFigure(os);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Triangle<T>& t) {
        t.setFigure(is);
        return is;
    }
    
    friend bool operator==(const Triangle<T>& left, const Triangle<T>& right) {
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
};


#include "triangle.ipp"