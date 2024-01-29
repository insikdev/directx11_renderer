#pragma once

class Gui {
public:
    Gui(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context);
    ~Gui();

public:
    void Render(void);
};
