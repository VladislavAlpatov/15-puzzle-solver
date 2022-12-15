//
// Created by nullifiedvlad on 10.12.2022.
//
#include "Tile.h"
#include "../imgui/imgui_internal.h"
#include <fmt/format.h>

void TextCentered(const ImVec2& pos, std::string text)
{
    auto centered_pos = pos-ImGui::CalcTextSize(text.c_str()) * 0.5f;
    ImGui::GetBackgroundDrawList()->AddText(centered_pos,ImColor(255, 255, 255), text.c_str());
}

namespace game
{
    void Tile::Render(const ImVec2& pos)
    {
        auto pDrawList = ImGui::GetBackgroundDrawList();

        if (m_iVal != 0)
        {
            pDrawList->AddRectFilled(pos, pos+ImVec2(90, 90), ImColor(255, 77, 77));
            TextCentered(pos+ImVec2(45, 45), fmt::format("{}", m_iVal));
        }
        else
            pDrawList->AddRect(pos, pos+ImVec2(90, 90), ImColor(255, 77, 77));


    }
} // game