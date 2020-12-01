#include "EnterSymbolMode.h"
#include <Windows.h>



EnterSymbolMode::EnterSymbolMode()
    : MainMode()
{
    this->type_ = SymbolModeActions::INIT_VALUE;
    this->is_first = true;
    this->new_symbol_ = 0;
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
    this->new_symbol_ = command[idx];
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
    if (idx == 0 )
    {
        this->type_ = SymbolModeActions::ENTER_SYMBOL_SMALL_I;
        return true;
    }
    switch (command[0])
    {
    case 'i':
    {
        this->type_ = SymbolModeActions::ENTER_SYMBOL_SMALL_I;
        return true;
    }
    case 'I':
    {
        this->type_ = SymbolModeActions::ENTER_SYMBOL_BIG_I;
        return true;
    }
    case 'A':
    {
        this->type_ = SymbolModeActions::ENTER_SYMBOL_A;
        return true;
    }
    case 'S':
    {
        this->type_ = SymbolModeActions::ENTER_SYMBOL_S;
        return true;
    }
    case 'r':
    {
        this->type_ = SymbolModeActions::ENTER_SYMBOL_R;
        return true;
    }
    default:
        return false;
    }
}



ModeType EnterSymbolMode::DoAction(int index)
{
    this->index = index;
    switch (this->type_)
    {
    case SymbolModeActions::ENTER_SYMBOL_SMALL_I:
    {
        this->EnterSymbol();
        break;
    }
    case SymbolModeActions::DELETE_SYMBOL:
    {
        //this->DeleteSymbol();
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




void EnterSymbolMode::EnterSymbol()
{
    this->text_->Insert(this->index, 1, this->new_symbol_);
    this->NotifyEnterSymbol(*this->text_);
    return;
}



void EnterSymbolMode::NewString()
{
    this->text_->Insert(this->index, "\n");
    this->NotifyNewString(*this->text_);
    this->NotifyDoRefreash();
}
