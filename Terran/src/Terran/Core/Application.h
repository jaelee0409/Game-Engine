#pragma once

#include "Core.h"
#include "Terran/Core/Timestep.h"

#include "Terran/Events/Event.h"
#include "Window.h"
#include "Terran/Events/ApplicationEvent.h"
#include "Terran/Core/LayerStack.h"

#include "Terran/ImGui/ImGuiLayer.h"

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
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}