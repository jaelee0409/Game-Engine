#include <Terran.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Terran::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
    {
        m_VertexArray.reset(Terran::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        std::shared_ptr<Terran::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Terran::VertexBuffer::Create(vertices, sizeof(vertices)));

        Terran::BufferLayout layout = {
            { Terran::ShaderDataType::Float3, "a_Position" },
            { Terran::ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);

        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = {
            0, 1, 2
        };

        std::shared_ptr<Terran::IndexBuffer> indexBuffer;
        indexBuffer.reset(Terran::IndexBuffer::Create(indices, sizeof(vertices) / sizeof(uint32_t)));

        m_VertexArray->SetIndexBuffer(indexBuffer);




        m_SquareVertexArray.reset(Terran::VertexArray::Create());

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };
        std::shared_ptr<Terran::VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(Terran::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        Terran::BufferLayout squareLayout = {
            { Terran::ShaderDataType::Float3, "a_Position" },
            { Terran::ShaderDataType::Float2, "a_TextureCoord" }
        };
        squareVertexBuffer->SetLayout(squareLayout);
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t squareIndices[6] = {
            0, 1, 2, 2, 3, 0
        };

        std::shared_ptr<Terran::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(Terran::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position, 1.0);
                color = v_Color;
            }
        )";

        m_Shader.reset(Terran::Shader::Create(vertexSrc, fragmentSrc));

        std::string vertexSrc2 = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc2 = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            uniform vec3 u_Color;

            void main()
            {
                color = vec4(u_Color, 1.0f);
            }
        )";

        m_Shader2.reset(Terran::Shader::Create(vertexSrc2, fragmentSrc2));
        m_TextureShader.reset(Terran::Shader::Create("assets/shaders/Texture.glsl"));

        m_Texture = Terran::Texture2D::Create("assets/textures/Checkerboard.png");
        m_ExampleTexture = Terran::Texture2D::Create("assets/textures/Example.png");
        std::dynamic_pointer_cast<Terran::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<Terran::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(Terran::Timestep timestep) override
    {
        if (Terran::Input::IsKeyPressed(TR_KEY_LEFT))
                m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
        else if (Terran::Input::IsKeyPressed(TR_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed * timestep;

        if (Terran::Input::IsKeyPressed(TR_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
        else if (Terran::Input::IsKeyPressed(TR_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed * timestep;

        if (Terran::Input::IsKeyPressed(TR_KEY_Q))
            m_CameraRotation += m_CameraRotationSpeed * timestep;
        else if (Terran::Input::IsKeyPressed(TR_KEY_E))
            m_CameraRotation -= m_CameraRotationSpeed * timestep;

        Terran::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Terran::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Terran::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<Terran::OpenGLShader>(m_Shader2)->Bind();
        std::dynamic_pointer_cast<Terran::OpenGLShader>(m_Shader2)->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 25; j++)
            {
                glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Terran::Renderer::Submit(m_Shader2, m_SquareVertexArray, transform);
            }
        }

        m_Texture->Bind();
        Terran::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_ExampleTexture->Bind();
        Terran::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        //Terran::Renderer::Submit(m_Shader, m_VertexArray);

        Terran::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Terran::Event& event) override
    {
    }

private:
    Terran::Ref<Terran::Shader> m_Shader;
    Terran::Ref<Terran::VertexArray> m_VertexArray;

    Terran::Ref<Terran::Shader> m_Shader2, m_TextureShader;
    Terran::Ref<Terran::VertexArray> m_SquareVertexArray;

    Terran::Ref<Terran::Texture2D> m_Texture, m_ExampleTexture;

    Terran::OrthographicCamera m_Camera;

    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 3.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 90.0f;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Terran::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

Terran::Application* Terran::CreateApplication()
{
    return new Sandbox();
}