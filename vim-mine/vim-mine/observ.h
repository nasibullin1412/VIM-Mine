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
	SEARCH_MODE,
	EXIT
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

	virtual void	DoRefreash() = 0;
	virtual void	NextCur() = 0;
	virtual void	PrevCur() = 0;
	virtual void	NewString(MyString& text) = 0;
	virtual void    EnterSymbol(MyString& text) = 0;
	virtual void	DeleteSymbol(MyString& text, bool delete_line, const int index) = 0;
	virtual void	OpneFile(MyString& text, MyString& file_name) = 0;
	virtual void	SetToBeginString(MyString& text) = 0;
	virtual void	SetToEndString(MyString& text) = 0;
	virtual void	DeleteStringPrep(MyString& text, const int index) = 0;
	virtual void	ChangeOneSymbol() = 0;
	virtual void	ChangeCurFileName(MyString& file_name) = 0;
	virtual void	SetCurYByIndex(MyString& text, const int index) = 0;
	virtual void	HelpInfo(MyString& help_info, MyString& text) = 0;
	virtual void	SearchWord(MyString& text, const int index) = 0;
	virtual void	SearchToBegin() = 0;
	virtual void	SetCursToWord(MyString& text, const int index) = 0;
	virtual void	SetCursRight() = 0;
	virtual void	SetCursLeft() = 0;
	virtual void    PastPreparation(MyString& copy_line, const int index) = 0;
};

class Observable
{
public:
		~Observable();
	void	AddObserver(Observer* observer);
	void	NotifyDoRefreash();
	void	NotifyNewString(MyString& text);
	void	NotifyEnterSymbol(MyString& text);
	void	NotifyDeleteSymbol(MyString& text, bool delete_line, const int index);
	void	NotifyOpenFile(MyString& text, MyString& file_name);
	void	NotifySetToBeginString(MyString& text);
	void	NotifySetToEndString(MyString& text);
	void	NotifyDeleteStringPrep(MyString& text, const int index);
	void	NotifyChangeOneSymbol();
	void	NotifyChangeCurFileName(MyString& file_name);
	void    NotifySetCurYByIndex(MyString& text, const int index);
	void	NotifyHelpInfo(MyString& help_info, MyString& text);
	void	NotifySearchWord(MyString& text, const int index);
	void	NotifySearchToBegin();
	void	NotifySetToWord(MyString& text, const int index);
	void	NotifySetCursRight();
	void	NotifySetCursLeft();
	void    NotifyPastPreparation(MyString& copy_line, const int index);

private:
	std::vector<Observer*> observers_;
};


#endif