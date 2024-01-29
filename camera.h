#pragma once

class Camera {
public:
    Camera(float aspect, float fov = 60.0f);
    ~Camera() = default;

public:
    Matrix GetView(void);
    Matrix GetProj(void);

public:
    Vector3 cameraPos { 3.0f, 1.5f, -3.0f };
    float m_aspect;
    float m_fov;
    float m_near { 0.1f };
    float m_far { 50.0f };
};
