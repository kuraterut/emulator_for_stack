#include <iostream>
#include <stdlib.h>
#include <iterator>

#include "../include/utils.hpp"
// #include "../include/myStack.hpp"
#include "../include/parser.hpp"
#include "../include/command.hpp"
#include "../include/emulator.hpp"

Emulator::Emulator(const std::vector<Command*>& cmd_list){
	code = cmd_list;
	memset(registers, 0, sizeof(Value_t)*REG_NUM);
	mode = false;
}

Emulator::~Emulator(){
	long size = code.size();
	for (long i = 0; i < size; i++){
		delete code[i];
	}
}

void Emulator::run(){
	printf("Run programm\n");

	int code_size = static_cast<int>(code.size());

	while (registers[REG_NUM-1] < code_size){

		code[registers[REG_NUM-1]]->execute(this);
		registers[REG_NUM-1]++;
	
	}

	printf("End Programm\n");


}