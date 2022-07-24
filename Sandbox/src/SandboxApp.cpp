#include "pch.h"
#include <Terran.h>

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

        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f, 0.75f, 0.0f,
            -0.75f, 0.75f, 0.0f
        };
        std::shared_ptr<Terran::VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(Terran::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        Terran::BufferLayout squareLayout = {
            { Terran::ShaderDataType::Float3, "a_Position" }
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

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

        m_Shader.reset(new Terran::Shader(vertexSrc, fragmentSrc));

        std::string vertexSrc2 = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc2 = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";

        m_Shader2.reset(new Terran::Shader(vertexSrc2, fragmentSrc2));
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

		Terran::Renderer::Submit(m_Shader2, m_SquareVertexArray);
		Terran::Renderer::Submit(m_Shader, m_VertexArray);

		Terran::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Terran::Event& event) override
	{
	}

private:
	std::shared_ptr<Terran::Shader> m_Shader;
	std::shared_ptr<Terran::VertexArray> m_VertexArray;

	std::shared_ptr<Terran::Shader> m_Shader2;
	std::shared_ptr<Terran::VertexArray> m_SquareVertexArray;

	Terran::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 3.0f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 90.0f;
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