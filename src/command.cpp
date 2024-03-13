#include <iostream>
#include <stdlib.h>
#include "command.hpp"

#include "emulator.hpp"

std::vector<std::string> reg_names = {"AX", "BX", "CX", "DX", "EX", "FX", "PC"};

std::vector<std::string> cmd_names = {"BEGIN", "END", "PUSH", "POP", "PUSHR", 
									  "POPR" , "ADD", "SUB" , "MUL", "DIV"  ,
									  "OUT"  , "IN"};

Reg_t reg_from_name_to_id(std::string name){
	
	long reg_size = reg_names.size();
	
	for (long i = 0; i < reg_size; i++){
		if (name == reg_names[i]){
			return i;
		}
	}

	return -1;

}

Cmd_t cmd_from_name_to_id(std::string name){
	
	long cmd_size = cmd_names.size();
	
	for (long i = 0; i < cmd_size; i++){
		if (name == cmd_names[i]){
			return i;
		}
	}

	return -1;	

}

void CommandBEGIN::execute(Emulator* emulator){
	emulator->mode = true;
}

void CommandEND::execute(Emulator* emulator){
	emulator->mode = false;
	emulator->registers[6] = emulator->code.size();
}

void CommandPUSH::execute(Emulator* emulator){
	if(emulator->mode){
		emulator->stack.push(value);
	}
}

void CommandPOP::execute(Emulator* emulator){
	if(emulator->mode){
		emulator->stack.pop();
	}
}

void CommandPUSHR::execute(Emulator* emulator){
	if(emulator->mode){
		emulator->stack.push(emulator->registers[reg_id]);
	}
}

void CommandPOPR::execute(Emulator* emulator){
	if(emulator->mode){
		emulator->registers[reg_id] = emulator->stack.top();
		emulator->stack.pop();
	}
}


void CommandADD::execute(Emulator* emulator){
	if(emulator->mode){
		Value_t val1 = emulator->stack.top();
		emulator->stack.pop();	
		Value_t val2 = emulator->stack.top();
		emulator->stack.pop();
		emulator->stack.push(val1+val2);
	}
}

void CommandSUB::execute(Emulator* emulator){
	if(emulator->mode){
		Value_t val1 = emulator->stack.top();
		emulator->stack.pop();	
		Value_t val2 = emulator->stack.top();
		emulator->stack.pop();
		emulator->stack.push(val1-val2);
	}
}

void CommandMUL::execute(Emulator* emulator){
	if(emulator->mode){
		Value_t val1 = emulator->stack.top();
		emulator->stack.pop();	
		Value_t val2 = emulator->stack.top();
		emulator->stack.pop();
		emulator->stack.push(val1*val2);
	}
}

void CommandDIV::execute(Emulator* emulator){
	if(emulator->mode){
		Value_t val1 = emulator->stack.top();
		emulator->stack.pop();	
		Value_t val2 = emulator->stack.top();
		emulator->stack.pop();
		emulator->stack.push(val1/val2);
	}
}

void CommandOUT::execute(Emulator* emulator){
	if(emulator->mode){
		std::cout << emulator->stack.top() << std::endl;
		emulator->stack.pop();
	}
}

void CommandIN::execute(Emulator* emulator){
	if(emulator->mode){
		Value_t var;
		std::cin >> var;
		emulator->stack.push(var);
	}
}