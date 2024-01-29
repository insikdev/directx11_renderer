#pragma once

class Camera {
public:
    Camera(float aspect, float fov = 60.0f);
    ~Camera() = default;

public:
    void Update(float dt);
    Matrix GetView(void);
    Matrix GetProj(void);

public: // view
    Vector3 pos { 3.0f, 0.5f, -3.0f };
    Vector3 front { Vector3::UnitZ };
    Vector3 up { Vector3::Up };
    Vector3 right { Vector3::Right };
    float yaw { 0.0f };
    float pitch { 0.0f };
    POINT prev {};

public: // projection
    float m_aspect;
    float m_fov;
    float m_near { 0.1f };
    float m_far { 50.0f };
};
