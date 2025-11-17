#include <exception>
#include <iostream>

#include "coordinates_vector.hpp"


CoordinatesVector::CoordinatesVector()
    : m_data{new Dot2D*[5]{}}
    , m_size{0}
    , m_capacity{5}
{
}


CoordinatesVector::CoordinatesVector(const CoordinatesVector& other)
    : m_data(new Dot2D*[other.getCapacity()]{})
    , m_size{0}
    , m_capacity(other.getCapacity())
{
    for (size_t i = 0; i < other.getSize(); ++i) {
        m_data[i] = new Dot2D(*other.m_data[i]);
        ++m_size;
    }
}


CoordinatesVector::CoordinatesVector(CoordinatesVector&& other) noexcept
    : m_data{other.m_data}
    , m_size{other.m_size}
    , m_capacity{other.m_capacity}
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}


CoordinatesVector& CoordinatesVector::operator=(const CoordinatesVector& other) {
    if (this != &other) {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_data[i];
        }

        delete[] m_data;

        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = new Dot2D*[other.m_capacity]{};
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = new Dot2D(*other.m_data[i]);
        }
    }

    return *this;
}


CoordinatesVector& CoordinatesVector::operator=(CoordinatesVector&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_data[i];
        }

        delete[] m_data;

        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    return *this;
}


CoordinatesVector::CoordinatesVector(size_t size)
    : m_data{new Dot2D*[size]{}}
    , m_size{0}
    , m_capacity{size}
{
}


CoordinatesVector::~CoordinatesVector() {
    if (m_size > 0) {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_data[i];
        }
    }

    delete[] m_data;
    m_data = nullptr;
}


size_t CoordinatesVector::getCapacity() const {
    return m_capacity;
}


size_t CoordinatesVector::getSize() const {
    return m_size;
}


Dot2D& CoordinatesVector::get_link() const {
    if (m_data != nullptr && m_data[0] != nullptr) {
        return **m_data;
    }

    throw std::out_of_range("Invalid index");
}


Dot2D& CoordinatesVector::takeByIndex(size_t index) {
    if (index < m_size && m_data[index] != nullptr) {
        return *m_data[index];
    }

    throw std::out_of_range("Index out of range");
}


const Dot2D& CoordinatesVector::takeByIndex(size_t index) const {
    if (index < m_size && m_data[index] != nullptr) {
        return *m_data[index];
    }

    throw std::out_of_range("Index out of range");
}


void CoordinatesVector::upSize() {
    ++m_size;
}


void CoordinatesVector::downSize() {
    --m_size;
}


bool CoordinatesVector::empty() const {
    return m_size == 0;
}


void CoordinatesVector::clear() {
    if (m_size > 0) {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_data[i];
            m_data[i] = nullptr;
        }
    }

    m_size = 0;
}


Dot2D& CoordinatesVector::back() {
    if (m_size > 0) {
        return *m_data[m_size - 1];
    } else {
        throw std::out_of_range("Array is empty");
    }
}


const Dot2D& CoordinatesVector::back() const {
    if (m_size > 0) {
        return *m_data[m_size - 1];
    } else {
        throw std::out_of_range("Array is empty");
    }
}


Dot2D& CoordinatesVector::front() {
    if (m_size > 0) {
        return *m_data[0];
    } else {
        throw std::out_of_range("Array is empty");
    }

}


const Dot2D& CoordinatesVector::front() const{
    if (m_size > 0) {
        return *m_data[0];
    } else {
        throw std::out_of_range("Array is empty");
    }
}


void CoordinatesVector::push_back(Dot2D& object) {
    if (m_size < m_capacity) {
        m_data[m_size] = new Dot2D(object);
        ++m_size;
    } else {
        m_capacity *= 2;
        Dot2D** new_data = new Dot2D*[m_capacity]{};
        for (size_t i = 0; i < m_size; ++i) {
            new_data[i] = m_data[i];
        }

        delete[] m_data;
        m_data = new_data;

        m_data[m_size] = new Dot2D(object);
        ++m_size;
    }
}


void CoordinatesVector::pop_back() {
    if (m_size > 0 && m_data[m_size - 1] != nullptr) {
        delete m_data[m_size - 1];
        m_data[m_size - 1] = nullptr;
        --m_size;
    }
}