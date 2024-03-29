#ifndef _ADAPTERPDCUR_H_
#define _ADAPTERPDCUR_H_
#pragma once
#include "curses.h"
#include "mystring.h"

namespace keys
{
	constexpr char key_up = static_cast<char>(KEY_UP);
	constexpr char key_down = static_cast<char>(KEY_DOWN);
	constexpr char key_left = static_cast<char>(KEY_LEFT);
	constexpr char key_right = static_cast<char>(KEY_RIGHT);
	constexpr char key_pg_up = static_cast<char>(KEY_PPAGE);
	constexpr char key_pg_down = static_cast<char>(KEY_NPAGE);
	constexpr char key_enter = 10;
	constexpr char key_escape = 27;
	constexpr char key_backspace = 8;
}

namespace border_
{
	constexpr chtype left_symbol = '~';
	constexpr chtype right_symbol = '|';
	constexpr chtype top_symbol = ' ';
	constexpr chtype bottom_symbol = ' ';
	constexpr chtype top_left_symbol = ' ';
	constexpr chtype top_right_symbol = '|';
	constexpr chtype bottom_right_symbol = '|';
	constexpr chtype bottom_left_symbol = ' ';
}

namespace winparam
{
	constexpr int height = 29;
	constexpr int weight = 119;
	constexpr int r_postion = 119;
	constexpr int n_postion = 120;
	constexpr int real_size = 10000;
}

class AdapterPDCur
{
public:
	AdapterPDCur();
	~AdapterPDCur();
	bool    InitScr();
	bool	NewPad(const int height, const int weight);
	WINDOW* GetWindow();
	WINDOW* GetPod();
	int		WMove(const int y, const int x);
	int		EndWin();
	int		MvwPrintw(int y, int x, char sym);
	int		Box(const chtype symbol_hieght, const chtype symbol_weight);
	int		WBorder(const chtype left_side, const chtype right_side, const chtype top_side, const chtype bottom_side,
				const chtype top_left_hand, const chtype top_right_hand, const chtype bottom_left, const chtype bottom_right);
	int		Raw();
	int		GetYX(int &y, int &x);
	int		GetMaxYX(int &y, int &x);
	int		Keypad(const bool mode);
	int		Echo();
	int		NoEcho();
	int		MVWGetch(const int y, const int x);
	int		GetCh();
	int		PRefresh();
	int		DeleteWin();
	void	HidePanelPosition();
	int		ClrToBot();
	int		GetOffsetY();
	int		GetOffsetX();
	bool	ChangeOffsetX(int cange_);
	bool	ChangeOffsetY(int change_);
	//int		WPrint(const char* put_string, ...);
private:
	WINDOW* screen_;
	WINDOW* pad_;
	int		offset_y_;
	int		offset_x_;

};





#endif