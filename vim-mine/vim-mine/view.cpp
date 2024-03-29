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
	this->file_name_;
	this->index_ = 0;
	this->after_key_ = false;
	this->after_beg_str_ = false;
	this->old_offset_ = 0;
	this->special_key_ = false;
	this->is_search = false;
	this->search_to_begin_ = false;
	this->is_enter_symbol = false;
}

ConsoleView::~ConsoleView()
{
	this->file_name_.~MyString();
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

/*
The function with which the logical part of the program begins
*/
void ConsoleView::BeginExecute()
{
	this->tui_object->InitScr();
	this->tui_object->NewPad(winparam::real_size, winparam::width);
	this->tui_object->PRefresh();
	this->tui_object->Keypad(true);
	this->tui_object->NewWin(winparam::pannel_height, winparam::width, winparam::pan_start_y, 0);
	ModeType type = ModeType::EDIT_MODE;
	MyString command;
	char symbol = 0;
	while (type != ModeType::EXIT)
	{
		command = this->UpdatePanel(type);
		this->tui_object->PRefresh();
		if (command.Empty())
		{
			symbol = this->ReadSymbol();
			command.AppEnd(1, symbol);
		}
		if (!special_key_)
		{
			this->SetActualIndex(symbol);
			/*
			send data of user actions to controller
			*/
			type =  this->p_controller_->InfoController(this->index_, command);
			if (type != ModeType::SEARCH_MODE)
			{
				this->is_search = false;
			}
		}
		else
		{
			this->DirectionKeys(symbol);
			this->after_key_ = true;
			this->special_key_ = false;
		}
		command.Clear();
		command.ShrinkToFit();
	}
	return;

}


char ConsoleView::ReadSymbol()
{
	this->tui_object->NoEcho();
	int symbol = 0;
	symbol = this->tui_object->GetCh();
	if (symbol > 127)
	{
		special_key_ = true;
	}
	this->tui_object->Echo();
	return symbol;
}

bool ConsoleView::DirectionKeys(const char symbol)
{
	if (this->is_search)
	{
		return false;
	}
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
	case keys::key_pg_up:
	{
		this->UpdateKeys(SpecialKeys::PG_UP);
		break;
	}
	case keys::key_pg_down:
	{
		this->UpdateKeys(SpecialKeys::PG_DOWN);
		break;
	}
	case keys::key_home:
	{
		this->UpdateKeys(SpecialKeys::HOME);
		break;
	}
	case keys::key_end:
	{
		this->UpdateKeys(SpecialKeys::END);
		break;
	}
	default:
		return false;
	}
	return true;
}

bool ConsoleView::IsOverflow(char symbol)
{
	int y, x = 0;
	this->tui_object->GetYX(y, x);
	if (y==0)//there is no line above on line zero
	{
		return false;
	}
	if (x!= 0)// the cursor itself moves only when x = 0
	{
		return false;
	}
	if (symbol == '\n')// line break character
	{
		return false;
	}
	if (this->p_symbol_map_->operator[](y)[1] == 0)// there are no line transfers, which means that the \ n character cannot be higher
	{
		return false;
	}
	if (this->p_symbol_map_->operator[](y - 1)[1] != winparam::width + 1)// if the above line is not overflowed
	{
		return false;
	}
	if (!is_enter_symbol)
	{
		return false;
	}
	if (this->p_symbol_map_->operator[](y)[1] == 1 && this->p_cur_position_->y != this->p_last_position_->y || after_key_)// overflow can only be if the previous change was in the enter_symbol function
	{
		return false;
	}
	return true;
}





int ConsoleView::SetActualIndex(const char symbol)
{
	int x, y = 0;
	this->tui_object->GetYX(y, x);
	if (this->IsOverflow(symbol))
	{
		this->index_ = this->p_symbol_map_->operator[](y - 1)[0] + this->p_symbol_map_->operator[](y - 1)[1] - 1;// when there is a line overflow with \ n at the end
	}
	else
	{
		this->index_ = this->p_symbol_map_->operator[](y)[0] + x;
	}
	this->is_enter_symbol = false;
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
	case SpecialKeys::PG_UP:
	{
		this->KeyPgUp();
		break;
	}
	case SpecialKeys::PG_DOWN:
	{
		this->KeyPgDown();
		break;
	}
	case SpecialKeys::HOME:
	{
		this->KeyHome();
		break;
	}
	case SpecialKeys::END:
	{
		this->KeyEnd();
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
		if (this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] <= this->p_cur_position_->x)
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
		
		if (this->p_cur_position_->x > this->p_symbol_map_->operator[](this->p_cur_position_->y)[1]-1)
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

void ConsoleView::KeyPgUp()
{

	for (size_t i = 0; i < winparam::height; i++)
	{
		this->KeyUp();
	}
	this->p_cur_position_->x = 0;
	tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
}

void ConsoleView::KeyPgDown()
{
	for (size_t i = 0; i < winparam::height; i++)
	{
		this->KeyDown();
	}
	this->p_cur_position_->x = 0;
	tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
}

void ConsoleView::KeyEnd()
{
	while (this->p_cur_position_->y != this->p_last_position_->y)
	{
		this->KeyPgDown();
	}
	this->p_cur_position_->x = this->p_last_position_->x;
	tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
}

void ConsoleView::KeyHome()
{
	while (this->p_cur_position_->y != 0)
	{
		this->KeyPgUp();
	}
	this->p_cur_position_->x = 0;
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
			x = winparam::width - 1;
		}
	}
	return false;
}

bool ConsoleView::DownCursor(bool to_begin_string, int& y, int& x)
{
	bool flag = false;
	if (y - tui_object->GetOffsetY() == winparam::height - 1)
	{
		tui_object->ChangeOffsetY(1);
		flag = true;
	}
	++y;
	if (to_begin_string)
	{
		x = 0;
	}
	return flag;
}

std::vector<int> ConsoleView::CreateNewLine()
{

	std::vector<int>new_line(2, 0);
	return new_line;

}


void ConsoleView::NextCursorPos(int& y, int& x)
{
	if (x >= winparam::width - 1)
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


void ConsoleView::PrinrWithoutEndlSym(int& y, int& x, char symbol, const int idx)
{
	this->tui_object->MvwPrintw(y, x, symbol);
	//this->tui_object->PRefresh();
	if (x == 0)
	{
		this->p_symbol_map_->operator[](y)[0] = idx;
		this->p_symbol_map_->operator[](y)[1] = 1;
	}
	else
	{
		this->p_symbol_map_->operator[](y)[1] += 1;
	}
	this->NextCursorPos(y, x);
}



void ConsoleView::PrintEndlSymbolNotXZero(int& y, int& x, char symbol, const int idx)
{
	this->p_symbol_map_->operator[](y)[1] += 1;
	this->DownCursor(true, y, x);
}

void ConsoleView::PrintEndlAfterNewString(int& y, int& x, MyString& text, const int idx)
{
	if (idx != 0 && this->p_symbol_map_->operator[](y - 1)[1] == winparam::width && text[idx - 1] != '\n')
	{
		this->p_symbol_map_->operator[](y - 1)[1] += 1;
		return;// in the case when the full line with \ n at the end and is driven in above
	}
	if (idx != 0)
	{
		this->p_symbol_map_->operator[](y)[0] = this->p_symbol_map_->operator[](y - 1)[1] + this->p_symbol_map_->operator[](y - 1)[0];// when only \ n is in the line
	}
	this->p_symbol_map_->operator[](y)[1] = 1;
	this->DownCursor(true, y, x);
}

void ConsoleView::PrintEndlAfterEnterSymbol(int& y, int& x, MyString& text, const int idx)
{
	if (idx != 0 && this->p_symbol_map_->operator[](y - 1)[1] >= winparam::width && text[idx - 1] != '\n')//����� �� enter symbol � ������ ���� �����������
	{
		this->p_symbol_map_->operator[](y - 1)[1] += 1;
	}
	else
	{
		this->p_symbol_map_->operator[](y)[1] = 1;
		this->p_symbol_map_->operator[](y)[0] = idx;
		this->DownCursor(true, y, x);
	}
	//this->tui_object->PRefresh();
}




void ConsoleView::PrintScreen(MyString& text, const bool new_string, int index)
{
	size_t length = text.Length();
	int x = 0;
	int y = this->p_cur_position_->y;
	if (this->after_beg_str_)
	{
		this->after_beg_str_ = false;
	}
	else
	{
		this->after_key_ = false;
	}
	int idx = 0;
	if (y != 0)
	{
		idx = this->p_symbol_map_->operator[](y - 1)[0] + this->p_symbol_map_->operator[](y - 1)[1];
		if (!new_string && this->p_cur_position_->x == 0 && this->p_symbol_map_->operator[](y -1)[1] == winparam::width + 1) // if from the function of entering a character, starting from position x = 0 b c of the overloaded string above
		{
			if (text[idx + 1] != '\n')// if not on a new line
			{
				--idx;
				--this->p_symbol_map_->operator[](y - 1)[1];// when overflow and adding a new character to the same string needs to be changed
			}
		}
	}
	else
	{
		idx = 0;
	}
	for (size_t i = static_cast<size_t>(idx); i < length; i++)
	{
		if (text[i] != '\n')
		{
			this->PrinrWithoutEndlSym(y, x, text[i], i);
		}
		else
		{
			if (x != 0)
			{
				this->PrintEndlSymbolNotXZero(y, x, '\n', i);
			}
			else
			{
				if (new_string)
				{
					this->PrintEndlAfterNewString(y, x, text, i);
				}
				else
				{
					this->PrintEndlAfterEnterSymbol(y, x, text, i);
				}
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
	if (this->p_cur_position_->x == winparam::width - 1 || this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] >= winparam::width)
	{
		std::vector<int> new_line = this->CreateNewLine();
		this->p_symbol_map_->emplace_back(new_line);
		return true;
	}
	return false;
}

int ConsoleView::NumberOfDigits(int value)
{
	int count = 0;
	while (value != 0)
	{
		value /= 10;
		count++;
	}
	return count + 1;
}

void ConsoleView::DeleteLine()
{
	if (this->p_cur_position_->x == 0 && this->p_cur_position_->y != 0)
	{
		if (this->p_symbol_map_->operator[](this->p_cur_position_->y - 1)[1] == winparam::width+1)
		{
			return;
		}
		if (this->p_cur_position_->y < static_cast<int>(this->p_symbol_map_->size())-1)
		{
			int check_sum = this->p_symbol_map_->operator[](this->p_cur_position_->y + 1)[1] + this->p_symbol_map_->operator[](this->p_cur_position_->y)[1];
			if (check_sum >= winparam::width)
			{
				return;
			}
		}
	}
	std::vector<std::vector<int>>::iterator it;
	it = this->p_symbol_map_->begin();
	it += this->p_cur_position_->y;
	this->p_symbol_map_->erase(it);

	this->KeyUp();
	this->p_cur_position_->x = this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] - 1;
	if (this->p_cur_position_->x < 0)
	{
		this->p_cur_position_->x = 0;
	}
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->tui_object->PRefresh();
}



MyString ConsoleView::UpdatePanel(ModeType& type)
{
	MyString command;
	this->tui_object->ClearPannel();
	switch (type)
	{
	case ModeType::EDIT_MODE:
	{
		this->PrintMyString(0, pan::edit_mode);
		this->PrintStatistic();
		break;
	}
	case ModeType::ENTER_SYM_MODE:
	{
		this->PrintMyString(0, pan::insert_mode);
		this->PrintStatistic();
		break;
	}
	case ModeType::ENTER_COM_MODE:
	{
		this->PrintMyString(0, pan::command_mode);
		command = this->GetMyString();
		break;
	}
	case ModeType::SEARCH_MODE:
	{
		if (!this->is_search)
		{
			if (this->search_to_begin_)
			{
				this->PrintMyString(0, pan::search_mode_to_begin);
			}
			else
			{
				this->PrintMyString(0, pan::search_mode_to_end);
			}
			command = this->GetMyString();
			this->is_search = true;
		}
		break;
	}
	default:
		break;
	}
	this->tui_object->WRefresh();

	return command;
}


bool ConsoleView::IsSpecKeyOnPanel(int& x, int sym, MyString& command_)
{
	if (sym == keys::key_backspace)
	{
		if (x != pan::read_begin)
		{
			--x;
			if (!command_.Empty())
			{
				command_.Erase(x - pan::read_begin, 1);
			}
		}
		return true;
	}
	return false;

}




MyString ConsoleView::GetMyString()
{
	MyString string_;
	int sym = 0;
	int y = 0;
	int x = pan::read_begin;
	bool backspace = false;
	sym = this->tui_object->Mvwscanf(y, x);
	while (sym != '\n')
	{
		if (!IsSpecKeyOnPanel(x, sym, string_))
		{
			if (sym == keys::key_escape)
			{
				string_.Clear();
				string_.AppEnd(1, static_cast<char>(sym));
				this->tui_object->ClearPannel();
				break;
			}
			string_.Insert(x - pan::read_begin, 1, static_cast<char>(sym));
			++x;
			if (x == winparam::width -1)
			{
				break;
			}
		}
		if (string_.Length() <= static_cast<size_t>(x - pan::read_begin))
		{
			this->tui_object->MvwprintPannel(y, x, ' ');
		}
		this->tui_object->WPanMove(y, x);
		this->tui_object->WRefresh();
		sym = tui_object->Mvwscanf(y, x);
	}
	return string_;
}

void ConsoleView::PrintMyString(int x, const MyString& string_)
{
	size_t length = string_.Length();
	for (size_t i = 0; i < length; i++)
	{
		this->tui_object->MvwprintPannel(0, x+i, string_.CStr()[i]);
		this->tui_object->PRefresh();
	}
}

void ConsoleView::PrintStatistic()
{
	int x = pan::statistic_begin;
	this->tui_object->WPanMove(0, x);
	this->tui_object->MvwPtintInt(0, x, this->p_cur_position_->y);
	x += this->NumberOfDigits(this->p_cur_position_->y);
	this->tui_object->MvwprintPannel(0, x, '/');
	x++;
	this->tui_object->MvwPtintInt(0, x, this->p_last_position_->y);
	if (this->file_name_.Empty())
	{
		this->PrintMyString(pan::file_name_begin ,pan::default_file_name);
	}
	else
	{
		this->PrintMyString(pan::file_name_begin, this->file_name_);
	}
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
	bool special = false;
	if (y != 0)// condition that it is not the first line
	{
		if (x == 0)// guarantees that at the beginning of the line
		{
			if (this->p_symbol_map_->operator[](y - 1)[1] == winparam::width) // makes sure the previous line is not over
			{
				if (this->index_ == text.Length()-1) // makes sure the end position of the console
				{
					special = true;
				}

			}

		}
	}
	if (!special)
	{
		std::vector<std::vector<int>>::iterator it;
		it = this->p_symbol_map_->begin();
		it += this->p_cur_position_->y+1;
		std::vector<int> new_line = this->CreateNewLine();
		this->p_symbol_map_->insert(it, new_line);
		this->old_offset_ = this->tui_object->GetOffsetY();
		this->PrintScreen(text, true, 0);
		this->DownCursor(true, this->p_cur_position_->y, this->p_cur_position_->x);
		if (this->p_last_position_->y > winparam::height)
		{
			this->old_offset_++;
		}
		
	}
	else
	{
		this->p_symbol_map_->operator[](y - 1)[1] += 1;
		this->p_symbol_map_->operator[](y)[0] = text.Length();
		this->p_symbol_map_->operator[](y)[1] += 0;
	}

	this->ReturnToCurLine();

	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->tui_object->PRefresh();
}

void ConsoleView::EnterSymbol(MyString& text)
{
	this->is_enter_symbol = true;
	this->ClearScreen();
	this->DoRefreash();
	this->CheckNewLine();
	this->old_offset_ = this->tui_object->GetOffsetY();
	this->PrintScreen(text, false, this->index_);
	this->ReturnToCurLine();
	this->NextCur();
	this->DoRefreash();
}



void ConsoleView::DeleteSymbol(MyString& text, bool delete_line, const int index)
{
	this->index_ = index;
	this->after_beg_str_ = true;
	//this->SetToBeginString(text);
	if (delete_line)
	{
		this->DeleteLine();
	}
	else
	{
		//this->PrevCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
		this->KeyLeft();
	}
	this->tui_object->ClrToBot();
	this->old_offset_ = this->tui_object->GetOffsetY();
	this->PrintScreen(text, false, 0);
	this->ReturnToCurLine();
	if (this->p_cur_position_->x == 1)
	{
		this->after_beg_str_ = false;
		this->after_beg_str_ = true;
	}
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->tui_object->PRefresh();
}



void ConsoleView::CountAndCreateLines(MyString& text)
{
	size_t length = text.Length();
	int x = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (text[i] == '\n' || x == winparam::width)
		{
			if (text[i] != '\n' || x != winparam::width+1)
			{
				std::vector<int> new_line = this->CreateNewLine();
				this->p_symbol_map_->emplace_back(new_line);
				x = 0;
			}
		}
		else
		{
			++x;
		}
	}

}

void ConsoleView::ReturnToCurLine()
{
	int y = this->tui_object->GetOffsetY();
	this->tui_object->ChangeOffsetY(old_offset_ - y);
	this->tui_object->PRefresh();
}



void ConsoleView::OpneFile(MyString& text, MyString& file_name)
{
	this->tui_object->WMove(0, 0);
	this->tui_object->ClrToBot();
	this->CountAndCreateLines(text);
	this->file_name_ = file_name;
	this->index_ = 0;
	this->p_cur_position_->y = 0;
	this->p_cur_position_->x = 0;
	this->PrintScreen(text, false, 0);
	*this->p_cur_position_ = *this->p_last_position_;
	this->tui_object->PRefresh();
}

void ConsoleView::SetToBeginString(MyString& text)
{
	this->after_beg_str_ = true;
	int y = this->p_cur_position_->y;
	if (y == 0)
	{
		this->p_cur_position_->x = 0;
		return;
	}
	int cur_index = this->p_symbol_map_->operator[](y - 1)[0] + this->p_symbol_map_->operator[](y - 1)[1];
	while (y != 0 && this->p_symbol_map_->operator[](y-1)[1] == winparam::width && text[cur_index] != '\n')
	{
		--y;
		cur_index = this->p_symbol_map_->operator[](y - 1)[0] + this->p_symbol_map_->operator[](y - 1)[1];
	}
	this->p_cur_position_->y = y;
	this->p_cur_position_->x = 0;
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->tui_object->PRefresh();
}

void ConsoleView::SetToEndString(MyString& text)
{
	this->after_beg_str_ = true;
	int y = this->p_cur_position_->y;
	int cur_index = this->p_symbol_map_->operator[](y)[0] + this->p_symbol_map_->operator[](y)[1];
	while (y != this->p_last_position_->y && this->p_symbol_map_->operator[](y)[1] == winparam::width && text[cur_index] != '\n')
	{
		++y;
		cur_index = this->p_symbol_map_->operator[](y)[0] + this->p_symbol_map_->operator[](y)[1];
	}
	this->p_cur_position_->y = y;
	this->p_cur_position_->x = this->p_symbol_map_->operator[](y)[1] - 2;
	if (this->p_cur_position_->x < 0)
	{
		this->p_cur_position_->x = 0;
	}
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->tui_object->PRefresh();
}

void ConsoleView::DeleteStringPrep(MyString& text, const int index)
{
	int y = this->p_cur_position_->y;
	this->SetToEndString(text);
	this->p_cur_position_->x = this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] - 1;
	if (this->p_cur_position_->x >= winparam::width)// if last the position of overflow string
	{
		this->NextCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
	}
	
	/*if (this->p_cur_position_->x == 0 && y != this->p_cur_position_->y)
	{
		if (y!= 0 &&this->p_symbol_map_->operator[](y - 1)[1] == winparam::width +1)
		{
			this->p_cur_position_->y = y - 1;
			this->p_cur_position_->x = winparam::width - 1;
		}
	}*/
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->index_ = index;
}

void ConsoleView::ChangeOneSymbol()
{
	this->after_key_ = true;
}

void ConsoleView::ChangeCurFileName(MyString& file_name)
{
	this->file_name_ = file_name;
}

/*
The function changes cur_y based on the new position in the text.
*/

void ConsoleView::SetCurYByIndex(MyString& text, const int index)
{
	int y = this->p_cur_position_->y;
	int length = static_cast<int>(text.Length());
	bool to_begin = false;
	int end_line_index = this->p_symbol_map_->operator[](y)[0] + this->p_symbol_map_->operator[](y)[1];
	if (this->p_symbol_map_->operator[](y)[0] > index) // ���������� ���� ��� ����
	{
		--y;
		while (y > 0 && this->p_symbol_map_->operator[](y)[0] > index)
		{
			--y;
			this->KeyUp();
			//this->tui_object->PRefresh();
		}
	}
	else
	{
		while (y != this->p_last_position_->y && index >= end_line_index)
		{
			++y;
			this->KeyDown();
			end_line_index = this->p_symbol_map_->operator[](y)[0] + this->p_symbol_map_->operator[](y)[1];
		}
	}
	this->KeyUp();
	this->p_cur_position_->y = y;
}



void ConsoleView::PrintHelpString(MyString& help_info)
{
	size_t length = help_info.Length();
	int x = 0;
	int y = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (help_info[i] == '\n')
		{
			this->DownCursor(true, y, x);
		}
		else
		{
			this->tui_object->MvwPrintw(y, x, help_info[i]);
			++x;
		}
	}
}



void ConsoleView::HelpInfo(MyString& help_info, MyString& text)
{
	int temp_y = this->p_cur_position_->y;
	int temp_x = this->p_cur_position_->x;
	this->old_offset_ = this->tui_object->GetOffsetY();
	this->tui_object->ChangeOffsetY(-this->old_offset_);
	this->p_cur_position_->x = 0;
	this->p_cur_position_->y = 0;
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	//this->tui_object->PRefresh();
	this->tui_object->ClrToBot();
	this->PrintHelpString(help_info);
	this->tui_object->PRefresh();
	int key = 0;
	while (key != keys::key_escape)
	{
		this->tui_object->Echo();
		key = this->tui_object->GetCh();
		this->tui_object->NoEcho();
	}
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->tui_object->ClrToBot();
	this->PrintScreen(text, false, 0);
	this->p_cur_position_->y = temp_y;
	this->p_cur_position_->x = temp_x;
	this->ReturnToCurLine();
	this->tui_object->WMove(temp_y, temp_x);
	this->tui_object->PRefresh();
}



void ConsoleView::SearchWord(MyString& text, const int index)
{
	this->after_key_ = true;
	this->SetCurYByIndex(text, index);
	this->p_cur_position_->x = index - this->p_symbol_map_->operator[](this->p_cur_position_->y)[0];
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->tui_object->PRefresh();
}

void ConsoleView::SearchToBegin()
{
	this->search_to_begin_ = true;
	this->after_key_ = true;
}

void ConsoleView::SetCursToWord(MyString& text, const int index)
{
	this->after_key_ = true;
	this->index_ = index;
	this->SetCurYByIndex(text, index);
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->tui_object->PRefresh();
	this->p_cur_position_->x = index - this->p_symbol_map_->operator[](this->p_cur_position_->y)[0];
	if (this->p_cur_position_->x < 0)
	{
		this->p_cur_position_->x = 0;
	}
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->tui_object->PRefresh();
}

void ConsoleView::SetCursRight()
{
	this->KeyRight();
}

void ConsoleView::SetCursLeft()
{
	this->KeyLeft();
}

void ConsoleView::PastPreparation(MyString& copy_line, const int index)
{
	if (copy_line[copy_line.Length()-1] == '\n')
	{
		std::vector<int> new_line = this->CreateNewLine();
		this->p_symbol_map_->emplace_back(new_line);
	}
	this->KeyRight();
	if (this->p_cur_position_->x == this->p_symbol_map_->operator[](this->p_cur_position_->y)[1])
	{
		this->KeyRight();
	}
}

