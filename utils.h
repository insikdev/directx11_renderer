#pragma once

class Utils {
public:
    static void CompileShaderFromFile(const std::wstring& path, const std::string& version, ComPtr<ID3DBlob>& blob);
    static void CreateVertexBuffer(ComPtr<ID3D11Device>& device, const std::vector<Vertex>& vertices, ComPtr<ID3D11Buffer>& buffer);
    static void CreateIndexBuffer(ComPtr<ID3D11Device>& device, const std::vector<uint32_t>& indices, ComPtr<ID3D11Buffer>& buffer);

    template <typename T>
    static void CreateConstantBuffer(ComPtr<ID3D11Device>& device, const T& constantData, ComPtr<ID3D11Buffer>& buffer);
};

template <typename T>
inline void Utils::CreateConstantBuffer(ComPtr<ID3D11Device>& device, const T& constantData, ComPtr<ID3D11Buffer>& buffer)
{
    D3D11_BUFFER_DESC desc {};
    desc.ByteWidth = static_cast<UINT>(sizeof(T));
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA data {};
    data.pSysMem = &constantData;

    HRESULT hr = device->CreateBuffer(&desc, &data, buffer.GetAddressOf());
    CHECK(hr, "Failed to create constant buffer.");
}
