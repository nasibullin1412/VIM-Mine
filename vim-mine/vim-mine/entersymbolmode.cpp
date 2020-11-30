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

ModeType EnterSymbolMode::DoAction()
{
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
        //this->NewString();
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
    //this->NotifyUpdate(tui_object, ModeType::ENTER_SYM_MODE);
    return ModeType::ENTER_SYM_MODE;
}

/*bool EnterSymbolMode::UpdateState()
{
    int x, y = 0;
    tui_object.PRefresh();
    tui_object.GetYX(y, x);
    this->plast_position_->x = x;
    this->plast_position_->y = y;
    if (*this->p_number_of_string_ != *this->p_string_number)
    {
        if (this->pcur_position_->x == winparam::weight)
        {
            tui_object.DownCursor(true, this->pcur_position_->y, this->pcur_position_->x);
        }
    }
    tui_object.WMove(this->pcur_position_->y, this->pcur_position_->x);
    tui_object.PRefresh();
    return false;
}
*/


void EnterSymbolMode::EnterSymbol()
{
    /*int x, y = 0;
    tui_object.GetYX(y, x);
    this->pcur_position_->x = x;
    this->pcur_position_->y = y;
    *this->p_index_ = this->p_symbol_map_->operator[](y)[x];
    if (*this->p_index_ == -1)
    {
        if (this->pcur_position_->y != 0 && x==0)
        {
            *this->p_index_ = this->p_symbol_map_->operator[](this->pcur_position_->y - 1)[winparam::n_postion] + 1;
        }
        else
        {
            if (x != 0)
            {
                *this->p_index_ = this->p_symbol_map_->operator[](y)[x-1] + 1;
            }
        }
    }
    if (*this->p_index_ == -1)
    {
        exit(-1);
    }*/
    //this->CountCurNumStrIndex(this->pcur_position_->x, this->pcur_position_->y);

    *this->p_index_ = this->NotifyCurPosition();

    this->text_->Insert(*this->p_index_, 1, this->new_symbol_);

    this->NotifyClearScreen();

    this->NotifyCheckNewLine();

 
    this->NotifyPrintScreen(*this->text_, false, *this->p_index_);
    this->NotifyDoRefreash();
    *this->p_index_ += 1;
    //this->NextCursorPos(tui_object, this->pcur_position_->y, this->pcur_position_->x);
    return;
}



/*void EnterSymbolMode::NewString(AdapterPDCur& tui_object)
{
    tui_object.GetYX(this->pcur_position_->y, this->pcur_position_->x);
    *this->p_index_ = this->p_symbol_map_->operator[](this->pcur_position_->y)[this->pcur_position_->x];
    
    int y = this->pcur_position_->y;
    int x = this->pcur_position_->x;

    bool shit = false;
    if (y != 0) //условие того что не первая линия
    {
        if (x == 0)// гарантирует то что в начале линнии
        {
            if (this->p_symbol_map_->operator[](y - 1)[winparam::n_postion] == -1) //гарантирует то что прошлая строка не закончилась
            {
                if (*this->p_index_ == this->text_->Length())//гарантирует то что крайняя позиция консоли
                {
                    shit = true;
                }

            }

        }
    }
    if (*this->p_index_ == -1)
    {
        if (y != 0)
        {
            *this->p_index_ = this->p_symbol_map_->operator[](y - 1)[winparam::n_postion] + 1;
        }
    }
    this->text_->Insert(*this->p_index_, "\r\n");
    tui_object.ClrToBot();
    if (shit)//если тот самый ужасный случай
    {
        this->p_symbol_map_->operator[](y)[0] = -1;
        this->p_symbol_map_->operator[](y - 1)[winparam::r_postion] = *this->p_index_;
        this->p_symbol_map_->operator[](y - 1)[winparam::n_postion] = *this->p_index_+1;
    }
    else
    {
        int temp = x;
        if (x != 0 || y != 0)
        {
            while (this->p_symbol_map_->operator[](y)[temp] != -1)
            {
                this->p_symbol_map_->operator[](y)[temp] = -1;
                temp++;
            }
        }
        if (*this->p_index_ == this->text_->Length() - 2)
        {
            this->p_symbol_map_->operator[](y)[winparam::r_postion] = *this->p_index_;
            this->p_symbol_map_->operator[](y)[winparam::n_postion] = *this->p_index_ + 1;
        }
        else
        {
            this->p_symbol_map_->operator[](y)[winparam::r_postion] = *this->p_index_ + 1;
            this->p_symbol_map_->operator[](y)[winparam::n_postion] = *this->p_index_ + 2;
        }
        std::vector<std::vector<int>>::iterator it;
        it = this->p_symbol_map_->begin();
        it += this->pcur_position_->y + 1;
        std::vector<int> new_line = this->CreateNewLine();
        this->p_symbol_map_->insert(it, new_line);
        this->PrintScreen(tui_object, true);
        tui_object.DownCursor(true, this->pcur_position_->y, this->pcur_position_->x);
    }


}
*/


/*void EnterSymbolMode::DeleteSymbol(AdapterPDCur& tui_object)
{
    /*tui_object.PrevCurPosition(this->pcur_position_->y, this->pcur_position_->x);
    this->CountCurNumStrIndex(this->pcur_position_->x, this->pcur_position_->y);
    tui_object.ClrToBot();
    this->ptext_->operator[](this->number_of_string_).Erase(this->index_, 1);*/
//    return;
//}

/*void EnterSymbolMode::PrintScreen(AdapterPDCur& tui_object, const bool new_string)
{
    size_t size = this->text_->Length();
    int x = this->pcur_position_->x;
    int y = this->pcur_position_->y;
    for (size_t i = *this->p_index_; i < size; i++)
    {
        char sym = this->text_->operator[](i);
        if (sym == '\r')
        {
            
            if (x != 0 || new_string)
            {
                tui_object.DownCursor(true, y, x);

            }
            ++i;
        }
        else
        {
            if (x == winparam::weight)
            {
                tui_object.DownCursor(true, y, x);
            }
            tui_object.MvwPrintw(y, x, sym);
            this->p_symbol_map_->operator[](y)[x] = i;
            this->NextCursorPos(tui_object, y, x);
        }
    }
    if (y < this->p_symbol_map_->size())
    {
        this->p_symbol_map_->operator[](y)[x] = static_cast<int>(size);
    }
}
*/
/*void EnterSymbolMode::PrintScreen(AdapterPDCur& tui_object, const bool new_string)
{
    size_t size = this->text_->Length();
    int x = this->pcur_position_->x;
    int y = this->pcur_position_->y;
    for (size_t i = *this->p_index_; i < size; i++)
    {
        char sym = this->text_->operator[](i);
        if (sym == '\r')
        {
            if (x != 0 || new_string)
            {
                this->p_symbol_map_->operator[](y)[winparam::r_postion] = i;
                this->p_symbol_map_->operator[](y)[winparam::n_postion] = i+1;
                tui_object.DownCursor(true, y, x);
            }
            else
            {
                this->p_symbol_map_->operator[](y-1)[winparam::r_postion] = i;
                this->p_symbol_map_->operator[](y-1)[winparam::n_postion] = i+1;
            }
            i++;
        }
        else
        {
            if (x == winparam::weight)
            {
                tui_object.DownCursor(true, y, x);
            }
            tui_object.MvwPrintw(y, x, sym);
            this->p_symbol_map_->operator[](y)[x] = i;
            this->NextCursorPos(tui_object, y, x);
        }
    }
    if (y < this->p_symbol_map_->size())
    {
        this->p_symbol_map_->operator[](y)[x] = static_cast<int>(size);
    }
}
*/