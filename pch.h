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
#include <exception>
#include <iostream>
#include <algorithm>

// library
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

// DirectX
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxtk/SimpleMath.h>
#include <directxtk/WICTextureLoader.h>
#include <directxtk/DDSTextureLoader.h>
#include <wrl/client.h>

using namespace Microsoft::WRL;
using namespace DirectX::SimpleMath;

namespace DX {
inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr)) {
        // Set a breakpoint on this line to catch DirectX API errors
        throw std::exception();
    }
}
}

struct Vertex {
    Vector3 pos;
    Vector3 normal;
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
    Matrix worldInverseTranspose;
};
