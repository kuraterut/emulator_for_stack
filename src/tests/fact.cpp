#include <iostream>
#include <ctime>
#include <typeinfo>
#include <vector>

#include "../../include/test_system.hpp"
#include "../../include/parser.hpp"
#include "../../include/command.hpp"
#include "../../include/emulator.hpp"

void emulator_run(const char* file, const char* file_bin){
    std::cout << "\n" << std::endl;
    Parser parser(file, file_bin);
    Emulator emul(parser.parse_programm());
    emul.run();
}


//--------------
// Test palette
//--------------



int main(void)
{
    emulator_run("src/tests/fact.test", "binaries/programm_fact.bin");
    return 0;
}