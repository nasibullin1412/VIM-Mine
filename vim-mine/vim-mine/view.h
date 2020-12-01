#ifndef _VIEW_H_
#define _VIEW_H_
#pragma once
#include "mainmode.h"
#include "postion.h"
#include "controller.h"

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

private:
    AdapterPDCur*                   tui_object;
    std::vector<std::vector<int>>*  p_symbol_map_;
    Controller*                     p_controller_;
    Position*                       p_last_position_;
    Position*                       p_cur_position_;
    int                             index_;

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
    char                            ReadSymbol();
    bool                            DirectionKeys(const char symbol);
    int                             SetActualIndex(const char symbol);
    bool	                        CheckNewLine();
    
};



#endif