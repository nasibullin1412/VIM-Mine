#include "adapterpdcur.h"

AdapterPDCur::AdapterPDCur()
{
	this->screen_ = nullptr;
	this->pad_ = nullptr;
	this->pannel_ = nullptr;
	this->offset_x_ = 0;
	this->offset_y_ = 0;
}

AdapterPDCur::~AdapterPDCur()
{

}

int AdapterPDCur::WMove(const int y, const int x)
{
	return wmove(this->pad_, y, x);
}

int AdapterPDCur::WPanMove(const int y, const int x)
{
	return wmove(this->pannel_, y, x);
}


int AdapterPDCur::EndWin()
{
	return endwin();
}


int AdapterPDCur::MvwPrintw(int y, int x, char sym)
{
	mvwprintw(this->pad_, y, x, "%c", sym);
	return 0;
}

int AdapterPDCur::Box(const chtype symbol_hieght, const chtype symbol_weight)
{
	return box(this->pad_, symbol_hieght, symbol_weight);
}

int AdapterPDCur::WBorder(const chtype left_side, const chtype right_side, const chtype top_side,
	const chtype bottom_side, const chtype top_left_hand, const chtype top_right_hand, const chtype bottom_left, const chtype bottom_right)
{
	return wborder(this->pad_, left_side, right_side, top_side,
		 bottom_side, top_left_hand, top_right_hand, bottom_left, bottom_right);
}

int AdapterPDCur::Raw()
{
	return raw();
}

int AdapterPDCur::GetYX(int &y, int &x)
{
	return getyx(this->pad_, y, x);
}

int AdapterPDCur::GetMaxYX(int &y, int &x)
{
	return getmaxyx(this->pad_, y, x);
}

int AdapterPDCur::Keypad(const bool mode)
{
	return keypad(this->pad_, mode);
}

int AdapterPDCur::Echo()
{
	return echo();
}

int AdapterPDCur::NoEcho()
{
	return noecho();
}

int AdapterPDCur::MVWGetch(const int y, const int x)
{
	return mvwgetch(this->pad_, y, x);
}

int AdapterPDCur::GetCh()
{
	return wgetch(this->pad_);
}

int AdapterPDCur::PRefresh()
{
	return prefresh(this->pad_, this->offset_y_, 0, this->offset_x_, 0, winparam::height, winparam::weight);
}

int AdapterPDCur::DeleteWin()
{
	return delwin(this->pad_);
}





int AdapterPDCur::ClrToBot()
{
	return wclrtobot(this->pad_);
}

int AdapterPDCur::GetOffsetY()
{
	return this->offset_y_;
}

int AdapterPDCur::GetOffsetX()
{
	return this->offset_x_;
}

bool AdapterPDCur::ChangeOffsetX(int change_)
{
	int check_sum = this->offset_x_ + change_;
	if (check_sum >= 0)
	{
		this->offset_x_ = check_sum;
	}
	return false;
}

bool AdapterPDCur::ChangeOffsetY(int change_)
{
	int check_sum = this->offset_y_ + change_;
	if (check_sum >= 0)
	{
		this->offset_y_ = check_sum;
	}
	return false;
}

int AdapterPDCur::MvwPtintInt(int y, int x, int value)
{
	mvwprintw(this->pannel_, y, x, "%d", value);
	return 0;
}

bool AdapterPDCur::NewWin(int height, int width, int start_y, int start_x)
{
	this->pannel_ = newwin(height, width, start_y, start_x);
	if (this->pannel_ == nullptr)
	{
		return false;
	}
	return true;
}

void AdapterPDCur::WRefresh()
{
	wrefresh(this->pannel_);
}

void AdapterPDCur::ClearPannel()
{
	wclear(this->pannel_);
}






bool AdapterPDCur::InitScr()
{
	this->pad_ = initscr();
	if (this->pad_)
	{
		return true;
	}
	return false;
}

bool AdapterPDCur::NewPad(const int height, const int weight)
{
	this->pad_ = newpad(height, weight);
	if (this->pad_)
	{
		return true;
	}
	return false;
}



WINDOW* AdapterPDCur::GetWindow()
{
	return this->pad_;
}

WINDOW* AdapterPDCur::GetPad()
{
	return this->pad_;
}


void AdapterPDCur::Mvwscanf(int y, int x, MyString& string_)
{
	mvwscanw(this->pannel_, y, x, "%s", string_.CStr());
}

void AdapterPDCur::MvwprintPannel(int y, int x, char sym)
{
	mvwprintw(this->pannel_, y, x, "%c", sym);
}
