#include "observ.h"




Observable::~Observable()
{
}

void  Observable::AddObserver(Observer* observer)
{
    observers_.push_back(observer);
}

void Observable::NotifyPrintScreen(MyString& text, const bool new_string, int index)
{
    observers_[0]->PrintScreen(text, new_string, index);   
}

void Observable::NotifyClearScreen()
{
    observers_[0]->ClearScreen();
}

void Observable::NotifyCheckNewLine()
{
    observers_[0]->CheckNewLine();
}

void Observable::NotifyDoRefreash()
{
    observers_[0]->DoRefreash();
}

void Observable::NotifyNextCurs()
{
    this->observers_[0]->NextCur();
}

void Observable::NotifyPrevCurs()
{
    this->observers_[0]->PrevCur();
}

void Observable::NotifyNewString(MyString& text)
{
    this->observers_[0]->NewString(text);
}

