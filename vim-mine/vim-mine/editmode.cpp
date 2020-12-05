#include "editmode.h"

EditMode::EditMode()
	: MainMode()
{
	this->type_ = ActionType::INIT_VALUE;
	this->copy_string_;
}

EditMode::~EditMode()
{
	this->copy_string_.~MyString();
}

bool EditMode::HandleAction(MyString& command)
{
	size_t i = 0;
	size_t length = command.Length() - 1;
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
		this->type_ = ActionType::DELETE_WORD;
		return true;
	case 4:
		this->type_ = ActionType::MOVE_CURSOR_LEFT_BEGIN;
		return true;
	case 5:
	{
		this->type_ = ActionType::MOVE_CURSOR_TO_NSTRING;
		length = command.Length() -1;
		size_t idx = 1;
		MyString number = command.Substr(length - idx, idx);
		while (this->IsNumber(number))
		{
			++idx;
			number = command.Substr(length - idx, idx);
		}
		return true;
	}
	case 6:
		this->type_ = ActionType::DELETE_SYMBOL_AFTER_CURSOR;
		return true;
	case 7:
		this->type_ = ActionType::COPY_CUR_WORD;
		return true;
	case 8:
		this->type_ = ActionType::CUT_CUR_STRING;
		return true;
	case 9:
	{
		if (command[length] != 'y')
		{
			command.Clear();
			return false;
		}
		this->type_ = ActionType::COPY_CUR_STRING;
		return true;
	}
	case 10:
		this->type_ = ActionType::MOVE_CURSOR_RIGHT_WORD_END;
		return true;
	case 11:
		this->type_ = ActionType::PASTE_AFTER_CURSOR;
		return true;
	case 12:
	{
		if (command[length-1] == 'd' || command[length] != 'i')
		{
			return false;
		}
		this->type_ = ActionType::GO_TO_ENTER_MODE;
		return true;
	}
	case 13:
		this->type_ = ActionType::GO_TO_ENTER_SYMBOL_BIG_I;
		return true;
	case 14:
		this->type_ = ActionType::ENTER_SYMBOL_A;
		return true;
	case 15:
		this->type_ = ActionType::ENTER_SYMBOL_S;
		return true;
	case 16:
		this->type_ = ActionType::ENTER_SYMBOL_R;
		return true;
	case 17:
		this->type_ = ActionType::GO_TO_COMMAND_MODE;
		return true;
	case 18:
		this->type_ = ActionType::GO_TO_FIND_MODE_TO_END;
		return true;
	case 19:
		this->type_ = ActionType::GO_TO_FIND_MODE_TO_BEGIN;
		return true;
	default:
		return false;
	}
}






ModeType EditMode::DoAction(int index)
{
	*this->index = index;
	switch (this->type_)
	{
	case ActionType::GO_TO_ENTER_MODE:
	{
		return ModeType::ENTER_SYM_MODE;
	}
	case ActionType::GO_TO_ENTER_SYMBOL_BIG_I:
	{
		this->InsertFromBeginString();
		return ModeType::ENTER_SYM_MODE;
	}
	case ActionType::ENTER_SYMBOL_A:
	{
		this->InsertFromEndString();
		return ModeType::ENTER_SYM_MODE;
	}

	case ActionType::ENTER_SYMBOL_S:
	{
		this->DeleteStringAndStartInsert();
		return ModeType::ENTER_SYM_MODE;
	}

	case ActionType::ENTER_SYMBOL_R:
	{
		*this->r_insert_mode_ = true;
		return ModeType::ENTER_SYM_MODE;
	}

	case ActionType::GO_TO_COMMAND_MODE:
	{
		return ModeType::ENTER_COM_MODE;
	}

	case ActionType::GO_TO_FIND_MODE_TO_BEGIN:
	{
		this->NotifySearchToBegin();
		return ModeType::SEARCH_MODE;
	}

	case ActionType::GO_TO_FIND_MODE_TO_END:
	{
		return ModeType::SEARCH_MODE;
	}

	case ActionType::MOVE_CURSOR_BEGIN_STRING:
	{
		this->NotifySetToBeginString(*this->text_);
		break;
	}

	case ActionType::MOVE_CURSOR_END_STRING:
	{
		this->NotifySetToEndString(*this->text_);
		break;
	}

	case ActionType::MOVE_CURSOR_RIGHT_WORD_END:
	{
		this->SetToRightWord();
		break;
	}
	case ActionType::MOVE_CURSOR_LEFT_BEGIN:
	{
		this->SetToLeftWord();
		this->NotifySetToWord(*this->text_, *this->index);
		break;
	}
	case ActionType::MOVE_CURSOR_TO_NSTRING:
	{
		this->GoToNumberString();
		break;
	}
	case ActionType::DELETE_SYMBOL_AFTER_CURSOR:
	{
		this->DeleteSymbolAfterCurs();
		break;
	}
	case ActionType::DELETE_WORD:
	{
		this->DeleteWord();
		break;
	}
	case ActionType::COPY_CUR_STRING:
	{
		this->CopyString();
		break;
	}
	case ActionType::CUT_CUR_STRING:
	{
		this->CutCurString();
		break;
	}
	case ActionType::COPY_CUR_WORD:
	{
		this->CopyCurWord();
		break;
	}
	case ActionType::PASTE_AFTER_CURSOR:
	{
		this->PasteAfterCursor();
		break;
	}
	default:
		break;
	}
	this->type_ = ActionType::INIT_VALUE;
	return ModeType::EDIT_MODE;
}


void EditMode::InsertFromBeginString()
{
	this->NotifySetToBeginString(*this->text_);
}

void EditMode::InsertFromEndString()
{
	this->NotifySetToEndString(*this->text_);
}

void EditMode::DeleteStringAndStartInsert()
{

	int size = static_cast<int>(this->text_->Length());
	while (*this->index < size && this->text_->operator[](*this->index) != '\n')
	{
		*this->index +=1;
	}
	this->NotifyDeleteStringPrep(*this->text_, *this->index);
	while (*this->index > 0 && this->text_->operator[](*this->index - 1) != '\n')
	{
		this->DeleteSymbol();
		*this->index -=1;
	}

}

void EditMode::SetToRightWord()
{
	size_t length = this->text_->Length();
	while (*this->index < length && (this->text_->operator[](*this->index+1) == '\n' || this->text_->operator[](*this->index+1) == ' '))
	{
		*this->index += 1;
	}
	if (*this->index != length)
	{
		*this->index += 1;
	}
	while (*this->index < length && this->text_->operator[](*this->index) != '\n' && this->text_->operator[](*this->index) != ' ')
	{
		*this->index += 1;
	}
	if (*this->index != length)
	{
		*this->index -= 1;
	}
	this->NotifySetToWord(*this->text_, *this->index);
}

void EditMode::SetToLeftWord()
{
	while (*this->index > 0 && (this->text_->operator[](*this->index - 1) == '\n' || this->text_->operator[](*this->index - 1) == ' '))
	{
		*this->index -= 1;
	}
	if (*this->index != 0)
	{
		*this->index -= 1;
	}
	while (*this->index > 0 && this->text_->operator[](*this->index) != '\n' && this->text_->operator[](*this->index) != ' ')
	{
		*this->index -= 1;
	}
	if (*this->index != 0)
	{
		*this->index += 1;
	}
	
}

void EditMode::DeleteSymbolAfterCurs()
{
	size_t length = this->text_->Length();
	if (*this->index == length-1)
	{
		return;
	}
	*this->index += 2;
	if (this->text_->operator[](*this->index - 1) == '\n')
	{
		return;
	}
	this->NotifySetCursRight();
	this->NotifyDoRefreash();
	this->NotifySetCursRight();
	this->NotifyDoRefreash();
	this->DeleteSymbol();
	this->NotifySetCursLeft();
	this->NotifyDoRefreash();
	*this->index += 1;
}




void EditMode::DeleteWord()
{
	size_t length = this->text_->Length();
	if (this->text_->operator[](*this->index) == '\n')
	{
		return;
	}
	if (this->text_->operator[](*this->index) == ' ')
	{
		while (*this->index < length && this->text_->operator[](*this->index) == ' ')
		{
			*this->index += 1;
			this->NotifySetCursRight();
		}
		while (*this->index > 0 && this->text_->operator[](*this->index - 1) == ' ')
		{
			this->DeleteSymbol();
			*this->index -= 1;
		}
	}
	else
	{
		while (*this->index < length && this->text_->operator[](*this->index) != ' ' && this->text_->operator[](*this->index) != '\n')
		{
			*this->index += 1;
			this->NotifySetCursRight();
			this->NotifyDoRefreash();
		}
		while (*this->index > 0 && this->text_->operator[](*this->index - 1) != ' ' && this->text_->operator[](*this->index - 1) != '\n')
		{
			this->DeleteSymbol();
			*this->index -= 1;
		}
	}
	
}

void EditMode::CopyString()
{
	if (!this->ComeToBeginString())
	{
		return;
	}
	int length = this->CountLengthString();
	if (length + *this->index == this->text_->Length())
	{
		this->copy_string_ = this->text_->Substr(*this->index, length);
		this->copy_string_.AppEnd(1, '\n');
		return;
	}
	this->copy_string_ = this->text_->Substr(*this->index, length + 1);
}

bool EditMode::ComeToBeginString()
{
	while (*this->index > 0 && this->text_->operator[](*this->index - 1) != '\n')
	{
		*this->index -= 1;
	}
	if (this->text_->operator[](*this->index) == '\n')
	{
		return false;
	}
	return true;
}

int EditMode::CountLengthString()
{
	int size = static_cast<int>(this->text_->Length());
	int idx = *this->index;
	int length = 0;
	while (idx+length < size && this->text_->operator[](idx+length) != '\n')
	{
		 ++length;
	}
	return length;
}

void EditMode::CutCurString()
{
	this->CopyString();
	this->DeleteStringAndStartInsert();
	this->NotifySetCursRight();
	this->DeleteSymbol();
}

void EditMode::CopyCurWord()
{
	if (this->text_->operator[](*this->index) == '\n' || this->text_->operator[](*this->index) == ' ')
	{
		return;
	}
	this->SetToLeftWord();
	int length = this->CountWordLength();
	this->copy_string_ = this->text_->Substr(*this->index, length);
}

int EditMode::CountWordLength()
{
	int size = static_cast<int>(this->text_->Length());
	int idx = *this->index;
	int length = 0;
	while (idx + length < size && this->text_->operator[](idx + length) != '\n' && this->text_->operator[](idx + length) != ' ')
	{
		++length;
	}
	return length;
}

void EditMode::PasteAfterCursor()
{
	if (this->copy_string_.Empty())
	{
		return;
	}
	int length = static_cast<int>(this->text_->Length());
	if (*this->index != length)
	{
		*this->index += 1;
		this->NotifyPastPreparation(this->copy_string_, *this->index);
		int length_copy = this->copy_string_.Length();
		for (size_t i = 0; i < length_copy; i++)
		{
			*this->new_symbol_ = this->copy_string_[i];
			this->EnterSymbol();
			*this->index += 1;
		}
		this->NotifySetToBeginString(*this->text_);
	}

}

