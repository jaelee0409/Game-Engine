#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Terran/Events/ApplicationEvent.h"
#include "Terran/LayerStack.h"

#include "Terran/ImGui/ImGuiLayer.h"

#include "Terran/Renderer/Shader.h"
#include "Terran/Renderer/Buffer.h"

namespace Terran {

	class Application
	{
	public:
		Application();
		virtual~Application();

		void OnEvent(Event& e);

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}