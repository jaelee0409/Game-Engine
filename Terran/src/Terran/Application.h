#pragma once

#include "Core.h"

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