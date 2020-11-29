#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#pragma once
#include "mainmode.h"
#include <cstdio>
#include <vector>


class Controller
{
public:
    Controller(std::vector<MainMode*>* model, AdapterPDCur& tui_object);
    ~Controller();
    void start();
private:
    std::vector<MainMode*> *model_;
    AdapterPDCur tui_object;
	MyString command_;
    ModeType mode_type_;
	bool ReadSymbol();
    void ChangeType(const ModeType &new_mode);
};

#endif