#pragma once

class Pipeline;

namespace Graphics {
// sampler states
extern std::vector<ID3D11SamplerState*> samplers;

// pipeline
extern Pipeline simplePipeline;
extern Pipeline skyboxPipeline;

void Initialize(ComPtr<ID3D11Device>& device);
}