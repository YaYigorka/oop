#include "figure.hpp"


template<Scalar T>
Figure<T>& Figure<T>::operator=(const Figure<T>& other) {
    if (this == &other) {
        return *this;
    }

    m_point_array = other.m_point_array;
    return *this;
}


template<Scalar T>
Figure<T>& Figure<T>::operator=(Figure<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    m_point_array = std::move(other.m_point_array);
    
    return *this;
}