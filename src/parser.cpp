#include <iostream>
#include <stdlib.h>
#include <regex>
#include <fstream>
#include <iterator>
#include <cstdint>

#include "../include/parser.hpp"
#include "../include/command.hpp"
#include "../include/utils.hpp"



Parser::Parser(const char* filename, const char* file_bin_name):
	file_ (std::ifstream(filename, std::ios::in)), file_bin (std::ofstream(file_bin_name, std::ios::binary|std::ios::out))
{	
	VERIFY_CONTRACT(file_.good(), "Unable to open file \'%s\'\n", filename);
	VERIFY_CONTRACT(file_bin.good(), "Unable to open file \'%s\'\n", filename);
	read_line_from_file();
}


void Parser::read_line_from_file()
{
	VERIFY_CONTRACT(file_.good(), "File is invalid\n");
	VERIFY_CONTRACT(!file_.eof(), "EOF, cannot read line\n");

	file_.getline(line_, MAX_LINE_LEN);
	pos_ = line_;
	end_ = line_ + strlen(line_);

}

bool Parser::parse_pattern(std::regex regexp)
{

	std::cmatch match_result;

	bool is_success = std::regex_search(pos_, end_, match_result, regexp, std::regex_constants::match_continuous);

	if (is_success){
		
		pos_ = match_result[0].second;

	}

	return is_success;

}

bool Parser::parse_pattern(std::regex regexp, std::string& ret)
{

	std::cmatch match_result;

	bool is_success = std::regex_search(pos_, end_, match_result, regexp, std::regex_constants::match_continuous);

	if (is_success){
		
		pos_ = match_result[0].second;

		ret = std::string(match_result[0].first, match_result[0].second);

	}

	return is_success;

}


bool Parser::parse_space_seq()
{
	std::regex pat("([ \t]+|\\/\\/[^\n]*)+");

	return parse_pattern(pat);

}

bool Parser::parse_newline_seq()
{
	bool status = (pos_ == end_);

	while ((pos_ == end_) && !file_.eof())
	{
		read_line_from_file();
	}

	return status;

}

bool Parser::parse_value(Value_t& value, int number)
{
	parse_space_seq();

	std::regex pat("0|(\\+|-)?[1-9][0-9]*");

	std::string val;

	bool success = parse_pattern(pat, val);

	if (success){
		value = std::stoi(val);
	}
	else{
		std::string text_err = "ERROR: Invalid value in line: " + std::string(line_);
		std::cout << text_err << std::endl;
		exit(1);
	}

	return success;
}

bool Parser::parse_label_name(std::string& name)
{
	parse_space_seq();

	std::regex pat("[a-zA-Z0-9_]+");

	return parse_pattern(pat, name);

}

Reg_t Parser::parse_register(int number)
{
	parse_space_seq();

	std::regex pat("AX|BX|CX|DX|EX|FX|PC");
	std::string reg;
	bool success = parse_pattern(pat, reg);
	if (!success){
		std::string text_err = "ERROR: Invalid register name in line: " + std::string(line_);
		std::cout << text_err << std::endl;
		exit(1);
	}
	return reg_from_name_to_id(reg);
}

std::string Parser::parse_command_name(int number)
{
	std::regex pat("PUSHR|POPR|BEGIN|END|PUSH|POP|ADD|SUB|MUL|DIV|OUT|IN|JMP|JEQ|JNE|JAE|JA|JBE|JB|CALL|RET|[a-zA-Z0-9_]+:");
	std::string com;
	bool success = parse_pattern(pat, com);
	// std::cout<<com<<std::endl;
	if (!success){
		std::string text_err = "ERROR: Invalid command syntax in line: " + std::string(line_);
		std::cout << text_err << std::endl;
		exit(1);
	}
	return com;
}

void Parser::parse_command_line(Command*& ret, int& lbl_jmp_cmd, int number)
{
	parse_newline_seq();
	parse_space_seq();
	std::string name = parse_command_name(number);
	Cmd_t id = cmd_from_name_to_id(name);

	Value_t val;
	Reg_t rg;
	size_t len;

	switch (id){

	case cmd_id::BEGIN:
		ret = new CommandBEGIN(); 

		file_bin.write((char*) &id, sizeof(Cmd_t));

		break;

	case cmd_id::END:
		ret = new CommandEND();

		file_bin.write((char*) &id, sizeof(Cmd_t));
		
		break;

	case cmd_id::PUSH:
		ret = new CommandPUSH();
		parse_value(val, number);
		dynamic_cast<CommandPUSH*>(ret)->value = val;
		
		file_bin.write((char*) &id, sizeof(Cmd_t));
		file_bin.write((char*) &val, sizeof(Value_t));
		
		break;

	case cmd_id::POP:
		ret = new CommandPOP();
		
		file_bin.write((char*) &id, sizeof(Cmd_t));
		
		break;

	case cmd_id::PUSHR:
		ret = new CommandPUSHR();
		rg = parse_register(number);
		dynamic_cast<CommandPUSHR*>(ret)->reg_id = rg;

		file_bin.write((char*) &id, sizeof(Cmd_t));
		file_bin.write((char*) &rg, sizeof(Reg_t));
		
		break;

	case cmd_id::POPR:
		ret = new CommandPOPR();
		rg = parse_register(number);
		dynamic_cast<CommandPOPR*>(ret)->reg_id = rg;
		
		file_bin.write((char*) &id, sizeof(Cmd_t));
		file_bin.write((char*) &rg, sizeof(Reg_t));

		break;
	
	case cmd_id::ADD:
		ret = new CommandADD();

		file_bin.write((char*) &id, sizeof(Cmd_t));
		
		break;
	
	case cmd_id::SUB:
		ret = new CommandSUB();
		
		file_bin.write((char*) &id, sizeof(Cmd_t));

		break;
	
	case cmd_id::MUL:
		ret = new CommandMUL();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		break;
	
	case cmd_id::DIV:
		ret = new CommandDIV();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		break;
	
	case cmd_id::OUT:
		ret = new CommandOUT();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		break;
	
	case cmd_id::IN:
		ret = new CommandIN();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		break;
	
	case cmd_id::JMP:
		ret = new CommandJMP();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		lbl_jmp_cmd = 1;
		break;

	case cmd_id::JEQ:
		ret = new CommandJEQ();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		lbl_jmp_cmd = 1;
		break;

	case cmd_id::JNE:
		ret = new CommandJNE();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		lbl_jmp_cmd = 1;
		break;

	case cmd_id::JA:
		ret = new CommandJA();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		lbl_jmp_cmd = 1;
		break;

	case cmd_id::JAE:
		ret = new CommandJAE();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		lbl_jmp_cmd = 1;
		break;

	case cmd_id::JB:
		ret = new CommandJB();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		lbl_jmp_cmd = 1;
		break;

	case cmd_id::JBE:
		ret = new CommandJBE();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		lbl_jmp_cmd = 1;
		break;

	case cmd_id::CALL:
		ret = new CommandCALL();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		lbl_jmp_cmd = 1;
		break;

	case cmd_id::RET:
		ret = new CommandRET();

		file_bin.write((char*) &id, sizeof(Cmd_t));

		break;

	default:
		// parse_label_name(name);
		name.pop_back();
		lbl_jmp_cmd = 0;
		labels_list.push_back(std::pair<std::string, int>(name, number));
		id = cmd_id::label;
		file_bin.write((char*) &id, sizeof(Cmd_t));
		len = name.length()+1;
		file_bin.write((char*) &len, sizeof(len));
		file_bin.write((char*) name.c_str(), len);


	}

	if (lbl_jmp_cmd == 1){
		std::string label_name;
		parse_label_name(label_name);
		jumps_list.push_back(std::pair<std::string, int>(label_name, number));
		len = label_name.length()+1;
		file_bin.write((char*) &len, sizeof(len));
		file_bin.write((char*) label_name.c_str(), len);

	}
	parse_space_seq();
	parse_newline_seq();

} // parse_command


std::vector<Command*> Parser::parse_programm()
{
	std::vector<Command*> vec_cmd;
	Command* cm;
	int lbl_jmp_cmd = 2;
	int i = 0;
	while (!file_.eof())
	{
		lbl_jmp_cmd = 2;
		parse_command_line(cm, lbl_jmp_cmd, i);
		if (lbl_jmp_cmd != 0){
			vec_cmd.push_back(cm);
			i++;
		}
	}
	for (size_t i = 0; i < jumps_list.size(); i++){
		for (size_t j = 0; j < labels_list.size(); j++){
			if (jumps_list[i].first == labels_list[j].first){
				dynamic_cast<CommandJUMP*>(vec_cmd[jumps_list[i].second])->go_to = labels_list[j].second;
			}
		}
	}

	return vec_cmd;
}