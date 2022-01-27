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

    ModeType          InfoController(const int index, MyString &command);
private:
    std::vector<MainMode*>*     model_;
    MyString                    command_;
    ModeType                    mode_type_;
    void                        ChangeType(const ModeType &new_mode);
};

#endif