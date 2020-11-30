#ifndef _MAINMODE_H_
#define _MAINMODE_H_
#pragma once
#include "observ.h"
#include "mystring.h"
#include <vector>
#include <array>
#include <Windows.h>


namespace modeconst
{
	constexpr int special_key = -32;
	constexpr int escape_key = 27;
	constexpr int backspace_key = 58;
}

class MainMode : public Observable
{
public:
	MainMode();
	~MainMode();
	virtual bool HandleAction(MyString& command) = 0;
	virtual ModeType DoAction() = 0;
	
	void InitAllPointers(MyString* text, int* p_index_);
protected:
	MyString *text_;
	int* p_index_;
};


#endif