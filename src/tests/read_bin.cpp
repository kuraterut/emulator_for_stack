
#include <fstream>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <regex>
#include <vector>
#include <cstdint>

#include "../include/command.hpp"
#include "../include/emulator.hpp"

void run_bin(const char* filename_bin){
	std::ifstream file_bin(filename_bin);
	
	Command* ret;

	std::vector<Command*> vec_com;
	std::vector<std::pair<std::string, int>> labels_list;
	std::vector<std::pair<std::string, int>> jumps_list;
	Cmd_t id;
	Reg_t reg;
	Value_t val;
	size_t len;
	std::string label;
	int i = 0;
	int is_label;


	while (file_bin.read((char*)&id, sizeof(Cmd_t))){
		is_label = 0;

		switch (id){

			case cmd_id::BEGIN:
				ret = new CommandBEGIN(); 

				break;

			case cmd_id::END:
				ret = new CommandEND();
		
				break;

			case cmd_id::PUSH:
				ret = new CommandPUSH();

				file_bin.read((char*) &val, sizeof(Value_t));
				dynamic_cast<CommandPUSH*>(ret)->value = val;
		
				break;

			case cmd_id::POP:
				ret = new CommandPOP();
				
				break;

			case cmd_id::PUSHR:

				ret = new CommandPUSHR();
				file_bin.read((char*) &reg, sizeof(Reg_t));
				dynamic_cast<CommandPUSHR*>(ret)->reg_id = reg;
		
				break;

			case cmd_id::POPR:
				ret = new CommandPOPR();
				file_bin.read((char*) &reg, sizeof(Reg_t));
				dynamic_cast<CommandPOPR*>(ret)->reg_id = reg;

				break;
	
			case cmd_id::ADD:
				ret = new CommandADD();
		
				break;
	
			case cmd_id::SUB:
				ret = new CommandSUB();

				break;
	
			case cmd_id::MUL:
				ret = new CommandMUL();

				break;
	
			case cmd_id::DIV:
				ret = new CommandDIV();

				break;
	
			case cmd_id::OUT:
				ret = new CommandOUT();

				break;
	
			case cmd_id::IN:
				ret = new CommandIN();

				break;
	
			case cmd_id::JMP:
				ret = new CommandJMP();

				is_label = 1;
				break;

			case cmd_id::JEQ:
				ret = new CommandJEQ();

				is_label = 1;
				break;

			case cmd_id::JNE:
				ret = new CommandJNE();

				is_label = 1;
				break;

			case cmd_id::JA:
				ret = new CommandJA();

				is_label = 1;
				break;

			case cmd_id::JAE:
				ret = new CommandJAE();
				is_label = 1;
				break;

			case cmd_id::JB:
				ret = new CommandJB();

				is_label = 1;
				break;

			case cmd_id::JBE:
				ret = new CommandJBE();

				is_label = 1;
				break;

			case cmd_id::CALL:
				ret = new CommandCALL();

				is_label = 1;
				break;

			case cmd_id::RET:
				ret = new CommandRET();

				break;
			case cmd_id::label:
				file_bin.read((char*) &len, sizeof(len));
				char* label_ch = new char[len];
				file_bin.read(label_ch, len);
				label = label_ch;
				labels_list.push_back(std::pair<std::string, int>(label, i));
				is_label = 2;
			}

		if (is_label == 1){
			file_bin.read((char*) &len, sizeof(len));
			char* label_ch = new char[len];
			file_bin.read(label_ch, len);
			label = label_ch;
			jumps_list.push_back(std::pair<std::string, int>(label, i));

		}
		if (is_label!=2){
			vec_com.push_back(ret);
			i++;
		}
		
	}


	for (size_t i = 0; i < jumps_list.size(); i++){
		for (size_t j = 0; j < labels_list.size(); j++){
			if (jumps_list[i].first == labels_list[j].first){
				dynamic_cast<CommandJUMP*>(vec_com[jumps_list[i].second])->go_to = labels_list[j].second;
			}
		}
	}


	Emulator emul(vec_com);
    emul.run();
}

int main(void){
	run_bin("binaries/programm_fibo.bin");

	return 0;
}