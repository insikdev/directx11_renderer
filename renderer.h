#pragma once

#include "camera.h"
class Pipeline;
class Mesh;

class Renderer {
public:
    Renderer(uint32_t width, uint32_t height, HWND hWnd);
    ~Renderer();

public:
    void Update(void);
    void Render(void);

private:
    void CreateDeviceAndSwapChain(void);
    void CreateRenderTargetView(void);
    void CreateDepthStencilView(void);
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
    ComPtr<ID3D11DepthStencilView> m_depthStencilView;
    D3D11_VIEWPORT m_viewport;
    float m_clearColor[4] { 1.0f, 1.0f, 1.0f, 1.0f };

private:
    std::vector<Mesh*> m_meshes;
    ComPtr<ID3D11Buffer> m_commonConstantBuffer;
    CommonConstant m_commonConstantData {};
    Camera camera;

private:
    Mesh* m_skybox;
    ComPtr<ID3D11ShaderResourceView> m_envDiffuse;
};
