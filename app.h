#pragma once

class Renderer;

class App {
public:
    App(LONG width, LONG height);
    ~App();

public:
    void Run();

private:
    void InitWindow(LONG width, LONG height);
    static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

private:
    HWND hWnd;
    Renderer* m_renderer;
};
