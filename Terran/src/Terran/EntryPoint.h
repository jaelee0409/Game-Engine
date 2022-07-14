#pragma once

#ifdef TR_PLATFORM_WINDOWS

extern Terran::Application* Terran::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Terran::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif