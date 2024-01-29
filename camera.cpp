#include "pch.h"
#include "camera.h"

Camera::Camera(float aspect, float fov)
    : m_aspect { aspect }
    , m_fov { fov }
{
}

Matrix Camera::GetView(void)
{
    return DirectX::XMMatrixLookAtLH(cameraPos, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
}

Matrix Camera::GetProj(void)
{
    return DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(m_fov), m_aspect, m_near, m_far);
}
