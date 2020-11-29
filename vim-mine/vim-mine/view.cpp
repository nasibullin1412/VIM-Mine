#include "view.h"
#pragma once

ConsoleView::ConsoleView(std::vector<MainMode*> *model)
{
	model->operator[](0)->AddObserver(this);
	model->operator[](1)->AddObserver(this);

	this->tui_object = nullptr;
	this->p_symbol_map_ = nullptr;
	this->p_cur_position_ = nullptr;
	this->p_last_position_ = nullptr;
	this->p_cur_position_ = nullptr;
	//this->model_->operator[](2)->AddObserver(this);
	//this->model_->operator[](3)->AddObserver(this);
}

ConsoleView::~ConsoleView()
{
}

void ConsoleView::InitAllPointers(AdapterPDCur* tui_object, std::vector<std::vector<int>>* p_symbol_map,int *P_cur_position, Position* p_last_position_, Position* p_cur_position_)
{
	this->tui_object = tui_object;
	this->p_symbol_map_ = p_symbol_map;
	this->p_cur_position_ = p_cur_position_;
	this->p_last_position_ = p_last_position_;
	this->p_cur_position_ = p_cur_position_;


}

int ConsoleView::UpdateKeys(MyString &string_, const SpecialKeys type)
{
	int index = 0;
	switch (type)
	{
	case SpecialKeys::CURSOR_UP:
	{
		index = this->KeyUp();
		break;
	}
	case SpecialKeys::CURSOR_DOWN:
	{
		index = this->KeyDown();
		break;
	}
	case SpecialKeys::CURSOR_RIGHT:
	{
		index = this->KeyRight();
		break;
	}
	case SpecialKeys::CURSOR_LEFT:
	{
		index = this->KeyLeft();
		break;
	}
	default:
		break;
	}
	return index;
}


int ConsoleView::KeyUp()
{
	this->tui_object->GetYX(this->p_cur_position_->y, this->p_cur_position_->x);
	this->UpCursor(false, this->p_cur_position_->y, this->p_cur_position_->x);
	while (this->p_cur_position_->x > 0 && this->p_symbol_map_->operator[](this->p_cur_position_->y)[this->p_cur_position_->x-1] == -1)
	{
		--this->p_cur_position_->x;
	}
	
	int index = this->p_symbol_map_->operator[](this->p_cur_position_->y)[this->p_cur_position_->x];
	if (index == -1)
	{
		if (this->p_cur_position_->x == 0)
		{
			if (this->p_cur_position_->y != 0)
			{
				index = this->p_symbol_map_->operator[](this->p_cur_position_->y - 1)[winparam::n_postion];
			}
		}
	}
	tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	return index;
}
int ConsoleView::KeyDown()
{
	this->tui_object->GetYX(this->p_cur_position_->y, this->p_cur_position_->x);
	if (this->p_cur_position_->y == this->p_symbol_map_->size() - 1)
	{
		return;
	}
	this->DownCursor(false, this->p_cur_position_->y, this->p_cur_position_->x);
	while (this->p_symbol_map_->operator[](this->p_cur_position_->y)[this->p_cur_position_->x] == -1)
	{
		--this->p_cur_position_->x;
	}
	tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
}

int ConsoleView::KeyLeft()
{
	this->tui_object->GetYX(this->p_cur_position_->y, this->p_cur_position_->x);
	do
	{
		this->PrevCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
	} while (this->p_symbol_map_->operator[](this->p_cur_position_->y)[this->p_cur_position_->x] == -1);
	tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
}


int ConsoleView::KeyRight()
{
	tui_object->GetYX(this->p_cur_position_->y, this->p_cur_position_->x);
	if (this->p_last_position_->y == p_cur_position_->y && this->p_cur_position_->x == p_cur_position_->x)
	{
		return;
	}
	do
	{
		this->NextCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
	} while (this->p_symbol_map_->operator[](this->p_cur_position_->y)[this->p_cur_position_->x] == -1);
	tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
}




bool ConsoleView::UpCursor(bool to_begin_string, int& y, int& x)
{
	if (y != 0)
	{
		if (y - tui_object->GetOffsetY() == 0)
		{
			tui_object->ChangeOffsetY(-1);
		}
		--y;
		if (to_begin_string)
		{
			x = winparam::weight - 1;
		}
	}
	return false;
}

bool ConsoleView::DownCursor(bool to_begin_string, int& y, int& x)
{
	if (y - tui_object->GetOffsetY() == winparam::height - 1)
	{
		tui_object->ChangeOffsetY(1);
	}
	++y;
	if (to_begin_string)
	{
		x = 0;
	}
	return false;
}

std::vector<int> ConsoleView::CreateNewLine()
{

	std::vector<int>new_line(winparam::weight + 2, -1);
	//new_line[0] = static_cast<int>(*this->p_index_);
	return new_line;

}


void ConsoleView::NextCursorPos(int& y, int& x)
{
	if (x == winparam::weight - 1)
	{
		this->DownCursor(true, y, x);
	}
	else
	{
		++x;
	}
	this->tui_object->WMove(y, x);
}

void ConsoleView::PrevCursorPos(int& y, int& x)
{
	if (x == 0)
	{
		this->UpCursor(true, y, x);
	}
	else
	{
		--x;
	}
	tui_object->WMove(y, x);
}


void ConsoleView::PrintScreen(MyString& text, const bool new_string, int index)
{
	size_t size = text.Length();
	int x = this->p_cur_position_->x;
	int y = this->p_cur_position_->y;
	for (size_t i = index; i < size; i++)
	{
		char sym = text[i];
		if (sym == '\r')
		{
			if (x != 0 || new_string)
			{
				this->p_symbol_map_->operator[](y)[winparam::r_postion] = i;
				this->p_symbol_map_->operator[](y)[winparam::n_postion] = i + 1;
				this->DownCursor(true, y, x);
			}
			else
			{
				this->p_symbol_map_->operator[](y - 1)[winparam::r_postion] = i;
				this->p_symbol_map_->operator[](y - 1)[winparam::n_postion] = i + 1;
			}
			i++;
		}
		else
		{
			if (x == winparam::weight)
			{
				this->DownCursor(true, y, x);
			}
			this->tui_object->MvwPrintw(y, x, sym);
			this->p_symbol_map_->operator[](y)[x] = i;
			this->NextCursorPos(y, x);
		}
	}
	if (y < this->p_symbol_map_->size())
	{
		this->p_symbol_map_->operator[](y)[x] = static_cast<int>(size);
	}
}