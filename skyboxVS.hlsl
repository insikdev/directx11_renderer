#include "common.hlsli"

PixelInput main(VertexInput input)
{
    PixelInput output;
    
    float4 pos = float4(mul(input.pos, (float3x3) view), 1.0);
    pos = mul(pos, proj);
    
    output.pos = pos.xyww;
    output.posWorld = input.pos;
    
    return output;
}