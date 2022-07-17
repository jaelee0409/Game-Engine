#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Terran/Events/ApplicationEvent.h"
#include "Terran/LayerStack.h"

namespace Terran {

	class TERRAN_API Application
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
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}