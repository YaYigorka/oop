#include <exception>
#include <iostream>

#include "../include/figure_vector.hpp"


FigureVector::FigureVector()
    : m_data{new Figure*[3]{}}
    , m_size{0}
    , m_capacity{3}
{
}


FigureVector::FigureVector(const FigureVector& other)
    : m_data(new Figure*[other.getCapacity()]{})
    , m_size{other.getSize()}
    , m_capacity(other.getCapacity())
{
    for (size_t i = 0; i < other.getSize(); ++i) {
        const std::type_info& type = typeid(*other.m_data[i]);
        if (type == typeid(Trapezoid)) {
            const Trapezoid* trapezoid_ptr = static_cast<const Trapezoid*>(other.m_data[i]);
            m_data[i] = new Trapezoid(*trapezoid_ptr);
        } else if (type == typeid(Rhombus)) {
            const Rhombus* rhombus_prt = static_cast<const Rhombus*>(other.m_data[i]);
            m_data[i] = new Rhombus(*rhombus_prt);
        } else {
            const Pentagon* pentagon_prt = static_cast<const Pentagon*>(other.m_data[i]);
            m_data[i] = new Pentagon(*pentagon_prt);
        }
    }
}


FigureVector::FigureVector(FigureVector&& other) noexcept
    : m_data{other.m_data}
    , m_size{other.m_size}
    , m_capacity{other.m_capacity}
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}


FigureVector& FigureVector::operator=(const FigureVector& other) {
    if (this != &other) {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_data[i];
        }

        delete[] m_data;

        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = new Figure*[other.m_capacity]{};
        for (size_t i = 0; i < other.getSize(); ++i) {
            const std::type_info& type = typeid(*other.m_data[i]);
            if (type == typeid(Trapezoid)) {
                const Trapezoid* trapezoid_ptr = static_cast<const Trapezoid*>(other.m_data[i]);
                m_data[i] = new Trapezoid(*trapezoid_ptr);
            } else if (type == typeid(Rhombus)) {
                const Rhombus* rhombus_prt = static_cast<const Rhombus*>(other.m_data[i]);
                m_data[i] = new Rhombus(*rhombus_prt);
            } else {
                const Pentagon* pentagon_prt = static_cast<const Pentagon*>(other.m_data[i]);
                m_data[i] = new Pentagon(*pentagon_prt);
            }
        }
    }

    return *this;
}


FigureVector& FigureVector::operator=(FigureVector&& other) noexcept {
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


FigureVector::FigureVector(size_t size)
    : m_data{new Figure*[size]{}}
    , m_size{0}
    , m_capacity{size}
{
}


FigureVector::~FigureVector() {
    if (m_size > 0) {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_data[i];
            m_data[i] = nullptr;
        }
    }

    delete[] m_data;
    m_data = nullptr;
}


size_t FigureVector::getCapacity() const {
    return m_capacity;
}


size_t FigureVector::getSize() const {
    return m_size;
}


Figure& FigureVector::get_link() const {
    if (m_data != nullptr && m_data[0] != nullptr) {
        return **m_data;
    }

    throw std::out_of_range("Invalid index");
}


Figure& FigureVector::takeByIndex(size_t index) {
    if (index < m_size && m_data[index] != nullptr) {
        return *m_data[index];
    }

    throw std::out_of_range("Index out of range");
}


const Figure& FigureVector::takeByIndex(size_t index) const {
    if (index < m_size && m_data[index] != nullptr) {
        return *m_data[index];
    }

    throw std::out_of_range("Index out of range");
}


void FigureVector::upSize() {
    ++m_size;
}


void FigureVector::downSize() {
    --m_size;
}


bool FigureVector::empty() const {
    return m_size == 0;
}


void FigureVector::clear() {
    if (m_size > 0) {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_data[i];
            m_data[i] = nullptr;
        }
    }

    m_size = 0;
}


Figure& FigureVector::back() {
    if (m_size > 0) {
        return *m_data[m_size - 1];
    } else {
        throw std::out_of_range("Array is empty");
    }
}


const Figure& FigureVector::back() const {
    if (m_size > 0) {
        return *m_data[m_size - 1];
    } else {
        throw std::out_of_range("Array is empty");
    }
}


Figure& FigureVector::front() {
    if (m_size > 0) {
        return *m_data[0];
    } else {
        throw std::out_of_range("Array is empty");
    }
}


const Figure& FigureVector::front() const{
    if (m_size > 0) {
        return *m_data[0];
    } else {
        throw std::out_of_range("Array is empty");
    }
}


void FigureVector::push_back(Figure& object) {
    if (m_size < m_capacity) {
        if (auto* trap = dynamic_cast<Trapezoid*>(&object)) {
            m_data[m_size] = new Trapezoid(*trap);
        } else if (auto* rhomb = dynamic_cast<Rhombus*>(&object)) {
            m_data[m_size] = new Rhombus(*rhomb);
        } else {
            auto* pent = dynamic_cast<Pentagon*>(&object);
            m_data[m_size] = new Pentagon(*pent);
        }
        ++m_size;
    } else {
        m_capacity *= 2;
        Figure** new_data = new Figure*[m_capacity]{};
        for (size_t i = 0; i < m_size; ++i) {
            new_data[i] = m_data[i];
        }

        delete[] m_data;
        m_data = new_data;

        if (auto* trap = dynamic_cast<Trapezoid*>(&object)) {
            m_data[m_size] = new Trapezoid(*trap);
        } else if (auto* rhomb = dynamic_cast<Rhombus*>(&object)) {
            m_data[m_size] = new Rhombus(*rhomb);
        } else {
            auto* pent = dynamic_cast<Pentagon*>(&object);
            m_data[m_size] = new Pentagon(*pent);
        }
        ++m_size;
    }
}


void FigureVector::pop_back() {
    if (m_size > 0 && m_data[m_size - 1] != nullptr) {
        delete m_data[m_size - 1];
        m_data[m_size - 1] = nullptr;
        --m_size;
    }
}


void FigureVector::figureInfo(size_t index) {
    if (m_size == 0) {
        std::cout << "Vector is empty" << std::endl;
    }
    if (index < m_size) {
        Dot2D centre = m_data[index]->geometricCenter();
        double area = *m_data[index];
    
        std::cout << "Figure type: " << typeid(*m_data[index]).name() << "\n" <<
                     "Figure centre (X, Y): (" << centre.getX() << ", " << centre.getY() << ")\n" <<
                     "Figure area: " << area << std::endl;
    } else {
        throw std::out_of_range("Index out of range");
    }
}


double FigureVector::totalArea() {
    if (m_size > 0) {
        double total_area;
        for (size_t i = 0; i < m_size; ++i) {
            total_area += static_cast<double>(*m_data[i]);
        }
        
        return total_area;
    } else {
        throw std::out_of_range("Array is empty");
    }
}