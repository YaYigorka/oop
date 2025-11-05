#pragma once

#include <string>

#include "DynamicArray.hpp"


class Eleven {
private:
    DynamicArray dynamic_array;
    unsigned int dec;
public:
    Eleven();
    ~Eleven();
    Eleven(const Eleven& other);
    Eleven(size_t size);
    Eleven(const std::string nubmer, int dec_number);
    Eleven& operator=(const Eleven& other);
    void write(const std::string number, int dec_number);
    const DynamicArray& get_array_link() const;
    DynamicArray& get_array_link();
    Eleven operator+(const Eleven& other);
    Eleven operator-(const Eleven& other);
    bool operator<(const Eleven& other);
    bool operator>(const Eleven& other);
    bool operator==(const Eleven& other);
    std::string getNumber() const;
    int decRead() const;
    void erase();
};