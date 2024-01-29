#include "common.hlsli"

PixelInput main(VertexInput input)
{
    PixelInput output;
    
    float4 pos = float4(input.pos, 1.0f);
    
    pos = mul(pos, world);
    output.posWorld = pos;
    
    pos = mul(pos, view);
    pos = mul(pos, proj);
    
    output.pos = pos;
    output.normalWorld = normalize(mul(float4(input.normal, 0.0), worldInverseTranspose).xyz);
    output.uv = input.uv;
    
    return output;
}