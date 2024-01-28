#include "pch.h"
#include "geometry.h"

MeshData Geometry::CreateRectangle(void)
{
    MeshData data;

    data.vertices = {
        { { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { -1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
        { { 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
        { { 1.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
    };

    // CW
    data.indices = { 0, 1, 3, 1, 2, 3 };

    return data;
}
