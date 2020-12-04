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
	this->tui_object->NewWin(winparam::pannel_height, winparam::weight, winparam::pan_start_y, 0);
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

int ConsoleView::SetActualIndex(const char symbol)
{
	int x, y = 0;
	this->tui_object->GetYX(y, x);
	if (x != 0 || y == 0 || this->p_symbol_map_->operator[](y - 1)[1] != winparam::weight + 1 || symbol == '\n' || this->p_symbol_map_->operator[](y)[1] == 0)
	{
		this->index_ = this->p_symbol_map_->operator[](y)[0] + x;
	}
	else
	{
		if (this->p_symbol_map_->operator[](y)[1] == 1 && this->p_cur_position_->y != this->p_last_position_->y || after_key_)
		{
			this->index_ = this->p_symbol_map_->operator[](y)[0] + x; //когда строка выше переполнена и на текущей строке только \n или пришли на данную позицию с помощью клавы
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
			x = winparam::weight - 1;
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
	//new_line[0] = static_cast<int>(*this->p_index_);
	return new_line;

}


void ConsoleView::NextCursorPos(int& y, int& x)
{
	if (x >= winparam::weight - 1)
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
		if (!new_string && this->p_cur_position_->x == 0 && this->p_symbol_map_->operator[](y -1)[1] == winparam::weight + 1) //если из при вводе символа, начиная со позиции x = 0 b c перегруженной строкой выше 
		{
			if (text[idx + 1] != '\n')//если не с новой строки
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
		if (y== 7)
		{
			y++;
			--y;
		}
		if (text[i] != '\n')
		{
			this->tui_object->MvwPrintw(y, x, text[i]);
			this->tui_object->PRefresh();
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
			if (x != 0 || new_string)// если не из новой строки вызвана или не с нулевой позиции
			{
				if (x == 0 && i != 0 && this->p_symbol_map_->operator[](y-1)[1] == winparam::weight && text[i-1] != '\n')
				{
					this->p_symbol_map_->operator[](y - 1)[1] += 1;
					continue;// в случае, когда полная строка с \n на конце и вбивается выше
				}
				if (x == 0) //если позиция 0
				{
					if (i != 0)
					{
						this->p_symbol_map_->operator[](y)[0] = this->p_symbol_map_->operator[](y - 1)[1] + this->p_symbol_map_->operator[](y - 1)[0]; // когда только \n в строке
					}
					this->p_symbol_map_->operator[](y)[1] = 1;

					this->DownCursor(true, y, x);
				}
				else
				{
					this->p_symbol_map_->operator[](y)[1] += 1;
					this->DownCursor(true, y, x);
				}
			}
			else
			{
				if (i != 0 && this->p_symbol_map_->operator[](y-1)[1] == winparam::weight && text[i-1] != '\n')
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
	if (this->p_cur_position_->x == winparam::weight - 1 || this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] >= winparam::weight)
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
		if (this->p_symbol_map_->operator[](this->p_cur_position_->y - 1)[1] == winparam::weight+1)
		{
			return;
		}
		if (this->p_cur_position_->y < this->p_symbol_map_->size()-1)
		{
			if (this->p_symbol_map_->operator[](this->p_cur_position_->y + 1)[1] + this->p_symbol_map_->operator[](this->p_cur_position_->y)[1] >= winparam::weight)
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
			if (x == winparam::weight -1)
			{
				break;
			}
		}
		if (string_.Length() <= x - pan::read_begin)
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
	if (y != 0) //условие того что не первая линия
	{
		if (x == 0)// гарантирует то что в начале линнии
		{
			if (this->p_symbol_map_->operator[](y - 1)[1] == winparam::weight) //гарантирует то что прошлая строка не закончилась
			{
				if (this->index_ == text.Length()-1)//гарантирует то что крайняя позиция консоли
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
		this->PrevCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
	}
	this->tui_object->ClrToBot();
	this->old_offset_ = this->tui_object->GetOffsetY();
	this->PrintScreen(text, false, 0);
	this->ReturnToCurLine();
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->tui_object->PRefresh();
}



void ConsoleView::CountAndCreateLines(MyString& text)
{
	size_t length = text.Length();
	int x = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (text[i] == '\n' || x == winparam::weight)
		{
			if (text[i] != '\n' || x != winparam::weight+1)
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
	while (y != 0 && this->p_symbol_map_->operator[](y-1)[1] == winparam::weight && text[cur_index] != '\n')
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
	while (y != this->p_last_position_->y && this->p_symbol_map_->operator[](y)[1] == winparam::weight && text[cur_index] != '\n')
	{
		++y;
		cur_index = this->p_symbol_map_->operator[](y)[0] + this->p_symbol_map_->operator[](y)[1];
	}
	this->p_cur_position_->y = y;
	this->p_cur_position_->x = this->p_symbol_map_->operator[](y)[1] - 1;
	if (this->p_cur_position_->x < 0)
	{
		this->p_cur_position_->x = 0;
	}
	if (this->p_cur_position_->x >= winparam::weight)
	{
		this->NextCursorPos(this->p_cur_position_->y, this->p_cur_position_->x);
	}
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
	this->tui_object->PRefresh();
}

void ConsoleView::DeleteStringPrep(MyString& text, const int index)
{
	int y = this->p_cur_position_->y;
	this->SetToEndString(text);
	if (this->p_cur_position_->x == 0 && y != this->p_cur_position_->y)
	{
		if (this->p_symbol_map_->operator[](y - 1)[1] == winparam::weight+1)
		{
			this->p_cur_position_->y = y - 1;
			this->p_cur_position_->x = winparam::weight - 1;
		}
	}
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
Функция изменяет cur_y основываясь на новой позиции в тексте.
*/

void ConsoleView::SetCurYByIndex(MyString& text, const int index)
{
	int y = this->p_cur_position_->y;
	int length = static_cast<int>(text.Length());
	bool to_begin = false;
	int end_line_index = this->p_symbol_map_->operator[](y)[0] + this->p_symbol_map_->operator[](y)[1];
	if (this->p_symbol_map_->operator[](y)[0] > index) // определеям выше или ниже
	{
		--y;
		while (y != 0 && this->p_symbol_map_->operator[](y)[0] > index)
		{
			--y;
			this->KeyUp();
			this->tui_object->PRefresh();
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
	this->p_cur_position_->x = 0;
	this->p_cur_position_->y = 0;
	this->tui_object->WMove(this->p_cur_position_->y, this->p_cur_position_->x);
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
	this->PrintScreen(text, false, 0);
	this->p_cur_position_->y = temp_y;
	this->p_cur_position_->x = temp_x;
	this->ReturnToCurLine();
	this->tui_object->WMove(temp_y, temp_x);
	this->tui_object->PRefresh();
}



void ConsoleView::SearchWord(MyString& text, const int index)
{
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

