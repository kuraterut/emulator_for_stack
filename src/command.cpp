#include <iostream>
#include <stdlib.h>
#include "command.hpp"

#include "emulator.hpp"

std::vector<std::string> reg_names = {"AX", "BX", "CX", "DX", "EX", "FX", "PC"};

std::vector<std::string> cmd_names = {
									"BEGIN", "END", "PUSH", "POP", "PUSHR", 
									"POPR" , "ADD", "SUB" , "MUL", "DIV"  ,
									"OUT"  , "IN" , "JMP" , "JEQ", "JNE"  , 
									"JA"   , "JAE", "JB"  , "JBE", "CALL" , 
									"RET", "label"
									};

Reg_t reg_from_name_to_id(std::string name){
	
	for (int i = 0; i < REG_NUM; i++){
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
	if (emulator->mode){
		emulator->mode = false;
		emulator->registers[REG_NUM-1] = emulator->code.size();
	}
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

// void CommandJMP::execute(Emulator* emulator){
// 	if(emulator->mode){
// 		emulator->registers[6] = go_to - 1;
// 	}
// }
bool CommandJUMP::check(Value_t var1, Value_t var2){
	return 1;
}

void CommandJUMP::execute(Emulator* emulator){
	if(emulator->mode){
		Value_t var1, var2;
		var1 = emulator->stack.top();
		emulator->stack.pop();
		var2 = emulator->stack.top();
		emulator->stack.push(var1);
		if (check(var1, var2)){
			emulator->registers[REG_NUM-1] = go_to - 1; 
		}
	}
}

void CommandJMP::execute(Emulator* emulator){
	if(emulator->mode){
		emulator->registers[REG_NUM-1] = go_to - 1;
	}
}

bool CommandJEQ::check(Value_t var1, Value_t var2){
	return var1 == var2;
}

bool CommandJNE::check(Value_t var1, Value_t var2){
	return var1 != var2;
}

bool CommandJA::check(Value_t var1, Value_t var2){
	return var1 > var2;
}

bool CommandJAE::check(Value_t var1, Value_t var2){
	return var1 >= var2;
}

bool CommandJB::check(Value_t var1, Value_t var2){
	std::cout << "LOL JB" << std::endl;
	return var1 < var2;
}

bool CommandJBE::check(Value_t var1, Value_t var2){
	return var1 <= var2;
}

void CommandCALL::execute(Emulator* emulator){
	if(emulator->mode){
		emulator->stack.push(emulator->registers[REG_NUM-1]);
		emulator->registers[REG_NUM-1] = go_to - 1;
	}
}

void CommandRET::execute(Emulator* emulator){
	if (emulator->mode){
		emulator->registers[REG_NUM-1] = emulator->stack.top();
		emulator->stack.pop();
	}
}