#include "pch.h"
#include "graphics_common.h"
#include "pipeline.h"
#include "utils.h"

void InitShader(ComPtr<ID3D11Device>& device);
void InitRasterizerState(ComPtr<ID3D11Device>& device);
void InitDepthStencilState(ComPtr<ID3D11Device>& device);
void InitSamplerState(ComPtr<ID3D11Device>& device);
void InitPipeline(void);

namespace Graphics {
// shader
ComPtr<ID3D11VertexShader> simple_VS;
ComPtr<ID3D11PixelShader> simple_PS;
ComPtr<ID3D11VertexShader> skybox_VS;
ComPtr<ID3D11PixelShader> skybox_PS;

// input layout
ComPtr<ID3D11InputLayout> pos_normal_uv_IL;

// rasterizer state
ComPtr<ID3D11RasterizerState> solid_cullBack_RS;
ComPtr<ID3D11RasterizerState> solid_cullNone_RS;
ComPtr<ID3D11RasterizerState> wire_cullBack_RS;

// depth stencil state
ComPtr<ID3D11DepthStencilState> simpleDS;
ComPtr<ID3D11DepthStencilState> skyboxDS;

// sampler state
ComPtr<ID3D11SamplerState> linear_wrap_SS;
std::vector<ID3D11SamplerState*> samplers;

// pipeline
Pipeline simplePipeline;
Pipeline skyboxPipeline;
}

void Graphics::Initialize(ComPtr<ID3D11Device>& device)
{
    InitShader(device);
    InitRasterizerState(device);
    InitDepthStencilState(device);
    InitSamplerState(device);
    InitPipeline();
}

void InitShader(ComPtr<ID3D11Device>& device)
{
    using namespace Graphics;

    HRESULT hr;
    ComPtr<ID3DBlob> blob;

    Utils::CompileShaderFromFile(TEXT("simpleVS.hlsl"), "vs_5_0", blob);
    hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, simple_VS.GetAddressOf());
    CHECK(hr, "Failed to compile vertex shader.");

    std::vector<D3D11_INPUT_ELEMENT_DESC> layout {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, pos), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, normal), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(Vertex, uv), D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    hr = device->CreateInputLayout(layout.data(), static_cast<UINT>(layout.size()), blob->GetBufferPointer(), blob->GetBufferSize(), pos_normal_uv_IL.GetAddressOf());
    CHECK(hr, "Failed to compile input layout.");

    blob.Reset();
    Utils::CompileShaderFromFile(L"simplePS.hlsl", "ps_5_0", blob);
    hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, simple_PS.GetAddressOf());
    CHECK(hr, "Failed to compile pixel shader.");

    blob.Reset();
    Utils::CompileShaderFromFile(L"skyboxVS.hlsl", "vs_5_0", blob);
    hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, skybox_VS.GetAddressOf());
    CHECK(hr, "Failed to compile vertex shader");

    blob.Reset();
    Utils::CompileShaderFromFile(L"skyboxPS.hlsl", "ps_5_0", blob);
    hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, skybox_PS.GetAddressOf());
    CHECK(hr, "Failed to compile pixel shader");
}

void InitRasterizerState(ComPtr<ID3D11Device>& device)
{
    using namespace Graphics;

    HRESULT hr;
    D3D11_RASTERIZER_DESC desc {};

    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_BACK;
    desc.FrontCounterClockwise = false;
    hr = device->CreateRasterizerState(&desc, solid_cullBack_RS.GetAddressOf());
    CHECK(hr, "Failed to create rasterizer state.");

    desc.FillMode = D3D11_FILL_WIREFRAME;
    hr = device->CreateRasterizerState(&desc, wire_cullBack_RS.GetAddressOf());
    CHECK(hr, "Failed to create rasterizer state.");

    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_NONE;
    hr = device->CreateRasterizerState(&desc, solid_cullNone_RS.GetAddressOf());
    CHECK(hr, "Failed to create rasterizer state.");
}

void InitDepthStencilState(ComPtr<ID3D11Device>& device)
{
    using namespace Graphics;
    HRESULT hr;

    D3D11_DEPTH_STENCIL_DESC desc {};
    desc.DepthEnable = true;
    desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    desc.DepthFunc = D3D11_COMPARISON_LESS;
    desc.StencilEnable = false;

    hr = device->CreateDepthStencilState(&desc, simpleDS.GetAddressOf());
    CHECK(hr, "Failed to create depth stencil state.");

    desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    hr = device->CreateDepthStencilState(&desc, skyboxDS.GetAddressOf());
    CHECK(hr, "Failed to create depth stencil state.");
}

void InitSamplerState(ComPtr<ID3D11Device>& device)
{
    using namespace Graphics;

    HRESULT hr;
    D3D11_SAMPLER_DESC desc {};
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MinLOD = 0;
    desc.MaxLOD = D3D11_FLOAT32_MAX;

    hr = device->CreateSamplerState(&desc, linear_wrap_SS.GetAddressOf());
    CHECK(hr, "Failed to create sampler state.");

    samplers.push_back(linear_wrap_SS.Get());
}

void InitPipeline()
{
    using namespace Graphics;

    simplePipeline.VS = simple_VS;
    simplePipeline.PS = simple_PS;
    simplePipeline.inputLayout = pos_normal_uv_IL;
    simplePipeline.rasterizerState = solid_cullBack_RS;
    simplePipeline.depthStencilState = simpleDS;

    skyboxPipeline.VS = skybox_VS;
    skyboxPipeline.PS = skybox_PS;
    skyboxPipeline.inputLayout = pos_normal_uv_IL;
    skyboxPipeline.rasterizerState = solid_cullNone_RS;
    skyboxPipeline.depthStencilState = skyboxDS;
}