// main.cpp
#include <iostream>
#include "allocator.hpp"
#include "list.hpp"

int main() {
    Allocator<int, 1024> alloc;
    
    List<int, 1024> myList(alloc);
    
    std::cout << "Adding elements to the list..." << std::endl;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    myList.push_front(5);
    
    std::cout << "List size: " << myList.get_size() << std::endl;
    
    std::cout << "List elements: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Removing elements..." << std::endl;
    myList.pop_back();
    myList.pop_front();
    
    std::cout << "Updated list size: " << myList.get_size() << std::endl;
    std::cout << "Updated elements: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Clearing the list..." << std::endl;
    myList.clear();
    std::cout << "Final list size: " << myList.get_size() << std::endl;
    
    std::cout << "Program completed successfully." << std::endl;
    
    return 0;
}