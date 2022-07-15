#include "Application.h"

#include "Terran/Events/ApplicationEvent.h"
#include "Terran/Log.h"

namespace Terran {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		TR_TRACE(e);

		while (true);
	}
}