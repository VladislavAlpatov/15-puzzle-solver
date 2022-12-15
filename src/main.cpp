//
// Created by Vlad on 09.12.2022.
//
#include <stdio.h>
#include "gui/Menu.h"
int main()
{
    setbuf(stdout, 0);

    gui::Menu().Render();

    auto field = game::Field();
    field.solve();

}