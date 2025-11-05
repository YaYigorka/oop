#include <iostream>
#include <exception>
#include <cstddef>
#include <string>

#include "DynamicArray.hpp"


DynamicArray::DynamicArray()
try
    : data{new unsigned char[10]{}}
    , size{}
    , capacity{10}
{
}
catch(const std::bad_alloc& e) {
    std::cerr << e.what() << std::endl;
    throw;
}


DynamicArray::DynamicArray(std::string number)
try
    : data{new unsigned char[number.size() + 1]{}}
    , size{}
    , capacity{number.size() + 1}
{   
    std::string string;
    for (int i = number.size(); i > 0; --i) {
        string += number[i - 1];
    }
    for (size_t i = 0; i != string.size(); ++i) {
        if (string[i] != 'A') {
            data[i] = static_cast<unsigned char>(string[i] - '0');

        } else {
            data[i] = static_cast<unsigned char>(10);
        }
        ++size;
    }    
}
catch(const std::bad_alloc& e) {
    std::cerr << e.what() << std::endl;
    throw;
}


DynamicArray::DynamicArray(size_t capacity)
try
    : data{new unsigned char[capacity]{}}
    , size{}
    , capacity{capacity}
{
}
catch(const std::bad_alloc& e) {
    std::cerr << e.what() << std::endl;
    throw;
}


DynamicArray::DynamicArray(const DynamicArray& other)
try
    : data{new unsigned char[other.capacity]}
    , size{other.size}
    , capacity{other.capacity}
{
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}
catch(const std::bad_alloc& e) {
    std::cerr << e.what() << std::endl;
    throw;
}


DynamicArray::~DynamicArray() {
    delete[] data;
}


DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (this == &other) {
        return *this;
    }
    
    try {
        unsigned char* new_data = new unsigned char[other.capacity];
        for (size_t i = 0; i < other.size; ++i) {
            new_data[i] = other.data[i];
        }

        delete[] data;
        data = new_data;
        size = other.size;
        capacity = other.capacity;
    }
    catch(const std::bad_alloc& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    
    return *this;
}


unsigned char& DynamicArray::operator[](size_t index) {
    if (index < size) {
        return data[index];
    }

    throw std::out_of_range("Index is out of range");
}


const unsigned char& DynamicArray::operator[](size_t index) const {
    if (index < size) {
        return data[index];
    }

    throw std::out_of_range("Index is out of range");
}


size_t DynamicArray::getSize() const {
    return size;
}


void DynamicArray::upSize() {
    ++size;
}

void DynamicArray::downSize() {
    --size;
}


size_t DynamicArray::getCapacity() const {
    return capacity;
}


bool DynamicArray::empty() const {
    return size == 0;
}


void DynamicArray::clear() {
    for (size_t i = 0; i < size; ++i) {
        data[i] = '\0';
    }

    size = 0;
}


unsigned char& DynamicArray::back() {
    if (size > 0) {
        return data[size - 1];
    }

    throw std::out_of_range("Array is empty");
}


unsigned char& DynamicArray::front() {
    if (size > 0) {
        return data[0];
    }
    
    throw std::out_of_range("Array is empty");
}


void DynamicArray::push_back(const unsigned char& smth) {
    if (size < capacity) {
        data[size] = smth;
        ++size;
    } else {
        try {
            capacity *= 2;
            unsigned char* new_data = new unsigned char[capacity]{};
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;

            data[size] = smth;
            ++size;
        }
        catch(const std::bad_alloc& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
    }
}


void DynamicArray::pop_back() {
    if (size > 0) {
        data[--size] = '\0';
    }
}


const unsigned char& DynamicArray::get_link() const {
    return *data;
}