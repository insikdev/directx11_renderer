#pragma once

class Utils {
public:
    static void CompileShaderFromFile(const std::wstring& path, const std::string& version, ComPtr<ID3DBlob>& blob);
    static void CreateVertexBuffer(ComPtr<ID3D11Device>& device, const std::vector<Vertex>& vertices, ComPtr<ID3D11Buffer>& buffer);
    static void CreateIndexBuffer(ComPtr<ID3D11Device>& device, const std::vector<uint32_t>& indices, ComPtr<ID3D11Buffer>& buffer);
};
