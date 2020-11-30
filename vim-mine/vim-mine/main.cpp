#include "controller.h"
#include "editmode.h"
//#include "entercommandmode.h"
//#include "searchmode.h"
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
	std::vector<int> first_string(winparam::weight + 2, -1);
	first_string[0] = 0;
	map.emplace_back(first_string);
	EditMode obj;
	obj.InitAllPointers(&text_, &index);
	list_.emplace_back(&obj);




	EnterSymbolMode obj_last;
	obj_last.InitAllPointers(&text_, &index);
	
	
	
	list_.emplace_back(&obj_last);
	AdapterPDCur tui_object;

	ConsoleView view_(&list_);
	view_.InitAllPointers(&tui_object, &map, &last_position, &cur_position);
	Controller contrl_(&list_, &tui_object);
	contrl_.start();



}

