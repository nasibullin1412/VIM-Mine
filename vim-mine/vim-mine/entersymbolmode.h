#ifndef _ENTERSYMBOLMODE_H_
#define _ENTERSYMBOLMODE_H_
#pragma once
#include "mainmode.h"


enum class SymbolModeActions
{
	INIT_VALUE,
	ENTER_SYMBOL_SMALL_I,
	ENTER_SYMBOL_BIG_I,
	ENTER_SYMBOL_A,
	ENTER_SYMBOL_S,
	ENTER_SYMBOL_R,
	DELETE_SYMBOL,
	NEW_STRING,
	EXIT
};

namespace entsym
{
	constexpr size_t number_of_check = 5;
	const std::array<MyString, number_of_check>check_commands = { "i", "I", "A", "S", "r" };
}


class EnterSymbolMode: public MainMode
{
public:
	EnterSymbolMode();
	~EnterSymbolMode();
	virtual bool HandleAction(MyString& command);
	virtual ModeType DoAction(int index);


private:
	SymbolModeActions		type_;
	bool					is_first;
	char					new_symbol_;
	int						index;
	void					EnterSymbol();
	void					NewString();
	void					DeleteSymbol();
};



#endif