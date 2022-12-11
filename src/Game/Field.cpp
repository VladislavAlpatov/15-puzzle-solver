//
// Created by nullifiedvlad on 10.12.2022.
//
#include "Field.h"
#include <stdio.h>
#include <algorithm>


namespace game
{

    Field::Field()
    {
        m_raw.reserve(4);

        m_raw.push_back({Tile(11), Tile(13), Tile(3), Tile(9)});
        m_raw.push_back({Tile(10), Tile(7), Tile(4), Tile(6)});
        m_raw.push_back({Tile(12), Tile(1), Tile(14), Tile(2)});
        m_raw.push_back({Tile(0), Tile(5), Tile(8), Tile(15)});
    }

    void Field::print()
    {
        system("cls");
        for (const auto& row : m_raw)
        {
            for (const auto tile: row)
                printf("%d  ", tile.m_iVal);
            printf("\n");

        }
    }

    Tile &Field::at(const Vec2& pos)
    {
        return m_raw[(int)pos.y][(int)pos.x];
    }
    const Tile &Field::at(const Vec2& pos) const
    {
        return m_raw[(int)pos.y][(int)pos.x];
    }

    std::vector<Vec2> Field::GetNeighbors(const Vec2 &pos)
    {
        std::vector<Vec2> valid;
        std::vector<Vec2> allPossibleNeighbors =
                {
                pos+Vec2(0, -1),
                pos+Vec2(0, 1),
                pos+Vec2(-1, 0),
                pos+Vec2(1, 0)
                };

        for (const auto& neighbor_pos : allPossibleNeighbors)
            if ((neighbor_pos.x >= 0 and neighbor_pos.x < 4 and neighbor_pos.y >= 0 and neighbor_pos.y < 4) and !at(neighbor_pos).m_bLock and !at(neighbor_pos).m_bVisited)
                valid.push_back(neighbor_pos);

        return valid;
    }

    Vec2 Field::FindTile(int val) const
    {

        for (size_t i = 0; i < m_raw.size(); i++)
            for (size_t j = 0; j < m_raw.size(); j++)
                if (m_raw[i][j].m_iVal == val)
                    return Vec2(j, i);


        return {};
    }

    std::vector<Vec2> Field::CalcPath(const Vec2 &from, const Vec2 &to)
    {
        std::vector<Vec2> path = {from};

        auto currentPoint = from;

        while (currentPoint != to)
        {
            at(currentPoint).m_bVisited = true;
            auto neighbors = GetNeighbors(currentPoint);

            // This check fixes bug when algorithm choose randomly path that has dead end
            if (neighbors.empty())
            {
                path = {from};
                currentPoint = from;
                continue;
            }

            std::sort(neighbors.begin(), neighbors.end(), [to, from](const Vec2& first, const Vec2& second) -> bool
            {
                return first.DistanceTo(to) < second.DistanceTo(to);
            } );


            currentPoint = neighbors.at(0);
            path.push_back(currentPoint);
        }
        resets_tiles_visited_state();
        return path;
    }

    void Field::move_empty(const Vec2 &end)
    {
        const auto path = CalcPath(FindTile(0), end);

        if (path.size() <= 1)
            return;

        for (int i = 0; i < path.size()-1; ++i)
        {
            pswap(at(path[i]), at(path[i+1]));
        }
    }

    void Field::move(int iVal, const Vec2 &end)
    {
        auto startPos = FindTile(iVal);
        const auto path = CalcPath(startPos, end);

        at(iVal).m_bLock = true;

        if (path.size() <= 1)
        {
            at(startPos).m_bLock = false;
            return;
        }

        for (size_t i = 0; i < path.size()-1;i++)
        {
            move_empty(path[i+1]);
            pswap(at(path[i]), at(path[i+1]));
        }

        at(iVal).m_bLock = false;
    }

    Tile &Field::at(const int iVal)
    {
        return at(FindTile(iVal));
    }

    void Field::move_and_lock(int iVal, const Vec2 &end)
    {
        move(iVal,end);
        at(iVal).m_bLock = true;
    }

    void Field::resets_tiles_visited_state()
    {
        for (auto& row : m_raw)
            for (auto& tile : row)
                tile.m_bVisited = false;
    }

    void Field::solve()
    {
        move_and_lock(1,{});
        move_and_lock(2,{1.f, 0.f});
        move_and_lock(4,{2.f, 0.f});
        move_and_lock(3,{2.f, 1.f});


        // Fix first line right corner
        move_empty({3.f, 0.f});
        move_and_lock(4,{3.f, 0.f});
        move_and_lock(3,{2.f, 0.f});

        // Make second line ready
        move_and_lock(5, {0.f, 1.f});
        move_and_lock(6, {1.f, 1.f});
        move_and_lock(8, {2.f, 1.f});
        move_and_lock(7, {2.f, 2.f});


        // Fix second line corner
        move_empty({3.f, 1.f});
        move_and_lock(8,{3.f, 1.f});
        move_and_lock(7,{2.f, 1.f});

        // Getting bottom corner ready
        move(9,{3.f, 3.f});
        move_and_lock(13,{0.f, 2.f});
        move_and_lock(9,{1.f, 2.f});
        // Fix bottom corner
        move_and_lock(13, {0.f,3.f});
        move_and_lock(9, {0.f, 2.f});

        // Getting 14 and 10 ready
        move(10, {3.f,3.f});
        move_and_lock(14, {1.f,2.f});
        move_and_lock(10, {2.f,2.f});

        // Fix 14 and 10
        move_and_lock(14, {1.f,3.f});
        move_and_lock(10, {1.f,2.f});

        move_and_lock(11, {2.f,2.f});
        move_and_lock(12, {3.f,2.f});
        move_and_lock(15, {2.f,3.f});
    }
} // game