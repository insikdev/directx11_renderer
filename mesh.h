#pragma once

class Mesh {
public:
    Mesh(ComPtr<ID3D11Device>& device, const MeshData& data);
    ~Mesh() = default;

public:
    void Update(ComPtr<ID3D11DeviceContext>& context, float dt);
    void Render(ComPtr<ID3D11DeviceContext>& context);

private:
    ComPtr<ID3D11Buffer> m_vertexBuffer;
    ComPtr<ID3D11Buffer> m_indexBuffer;
    ComPtr<ID3D11Buffer> m_constantBuffer;
    MeshConstant m_constantData {};
    UINT indexCount;
    UINT stride { sizeof(Vertex) };
    UINT offset { 0 };

public: // material
    ComPtr<ID3D11ShaderResourceView> diffuseSRV;
};
