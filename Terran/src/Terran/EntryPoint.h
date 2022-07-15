#pragma once

#ifdef TR_PLATFORM_WINDOWS

extern Terran::Application* Terran::CreateApplication();

int main(int argc, char** argv)
{
	Terran::Log::Init();
	TR_CORE_WARN("INIT CORE LOG");
	int a = 5;
	TR_INFO("INIT CLIENT LOG var={0}", a);

	auto app = Terran::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif