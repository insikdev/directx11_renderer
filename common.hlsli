#pragma pack_matrix(row_major)

// constants
cbuffer MeshConstants : register(b0)
{
    float4x4 world;
    float4x4 worldInverseTranspose;
};

cbuffer CommonConstants : register(b1)
{
    float4x4 view;
    float4x4 proj;
};

struct VertexInput
{
    float3 pos : POSITION;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float3 posWorld : POSITION0;
    float3 normalWorld : NORMAL0;
    float2 uv : TEXCOORD0;
};

// mesh texture
Texture2D diffuse : register(t0);

// global texture
TextureCube skybox : register(t10);

// sampler states
SamplerState linearWrap : register(s0);