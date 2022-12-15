//
// Created by nullifiedvlad on 10.12.2022.
//
#pragma once
#include "../imgui/imgui.h"
namespace game
{

    class Tile
    {
    public:
        explicit Tile(int val) {m_iVal = val;}
        int m_iVal;
        bool m_bLock = false;
        bool m_bVisited = false;

        void Render(const ImVec2& pos);
    };

} // game