//
// Created by nullifiedvlad on 05.12.2022.
//
#pragma once
#include <d3d9.h>
#include "../game/Field.h"


namespace gui
{

    class Menu
    {
    public:
        Menu();
        ~Menu();
        void Render();
        void Internal();
    private:
        game::Field m_GameField;

        LPDIRECT3D9              m_pD3D;
        LPDIRECT3DDEVICE9        m_pDevice;
        D3DPRESENT_PARAMETERS    m_D3dParams;
    };

} // gui