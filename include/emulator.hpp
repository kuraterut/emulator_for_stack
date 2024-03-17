#pragma once
#include <iostream>
#include <stdlib.h>
#include <regex>
#include <fstream>
#include <iterator>

#include "command.hpp"
#include "utils.hpp"
#include "myStack.hpp"



class Emulator{
public:
	std::vector<Command*> code;
	myStack<Value_t> stack;
	// myStack<Value_t> stack_calls;
	int registers[REG_NUM];
	bool mode;

	Emulator(const std::vector<Command*>& cmd_list);
	~Emulator();
	void run();
};