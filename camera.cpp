#include "pch.h"
#include "camera.h"

Camera::Camera(float aspect, float fov)
    : m_aspect { aspect }
    , m_fov { fov }
{
}

void Camera::Update(float dt)
{
    if (GetAsyncKeyState(0x57) & 0x8000) {
        pos += front * dt;
    }
    if (GetAsyncKeyState(0x53) & 0x8000) {
        pos -= front * dt;
    }
    if (GetAsyncKeyState(0x44) & 0x8000) {
        pos += right * dt;
    }
    if (GetAsyncKeyState(0x41) & 0x8000) {
        pos -= right * dt;
    }

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
        POINT currentPos {};
        GetCursorPos(&currentPos);

        if (prev.x != 0 && prev.y != 0) {
            int dx = currentPos.x - prev.x;
            int dy = currentPos.y - prev.y;
            yaw += static_cast<float>(dx);
            pitch += static_cast<float>(dy);
            pitch = std::clamp(pitch, -30.0f, 30.0f);
        }

        prev = currentPos;
    } else {
        prev.x = 0;
        prev.y = 0;
    }

    Matrix rotationMatrix = Matrix::CreateRotationX(DirectX::XMConvertToRadians(pitch)) * Matrix::CreateRotationY(DirectX::XMConvertToRadians(yaw));
    front = Vector3::Transform(Vector3::UnitZ, rotationMatrix);
    right = Vector3::Up.Cross(front);
    up = front.Cross(right);
}

Matrix Camera::GetView(void)
{
    return DirectX::XMMatrixLookAtLH(pos, pos + front, Vector3::Up);
}

Matrix Camera::GetProj(void)
{
    return DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(m_fov), m_aspect, m_near, m_far);
}
