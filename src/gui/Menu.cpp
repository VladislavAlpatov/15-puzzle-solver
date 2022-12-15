//
// Created by nullifiedvlad on 05.12.2022.
//
#include "Menu.h"
#include <fmt/format.h>


#include  <windows.h>
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imstb_truetype.h"
#include "../imgui/imgui_internal.h"
#include <thread>

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static POINTS oldCursorPos;
    static bool bMoveWindow = false;
    extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
        case WM_LBUTTONDOWN:
            oldCursorPos = MAKEPOINTS(lParam);

            if (oldCursorPos.y <= 15)
                bMoveWindow = true;

            return 0;
        case WM_LBUTTONUP:
            bMoveWindow = false;

        case WM_MOUSEMOVE:
            if (wParam != MK_LBUTTON or !bMoveWindow)
                return 0;

            const auto newCursorPos = MAKEPOINTS(lParam);

            RECT windowRect;
            GetWindowRect(hWnd, &windowRect);



            windowRect.left += newCursorPos.x - oldCursorPos.x;
            windowRect.top += newCursorPos.y - oldCursorPos.y;

            SetWindowPos(hWnd, HWND_TOPMOST, windowRect.left, windowRect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);

            return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}


namespace gui
{

    Menu::~Menu()
    {
        m_pDevice->Release();
        m_pD3D->Release();
    }

    Menu::Menu()
    {
        WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, "ImGui Example", nullptr};
        RegisterClassEx(&wc);
        const HWND hwnd = CreateWindowExA(0, wc.lpszClassName, "ENDURANCE", WS_POPUP, 100, 100, 556, 426, nullptr, nullptr, wc.hInstance, nullptr);


        m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

        ZeroMemory(&m_D3dParams, sizeof(m_D3dParams));

        m_D3dParams.Windowed               = TRUE;
        m_D3dParams.SwapEffect             = D3DSWAPEFFECT_DISCARD;
        m_D3dParams.BackBufferFormat       = D3DFMT_UNKNOWN;
        m_D3dParams.EnableAutoDepthStencil = TRUE;
        m_D3dParams.AutoDepthStencilFormat = D3DFMT_D16;
        m_D3dParams.PresentationInterval   = D3DPRESENT_INTERVAL_ONE;


        m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_D3dParams, &m_pDevice);

        ShowWindow(hwnd, SW_SHOWDEFAULT);
        UpdateWindow(hwnd);


        ImGui::CreateContext();
        const ImGuiIO& io = ImGui::GetIO();
        ImFontConfig cfg;
        static ImWchar ranges[] = { 0x1, 0xFFFD, 0 };
        ImGui::GetIO().Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\verdanab.ttf)",20.f, &cfg, ranges);

        auto& style = ImGui::GetStyle();
        auto& theme = style.Colors;

        style.FrameBorderSize = 1;

        style.AntiAliasedLinesUseTex = false;
        style.AntiAliasedLines       = false;
        style.ScrollbarRounding      = 0.f;

        theme[ImGuiCol_Text]                     = ImColor(255, 255, 255);
        theme[ImGuiCol_TextDisabled]             = ImColor(199, 199, 199);
        theme[ImGuiCol_WindowBg]				 = ImColor(19, 19, 19);
        theme[ImGuiCol_ChildBg]                  = ImColor();
        theme[ImGuiCol_PopupBg]			         = ImColor(19, 19, 19);
        theme[ImGuiCol_Border]			         = ImColor(255, 95, 95);
        theme[ImGuiCol_BorderShadow]	         = ImColor();
        theme[ImGuiCol_FrameBg]                  = ImColor();
        theme[ImGuiCol_FrameBgHovered]		     = ImColor(255,102,102, 90);
        theme[ImGuiCol_FrameBgActive]            = ImColor(255, 255, 255, 90);
        theme[ImGuiCol_Header]			         = ImColor(255, 95, 95);
        theme[ImGuiCol_HeaderActive]             = ImColor(255, 255, 255, 90);
        theme[ImGuiCol_HeaderHovered]            = ImColor(255, 102, 102, 90);
        theme[ImGuiCol_CheckMark]			     = ImColor(255, 95, 95);
        theme[ImGuiCol_Button]		             = ImColor();
        theme[ImGuiCol_ButtonHovered]	         = ImColor(255, 102, 102, 90);
        theme[ImGuiCol_ButtonActive]			 = ImColor(255, 255, 255, 90);
        theme[ImGuiCol_TextSelectedBg]           = ImColor(255, 95, 95);
        theme[ImGuiCol_SliderGrab]		         = ImColor(255, 95, 95);
        theme[ImGuiCol_SliderGrabActive]		 = ImColor(255, 255, 255, 90);
        theme[ImGuiCol_ScrollbarGrabActive]		 = ImColor(255, 255, 255, 90);
        theme[ImGuiCol_ScrollbarGrab]		     = ImColor(255, 95, 95);



        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX9_Init(m_pDevice);
    }

    void Menu::Render()
    {
        while (true)
        {
            MSG msg;
            while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (msg.message == WM_QUIT or GetAsyncKeyState(VK_ESCAPE))
                    exit(0);
            }

            ImGui_ImplDX9_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            Internal();

            ImGui::EndFrame();
            m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
            m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
            m_pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

            m_pDevice->Clear(RGB(0, 0, 0), nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(30, 30, 35, 255), 1.0f, 0);
            if (m_pDevice->BeginScene() >= 0)
            {
                ImGui::Render();
                ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
                m_pDevice->EndScene();
            }
            m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);
        }
    }

    void Menu::Internal()
    {
        ImGui::GetBackgroundDrawList()->AddRectFilled({}, {ImGui::GetMainViewport()->Size.x, 15.f}, ImColor(79, 79, 79));

        m_GameField.m_mutexLock.lock();

        for (int i = 0; i < m_GameField.m_raw.size(); ++i)
            for (int j = 0; j < m_GameField.m_raw.size(); ++j)
                m_GameField.m_raw[i][j].Render(ImVec2(15, 25) + ImVec2{100.f*j, 100.f*i});

        m_GameField.m_mutexLock.unlock();

        ImGui::Begin("Settings",0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove );
        {
            static bool bBusy = false;
            ImGui::SetWindowPos({410, 25});
            ImGui::SetWindowSize({140, 300});
            if (ImGui::Button("SOLVE") and !bBusy)
                std::thread([this](bool *pFlag)
                {
                    *pFlag = true;
                    m_GameField.solve();
                    *pFlag = false;
                }
                , &bBusy).detach();

            if (ImGui::Button("MIX") and !bBusy)
                std::thread([this](bool *pFlag){*pFlag = true; m_GameField.mix(); *pFlag = false;}, &bBusy).detach();

            ImGui::SliderFloat("###sliderf", &m_GameField.m_fDelay, 0.01f, 1.f);
            if (bBusy)
                ImGui::Text("*BUSY*");
            ImGui::End();
        }
    }
} // gui