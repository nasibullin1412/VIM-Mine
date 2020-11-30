#ifndef _VIEW_H_
#define _VIEW_H_
#pragma once
#include "mainmode.h"
#include "postion.h"

class ConsoleView : public Observer
{
public:
    ConsoleView(std::vector<MainMode*>* model_);
    ~ConsoleView();

    void            InitAllPointers(AdapterPDCur* tui_object, std::vector<std::vector<int>>* p_symbol_map, 
                                 Position* p_last_position_, Position* p_cur_position_);

    virtual int     UpdateKeys(MyString& string_, const SpecialKeys type);
    virtual int     KeyUp();
    virtual int     KeyDown();
    virtual int     KeyLeft();
    virtual int     KeyRight();
    virtual void    PrintScreen(MyString& text, const bool new_string, int index);
    virtual void	ClearScreen();
    virtual void	CheckNewLine();
    virtual void	DoRefreash();
    virtual int		CurPosition();

private:
    AdapterPDCur*                   tui_object;
    std::vector<std::vector<int>>*  p_symbol_map_;
    int                             index_;
    Position*                       p_last_position_;
    Position*                       p_cur_position_;

    bool                            UpCursor(bool to_begin_string, int& y, int& x);
    bool                            DownCursor(bool to_begin_string, int& y, int& x);
    std::vector<int>                CreateNewLine();
    void                            NextCursorPos(int& y, int& x);
    void                            PrevCursorPos(int& y, int& x);
    
    
};



#endif