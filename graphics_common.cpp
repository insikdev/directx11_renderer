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

    ComPtr<ID3DBlob> blob;

    Utils::CompileShaderFromFile(TEXT("simpleVS.hlsl"), "vs_5_0", blob);
    DX::ThrowIfFailed(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, simple_VS.GetAddressOf()));

    std::vector<D3D11_INPUT_ELEMENT_DESC> layout {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, pos), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, normal), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(Vertex, uv), D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    DX::ThrowIfFailed(device->CreateInputLayout(layout.data(), static_cast<UINT>(layout.size()), blob->GetBufferPointer(), blob->GetBufferSize(), pos_normal_uv_IL.GetAddressOf()));

    blob.Reset();
    Utils::CompileShaderFromFile(TEXT("simplePS.hlsl"), "ps_5_0", blob);
    DX::ThrowIfFailed(device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, simple_PS.GetAddressOf()));

    blob.Reset();
    Utils::CompileShaderFromFile(TEXT("skyboxVS.hlsl"), "vs_5_0", blob);
    DX::ThrowIfFailed(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, skybox_VS.GetAddressOf()));

    blob.Reset();
    Utils::CompileShaderFromFile(TEXT("skyboxPS.hlsl"), "ps_5_0", blob);
    DX::ThrowIfFailed(device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, skybox_PS.GetAddressOf()));
}

void InitRasterizerState(ComPtr<ID3D11Device>& device)
{
    using namespace Graphics;

    D3D11_RASTERIZER_DESC desc {};

    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_BACK;
    desc.FrontCounterClockwise = false;
    DX::ThrowIfFailed(device->CreateRasterizerState(&desc, solid_cullBack_RS.GetAddressOf()));

    desc.FillMode = D3D11_FILL_WIREFRAME;
    DX::ThrowIfFailed(device->CreateRasterizerState(&desc, wire_cullBack_RS.GetAddressOf()));

    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_NONE;
    DX::ThrowIfFailed(device->CreateRasterizerState(&desc, solid_cullNone_RS.GetAddressOf()));
}

void InitDepthStencilState(ComPtr<ID3D11Device>& device)
{
    using namespace Graphics;

    D3D11_DEPTH_STENCIL_DESC desc {};
    desc.DepthEnable = true;
    desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    desc.DepthFunc = D3D11_COMPARISON_LESS;
    desc.StencilEnable = false;
    DX::ThrowIfFailed(device->CreateDepthStencilState(&desc, simpleDS.GetAddressOf()));

    desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    DX::ThrowIfFailed(device->CreateDepthStencilState(&desc, skyboxDS.GetAddressOf()));
}

void InitSamplerState(ComPtr<ID3D11Device>& device)
{
    using namespace Graphics;

    D3D11_SAMPLER_DESC desc {};
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MinLOD = 0;
    desc.MaxLOD = D3D11_FLOAT32_MAX;

    DX::ThrowIfFailed(device->CreateSamplerState(&desc, linear_wrap_SS.GetAddressOf()));

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