#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#pragma once
#include "mainmode.h"
#include <cstdio>
#include <vector>


class Controller
{
public:
    Controller(std::vector<MainMode*>* model);
    ~Controller();

    bool          InfoController(const int index, const char symbol);
private:
    std::vector<MainMode*>*     model_;
    MyString                    command_;
    ModeType                    mode_type_;
    void                        ChangeType(const ModeType &new_mode);
};

#endif