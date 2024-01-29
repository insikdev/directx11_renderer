#include "pch.h"
#include "renderer.h"
#include "graphics_common.h"
#include "pipeline.h"
#include "geometry.h"
#include "mesh.h"
#include "utils.h"
#include "gui.h"

Renderer::Renderer(uint32_t width, uint32_t height, HWND hWnd)
    : m_width { width }
    , m_height { height }
    , m_hWnd { hWnd }
    , camera { static_cast<float>(width) / height }
{
    CreateDeviceAndSwapChain();
    CreateRenderTargetView();
    CreateDepthStencilView();
    SetViewport();

    m_gui = new Gui { hWnd, m_device.Get(), m_context.Get() };
    Graphics::Initialize(m_device);

    Mesh* cube = new Mesh { m_device, Geometry::CreateCube() };
    Utils::CreateTextureFromFile(m_device, TEXT("C:/assets/images/crate2_diffuse.png"), cube->diffuseSRV);
    m_meshes.push_back(cube);

    Utils::CreateConstantBuffer<CommonConstant>(m_device, m_commonConstantData, m_commonConstantBuffer);

    m_skybox = new Mesh { m_device, Geometry::CreateCube() };
    Utils::CreateDDSTextureFromFile(m_device, TEXT("C:/assets/cubemap/skybox.dds"), m_envDiffuse);
}

Renderer::~Renderer()
{
    for (Mesh* m : m_meshes) {
        delete m;
    }

    delete m_skybox;
    delete m_gui;
}

void Renderer::Update(void)
{
    float dt = ImGui::GetIO().DeltaTime;

    camera.Update(dt);

    m_commonConstantData.view = camera.GetView();
    m_commonConstantData.proj = camera.GetProj();

    Utils::UpdateConstantBuffer(m_context, m_commonConstantData, m_commonConstantBuffer);

    for (Mesh* m : m_meshes) {
        m->Update(m_context, dt);
    }
}

void Renderer::Render(void)
{
    SetPipeline(Graphics::simplePipeline);

    m_context->ClearRenderTargetView(m_renderTargetView.Get(), m_clearColor);
    m_context->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    m_context->RSSetViewports(1, &m_viewport);

    m_context->VSSetConstantBuffers(1, 1, m_commonConstantBuffer.GetAddressOf());

    m_context->PSSetSamplers(0, static_cast<UINT>(Graphics::samplers.size()), Graphics::samplers.data());

    std::vector<ID3D11ShaderResourceView*> commonSRVs = { m_envDiffuse.Get() };

    m_context->PSSetShaderResources(10, static_cast<UINT>(commonSRVs.size()), commonSRVs.data());

    for (Mesh* m : m_meshes) {
        m->Render(m_context);
    }

    SetPipeline(Graphics::skyboxPipeline);
    m_skybox->Render(m_context);

    m_gui->Render();

    m_swapChain->Present(1, 0);
}

void Renderer::CreateDeviceAndSwapChain()
{
    DXGI_MODE_DESC bufferDesc {};
    {
        bufferDesc.Width = m_width;
        bufferDesc.Height = m_height;
        bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        bufferDesc.RefreshRate.Numerator = 60;
        bufferDesc.RefreshRate.Denominator = 1;
    }

    DXGI_SAMPLE_DESC sampleDesc {};
    {
        sampleDesc.Count = 1;
        sampleDesc.Quality = 0;
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc {};
    {
        swapChainDesc.BufferDesc = bufferDesc;
        swapChainDesc.SampleDesc = sampleDesc;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 2;
        swapChainDesc.OutputWindow = m_hWnd;
        swapChainDesc.Windowed = true;
    }

    D3D_FEATURE_LEVEL level;

    DX::ThrowIfFailed(::D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        NULL,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        m_swapChain.GetAddressOf(),
        m_device.GetAddressOf(),
        &level,
        m_context.GetAddressOf()));
}

void Renderer::CreateRenderTargetView(void)
{
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf()));

    DX::ThrowIfFailed(m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.GetAddressOf()));
}

void Renderer::CreateDepthStencilView(void)
{
    DXGI_SAMPLE_DESC sampleDesc {};
    sampleDesc.Count = 1;
    sampleDesc.Quality = 0;

    D3D11_TEXTURE2D_DESC desc {};
    desc.Width = m_width;
    desc.Height = m_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    desc.SampleDesc = sampleDesc;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    ComPtr<ID3D11Texture2D> depthStencilBuffer;

    DX::ThrowIfFailed(m_device->CreateTexture2D(&desc, 0, depthStencilBuffer.GetAddressOf()));
    DX::ThrowIfFailed(m_device->CreateDepthStencilView(depthStencilBuffer.Get(), NULL, m_depthStencilView.GetAddressOf()));
}

void Renderer::SetViewport(void)
{
    m_viewport.TopLeftX = 0;
    m_viewport.TopLeftY = 0;
    m_viewport.Width = static_cast<float>(m_width);
    m_viewport.Height = static_cast<float>(m_height);
    m_viewport.MinDepth = 0.0f;
    m_viewport.MaxDepth = 1.0f;
}

void Renderer::SetPipeline(const Pipeline& pipeline)
{
    // IA
    m_context->IASetInputLayout(pipeline.inputLayout.Get());
    m_context->IASetPrimitiveTopology(pipeline.primitiveTopology);

    // VS
    m_context->VSSetShader(pipeline.VS.Get(), nullptr, 0);

    // RS
    m_context->RSSetState(pipeline.rasterizerState.Get());

    // PS
    m_context->PSSetShader(pipeline.PS.Get(), nullptr, 0);

    // OM
    m_context->OMSetDepthStencilState(pipeline.depthStencilState.Get(), 0);
}
