#include "controller.h"
#include "Windows.h"
#include <iostream>
#include <string>




Controller::Controller(std::vector<MainMode*>* model, AdapterPDCur &tui_object)
{
	this->model_ = model;
	this->tui_object = tui_object;
	this->mode_type_ = ModeType::EDIT_MODE;
	this->command_;
}

Controller::~Controller()
{
}




void Controller::start()
{
	
	this->tui_object.InitScr();
	this->tui_object.NewPad(winparam::real_size, winparam::weight);
	this->tui_object.PRefresh();
	this->tui_object.Keypad(true);
	while (true)
	{
		this->ReadSymbol();
		switch (this->mode_type_)
		{
		case ModeType::EDIT_MODE:
		{
			if (this->model_->operator[](static_cast<size_t>(ModeType::EDIT_MODE))->HandleAction(this->command_, this->tui_object))
			{
				ModeType temp_type = this->model_->operator[](static_cast<size_t>(ModeType::EDIT_MODE))->DoAction(this->tui_object);
				this->ChangeType(temp_type);
			}
			break;
		}
		case ModeType::ENTER_COM_MODE:
		{

		}
		case ModeType::SEARCH_MODE:
		{

		}
		case ModeType::ENTER_SYM_MODE:
		{
			if (this->model_->operator[](static_cast<size_t>(ModeType::ENTER_SYM_MODE))->HandleAction(this->command_, this->tui_object))
			{
				ModeType temp_type = this->model_->operator[](static_cast<size_t>(ModeType::ENTER_SYM_MODE))->DoAction(this->tui_object);
				this->ChangeType(temp_type);
			}
		}
		default:
			break;
		}
	}
	return;
}

bool Controller::ReadSymbol()
{
	this->tui_object.NoEcho();
	int symbol = 0;
	symbol = this->tui_object.GetCh();
	this->tui_object.Echo();
	this->command_.AppEnd(1, static_cast<char>(symbol));
	return true;
}

void Controller::ChangeType(const ModeType& new_mode)
{
	if (this->mode_type_ == new_mode)
	{
		this->command_.~MyString();
		return;
	}
	this->mode_type_ = new_mode;
	if (this->mode_type_ == ModeType::EDIT_MODE)
	{
		this->command_.Clear();
		this->command_.ShrinkToFit();
		return;
	}
	size_t length = command_.Length();
	length -= 1;
	command_.Erase(0, length);
	command_.ShrinkToFit();
}
