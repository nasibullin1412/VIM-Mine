#include "observ.h"




Observable::~Observable()
{
}

void  Observable::AddObserver(Observer* observer)
{
    _observers.push_back(observer);
}

int Observable::NotifyUpdateKeys(MyString& string_, const SpecialKeys type_)
{
    return _observers[0]->UpdateKeys(string_, type_);
}

int Observable::NotifyPrintScreen(MyString& text, const bool new_string, int index)
{
    return _observers[0]->PrintScreen(text, new_string, index);   
}

