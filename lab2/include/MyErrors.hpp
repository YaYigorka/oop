#pragma once

#include <exception>
#include <string>


class NegetiveValueError : public std::exception {
private:
    std::string message;
public:
    NegetiveValueError(const std::string& context = "");
    const char* what() const noexcept override;
};