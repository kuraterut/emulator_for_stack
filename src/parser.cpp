#include <iostream>
#include <stdlib.h>
#include <regex>
#include <fstream>
#include <iterator>
#include <cstdint>

#include "../include/parser.hpp"
#include "../include/command.hpp"
#include "../include/utils.hpp"



Parser::Parser(const char* filename):
	file_ (std::ifstream(filename, std::ios::in))
{	
	VERIFY_CONTRACT(file_.good(), "Unable to open file \'%s\'\n", filename);

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
		std::string text_err = "ERROR in command number: " + std::to_string(number+1) + ", Invalid value in line: " + std::string(line_);
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
		std::string text_err = "ERROR in command number: " + std::to_string(number+1) + ", Invalid register name in line: " + std::string(line_);
		std::cout << text_err << std::endl;
		exit(1);
	}
	return reg_from_name_to_id(reg);
}

std::string Parser::parse_command_name()
{
	std::regex pat("PUSHR|POPR|BEGIN|END|PUSH|POP|ADD|SUB|MUL|DIV|OUT|IN|[a-zA-Z0-9_]+:");
	std::string com;
	bool success = parse_pattern(pat, com);
	// if (!success){
	// 	std::cout << "ERROR: It's not a command and not a label: ";
	// 	std::cout << line_ << std::endl;
	// 	exit(1);
	// }
	return com;
}

void Parser::parse_command_line(Command*& ret, int& status, int number)
{
	parse_newline_seq();
	parse_space_seq();
	std::string name = parse_command_name();
	Cmd_t id = cmd_from_name_to_id(name);

	Value_t val;
	Reg_t rg;

	switch (id){
	case cmd_id::BEGIN:
		ret = new CommandBEGIN();
		break;
	case cmd_id::END:
		ret = new CommandEND();
		break;
	case cmd_id::PUSH:
		ret = new CommandPUSH();
		parse_value(val, number);
		dynamic_cast<CommandPUSH*>(ret)->value = val;
		// std::cout << ret << std::endl;
		break;

	case cmd_id::POP:
		ret = new CommandPOP();
		break;
	case cmd_id::PUSHR:
		ret = new CommandPUSHR();

		rg = parse_register(number);
		dynamic_cast<CommandPUSHR*>(ret)->reg_id = rg;

		break;
	case cmd_id::POPR:
		ret = new CommandPOPR();
		rg = parse_register(number);
		dynamic_cast<CommandPOPR*>(ret)->reg_id = rg;
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
	default:
		parse_label_name(name);
		if(name.length() != strlen(line_)){	
			std::string text_err = "ERROR in command number: " + std::to_string(number+1) + ", Invalid syntax in line: " + std::string(line_);
			std::cout << text_err << std::endl;
			exit(1);
		}
		status = 0;
	
	// case CMD_ID::JMP:
	// 	ret = new Cmd_JMP();
	// 	status = 1;
	// 	break;
	// case CMD_ID::JEQ:
	// 	ret = new Cmd_JEQ();
	// 	status = 1;
	// 	break;
	// case CMD_ID::JNE:
	// 	ret = new Cmd_JNE();
	// 	status = 1;
	// 	break;
	// case CMD_ID::JA:
	// 	ret = new Cmd_JA();
	// 	status = 1;
	// 	break;
	// case CMD_ID::JAE:
	// 	ret = new Cmd_JAE();
	// 	status = 1;
	// 	break;
	// case CMD_ID::JB:
	// 	ret = new Cmd_JB();
	// 	status = 1;
	// 	break;
	// case CMD_ID::JBE:
	// 	ret = new Cmd_JBE();
	// 	status = 1;
	// 	break;
	// case CMD_ID::CALL:
	// 	ret = new Cmd_CALL();
	// 	status = 1;
	// 	break;
	// case CMD_ID::RET:
	// 	ret = new Cmd_RET();
	// 	break;
	// default:
	// 	//ret = new Cmd_LABEL();
	// 	name.pop_back();

	// 	//dynamic_cast<Cmd_LABEL*>(ret)->name = name;
	// 	status = 0;
	// 	labels.push_back(std::pair<std::string, int>(name, number));

	}

	// if (status == 1){
	// 	std::string lbl;
	// 	parse_label_name(lbl);
	// 	jumps.push_back(std::pair<std::string, int>(lbl, number));
	// }

	parse_space_seq();
	parse_newline_seq();

} // parse_command


std::vector<Command*> Parser::parse_programm()
{
	std::vector<Command*> vec_cmd;
	Command* cm;
	int res = 2;
	int i = 0;
	while (!file_.eof())
	{
		res = 2;
		parse_command_line(cm, res, i);

		if (res)
		{
			vec_cmd.push_back(cm);
			i++;
		}
	}


	// for (size_t i = 0; i < jumps.size(); i++)
	// {
	// 	for (size_t j = 0; j < labels.size(); j++)
	// 	{
	// 		if (jumps[i].first == labels[j].first)
	// 		{
	// 			dynamic_cast<Cmd_JUMP*>(vec[jumps[i].second])->to = labels[j].second;
	// 		}
	// 	}
	// }

	return vec_cmd;
}