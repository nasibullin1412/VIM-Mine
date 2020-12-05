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

void Observable::NotifyEnterSymbol(MyString& text)
{
    this->observers_[0]->EnterSymbol(text);
}

void Observable::NotifyDeleteSymbol(MyString& text, bool delete_line, const int index)
{
    this->observers_[0]->DeleteSymbol(text, delete_line, index);
}

void Observable::NotifyOpenFile(MyString& text, MyString& file_name)
{
    this->observers_[0]->OpneFile(text, file_name);
}

void Observable::NotifySetToBeginString(MyString& text)
{
    this->observers_[0]->SetToBeginString(text);
}

void Observable::NotifySetToEndString(MyString& text)
{
    this->observers_[0]->SetToEndString(text);
}

void Observable::NotifyDeleteStringPrep(MyString& text, const int index)
{
    this->observers_[0]->DeleteStringPrep(text, index);
}

void Observable::NotifyChangeOneSymbol()
{
    this->observers_[0]->ChangeOneSymbol();
}

void Observable::NotifyChangeCurFileName(MyString& file_name)
{
    this->observers_[0]->ChangeCurFileName(file_name);
}

void Observable::NotifySetCurYByIndex(MyString& text, const int index)
{
    this->observers_[0]->SetCurYByIndex(text, index);
}

void Observable::NotifyHelpInfo(MyString& help_info, MyString& text)
{
    this->observers_[0]->HelpInfo(help_info, text);
}

void Observable::NotifySearchWord(MyString& text, const int index)
{
    this->observers_[0]->SearchWord(text, index);
}

void Observable::NotifySearchToBegin()
{
    this->observers_[0]->SearchToBegin();
}

void Observable::NotifySetToWord(MyString& text, const int index)
{
    this->observers_[0]->SetCursToWord(text, index);
}

void Observable::NotifySetCursRight()
{
    this->observers_[0]->SetCursRight();
}

void Observable::NotifySetCursLeft()
{
    this->observers_[0]->SetCursLeft();
}

