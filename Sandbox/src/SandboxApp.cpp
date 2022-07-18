#include "pch.h"
#include <Terran.h>

class ExampleLayer : public Terran::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Terran::Input::IsKeyPressed(TR_KEY_TAB))
			TR_TRACE("Tab key is pressed");
	}

	void OnEvent(Terran::Event& event) override
	{
		//TR_TRACE("{0}", event);
	}
};

class Sandbox : public Terran::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Terran::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Terran::Application* Terran::CreateApplication()
{
	return new Sandbox();
}