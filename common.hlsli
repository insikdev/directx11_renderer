#pragma pack_matrix(row_major)

cbuffer MeshConstants : register(b0)
{
    float4x4 world;
};

cbuffer CommonConstants : register(b1)
{
    float4x4 view;
    float4x4 proj;
};

struct VertexInput
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
};