#include "pch.h"
#include "app.h"
#include "renderer.h"

App::App(uint32_t width, uint32_t height)
    : m_width { width }
    , m_height { height }
{
    InitWindow();
    m_renderer = new Renderer {};
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
        }
    }
}

void App::InitWindow(void)
{
    WNDCLASSEXW wcex {};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = App::WndProc;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.lpszClassName = TEXT("DirectX11");

    if (::RegisterClassEx(&wcex) == 0) {
        SPDLOG_ERROR("Failed to register class.");
        exit(EXIT_FAILURE);
    }

    RECT windowRect = { 0, 0, 1280, 720 };
    ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);
    const int width = windowRect.right - windowRect.left;
    const int height = windowRect.bottom - windowRect.top;

    hWnd = ::CreateWindow(wcex.lpszClassName, TEXT("renderer"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, width, height, nullptr, nullptr, nullptr, nullptr);

    if (!hWnd) {
        SPDLOG_ERROR("Failed to create window.");
        exit(EXIT_FAILURE);
    }

    ::ShowWindow(hWnd, SW_SHOW);
    ::UpdateWindow(hWnd);
}

LRESULT App::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
