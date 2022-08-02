#pragma once

#ifdef TR_PLATFORM_WINDOWS

extern Terran::Application* Terran::CreateApplication();

int main(int argc, char** argv)
{
	Terran::Log::Init();

	TR_PROFILE_BEGIN_SESSION("Startup", "TerranProfile-Startup.json");
	auto app = Terran::CreateApplication();
	TR_PROFILE_END_SESSION();

	TR_PROFILE_BEGIN_SESSION("Runtime", "TerranProfile-Runtime.json");
	app->Run();
	TR_PROFILE_END_SESSION();

	TR_PROFILE_BEGIN_SESSION("Shutdown", "TerranProfile-Shutdown.json");
	delete app;
	TR_PROFILE_END_SESSION();

	return 0;
}

#endif