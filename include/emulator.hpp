#pragma once
#include <iostream>
#include <stdlib.h>
#include <regex>
#include <fstream>
#include <iterator>

#include "command.hpp"
#include "utils.hpp"
#include "myStack.hpp"

#define REG_NUM 7

class Emulator{
public:
	std::vector<Command*> code;
	myStack<Value_t> stack;
	int registers[REG_NUM];
	bool mode;

	Emulator(const std::vector<Command*>& cmd_list);
	~Emulator();
	void run();
};