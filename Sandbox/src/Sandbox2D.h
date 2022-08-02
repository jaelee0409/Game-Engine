#pragma once

#include <Terran.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sandbox2D : public Terran::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Terran::Timestep timestep) override;
    void OnEvent(Terran::Event& e) override;
    virtual void OnImGuiRender() override;
    bool OnWindowResize(Terran::WindowResizeEvent& event);
    bool OnMouseScrolled(Terran::MouseScrolledEvent& event);
private:
    Terran::ShaderLibrary m_ShaderLibrary;
    Terran::Ref<Terran::Shader> m_Shader;
    Terran::Ref<Terran::VertexArray> m_VertexArray;

    Terran::Ref<Terran::Texture2D> m_Texture, m_ExampleTexture;

    float m_CameraZoom = 1.0f;
    float m_AspectRatio = 16.0f / 9.0f;
    Terran::OrthographicCameraController m_CameraController;

    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 3.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 90.0f;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

    int32_t m_MaxQuadsPerDraw = 10000;
    int32_t m_NumberOfSprites = 100;

    float m_FrameTimeGraph[100];
    int values_offset = 0;
};

