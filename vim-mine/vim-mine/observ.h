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
	CURSOR_LEFT, 
	PG_UP,
	PG_DOWN,
	HOME,
	END
};


class Observer
{
public:
	virtual void	PrintScreen(MyString &text, const bool new_string, int index) = 0;
	virtual void	ClearScreen() = 0;
	virtual void	DoRefreash() = 0;
	virtual void	NextCur() = 0;
	virtual void	PrevCur() = 0;
	virtual void	NewString(MyString& text) = 0;
	virtual void    EnterSymbol(MyString& text) = 0;

};

class Observable
{
public:
		~Observable();
	void	AddObserver(Observer* observer);
	void	NotifyPrintScreen(MyString& text, const bool new_string, int index);
	void	NotifyClearScreen();
	void	NotifyDoRefreash();
	void	NotifyNextCurs();
	void	NotifyPrevCurs();
	void	NotifyNewString(MyString& text);
	void	NotifyEnterSymbol(MyString& text);


private:
	std::vector<Observer*> observers_;
};


#endif