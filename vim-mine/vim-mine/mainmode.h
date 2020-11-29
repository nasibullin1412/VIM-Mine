#ifndef _MAINMODE_H_
#define _MAINMODE_H_
#pragma once
#include "observ.h"
#include "mystring.h"
#include "postion.h"
#include <vector>
#include <array>
#include <Windows.h>


namespace modeconst
{
	constexpr int special_key = -32;
	constexpr int escape_key = 27;
	constexpr int backspace_key = 58;
}

class MainMode : public Observable
{
public:
	MainMode(MyString *text, Position *plast_position, Position *pcur_position, std::vector<size_t>* p_indexes_of_strings);
	~MainMode();
	virtual bool HandleAction(MyString& command, AdapterPDCur& tui_object) = 0;
	virtual ModeType DoAction(AdapterPDCur &tui_object) = 0;
	
	void InitAllPointers(size_t* p_number_of_string_, size_t* p_string_number, int* p_index_, std::vector<std::vector<int>>* p_symbol_map);
	MyString GetText();
protected:
	MyString *text_;
	std::vector<size_t>* p_indexes_of_strings_;
	Position* plast_position_;
	Position* pcur_position_;
	size_t* p_number_of_string_;
	size_t* p_string_number;
	int* p_index_;
	std::vector<std::vector<int>>* p_symbol_map_;
	bool change_;
	bool UpdateIndexes(size_t start_string, int value_update);
	void NextCursorPos(AdapterPDCur& tui_object, int &y, int &x);
	void PrevCursorPos(AdapterPDCur& tui_object, int& y, int& x);
	std::vector<int> CreateNewLine();

	//void CountCurNumStrIndex(const int cur_x, const int cur_y);

};


#endif