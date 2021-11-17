#include <iostream>
#include <stdio.h>
#include <string>
#include "Drivers.h"

int main() {

    std::cout << "Menu - COMP 345 Project - Part 1 - Team DN7" << std::endl;
    std::cout << "Here are the driver options for execution:" << std::endl;

    char option = 'A'; // Initial value must be an option.
    std::string options = "ABCDEFGH";

    while (option != 'F') {
        std::cout << std::endl;
        if (options.find(option) != options.npos) {
            std::cout << "Enter a driver to execute." << std::endl;
            std::cout << "A- Map (Chris + Henry)" << std::endl;
            std::cout << "B- Order Execution (Isaac)" << std::endl;
            std::cout << "C- Commands (Salaheddine)" << std::endl;
            std::cout << "D- Commands Driver" << std::endl;
            std::cout << "E- Territory Reinforcements" << std::endl;
            std::cout << "F- Command Processor" << std::endl;
            std::cout << "G- Game Log Observer" << std::endl;
            std::cout << "H- Stop the program" << std::endl;
        }

        std::cout << "Enter your option: ";
        std::cout.flush();
        std::cin >> option;
        option = (char) toupper(option);

        switch (option) {
            case 'A':
                mapDriver();
                break;
            case 'B':{
                orderExecutionDriver();
                break;
            }
            case 'C': {
                commandsDriver();
                break;
            }
            case 'D':
                commandsDriver();
                break;
            case 'E':
                territoryValuesDriver();
                break;
            case 'F':
                break;
            case 'G':
                break;
            case 'H':
                return EXIT_SUCCESS;
                break;
            default:
                std::cout << "Please double check your selection." << std::endl;
        }
    }

    return 0;
}