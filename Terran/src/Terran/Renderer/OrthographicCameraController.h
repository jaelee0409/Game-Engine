#pragma once

#include "Terran/Renderer/OrthographicCamera.h"
#include "Terran/Core/Timestep.h"

#include "Terran/Events/ApplicationEvent.h"
#include "Terran/Events/MouseEvent.h"

namespace Terran {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep timestep);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation = false;
        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        //float m_CameraMoveSpeed = 3.0f;
        float m_CameraMoveSpeed = m_ZoomLevel;

        float m_CameraZoomSpeed = 0.25f;

        float m_CameraRotation = 0.0f;
        float m_CameraRotationSpeed = 90.0f;
    };

}
