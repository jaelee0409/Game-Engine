#include "pch.h"
#include "OrthographicCameraController.h"

#include "Terran/Core/Input.h"
#include "Terran/Core/KeyCodes.h"

namespace Terran {

    

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio), m_Rotation(rotation),
        m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep timestep)
    {
        if (Input::IsKeyPressed(TR_KEY_A))
            m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
        else if (Input::IsKeyPressed(TR_KEY_D))
            m_CameraPosition.x += m_CameraMoveSpeed * timestep;

        if (Input::IsKeyPressed(TR_KEY_S))
            m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
        else if (Input::IsKeyPressed(TR_KEY_W))
            m_CameraPosition.y += m_CameraMoveSpeed * timestep;

        m_Camera.SetPosition(m_CameraPosition);

        if (m_Rotation)
        {
            if (Input::IsKeyPressed(TR_KEY_Q))
                m_CameraRotation += m_CameraRotationSpeed * timestep;
            else if (Input::IsKeyPressed(TR_KEY_E))
                m_CameraRotation -= m_CameraRotationSpeed * timestep;

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_CameraMoveSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(TR_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(TR_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffset() * m_CameraZoomSpeed;
        m_ZoomLevel = std::min(m_ZoomLevel, 10.0f);
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

        return false;
    }

}
