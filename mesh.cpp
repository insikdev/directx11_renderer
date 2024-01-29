#include "pch.h"
#include "mesh.h"
#include "utils.h"

Mesh::Mesh(ComPtr<ID3D11Device>& device, const MeshData& data)
{
    Utils::CreateVertexBuffer(device, data.vertices, m_vertexBuffer);
    Utils::CreateIndexBuffer(device, data.indices, m_indexBuffer);
    Utils::CreateConstantBuffer<MeshConstant>(device, m_constantData, m_constantBuffer);
    indexCount = data.indices.size();
}

void Mesh::Render(ComPtr<ID3D11DeviceContext>& context)
{
    context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
    context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

    context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
    context->DrawIndexed(indexCount, 0, 0);
}
