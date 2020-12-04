#include "commode.h"
#include<fstream>

ComMode::ComMode()
{
	this->type_ = ComAction::INIT_VALUE;
	this->open_ = false;
	this->file_;
	this->new_file_;
	this->is_first_ = true;
}

ComMode::~ComMode()
{
}

bool ComMode::HandleAction(MyString& command)
{
	this->command_ = command;
	MyString escape_;
	escape_.AppEnd(1, keys::key_escape);
	if (command_.Find(escape_.CStr()) != -1)
	{
		this->type_ = ComAction::EXIT_FROM_THIS_MODE;
		return true;
	}
	size_t i = 0;
	size_t length = this->command_.Length();
	for (size_t j = 0; j <= length; j++)
	{
		MyString sub_command = this->command_.Substr(0, j);
		for (i = 0; i < commode::number_of_check; i++)
		{
			if (sub_command.Find(commode::check_commands[i].CStr()) != commode::not_found)
			{
				break;
			}
		}
		if (i != commode::number_of_check)
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
		size_t length = command_.Length();
		if (command[length - 1] == 'w')
		{
			this->type_ = ComAction::SAVE_CUR_FILE;
			return true;
		}
		if (command.Find(commode::check_commands[commode::qw_nunber].CStr()) != commode::not_found)
		{
			this->type_ = ComAction::SAVE_FILE_EXIT;
			return true;
		}
		this->type_ = ComAction::SAVE_TO_FILE;
		return true;
	}
	case 4:
	{
		if (!*this->is_change_)
		{
			this->type_ = ComAction::EXIT;
			return true;
		}
		if (length > 1 && this->command_[length - 2] == 'q' && this->command_[length - 1] == '!')
		{
			this->type_ = ComAction::EXIT;
			return true;
		}
		break;
	}
	case 5:
	{
		this->type_ = ComAction::EXIT_WITHOUT_SAVE;
		return true;
	}
	case 6:
	{
		this->type_ = ComAction::HELP;
		return true;
	}
	default:
		break;
	}
	int idx = 0;
	if (this->is_first_)
	{
		idx = 1;
		this->is_first_ = false;
	}
	MyString number = command.Substr(idx);
	if (this->IsNumber(number))
	{
		this->type_ = ComAction::NUMBER;
		return true;
	}
	command.Clear();
	return false;
}

ModeType ComMode::DoAction(int index)
{
	this->is_first_ = false;
	switch (this->type_)
	{
	case ComAction::OPEN_FILE:
	{
		this->ReadFile();
		break;
	}
	case ComAction::SAVE_FILE_EXIT:
	{
		if (this->SaveToFile())
		{
			return ModeType::EXIT;
		}
		break;
	}
	case ComAction::SAVE_CUR_FILE:
	{
		this->SaveToFile();
		break;
	}
	case ComAction::SAVE_TO_FILE:
	{
		this->SaveToOtherFile();
		break;
	}
	case ComAction::EXIT:
	{
		return ModeType::EXIT;
	}

	case ComAction::NUMBER:
	{
		this->GoToNumberString();
		this->is_first_ = true;
		return ModeType::EDIT_MODE;
	}
	case ComAction::HELP:
	{
		this->HelpInfo();
		break;
	}
	case ComAction::EXIT_FROM_THIS_MODE:
	{
		this->is_first_ = true;
		return ModeType::EDIT_MODE;
	}
	default:
		break;
	}
	return ModeType::ENTER_COM_MODE;
}






bool ComMode::SaveToOtherFile()
{
	if (!this->ParseFile('w'))
	{
		return false;
	}
	if (!this->SaveToFile())
	{
		this->file_ = this->new_file_;
		return false;
	}
	this->NotifyChangeCurFileName(this->file_);
	*this->is_change_ = false;
	return true;
}

bool ComMode::SaveToFile()
{
	if (this->file_.Empty())
	{
		return false;
	}
	std::ofstream fout;
	fout.open(this->file_.CStr());
	if (!fout.is_open())
	{
		return false;
	}
	fout.write(this->text_->CStr(), this->text_->Length());
	fout.close();
	*this->is_change_ = false;
	return true;
}



bool ComMode::ParseFile(char special_symbol)
{
	size_t length = this->command_.Length();
	this->new_file_ = this->file_;
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

bool ComMode::ReadFile()
{
	*this->is_change_ = false;
	if (!this->ParseFile('o'))
	{
		return false;
	}
	std::ifstream fin;
	fin.open(this->file_.CStr());
	if (!fin.is_open())
	{
		this->file_ = this->new_file_;
		return false;
	}
	if (!this->text_->Empty())
	{
		return false;
	}
	int symbol = fin.get();
	while (!fin.eof())
	{
		if (symbol != '\r')
		{
			this->text_->AppEnd(1, symbol);
		}
		symbol = fin.get();
	}
	this->NotifyOpenFile(*this->text_, this->file_);
	return true;
}

void ComMode::HelpInfo()
{
	MyString help = commode::help_string;
	this->NotifyHelpInfo(help, *this->text_);
}


