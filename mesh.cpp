#include "pch.h"
#include "mesh.h"
#include "utils.h"

Mesh::Mesh(ComPtr<ID3D11Device>& device, const MeshData& data)
{
    Utils::CreateVertexBuffer(device, data.vertices, vertexBuffer);
    Utils::CreateIndexBuffer(device, data.indices, indexBuffer);
    indexCount = data.indices.size();
}

void Mesh::Render(ComPtr<ID3D11DeviceContext>& context)
{
    context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    context->DrawIndexed(indexCount, 0, 0);
}
