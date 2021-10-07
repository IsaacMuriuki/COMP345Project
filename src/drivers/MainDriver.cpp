#include <iostream>
#include <stdio.h>
#include <string>

int main() {
    std::cout << "Menu - COMP 345 Project - Part 1 - Team DN7" << std::endl;
    std::cout << "Here are the driver options for execution:" << std::endl;
    std::cout << "" << std::endl;

    char option = ' '; // Initial value must not be an option.
    std::string options = "ABCDEF";

    while (option != 'F') {
        std::cout << std::endl;
        if (options.find(option) != std::string::npos) {
            std::cout << "Enter a driver to execute." << std::endl;
            std::cout << "A- Map (Chris + Henry)" << std::endl;
            std::cout << "B- Player (Isaac)" << std::endl;
            std::cout << "C- Orders List (Thomas)" << std::endl;
            std::cout << "D- Cards/Deck (Tyler)" << std::endl;
            std::cout << "E- Game Engine (Salaheddine)" << std::endl;
            std::cout << "F- Stop the program" << std::endl;
        }

        std::cout << "Enter your option: ";
        std::cout.flush();
        std::cin >> option;
        option = (char) toupper(option);

        switch (option) {
            case 'A':
                // MapDriver
                break;
            case 'B':
                // PlayerDriver
                break;
            case 'C':
                // OrdersDriver
                break;
            case 'D':
                // CardsDriver
                break;
            case 'E':
                // GameEngineDriver
                break;
            case 'F':
                // Ignore.
                break;
            default:
                std::cout << "Please double check your selection." << std::endl;
        }
    }
    return 0;
}