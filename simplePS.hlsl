#include "common.hlsli"

float4 main(PixelInput input) : SV_TARGET
{
    return diffuse.Sample(linearWrap, input.uv);
}