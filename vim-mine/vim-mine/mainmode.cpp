#include "mainmode.h"

MainMode::MainMode()
{
	this->text_ = nullptr;
}

MainMode::~MainMode()
{
}

void MainMode::InitAllPointers(MyString* text)
{
    this->text_ = text;
}

