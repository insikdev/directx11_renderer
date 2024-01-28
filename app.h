#pragma once

class Renderer;

class App {
public:
    App(uint32_t width, uint32_t height);
    ~App();

public:
    void Run();

private:
    void InitWindow(void);
    static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

private:
    HWND hWnd;
    uint32_t m_width;
    uint32_t m_height;
    Renderer* m_renderer;
};
