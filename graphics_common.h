#pragma once

class Pipeline;

namespace Graphics {
// shader
extern ComPtr<ID3D11VertexShader> simple_VS;
extern ComPtr<ID3D11PixelShader> simple_PS;

// input layout
extern ComPtr<ID3D11InputLayout> inputLayout;

// rasterizer state
extern ComPtr<ID3D11RasterizerState> solid_back_cw_RS;
extern ComPtr<ID3D11RasterizerState> solid_back_ccw_RS;
extern ComPtr<ID3D11RasterizerState> wire_back_cw_RS;

extern Pipeline simplePipeline;

void Initialize(ComPtr<ID3D11Device>& device);
}