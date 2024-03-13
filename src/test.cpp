#include <iostream>
#include <stdlib.h>

#include "../include/parser.hpp"
#include "../include/command.hpp"
#include "../include/emulator.hpp"

int main(){

    Parser parser("emulator_test.test");

    Emulator eml(parser.parse_programm());
    
    eml.run();

    return 0;
}