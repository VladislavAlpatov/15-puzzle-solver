//
// Created by nullifiedvlad on 10.12.2022.
//
#pragma once
namespace game
{

    class Tile
    {
    public:
        explicit Tile(int val) {m_iVal = val;}
        int m_iVal;
        bool m_bLock = false;
        bool m_bVisited = false;
    };

} // game