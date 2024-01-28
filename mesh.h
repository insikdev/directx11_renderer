#pragma once

class Mesh {
public:
    Mesh(ComPtr<ID3D11Device>& device, const MeshData& data);
    ~Mesh() = default;

public:
    void Render(ComPtr<ID3D11DeviceContext>& context);

private:
    ComPtr<ID3D11Buffer> vertexBuffer;
    ComPtr<ID3D11Buffer> indexBuffer;
    UINT indexCount;
    UINT stride { sizeof(Vertex) };
    UINT offset { 0 };
};
