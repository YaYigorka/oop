// main.cpp
#include <iostream>
#include "triangle.hpp"
#include "square.hpp"
#include "rectangle.hpp"

int main() {
    std::cout << "=== Демонстрация работы с фигурами ===\n" << std::endl;

    // Треугольник
    std::cout << "1. Треугольник:" << std::endl;
    Triangle<int> triangle;
    std::cout << "Введите 6 координат (x1 y1 x2 y2 x3 y3): ";
    std::cin >> triangle;
    std::cout << triangle;
    std::cout << "Центр масс: " << triangle.geometricCenter() << std::endl;
    std::cout << "Площадь: " << static_cast<double>(triangle) << std::endl;
    std::cout << std::endl;

    // Квадрат
    std::cout << "2. Квадрат:" << std::endl;
    Square<int> square;
    std::cout << "Введите 8 координат (x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cin >> square;
    std::cout << square;
    std::cout << "Центр масс: " << square.geometricCenter() << std::endl;
    std::cout << "Площадь: " << static_cast<double>(square) << std::endl;
    std::cout << std::endl;

    // Прямоугольник
    std::cout << "3. Прямоугольник:" << std::endl;
    Rectangle<int> rectangle;
    std::cout << "Введите 8 координат (x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cin >> rectangle;
    std::cout << rectangle;
    std::cout << "Центр масс: " << rectangle.geometricCenter() << std::endl;
    std::cout << "Площадь: " << static_cast<double>(rectangle) << std::endl;

    return 0;
}