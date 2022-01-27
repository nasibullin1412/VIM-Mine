#ifndef _MAINMODE_H_
#define _MAINMODE_H_
#pragma once
#include "observ.h"
#include "mystring.h"
#include <vector>
#include <array>


namespace symconst
{
	constexpr char	 zero_code = '0';
	constexpr char	 nine_code = '9';
	constexpr size_t max_length_number = 6;
}


class MainMode : public Observable
{
public:
	MainMode();
	~MainMode();
	virtual bool HandleAction(MyString& command) = 0;
	virtual ModeType DoAction(int index) = 0;
	
	void InitAllPointers(MyString* text, bool* r_insert_mode, int *index, char* new_symbol, bool* change);
protected:
	MyString*	text_;
	bool*		r_insert_mode_;
	int*		index;
	char*		new_symbol_;
	bool*		is_change_;
	int			number_string_;

	bool		IsNumber(MyString& number);
	void		EnterSymbol();
	void		DeleteSymbol();
	void		GoToNumberString();
};


#endif