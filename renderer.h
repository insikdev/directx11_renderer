#pragma once

class Pipeline;
class Mesh;

class Renderer {
public:
    Renderer(uint32_t width, uint32_t height, HWND hWnd);
    ~Renderer();

public:
    void Render(void);

private:
    void CreateDeviceAndSwapChain(void);
    void CreateRenderTargetView(void);
    void SetViewport(void);
    void SetPipeline(const Pipeline& pipeline);

private:
    uint32_t m_width;
    uint32_t m_height;
    HWND m_hWnd;
    ComPtr<ID3D11Device> m_device;
    ComPtr<IDXGISwapChain> m_swapChain;
    ComPtr<ID3D11DeviceContext> m_context;
    ComPtr<ID3D11RenderTargetView> m_renderTargetView;
    D3D11_VIEWPORT m_viewport;
    Mesh* mesh;
};
