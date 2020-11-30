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
}

bool Controller::InfoController(const int index, const char symbol)
{
	this->command_.AppEnd(1, symbol);
	if (this->model_->operator[](static_cast<size_t>(this->mode_type_))->HandleAction(this->command_))
	{
		ModeType temp_type = this->model_->operator[](static_cast<size_t>(this->mode_type_))->DoAction(index);
		this->ChangeType(temp_type);
	}
	return false;
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
