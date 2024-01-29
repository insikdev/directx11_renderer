#include "pch.h"
#include "renderer.h"
#include "graphics_common.h"
#include "pipeline.h"
#include "geometry.h"
#include "mesh.h"
#include "utils.h"

Renderer::Renderer(uint32_t width, uint32_t height, HWND hWnd)
    : m_width { width }
    , m_height { height }
    , m_hWnd { hWnd }
    , camera { static_cast<float>(width) / height }
{
    CreateDeviceAndSwapChain();
    CreateRenderTargetView();
    SetViewport();

    Graphics::Initialize(m_device);
    SetPipeline(Graphics::simplePipeline);

    mesh = new Mesh { m_device, Geometry::CreateCube() };

    Utils::CreateConstantBuffer<CommonConstant>(m_device, m_commonConstantData, m_commonConstantBuffer);
}

Renderer::~Renderer()
{
}

void Renderer::Update(void)
{
    m_commonConstantData.view = camera.GetView();
    m_commonConstantData.proj = camera.GetProj();

    D3D11_MAPPED_SUBRESOURCE mappedResource {};
    m_context->Map(m_commonConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy(mappedResource.pData, &m_commonConstantData, sizeof(CommonConstant));
    m_context->Unmap(m_commonConstantBuffer.Get(), 0);
}

void Renderer::Render(void)
{
    float clear[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);
    m_context->ClearRenderTargetView(m_renderTargetView.Get(), clear);
    m_context->RSSetViewports(1, &m_viewport);

    m_context->VSSetConstantBuffers(1, 1, m_commonConstantBuffer.GetAddressOf());

    mesh->Render(m_context);
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

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
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
        m_context.GetAddressOf());

    CHECK(hr, "Failed to create device and swap chain");
}

void Renderer::CreateRenderTargetView(void)
{
    HRESULT hr;

    ComPtr<ID3D11Texture2D> backBuffer;
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
    CHECK(hr, "Failed to get back buffer");

    m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.GetAddressOf());
    CHECK(hr, "Failed to create render target view");
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
    m_context->IASetInputLayout(pipeline.inputLayout.Get());
    m_context->IASetPrimitiveTopology(pipeline.primitiveTopology);

    m_context->VSSetShader(pipeline.VS.Get(), nullptr, 0);

    m_context->RSSetState(pipeline.rasterizerState.Get());

    m_context->PSSetShader(pipeline.PS.Get(), nullptr, 0);
}
