//
// Created by Vlad on 09.12.2022.
//
#include "Game/Field.h"
#include <stdio.h>
#include "windows.h"

int main()
{
    setbuf(stdout, 0);

    auto field = game::Field();


    field.move_and_lock(1,{});
    field.move_and_lock(2,{1.f, 0.f});
    field.move_and_lock(4,{2.f, 0.f});
    field.move_and_lock(3,{2.f, 1.f});
    field.move_empty({3.f, 0.f});

    field.at(4).m_bLock = false;
    field.move_and_lock(4,{3.f, 0.f});
    field.at(3).m_bLock = false;
    field.move_and_lock(3,{2.f, 0.f});

    field.move_and_lock(5, {0.f, 1.f});
    field.move_and_lock(6, {1.f, 1.f});
    field.move_and_lock(8, {2.f, 1.f});
    field.move_and_lock(7, {2.f, 2.f});

    field.move_empty({3.f, 2.f});
    field.Print();
}