#ifndef _EDIT_H_
#define _EDIT_H_
#pragma once
#include "mainmode.h"




enum class ActionType
{
	INIT_VALUE,
	MOVE_CURSOR_BEGIN_STRING,
	MOVE_CURSOR_END_STRING,
	MOVE_CURSOR_RIGHT_WORD_END,
	MOVE_CURSOR__LEFT_BEGIN,
	MOVE_CURSOR_BEGIN,
	MOVE_CURSOR_END,
	MOVE_CURSOR_TO_NSTRING,
	DELETE_SYMBOL_AFTER_CURSOR,
	DELETE_WORD,
	CUT_CUR_STRING,
	COPY_CUR_STRING,
	COPY_CUR_WORD,
	PASTE_AFTER_CURSOR,
	GO_TO_ENTER_MODE,
	GO_TO_COMMAND_MODE,
	GO_TO_FIND_MODE_TO_END,
	GO_TO_FIND_MODE_TO_BEGIN,
};

namespace editm
{
	constexpr size_t number_of_check = 23;
	const std::array < MyString, number_of_check>check_commands = { "^", "$", "w", "b", "gg", "G", "NG", "x", "diw",
	"dd", "y", "yw", "p", "i", "I", "A", "S", "r", ":", "/", "?"};
	
	constexpr int not_found = -1;
}
class EditMode: public MainMode
{
public:
	EditMode();
	~EditMode();
	virtual bool HandleAction(MyString &command);
	virtual ModeType DoAction(int index);
private:
	ActionType type_;
	
};

#endif