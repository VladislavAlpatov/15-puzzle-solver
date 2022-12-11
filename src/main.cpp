//
// Created by Vlad on 09.12.2022.
//
#include "Game/Field.h"
#include <stdio.h>

int main()
{
    setbuf(stdout, 0);

    auto field = game::Field();
    field.solve();

}