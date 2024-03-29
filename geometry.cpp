#include "pch.h"
#include "geometry.h"

MeshData Geometry::CreateRectangle(void)
{
    MeshData data;

    data.vertices = {
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },
        { { -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },
        { { 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },
        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } },
    };

    // CW
    data.indices = { 0, 1, 3, 1, 2, 3 };

    return data;
}

MeshData Geometry::CreateCube(float a)
{
    MeshData data;

    std::vector<Vertex> front {
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },
        { { -0.5f, 0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },
        { { 0.5f, 0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },
    };

    std::vector<Vertex> back {
        { { 0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { { -0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
        { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
    };

    std::vector<Vertex> top {
        { { -0.5f, 0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
        { { -0.5f, 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f, 0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
    };

    std::vector<Vertex> bottom {
        { { 0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },
        { { 0.5f, -0.5f, 0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { -0.5f, -0.5f, 0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
    };

    std::vector<Vertex> left {
        { { -0.5f, -0.5f, 0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
        { { -0.5f, 0.5f, 0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { -0.5f, 0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
        { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
    };

    std::vector<Vertex> right {
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
        { { 0.5f, 0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
    };

    data.vertices.insert(data.vertices.end(), front.begin(), front.end());
    data.vertices.insert(data.vertices.end(), back.begin(), back.end());
    data.vertices.insert(data.vertices.end(), top.begin(), top.end());
    data.vertices.insert(data.vertices.end(), bottom.begin(), bottom.end());
    data.vertices.insert(data.vertices.end(), left.begin(), left.end());
    data.vertices.insert(data.vertices.end(), right.begin(), right.end());

    for (auto& v : data.vertices) {
        v.pos *= a;
    }

    // CW
    data.indices = {
        0, 1, 3, 1, 2, 3, // front
        4, 5, 7, 5, 6, 7, // back
        8, 9, 11, 9, 10, 11, // top
        12, 13, 15, 13, 14, 15, // bottom
        16, 17, 19, 17, 18, 19, // left
        20, 21, 23, 21, 22, 23, // right
    };

    return data;
}
