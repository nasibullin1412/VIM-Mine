#ifndef _OBSERV_H_
#define _OBSERV_H_
#pragma once
#include <vector>
#include "adapterpdcur.h"

enum class ModeType : size_t
{
	EDIT_MODE,
	ENTER_SYM_MODE,
	ENTER_COM_MODE,
	SEARCH_MODE
};

enum class SpecialKeys
{
	CURSOR_UP,
	CURSOR_DOWN,
	CURSOR_RIGHT,
	CURSOR_LEFT
};


class Observer
{
public:
	virtual int		PrintScreen(MyString &text, const bool new_string, int index) = 0;
	virtual int 	UpdateKeys(MyString &string_, const SpecialKeys type) = 0;
	virtual int 	KeyUp() = 0;
	virtual int 	KeyDown() = 0;
	virtual int		KeyLeft() = 0;
	virtual int		KeyRight() = 0;
	


};

class Observable
{
public:
		~Observable();
	void	AddObserver(Observer* observer);
	int		NotifyUpdateKeys(MyString& string_, const SpecialKeys type_);
	int		NotifyPrintScreen(MyString& text, const bool new_string, int index);


private:
	std::vector<Observer*> _observers;
};


#endif