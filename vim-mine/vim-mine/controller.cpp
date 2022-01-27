#include "controller.h"
#include "Windows.h"
#include <iostream>
#include <string>




Controller::Controller(std::vector<MainMode*>* model)
{
	this->model_ = model;
	this->mode_type_ = ModeType::EDIT_MODE;
	this->command_;
}

Controller::~Controller()
{
	this->command_.~MyString();
}

ModeType Controller::InfoController(const int index, MyString& command)
{
	this->command_.AppEnd(command.CStr());
	if (this->model_->operator[](static_cast<size_t>(this->mode_type_))->HandleAction(this->command_))
	{
		ModeType temp_type = this->model_->operator[](static_cast<size_t>(this->mode_type_))->DoAction(index);
		this->ChangeType(temp_type);
	}
	return this->mode_type_;
}



void Controller::ChangeType(const ModeType& new_mode)
{
	if (this->mode_type_ == new_mode)
	{
		if (this->mode_type_ == ModeType::EDIT_MODE)
		{
			size_t length = command_.Length();
			if (this->command_[length-1] == 'y')
			{
				return;
			}
		}
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
