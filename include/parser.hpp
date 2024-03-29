#pragma once
#include <fstream>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <regex>
#include <vector>

#include "command.hpp"

class Parser{
public:
	
	Parser() = delete;

	Parser(const Parser& parser) = delete;
	Parser(Parser&& parser) = default;

	Parser& operator=(const Parser& parser) = delete;
	Parser& operator=(Parser&& parser) = default;

	Parser(const char* filename, const char* file_bin_name);

	std::vector<Command*> parse_programm();

private:
	std::ofstream file_bin;
	std::ifstream file_;
	const char* pos_;
	const char* end_;
	char line_[MAX_LINE_LEN];
	std::vector<std::pair<std::string, int>> labels_list;
	std::vector<std::pair<std::string, int>> jumps_list;

	void read_line_from_file();
	
	void parse_command_line(Command*& ret, int& status, int number);

	bool parse_pattern(std::regex regexp);
	bool parse_pattern(std::regex regexp, std::string& ret);
	
	std::string parse_command_name(int number);
	
	Reg_t parse_register(int number);
	bool parse_value(Value_t& val, int number);

	bool parse_label_name(std::string& name);

	bool parse_space_seq();
	bool parse_newline_seq();

};