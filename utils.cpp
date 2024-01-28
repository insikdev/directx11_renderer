#include "pch.h"
#include "utils.h"

void Utils::CompileShaderFromFile(const std::wstring& path, const std::string& version, ComPtr<ID3DBlob>& blob)
{
    UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    HRESULT hr = ::D3DCompileFromFile(
        path.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        version.c_str(),
        compileFlags,
        0,
        blob.GetAddressOf(),
        nullptr);

    CHECK(hr, "Failed to complie shader");
}

void Utils::CreateVertexBuffer(ComPtr<ID3D11Device>& device, const std::vector<Vertex>& vertices, ComPtr<ID3D11Buffer>& buffer)
{
    D3D11_BUFFER_DESC desc {};
    desc.ByteWidth = static_cast<UINT>(vertices.size() * sizeof(Vertex));
    desc.Usage = D3D11_USAGE_IMMUTABLE;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA data {};
    data.pSysMem = vertices.data();

    HRESULT hr = device->CreateBuffer(&desc, &data, buffer.GetAddressOf());
    CHECK(hr, "Failed to create vertex buffer.");
}

void Utils::CreateIndexBuffer(ComPtr<ID3D11Device>& device, const std::vector<uint32_t>& indices, ComPtr<ID3D11Buffer>& buffer)
{
    D3D11_BUFFER_DESC desc {};
    desc.ByteWidth = static_cast<UINT>(indices.size() * sizeof(uint32_t));
    desc.Usage = D3D11_USAGE_IMMUTABLE;
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA data {};
    data.pSysMem = indices.data();

    HRESULT hr = device->CreateBuffer(&desc, &data, buffer.GetAddressOf());
    CHECK(hr, "Failed to create index buffer.");
}
