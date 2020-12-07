#ifndef _COMMODE_H_
#define _COMMODE_H_
#pragma once
#include "mainmode.h"

namespace commode
{
	constexpr size_t			number_of_check = 8;
	constexpr size_t			qw_nunber = 5;
	const std::array <MyString, number_of_check>check_commands = { "o", "x", "w", "q", "q!", "h"};
	constexpr int				not_found = -1;
	const MyString				help_string = "Here will be help information, developer is realy tired";
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
	MyString		new_file_;
	MyString		command_;
	bool			open_;
	bool			is_first_;

	bool			SaveToOtherFile();
	bool			SaveToFile();
	bool			ParseFile(const char special_symbol);
	bool			ReadFile();
	void			HelpInfo();
	
};


#endif
