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
	this->DeleteWin();
	this->screen_ = nullptr;
	this->pad_ = nullptr;
	this->pannel_ = nullptr;
	this->offset_x_ = 0;
	this->offset_y_ = 0;
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
	return prefresh(this->pad_, this->offset_y_, 0, this->offset_x_, 0, winparam::height, winparam::width);
}

int AdapterPDCur::DeleteWin()
{
	wmove(this->pannel_, 0, 0);
	wmove(this->pad_, 0, 0);
	wclrtobot(this->pad_);
	wclrtobot(this->pannel_);
	this->PRefresh();
	this->WRefresh();
	delwin(this->pad_);
	delwin(this->pannel_);
	delwin(this->screen_);
	return 0;
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


int AdapterPDCur::Mvwscanf(int y, int x)
{
	return mvwgetch(this->pannel_, y, x);
}

void AdapterPDCur::MvwprintPannel(int y, int x, char sym)
{
	mvwprintw(this->pannel_, y, x, "%c", sym);
}
