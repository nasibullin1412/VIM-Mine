#include "mainmode.h"

MainMode::MainMode()
{
	this->text_ = nullptr;
    this->index = nullptr;
    this->new_symbol_ = nullptr;
    this->r_insert_mode_ = nullptr;
}

MainMode::~MainMode()
{
}

void MainMode::InitAllPointers(MyString* text, bool* r_insert_mode, int* index, char* new_symbol)
{
    this->text_ = text;
    this->r_insert_mode_ = r_insert_mode;
    this->index = index;
    this->new_symbol_ = new_symbol;
}


void MainMode::DeleteSymbol()
{
    bool delete_line = false;
    if (*this->index != 0)
    {
        if (this->text_->operator[](*this->index - 1) == '\n')
        {
            delete_line = true;
        }
        this->text_->Erase(*this->index - 1, 1);
        this->NotifyDeleteSymbol(*this->text_, delete_line, *index);
    }
}


void MainMode::EnterSymbol()
{
    this->text_->Insert(*this->index, 1, *this->new_symbol_);
    this->NotifyEnterSymbol(*this->text_);
    return;
}

