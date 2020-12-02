#include "commode.h"
#include<fstream>

ComMode::ComMode()
{
	this->type_ = ComAction::INIT_VALUE;
	this->open_ = false;
}

ComMode::~ComMode()
{
}

bool ComMode::HandleAction(MyString& command)
{
	this->command_ = command;
	if (command[0] == keys::key_escape)
	{
		this->type_ = ComAction::EXIT_FROM_THIS_MODE;
		return true;
	}
	size_t i = 0;
	for (i; i < commode::number_of_check; i++)
	{
		if (this->command_.Find(commode::check_commands[i].CStr()) != commode::not_found)
		{
			break;
		}
	}
	++i;
	switch (i)
	{
	case 1:
	{
		this->type_ = ComAction::OPEN_FILE;
		return true;

	}
	case 2:
	{
		this->type_ = ComAction::SAVE_FILE_EXIT;
		return true;
	}
	case 3:
	{
		this->type_ = ComAction::SAVE_CUR_FILE;
		return true;
	}
	case 4:
	{
		this->type_ = ComAction::SAVE_TO_FILE;
		return true;
	}
	case 5:
	{
		this->type_ = ComAction::EXIT;
		return true;
	}
	case 6:
	{
		this->type_ = ComAction::EXIT_WITHOUT_SAVE;
		return true;
	}
	case 7:
	{
		this->type_ = ComAction::NUMBER;
		return true;
	}
	case 8:
	{
		this->type_ = ComAction::HELP;
		return true;
	}
	default:
		break;
	}
	return false;
}

ModeType ComMode::DoAction(int index)
{
	switch (this->type_)
	{
	case ComAction::OPEN_FILE:
	{
		this->OPenFile();
		break;
	}
	case ComAction::SAVE_FILE_EXIT:
	{
		break;
	}
	case ComAction::SAVE_CUR_FILE:
	{
		break;
	}
	case ComAction::SAVE_TO_FILE:
	{
		break;
	}
	case ComAction::EXIT_WITHOUT_SAVE:
	{
		break;
	}
	case ComAction::NUMBER:
	{
		break;
	}
	case ComAction::HELP:
	{
		break;
	}
	case ComAction::EXIT_FROM_THIS_MODE:
	{
		return ModeType::EDIT_MODE;
	}
	default:
		break;
	}
	return ModeType::ENTER_COM_MODE;
}

bool ComMode::ParseFile(char special_symbol)
{
	size_t length = this->command_.Length();
	if (this->command_[length - 1] == special_symbol)
	{
		return false;
	}

	for (size_t i = 0; i < length; i++)
	{
		if (this->command_[i] == special_symbol)
		{
			this->file_ = this->command_.Substr(i+2);
			break;
		}
	}
	return true;
}

bool ComMode::OPenFile()
{
	if (!this->ParseFile('o'))
	{
		return false;
	}
	std::ifstream fin;
	fin.open(this->file_.CStr());
	if (!fin.is_open())
	{
		return false;
	}
	if (!this->text_->Empty())
	{
		return false;
	}
	int symbol = fin.get();
	while (!fin.eof())
	{
		this->text_->AppEnd(1, symbol);
		symbol = fin.get();
	}
	this->NotifyOpenFile(*this->text_, this->file_);
	return true;
}
