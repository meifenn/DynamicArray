#include <iostream>
#include <cassert>
#include "DynamicArray.hpp"

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    DynamicArray<int> arr;
    int choice;

    do {
        std::cout << std::endl << "=== Dynamic Array Menu ===" << std::endl;
        std::cout << "1. Add element" << std::endl;
        std::cout << "2. Remove last element" << std::endl;
        std::cout << "3. Show all elements" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int value;
            std::cout << "Enter value to add: ";
            std::cin >> value;
            arr.push_back(value);
            std::cout << "Added " << value << " to array." << std::endl;
            std::cout << "Array contents: ";
            for (size_t i = 0; i < arr.size(); ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
            std::cout << "Size: " << arr.size() << ", Current Capacity: " << arr.capacity() << std::endl;
        }
        else if (choice == 2) {
            if (!arr.empty()) {
                int last = arr.back();
                arr.pop_back();
                std::cout << "Removed last element: " << last << std::endl;
                std::cout << "Array contents: ";
                for (size_t i = 0; i < arr.size(); ++i) {
                    std::cout << arr[i] << " ";
                }
                std::cout << std::endl;
                std::cout << "Current Capacity: " << arr.capacity() << std::endl;
            }
            else {
                std::cout << "Array is empty." << std::endl;
            }
        }
        else if (choice == 3) {
            std::cout << "Array contents: ";
            for (size_t i = 0; i < arr.size(); ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }

    } while (choice != 0);

    std::cout << "Exiting. Final size: " << arr.size() << ", Capacity: " << arr.capacity() << std::endl;

    return 0;

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks;
}