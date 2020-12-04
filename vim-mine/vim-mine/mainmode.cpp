#include "mainmode.h"

MainMode::MainMode()
{
	this->text_ = nullptr;
    this->index = nullptr;
    this->new_symbol_ = nullptr;
    this->r_insert_mode_ = nullptr;
    this->is_change_ = nullptr;
    this->number_string_ = 0;
}

MainMode::~MainMode()
{
}

void MainMode::InitAllPointers(MyString* text, bool* r_insert_mode, int* index, char* new_symbol, bool* change)
{
    this->text_ = text;
    this->r_insert_mode_ = r_insert_mode;
    this->index = index;
    this->new_symbol_ = new_symbol;
    this->is_change_ = change;
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
    *this->is_change_ = true;
}

void MainMode::GoToNumberString()
{
    size_t index = 0;
    size_t length = this->text_->Length();
    int count_strings = 0;
    while (index < length && count_strings != this->number_string_)
    {
        if (this->text_->operator[](index) == '\n')
        {
            ++count_strings;
        }
        ++index;
    }
    this->NotifySetCurYByIndex(*this->text_, index-1);
    this->NotifySetToBeginString(*this->text_);
}


void MainMode::EnterSymbol()
{
    this->text_->Insert(*this->index, 1, *this->new_symbol_);
    this->NotifyEnterSymbol(*this->text_);
    *this->is_change_ = true;
    return;
}

bool MainMode::IsNumber(MyString& number)
{
    size_t length = number.Length();
    size_t i = 0;
    if (length > symconst::max_length_number)
    {
        return false;
    }
    for (i; i < length; i++)
    {
        if (symconst::zero_code > number[i] || symconst::nine_code < number[i])
        {
            break;
        }
    }
    if (i != length)
    {
        return false;
    }
    
    this->number_string_ = atoi(number.CStr());
    return true;

}