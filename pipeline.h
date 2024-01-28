#pragma once

class Pipeline {
public:
    ComPtr<ID3D11VertexShader> VS;
    ComPtr<ID3D11PixelShader> PS;
    ComPtr<ID3D11InputLayout> inputLayout;
    ComPtr<ID3D11RasterizerState> rasterizerState;
    ComPtr<ID3D11DepthStencilState> depthStencilState;
    ComPtr<ID3D11BlendState> blendState;
    D3D11_PRIMITIVE_TOPOLOGY primitiveTopology { D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST };
};
