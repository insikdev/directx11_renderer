#include "common.hlsli"

PixelInput main(VertexInput input)
{
    PixelInput output;
    
    float4 pos = float4(input.pos, 1.0f);
    pos = mul(pos, world);
    pos = mul(pos, view);
    pos = mul(pos, proj);
    
    output.pos = pos;
    output.uv = input.uv;
    
    return output;
}