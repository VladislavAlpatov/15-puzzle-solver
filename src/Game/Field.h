//
// Created by nullifiedvlad on 10.12.2022.
//
#pragma once
#include "vector"
#include <cmath>
#include "Tile.h"
#include "windows.h"
namespace game
{
    class Vec2
    {
    public:
        float x= 0.f;
        float y = 0.f;
        Vec2() = default;
        Vec2(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        float DistanceTo(const Vec2& other) const
        {
            auto diff = *this - other;

            return sqrt(diff.x*diff.x + diff.y*diff.y);
        }
        Vec2 operator-(const Vec2& other) const
        {
            return {x - other.x, y - other.y};
        }
        Vec2 operator+(const Vec2& other) const
        {
            return {x + other.x, y + other.y};
        }

        bool operator==(const Vec2& other) const
        {
            return x == other.x and y == other.y;
        }
        bool operator!=(const Vec2& other) const
        {
            return !(*this == other);
        }
    };

    class Field
    {
    public:
        Field();
        void Print();
        Tile& at(const Vec2& pos);
        Tile& at(const int iVal);
        const Tile& at(const Vec2& pos) const;
        std::vector<Vec2> GetNeighbors(const Vec2& pos);
        Vec2 FindTile(int val) const;
        std::vector<std::vector<Tile>> m_raw;
        std::vector<Vec2> CalcPath(const Vec2& from, const Vec2& to);
        void move_empty(const Vec2& end);
        void move(int iVal, const Vec2& end);
        void move_and_lock(int iVal, const Vec2& end);
        void normalize_first_line();
        void resets_tiles_visited_state();

        template<typename T>
        void pswap(T& a, T& b)
        {
            Print();
            std::swap(a, b);
            Sleep(100);
            Print();
        }
    };

} // game