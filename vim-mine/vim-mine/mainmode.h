#ifndef _MAINMODE_H_
#define _MAINMODE_H_
#pragma once
#include "observ.h"
#include "mystring.h"
#include <vector>
#include <array>





class MainMode : public Observable
{
public:
	MainMode();
	~MainMode();
	virtual bool HandleAction(MyString& command) = 0;
	virtual ModeType DoAction(int index) = 0;
	
	void InitAllPointers(MyString* text);
protected:
	MyString*	text_;

};


#endif