#include "EnterSymbolMode.h"
#include <Windows.h>



EnterSymbolMode::EnterSymbolMode()
    : MainMode()
{
    this->type_ = SymbolModeActions::INIT_VALUE;
    this->is_first = true;
}

EnterSymbolMode::~EnterSymbolMode()
{
}

bool EnterSymbolMode::HandleAction(MyString& command)
{
    size_t idx = 0;
    if (this->is_first)
    {
        idx = 1;
        this->is_first = false;
    }
    *this->new_symbol_ = command[idx];
    switch (command[idx])
    {
    case keys::key_escape:
    {
        this->type_ = SymbolModeActions::EXIT;
        return true;
    }
    case keys::key_backspace:
    {
        this->type_ = SymbolModeActions::DELETE_SYMBOL;
        return true;
    }
    case keys::key_enter:
    {
        this->type_ = SymbolModeActions::NEW_STRING;
        return true;
    }
    default:
        break;
    }
    this->type_ = SymbolModeActions::ENTER_SYMBOL_SMALL_I;
    return true;
}



ModeType EnterSymbolMode::DoAction(int index)
{
    *this->index = index;
    switch (this->type_)
    {
    case SymbolModeActions::ENTER_SYMBOL_SMALL_I:
    {
        if (*this->r_insert_mode_)
        {
            this->ChangeOneSymbol();
            *this->r_insert_mode_ = false;
            this->is_first = true;
            return ModeType::EDIT_MODE;
        }
        this->EnterSymbol();
        break;
    }
    case SymbolModeActions::DELETE_SYMBOL:
    {
        this->DeleteSymbol();
        break;
    }
    case SymbolModeActions::NEW_STRING:
    {
        this->NewString();
        break;
    }
    case SymbolModeActions::EXIT:
    {
        this->is_first = true;
        return ModeType::EDIT_MODE;
    }
    default:
        break;
    }
    return ModeType::ENTER_SYM_MODE;
}


void EnterSymbolMode::NewString()
{
    *this->is_change_ = true;
    this->text_->Insert(*this->index, "\n");
    this->NotifyNewString(*this->text_);
    this->NotifyDoRefreash();
}

void EnterSymbolMode::ChangeOneSymbol()
{
    if (*this->index == this->text_->Length())
    {
        return;
    }
    if (this->text_->operator[](*this->index) == '\n')
    {
        return;
    }
    *this->index += 1;
    this->DeleteSymbol();
    *this->index -= 1;
    this->EnterSymbol();
    this->NotifyChangeOneSymbol();
}


