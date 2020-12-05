#ifndef _VIEW_H_
#define _VIEW_H_
#pragma once
#include "mainmode.h"
#include "postion.h"
#include "controller.h"

namespace pan
{
    const MyString  edit_mode = "--EDIT AND NAVIGATE--";
    const MyString  insert_mode = "--INSERT--";
    const MyString  search_mode_to_end = "/";
    const MyString  search_mode_to_begin = "?";
    const MyString  command_mode = ":";
    const MyString  default_file_name = "NONE";
    constexpr int   statistic_begin = 80;
    constexpr int   file_name_begin = 100;
    constexpr int   read_begin = 3;
}



class ConsoleView : public Observer
{
public:
    ConsoleView();
    ~ConsoleView();

    void            InitAllPointers(AdapterPDCur* tui_object, std::vector<std::vector<int>>* p_symbol_map, 
                                 Position* p_last_position_, Position* p_cur_position_, Controller* p_controller);

    void            BeginExecute();


 

    virtual void    PrintScreen(MyString& text, const bool new_string, int index);
    virtual void	ClearScreen();
    virtual void	DoRefreash();
    virtual void    NextCur();
    virtual void    PrevCur();
    virtual void	NewString(MyString& text);
    virtual void    EnterSymbol(MyString& text);
    virtual void	DeleteSymbol(MyString& text, bool delete_line, const int index);
    virtual void	OpneFile(MyString& text, MyString& file_name);
    virtual void	SetToBeginString(MyString& text);
    virtual void	SetToEndString(MyString& text);
    virtual void	DeleteStringPrep(MyString& text, const int index);
    virtual void	ChangeOneSymbol();
    virtual void	ChangeCurFileName(MyString& file_name);
    virtual void	SetCurYByIndex(MyString& text, const int index);
    virtual void	HelpInfo(MyString& help_info, MyString& text);
    virtual void	SearchWord(MyString& text, const int index);
    virtual void	SearchToBegin();
    virtual void	SetCursToWord(MyString& text, const int index);
    virtual void	SetCursRight();
    virtual void	SetCursLeft();
    virtual void    PastPreparation(MyString& text, const int index);

private:
    AdapterPDCur*                   tui_object;
    std::vector<std::vector<int>>*  p_symbol_map_;
    Controller*                     p_controller_;
    Position*                       p_last_position_;
    Position*                       p_cur_position_;
    MyString                        file_name_;
    int                             index_;
    bool                            after_key_;
    bool                            after_beg_str_;
    int                             old_offset_;
    bool                            special_key_;
    bool                            is_search;
    bool                            search_to_begin_;
    bool                            is_enter_symbol;

    MyString                        UpdatePanel(ModeType& type);
    MyString                        GetMyString();
    void                            PrintMyString(const int x, const MyString& string_);
    void                            PrintStatistic();
    bool                            UpCursor(bool to_begin_string, int& y, int& x);
    bool                            DownCursor(bool to_begin_string, int& y, int& x);
    std::vector<int>                CreateNewLine();
    void                            NextCursorPos(int& y, int& x);
    void                            PrevCursorPos(int& y, int& x);
    void                            UpdateKeys(const SpecialKeys type);
    void                            KeyUp();
    void                            KeyDown();
    void                            KeyLeft();
    void                            KeyRight();
    void                            KeyPgUp();
    void                            KeyPgDown();
    void                            KeyEnd();
    void                            KeyHome();
    char                            ReadSymbol();
    bool                            DirectionKeys(const char symbol);
    int                             SetActualIndex(const char symbol);
    bool	                        CheckNewLine();
    int                             NumberOfDigits(int value);
    void                            DeleteLine();
    bool                            IsSpecKeyOnPanel(int& x, int sym, MyString& command_);
    void                            CountAndCreateLines(MyString& text);
    void                            ReturnToCurLine();
    void                            PrintHelpString(MyString& help_info);
    bool                            IsOverflow(char symbol);
    void                            PrinrWithoutEndlSym(int& y, int& x, char symbol, const int idx);
    void                            PrintEndlSymbolNotXZero(int &y, int& x, char symbol, const int idx);
    void                            PrintEndlAfterNewString(int& y, int& x, MyString& text, const int idx);
    void                            PrintEndlAfterEnterSymbol(int& y, int& x, MyString& text, const int idx);
};



#endif