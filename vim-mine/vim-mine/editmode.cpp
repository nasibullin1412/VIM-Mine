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
	int com = command[0];
	switch (com)
	{
	case keys::key_up:
		this->type_ = ActionType::CURSOR_UP;
		return true;
	case keys::key_pg_up:
		this->type_ = ActionType::MOVE_CURSOR_UP;
		return true;
	case keys::key_pg_down:
		this->type_ = ActionType::MOVE_CURSOR_DOWN;
		return true;
	case keys::key_left:
		this->type_ = ActionType::CURSOR_LEFT;
		return true;
	case keys::key_right:
		this->type_ = ActionType::CURSOR_RIGHT;
		return true;
	case keys::key_down:
		this->type_ = ActionType::CURSOR_DOWN;
		return true;
	default:
		break;
	}
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






ModeType EditMode::DoAction()
{
	switch (this->type_)
	{
	case ActionType::CURSOR_UP:
	{
		*this->p_index_ = this->NotifyUpdateKeys(*this->text_, SpecialKeys::CURSOR_UP);
		break;
	}
	case ActionType::CURSOR_DOWN:
	{
		*this->p_index_ = this->NotifyUpdateKeys(*this->text_, SpecialKeys::CURSOR_DOWN);
		break;
	}
	case ActionType::CURSOR_LEFT:
	{
		*this->p_index_ = this->NotifyUpdateKeys(*this->text_, SpecialKeys::CURSOR_LEFT);
		break;
	}
	case ActionType::CURSOR_RIGHT:
	{
		*this->p_index_ = this->NotifyUpdateKeys(*this->text_, SpecialKeys::CURSOR_RIGHT);
		break;
	}
	case ActionType::MOVE_CURSOR_UP:
	{
		cout << "U";
		break;
	}
	case ActionType::MOVE_CURSOR_DOWN:
	{
		cout << "D";
		break;
	}
	case ActionType::GO_TO_ENTER_MODE:
	{
		return ModeType::ENTER_SYM_MODE;
	}
	default:
		break;
	}
	this->type_ = ActionType::INIT_VALUE;
	return ModeType::EDIT_MODE;
}




