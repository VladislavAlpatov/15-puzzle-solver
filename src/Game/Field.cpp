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

        m_raw.push_back({Tile(5), Tile(7), Tile(6), Tile(4)});
        m_raw.push_back({Tile(11), Tile(13), Tile(1), Tile(15)});
        m_raw.push_back({Tile(10), Tile(3), Tile(8), Tile(14)});
        m_raw.push_back({Tile(2), Tile(12), Tile(9), Tile(0)});
    }

    void Field::Print()
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
} // game