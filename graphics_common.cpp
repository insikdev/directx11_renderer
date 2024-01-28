#include "pch.h"
#include "graphics_common.h"
#include "pipeline.h"
#include "utils.h"

void InitShader(ComPtr<ID3D11Device>& device);
void InitRS(ComPtr<ID3D11Device>& device);

namespace Graphics {
// shader
ComPtr<ID3D11VertexShader> simple_VS;
ComPtr<ID3D11PixelShader> simple_PS;

// input layout
ComPtr<ID3D11InputLayout> inputLayout;

// rasterizer state
ComPtr<ID3D11RasterizerState> solid_back_cw_RS;
ComPtr<ID3D11RasterizerState> solid_back_ccw_RS;
ComPtr<ID3D11RasterizerState> wire_back_cw_RS;

Pipeline simplePipeline;
}

void Graphics::Initialize(ComPtr<ID3D11Device>& device)
{
    InitShader(device);
    InitRS(device);

    //
    simplePipeline.VS = simple_VS;
    simplePipeline.PS = simple_PS;
    simplePipeline.inputLayout = inputLayout;
    simplePipeline.rasterizerState = solid_back_cw_RS;
}

void InitShader(ComPtr<ID3D11Device>& device)
{
    using namespace Graphics;
    HRESULT hr;
    ComPtr<ID3DBlob> blob;

    Utils::CompileShaderFromFile(L"simpleVS.hlsl", "vs_5_0", blob);
    hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, simple_VS.GetAddressOf());
    CHECK(hr, "Failed to compile vertex shader");

    std::vector<D3D11_INPUT_ELEMENT_DESC> layout {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    hr = device->CreateInputLayout(layout.data(), static_cast<UINT>(layout.size()), blob->GetBufferPointer(), blob->GetBufferSize(), inputLayout.GetAddressOf());

    blob.Reset();
    Utils::CompileShaderFromFile(L"simplePS.hlsl", "ps_5_0", blob);
    hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, simple_PS.GetAddressOf());
    CHECK(hr, "Failed to compile pixel shader");
}

void InitRS(ComPtr<ID3D11Device>& device)
{
    using namespace Graphics;
    HRESULT hr;
    D3D11_RASTERIZER_DESC rasterizerDesc {};

    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    rasterizerDesc.FrontCounterClockwise = false;
    hr = device->CreateRasterizerState(&rasterizerDesc, solid_back_cw_RS.GetAddressOf());
    CHECK(hr, "Failed to create rasterizer state");

    rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    hr = device->CreateRasterizerState(&rasterizerDesc, wire_back_cw_RS.GetAddressOf());
    CHECK(hr, "Failed to create rasterizer state");

    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.FrontCounterClockwise = true;
    hr = device->CreateRasterizerState(&rasterizerDesc, solid_back_ccw_RS.GetAddressOf());
    CHECK(hr, "Failed to create rasterizer state");
}
