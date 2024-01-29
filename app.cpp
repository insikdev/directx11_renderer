#include "pch.h"
#include "app.h"
#include "renderer.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

App::App(LONG width, LONG height)
{
    InitWindow(width, height);
    m_renderer = new Renderer { static_cast<uint32_t>(width), static_cast<uint32_t>(height), hWnd };
}

App::~App()
{
    delete m_renderer;
}

void App::Run()
{
    MSG msg {};

    while (msg.message != WM_QUIT) {
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        } else {
            m_renderer->Update();
            m_renderer->Render();
        }
    }
}

void App::InitWindow(LONG width, LONG height)
{
    WNDCLASSEXW wcex {};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = App::WndProc;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.lpszClassName = TEXT("DirectX11");

    if (::RegisterClassEx(&wcex) == 0) {
        throw std::exception();
    }

    RECT windowRect = { 0, 0, width, height };
    ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);
    int windowWidth = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;

    hWnd = ::CreateWindow(wcex.lpszClassName, TEXT("renderer"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, windowWidth, windowHeight, nullptr, nullptr, nullptr, nullptr);

    if (!hWnd) {
        throw std::exception();
    }

    ::ShowWindow(hWnd, SW_SHOW);
    ::UpdateWindow(hWnd);
}

LRESULT App::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) {
        return true;
    }

    switch (message) {
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            ::PostQuitMessage(0);
            return 0;
        }
        break;
    }

    return ::DefWindowProc(hWnd, message, wParam, lParam);
}
