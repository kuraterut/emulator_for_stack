#include <iostream>
#include <ctime>
#include <typeinfo>
#include <vector>

#include "../../include/test_system.hpp"
#include "../../include/parser.hpp"
#include "../../include/command.hpp"
#include "../../include/emulator.hpp"

void emulator_run(const char* file){
    std::cout << "\n" << std::endl;
    Parser parser(file);
    Emulator emul(parser.parse_programm());
    emul.run();
}


//--------------
// Test palette
//--------------



int main(void)
{
    emulator_run("src/tests/fibo.test");
    return 0;
}