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
			this->SetActualIndex(symbol);
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

int ConsoleView::SetActualIndex(const char symbol)
{
	int x, y = 0;
	this->tui_object->GetYX(y, x);
	if (x != 0 || y == 0 || this->p_symbol_map_->operator[](y - 1)[1] != winparam::weight + 1 || symbol == '\n')
	{
	
		this->index_ = this->p_symbol_map_->operator[](y)[0] + x;
	}
	else
	{
		if (this->p_symbol_map_->operator[](y)[1] == 1 && this->p_cur_position_->y != this->p_last_position_->y)
		{
			this->index_ = this->p_symbol_map_->operator[](y)[0] + x; //когда строка выше переполнена и на текущей строке только \n
		}
		else
		{
			this->index_ = this->p_symbol_map_->operator[](y - 1)[0] + this->p_symbol_map_->operator[](y - 1)[1] - 1;//когда происходит переполнение строки с \n на конце
		}
			
	}
	return 0;
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

	if (this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] == 1)
	{
		this->p_cur_position_->x = 0;
	}
	else
	{
		if (this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] < this->p_cur_position_->x)
		{
			this->p_cur_position_->x = this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] - 1;
		}
	}
	
	tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);

}


void ConsoleView::KeyDown()
{
	this->tui_object->GetYX(this->p_cur_position_->y, this->p_cur_position_->x);
	if (this->p_cur_position_->y != this->p_last_position_->y)
	{
		
		this->DownCursor(false, this->p_cur_position_->y, this->p_cur_position_->x);
		
		if (this->p_cur_position_->x > this->p_symbol_map_->operator[](this->p_cur_position_->y)[1])
		{
			if (this->p_cur_position_->y == this->p_last_position_->y || this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] != 1)
			{
				if (this->p_cur_position_->y == this->p_last_position_->y)
				{
					this->p_cur_position_->x = this->p_symbol_map_->operator[](this->p_cur_position_->y)[1];
				}
				else
				{
					this->p_cur_position_->x = this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] - 1;
				}
			}
			else
			{
				this->p_cur_position_->x = 0;
			}
		}
	}
	tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
}

void ConsoleView::KeyLeft()
{
	this->tui_object->GetYX(this->p_cur_position_->y, this->p_cur_position_->x);
	this->PrevCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
	if (this->p_cur_position_->x > this->p_symbol_map_->operator[](this->p_cur_position_->y)[1])
	{
		if (this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] != 1)
		{
			this->p_cur_position_->x = this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] - 1;
		}
		else
		{
			this->p_cur_position_->x = 0;
		}
	}
	tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
}


void ConsoleView::KeyRight()
{
	this->tui_object->GetYX(this->p_cur_position_->y, this->p_cur_position_->x);

	if (this->p_cur_position_->y != this->p_last_position_->y || this->p_cur_position_->x != this->p_last_position_->x)
	{

		this->NextCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
		if (this->p_cur_position_->x > this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] - 1)
		{
			if (this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] != 1)
			{
				if (this->p_cur_position_->y == this->p_last_position_->y)
				{
					this->p_cur_position_->x = this->p_symbol_map_->operator[](this->p_cur_position_->y)[1];
				}
				else
				{
					this->p_cur_position_->x = this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] - 1;
				}
			}
			else
			{
				this->p_cur_position_->x = 0;
			}
		}
	}

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

	std::vector<int>new_line(2, 0);
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
	size_t length = text.Length();
	int x = 0;
	int y = this->p_cur_position_->y;

	int idx = 0;
	if (y != 0)
	{
		idx = this->p_symbol_map_->operator[](y - 1)[0] + this->p_symbol_map_->operator[](y - 1)[1];
		if (!new_string && this->p_cur_position_->x == 0 && this->p_symbol_map_->operator[](y -1)[1] == winparam::weight + 1)
		{
			if (text[idx + 1] != '\n')
			{
				--idx;
				--this->p_symbol_map_->operator[](y - 1)[1];
			}
		}
	}
	else
	{
		idx = 0;
	}
	this->tui_object->PRefresh();
	for (size_t i = static_cast<size_t>(idx); i < length; i++)
	{

		if (text[i] != '\n')
		{
			this->tui_object->MvwPrintw(y, x, text[i]);
			if (x == 0)
			{
				this->p_symbol_map_->operator[](y)[0] = i;
				this->p_symbol_map_->operator[](y)[1] = 1;
			}
			else
			{
				this->p_symbol_map_->operator[](y)[1] +=1;
			}
			this->NextCursorPos(y, x);
		}
		else
		{
			if (x != 0 || new_string)
			{
				if (x == 0)
				{
					if (i != 0)
					{
						this->p_symbol_map_->operator[](y)[0] = this->p_symbol_map_->operator[](y-1)[1] + this->p_symbol_map_->operator[](y-1)[0];
					}
					this->p_symbol_map_->operator[](y)[1] = 1;
				}
				else
				{
					this->p_symbol_map_->operator[](y)[1] += 1;
				}
				this->DownCursor(true, y, x);
			}
			else
			{
				if (this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] == winparam::weight && text[i-1] != '\n')
				{
					this->p_symbol_map_->operator[](y - 1)[1] += 1;
				}
				else
				{
					this->p_symbol_map_->operator[](y)[1] = 1;
					this->p_symbol_map_->operator[](y)[0] = i;
					this->DownCursor(true, y, x);
				}
				this->tui_object->PRefresh();
				
			}
		}
	}
	if (x == 0 && this->p_symbol_map_->size() != y)
	{
		this->p_symbol_map_->operator[](y)[0] = length;
		this->p_symbol_map_->operator[](y)[1] = 0;
	}
	this->p_last_position_->y = y;
	this->p_last_position_->x = x;
}

void ConsoleView::ClearScreen()
{
	this->tui_object->ClrToBot();
}

bool ConsoleView::CheckNewLine()
{
	if (this->p_cur_position_->x == winparam::weight - 1 || this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] == winparam::weight+1)
	{
		std::vector<int> new_line = this->CreateNewLine();
		this->p_symbol_map_->emplace_back(new_line);
		return true;
	}
	return false;
}

void ConsoleView::DoRefreash()
{
	this->tui_object->PRefresh();
}

void ConsoleView::NextCur()
{
	this->NextCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
}

void ConsoleView::PrevCur()
{
	this->PrevCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
}

void ConsoleView::NewString(MyString& text)
{
	int x = this->p_cur_position_->x;
	int y = this->p_cur_position_->y;
	this->tui_object->WMove(y, 0);
	this->tui_object->ClrToBot();
	bool shit = false;
	if (y != 0) //условие того что не первая линия
	{
		if (x == 0)// гарантирует то что в начале линнии
		{
			if (this->p_symbol_map_->operator[](y - 1)[1] == winparam::weight) //гарантирует то что прошлая строка не закончилась
			{
				if (this->index_ == text.Length()-1)//гарантирует то что крайняя позиция консоли
				{
					shit = true;
				}

			}

		}
	}
	if (!shit)
	{
		std::vector<std::vector<int>>::iterator it;
		it = this->p_symbol_map_->begin();
		it += this->p_cur_position_->y+1;
		std::vector<int> new_line = this->CreateNewLine();
		this->p_symbol_map_->insert(it, new_line);
		this->PrintScreen(text, true, 0);
		this->DownCursor(true, this->p_cur_position_->y, this->p_cur_position_->x);
		
		
	}
	else
	{
		this->p_symbol_map_->operator[](y - 1)[1] += 1;
		this->p_symbol_map_->operator[](y)[0] = text.Length();
		this->p_symbol_map_->operator[](y)[1] += 0;

	}
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	
}

void ConsoleView::EnterSymbol(MyString& text)
{
	
	this->ClearScreen();
	this->DoRefreash();
	this->CheckNewLine();
	this->PrintScreen(text, false, this->index_);
	this->NextCur();
	this->DoRefreash();
}

