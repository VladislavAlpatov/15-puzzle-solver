//
// Created by Vlad on 09.12.2022.
//
#include "Game/Field.h"
#include <stdio.h>

int main()
{
    setbuf(stdout, 0);

    auto field = game::Field();
    // field.Print();

    // Make first line ready
    field.move_and_lock(1,{});
    field.move_and_lock(2,{1.f, 0.f});
    field.move_and_lock(4,{2.f, 0.f});
    field.move_and_lock(3,{2.f, 1.f});


    // Fix first line right corner
    field.move_empty({3.f, 0.f});
    field.move_and_lock(4,{3.f, 0.f});
    field.move_and_lock(3,{2.f, 0.f});

    // Make second line ready
    field.move_and_lock(5, {0.f, 1.f});
    field.move_and_lock(6, {1.f, 1.f});
    field.move_and_lock(8, {2.f, 1.f});
    field.move_and_lock(7, {2.f, 2.f});


    // Fix second line corner
    field.move_empty({3.f, 1.f});
    field.move_and_lock(8,{3.f, 1.f});
    field.move_and_lock(7,{2.f, 1.f});

    // Getting bottom corner ready
    field.move_and_lock(13,{0.f, 2.f});
    field.move_and_lock(9,{1.f, 2.f});

    // Fix bottom corner
    field.move_and_lock(13, {0.f,3.f});
    field.move_and_lock(9, {0.f, 2.f});

    // Getting 14 and 10 ready
    field.move_and_lock(14, {1.f,2.f});
    field.move_and_lock(10, {2.f,2.f});

    // Fix 14 and 10
    field.move_and_lock(14, {1.f,3.f});
    field.move_and_lock(10, {1.f,2.f});

    field.move_and_lock(11, {2.f,2.f});
    field.move_and_lock(12, {3.f,2.f});

}