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
        if (dynamic_array.takeByIndex(i - 1) != 10) {
            number += static_cast<char>(dynamic_array.takeByIndex(i - 1) + '0');
        } else {
            number += 'A';
        }
    }

    return number;
}


Eleven add(const Eleven& left, const Eleven& right) {
    const DynamicArray& left_array = left.get_array_link();
    const DynamicArray& right_array = right.get_array_link();
    Eleven result;
    DynamicArray& result_array = result.get_array_link();
    
    size_t i = 0;
    unsigned char buffer = 0;
    unsigned char elem1, elem2;
    while (i < left_array.getSize() || i < right_array.getSize() || buffer != 0) {
        if (i < left_array.getSize()) {
            elem1 = left_array.takeByIndex(i);
        } else {
            elem1 = 0;
        }
        
        if (i < right_array.getSize()) {
            elem2 = right_array.takeByIndex(i);
        } else {
            elem2 = 0;
        }

        result_array.push_back((elem1 + elem2 + buffer) % 11);
        buffer = (elem1 + elem2 + buffer) / 11;

        ++i;
    }

    return result;
}


Eleven sub(const Eleven& left, const Eleven& right) {
    if (right.decRead() > left.decRead()) {
        throw NegetiveValueError();
    }

    const DynamicArray& left_array = left.get_array_link();
    const DynamicArray& right_array = right.get_array_link();
    Eleven result;
    DynamicArray& result_array = result.get_array_link();

    size_t i = 0;
    unsigned char buffer = 0;
    unsigned char elem1, elem2;
    while (i < left_array.getSize()) {
        elem1 = left_array.takeByIndex(i);
        
        if (i < right_array.getSize()) {
            elem2 = right_array.takeByIndex(i);
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
        if (array.takeByIndex(static_cast<size_t>(i)) == 0) {
            ++zero_count;
        } else {
            break;
        }
    }
    for (int i = 0; i < zero_count; ++i) {
        array.downSize();
    }
}


bool less(const Eleven& left, const Eleven& right) {
    const DynamicArray& left_array = left.get_array_link();
    const DynamicArray& right_array = right.get_array_link();

    if (left_array.getSize() < right_array.getSize()) {
        return true;
    } else if (left_array.getSize() > right_array.getSize()) {
        return false;
    } else {
        for (int i = static_cast<int>(left_array.getSize()) - 1; i >= 0; --i) {
            if (left_array.takeByIndex(i) != right_array.takeByIndex(i)) {
                return left_array.takeByIndex(i) < right_array.takeByIndex(i);
            }
        }
    }

    return false;
}


bool more(const Eleven& left, const Eleven& right) {
    const DynamicArray& left_array = left.get_array_link();
    const DynamicArray& right_array = right.get_array_link();

    if (left_array.getSize() > right_array.getSize()) {
        return true;
    } else if (left_array.getSize() < right_array.getSize()) {
        return false;
    } else {
        for (int i = static_cast<int>(left_array.getSize()) - 1; i >= 0; --i) {
            if (left_array.takeByIndex(i) != right_array.takeByIndex(i)) {
                return left_array.takeByIndex(i) > right_array.takeByIndex(i);
            }
        }
    }

    return false;
}


bool equal(const Eleven& left, const Eleven& right) {
    const DynamicArray& left_array = left.get_array_link();
    const DynamicArray& right_array = right.get_array_link();

    if (left_array.getSize() > right_array.getSize()) {
        return false;
    } else if (left_array.getSize() < right_array.getSize()) {
        return false;
    } else {
        for (int i = static_cast<int>(left_array.getSize()) - 1; i >= 0; --i) {
            if (left_array.takeByIndex(i) != right_array.takeByIndex(i)) {
                return false;
            }
        }
    }

    return true;
}