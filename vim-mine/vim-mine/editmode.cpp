#include "editmode.h"

EditMode::EditMode()
	: MainMode()
{
	this->type_ = ActionType::INIT_VALUE;
}

EditMode::~EditMode()
{
}

bool EditMode::HandleAction(MyString& command)
{
	size_t i = 0;
	for (i; i < editm::number_of_check; i++)
	{
		if (command.Find(editm::check_commands[i].CStr()) != editm::not_found)
		{
			break;
		}
	}
	++i;
	switch (i)
	{
	case 1:
		this->type_ = ActionType::MOVE_CURSOR_BEGIN_STRING;
		return true;
	case 2:
		this->type_ = ActionType::MOVE_CURSOR_END_STRING;
		return true;
	case 3:
		this->type_ = ActionType::MOVE_CURSOR_RIGHT_WORD_END;
		return true;
	case 4:
		this->type_ = ActionType::MOVE_CURSOR__LEFT_BEGIN;
		return true;
	case 5:
		this->type_ = ActionType::MOVE_CURSOR_BEGIN;
		return true;
	case 6:
		this->type_ = ActionType::MOVE_CURSOR_END;
		return true;
	case 7:
		this->type_ = ActionType::MOVE_CURSOR_TO_NSTRING;
		return true;
	case 8:
		this->type_ = ActionType::DELETE_SYMBOL_AFTER_CURSOR;
		return true;
	case 9:
		this->type_ = ActionType::DELETE_WORD;
		return true;
	case 10:
		this->type_ = ActionType::CUT_CUR_STRING;
		return true;
	case 11:
		this->type_ = ActionType::COPY_CUR_STRING;
		return true;
	case 12:
		this->type_ = ActionType::COPY_CUR_WORD;
		return true;
	case 13:
		this->type_ = ActionType::PASTE_AFTER_CURSOR;
		return true;
	case 14:
		this->type_ = ActionType::GO_TO_ENTER_MODE;
		return true;
	case 15:
		this->type_ = ActionType::GO_TO_ENTER_MODE;
		return true;
	case 16:
		this->type_ = ActionType::GO_TO_ENTER_MODE;
		return true;
	case 17:
		this->type_ = ActionType::GO_TO_ENTER_MODE;
		return true;
	case 18:
		this->type_ = ActionType::GO_TO_ENTER_MODE;
		return true;
	case 19:
		this->type_ = ActionType::GO_TO_COMMAND_MODE;
		return true;
	case 20:
		this->type_ = ActionType::GO_TO_FIND_MODE_TO_END;
		return true;
	case 21:
		this->type_ = ActionType::GO_TO_FIND_MODE_TO_BEGIN;
		return true;
	default:
		return false;
	}
}






ModeType EditMode::DoAction(int index)
{
	switch (this->type_)
	{
	case ActionType::GO_TO_ENTER_MODE:
	{
		return ModeType::ENTER_SYM_MODE;
	}
	case ActionType::GO_TO_COMMAND_MODE:
	{
		return ModeType::ENTER_COM_MODE;
	}
	default:
		break;
	}
	this->type_ = ActionType::INIT_VALUE;
	return ModeType::EDIT_MODE;
}




