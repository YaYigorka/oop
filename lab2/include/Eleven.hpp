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
    void write(const std::string number, int dec_number);
    const DynamicArray& get_array_link() const;
    DynamicArray& get_array_link();
    std::string getNumber() const;
    int decRead() const;
    void erase();
};


Eleven add(const Eleven& left, const Eleven& right);
Eleven sub(const Eleven& left, const Eleven& right);
bool less(const Eleven& left, const Eleven& right);
bool more(const Eleven& left, const Eleven& right);
bool equal(const Eleven& left, const Eleven& right);