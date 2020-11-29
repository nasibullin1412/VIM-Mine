#include "mainmode.h"

MainMode::MainMode(MyString* text, Position* plast_position, Position* pcur_position, std::vector<size_t>* p_indexes_of_strings)
{
	this->text_ = text;
	this->plast_position_ = plast_position;
	this->pcur_position_ = pcur_position;
	this->change_ = false;
	this->p_number_of_string_ = nullptr;
	this->p_string_number = nullptr;
	this->p_indexes_of_strings_ = p_indexes_of_strings;
    this->p_index_ = nullptr;
    this->p_symbol_map_ = nullptr;
}

MainMode::~MainMode()
{
}

void MainMode::InitAllPointers(size_t* p_number_of_string, size_t* p_string_numb, int* p_index, std::vector<std::vector<int>> *p_symbol_map)
{
    this->p_number_of_string_ = p_number_of_string;
    this->p_string_number = p_string_numb;
    this->p_index_ = p_index;
    this->p_symbol_map_ = p_symbol_map;
}

MyString MainMode::GetText()
{
	//return ptext_->Substr(0);
	return 0;
}

bool MainMode::UpdateIndexes(size_t start_string, int value_update)
{
	size_t value_ = 0;
	bool natural = false;
	if (value_update < 0)
	{
		value_ = static_cast<size_t>(-value_update);
	}
	else
	{
		value_ = static_cast<size_t>(value_update);
		natural = true;
	}
	for (size_t i = start_string; i < *this->p_string_number; i++)
	{
		if (this->p_indexes_of_strings_->operator[](i) > value_)
		{
			if (natural)
			{
				this->p_indexes_of_strings_->operator[](i) += value_;
			}
			else
			{
				this->p_indexes_of_strings_ -= value_;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

/*
void MainMode::NextCursorPos(AdapterPDCur& tui_object, int& y, int& x)
{
    if (x == winparam::weight - 1)
    {
        tui_object.DownCursor(true, y, x);
    }
    else
    {
        ++x;
    }
    tui_object.WMove(y, x);
}

void MainMode::PrevCursorPos(AdapterPDCur& tui_object, int& y, int& x)
{
    if (x == 0)
    {
        tui_object.UpCursor(true, y, x);
    }
    else
    {
        --x;
    }
    tui_object.WMove(y, x);
}

*/


/*void MainMode::CountCurNumStrIndex(const int cur_x, const int cur_y)
{
    this->number_of_string_ = 0;
    int count_console_line = 0;
    int length_string = 0;
    int summary_index = 0;
    int check = 0;
    bool kostyl = false;
    int is_use = 0;
    if (this->string_number > 0)
    {
        length_string = this->p_indexes_of_strings_->operator[](this->number_of_string_);
        check = length_string - 2;
        while (length_string != 0 && ((cur_y - count_console_line) * winparam::weight + cur_x) >= check)
        {
            if (check == (cur_y - count_console_line) * winparam::weight + cur_x)
            {
                if (cur_x != 0)
                {
                    break;
                }
                if (this->number_of_string_ == this->string_number)
                {
                    break;
                }
                if (check == 0 && kostyl)
                {
                    break;
                }
            }
            this->number_of_string_++;
            summary_index += check;
            count_console_line += check / winparam::weight;
            if ((check % winparam::weight || check == 0) && count_console_line != cur_y)
            {
                ++count_console_line;
            }
            if (this->number_of_string_ < this->string_number)
            {
                length_string = this->p_indexes_of_strings_->operator[](this->number_of_string_) - this->p_indexes_of_strings_->operator[](this->number_of_string_ - 1);
                check = length_string - 2;
                kostyl = true;
            }
            else
            {
                length_string = this->text_->Length() - this->p_indexes_of_strings_->operator[](this->number_of_string_ - 1);
                check = length_string;
                kostyl = false;
            }

        }
        summary_index += (cur_y - count_console_line) * winparam::weight + cur_x;

 

        summary_index += (this->number_of_string_) * 2;
        this->index_ = summary_index;
    }
    else
    {
        this->index_ = cur_y * winparam::weight + cur_x;
    }
}
*/


