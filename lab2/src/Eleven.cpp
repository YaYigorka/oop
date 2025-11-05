#include <string>
#include <exception>
#include <iostream>
#include <algorithm>

#include "Eleven.hpp"
#include "MyErrors.hpp"


static void deleteZero(DynamicArray& array);


Eleven::Eleven()
try
    : dynamic_array()
    , dec{}
{
}
catch(const std::bad_alloc& e) {
    std::cerr << e.what() << std::endl;
    throw;
}


Eleven::~Eleven() {}


Eleven::Eleven(const Eleven& other)
try
    : dynamic_array(other.dynamic_array)
    , dec{other.decRead()}
{
}
catch(const std::bad_alloc& e) {
    std::cerr << e.what() << std::endl;
    throw;
}


Eleven::Eleven(size_t size)
try
    : dynamic_array(size)
    , dec{}
{
}
catch (const std::bad_alloc& e) {
    std::cerr << e.what() << std::endl;
    throw;
}


Eleven::Eleven(const std::string number, int dec_number)
try
    : dynamic_array(number)
    , dec{dec_number}
{
}
catch(const std::bad_alloc& e) {
    std::cerr << e.what() << std::endl;
    throw;
}


Eleven& Eleven::operator=(const Eleven& other) {
    if (this == &other) {
        return *this;
    }
    
    try {
        dynamic_array = other.get_array_link();
        dec = other.dec;
    }
    catch(const std::bad_alloc& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    return *this;
}


void Eleven::write(const std::string number, int dec_number) {
    if (decRead() > 0) {
        std::cerr << "It's already a number";
        return;
    }

    dynamic_array.clear();
    
    std::string string;
    for (int i = number.size(); i != 0; --i) {
        string += number[i - 1];
    }
    for (size_t i = 0; i != string.size(); ++i) {
        if (string[i] != 'A') {
            dynamic_array.push_back(static_cast<unsigned char>(string[i] - '0'));
        } else {
            dynamic_array.push_back(10);
        }
    }

    dec = dec_number;
}


const DynamicArray& Eleven::get_array_link() const {
    return dynamic_array;
}

DynamicArray& Eleven::get_array_link() {
    return dynamic_array;
}


void Eleven::erase() {
    dynamic_array.clear();
}


int Eleven::decRead() const {
    return dec;
}


std::string Eleven::getNumber() const{
    std::string number;
    size_t size = dynamic_array.getSize();
    for (size_t i = dynamic_array.getSize(); i > 0; --i) {
        if (dynamic_array[i - 1] != 10) {
            number += static_cast<char>(dynamic_array[i - 1] + '0');
        } else {
            number += 'A';
        }
    }

    return number;
}


Eleven Eleven::operator+(const Eleven& other) {
    const DynamicArray& this_array = this->get_array_link();
    const DynamicArray& other_array = other.get_array_link();
    Eleven result;
    DynamicArray& result_array = result.get_array_link();
    
    size_t i = 0;
    unsigned char buffer = 0;
    unsigned char elem1, elem2;
    while (i < this_array.getSize() || i < other_array.getSize() || buffer != 0) {
        if (i < this_array.getSize()) {
            elem1 = this_array[i];
        } else {
            elem1 = 0;
        }
        
        if (i < other_array.getSize()) {
            elem2 = other_array[i];
        } else {
            elem2 = 0;
        }

        result_array.push_back((elem1 + elem2 + buffer) % 11);
        buffer = (elem1 + elem2 + buffer) / 11;

        ++i;
    }

    return result;
}


Eleven Eleven::operator-(const Eleven& other) {
    if (other.dec > this->dec) {
        throw NegetiveValueError();
    }

    const DynamicArray& this_array = this->get_array_link();
    const DynamicArray& other_array = other.get_array_link();
    Eleven result;
    DynamicArray& result_array = result.get_array_link();

    size_t i = 0;
    unsigned char buffer = 0;
    unsigned char elem1, elem2;
    while (i < this_array.getSize()) {
        elem1 = this_array[i];
        
        if (i < other_array.getSize()) {
            elem2 = other_array[i];
        } else {
            elem2 = 0;
        }

        int difference = elem1 - elem2 - buffer;
        if (difference < 0) {
            difference += 11;
            buffer = 1;
            result_array.push_back(difference);
        } else {
            result_array.push_back(difference);
            buffer = 0;
        }

        ++i;
    }

    deleteZero(result_array);
    return result;
}


static void deleteZero(DynamicArray& array) {
    int size = static_cast<int>(array.getSize() - 1);
    int zero_count = 0;
    for (int i = size; i >= 0; --i) {
        if (array[static_cast<size_t>(i)] == 0) {
            ++zero_count;
        } else {
            break;
        }
    }
    for (int i = 0; i < zero_count; ++i) {
        array.downSize();
    }
}


bool Eleven::operator<(const Eleven& other) {
    const DynamicArray& this_array = this->get_array_link();
    const DynamicArray& other_array = other.get_array_link();

    if (this_array.getSize() < other_array.getSize()) {
        return true;
    } else if (this_array.getSize() > other_array.getSize()) {
        return false;
    } else {
        for (int i = static_cast<int>(this_array.getSize()) - 1; i >= 0; --i) {
            if (this_array[i] != other_array[i]) {
                return this_array[i] < other_array[i];
            }
        }
    }

    return false;
}


bool Eleven::operator>(const Eleven& other) {
    const DynamicArray& this_array = this->get_array_link();
    const DynamicArray& other_array = other.get_array_link();

    if (this_array.getSize() > other_array.getSize()) {
        return true;
    } else if (this_array.getSize() < other_array.getSize()) {
        return false;
    } else {
        for (int i = static_cast<int>(this_array.getSize()) - 1; i >= 0; --i) {
            if (this_array[i] != other_array[i]) {
                return this_array[i] > other_array[i];
            }
        }
    }

    return false;
}


bool Eleven::operator==(const Eleven& other) {
    const DynamicArray& this_array = this->get_array_link();
    const DynamicArray& other_array = other.get_array_link();

    if (this_array.getSize() > other_array.getSize()) {
        return false;
    } else if (this_array.getSize() < other_array.getSize()) {
        return false;
    } else {
        for (int i = static_cast<int>(this_array.getSize()) - 1; i >= 0; --i) {
            if (this_array[i] != other_array[i]) {
                return false;
            }
        }
    }

    return true;
}