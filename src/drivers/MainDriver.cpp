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
            std::cout << "A- Order Execution (Isaac)" << std::endl;
            std::cout << "B- Commands (Salaheddine)" << std::endl;
            std::cout << "C- Territory Values" << std::endl;
            std::cout << "D- Game Log Observer" << std::endl;
            std::cout << "E- Stop the program" << std::endl;
        }

        std::cout << "Enter your option: ";
        std::cout.flush();
        std::cin >> option;
        option = (char) toupper(option);

        switch (option) {
            case 'A':
                 orderExecutionDriver();
                break;
            case 'B':{
               commandsDriver();
                break;
            }
            case 'C': {
                territoryValuesDriver();
                break;
            }
            case 'D':
                logObserverDriver();
                break;
            case 'E':
                return EXIT_SUCCESS;
                break;
            default:
                std::cout << "Please double check your selection." << std::endl;
        }
    }
    //test

    return 0;
}