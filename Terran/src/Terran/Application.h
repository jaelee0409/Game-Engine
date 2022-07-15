#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Terran {

	class TERRAN_API Application
	{
	public:
		Application();
		virtual~Application();

		void Run();
	};

	Application* CreateApplication();
}