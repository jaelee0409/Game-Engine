#include "Sandbox2D.h"

//static Terran::Ref<Terran::Renderer2D> s_Renderer2D;

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"),
    m_CameraController(1280.0f / 720.0f)
{
    //m_Texture = Terran::Texture2D::Create("assets/textures/Checkerboard.png");
    //m_ExampleTexture = Terran::Texture2D::Create("assets/textures/Example.png");

    //if (!s_Renderer2D)
    //{
    //    s_Renderer2D = std::make_shared<Terran::RendererAPI>();
    //}

    //memset(m_FrameTimeGraph, 0, sizeof(float) * 100);
}

void Sandbox2D::OnAttach()
{
    m_Texture = Terran::Texture2D::Create("assets/textures/Checkerboard.png");
    m_ExampleTexture = Terran::Texture2D::Create("assets/textures/Example.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Terran::Timestep timestep)
{
    //s_Renderer2D->ResetStats();
    TR_PROFILE_FUNCTION();

    m_CameraController.OnUpdate(timestep);

    Terran::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Terran::RenderCommand::Clear();

    Terran::Renderer2D::BeginScene(m_CameraController.GetCamera());
    //s_Renderer2D->BeginScene(m_CameraController.GetCamera());

    float xOffset = -2.5f;
    float yOffset = -2.5f;
    for (int y = 0; y < m_NumberOfSprites; y++)
    {
        float yPos = y * 0.05f + yOffset;
        for (int x = 0; x < m_NumberOfSprites; x++)
        {
            float xPos = x * 0.05f + xOffset;
            //s_Renderer2D->DrawQuad({ xp, yp }, { 0.045f, 0.045f }, glm::vec4((float)x / m_NumberOfSprites, 0.3f, (float)y / m_NumberOfSprites), );
            /*glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
            Terran::Renderer::Submit(m_Shader2, m_SquareVertexArray, transform);*/
        }
    }

    //Terran::Renderer::Submit(m_Shader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Terran::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 2.0f, 2.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Terran::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.2f, 0.8f, 1.0f });
    Terran::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.4f, 10.9f }, m_ExampleTexture);
    Terran::Renderer2D::EndScene();
    //s_Renderer2D->Flush();
}

void Sandbox2D::OnEvent(Terran::Event& e)
{
    m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
    TR_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

