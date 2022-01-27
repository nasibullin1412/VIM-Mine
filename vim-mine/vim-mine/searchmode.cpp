#include "searchmode.h"

SearchMode::SearchMode():MainMode()
{
	this->is_first_ = true;
	this->search_word_;
	this->type_ = SearchActions::INIT;
	this->founded_indexes_;
	this->start_type_ = SearchActions::INIT;
}

SearchMode::~SearchMode()
{
	this->search_word_.~MyString();
	this->founded_indexes_.clear();
}

bool SearchMode::HandleAction(MyString& command)
{
	int i = 0;
	MyString escape_ = { keys::key_escape };
	if (command.Find(escape_.CStr()) != searchmode::not_found)
	{
		this->type_ = SearchActions::EXIT;
		return true;
	}
	if (this->is_first_ && command.Length() != 1)
	{
		if (command[0] == '/')
		{
			this->start_type_ = SearchActions::SEARCH_TO_END;
			this->type_ = SearchActions::SEARCH_TO_END;
		}
		else
		{
			this->start_type_ = SearchActions::SEARCH_TO_BEGIN;
			this->type_ = SearchActions::SEARCH_TO_BEGIN;
		}
		this->search_word_ = command.Substr(1);
		this->SearchWord();
		return true;
	}
	for (i; i < searchmode::number_of_check; i++)
	{
		if (command.Find(searchmode::check_commands[i].CStr()) != searchmode::not_found)
		{
			break;
		}
	}
	i++;
	command.Clear();
	switch (i)
	{
	case 1:
	{
		if (this->start_type_ == SearchActions::SEARCH_TO_END)
		{
			this->type_ = SearchActions::SEARCH_TO_END;
		}
		else
		{
			this->type_ = SearchActions::SEARCH_TO_BEGIN;
		}
		return true;
	}
	case 2:
	{
		if (this->start_type_ == SearchActions::SEARCH_TO_END)
		{
			this->type_ = SearchActions::SEARCH_TO_BEGIN;
		}
		else
		{
			this->type_ = SearchActions::SEARCH_TO_END;
		}
		return true;
	}
	default:
		break;
	}
	command.Clear();
	return false;
}

ModeType SearchMode::DoAction(int index)
{
	if (this->is_first_)
	{
		*this->index = index;
		this->is_first_ = false;
	}
	switch (this->type_)
	{
	case SearchActions::SEARCH_TO_END:
	{
		this->SearchNext();
		break;
	}
	case SearchActions::SEARCH_TO_BEGIN:
	{
		this->SearchPrev();
		break;
	}
	case SearchActions::EXIT:
	{
		this->is_first_ = true;
		this->search_word_.Clear();
		this->founded_indexes_.clear();
		this->type_ = SearchActions::INIT;
		return ModeType::EDIT_MODE;
	}
	default:
		break;
	}
	return ModeType::SEARCH_MODE;
}

void SearchMode::SearchWord()
{
	int f_index = 0;
	f_index = this->text_->Find(this->search_word_.CStr(), f_index);
	while (f_index != searchmode::not_found)
	{
		this->founded_indexes_.emplace_back(f_index);
		++f_index;
		f_index = this->text_->Find(this->search_word_.CStr(), f_index);
	}
}

void SearchMode::SearchNext()
{
	if (this->founded_indexes_.empty())
	{
		return;
	}
	size_t count = 0;
	size_t size = this->founded_indexes_.size();
	while (count < size && *this->index > this->founded_indexes_[count])
	{
		++count;
	}
	if (count == size)
	{
		return;
	}
	*this->index = this->founded_indexes_[count];
	this->NotifySearchWord(*this->text_, *this->index);
	*this->index += 1;
}

void SearchMode::SearchPrev()
{
	if (this->founded_indexes_.empty())
	{
		return;
	}
	int count = this->founded_indexes_.size() - 1;

	while (count >= 0 && *this->index < this->founded_indexes_[count])
	{
		--count;
	}
	if (count < 0)
	{
		return;
	}
	*this->index = this->founded_indexes_[count];
	this->NotifySearchWord(*this->text_, *this->index);
	*this->index -= 1;
}

