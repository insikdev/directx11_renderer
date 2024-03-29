#include "pch.h"
#include "utils.h"

void Utils::CompileShaderFromFile(const std::wstring& path, const std::string& version, ComPtr<ID3DBlob>& blob)
{
    UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    DX::ThrowIfFailed(::D3DCompileFromFile(
        path.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        version.c_str(),
        compileFlags,
        0,
        blob.GetAddressOf(),
        nullptr));
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

    DX::ThrowIfFailed(device->CreateBuffer(&desc, &data, buffer.GetAddressOf()));
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

    DX::ThrowIfFailed(device->CreateBuffer(&desc, &data, buffer.GetAddressOf()));
}

void Utils::CreateTextureFromFile(ComPtr<ID3D11Device>& device, const std::wstring& path, ComPtr<ID3D11ShaderResourceView>& view)
{
    DX::ThrowIfFailed(DirectX::CreateWICTextureFromFile(device.Get(), path.c_str(), nullptr, view.GetAddressOf()));
}

void Utils::CreateDDSTextureFromFile(ComPtr<ID3D11Device>& device, const std::wstring& path, ComPtr<ID3D11ShaderResourceView>& view)
{
    ComPtr<ID3D11Texture2D> texture;

    UINT miscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

    DX::ThrowIfFailed(DirectX::CreateDDSTextureFromFileEx(
        device.Get(),
        path.c_str(),
        0,
        D3D11_USAGE_DEFAULT,
        D3D11_BIND_SHADER_RESOURCE,
        0,
        miscFlags,
        DirectX::DDS_LOADER_FLAGS(false),
        (ID3D11Resource**)texture.GetAddressOf(),
        view.GetAddressOf(),
        NULL));
}
