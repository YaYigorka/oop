template<typename T>
Array<T>::Array()
    : m_data(new std::shared_ptr<T>[1], [](std::shared_ptr<T>* ptr) { delete[] ptr; })
    , m_size(0)
    , m_capacity(1)
{
}


template<typename T>
Array<T>::Array(size_t size)
    : m_data(new std::shared_ptr<T>[size], [](std::shared_ptr<T>* ptr) { delete[] ptr; })
    , m_size(0)
    , m_capacity(size)
{
}


template<typename T>
Array<T>::Array(const Array<T>& other)
    : m_data(new std::shared_ptr<T>[other.m_capacity], [](std::shared_ptr<T>* ptr) { delete[] ptr; })
    , m_size(other.m_size)
    , m_capacity(other.m_capacity)
{
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = std::make_shared<T>(other.takeByIndex(i));
    }
}


template<typename T>
Array<T>::Array(Array<T>&& other) noexcept
    : m_data(std::move(other.m_data))
    , m_size(other.m_size)
    , m_capacity(other.m_capacity)
{
    other.m_size = 0;
    other.m_capacity = 0;
}


template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this == &other) return *this;

    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_data.reset(new std::shared_ptr<T>[m_capacity]);
    
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = std::make_shared<T>(other.takeByIndex(i));
    }
    return *this;
}


template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& other) noexcept {
    if (this == &other) return *this;

    m_data = std::move(other.m_data);
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    other.m_size = 0;
    other.m_capacity = 0;
    return *this;
}


template<typename T>
Array<T>::~Array() noexcept = default;


template<typename T>
T& Array<T>::takeByIndex(size_t index) {
    if (index < m_size && m_data[index]) {
        return *m_data[index];
    }
    throw std::out_of_range("Index out of range");
}


template<typename T>
const T& Array<T>::takeByIndex(size_t index) const {
    if (index < m_size && m_data[index]) {
        return *m_data[index];
    }
    throw std::out_of_range("Index out of range");
}


template<typename T>
void Array<T>::resize(size_t new_capacity) {
    auto new_data = std::shared_ptr<std::shared_ptr<T>[]>(
        new std::shared_ptr<T>[new_capacity],
        [](std::shared_ptr<T>* ptr) { delete[] ptr; }
    );
    
    for (size_t i = 0; i < m_size; ++i) {
        new_data[i] = m_data[i];
    }
    
    m_data = new_data;
    m_capacity = new_capacity;
}


template<typename T>
void Array<T>::clear() {
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i].reset();
    }
    m_size = 0;
}


template<typename T>
T& Array<T>::back() {
    if (m_size > 0) {
        return *m_data[m_size - 1];
    }
    throw std::out_of_range("Array is empty");
}


template<typename T>
const T& Array<T>::back() const {
    if (m_size > 0) {
        return *m_data[m_size - 1];
    }
    throw std::out_of_range("Array is empty");
}


template<typename T>
T& Array<T>::front() {
    if (m_size > 0) {
        return *m_data[0];
    }
    throw std::out_of_range("Array is empty");
}


template<typename T>
const T& Array<T>::front() const {
    if (m_size > 0) {
        return *m_data[0];
    }
    throw std::out_of_range("Array is empty");
}


template<typename T>
void Array<T>::push_back(const T& object) {
    if (m_size >= m_capacity) {
        resize(m_capacity * 2);
    }
    
    m_data[m_size] = std::make_shared<T>(object);
    ++m_size;
}


template<typename T>
void Array<T>::pop_back() {
    if (m_size > 0) {
        m_data[m_size - 1].reset();
        --m_size;
    }
}