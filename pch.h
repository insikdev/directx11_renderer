#pragma once

// Windows
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// C++
#include <cstdint>
#include <stdlib.h>
#include <string>
#include <vector>

// library
#include <spdlog/spdlog.h>

// DirectX
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxtk/SimpleMath.h>
#include <directxtk/WICTextureLoader.h>
#include <wrl/client.h>

using namespace Microsoft::WRL;
using namespace DirectX::SimpleMath;

#define CHECK(hr, errorMsg)     \
    if (FAILED(hr)) {           \
        SPDLOG_ERROR(errorMsg); \
        exit(EXIT_FAILURE);     \
    }

struct Vertex {
    Vector3 pos;
    Vector2 uv;
};

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

struct CommonConstant {
    Matrix view;
    Matrix proj;
};

struct MeshConstant {
    Matrix world;
};