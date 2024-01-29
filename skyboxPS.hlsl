#include "common.hlsli"

float4 main(PixelInput input) : SV_TARGET
{
    return skybox.Sample(linearWrap, input.posWorld);
}