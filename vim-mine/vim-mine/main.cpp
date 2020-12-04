#include "controller.h"
#include "editmode.h"
#include "commode.h"
#include "entersymbolmode.h"
#include "view.h"


int main()
{
	MyString text_;
	std::vector<MainMode*> list_;
	Position last_position;
	Position cur_position;
	int index = 0;
	std::vector<std::vector<int>> map;
	std::vector<int> first_string(2, 0);
	first_string[0] = 0;
	map.emplace_back(first_string);
	ConsoleView view_;
	bool r_mode_insert = false;
	char new_symbol = 0;
	EditMode obj;
	obj.AddObserver(&view_);
	obj.InitAllPointers(&text_, &r_mode_insert, &index, &new_symbol);
	

	EnterSymbolMode obj_last;
	obj_last.AddObserver(&view_);
	obj_last.InitAllPointers(&text_, &r_mode_insert, &index, &new_symbol);

	ComMode commode_obj;
	commode_obj.AddObserver(&view_);
	commode_obj.InitAllPointers(&text_, &r_mode_insert, &index, &new_symbol);

	list_.emplace_back(&obj);
	list_.emplace_back(&obj_last);
	list_.emplace_back(&commode_obj);
	AdapterPDCur tui_object;
	Controller contr_object(&list_);
	view_.InitAllPointers(&tui_object, &map, &last_position, &cur_position, &contr_object);
	view_.BeginExecute();

	


}

