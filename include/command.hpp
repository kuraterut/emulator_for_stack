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
		virtual ~Command() {}
		virtual void execute(Emulator* emulator) = 0;
		// ~Command() = default;
};

class CommandBEGIN : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandBEGIN() override;
};

class CommandEND : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandEND() override;
};

class CommandPUSH : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandPUSH() override;
		Value_t value;
};

class CommandPOP : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandPOP() override;
};

class CommandPUSHR : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandPUSHR() override;
		Reg_t reg_id;
};

class CommandPOPR : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandPOPR() override;
		Reg_t reg_id;
};

class CommandADD : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandADD() override;
};

class CommandSUB : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandSUB() override;
};

class CommandMUL : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandMUL() override;
};

class CommandDIV : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandDIV() override;
};

class CommandOUT : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandOUT() override;
};

class CommandIN : public Command{
	public:
		virtual void execute(Emulator* emulator) override;
		// virtual ~CommandIN() override;
};