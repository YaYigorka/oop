#pragma once

#include <cstddef>


class DynamicArray {
private:
    unsigned char* data; //указатель на динамический массив
    size_t size;
    size_t capacity;
public:
    DynamicArray();
    DynamicArray(std::string number);
    DynamicArray(size_t capacity);
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();
    DynamicArray& operator=(const DynamicArray& other);
    unsigned char& operator[](size_t index);
    const unsigned char& operator[](size_t index) const;
    size_t getSize() const;
    void upSize();
    void downSize();
    size_t getCapacity() const;
    bool empty() const;
    void clear();
    unsigned char& back();
    unsigned char& front();
    void push_back(const unsigned char& smth);
    void pop_back();
    const unsigned char& get_link() const;
};