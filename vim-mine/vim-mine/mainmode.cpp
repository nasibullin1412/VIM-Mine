#include "mainmode.h"

MainMode::MainMode()
{
	this->text_ = nullptr;
    this->p_index_ = nullptr;

}

MainMode::~MainMode()
{
}

void MainMode::InitAllPointers(MyString* text, int* p_index_)
{
    this->p_index_ = p_index_;
    this->text_ = text;
}

