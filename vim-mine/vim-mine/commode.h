#ifndef _COMMODE_H_
#define _COMMODE_H_
#pragma once
#include "mainmode.h"

namespace commode
{
	constexpr size_t number_of_check = 8;
	const std::array <MyString, number_of_check>check_commands = { "o", "x", "w", "q", "q!", "wq!", "number", "h"};
	constexpr int not_found = -1;
}


enum class ComAction
{
	INIT_VALUE,
	OPEN_FILE,
	SAVE_FILE_EXIT,
	SAVE_CUR_FILE,
	SAVE_TO_FILE,
	EXIT,
	EXIT_WITHOUT_SAVE,
	NUMBER,
	HELP,
	EXIT_FROM_THIS_MODE
};

class ComMode : public MainMode
{
public:
	ComMode();
	~ComMode();
	virtual bool		HandleAction(MyString& command);
	virtual ModeType	DoAction(int index);
	


private:
	ComAction		type_;
	MyString		file_;
	MyString		command_;
	bool			open_;
	bool			ParseFile(const char special_symbol);
	bool			OPenFile();

};


#endif
