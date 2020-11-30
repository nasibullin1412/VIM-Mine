#include "view.h"
#pragma once

ConsoleView::ConsoleView()
{
	this->tui_object = nullptr;
	this->p_symbol_map_ = nullptr;
	this->p_cur_position_ = nullptr;
	this->p_last_position_ = nullptr;
	this->p_cur_position_ = nullptr;
	this->p_controller_ = nullptr;
	this->index_ = 0;
}

ConsoleView::~ConsoleView()
{
}

void ConsoleView::InitAllPointers(AdapterPDCur* tui_object, std::vector<std::vector<int>>* p_symbol_map,
									Position* p_last_position_, Position* p_cur_position_, Controller* p_controller)
{
	this->tui_object = tui_object;
	this->p_symbol_map_ = p_symbol_map;
	this->p_cur_position_ = p_cur_position_;
	this->p_last_position_ = p_last_position_;
	this->p_cur_position_ = p_cur_position_;
	this->p_controller_ = p_controller;

}



void ConsoleView::BeginExecute()
{
	
	this->tui_object->InitScr();
	this->tui_object->NewPad(winparam::real_size, winparam::weight);
	this->tui_object->PRefresh();
	this->tui_object->Keypad(true);
	while (true)
	{
		char symbol = this->ReadSymbol();

		if (!this->DirectionKeys(symbol))
		{
			this->SetActualIndex();
			this->p_controller_->InfoController(this->index_, symbol);
		}
	}
	return;

}


char ConsoleView::ReadSymbol()
{
	this->tui_object->NoEcho();
	int symbol = 0;
	symbol = this->tui_object->GetCh();
	this->tui_object->Echo();
	return symbol;
}

bool ConsoleView::DirectionKeys(const char symbol)
{
	switch (symbol)
	{
	case keys::key_up: 
	{
		this->UpdateKeys(SpecialKeys::CURSOR_UP);
		break;
	}
	case keys::key_down:
	{
		this->UpdateKeys(SpecialKeys::CURSOR_DOWN);
		break;
	}
	case keys::key_left:
	{
		this->UpdateKeys(SpecialKeys::CURSOR_LEFT);
		break;
	}
	case keys::key_right:
	{
		this->UpdateKeys(SpecialKeys::CURSOR_RIGHT);
		break;
	}
	default:
		return false;
	}
	return true;
}

int ConsoleView::SetActualIndex()
{
	int x, y = 0;
	this->tui_object->GetYX(y, x);
	this->index_ = this->p_symbol_map_->operator[](y)[x];
	if (this->index_ == -1)
	{
		if (y != 0 && x == 0)
		{
			this->index_ = this->p_symbol_map_->operator[](y - 1)[winparam::n_postion] + 1;
		}
		else
		{
			if (x != 0)
			{
				this->index_ = this->p_symbol_map_->operator[](y)[x - 1] + 1;
			}
		}
	}
	if (this->index_ == -1)
	{
		exit(-1);
	}
}


void ConsoleView::UpdateKeys(const SpecialKeys type)
{
	switch (type)
	{
	case SpecialKeys::CURSOR_UP:
	{
		this->KeyUp();
		break;
	}
	case SpecialKeys::CURSOR_DOWN:
	{
		this->KeyDown();
		break;
	}
	case SpecialKeys::CURSOR_RIGHT:
	{
		this->KeyRight();
		break;
	}
	case SpecialKeys::CURSOR_LEFT:
	{
		this->KeyLeft();
		break;
	}
	default:
		break;
	}
	this->tui_object->PRefresh();
}


void ConsoleView::KeyUp()
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

}


void ConsoleView::KeyDown()
{
	this->tui_object->GetYX(this->p_cur_position_->y, this->p_cur_position_->x);
	this->DownCursor(false, this->p_cur_position_->y, this->p_cur_position_->x);
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
}

void ConsoleView::KeyLeft()
{
	this->tui_object->GetYX(this->p_cur_position_->y, this->p_cur_position_->x);
	do
	{
		this->PrevCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
	} while (this->p_cur_position_->x > 0 && this->p_symbol_map_->operator[](this->p_cur_position_->y)[this->p_cur_position_->x-1] == -1);
	tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
}


void ConsoleView::KeyRight()
{
	tui_object->GetYX(this->p_cur_position_->y, this->p_cur_position_->x);
	do
	{
		this->NextCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
	} while (this->p_cur_position_->x > 0 && this->p_symbol_map_->operator[](this->p_cur_position_->y)[this->p_cur_position_->x - 1] == -1);
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
				this->p_symbol_map_->operator[](y)[winparam::r_postion] = this->p_symbol_map_->operator[](y-1)[winparam::r_postion];
				this->p_symbol_map_->operator[](y)[winparam::n_postion] = this->p_symbol_map_->operator[](y-1)[winparam::n_postion];
				this->p_symbol_map_->operator[](y-1)[winparam::r_postion] = -1;
				this->p_symbol_map_->operator[](y-1)[winparam::n_postion] = -1;
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

void ConsoleView::ClearScreen()
{
	this->tui_object->ClrToBot();
}

void ConsoleView::CheckNewLine()
{
	if (this->p_cur_position_->x == winparam::weight - 1)
	{
		std::vector<int> new_line = this->CreateNewLine();
		this->p_symbol_map_->emplace_back(new_line);
	}
}

void ConsoleView::DoRefreash()
{
	this->tui_object->PRefresh();
}

void ConsoleView::NextCur()
{
	this->NextCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
	this->index_ = this->p_symbol_map_->operator[](this->p_cur_position_->y)[this->p_cur_position_->x];
}

void ConsoleView::PrevCur()
{
	this->PrevCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
	this->index_ = this->p_symbol_map_->operator[](this->p_cur_position_->y)[this->p_cur_position_->x];
}

void ConsoleView::NewString(MyString &text)
{
	int y = 0;
	int x = 0;
	this->tui_object->GetYX(y, x);
	bool shit = false;
	if (y != 0) //условие того что не первая линия
	{
		if (x == 0)// гарантирует то что в начале линнии
		{
			if (this->p_symbol_map_->operator[](y - 1)[winparam::n_postion] == -1) //гарантирует то что прошлая строка не закончилась
			{
				if (this->index_ == text.Length()-2)//гарантирует то что крайняя позиция консоли
				{
					shit = true;
				}

			}

		}
	}
	if (this->index_ == -1)
	{
		if (y != 0)
		{
			this->index_ = this->p_symbol_map_->operator[](y - 1)[winparam::n_postion] + 1;
		}
	}
	this->tui_object->ClrToBot();
	if (shit)//если тот самый ужасный случай
	{
		this->p_symbol_map_->operator[](y)[0] = -1;
		this->p_symbol_map_->operator[](y - 1)[winparam::r_postion] = this->index_;
		this->p_symbol_map_->operator[](y - 1)[winparam::n_postion] = this->index_ + 1;
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
		if (this->index_ == text.Length() - 2)
		{
			this->p_symbol_map_->operator[](y)[winparam::r_postion] = this->index_;
			this->p_symbol_map_->operator[](y)[winparam::n_postion] = this->index_ + 1;
		}
		else
		{
			this->p_symbol_map_->operator[](y)[winparam::r_postion] = this->index_ + 1;
			this->p_symbol_map_->operator[](y)[winparam::n_postion] = this->index_ + 2;
		}
		std::vector<std::vector<int>>::iterator it;
		it = this->p_symbol_map_->begin();
		it += this->p_cur_position_->y + 1;
		std::vector<int> new_line = this->CreateNewLine();
		this->p_symbol_map_->insert(it, new_line);
		this->PrintScreen(text, true, this->index_);
		this->DownCursor(true, this->p_cur_position_->y, this->p_cur_position_->x);
	}
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
}

