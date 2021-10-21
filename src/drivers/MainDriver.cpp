#include <iostream>
#include <stdio.h>
#include <string>
#include "Drivers.h"

#include "GameEngine.h"

int main() {
    std::cout << "Menu - COMP 345 Project - Part 1 - Team DN7" << std::endl;
    std::cout << "Here are the driver options for execution:" << std::endl;

    char option = 'A'; // Initial value must be an option.
    std::string options = "ABCDEF";

    while (option != 'F') {
        std::cout << std::endl;
        if (options.find(option) != options.npos) {
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
                MapDriver::demo();
                break;
            case 'B':{
                // PlayerDriver
                PlayerDriver::demo();
                break;
            }
            case 'C': {

                // OrdersDriver
                OrdersDriver::demo();
                break;
            }
            case 'D':
                // CardsDriver
                CardsDriver::demo();
                break;
            case 'E':
                // GameEngineDriver
                // GameEngineDriver::demo();
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