#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>

typedef int Value_t;
typedef uint8_t Reg_t;
typedef uint8_t Cmd_t;

#define MAX_LINE_LEN 100

extern std::vector<std::string> reg_names, cmd_names;

Reg_t reg_from_name_to_id(std::string name);
Cmd_t cmd_from_name_to_id(std::string name);

enum cmd_id: Cmd_t{
	BEGIN,
	END,
	PUSH,
	POP,
	PUSHR,
	POPR,
	ADD,
	SUB,
	MUL,
	DIV,
	OUT,
	IN	
};


class Emulator;

class Command{
	public: 
		virtual void execute(Emulator* emulator) = 0;
};

class CommandBEGIN : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
};

class CommandEND : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
};

class CommandPUSH : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		Value_t value;
};

class CommandPOP : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
};

class CommandPUSHR : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		Reg_t reg_id;
};

class CommandPOPR : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		Reg_t reg_id;
};

class CommandADD : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
};

class CommandSUB : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
};

class CommandMUL : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
};

class CommandDIV : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
};

class CommandOUT : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
};

class CommandIN : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
};