#ifndef _SEARCHMODE_H_
#define _SEARCHMODE_H_
#pragma once
#include "mainmode.h"

namespace searchmode
{
	constexpr int number_of_check = 2;
	const std::array < MyString, number_of_check>check_commands = { "n", "N" };
	constexpr int not_found = -1;
}


enum class SearchActions
{
	INIT,
	SEARCH_TO_END,
	SEARCH_TO_BEGIN,
	EXIT
};

class SearchMode : public MainMode
{
public:
	SearchMode();
	~SearchMode();
	virtual bool		HandleAction(MyString& command);
	virtual ModeType	DoAction(int index);

private:
	bool				is_first_;
	SearchActions		type_;
	SearchActions		start_type_;
	MyString			search_word_;
	std::vector<int>	founded_indexes_;


	void				SearchWord();
	void				SearchNext();
	void				SearchPrev();
};

#endif