#include "common.hlsli"

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
    return texture0.Sample(sampler0, input.uv);
}