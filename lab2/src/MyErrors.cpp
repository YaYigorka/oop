#include <iostream>

#include "MyErrors.hpp"


NegetiveValueError::NegetiveValueError(const std::string& context)
    : message{"Negative value error"}
{
    if (!context.empty()) {
        message += ":" + context;
    }
}


const char* NegetiveValueError::what() const noexcept {
    return message.c_str();
}