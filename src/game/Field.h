//
// Created by nullifiedvlad on 10.12.2022.
//
#pragma once
#include "vector"
#include <cmath>
#include "Tile.h"
#include "windows.h"
#include <mutex>
namespace gui {class Menu;}

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
        friend  gui::Menu;
    public:
        Field();
        void solve();
        void mix();
        float m_fDelay = 0.1f;
    private:
        std::mutex m_mutexLock;
        void print();
        Tile& at(const Vec2& pos);
        Tile& at(int iVal);
        const Tile& at(const Vec2& pos) const;
        std::vector<Vec2> get_valid_neighbors(const Vec2& pos);
        Vec2 find_tile_cords_by_number(int val) const;
        std::vector<std::vector<Tile>> m_raw;
        std::vector<Vec2> calc_path(const Vec2& from, const Vec2& to);
        void move_empty(const Vec2& end);
        void move(int iVal, const Vec2& end);
        void move_and_lock(int iVal, const Vec2& end);
        void resets_tiles_visited_state();
        void resets_tiles_lock_state();
        template<typename T>
        void print_and_swap(T& a, T& b)
        {
            Sleep(m_fDelay*1000);

            std::lock_guard gurad(m_mutexLock);
            std::swap(a, b);

        }
    };

} // game